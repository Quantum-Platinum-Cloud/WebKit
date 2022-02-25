/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "JSTestDefaultToJSONFilteredByExposed.h"

#include "ActiveDOMObject.h"
#include "DOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertNumbers.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/ObjectConstructor.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

// Functions

static JSC_DECLARE_HOST_FUNCTION(jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSON);

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposedConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_normalAttribute);
static JSC_DECLARE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttribute);
static JSC_DECLARE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttribute);

class JSTestDefaultToJSONFilteredByExposedPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestDefaultToJSONFilteredByExposedPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestDefaultToJSONFilteredByExposedPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestDefaultToJSONFilteredByExposedPrototype>(vm)) JSTestDefaultToJSONFilteredByExposedPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestDefaultToJSONFilteredByExposedPrototype, Base);
        return &vm.plainObjectSpace();
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestDefaultToJSONFilteredByExposedPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestDefaultToJSONFilteredByExposedPrototype, JSTestDefaultToJSONFilteredByExposedPrototype::Base);

using JSTestDefaultToJSONFilteredByExposedDOMConstructor = JSDOMConstructorNotConstructable<JSTestDefaultToJSONFilteredByExposed>;

template<> const ClassInfo JSTestDefaultToJSONFilteredByExposedDOMConstructor::s_info = { "TestDefaultToJSONFilteredByExposed", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestDefaultToJSONFilteredByExposedDOMConstructor) };

template<> JSValue JSTestDefaultToJSONFilteredByExposedDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestDefaultToJSONFilteredByExposedDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "TestDefaultToJSONFilteredByExposed"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSTestDefaultToJSONFilteredByExposed::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const HashTableValue JSTestDefaultToJSONFilteredByExposedPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestDefaultToJSONFilteredByExposedConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "normalAttribute", static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestDefaultToJSONFilteredByExposed_normalAttribute), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "filteredByExposedWindowAttribute", static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttribute), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "filteredByExposedWorkerAttribute", static_cast<unsigned>(JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttribute), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "toJSON", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSON), (intptr_t) (0) } },
};

const ClassInfo JSTestDefaultToJSONFilteredByExposedPrototype::s_info = { "TestDefaultToJSONFilteredByExposed", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestDefaultToJSONFilteredByExposedPrototype) };

void JSTestDefaultToJSONFilteredByExposedPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestDefaultToJSONFilteredByExposed::info(), JSTestDefaultToJSONFilteredByExposedPrototypeTableValues, *this);
    bool hasDisabledRuntimeProperties = false;
    if (!jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext()->isDocument()) {
        hasDisabledRuntimeProperties = true;
        auto propertyName = Identifier::fromString(vm, reinterpret_cast<const LChar*>("filteredByExposedWindowAttribute"), strlen("filteredByExposedWindowAttribute"));
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        DeletePropertySlot slot;
        JSObject::deleteProperty(this, globalObject(), propertyName, slot);
    }
    if (!jsCast<JSDOMGlobalObject*>(globalObject())->scriptExecutionContext()->isWorkerGlobalScope()) {
        hasDisabledRuntimeProperties = true;
        auto propertyName = Identifier::fromString(vm, reinterpret_cast<const LChar*>("filteredByExposedWorkerAttribute"), strlen("filteredByExposedWorkerAttribute"));
        VM::DeletePropertyModeScope scope(vm, VM::DeletePropertyMode::IgnoreConfigurable);
        DeletePropertySlot slot;
        JSObject::deleteProperty(this, globalObject(), propertyName, slot);
    }
    if (hasDisabledRuntimeProperties && structure()->isDictionary())
        flattenDictionaryObject(vm);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestDefaultToJSONFilteredByExposed::s_info = { "TestDefaultToJSONFilteredByExposed", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestDefaultToJSONFilteredByExposed) };

