//
// Copyright 2020 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

#include <cctype>
#include <map>

#include "compiler/translator/ImmutableStringBuilder.h"
#include "compiler/translator/SymbolTable.h"
#include "compiler/translator/TranslatorMetalDirect.h"
#include "compiler/translator/TranslatorMetalDirect/AstHelpers.h"
#include "compiler/translator/TranslatorMetalDirect/ConstantNames.h"
#include "compiler/translator/TranslatorMetalDirect/Debug.h"
#include "compiler/translator/TranslatorMetalDirect/DebugSink.h"
#include "compiler/translator/TranslatorMetalDirect/EmitMetal.h"
#include "compiler/translator/TranslatorMetalDirect/EnvironmentVariable.h"
#include "compiler/translator/TranslatorMetalDirect/Layout.h"
#include "compiler/translator/TranslatorMetalDirect/Name.h"
#include "compiler/translator/TranslatorMetalDirect/ProgramPrelude.h"
#include "compiler/translator/TranslatorMetalDirect/RewritePipelines.h"
#include "compiler/translator/tree_util/IntermTraverse.h"
#include "libANGLE/renderer/metal/mtl_constants.h"

using namespace sh;

////////////////////////////////////////////////////////////////////////////////

#if defined(ANGLE_ENABLE_ASSERTS)
using Sink = DebugSink;
#else
using Sink = TInfoSinkBase;
#endif

////////////////////////////////////////////////////////////////////////////////

namespace
{

struct VarDecl
{
    explicit VarDecl(const TVariable &var) : mVariable(&var), mIsField(false) {}
    explicit VarDecl(const TField &field) : mField(&field), mIsField(true) {}

    ANGLE_INLINE const TVariable &variable() const
    {
        ASSERT(isVariable());
        return *mVariable;
    }

    ANGLE_INLINE const TField &field() const
    {
        ASSERT(isField());
        return *mField;
    }

    ANGLE_INLINE bool isVariable() const { return !mIsField; }

    ANGLE_INLINE bool isField() const { return mIsField; }

    const TType &type() const { return isField() ? *field().type() : variable().getType(); }

    SymbolType symbolType() const
    {
        return isField() ? field().symbolType() : variable().symbolType();
    }

  private:
    union
    {
        const TVariable *mVariable;
        const TField *mField;
    };
    bool mIsField;
};

class GenMetalTraverser : public TIntermTraverser
{
  public:
    ~GenMetalTraverser() override;

    GenMetalTraverser(const TCompiler &compiler,
                      Sink &out,
                      IdGen &idGen,
                      const PipelineStructs &pipelineStructs,
                      const Invariants &invariants,
                      SymbolEnv &symbolEnv);

    void visitSymbol(TIntermSymbol *) override;
    void visitConstantUnion(TIntermConstantUnion *) override;
    bool visitSwizzle(Visit, TIntermSwizzle *) override;
    bool visitBinary(Visit, TIntermBinary *) override;
    bool visitUnary(Visit, TIntermUnary *) override;
    bool visitTernary(Visit, TIntermTernary *) override;
    bool visitIfElse(Visit, TIntermIfElse *) override;
    bool visitSwitch(Visit, TIntermSwitch *) override;
    bool visitCase(Visit, TIntermCase *) override;
    void visitFunctionPrototype(TIntermFunctionPrototype *) override;
    bool visitFunctionDefinition(Visit, TIntermFunctionDefinition *) override;
    bool visitAggregate(Visit, TIntermAggregate *) override;
    bool visitBlock(Visit, TIntermBlock *) override;
    bool visitGlobalQualifierDeclaration(Visit, TIntermGlobalQualifierDeclaration *) override;
    bool visitDeclaration(Visit, TIntermDeclaration *) override;
    bool visitLoop(Visit, TIntermLoop *) override;
    bool visitForLoop(TIntermLoop *);
    bool visitWhileLoop(TIntermLoop *);
    bool visitDoWhileLoop(TIntermLoop *);
    bool visitBranch(Visit, TIntermBranch *) override;

  private:
    using FuncToName = std::map<ImmutableString, Name>;
    static FuncToName BuildFuncToName();

    struct EmitVariableDeclarationConfig
    {
        bool isParameter                = false;
        bool isMainParameter            = false;
        bool emitPostQualifier          = false;
        bool isPacked                   = false;
        bool disableStructSpecifier     = false;
        bool isUBO                      = false;
        const AddressSpace *isPointer   = nullptr;
        const AddressSpace *isReference = nullptr;
    };

    struct EmitTypeConfig
    {
        const EmitVariableDeclarationConfig *evdConfig = nullptr;
    };

    void emitIndentation();
    void emitOpeningPointerParen();
    void emitClosingPointerParen();
    void emitFunctionSignature(const TFunction &func);
    void emitFunctionReturn(const TFunction &func);
    void emitFunctionParameter(const TFunction &func, const TVariable &param);

    void emitNameOf(const TField &object);
    void emitNameOf(const TSymbol &object);
    void emitNameOf(const VarDecl &object);

    void emitBareTypeName(const TType &type, const EmitTypeConfig &etConfig);
    void emitType(const TType &type, const EmitTypeConfig &etConfig);
    void emitPostQualifier(const EmitVariableDeclarationConfig &evdConfig,
                           const VarDecl &decl,
                           const TQualifier qualifier);

    struct FieldAnnotationIndices
    {
        size_t attribute = 0;
        size_t color     = 0;
    };

    void emitFieldDeclaration(const TField &field,
                              const TStructure &parent,
                              FieldAnnotationIndices &annotationIndices);
    void emitAttributeDeclaration(const TField &field, FieldAnnotationIndices &annotationIndices);
    void emitUniformBufferDeclaration(const TField &field, FieldAnnotationIndices &annotationIndices);
    void emitStructDeclaration(const TType &type);
    void emitOrdinaryVariableDeclaration(const VarDecl &decl,
                                         const EmitVariableDeclarationConfig &evdConfig);
    void emitVariableDeclaration(const VarDecl &decl,
                                 const EmitVariableDeclarationConfig &evdConfig);

    void emitOpenBrace();
    void emitCloseBrace();

    void groupedTraverse(TIntermNode &node);

    const TField &getDirectField(const TFieldListCollection &fieldsNode,
                                 const TConstantUnion &index);
    const TField &getDirectField(const TIntermTyped &fieldsNode, TIntermTyped &indexNode);

    const TConstantUnion *emitConstantUnionArray(const TConstantUnion *const constUnion,
                                                 const size_t size);

    const TConstantUnion *emitConstantUnion(const TType &type, const TConstantUnion *constUnion);

    void emitSingleConstant(const TConstantUnion *const constUnion);

  private:
    Sink &mOut;
    const TCompiler &mCompiler;
    const PipelineStructs &mPipelineStructs;
    const Invariants &mInvariants;
    SymbolEnv &mSymbolEnv;
    IdGen &mIdGen;
    int mIndentLevel           = -1;
    int mLastIndentationPos    = -1;
    int mOpenPointerParenCount = 0;
    bool mParentIsSwitch    = false;
    bool isTraversingVertexMain  = false;
    bool mTemporarilyDisableSemicolon = false;
    std::unordered_map<const TSymbol *, Name> mRenamedSymbols;
    const FuncToName mFuncToName   = BuildFuncToName();
    size_t mMainTextureIndex       = 0;
    size_t mMainSamplerIndex       = 0;
    size_t mMainUniformBufferIndex = rx::mtl::kDefaultUniformsBindingIndex;
};

}  // anonymous namespace

GenMetalTraverser::~GenMetalTraverser()
{
    ASSERT(mIndentLevel == -1);
    ASSERT(!mParentIsSwitch);
    ASSERT(mOpenPointerParenCount == 0);
}

GenMetalTraverser::GenMetalTraverser(const TCompiler &compiler,
                                     Sink &out,
                                     IdGen &idGen,
                                     const PipelineStructs &pipelineStructs,
                                     const Invariants &invariants,
                                     SymbolEnv &symbolEnv)
    : TIntermTraverser(true, false, false),
      mOut(out),
      mCompiler(compiler),
      mPipelineStructs(pipelineStructs),
      mInvariants(invariants),
      mSymbolEnv(symbolEnv),
      mIdGen(idGen)
{}

void GenMetalTraverser::emitIndentation()
{
    ASSERT(mIndentLevel >= 0);

    if (mLastIndentationPos == mOut.size())
    {
        return;  // Line is already indented.
    }

    for (int i = 0; i < mIndentLevel; ++i)
    {
        mOut << "  ";
    }

    mLastIndentationPos = mOut.size();
}

void GenMetalTraverser::emitOpeningPointerParen()
{
    mOut << "(*";
    mOpenPointerParenCount++;
}

void GenMetalTraverser::emitClosingPointerParen()
{
    if (mOpenPointerParenCount > 0)
    {
        mOut << ")";
        mOpenPointerParenCount--;
    }
}

