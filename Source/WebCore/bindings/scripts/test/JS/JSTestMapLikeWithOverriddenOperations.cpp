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
#include "JSTestMapLikeWithOverriddenOperations.h"

#include "ActiveDOMObject.h"
#include "DOMIsoSubspaces.h"
#include "IDLTypes.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMConvertAny.h"
#include "JSDOMConvertBase.h"
#include "JSDOMConvertNumbers.h"
#include "JSDOMConvertStrings.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMMapLike.h"
#include "JSDOMOperation.h"
#include "JSDOMWrapperCache.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include <JavaScriptCore/BuiltinNames.h>
#include <JavaScriptCore/FunctionPrototype.h>
#include <JavaScriptCore/HeapAnalyzer.h>
#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSDestructibleObjectHeapCellType.h>
#include <JavaScriptCore/SlotVisitorMacros.h>
#include <JavaScriptCore/SubspaceInlines.h>
#include <wtf/GetPtr.h>
#include <wtf/PointerPreparations.h>
#include <wtf/URL.h>


namespace WebCore {
using namespace JSC;

// Functions

static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_clear);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_get);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_has);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_entries);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_keys);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_values);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_forEach);
static JSC_DECLARE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_delete);

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsTestMapLikeWithOverriddenOperationsConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsTestMapLikeWithOverriddenOperations_set);
static JSC_DECLARE_CUSTOM_SETTER(setJSTestMapLikeWithOverriddenOperations_set);
static JSC_DECLARE_CUSTOM_GETTER(jsTestMapLikeWithOverriddenOperations_size);

class JSTestMapLikeWithOverriddenOperationsPrototype final : public JSC::JSNonFinalObject {
public:
    using Base = JSC::JSNonFinalObject;
    static JSTestMapLikeWithOverriddenOperationsPrototype* create(JSC::VM& vm, JSDOMGlobalObject* globalObject, JSC::Structure* structure)
    {
        JSTestMapLikeWithOverriddenOperationsPrototype* ptr = new (NotNull, JSC::allocateCell<JSTestMapLikeWithOverriddenOperationsPrototype>(vm.heap)) JSTestMapLikeWithOverriddenOperationsPrototype(vm, globalObject, structure);
        ptr->finishCreation(vm);
        return ptr;
    }

    DECLARE_INFO;
    template<typename CellType, JSC::SubspaceAccess>
    static JSC::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestMapLikeWithOverriddenOperationsPrototype, Base);
        return &vm.plainObjectSpace;
    }
    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info());
    }

private:
    JSTestMapLikeWithOverriddenOperationsPrototype(JSC::VM& vm, JSC::JSGlobalObject*, JSC::Structure* structure)
        : JSC::JSNonFinalObject(vm, structure)
    {
    }

    void finishCreation(JSC::VM&);
};
STATIC_ASSERT_ISO_SUBSPACE_SHARABLE(JSTestMapLikeWithOverriddenOperationsPrototype, JSTestMapLikeWithOverriddenOperationsPrototype::Base);

using JSTestMapLikeWithOverriddenOperationsDOMConstructor = JSDOMConstructorNotConstructable<JSTestMapLikeWithOverriddenOperations>;

template<> const ClassInfo JSTestMapLikeWithOverriddenOperationsDOMConstructor::s_info = { "TestMapLikeWithOverriddenOperations", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestMapLikeWithOverriddenOperationsDOMConstructor) };

template<> JSValue JSTestMapLikeWithOverriddenOperationsDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    UNUSED_PARAM(vm);
    return globalObject.functionPrototype();
}

template<> void JSTestMapLikeWithOverriddenOperationsDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->prototype, JSTestMapLikeWithOverriddenOperations::prototype(vm, globalObject), JSC::PropertyAttribute::DontDelete | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->name, jsNontrivialString(vm, "TestMapLikeWithOverriddenOperations"_s), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
}

/* Hash table for prototype */

