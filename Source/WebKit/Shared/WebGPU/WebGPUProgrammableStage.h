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

#include "WebGPUIdentifier.h"
#include <optional>
#include <wtf/KeyValuePair.h>
#include <wtf/Ref.h>
#include <wtf/Vector.h>

namespace WebKit::WebGPU {

using PipelineConstantValue = double; // May represent WGSL’s bool, f32, i32, u32.

struct ProgrammableStage {
    WebGPUIdentifier module;
    String entryPoint;
    Vector<KeyValuePair<String, PipelineConstantValue>> constants;

    template<class Encoder> void encode(Encoder& encoder) const
    {
        encoder << module;
        encoder << entryPoint;
        encoder << constants;
    }

    template<class Decoder> static std::optional<ProgrammableStage> decode(Decoder& decoder)
    {
        std::optional<WebGPUIdentifier> module;
        decoder >> module;
        if (!module)
            return std::nullopt;

        std::optional<String> entryPoint;
        decoder >> entryPoint;
        if (!entryPoint)
            return std::nullopt;

        std::optional<Vector<KeyValuePair<String, PipelineConstantValue>>> constants;
        decoder >> constants;
        if (!constants)
            return std::nullopt;

        return { { WTFMove(*module), WTFMove(*entryPoint), WTFMove(*constants) } };
    }
};

} // namespace WebKit::WebGPU

#endif // ENABLE(GPU_PROCESS)