static const char *GetOperatorString(TOperator op,
                                     const TType &resultType,
                                     const TType *argType0,
                                     const TType *argType1 = nullptr,
                                     const TType *argType2 = nullptr)
{
    switch (op)
    {
        case TOperator::EOpComma:
            return ",";
        case TOperator::EOpAssign:
            return "=";
        case TOperator::EOpInitialize:
            return "=";
        case TOperator::EOpAddAssign:
            return "+=";
        case TOperator::EOpSubAssign:
            return "-=";
        case TOperator::EOpMulAssign:
            return "*=";
        case TOperator::EOpDivAssign:
            return "/=";
        case TOperator::EOpIModAssign:
            return "%=";
        case TOperator::EOpBitShiftLeftAssign:
            return "<<=";  // TODO: Check logical vs arithmetic shifting.
        case TOperator::EOpBitShiftRightAssign:
            return ">>=";  // TODO: Check logical vs arithmetic shifting.
        case TOperator::EOpBitwiseAndAssign:
            return "&=";
        case TOperator::EOpBitwiseXorAssign:
            return "^=";
        case TOperator::EOpBitwiseOrAssign:
            return "|=";
        case TOperator::EOpAdd:
            return "+";
        case TOperator::EOpSub:
            return "-";
        case TOperator::EOpMul:
            return "*";
        case TOperator::EOpDiv:
            return "/";
        case TOperator::EOpIMod:
            return "%";
        case TOperator::EOpBitShiftLeft:
            return "<<";  // TODO: Check logical vs arithmetic shifting.
        case TOperator::EOpBitShiftRight:
            return ">>";  // TODO: Check logical vs arithmetic shifting.
        case TOperator::EOpBitwiseAnd:
            return "&";
        case TOperator::EOpBitwiseXor:
            return "^";
        case TOperator::EOpBitwiseOr:
            return "|";
        case TOperator::EOpLessThan:
            return "<";
        case TOperator::EOpGreaterThan:
            return ">";
        case TOperator::EOpLessThanEqual:
            return "<=";
        case TOperator::EOpGreaterThanEqual:
            return ">=";
        case TOperator::EOpLessThanComponentWise:
            return "<";
        case TOperator::EOpLessThanEqualComponentWise:
            return "<=";
        case TOperator::EOpGreaterThanEqualComponentWise:
            return ">=";
        case TOperator::EOpGreaterThanComponentWise:
            return ">";
        case TOperator::EOpLogicalOr:
            return "||";
        case TOperator::EOpLogicalXor:
            return "!=/*xor*/";  // XXX: This might need to be handled differently for some obtuse
                                 // use case.
        case TOperator::EOpLogicalAnd:
            return "&&";
        case TOperator::EOpNegative:
            return "-";
        case TOperator::EOpPositive:
            if (argType0->isMatrix())
            {
                return "";
            }
            return "+";
        case TOperator::EOpLogicalNot:
            return "!";
        case TOperator::EOpLogicalNotComponentWise:
            return "!";
        case TOperator::EOpBitwiseNot:
            return "~";
        case TOperator::EOpPostIncrement:
            return "++";
        case TOperator::EOpPostDecrement:
            return "--";
        case TOperator::EOpPreIncrement:
            return "++";
        case TOperator::EOpPreDecrement:
            return "--";
        case TOperator::EOpVectorTimesScalarAssign:
            return "*=";
        case TOperator::EOpVectorTimesMatrixAssign:
            return "*=";
        case TOperator::EOpMatrixTimesScalarAssign:
            return "*=";
        case TOperator::EOpMatrixTimesMatrixAssign:
            return "*=";
        case TOperator::EOpVectorTimesScalar:
            return "*";
        case TOperator::EOpVectorTimesMatrix:
            return "*";
        case TOperator::EOpMatrixTimesVector:
            return "*";
        case TOperator::EOpMatrixTimesScalar:
            return "*";
        case TOperator::EOpMatrixTimesMatrix:
            return "*";
        case TOperator::EOpEqualComponentWise:
            return "==";
        case TOperator::EOpNotEqualComponentWise:
            return "!=";

        case TOperator::EOpEqual:
            if((argType0->getStruct() && argType1->getStruct()) &&
               (argType0->isArray() && argType1->isArray()))
            {
                return "ANGLE_equalStructArray";
            }
           
            if ((argType0->isVector() && argType1->isVector()) ||
                (argType0->getStruct() && argType1->getStruct()) ||
                (argType0->isArray() && argType1->isArray()) ||
                (argType0->isMatrix() && argType1->isMatrix()))

            {
                return "ANGLE_equal";
            }

            return "==";

        case TOperator::EOpNotEqual:
            if((argType0->getStruct() && argType1->getStruct()) &&
               (argType0->isArray() && argType1->isArray()))
            {
                return "ANGLE_notEqualStructArray";
            }
           
            if ((argType0->isVector() && argType1->isVector()) ||
                (argType0->isArray() && argType1->isArray()) ||
                (argType0->isMatrix() && argType1->isMatrix()))
            {
                return "ANGLE_notEqual";
            }
            else if (argType0->getStruct() && argType1->getStruct())
            {
                return "ANGLE_notEqualStruct";
            }
            return "!=";

        case TOperator::EOpKill:
            TODO();
            return "kill";
        case TOperator::EOpReturn:
            return "return";
        case TOperator::EOpBreak:
            return "break";
        case TOperator::EOpContinue:
            return "continue";

        case TOperator::EOpRadians:
            return "ANGLE_radians";
        case TOperator::EOpDegrees:
            return "ANGLE_degrees";
        case TOperator::EOpAtan:
            return "ANGLE_atan";
        case TOperator::EOpMod:
            return "ANGLE_mod";  // differs from metal::mod
        case TOperator::EOpRefract:
            return "ANGLE_refract";
        case TOperator::EOpDistance:
            return "ANGLE_distance";
        case TOperator::EOpLength:
            return "ANGLE_length";
        case TOperator::EOpDot:
            return "ANGLE_dot";
        case TOperator::EOpNormalize:
            return "ANGLE_normalize";
        case TOperator::EOpFaceforward:
            return "ANGLE_faceforward";
        case TOperator::EOpReflect:
            return "ANGLE_reflect";
        case TOperator::EOpMulMatrixComponentWise:
            return "ANGLE_componentWiseMultiply";
        case TOperator::EOpOuterProduct:
            return "ANGLE_outerProduct";
        case TOperator::EOpSign:
            return "ANGLE_sign";

        case TOperator::EOpAbs:
            return "metal::abs";
        case TOperator::EOpAll:
            return "metal::all";
        case TOperator::EOpAny:
            return "metal::any";
        case TOperator::EOpSin:
            return "metal::sin";
        case TOperator::EOpCos:
            return "metal::cos";
        case TOperator::EOpTan:
            return "metal::tan";
        case TOperator::EOpAsin:
            return "metal::asin";
        case TOperator::EOpAcos:
            return "metal::acos";
        case TOperator::EOpSinh:
            return "metal::sinh";
        case TOperator::EOpCosh:
            return "metal::cosh";
        case TOperator::EOpTanh:
            return "metal::tanh";
        case TOperator::EOpAsinh:
            return "metal::asinh";
        case TOperator::EOpAcosh:
            return "metal::acosh";
        case TOperator::EOpAtanh:
            return "metal::atanh";
        case TOperator::EOpFma:
            return "metal::fma";
        case TOperator::EOpPow:
            return "metal::pow";
        case TOperator::EOpExp:
            return "metal::exp";
        case TOperator::EOpExp2:
            return "metal::exp2";
        case TOperator::EOpLog:
            return "metal::log";
        case TOperator::EOpLog2:
            return "metal::log2";
        case TOperator::EOpSqrt:
            return "metal::sqrt";
        case TOperator::EOpFloor:
            return "metal::floor";
        case TOperator::EOpTrunc:
            return "metal::trunc";
        case TOperator::EOpCeil:
            return "metal::ceil";
        case TOperator::EOpFract:
            return "metal::fract";
        case TOperator::EOpMin:
            return "metal::min";
        case TOperator::EOpMax:
            return "metal::max";
        case TOperator::EOpRound:
            return "metal::round";
        case TOperator::EOpRoundEven:
            return "metal::rint";
        case TOperator::EOpClamp:
            return "metal::clamp";  // TODO fast vs precise namespace
        case TOperator::EOpMix:
            if(argType2 && argType2->getBasicType() == EbtBool)
                return "ANGLE_mix_bool";
            return "metal::mix";
        case TOperator::EOpStep:
            return "metal::step";
        case TOperator::EOpSmoothstep:
            return "metal::smoothstep";
        case TOperator::EOpModf:
            return "metal::modf";
        case TOperator::EOpIsnan:
            return "metal::isnan";
        case TOperator::EOpIsinf:
            return "metal::isinf";
        case TOperator::EOpLdexp:
            return "metal::ldexp";
        case TOperator::EOpFrexp:
            return "metal::frexp";
        case TOperator::EOpInversesqrt:
            return "metal::rsqrt";
        case TOperator::EOpCross:
            return "metal::cross";
        case TOperator::EOpDFdx:
            return "metal::dfdx";
        case TOperator::EOpDFdy:
            return "metal::dfdy";
        case TOperator::EOpFwidth:
            return "metal::fwidth";
        case TOperator::EOpTranspose:
            return "metal::transpose";
        case TOperator::EOpDeterminant:
            return "metal::determinant";

        case TOperator::EOpInverse:
            return "ANGLE_inverse";

        case TOperator::EOpFloatBitsToInt:
        case TOperator::EOpFloatBitsToUint:
        case TOperator::EOpIntBitsToFloat:
        case TOperator::EOpUintBitsToFloat:
        {
#define RETURN_AS_TYPE(post)                     \
    do                                           \
        switch (resultType.getBasicType())       \
        {                                        \
            case TBasicType::EbtInt:             \
                return "as_type<int" post ">";   \
            case TBasicType::EbtUInt:            \
                return "as_type<uint" post ">";  \
            case TBasicType::EbtFloat:           \
                return "as_type<float" post ">"; \
            default:                             \
                TODO();                          \
                return "TOperator_TODO";         \
        }                                        \
    while (false)

            if (resultType.isScalar())
            {
                RETURN_AS_TYPE("");
            }
            else if (resultType.isVector())
            {
                switch (resultType.getNominalSize())
                {
                    case 2:
                        RETURN_AS_TYPE("2");
                    case 3:
                        RETURN_AS_TYPE("3");
                    case 4:
                        RETURN_AS_TYPE("4");
                    default:
                        LOGIC_ERROR();
                        return nullptr;
                }
            }
            else
            {
                TODO();
                return "TOperator_TODO";
            }

#undef RETURN_AS_TYPE
        }

        case TOperator::EOpPackUnorm2x16:
            return "metal::pack_float_to_unorm2x16";
        case TOperator::EOpPackSnorm2x16:
            return "metal::pack_float_to_snorm2x16";

        case TOperator::EOpPackUnorm4x8:
            return "metal::pack_float_to_unorm4x8";
        case TOperator::EOpPackSnorm4x8:
            return "metal::pack_float_to_snorm4x8";

        case TOperator::EOpUnpackUnorm2x16:
            return "metal::unpack_unorm2x16_to_float";
        case TOperator::EOpUnpackSnorm2x16:
            return "metal::unpack_snorm2x16_to_float";

        case TOperator::EOpUnpackUnorm4x8:
            return "metal::unpack_unorm4x8_to_float";
        case TOperator::EOpUnpackSnorm4x8:
            return "metal::unpack_snorm4x8_to_float";

        case TOperator::EOpPackHalf2x16:
            return "ANGLE_pack_half_2x16";
        case TOperator::EOpUnpackHalf2x16:
            return "ANGLE_unpack_half_2x16";

        case TOperator::EOpBitfieldExtract:
        case TOperator::EOpBitfieldInsert:
        case TOperator::EOpBitfieldReverse:
        case TOperator::EOpBitCount:
        case TOperator::EOpFindLSB:
        case TOperator::EOpFindMSB:
        case TOperator::EOpUaddCarry:
        case TOperator::EOpUsubBorrow:
        case TOperator::EOpUmulExtended:
        case TOperator::EOpImulExtended:
        case TOperator::EOpBarrier:
        case TOperator::EOpMemoryBarrier:
        case TOperator::EOpMemoryBarrierAtomicCounter:
        case TOperator::EOpMemoryBarrierBuffer:
        case TOperator::EOpMemoryBarrierImage:
        case TOperator::EOpMemoryBarrierShared:
        case TOperator::EOpGroupMemoryBarrier:
        case TOperator::EOpAtomicAdd:
        case TOperator::EOpAtomicMin:
        case TOperator::EOpAtomicMax:
        case TOperator::EOpAtomicAnd:
        case TOperator::EOpAtomicOr:
        case TOperator::EOpAtomicXor:
        case TOperator::EOpAtomicExchange:
        case TOperator::EOpAtomicCompSwap:
        case TOperator::EOpEmitVertex:
        case TOperator::EOpEndPrimitive:
        case TOperator::EOpFTransform:
        case TOperator::EOpPackDouble2x32:
        case TOperator::EOpUnpackDouble2x32:
        case TOperator::EOpArrayLength:
            TODO();
            return "TOperator_TODO";

        case TOperator::EOpNull:
        case TOperator::EOpConstruct:
        case TOperator::EOpCallFunctionInAST:
        case TOperator::EOpCallInternalRawFunction:
        case TOperator::EOpCallBuiltInFunction:
        case TOperator::EOpIndexDirect:
        case TOperator::EOpIndexIndirect:
        case TOperator::EOpIndexDirectStruct:
        case TOperator::EOpIndexDirectInterfaceBlock:
            LOGIC_ERROR();
            return nullptr;
    }
}