static const HashTableValue JSTestMapLikeWithOverriddenOperationsPrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestMapLikeWithOverriddenOperationsConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "set", static_cast<unsigned>(JSC::PropertyAttribute::CustomAccessor | JSC::PropertyAttribute::DOMAttribute), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestMapLikeWithOverriddenOperations_set), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(setJSTestMapLikeWithOverriddenOperations_set) } },
    { "size", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::CustomAccessor), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsTestMapLikeWithOverriddenOperations_size), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "clear", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_clear), (intptr_t) (0) } },
    { "get", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_get), (intptr_t) (1) } },
    { "has", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_has), (intptr_t) (1) } },
    { "entries", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_entries), (intptr_t) (0) } },
    { "keys", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_keys), (intptr_t) (0) } },
    { "values", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_values), (intptr_t) (0) } },
    { "forEach", static_cast<unsigned>(JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_forEach), (intptr_t) (1) } },
    { "delete", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::Function), NoIntrinsic, { (intptr_t)static_cast<RawNativeFunction>(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_delete), (intptr_t) (1) } },
};

const ClassInfo JSTestMapLikeWithOverriddenOperationsPrototype::s_info = { "TestMapLikeWithOverriddenOperations", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestMapLikeWithOverriddenOperationsPrototype) };

void JSTestMapLikeWithOverriddenOperationsPrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSTestMapLikeWithOverriddenOperations::info(), JSTestMapLikeWithOverriddenOperationsPrototypeTableValues, *this);
    putDirect(vm, vm.propertyNames->iteratorSymbol, getDirect(vm, vm.propertyNames->builtinNames().entriesPublicName()), static_cast<unsigned>(JSC::PropertyAttribute::DontEnum));
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSTestMapLikeWithOverriddenOperations::s_info = { "TestMapLikeWithOverriddenOperations", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSTestMapLikeWithOverriddenOperations) };

JSTestMapLikeWithOverriddenOperations::JSTestMapLikeWithOverriddenOperations(Structure* structure, JSDOMGlobalObject& globalObject, Ref<TestMapLikeWithOverriddenOperations>&& impl)
    : JSDOMWrapper<TestMapLikeWithOverriddenOperations>(structure, globalObject, WTFMove(impl))
{
}

void JSTestMapLikeWithOverriddenOperations::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    ASSERT(inherits(vm, info()));

    static_assert(!std::is_base_of<ActiveDOMObject, TestMapLikeWithOverriddenOperations>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

}

JSObject* JSTestMapLikeWithOverriddenOperations::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSTestMapLikeWithOverriddenOperationsPrototype::create(vm, &globalObject, JSTestMapLikeWithOverriddenOperationsPrototype::createStructure(vm, &globalObject, globalObject.objectPrototype()));
}

JSObject* JSTestMapLikeWithOverriddenOperations::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSTestMapLikeWithOverriddenOperations>(vm, globalObject);
}

JSValue JSTestMapLikeWithOverriddenOperations::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSTestMapLikeWithOverriddenOperationsDOMConstructor, DOMConstructorID::TestMapLikeWithOverriddenOperations>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

void JSTestMapLikeWithOverriddenOperations::destroy(JSC::JSCell* cell)
{
    JSTestMapLikeWithOverriddenOperations* thisObject = static_cast<JSTestMapLikeWithOverriddenOperations*>(cell);
    thisObject->JSTestMapLikeWithOverriddenOperations::~JSTestMapLikeWithOverriddenOperations();
}

