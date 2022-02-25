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

#pragma once

#include "JSDOMWrapper.h"

namespace WebCore {

class JSTestJSBuiltinConstructor : public JSDOMObject {
public:
    using Base = JSDOMObject;
    static JSTestJSBuiltinConstructor* create(JSC::Structure* structure, JSDOMGlobalObject* globalObject)
    {
        JSTestJSBuiltinConstructor* ptr = new (NotNull, JSC::allocateCell<JSTestJSBuiltinConstructor>(globalObject->vm())) JSTestJSBuiltinConstructor(structure, *globalObject);
        ptr->finishCreation(globalObject->vm());
        return ptr;
    }

    static JSC::JSObject* createPrototype(JSC::VM&, JSDOMGlobalObject&);
    static JSC::JSObject* prototype(JSC::VM&, JSDOMGlobalObject&);
    static void destroy(JSC::JSCell*);

    DECLARE_INFO;

    static JSC::Structure* createStructure(JSC::VM& vm, JSC::JSGlobalObject* globalObject, JSC::JSValue prototype)
    {
        return JSC::Structure::create(vm, globalObject, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), info(), JSC::NonArray);
    }

    static JSC::JSValue getConstructor(JSC::VM&, const JSC::JSGlobalObject*);
    template<typename, JSC::SubspaceAccess mode> static JSC::IsoSubspace* subspaceFor(JSC::VM& vm)
    {
        if constexpr (mode == JSC::SubspaceAccess::Concurrently)
            return nullptr;
        return subspaceForImpl(vm);
    }
    static JSC::IsoSubspace* subspaceForImpl(JSC::VM& vm);

    // Custom attributes
    JSC::JSValue testAttributeCustom(JSC::JSGlobalObject&) const;
    JSC::JSValue testAttributeRWCustom(JSC::JSGlobalObject&) const;
    void setTestAttributeRWCustom(JSC::JSGlobalObject&, JSC::JSValue);

    // Custom functions
    JSC::JSValue testCustomFunction(JSC::JSGlobalObject&, JSC::CallFrame&);
protected:
    JSTestJSBuiltinConstructor(JSC::Structure*, JSDOMGlobalObject&);

    void finishCreation(JSC::VM&);
};



} // namespace WebCore