#if 0
static int GetOperatorPrecedence(TOperator op)
{
    switch (op)
    {
        case TOperator::EOpComma: {
            return 17;
        } break;

        case TOperator::EOpAssign:
        case TOperator::EOpInitialize:
        case TOperator::EOpAddAssign:
        case TOperator::EOpSubAssign:
        case TOperator::EOpMulAssign:
        case TOperator::EOpDivAssign:
        case TOperator::EOpIModAssign:
        case TOperator::EOpBitShiftLeftAssign:
        case TOperator::EOpBitShiftRightAssign:
        case TOperator::EOpBitwiseAndAssign:
        case TOperator::EOpBitwiseXorAssign:
        case TOperator::EOpBitwiseOrAssign: {
            return 16;
        } break;

        case TOperator::EOpLogicalOr: {
            return 15;
        } break;

        case TOperator::EOpLogicalAnd: {
            return 14;
        } break;

        case TOperator::EOpBitwiseOr: {
            return 13;
        } break;

        case TOperator::EOpBitwiseXor: {
            return 12;
        } break;

        case TOperator::EOpBitwiseAnd: {
            return 11;
        } break;

        case TOperator::EOpLogicalXor:
        case TOperator::EOpEqual:
        case TOperator::EOpNotEqual: {
            return 10;
        } break;

        case TOperator::EOpLessThan:
        case TOperator::EOpGreaterThan:
        case TOperator::EOpLessThanEqual:
        case TOperator::EOpGreaterThanEqual: {
            return 9;
        } break;

        case TOperator::EOpBitShiftLeft:
        case TOperator::EOpBitShiftRight: {
            return 7;
        } break;

        case TOperator::EOpAdd:
        case TOperator::EOpSub: {
            return 6;
        } break;

        case TOperator::EOpMul:
        case TOperator::EOpDiv:
        case TOperator::EOpIMod: {
            return 5;
        } break;

        case TOperator::EOpNegative:
        case TOperator::EOpPositive:
        case TOperator::EOpLogicalNot:
        case TOperator::EOpBitwiseNot:
        case TOperator::EOpPreIncrement:
        case TOperator::EOpPreDecrement: {
            return 3;
        } break;

        case TOperator::EOpPostIncrement:
        case TOperator::EOpPostDecrement: {
            return 2;
        } break;

        default: {
            TODO();
            return -1;
        }
    }
}

namespace
{

enum class Associativity
{
    None,
    Left,
    Right,
};

} // anonymous namespace

static Associativity GetAssociativity(TOperator op)
{
    switch (op)
    {
        case TOperator::EOpAdd:
        case TOperator::EOpSub:
        case TOperator::EOpMul:
        case TOperator::EOpDiv:
        case TOperator::EOpIMod:
        case TOperator::EOpBitShiftLeft:
        case TOperator::EOpBitShiftRight:
        case TOperator::EOpBitwiseAnd:
        case TOperator::EOpBitwiseXor:
        case TOperator::EOpBitwiseOr:
        case TOperator::EOpEqual:
        case TOperator::EOpNotEqual:
        case TOperator::EOpLessThan:
        case TOperator::EOpGreaterThan:
        case TOperator::EOpLessThanEqual:
        case TOperator::EOpGreaterThanEqual:
        case TOperator::EOpLogicalOr:
        case TOperator::EOpLogicalXor:
        case TOperator::EOpLogicalAnd:
        case TOperator::EOpComma: {
            return Associativity::Left;
        } break;

        case TOperator::EOpAssign:
        case TOperator::EOpInitialize:
        case TOperator::EOpAddAssign:
        case TOperator::EOpSubAssign:
        case TOperator::EOpMulAssign:
        case TOperator::EOpDivAssign:
        case TOperator::EOpIModAssign:
        case TOperator::EOpBitShiftLeftAssign:
        case TOperator::EOpBitShiftRightAssign:
        case TOperator::EOpBitwiseAndAssign:
        case TOperator::EOpBitwiseXorAssign:
        case TOperator::EOpBitwiseOrAssign: {
            return Associativity::Right;
        } break;

        case TOperator::EOpNegative:
        case TOperator::EOpPositive:
        case TOperator::EOpLogicalNot:
        case TOperator::EOpBitwiseNot:
        case TOperator::EOpPostIncrement:
        case TOperator::EOpPostDecrement:
        case TOperator::EOpPreIncrement:
        case TOperator::EOpPreDecrement: {
            return Associativity::None;
        } break;

        default: {
            TODO();
            return Associativity::None;
        }
    }
}
#endif

static bool IsSymbolicOperator(TOperator op,
                               const TType &resultType,
                               const TType *argType0,
                               const TType *argType1 = nullptr)
{
    if (op == TOperator::EOpCallBuiltInFunction)
    {
        return false;
    }
    return !std::isalnum(GetOperatorString(op, resultType, argType0, argType1)[0]);
}

static TIntermBinary *AsSpecificBinaryNode(TIntermNode &node, TOperator op)
{
    TIntermBinary *binaryNode = node.getAsBinaryNode();
    if (binaryNode)
    {
        return binaryNode->getOp() == op ? binaryNode : nullptr;
    }
    return nullptr;
}

static bool Parenthesize(TIntermNode &node)
{
    if (node.getAsSymbolNode())
    {
        return false;
    }
    if (node.getAsConstantUnion())
    {
        return false;
    }
    if (node.getAsAggregate())
    {
        return false;
    }
    if (node.getAsSwizzleNode())
    {
        return false;
    }

    if (TIntermUnary *unaryNode = node.getAsUnaryNode())
    {
        // TODO: Use a precedence and associativity rules instead of this ad-hoc impl.
        const TType &resultType = unaryNode->getType();
        const TType &argType    = unaryNode->getOperand()->getType();
        return IsSymbolicOperator(unaryNode->getOp(), resultType, &argType);
    }

    if (TIntermBinary *binaryNode = node.getAsBinaryNode())
    {
        // TODO: Use a precedence and associativity rules instead of this ad-hoc impl.
        const TOperator op = binaryNode->getOp();
        switch (op)
        {
            case TOperator::EOpIndexDirectStruct:
            case TOperator::EOpIndexDirectInterfaceBlock:
            case TOperator::EOpIndexDirect:
            case TOperator::EOpIndexIndirect:
                return Parenthesize(*binaryNode->getLeft());

            case TOperator::EOpAssign:
            case TOperator::EOpInitialize:
                return AsSpecificBinaryNode(*binaryNode->getRight(), TOperator::EOpComma);

            default:
            {
                const TType &resultType = binaryNode->getType();
                const TType &leftType   = binaryNode->getLeft()->getType();
                const TType &rightType  = binaryNode->getRight()->getType();
                return IsSymbolicOperator(binaryNode->getOp(), resultType, &leftType, &rightType);
            }
        }
    }

    return true;
}