JSC_DEFINE_CUSTOM_GETTER(jsTestMapLikeWithOverriddenOperationsConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSTestMapLikeWithOverriddenOperationsPrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSTestMapLikeWithOverriddenOperations::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

static inline JSValue jsTestMapLikeWithOverriddenOperations_setGetter(JSGlobalObject& lexicalGlobalObject, JSTestMapLikeWithOverriddenOperations& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    RELEASE_AND_RETURN(throwScope, (toJS<IDLLong>(lexicalGlobalObject, throwScope, impl.set())));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestMapLikeWithOverriddenOperations_set, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestMapLikeWithOverriddenOperations>::get<jsTestMapLikeWithOverriddenOperations_setGetter, CastedThisErrorBehavior::Assert>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline bool setJSTestMapLikeWithOverriddenOperations_setSetter(JSGlobalObject& lexicalGlobalObject, JSTestMapLikeWithOverriddenOperations& thisObject, JSValue value)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto& impl = thisObject.wrapped();
    auto nativeValue = convert<IDLLong>(lexicalGlobalObject, value);
    RETURN_IF_EXCEPTION(throwScope, false);
    invokeFunctorPropagatingExceptionIfNecessary(lexicalGlobalObject, throwScope, [&] {
        return impl.setSet(WTFMove(nativeValue));
    });
    return true;
}

JSC_DEFINE_CUSTOM_SETTER(setJSTestMapLikeWithOverriddenOperations_set, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, EncodedJSValue encodedValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestMapLikeWithOverriddenOperations>::set<setJSTestMapLikeWithOverriddenOperations_setSetter>(*lexicalGlobalObject, thisValue, encodedValue, attributeName);
}

static inline JSValue jsTestMapLikeWithOverriddenOperations_sizeGetter(JSGlobalObject& lexicalGlobalObject, JSTestMapLikeWithOverriddenOperations& thisObject)
{
    auto& vm = JSC::getVM(&lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    RELEASE_AND_RETURN(throwScope, (toJS<IDLAny>(lexicalGlobalObject, throwScope, forwardSizeToMapLike(lexicalGlobalObject, thisObject))));
}

JSC_DEFINE_CUSTOM_GETTER(jsTestMapLikeWithOverriddenOperations_size, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSTestMapLikeWithOverriddenOperations>::get<jsTestMapLikeWithOverriddenOperations_sizeGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSC::EncodedJSValue jsTestMapLikeWithOverriddenOperationsPrototypeFunction_clearBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLikeWithOverriddenOperations>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    auto& impl = castedThis->wrapped();
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLUndefined>(*lexicalGlobalObject, throwScope, [&]() -> decltype(auto) { return impl.clear(); })));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_clear, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLikeWithOverriddenOperations>::call<jsTestMapLikeWithOverriddenOperationsPrototypeFunction_clearBody>(*lexicalGlobalObject, *callFrame, "clear");
}

static inline JSC::EncodedJSValue jsTestMapLikeWithOverriddenOperationsPrototypeFunction_getBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLikeWithOverriddenOperations>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto key = convert<IDLDOMString>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardGetToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(key)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_get, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLikeWithOverriddenOperations>::call<jsTestMapLikeWithOverriddenOperationsPrototypeFunction_getBody>(*lexicalGlobalObject, *callFrame, "get");
}

static inline JSC::EncodedJSValue jsTestMapLikeWithOverriddenOperationsPrototypeFunction_hasBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLikeWithOverriddenOperations>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto key = convert<IDLDOMString>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardHasToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(key)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_has, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLikeWithOverriddenOperations>::call<jsTestMapLikeWithOverriddenOperationsPrototypeFunction_hasBody>(*lexicalGlobalObject, *callFrame, "has");
}

static inline JSC::EncodedJSValue jsTestMapLikeWithOverriddenOperationsPrototypeFunction_entriesBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLikeWithOverriddenOperations>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardEntriesToMapLike(*lexicalGlobalObject, *callFrame, *castedThis))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_entries, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLikeWithOverriddenOperations>::call<jsTestMapLikeWithOverriddenOperationsPrototypeFunction_entriesBody>(*lexicalGlobalObject, *callFrame, "entries");
}