JSTestDefaultToJSONFilteredByExposed::JSTestDefaultToJSONFilteredByExposed(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestDefaultToJSONFilteredByExposed>&& impl)
    : JSDOMWrapper<TestDefaultToJSONFilteredByExposed>(structure, globalObject, WTFMove(impl))
{
}

void JSTestDefaultToJSONFilteredByExposed::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

    static_assert(!std::is_base_of<ActiveDOMObject, TestDefaultToJSONFilteredByExposed>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

}

JSObject* JSTestDefaultToJSONFilteredByExposed::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestDefaultToJSONFilteredByExposedPrototype::create(vm, &globalObject, JSTestDefaultToJSONFilteredByExposedPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestDefaultToJSONFilteredByExposed::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestDefaultToJSONFilteredByExposed>(vm, globalObject);
}

JSValue JSTestDefaultToJSONFilteredByExposed::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestDefaultToJSONFilteredByExposedDOMConstructor, DOMConstructorID::TestDefaultToJSONFilteredByExposed>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestDefaultToJSONFilteredByExposed::destroy(JSC::JSCell* cell)
{
    JSTestDefaultToJSONFilteredByExposed* thisObject = static_cast<JSTestDefaultToJSONFilteredByExposed*>(cell);
    thisObject->JSTestDefaultToJSONFilteredByExposed::~JSTestDefaultToJSONFilteredByExposed();
}

JSC_DEFINE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposedConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestDefaultToJSONFilteredByExposedPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestDefaultToJSONFilteredByExposed::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