void GenMetalTraverser::groupedTraverse(TIntermNode &node)
{
    const bool emitParens = Parenthesize(node);

    if (emitParens)
    {
        mOut << "(";
    }

    node.traverse(this);

    if (emitParens)
    {
        mOut << ")";
    }
}

void GenMetalTraverser::emitPostQualifier(const EmitVariableDeclarationConfig &evdConfig,
                                          const VarDecl &decl,
                                          const TQualifier qualifier)
{
    switch (qualifier)
    {
        case TQualifier::EvqPosition:
        case TQualifier::EvqFragCoord:
            mOut << " [[position]]";
            break;

        case TQualifier::EvqPointSize:
            mOut << " [[point_size]]";
            break;

        case TQualifier::EvqVertexID:
            if (evdConfig.isMainParameter)
            {
                mOut << " [[vertex_id]]";
            }
            break;

        case TQualifier::EvqPointCoord:
            if (evdConfig.isMainParameter)
            {
                mOut << " [[point_coord]]";
            }
            break;

        case TQualifier::EvqFrontFacing:
            if (evdConfig.isMainParameter)
            {
                mOut << " [[front_facing]]";
            }
            break;

        default:
            break;
    }

    const bool isInvariant =
    (decl.isField() ? mInvariants.contains(decl.field()) : mInvariants.contains(decl.variable())) && (qualifier == TQualifier::EvqPosition || qualifier == TQualifier::EvqFragCoord);

    if (isInvariant)
    {
        mOut << " [[invariant]]";
        TranslatorMetalReflection *reflection =
            ((sh::TranslatorMetalDirect *)&mCompiler)->getTranslatorMetalReflection();
        reflection->hasInvariance = true;
    }
}

static void EmitName(Sink &out, const Name &name)
{
#if defined(ANGLE_ENABLE_ASSERTS)
    DebugSink::EscapedSink escapedOut(out.escape());
#else
    TInfoSinkBase &escapedOut = out;
#endif
    name.emit(escapedOut);
}

void GenMetalTraverser::emitNameOf(const TField &object)
{
    EmitName(mOut, Name(object));
}

void GenMetalTraverser::emitNameOf(const TSymbol &object)
{
    auto it = mRenamedSymbols.find(&object);
    if (it == mRenamedSymbols.end())
    {
        EmitName(mOut, Name(object));
    }
    else
    {
        EmitName(mOut, it->second);
    }
}

void GenMetalTraverser::emitNameOf(const VarDecl &object)
{
    if (object.isField())
    {
        emitNameOf(object.field());
    }
    else
    {
        emitNameOf(object.variable());
    }
}

void GenMetalTraverser::emitBareTypeName(const TType &type, const EmitTypeConfig &etConfig)
{
    const TBasicType basicType = type.getBasicType();

    switch (basicType)
    {
        case TBasicType::EbtVoid:
        case TBasicType::EbtBool:
        case TBasicType::EbtFloat:
        case TBasicType::EbtInt:
        case TBasicType::EbtUInt:
        {
            mOut << type.getBasicString();
        }
        break;

        case TBasicType::EbtStruct:
        {
            const TStructure &structure = *type.getStruct();
            emitNameOf(structure);
        }
        break;

        case TBasicType::EbtInterfaceBlock:
        {
            const TInterfaceBlock &interfaceBlock = *type.getInterfaceBlock();
            emitNameOf(interfaceBlock);
        }
        break;

        default:
        {
            if (IsSampler(basicType))
            {
                if (etConfig.evdConfig && etConfig.evdConfig->isMainParameter)
                {
                    EmitName(mOut, GetTextureTypeName(basicType));
                }
                else
                {
                    const TStructure &env = mSymbolEnv.getTextureEnv(basicType);
                    emitNameOf(env);
                }
            }
            else
            {
                TODO();
            }
        }
    }
}

void GenMetalTraverser::emitType(const TType &type, const EmitTypeConfig &etConfig)
{
    const bool isUBO = etConfig.evdConfig ? etConfig.evdConfig->isUBO : false;
    if (etConfig.evdConfig)
    {
        const auto &evdConfig = *etConfig.evdConfig;
        if (isUBO)
        {
            if (type.isArray())
            {
                mOut << "ANGLE_tensor<";
            }
        }
        if (evdConfig.isPointer)
        {
            mOut << toString(*evdConfig.isPointer);
            mOut << " ";
        }
        else if (evdConfig.isReference)
        {
            mOut << toString(*evdConfig.isReference);
            mOut << " ";
        }
    }

    if (!isUBO)
    {
        if (type.isArray())
        {
            mOut << "ANGLE_tensor<";
        }
    }

    if (type.isVector() || type.isMatrix())
    {
        mOut << "metal::";
    }

    if (etConfig.evdConfig && etConfig.evdConfig->isPacked)
    {
        mOut << "packed_";
    }

    emitBareTypeName(type, etConfig);

    if (type.isVector())
    {
        mOut << type.getNominalSize();
    }
    else if (type.isMatrix())
    {
        mOut << type.getCols() << "x" << type.getRows();
    }

    if (!isUBO)
    {
        if (type.isArray())
        {
            for (auto size : type.getArraySizes())
            {
                mOut << ", " << size;
            }
            mOut << ">";
        }
    }

    if (etConfig.evdConfig)
    {
        const auto &evdConfig = *etConfig.evdConfig;
        if (evdConfig.isPointer)
        {
            mOut << " *";
        }
        else if (evdConfig.isReference)
        {
            mOut << " &";
        }
        if (isUBO)
        {
            if (type.isArray())
            {
                for (auto size : type.getArraySizes())
                {
                    mOut << ", " << size;
                }
                mOut << ">";
            }
        }
    }
}

void GenMetalTraverser::emitFieldDeclaration(const TField &field,
                                             const TStructure &parent,
                                             FieldAnnotationIndices &annotationIndices)
{
    const TType &type      = *field.type();
    const TBasicType basic = type.getBasicType();

    EmitVariableDeclarationConfig evdConfig;
    evdConfig.emitPostQualifier      = true;
    evdConfig.disableStructSpecifier = true;
    evdConfig.isPacked               = mSymbolEnv.isPacked(field);
    evdConfig.isUBO                  = mSymbolEnv.isUBO(field);
    evdConfig.isPointer              = mSymbolEnv.isPointer(field);
    evdConfig.isReference            = mSymbolEnv.isReference(field);
    emitVariableDeclaration(VarDecl(field), evdConfig);

    const TQualifier qual = type.getQualifier();
    switch (qual)
    {
        case TQualifier::EvqFlatIn:
            if (mPipelineStructs.fragmentIn.external == &parent)
            {
                mOut << " [[flat]]";
                TranslatorMetalReflection *reflection =
                    ((sh::TranslatorMetalDirect *)&mCompiler)->getTranslatorMetalReflection();
                reflection->hasFlatInput = true;
            }
            break;

        case TQualifier::EvqFragmentOut:
        case TQualifier::EvqFragData:
            if (mPipelineStructs.fragmentOut.external == &parent)
            {
                if ((type.isVector() &&
                     (basic == TBasicType::EbtInt || basic == TBasicType::EbtUInt ||
                      basic == TBasicType::EbtFloat)) ||
                    type.getQualifier() == EvqFragData)
                {
                    // TODO:
                    // This is not correct in general and needs a reimplementation.
                    // In GLSL 3.0, We can't always assume this is going to be a safe index.
                    // See 4.3.8.2
                    // https://www.khronos.org/registry/OpenGL/specs/es/3.0/GLSL_ES_Specification_3.00.pdf
                    size_t index = annotationIndices.color++;
                    mOut << " [[color(" << index << ")]]";
                }
            }
            break;

        case TQualifier::EvqFragDepth:
            mOut << " [[depth(any)]]";
            break;

        case TQualifier::EvqSampleMask:
            mOut << " [[sample_mask, function_constant(" << sh::TranslatorMetalDirect::GetCoverageMaskEnabledConstName() << ")]]";
            break;

        default:
            break;
    }
}

static std::map<Name, size_t> BuildExternalAttributeIndexMap(
    const TCompiler &compiler,
    const PipelineScoped<TStructure> &structure)
{
    ASSERT(structure.isTotallyFull());

    const auto &shaderVars     = compiler.getAttributes();
    const size_t shaderVarSize = shaderVars.size();
    size_t shaderVarIndex      = 0;

    const auto &externalFields = structure.external->fields();
    const size_t externalSize  = externalFields.size();
    size_t externalIndex       = 0;

    const auto &internalFields = structure.internal->fields();
    const size_t internalSize  = internalFields.size();
    size_t internalIndex       = 0;

    // Internal fields are never split. External fields are sometimes split.
    ASSERT(externalSize >= internalSize);

    // Structures do not contain any inactive fields.
    ASSERT(shaderVarSize >= internalSize);

    std::map<Name, size_t> externalNameToAttributeIndex;
    size_t attributeIndex = 0;

    while (internalIndex < internalSize)
    {
        const TField &internalField = *internalFields[internalIndex];
        const Name internalName     = Name(internalField);
        const TType &internalType   = *internalField.type();
        while (internalName.rawName() != shaderVars[shaderVarIndex].name &&
               internalName.rawName() != shaderVars[shaderVarIndex].mappedName)
        {
            // This case represents an inactive field.

            ++shaderVarIndex;
            ASSERT(shaderVarIndex < shaderVarSize);

            ++attributeIndex;  // TODO: Might need to increment more if shader var type is a matrix.
        }

        const size_t cols = internalType.isMatrix() ? internalType.getCols() : 1;

        for (size_t c = 0; c < cols; ++c)
        {
            const TField &externalField = *externalFields[externalIndex];
            const Name externalName     = Name(externalField);
            ASSERT(!externalField.type()->isMatrix());

            externalNameToAttributeIndex[externalName] = attributeIndex;

            ++externalIndex;
            ++attributeIndex;
        }

        ++shaderVarIndex;
        ++internalIndex;
    }

    ASSERT(shaderVarIndex <= shaderVarSize);
    ASSERT(externalIndex <= externalSize);  // less than if padding was introduced
    ASSERT(internalIndex == internalSize);

    return externalNameToAttributeIndex;
}