static inline JSC::EncodedJSValue jsTestMapLikeWithOverriddenOperationsPrototypeFunction_keysBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLikeWithOverriddenOperations>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardKeysToMapLike(*lexicalGlobalObject, *callFrame, *castedThis))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_keys, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLikeWithOverriddenOperations>::call<jsTestMapLikeWithOverriddenOperationsPrototypeFunction_keysBody>(*lexicalGlobalObject, *callFrame, "keys");
}

static inline JSC::EncodedJSValue jsTestMapLikeWithOverriddenOperationsPrototypeFunction_valuesBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLikeWithOverriddenOperations>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardValuesToMapLike(*lexicalGlobalObject, *callFrame, *castedThis))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_values, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLikeWithOverriddenOperations>::call<jsTestMapLikeWithOverriddenOperationsPrototypeFunction_valuesBody>(*lexicalGlobalObject, *callFrame, "values");
}

static inline JSC::EncodedJSValue jsTestMapLikeWithOverriddenOperationsPrototypeFunction_forEachBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLikeWithOverriddenOperations>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto callback = convert<IDLAny>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardForEachToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(callback)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_forEach, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLikeWithOverriddenOperations>::call<jsTestMapLikeWithOverriddenOperationsPrototypeFunction_forEachBody>(*lexicalGlobalObject, *callFrame, "forEach");
}

static inline JSC::EncodedJSValue jsTestMapLikeWithOverriddenOperationsPrototypeFunction_deleteBody(JSC::JSGlobalObject* lexicalGlobalObject, JSC::CallFrame* callFrame, typename IDLOperation<JSTestMapLikeWithOverriddenOperations>::ClassParameter castedThis)
{
    auto& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    UNUSED_PARAM(throwScope);
    UNUSED_PARAM(callFrame);
    if (UNLIKELY(callFrame->argumentCount() < 1))
        return throwVMError(lexicalGlobalObject, throwScope, createNotEnoughArgumentsError(lexicalGlobalObject));
    EnsureStillAliveScope argument0 = callFrame->uncheckedArgument(0);
    auto key = convert<IDLDOMString>(*lexicalGlobalObject, argument0.value());
    RETURN_IF_EXCEPTION(throwScope, encodedJSValue());
    RELEASE_AND_RETURN(throwScope, JSValue::encode(toJS<IDLAny>(*lexicalGlobalObject, throwScope, forwardDeleteToMapLike(*lexicalGlobalObject, *callFrame, *castedThis, WTFMove(key)))));
}

JSC_DEFINE_HOST_FUNCTION(jsTestMapLikeWithOverriddenOperationsPrototypeFunction_delete, (JSGlobalObject* lexicalGlobalObject, CallFrame* callFrame))
{
    return IDLOperation<JSTestMapLikeWithOverriddenOperations>::call<jsTestMapLikeWithOverriddenOperationsPrototypeFunction_deleteBody>(*lexicalGlobalObject, *callFrame, "delete");
}

