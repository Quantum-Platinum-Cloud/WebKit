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
#include "JSWorkerGlobalScope.h"

#include "ActiveDOMObject.h"
#include "DOMIsoSubspaces.h"
#include "JSDOMAttribute.h"
#include "JSDOMBinding.h"
#include "JSDOMConstructorNotConstructable.h"
#include "JSDOMExceptionHandling.h"
#include "JSDOMGlobalObjectInlines.h"
#include "JSDOMWrapperCache.h"
#include "JSExposedToWorkerAndWindow.h"
#include "JSTestDefaultToJSONFilteredByExposed.h"
#include "JSTestNode.h"
#include "JSTestObj.h"
#include "JSTestPromiseRejectionEvent.h"
#include "JSWorkerGlobalScope.h"
#include "ScriptExecutionContext.h"
#include "WebCoreJSClientData.h"
#include "WorkerGlobalScope.h"
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

// Attributes

static JSC_DECLARE_CUSTOM_GETTER(jsWorkerGlobalScopeConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsWorkerGlobalScope_ExposedToWorkerAndWindowConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsWorkerGlobalScope_TestDefaultToJSONFilteredByExposedConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsWorkerGlobalScope_TestNodeConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsWorkerGlobalScope_TestObjectConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsWorkerGlobalScope_TestPromiseRejectionEventConstructor);
static JSC_DECLARE_CUSTOM_GETTER(jsWorkerGlobalScope_WorkerGlobalScopeConstructor);

using JSWorkerGlobalScopeDOMConstructor = JSDOMConstructorNotConstructable<JSWorkerGlobalScope>;

/* Hash table */