void GenMetalTraverser::emitAttributeDeclaration(const TField &field,
                                                 FieldAnnotationIndices &annotationIndices)
{
    EmitVariableDeclarationConfig evdConfig;
    evdConfig.disableStructSpecifier = true;
    emitVariableDeclaration(VarDecl(field), evdConfig);
    mOut << sh::kUnassignedAttributeString;
}

void GenMetalTraverser::emitUniformBufferDeclaration(const TField &field,
                                                 FieldAnnotationIndices &annotationIndices)
{
    EmitVariableDeclarationConfig evdConfig;
    evdConfig.disableStructSpecifier = true;
    evdConfig.isUBO                  = mSymbolEnv.isUBO(field);
    evdConfig.isPointer              = mSymbolEnv.isPointer(field);
    emitVariableDeclaration(VarDecl(field), evdConfig);
    mOut << "[[id(" << annotationIndices.attribute << ")]]";

    const TType &type = *field.type();
    const int arraySize = type.isArray() ? type.getArraySizeProduct() : 1;

    TranslatorMetalReflection *reflection =
        ((sh::TranslatorMetalDirect *)&mCompiler)->getTranslatorMetalReflection();
    ASSERT(type.getBasicType() == TBasicType::EbtStruct);
    const TStructure *structure = type.getStruct();
    const std::string originalName =
        reflection->getOriginalName(structure->uniqueId().get());
    reflection->addUniformBufferBinding(originalName, {.bindIndex = annotationIndices.attribute, .arraySize = static_cast<size_t>(arraySize)});

    annotationIndices.attribute += arraySize;
}

void GenMetalTraverser::emitStructDeclaration(const TType &type)
{
    ASSERT(type.getBasicType() == TBasicType::EbtStruct);
    ASSERT(type.isStructSpecifier());

    mOut << "struct ";
    emitBareTypeName(type, {});

    mOut << "\n";
    emitOpenBrace();

    const TStructure &structure = *type.getStruct();
    std::map<Name, size_t> fieldToAttributeIndex;
    const bool hasAttributeIndices           = mPipelineStructs.vertexIn.external == &structure;
    const bool hasUniformBufferIndicies      = mPipelineStructs.uniformBuffers.external == &structure;
    const bool reclaimUnusedAttributeIndices = mCompiler.getShaderVersion() < 300;

    if (hasAttributeIndices)
    {
        fieldToAttributeIndex =
            BuildExternalAttributeIndexMap(mCompiler, mPipelineStructs.vertexIn);
    }

    FieldAnnotationIndices annotationIndices;

    for (const TField *field : structure.fields())
    {
        emitIndentation();
        if (hasAttributeIndices)
        {
            const auto it = fieldToAttributeIndex.find(Name(*field));
            if (it == fieldToAttributeIndex.end())
            {
                ASSERT(field->symbolType() == SymbolType::AngleInternal);
                ASSERT(field->name().beginsWith("_"));
                ASSERT(angle::EndsWith(field->name().data(), "_pad"));
                emitFieldDeclaration(*field, structure, annotationIndices);
            }
            else
            {
                ASSERT(field->symbolType() != SymbolType::AngleInternal ||
                       !field->name().beginsWith("_") ||
                       !angle::EndsWith(field->name().data(), "_pad"));
                if (!reclaimUnusedAttributeIndices)
                {
                    annotationIndices.attribute = it->second;
                }
                emitAttributeDeclaration(*field, annotationIndices);
            }
        }
        else if(hasUniformBufferIndicies)
        {
            emitUniformBufferDeclaration(*field, annotationIndices);
        }
        else
        {
            emitFieldDeclaration(*field, structure, annotationIndices);
        }
        mOut << ";\n";
    }

    if (!mPipelineStructs.matches(structure, true, true))
    {
        MetalLayoutOfConfig layoutConfig;
        layoutConfig.treatSamplersAsTextureEnv = true;
        Layout layout                          = MetalLayoutOf(type, layoutConfig);
        size_t pad                             = (kDefaultStructAlignmentSize - layout.sizeOf) % kDefaultStructAlignmentSize;
        if (pad != 0)
        {
            emitIndentation();
            mOut << "char ";
            EmitName(mOut, mIdGen.createNewName("pad"));
            mOut << "[" << pad << "];\n";
        }
    }

    emitCloseBrace();
}

void GenMetalTraverser::emitOrdinaryVariableDeclaration(
    const VarDecl &decl,
    const EmitVariableDeclarationConfig &evdConfig)
{
    EmitTypeConfig etConfig;
    etConfig.evdConfig = &evdConfig;

    const TType &type = decl.type();
    emitType(type, etConfig);
    if (decl.symbolType() != SymbolType::Empty)
    {
        mOut << " ";
        emitNameOf(decl);
    }
}

void GenMetalTraverser::emitVariableDeclaration(const VarDecl &decl,
                                                const EmitVariableDeclarationConfig &evdConfig)
{
    const SymbolType symbolType = decl.symbolType();
    const TType &type           = decl.type();
    const TBasicType basicType  = type.getBasicType();

    switch (basicType)
    {
        case TBasicType::EbtStruct:
        {
            if (type.isStructSpecifier() && !evdConfig.disableStructSpecifier)
            {
                ASSERT(!evdConfig.isParameter);
                emitStructDeclaration(type);
                if (symbolType != SymbolType::Empty)
                {
                    mOut << " ";
                    emitNameOf(decl);
                }
            }
            else
            {
                emitOrdinaryVariableDeclaration(decl, evdConfig);
            }
        }
        break;

        default:
        {
            ASSERT(symbolType != SymbolType::Empty || evdConfig.isParameter);
            emitOrdinaryVariableDeclaration(decl, evdConfig);
        }
    }

    if (evdConfig.emitPostQualifier)
    {
        emitPostQualifier(evdConfig, decl, type.getQualifier());
    }
}

void GenMetalTraverser::visitSymbol(TIntermSymbol *symbolNode)
{
    const TVariable &var = symbolNode->variable();
    const TType &type    = var.getType();
    ASSERT(var.symbolType() != SymbolType::Empty);

    if (type.getBasicType() == TBasicType::EbtVoid)
    {
        mOut << "/*";
        emitNameOf(var);
        mOut << "*/";
    }
    else
    {
        emitNameOf(var);
    }
}

void GenMetalTraverser::emitSingleConstant(const TConstantUnion *const constUnion)
{
    switch (constUnion->getType())
    {
        case TBasicType::EbtBool:
        {
            mOut << (constUnion->getBConst() ? "true" : "false");
        }
        break;

        case TBasicType::EbtFloat:
        {
            if (ANGLE_UNLIKELY(isnan(constUnion->getFConst())))
            {
                mOut << "NAN";
            }
            if (ANGLE_UNLIKELY(isinf(constUnion->getFConst())))
            {
                if(constUnion->getFConst() < 0)
                {
                    mOut << "-INFINITY";
                }
                else
                {
                    mOut << "INFINITY";
                }
            }
            else
            {
                mOut << constUnion->getFConst() << "f";
            }
        }
        break;

        case TBasicType::EbtInt:
        {
            mOut << constUnion->getIConst();
        }
        break;

        case TBasicType::EbtUInt:
        {
            mOut << constUnion->getUConst() << "u";
        }
        break;

        default:
        {
            TODO();
        }
    }
}

const TConstantUnion *GenMetalTraverser::emitConstantUnionArray(
    const TConstantUnion *const constUnion,
    const size_t size)
{
    const TConstantUnion *constUnionIterated = constUnion;
    for (size_t i = 0; i < size; i++, constUnionIterated++)
    {
        emitSingleConstant(constUnionIterated);

        if (i != size - 1)
        {
            mOut << ", ";
        }
    }
    return constUnionIterated;
}

const TConstantUnion *GenMetalTraverser::emitConstantUnion(const TType &type,
                                                           const TConstantUnion *constUnionBegin)
{
    const TConstantUnion *constUnionCurr = constUnionBegin;
    const TStructure *structure          = type.getStruct();
    if (structure)
    {
        EmitTypeConfig config = EmitTypeConfig{nullptr};
        emitType(type, config);
        mOut << "{";
        const TFieldList &fields = structure->fields();
        for (size_t i = 0; i < fields.size(); ++i)
        {
            const TType *fieldType = fields[i]->type();
            constUnionCurr         = emitConstantUnion(*fieldType, constUnionCurr);
            if (i != fields.size() - 1)
            {
                mOut << ", ";
            }
        }
        mOut << "}";
    }
    else
    {
        size_t size    = type.getObjectSize();
        bool writeType = size > 1;
        if (writeType)
        {
            EmitTypeConfig config = EmitTypeConfig{nullptr};
            emitType(type, config);
            mOut << "(";
        }
        constUnionCurr = emitConstantUnionArray(constUnionCurr, size);
        if (writeType)
        {
            mOut << ")";
        }
    }
    return constUnionCurr;
}