JSC::IsoSubspace* JSTestMapLikeWithOverriddenOperations::subspaceForImpl(JSC::VM& vm)
{
    auto& clientData = *static_cast<JSVMClientData*>(vm.clientData);
    auto& spaces = clientData.subspaces();
    if (auto* space = spaces.m_subspaceForTestMapLikeWithOverriddenOperations.get())
        return space;
    static_assert(std::is_base_of_v<JSC::JSDestructibleObject, JSTestMapLikeWithOverriddenOperations> || !JSTestMapLikeWithOverriddenOperations::needsDestruction);
    if constexpr (std::is_base_of_v<JSC::JSDestructibleObject, JSTestMapLikeWithOverriddenOperations>)
        spaces.m_subspaceForTestMapLikeWithOverriddenOperations = makeUnique<IsoSubspace> ISO_SUBSPACE_INIT(vm.heap, vm.destructibleObjectHeapCellType.get(), JSTestMapLikeWithOverriddenOperations);
    else
        spaces.m_subspaceForTestMapLikeWithOverriddenOperations = makeUnique<IsoSubspace> ISO_SUBSPACE_INIT(vm.heap, vm.cellHeapCellType.get(), JSTestMapLikeWithOverriddenOperations);
    auto* space = spaces.m_subspaceForTestMapLikeWithOverriddenOperations.get();
IGNORE_WARNINGS_BEGIN("unreachable-code")
IGNORE_WARNINGS_BEGIN("tautological-compare")
    void (*myVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSTestMapLikeWithOverriddenOperations::visitOutputConstraints;
    void (*jsCellVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSC::JSCell::visitOutputConstraints;
    if (myVisitOutputConstraint != jsCellVisitOutputConstraint)
        clientData.outputConstraintSpaces().append(space);
IGNORE_WARNINGS_END
IGNORE_WARNINGS_END
    return space;
}

void JSTestMapLikeWithOverriddenOperations::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSTestMapLikeWithOverriddenOperations*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

bool JSTestMapLikeWithOverriddenOperationsOwner::isReachableFromOpaqueRoots(JSC::Handle<JSC::Unknown> handle, void*, AbstractSlotVisitor& visitor, const char** reason)
{
    UNUSED_PARAM(handle);
    UNUSED_PARAM(visitor);
    UNUSED_PARAM(reason);
    return false;
}

void JSTestMapLikeWithOverriddenOperationsOwner::finalize(JSC::Handle<JSC::Unknown> handle, void* context)
{
    auto* jsTestMapLikeWithOverriddenOperations = static_cast<JSTestMapLikeWithOverriddenOperations*>(handle.slot()->asCell());
    auto& world = *static_cast<DOMWrapperWorld*>(context);
    uncacheWrapper(world, &jsTestMapLikeWithOverriddenOperations->wrapped(), jsTestMapLikeWithOverriddenOperations);
}

#if ENABLE(BINDING_INTEGRITY)
#if PLATFORM(WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestMapLikeWithOverriddenOperations@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore35TestMapLikeWithOverriddenOperationsE[]; }
#endif
#endif

JSC::JSValue toJSNewlyCreated(JSC::JSGlobalObject*, JSDOMGlobalObject* globalObject, Ref<TestMapLikeWithOverriddenOperations>&& impl)
{

#if ENABLE(BINDING_INTEGRITY)
    const void* actualVTablePointer = getVTablePointer(impl.ptr());
#if PLATFORM(WIN)
    void* expectedVTablePointer = __identifier("??_7TestMapLikeWithOverriddenOperations@WebCore@@6B@");
#else
    void* expectedVTablePointer = &_ZTVN7WebCore35TestMapLikeWithOverriddenOperationsE[2];
#endif

    // If this fails TestMapLikeWithOverriddenOperations does not have a vtable, so you need to add the
    // ImplementationLacksVTable attribute to the interface definition
    static_assert(std::is_polymorphic<TestMapLikeWithOverriddenOperations>::value, "TestMapLikeWithOverriddenOperations is not polymorphic");

    // If you hit this assertion you either have a use after free bug, or
    // TestMapLikeWithOverriddenOperations has subclasses. If TestMapLikeWithOverriddenOperations has subclasses that get passed
    // to toJS() we currently require TestMapLikeWithOverriddenOperations you to opt out of binding hardening
    // by adding the SkipVTableValidation attribute to the interface IDL definition
    RELEASE_ASSERT(actualVTablePointer == expectedVTablePointer);
#endif
    return createWrapper<TestMapLikeWithOverriddenOperations>(globalObject, WTFMove(impl));
}

JSC::JSValue toJS(JSC::JSGlobalObject* lexicalGlobalObject, JSDOMGlobalObject* globalObject, TestMapLikeWithOverriddenOperations& impl)
{
    return wrap(lexicalGlobalObject, globalObject, impl);
}

TestMapLikeWithOverriddenOperations* JSTestMapLikeWithOverriddenOperations::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSTestMapLikeWithOverriddenOperations*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
