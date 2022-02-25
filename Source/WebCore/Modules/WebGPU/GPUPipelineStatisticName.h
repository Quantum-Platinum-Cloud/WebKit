/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <cstdint>
#include <pal/graphics/WebGPU/WebGPUPipelineStatisticName.h>

namespace WebCore {

enum class GPUPipelineStatisticName : uint8_t {
    VertexShaderInvocations,
    ClipperInvocations,
    ClipperPrimitivesOut,
    FragmentShaderInvocations,
    ComputeShaderInvocations,
};

inline PAL::WebGPU::PipelineStatisticName convertToBacking(GPUPipelineStatisticName pipelineStatisticName)
{
    switch (pipelineStatisticName) {
    case GPUPipelineStatisticName::VertexShaderInvocations:
        return PAL::WebGPU::PipelineStatisticName::VertexShaderInvocations;
    case GPUPipelineStatisticName::ClipperInvocations:
        return PAL::WebGPU::PipelineStatisticName::ClipperInvocations;
    case GPUPipelineStatisticName::ClipperPrimitivesOut:
        return PAL::WebGPU::PipelineStatisticName::ClipperPrimitivesOut;
    case GPUPipelineStatisticName::FragmentShaderInvocations:
        return PAL::WebGPU::PipelineStatisticName::FragmentShaderInvocations;
    case GPUPipelineStatisticName::ComputeShaderInvocations:
        return PAL::WebGPU::PipelineStatisticName::ComputeShaderInvocations;
    }
    RELEASE_ASSERT_NOT_REACHED();
}

}