void GenMetalTraverser::visitConstantUnion(TIntermConstantUnion *constValueNode)
{
    emitConstantUnion(constValueNode->getType(), constValueNode->getConstantValue());
}

bool GenMetalTraverser::visitSwizzle(Visit, TIntermSwizzle *swizzleNode)
{
    groupedTraverse(*swizzleNode->getOperand());
    mOut << ".";

    {
#if defined(ANGLE_ENABLE_ASSERTS)
        DebugSink::EscapedSink escapedOut(mOut.escape());
        TInfoSinkBase &out = escapedOut.get();
#else
        TInfoSinkBase &out        = mOut;
#endif
        swizzleNode->writeOffsetsAsXYZW(&out);
    }

    return false;
}

const TField &GenMetalTraverser::getDirectField(const TFieldListCollection &fieldListCollection,
                                                const TConstantUnion &index)
{
    ASSERT(index.getType() == TBasicType::EbtInt);

    const TFieldList &fieldList = fieldListCollection.fields();
    const int indexVal          = index.getIConst();
    const TField &field         = *fieldList[indexVal];

    return field;
}

const TField &GenMetalTraverser::getDirectField(const TIntermTyped &fieldsNode,
                                                TIntermTyped &indexNode)
{
    const TType &fieldsType = fieldsNode.getType();

    const TFieldListCollection *fieldListCollection = fieldsType.getStruct();
    if (fieldListCollection == nullptr)
    {
        fieldListCollection = fieldsType.getInterfaceBlock();
    }
    ASSERT(fieldListCollection);

    const TIntermConstantUnion *indexNode_ = indexNode.getAsConstantUnion();
    ASSERT(indexNode_);
    const TConstantUnion &index = *indexNode_->getConstantValue();

    return getDirectField(*fieldListCollection, index);
}

bool GenMetalTraverser::visitBinary(Visit, TIntermBinary *binaryNode)
{
    const TOperator op      = binaryNode->getOp();
    TIntermTyped &leftNode  = *binaryNode->getLeft();
    TIntermTyped &rightNode = *binaryNode->getRight();

    switch (op)
    {
        case TOperator::EOpIndexDirectStruct:
        case TOperator::EOpIndexDirectInterfaceBlock:
        {
            const TField &field = getDirectField(leftNode, rightNode);
            if (mSymbolEnv.isPointer(field) && mSymbolEnv.isUBO(field)) {
                emitOpeningPointerParen();
            }
            groupedTraverse(leftNode);
            if (!mSymbolEnv.isPointer(field))
            {
                emitClosingPointerParen();
            }
            mOut << ".";
            emitNameOf(field);
        }
        break;

        case TOperator::EOpIndexDirect:
        case TOperator::EOpIndexIndirect:
        {
            TType leftType = leftNode.getType();
            groupedTraverse(leftNode);
            mOut << "[";
            {
                mOut << "ANGLE_int_clamp(";
                groupedTraverse(rightNode);
                mOut << ", 0, ";
                if(leftType.isUnsizedArray())
                {
                    groupedTraverse(leftNode);
                    mOut << ".size()";
                }
                else
                {
                    int maxSize;
                    if (leftType.isArray())
                    {
                        maxSize = static_cast<int>(leftType.getOutermostArraySize()) - 1;
                    }
                    else
                    {
                        maxSize = leftType.getNominalSize() - 1;
                    }
                    mOut << maxSize;
                }
                mOut << ")";
            }
            mOut << "]";
        }
        break;

        default:
        {
            const TType &resultType = binaryNode->getType();
            const TType &leftType   = leftNode.getType();
            const TType &rightType  = rightNode.getType();

            if (IsSymbolicOperator(op, resultType, &leftType, &rightType))
            {
                groupedTraverse(leftNode);
                if (op != TOperator::EOpComma)
                {
                    mOut << " ";
                }
                else
                {
                    emitClosingPointerParen();
                }
                mOut << GetOperatorString(op, resultType, &leftType, &rightType) << " ";
                groupedTraverse(rightNode);
            }
            else
            {
                emitClosingPointerParen();
                mOut << GetOperatorString(op, resultType, &leftType, &rightType) << "(";
                leftNode.traverse(this);
                mOut << ", ";
                rightNode.traverse(this);
                mOut << ")";
            }
        }
    }

    return false;
}

static bool IsPostfix(TOperator op)
{
    switch (op)
    {
        case TOperator::EOpPostIncrement:
        case TOperator::EOpPostDecrement:
            return true;

        default:
            return false;
    }
}

bool GenMetalTraverser::visitUnary(Visit, TIntermUnary *unaryNode)
{
    const TOperator op      = unaryNode->getOp();
    const TType &resultType = unaryNode->getType();

    TIntermTyped &arg    = *unaryNode->getOperand();
    const TType &argType = arg.getType();

    const char *name = GetOperatorString(op, resultType, &argType);

    if (IsSymbolicOperator(op, resultType, &argType))
    {
        const bool postfix = IsPostfix(op);
        if (!postfix)
        {
            mOut << name;
        }
        groupedTraverse(arg);
        if (postfix)
        {
            mOut << name;
        }
    }
    else
    {
        mOut << name << "(";
        arg.traverse(this);
        mOut << ")";
    }

    return false;
}

bool GenMetalTraverser::visitTernary(Visit, TIntermTernary *conditionalNode)
{
    groupedTraverse(*conditionalNode->getCondition());
    mOut << " ? ";
    groupedTraverse(*conditionalNode->getTrueExpression());
    mOut << " : ";
    groupedTraverse(*conditionalNode->getFalseExpression());

    return false;
}

bool GenMetalTraverser::visitIfElse(Visit, TIntermIfElse *ifThenElseNode)
{
    TIntermTyped &condNode = *ifThenElseNode->getCondition();
    TIntermBlock *thenNode = ifThenElseNode->getTrueBlock();
    TIntermBlock *elseNode = ifThenElseNode->getFalseBlock();

    emitIndentation();
    mOut << "if (";
    condNode.traverse(this);
    mOut << ")";

    if (thenNode)
    {
        mOut << "\n";
        thenNode->traverse(this);
    }
    else
    {
        mOut << " {}";
    }

    if (elseNode)
    {
        mOut << "\n";
        emitIndentation();
        mOut << "else\n";
        elseNode->traverse(this);
    }
    else
    {
        // Always emit "else" even when empty block to avoid nested if-stmt issues.
        mOut << " else {}";
    }

    return false;
}

bool GenMetalTraverser::visitSwitch(Visit, TIntermSwitch *switchNode)
{
    emitIndentation();
    mOut << "switch (";
    switchNode->getInit()->traverse(this);
    mOut << ")\n";

    ASSERT(!mParentIsSwitch);
    mParentIsSwitch = true;
    switchNode->getStatementList()->traverse(this);
    mParentIsSwitch = false;

    return false;
}

bool GenMetalTraverser::visitCase(Visit, TIntermCase *caseNode)
{
    emitIndentation();

    if (caseNode->hasCondition())
    {
        TIntermTyped *condExpr = caseNode->getCondition();
        mOut << "case ";
        condExpr->traverse(this);
        mOut << ":";
    }
    else
    {
        mOut << "default:\n";
    }

    return false;
}

void GenMetalTraverser::emitFunctionSignature(const TFunction &func)
{
    const bool isMain = func.isMain();

    emitFunctionReturn(func);

    mOut << " ";
    emitNameOf(func);
    if (isMain)
    {
        mOut << "0";
    }
    mOut << "(";

    bool emitComma          = false;
    const size_t paramCount = func.getParamCount();
    for (size_t i = 0; i < paramCount; ++i)
    {
        if (emitComma)
        {
            mOut << ", ";
        }
        emitComma = true;

        const TVariable &param = *func.getParam(i);
        emitFunctionParameter(func, param);
    }
    if(isTraversingVertexMain)
    {
        mOut << " @@XFB-Bindings@@ ";
    }

    mOut << ")";
}

void GenMetalTraverser::emitFunctionReturn(const TFunction &func)
{
    const bool isMain = func.isMain();
    bool isVertexMain = false;
    const TType &returnType = func.getReturnType();
    if (isMain)
    {
        const TStructure *structure = returnType.getStruct();
        ASSERT(structure != nullptr);
        if (mPipelineStructs.fragmentOut.matches(*structure))
        {
            mOut << "fragment ";
        }
        else if (mPipelineStructs.vertexOut.matches(*structure))
        {
            mOut << "vertex __VERTEX_OUT(";
            isVertexMain = true;
        }
        else
        {
            TODO();
        }
    }
    emitType(returnType, EmitTypeConfig());
    if(isVertexMain)
        mOut << ") ";
}

