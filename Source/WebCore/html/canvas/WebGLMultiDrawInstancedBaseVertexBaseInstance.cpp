/*
 * Copyright 2022 The Chromium Authors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"

#if ENABLE(WEBGL)
#include "WebGLMultiDrawInstancedBaseVertexBaseInstance.h"

#include "InspectorInstrumentation.h"

#include <wtf/IsoMallocInlines.h>

namespace WebCore {

WTF_MAKE_ISO_ALLOCATED_IMPL(WebGLMultiDrawInstancedBaseVertexBaseInstance);

WebGLMultiDrawInstancedBaseVertexBaseInstance::WebGLMultiDrawInstancedBaseVertexBaseInstance(WebGLRenderingContextBase& context)
    : WebGLExtension(context)
{
    context.graphicsContextGL()->ensureExtensionEnabled("GL_ANGLE_base_vertex_base_instance"_s);

    // Spec requires WEBGL_multi_draw to be turned on implicitly here.
    // Enable it both in the backend and in WebKit.
    context.getExtension("WEBGL_multi_draw"_s);
}

WebGLMultiDrawInstancedBaseVertexBaseInstance::~WebGLMultiDrawInstancedBaseVertexBaseInstance() = default;

WebGLExtension::ExtensionName WebGLMultiDrawInstancedBaseVertexBaseInstance::getName() const
{
    return WebGLMultiDrawInstancedBaseVertexBaseInstanceName;
}

bool WebGLMultiDrawInstancedBaseVertexBaseInstance::supported(GraphicsContextGL& context)
{
    return context.supportsExtension("GL_ANGLE_base_vertex_base_instance"_s)
        && context.supportsExtension("GL_ANGLE_multi_draw"_s);
}

void WebGLMultiDrawInstancedBaseVertexBaseInstance::multiDrawArraysInstancedBaseInstanceWEBGL(GCGLenum mode, Int32List&& firstsList, GCGLuint firstsOffset, Int32List&& countsList, GCGLuint countsOffset, Int32List&& instanceCountsList, GCGLuint instanceCountsOffset, Uint32List&& baseInstancesList, GCGLuint baseInstancesOffset, GCGLsizei drawcount)
{
    if (!m_context || m_context->isContextLost())
        return;

    if (!validateDrawcount("multiDrawArraysInstancedBaseInstanceWEBGL", drawcount)
        || !validateOffset("multiDrawArraysInstancedBaseInstanceWEBGL", "firstsOffset out of bounds", firstsList.length(), firstsOffset, drawcount)
        || !validateOffset("multiDrawArraysInstancedBaseInstanceWEBGL", "countsOffset out of bounds", countsList.length(), countsOffset, drawcount)
        || !validateOffset("multiDrawArraysInstancedBaseInstanceWEBGL", "instanceCountsOffset out of bounds", instanceCountsList.length(), instanceCountsOffset, drawcount)
        || !validateOffset("multiDrawArraysInstancedBaseInstanceWEBGL", "baseInstancesOffset out of bounds", baseInstancesList.length(), baseInstancesOffset, drawcount)) {
        return;
    }

    if (!m_context->validateVertexArrayObject("multiDrawArraysInstancedBaseInstanceWEBGL"))
        return;

    if (m_context->m_currentProgram && InspectorInstrumentation::isWebGLProgramDisabled(*m_context, *m_context->m_currentProgram))
        return;

    m_context->clearIfComposited(WebGLRenderingContextBase::CallerTypeDrawOrClear);

    {
        InspectorScopedShaderProgramHighlight scopedHighlight(*m_context, m_context->m_currentProgram.get());

        m_context->graphicsContextGL()->multiDrawArraysInstancedBaseInstanceANGLE(mode, GCGLSpanTuple { firstsList.data() +  firstsOffset, countsList.data() + countsOffset, instanceCountsList.data() + instanceCountsOffset, baseInstancesList.data() + baseInstancesOffset, static_cast<size_t>(drawcount) });
    }

    m_context->markContextChangedAndNotifyCanvasObserver();
}

void WebGLMultiDrawInstancedBaseVertexBaseInstance::multiDrawElementsInstancedBaseVertexBaseInstanceWEBGL(GCGLenum mode, Int32List&& countsList, GCGLuint countsOffset, GCGLenum type, Int32List&& offsetsList, GCGLuint offsetsOffset, Int32List&& instanceCountsList, GCGLuint instanceCountsOffset, Int32List&& baseVerticesList, GCGLuint baseVerticesOffset, Uint32List&& baseInstancesList, GCGLuint baseInstancesOffset, GCGLsizei drawcount)
{
    if (!m_context || m_context->isContextLost())
        return;

    if (!validateDrawcount("multiDrawElementsInstancedBaseVertexBaseInstanceWEBGL", drawcount)
        || !validateOffset("multiDrawElementsInstancedBaseVertexBaseInstanceWEBGL", "countsOffset out of bounds", countsList.length(), countsOffset, drawcount)
        || !validateOffset("multiDrawElementsInstancedBaseVertexBaseInstanceWEBGL", "offsetsOffset out of bounds", offsetsList.length(), offsetsOffset, drawcount)
        || !validateOffset("multiDrawElementsInstancedBaseVertexBaseInstanceWEBGL", "instanceCountsOffset out of bounds", instanceCountsList.length(), instanceCountsOffset, drawcount)
        || !validateOffset("multiDrawElementsInstancedBaseVertexBaseInstanceWEBGL", "baseVerticesOffset out of bounds", baseVerticesList.length(), baseVerticesOffset, drawcount)
        || !validateOffset("multiDrawElementsInstancedBaseVertexBaseInstanceWEBGL", "baseInstancesOffset out of bounds", baseInstancesList.length(), baseInstancesOffset, drawcount)) {
        return;
    }

    if (!m_context->validateVertexArrayObject("multiDrawElementsInstancedBaseVertexBaseInstanceWEBGL"))
        return;

    if (m_context->m_currentProgram && InspectorInstrumentation::isWebGLProgramDisabled(*m_context, *m_context->m_currentProgram))
        return;

    m_context->clearIfComposited(WebGLRenderingContextBase::CallerTypeDrawOrClear);

    {
        InspectorScopedShaderProgramHighlight scopedHighlight(*m_context, m_context->m_currentProgram.get());

        m_context->graphicsContextGL()->multiDrawElementsInstancedBaseVertexBaseInstanceANGLE(mode, GCGLSpanTuple { countsList.data() + countsOffset, offsetsList.data() + offsetsOffset, instanceCountsList.data() + instanceCountsOffset, baseVerticesList.data() + baseVerticesOffset, baseInstancesList.data() + baseInstancesOffset, static_cast<size_t>(drawcount) }, type);
    }

    m_context->markContextChangedAndNotifyCanvasObserver();
}

bool WebGLMultiDrawInstancedBaseVertexBaseInstance::validateDrawcount(const char* functionName, GCGLsizei drawcount)
{
    if (drawcount < 0) {
        m_context->synthesizeGLError(GraphicsContextGL::INVALID_VALUE, functionName, "negative drawcount");
        return false;
    }

    return true;
}

bool WebGLMultiDrawInstancedBaseVertexBaseInstance::validateOffset(const char* functionName, const char* outOfBoundsDescription, GCGLsizei size, GCGLuint offset, GCGLsizei drawcount)
{
    if (drawcount > size) {
        m_context->synthesizeGLError(GraphicsContextGL::INVALID_OPERATION, functionName, "drawcount out of bounds");
        return false;
    }

    if (offset > static_cast<GCGLuint>(size - drawcount)) {
        m_context->synthesizeGLError(GraphicsContextGL::INVALID_OPERATION, functionName, outOfBoundsDescription);
        return false;
    }

    return true;
}

} // namespace WebCore

#endif // ENABLE(WEBGL)