static const struct CompactHashIndex JSWorkerGlobalScopeTableIndex[18] = {
    { -1, -1 },
    { 0, 16 },
    { 5, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 3, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { -1, -1 },
    { 4, -1 },
    { -1, -1 },
    { 1, 17 },
    { 2, -1 },
};


static const HashTableValue JSWorkerGlobalScopeTableValues[] =
{
    { "ExposedToWorkerAndWindow", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWorkerGlobalScope_ExposedToWorkerAndWindowConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "TestDefaultToJSONFilteredByExposed", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWorkerGlobalScope_TestDefaultToJSONFilteredByExposedConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "TestNode", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWorkerGlobalScope_TestNodeConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "TestObject", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWorkerGlobalScope_TestObjectConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "TestPromiseRejectionEvent", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWorkerGlobalScope_TestPromiseRejectionEventConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
    { "WorkerGlobalScope", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWorkerGlobalScope_WorkerGlobalScopeConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
};

static const HashTable JSWorkerGlobalScopeTable = { 6, 15, true, JSWorkerGlobalScope::info(), JSWorkerGlobalScopeTableValues, JSWorkerGlobalScopeTableIndex };
template<> const ClassInfo JSWorkerGlobalScopeDOMConstructor::s_info = { "WorkerGlobalScope", &Base::s_info, nullptr, nullptr, CREATE_METHOD_TABLE(JSWorkerGlobalScopeDOMConstructor) };

template<> JSValue JSWorkerGlobalScopeDOMConstructor::prototypeForStructure(JSC::VM& vm, const JSDOMGlobalObject& globalObject)
{
    return JSEventTarget::getConstructor(vm, &globalObject);
}

template<> void JSWorkerGlobalScopeDOMConstructor::initializeProperties(VM& vm, JSDOMGlobalObject& globalObject)
{
    putDirect(vm, vm.propertyNames->length, jsNumber(0), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    JSString* nameString = jsNontrivialString(vm, "WorkerGlobalScope"_s);
    m_originalName.set(vm, this, nameString);
    putDirect(vm, vm.propertyNames->name, nameString, JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum);
    putDirect(vm, vm.propertyNames->prototype, JSWorkerGlobalScope::prototype(vm, globalObject), JSC::PropertyAttribute::ReadOnly | JSC::PropertyAttribute::DontEnum | JSC::PropertyAttribute::DontDelete);
}

/* Hash table for prototype */

static const struct CompactHashIndex JSWorkerGlobalScopePrototypeTableIndex[2] = {
    { -1, -1 },
    { 0, -1 },
};


static const HashTableValue JSWorkerGlobalScopePrototypeTableValues[] =
{
    { "constructor", static_cast<unsigned>(JSC::PropertyAttribute::DontEnum), NoIntrinsic, { (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsWorkerGlobalScopeConstructor), (intptr_t) static_cast<PutPropertySlot::PutValueFunc>(0) } },
};

static const HashTable JSWorkerGlobalScopePrototypeTable = { 1, 1, true, JSWorkerGlobalScope::info(), JSWorkerGlobalScopePrototypeTableValues, JSWorkerGlobalScopePrototypeTableIndex };
const ClassInfo JSWorkerGlobalScopePrototype::s_info = { "WorkerGlobalScope", &Base::s_info, &JSWorkerGlobalScopePrototypeTable, nullptr, CREATE_METHOD_TABLE(JSWorkerGlobalScopePrototype) };

void JSWorkerGlobalScopePrototype::finishCreation(VM& vm)
{
    Base::finishCreation(vm);
    reifyStaticProperties(vm, JSWorkerGlobalScope::info(), JSWorkerGlobalScopePrototypeTableValues, *this);
    JSC_TO_STRING_TAG_WITHOUT_TRANSITION();
}

const ClassInfo JSWorkerGlobalScope::s_info = { "WorkerGlobalScope", &Base::s_info, &JSWorkerGlobalScopeTable, nullptr, CREATE_METHOD_TABLE(JSWorkerGlobalScope) };

JSWorkerGlobalScope::JSWorkerGlobalScope(VM& vm, Structure* structure, Ref<WorkerGlobalScope>&& impl)
    : JSEventTarget(vm, structure, WTFMove(impl))
{
}

void JSWorkerGlobalScope::finishCreation(VM& vm, JSProxy* proxy)
{
    Base::finishCreation(vm, proxy);

    static_assert(!std::is_base_of<ActiveDOMObject, WorkerGlobalScope>::value, "Interface is not marked as [ActiveDOMObject] even though implementation class subclasses ActiveDOMObject.");

}

JSObject* JSWorkerGlobalScope::createPrototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return JSWorkerGlobalScopePrototype::create(vm, &globalObject, JSWorkerGlobalScopePrototype::createStructure(vm, &globalObject, JSEventTarget::prototype(vm, globalObject)));
}

JSObject* JSWorkerGlobalScope::prototype(VM& vm, JSDOMGlobalObject& globalObject)
{
    return getDOMPrototype<JSWorkerGlobalScope>(vm, globalObject);
}

JSValue JSWorkerGlobalScope::getConstructor(VM& vm, const JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSWorkerGlobalScopeDOMConstructor, DOMConstructorID::WorkerGlobalScope>(vm, *jsCast<const JSDOMGlobalObject*>(globalObject));
}

JSC_DEFINE_CUSTOM_GETTER(jsWorkerGlobalScopeConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName))
{
    VM& vm = JSC::getVM(lexicalGlobalObject);
    auto throwScope = DECLARE_THROW_SCOPE(vm);
    auto* prototype = jsDynamicCast<JSWorkerGlobalScopePrototype*>(vm, JSValue::decode(thisValue));
    if (UNLIKELY(!prototype))
        return throwVMTypeError(lexicalGlobalObject, throwScope);
    return JSValue::encode(JSWorkerGlobalScope::getConstructor(JSC::getVM(lexicalGlobalObject), prototype->globalObject()));
}

static inline JSValue jsWorkerGlobalScope_ExposedToWorkerAndWindowConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSWorkerGlobalScope& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSExposedToWorkerAndWindow::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsWorkerGlobalScope_ExposedToWorkerAndWindowConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSWorkerGlobalScope>::get<jsWorkerGlobalScope_ExposedToWorkerAndWindowConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsWorkerGlobalScope_TestDefaultToJSONFilteredByExposedConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSWorkerGlobalScope& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSTestDefaultToJSONFilteredByExposed::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsWorkerGlobalScope_TestDefaultToJSONFilteredByExposedConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSWorkerGlobalScope>::get<jsWorkerGlobalScope_TestDefaultToJSONFilteredByExposedConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsWorkerGlobalScope_TestNodeConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSWorkerGlobalScope& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSTestNode::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsWorkerGlobalScope_TestNodeConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSWorkerGlobalScope>::get<jsWorkerGlobalScope_TestNodeConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsWorkerGlobalScope_TestObjectConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSWorkerGlobalScope& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSTestObj::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsWorkerGlobalScope_TestObjectConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSWorkerGlobalScope>::get<jsWorkerGlobalScope_TestObjectConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsWorkerGlobalScope_TestPromiseRejectionEventConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSWorkerGlobalScope& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSTestPromiseRejectionEvent::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsWorkerGlobalScope_TestPromiseRejectionEventConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSWorkerGlobalScope>::get<jsWorkerGlobalScope_TestPromiseRejectionEventConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

static inline JSValue jsWorkerGlobalScope_WorkerGlobalScopeConstructorGetter(JSGlobalObject& lexicalGlobalObject, JSWorkerGlobalScope& thisObject)
{
    UNUSED_PARAM(lexicalGlobalObject);
    return JSWorkerGlobalScope::getConstructor(JSC::getVM(&lexicalGlobalObject), &thisObject);
}

JSC_DEFINE_CUSTOM_GETTER(jsWorkerGlobalScope_WorkerGlobalScopeConstructor, (JSGlobalObject* lexicalGlobalObject, EncodedJSValue thisValue, PropertyName attributeName))
{
    return IDLAttribute<JSWorkerGlobalScope>::get<jsWorkerGlobalScope_WorkerGlobalScopeConstructorGetter>(*lexicalGlobalObject, thisValue, attributeName);
}

JSC::IsoSubspace* JSWorkerGlobalScope::subspaceForImpl(JSC::VM& vm)
{
    auto& clientData = *static_cast<JSVMClientData*>(vm.clientData);
    auto& spaces = clientData.subspaces();
    if (auto* space = spaces.m_subspaceForWorkerGlobalScope.get())
        return space;
    spaces.m_subspaceForWorkerGlobalScope = makeUnique<IsoSubspace> ISO_SUBSPACE_INIT(vm.heap, clientData.m_heapCellTypeForJSWorkerGlobalScope, JSWorkerGlobalScope);
    auto* space = spaces.m_subspaceForWorkerGlobalScope.get();
IGNORE_WARNINGS_BEGIN("unreachable-code")
IGNORE_WARNINGS_BEGIN("tautological-compare")
    void (*myVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSWorkerGlobalScope::visitOutputConstraints;
    void (*jsCellVisitOutputConstraint)(JSC::JSCell*, JSC::SlotVisitor&) = JSC::JSCell::visitOutputConstraints;
    if (myVisitOutputConstraint != jsCellVisitOutputConstraint)
        clientData.outputConstraintSpaces().append(space);
IGNORE_WARNINGS_END
IGNORE_WARNINGS_END
    return space;
}

void JSWorkerGlobalScope::analyzeHeap(JSCell* cell, HeapAnalyzer& analyzer)
{
    auto* thisObject = jsCast<JSWorkerGlobalScope*>(cell);
    analyzer.setWrappedObjectForCell(cell, &thisObject->wrapped());
    if (thisObject->scriptExecutionContext())
        analyzer.setLabelForCell(cell, "url " + thisObject->scriptExecutionContext()->url().string());
    Base::analyzeHeap(cell, analyzer);
}

WorkerGlobalScope* JSWorkerGlobalScope::toWrapped(JSC::VM& vm, JSC::JSValue value)
{
    if (auto* wrapper = jsDynamicCast<JSWorkerGlobalScope*>(vm, value))
        return &wrapper->wrapped();
    return nullptr;
}

}