void GenMetalTraverser::emitFunctionParameter(const TFunction &func, const TVariable &param)
{
    const bool isMain = func.isMain();

    const TType &type           = param.getType();
    const TStructure *structure = type.getStruct();

    EmitVariableDeclarationConfig evdConfig;
    evdConfig.isParameter       = true;
    evdConfig.isMainParameter   = isMain;
    evdConfig.emitPostQualifier = isMain;
    evdConfig.isUBO             = mSymbolEnv.isUBO(param);
    evdConfig.isPointer         = mSymbolEnv.isPointer(param);
    evdConfig.isReference       = mSymbolEnv.isReference(param);
    emitVariableDeclaration(VarDecl(param), evdConfig);

    if (isMain)
    {
        TranslatorMetalReflection *reflection =
            ((sh::TranslatorMetalDirect *)&mCompiler)->getTranslatorMetalReflection();
        if (structure)
        {
            if (mPipelineStructs.fragmentIn.matches(*structure) ||
                mPipelineStructs.vertexIn.matches(*structure))
            {
                mOut << " [[stage_in]]";
            }
            else if (mPipelineStructs.angleUniforms.matches(*structure))
            {
                mOut << " [[buffer(" << rx::mtl::kDriverUniformsBindingIndex << ")]]";
            }
            else if (mPipelineStructs.uniformBuffers.matches(*structure))
            {
                mOut << " [[buffer(" << rx::mtl::kUBOArgumentBufferBindingIndex << ")]]";
                reflection->hasUBOs = true;
            }
            else if (mPipelineStructs.userUniforms.matches(*structure))
            {
                mOut << " [[buffer(" << mMainUniformBufferIndex << ")]]";
                reflection->addUserUniformBufferBinding(param.name().data(), mMainUniformBufferIndex);
                mMainUniformBufferIndex += type.getArraySizeProduct();
            }
            else if (structure->name() == "metal::sampler")
            {
                mOut << " [[sampler(" << (mMainSamplerIndex) << ")]]";
                const std::string originalName =
                    reflection->getOriginalName(param.uniqueId().get());
                reflection->addSamplerBinding(originalName, mMainSamplerIndex);
                mMainSamplerIndex += type.getArraySizeProduct();
            }
        }
        else if (IsSampler(type.getBasicType()))
        {
            mOut << " [[texture(" << (mMainTextureIndex) << ")]]";
            const std::string originalName = reflection->getOriginalName(param.uniqueId().get());
            reflection->addTextureBinding(originalName, mMainSamplerIndex);
            mMainTextureIndex += type.getArraySizeProduct();
        }
        else if (Name(param) == Pipeline{Pipeline::Type::InstanceId, nullptr}.getStructInstanceName(
                                    Pipeline::Variant::Modified))
        {
            mOut << " [[instance_id]]";
        }
    }
}

void GenMetalTraverser::visitFunctionPrototype(TIntermFunctionPrototype *funcProtoNode)
{
    const TFunction &func = *funcProtoNode->getFunction();

    emitIndentation();
    emitFunctionSignature(func);
}

bool GenMetalTraverser::visitFunctionDefinition(Visit, TIntermFunctionDefinition *funcDefNode)
{
    const TFunction &func = *funcDefNode->getFunction();
    TIntermBlock &body    = *funcDefNode->getBody();
    if(func.isMain())
    {
        const TType &returnType = func.getReturnType();
        const TStructure *structure = returnType.getStruct();
        isTraversingVertexMain = (mPipelineStructs.vertexOut.matches(*structure));
    }
    emitIndentation();
    emitFunctionSignature(func);
    mOut << "\n";
    body.traverse(this);
    if(isTraversingVertexMain)
    {
        isTraversingVertexMain = false;
    }
    return false;
}

GenMetalTraverser::FuncToName GenMetalTraverser::BuildFuncToName()
{
    FuncToName map;

    auto putAngle = [&](const char *nameStr) {
        const ImmutableString name(nameStr);
        ASSERT(map.find(name) == map.end());
        map[name] = Name(nameStr, SymbolType::AngleInternal);
    };

    putAngle("texelFetch");
    putAngle("texelFetchOffset");
    putAngle("texture");
    putAngle("texture1D");
    putAngle("texture1DLod");
    putAngle("texture1DProjLod");
    putAngle("texture2D");
    putAngle("texture2DLod");
    putAngle("texture2DProj");
    putAngle("texture2DRect");
    putAngle("texture2DProjLod");
    putAngle("texture2DRectProj");
    putAngle("texture3D");
    putAngle("texture3DLod");
    putAngle("texture3DProjLod");
    putAngle("textureCube");
    putAngle("textureCubeLod");
    putAngle("textureCubeProjLod");
    putAngle("textureGrad");
    putAngle("textureGradOffset");
    putAngle("textureLod");
    putAngle("textureLodOffset");
    putAngle("textureOffset");
    putAngle("textureProj");
    putAngle("textureProjGrad");
    putAngle("textureProjGradOffset");
    putAngle("textureProjLod");
    putAngle("textureProjLodOffset");
    putAngle("textureProjOffset");
    putAngle("textureSize");

    return map;
}

bool GenMetalTraverser::visitAggregate(Visit, TIntermAggregate *aggregateNode)
{
    const TIntermSequence &args = *aggregateNode->getSequence();

    auto emitArgList = [&](const char *open, const char *close) {
        mOut << open;

        bool emitComma = false;
        for (TIntermNode *arg : args)
        {
            if (emitComma)
            {
                emitClosingPointerParen();
                mOut << ", ";
            }
            emitComma = true;
            arg->traverse(this);
        }

        mOut << close;
    };

    const TType &retType = aggregateNode->getType();

    if (aggregateNode->isConstructor())
    {
        const bool isStandalone = getParentNode()->getAsBlock();
        if (isStandalone)
        {
            // Prevent constructor from being interpreted as a declaration by wrapping in parens.
            // This can happen if given something like:
            //      int(symbol); // <- This will be treated like `int symbol;`... don't want that.
            // So instead emit:
            //      (int(symbol));
            mOut << "(";
        }

        const EmitTypeConfig etConfig;

        if (retType.isArray())
        {
            emitType(retType, etConfig);
            emitArgList("{", "}");
        }
        else if (retType.getStruct())
        {
            emitType(retType, etConfig);
            emitArgList("{", "}");
        }
        else
        {
            emitType(retType, etConfig);
            emitArgList("(", ")");
        }

        if (isStandalone)
        {
            mOut << ")";
        }

        return false;
    }
    else
    {
        const TOperator op = aggregateNode->getOp();
        if(op == EOpAtan)
        {
            TranslatorMetalReflection *reflection =
                ((sh::TranslatorMetalDirect *)&mCompiler)->getTranslatorMetalReflection();
            reflection->hasAtan = true;
        }
        switch (op)
        {
            case TOperator::EOpCallFunctionInAST:
            case TOperator::EOpCallInternalRawFunction:
            {
                const TFunction &func = *aggregateNode->getFunction();
                emitNameOf(func);
                //'@' symbol in name specifices a macro substitution marker.
                if(!func.name().contains("@"))
                {
                    emitArgList("(", ")");
                }
                else
                {
                    mTemporarilyDisableSemicolon = true; //Disable semicolon for macro substitution.
                }
                return false;
            }

            case TOperator::EOpCallBuiltInFunction:
            {
                const TFunction &func = *aggregateNode->getFunction();
                auto it               = mFuncToName.find(func.name());
                ASSERT(it != mFuncToName.end());
                EmitName(mOut, it->second);
                emitArgList("(", ")");
                return false;
            }

            default:
            {
                auto getArgType = [&](size_t index) -> const TType * {
                    if (index < args.size())
                    {
                        TIntermTyped *arg = args[index]->getAsTyped();
                        ASSERT(arg);
                        return &arg->getType();
                    }
                    return nullptr;
                };

                ASSERT(!args.empty());
                const TType *argType0 = getArgType(0);
                const TType *argType1 = getArgType(1);
                const TType *argType2 = getArgType(2);
                ASSERT(argType0);

                const char *opName = GetOperatorString(op, retType, argType0, argType1, argType2);

                if (IsSymbolicOperator(op, retType, argType0, argType1))
                {
                    switch (args.size())
                    {
                        case 1:
                        {
                            TIntermNode &operandNode = *aggregateNode->getChildNode(0);
                            if (IsPostfix(op))
                            {
                                mOut << opName;
                                groupedTraverse(operandNode);
                                return false;
                            }
                            else
                            {
                                groupedTraverse(operandNode);
                                mOut << opName;
                                return false;
                            }
                        }
                        break;

                        case 2:
                        {
                            TIntermNode &leftNode  = *aggregateNode->getChildNode(0);
                            TIntermNode &rightNode = *aggregateNode->getChildNode(1);
                            groupedTraverse(leftNode);
                            mOut << " " << opName << " ";
                            groupedTraverse(rightNode);
                            return false;
                        }
                        break;

                        default:
                            LOGIC_ERROR();
                            return false;
                    }
                }
                else
                {
                    mOut << opName;
                    emitArgList("(", ")");
                    return false;
                }
            }
        }
    }
}

void GenMetalTraverser::emitOpenBrace()
{
    ASSERT(mIndentLevel >= 0);

    emitIndentation();
    mOut << "{\n";
    ++mIndentLevel;
}

void GenMetalTraverser::emitCloseBrace()
{
    ASSERT(mIndentLevel >= 1);

    --mIndentLevel;
    emitIndentation();
    mOut << "}";
}

static bool RequiresSemicolonTerminator(TIntermNode &node)
{
    if (node.getAsBlock())
    {
        return false;
    }
    if (node.getAsLoopNode())
    {
        return false;
    }
    if (node.getAsSwitchNode())
    {
        return false;
    }
    if (node.getAsIfElseNode())
    {
        return false;
    }
    if (node.getAsFunctionDefinition())
    {
        return false;
    }
    if (node.getAsCaseNode())
    {
        return false;
    }

    return true;
}

static bool NewlinePad(TIntermNode &node)
{
    if (node.getAsFunctionDefinition())
    {
        return true;
    }
    if (TIntermDeclaration *declNode = node.getAsDeclarationNode())
    {
        ASSERT(declNode->getChildCount() == 1);
        TIntermNode &childNode = *declNode->getChildNode(0);
        if (TIntermSymbol *symbolNode = childNode.getAsSymbolNode())
        {
            const TVariable &var = symbolNode->variable();
            return var.getType().isStructSpecifier();
        }
        return false;
    }
    return false;
}