static inline JSValue jsTestDefaultToJSONFilteredByExposed_normalAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestDefaultToJSONFilteredByExposed& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLLong>(lexicalGlobalObject, throwScope, impl.normalAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_normalAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestDefaultToJSONFilteredByExposed>::get<jsTestDefaultToJSONFilteredByExposed_normalAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestDefaultToJSONFilteredByExposed& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDouble>(lexicalGlobalObject, throwScope, impl.filteredByExposedWindowAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestDefaultToJSONFilteredByExposed>::get<jsTestDefaultToJSONFilteredByExposed_filteredByExposedWindowAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttributeGetter(JSGlobalObject& lexicalGlobalObject, JSTestDefaultToJSONFilteredByExposed& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLDOMString>(lexicalGlobalObject, throwScope, impl.filteredByExposedWorkerAttribute())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttribute, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestDefaultToJSONFilteredByExposed>::get<jsTestDefaultToJSONFilteredByExposed_filteredByExposedWorkerAttributeGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline EncodedJSValue jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSONBody(JSGlobalObject* lexicalGlobalObject, CallFrame*, JSTestDefaultToJSONFilteredByExposed* castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    auto& impl = castedThis->wrapped();
    auto* result = constructEmptyObject(lexicalGlobalObject, castedThis->globalObject()->objectPrototype());
    auto normalAttributeValue = toJS<IDLLong>(*lexicalGlobalObject, throwScope, impl.normalAttribute());
    RETURN_IF_EXCEPTION(throwScope, { });
    result->putDirect(vm, Identifier::fromString(vm, "normalAttribute"), normalAttributeValue);
    if (jsCast<JSDOMGlobalObject*>(castedThis->globalObject())->scriptExecutionContext()->isDocument()) {
        auto filteredByExposedWindowAttributeValue = toJS<IDLDouble>(*lexicalGlobalObject, throwScope, impl.filteredByExposedWindowAttribute());
        RETURN_IF_EXCEPTION(throwScope, { });
        result->putDirect(vm, Identifier::fromString(vm, "filteredByExposedWindowAttribute"), filteredByExposedWindowAttributeValue);
    }
    if (jsCast<JSDOMGlobalObject*>(castedThis->globalObject())->scriptExecutionContext()->isWorkerGlobalScope()) {
        auto filteredByExposedWorkerAttributeValue = toJS<IDLDOMString>(*lexicalGlobalObject, throwScope, impl.filteredByExposedWorkerAttribute());
        RETURN_IF_EXCEPTION(throwScope, { });
        result->putDirect(vm, Identifier::fromString(vm, "filteredByExposedWorkerAttribute"), filteredByExposedWorkerAttributeValue);
    }
    return JSValue::encode(result);
}

JSC_DEFINE_HOST_FUNCTION(jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSON, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestDefaultToJSONFilteredByExposed>::call<jsTestDefaultToJSONFilteredByExposedPrototypeFunction_toJSONBody>(*lexicalGlobalObject, *callFrame, "toJSON");
}

JSC::IsoSubspace* JSTestDefaultToJSONFilteredByExposed::subspaceForImpl(JSC::VM& vm)
{
    auto& clientData = *static_cast<JSVMClientData*>(vm.clientData);
    auto& spaces = clientData.subspaces();
    if (auto* space = spaces.m_subspaceForTestDefaultToJSONFilteredByExposed.get())
        return space;
    static_assert(std::is_base_of_v<JSC::JSDestructibleObject, JSTestDefaultToJSONFilteredByExposed> || !JSTestDefaultToJSONFilteredByExposed::needsDestruction);
    if constexpr (std::is_base_of_v<JSC::JSDestructibleObject, JSTestDefaultToJSONFilteredByExposed>)
        spaces.m_subspaceForTestDefaultToJSONFilteredByExposed = makeUnique<IsoSubspace> ISO_SUBSPACE_INIT(vm.heap, vm.destructibleObjectHeapCellType(), JSTestDefaultToJSONFilteredByExposed);
    else
        spaces.m_subspaceForTestDefaultToJSONFilteredByExposed = makeUnique<IsoSubspace> ISO_SUBSPACE_INIT(vm.heap, vm.cellHeapCellType(), JSTestDefaultToJSONFilteredByExposed);
    auto* space = spaces.m_subspaceForTestDefaultToJSONFilteredByExposed.get();
IGNORE_WARNINGS_BEGIN("unreachable-code")
IGNORE_WARNINGS_BEGIN("tautological-compare")
    void (*myVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSTestDefaultToJSONFilteredByExposed::visitOutputConstraints;
    void (*jsCellVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSC::JSCell::visitOutputConstraints;
    if (myVisitOutputConstraint != jsCellVisitOutputConstraint)
        clientData.outputConstraintSpaces().append(space);
IGNORE_WARNINGS_END
IGNORE_WARNINGS_END
    return space;
}

void JSTestDefaultToJSONFilteredByExposed::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestDefaultToJSONFilteredByExposed*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestDefaultToJSONFilteredByExposedOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestDefaultToJSONFilteredByExposedOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestDefaultToJSONFilteredByExposed = static_cast<JSTestDefaultToJSONFilteredByExposed*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestDefaultToJSONFilteredByExposed->wrapped(), jsTestDefaultToJSONFilteredByExposed);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestDefaultToJSONFilteredByExposed@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore34TestDefaultToJSONFilteredByExposedE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestDefaultToJSONFilteredByExposed>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    const void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
    void* expectedVTablePointer = __identifier("??_7TestDefaultToJSONFilteredByExposed@WebCore@@6B@");
#else
    void* expectedVTablePointer = &_ZTVN7WebCore34TestDefaultToJSONFilteredByExposedE[2];
#endif

    // If this fails TestDefaultToJSONFilteredByExposed does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestDefaultToJSONFilteredByExposed>::value, "TestDefaultToJSONFilteredByExposed is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestDefaultToJSONFilteredByExposed has subclasses. If TestDefaultToJSONFilteredByExposed has subclasses that get passed
    // to toJS() we currently require TestDefaultToJSONFilteredByExposed you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestDefaultToJSONFilteredByExposed>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestDefaultToJSONFilteredByExposed& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestDefaultToJSONFilteredByExposed* JSTestDefaultToJSONFilteredByExposed::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestDefaultToJSONFilteredByExposed*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
