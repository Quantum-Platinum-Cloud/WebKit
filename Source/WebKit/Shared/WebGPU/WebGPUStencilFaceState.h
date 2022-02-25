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

#if ENABLE(GPU_PROCESS)

#include <optional>
#include <pal/graphics/WebGPU/WebGPUCompareFunction.h>
#include <pal/graphics/WebGPU/WebGPUStencilOperation.h>

namespace WebKit::WebGPU {

struct StencilFaceState {
    PAL::WebGPU::CompareFunction compare { PAL::WebGPU::CompareFunction::Always };
    PAL::WebGPU::StencilOperation failOp { PAL::WebGPU::StencilOperation::Keep };
    PAL::WebGPU::StencilOperation depthFailOp { PAL::WebGPU::StencilOperation::Keep };
    PAL::WebGPU::StencilOperation passOp { PAL::WebGPU::StencilOperation::Keep };

    template<class Encoder> void encode(Encoder& encoder) const
    {
        encoder << compare;
        encoder << failOp;
        encoder << depthFailOp;
        encoder << passOp;
    }

    template<class Decoder> static std::optional<StencilFaceState> decode(Decoder& decoder)
    {
        std::optional<PAL::WebGPU::CompareFunction> compare;
        decoder >> compare;
        if (!compare)
            return std::nullopt;

        std::optional<PAL::WebGPU::StencilOperation> failOp;
        decoder >> failOp;
        if (!failOp)
            return std::nullopt;

        std::optional<PAL::WebGPU::StencilOperation> depthFailOp;
        decoder >> depthFailOp;
        if (!depthFailOp)
            return std::nullopt;

        std::optional<PAL::WebGPU::StencilOperation> passOp;
        decoder >> passOp;
        if (!passOp)
            return std::nullopt;

        return { { WTFMove(*compare), WTFMove(*failOp), WTFMove(*depthFailOp), WTFMove(*passOp) } };
    }
};

} // namespace WebKit::WebGPU

#endif // ENABLE(GPU_PROCESS)