bool GenMetalTraverser::visitBlock(Visit, TIntermBlock *blockNode)
{
    ASSERT(mIndentLevel >= -1);
    const bool isGlobalScope  = mIndentLevel == -1;
    const bool parentIsSwitch = mParentIsSwitch;
    mParentIsSwitch           = false;

    if (isGlobalScope)
    {
        ++mIndentLevel;
    }
    else
    {
        emitOpenBrace();
        if (parentIsSwitch)
        {
            ++mIndentLevel;
        }
    }

    TIntermNode *prevStmtNode = nullptr;

    const size_t stmtCount = blockNode->getChildCount();
    for (size_t i = 0; i < stmtCount; ++i)
    {
        TIntermNode &stmtNode = *blockNode->getChildNode(i);

        if (isGlobalScope && prevStmtNode && (NewlinePad(*prevStmtNode) || NewlinePad(stmtNode)))
        {
            mOut << "\n";
        }
        const bool isCase = stmtNode.getAsCaseNode();
        mIndentLevel -= isCase;
        emitIndentation();
        mIndentLevel += isCase;
        stmtNode.traverse(this);
        if (RequiresSemicolonTerminator(stmtNode) && !mTemporarilyDisableSemicolon)
        {
            mOut << ";";
        }
        mTemporarilyDisableSemicolon = false;
        mOut << "\n";

        prevStmtNode = &stmtNode;
    }

    if (isGlobalScope)
    {
        ASSERT(mIndentLevel == 0);
        --mIndentLevel;
    }
    else
    {
        if (parentIsSwitch)
        {
            ASSERT(mIndentLevel >= 1);
            --mIndentLevel;
        }
        emitCloseBrace();
        mParentIsSwitch = parentIsSwitch;
    }

    return false;
}

bool GenMetalTraverser::visitGlobalQualifierDeclaration(Visit, TIntermGlobalQualifierDeclaration *)
{
    LOGIC_ERROR();  // RewriteGlobalQualifierDecls should have been called before this.
    return false;
}

bool GenMetalTraverser::visitDeclaration(Visit, TIntermDeclaration *declNode)
{
    ASSERT(declNode->getChildCount() == 1);
    TIntermNode &node = *declNode->getChildNode(0);

    EmitVariableDeclarationConfig evdConfig;

    if (TIntermSymbol *symbolNode = node.getAsSymbolNode())
    {
        const TVariable &var = symbolNode->variable();
        emitVariableDeclaration(VarDecl(var), evdConfig);
    }
    else if (TIntermBinary *initNode = node.getAsBinaryNode())
    {
        ASSERT(initNode->getOp() == TOperator::EOpInitialize);
        TIntermSymbol *symbolNode = initNode->getLeft()->getAsSymbolNode();
        TIntermTyped *valueNode   = initNode->getRight()->getAsTyped();
        ASSERT(symbolNode && valueNode);

        if (getRootNode() == getParentBlock())
        {
            // DeferGlobalInitializers should have turned non-const global initializers into
            // deferred initializers. Note that variables marked as EvqGlobal can be treated as
            // EvqConst in some ANGLE code but not actually have their qualifier actually changed to
            // EvqConst. Thus just assume all EvqGlobal are actually EvqConst for all code run after
            // DeferGlobalInitializers.
            mOut << "constant ";
        }

        const TVariable &var = symbolNode->variable();
        const Name varName(var);

        if (ExpressionContainsName(varName, *valueNode))
        {
            mRenamedSymbols[&var] = mIdGen.createNewName(varName);
        }

        emitVariableDeclaration(VarDecl(var), evdConfig);
        mOut << " = ";
        groupedTraverse(*valueNode);
    }
    else
    {
        LOGIC_ERROR();
    }

    return false;
}

bool GenMetalTraverser::visitLoop(Visit, TIntermLoop *loopNode)
{
    const TLoopType loopType = loopNode->getType();

    switch (loopType)
    {
        case TLoopType::ELoopFor:
            return visitForLoop(loopNode);
        case TLoopType::ELoopWhile:
            return visitWhileLoop(loopNode);
        case TLoopType::ELoopDoWhile:
            return visitDoWhileLoop(loopNode);
    }
}

bool GenMetalTraverser::visitForLoop(TIntermLoop *loopNode)
{
    ASSERT(loopNode->getType() == TLoopType::ELoopFor);

    TIntermNode *initNode  = loopNode->getInit();
    TIntermTyped *condNode = loopNode->getCondition();
    TIntermTyped *exprNode = loopNode->getExpression();
    TIntermBlock *bodyNode = loopNode->getBody();
    ASSERT(bodyNode);

    mOut << "for (";

    if (initNode)
    {
        initNode->traverse(this);
    }
    else
    {
        mOut << " ";
    }

    mOut << "; ";

    if (condNode)
    {
        condNode->traverse(this);
    }

    mOut << "; ";

    if (exprNode)
    {
        exprNode->traverse(this);
    }

    mOut << ")\n";

    bodyNode->traverse(this);

    return false;
}

bool GenMetalTraverser::visitWhileLoop(TIntermLoop *loopNode)
{
    ASSERT(loopNode->getType() == TLoopType::ELoopWhile);

    TIntermNode *initNode  = loopNode->getInit();
    TIntermTyped *condNode = loopNode->getCondition();
    TIntermTyped *exprNode = loopNode->getExpression();
    TIntermBlock *bodyNode = loopNode->getBody();
    ASSERT(condNode && bodyNode);
    ASSERT(!initNode && !exprNode);

    emitIndentation();
    mOut << "while (";
    condNode->traverse(this);
    mOut << ")\n";
    bodyNode->traverse(this);

    return false;
}

bool GenMetalTraverser::visitDoWhileLoop(TIntermLoop *loopNode)
{
    ASSERT(loopNode->getType() == TLoopType::ELoopDoWhile);

    TIntermNode *initNode  = loopNode->getInit();
    TIntermTyped *condNode = loopNode->getCondition();
    TIntermTyped *exprNode = loopNode->getExpression();
    TIntermBlock *bodyNode = loopNode->getBody();
    ASSERT(condNode && bodyNode);
    ASSERT(!initNode && !exprNode);

    emitIndentation();
    mOut << "do\n";
    bodyNode->traverse(this);
    mOut << "\n";
    emitIndentation();
    mOut << "while (";
    condNode->traverse(this);
    mOut << ");";

    return false;
}

bool GenMetalTraverser::visitBranch(Visit, TIntermBranch *branchNode)
{
    const TOperator flowOp = branchNode->getFlowOp();
    TIntermTyped *exprNode = branchNode->getExpression();

    emitIndentation();

    switch (flowOp)
    {
        case TOperator::EOpKill:
        {
            ASSERT(exprNode == nullptr);
            mOut << "metal::discard_fragment()";
        }
        break;

        case TOperator::EOpReturn:
        {
            if(isTraversingVertexMain)
            {
                mOut << "#if TRANSFORM_FEEDBACK_ENABLED\n";
                emitIndentation();
                mOut << "return;\n";
                emitIndentation();
                mOut << "#else\n";
                emitIndentation();
            }
            mOut << "return";
            if (exprNode)
            {
                mOut << " ";
                exprNode->traverse(this);
                mOut << ";";
            }
            if(isTraversingVertexMain)
            {
                mOut << "\n";
                emitIndentation();
                mOut << "#endif\n";
                mTemporarilyDisableSemicolon = true;
            }
        }
        break;

        case TOperator::EOpBreak:
        {
            ASSERT(exprNode == nullptr);
            mOut << "break";
        }
        break;

        case TOperator::EOpContinue:
        {
            ASSERT(exprNode == nullptr);
            mOut << "continue";
        }
        break;

        default:
        {
            LOGIC_ERROR();
        }
    }

    return false;
}

static size_t emitMetalCallCount = 0;

bool sh::EmitMetal(TCompiler &compiler,
                   TIntermBlock &root,
                   IdGen &idGen,
                   const PipelineStructs &pipelineStructs,
                   const Invariants &invariants,
                   SymbolEnv &symbolEnv,
                   const ProgramPreludeConfig &ppc)
{
    TInfoSinkBase &out = compiler.getInfoSink().obj;

    {
        ++emitMetalCallCount;
        auto filenameProto = readStringEnvVar("GMD_FIXED_EMIT");
        if (!filenameProto.empty())
        {
            if (filenameProto != "/dev/null")
            {
                auto tryOpen = [&](char const *ext) {
                    auto filename = filenameProto;
                    filename += std::to_string(emitMetalCallCount);
                    filename += ".";
                    filename += ext;
                    return fopen(filename.c_str(), "rb");
                };
                FILE *file = tryOpen("metal");
                if (!file)
                {
                    file = tryOpen("cpp");
                }
                ASSERT(file);

                fseek(file, 0, SEEK_END);
                size_t fileSize = ftell(file);
                fseek(file, 0, SEEK_SET);

                std::vector<char> buff;
                buff.resize(fileSize + 1);
                fread(buff.data(), fileSize, 1, file);
                buff.back() = '\0';

                fclose(file);

                out << buff.data();
            }

            return true;
        }
    }

    out << "\n\n";

    if (!EmitProgramPrelude(root, out, ppc))
    {
        return false;
    }

    {
#if defined(ANGLE_ENABLE_ASSERTS)
        DebugSink outWrapper(out, readBoolEnvVar("GMD_STDOUT"));
        outWrapper.watch(readStringEnvVar("GMD_WATCH_STRING"));
#else
        TInfoSinkBase &outWrapper = out;
#endif
        GenMetalTraverser gen(compiler, outWrapper, idGen, pipelineStructs, invariants, symbolEnv);
        root.traverse(&gen);
    }

    out << "\n";

    return true;
}
