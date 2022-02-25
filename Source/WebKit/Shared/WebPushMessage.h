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

#include <optional>
#include <wtf/URL.h>
#include <wtf/Vector.h>

OBJC_CLASS NSDictionary;

namespace WebKit {

struct WebPushMessage {
    template<class Encoder> void encode(Encoder&) const;
    template<class Decoder> static std::optional<WebPushMessage> decode(Decoder&);

    Vector<uint8_t> pushData;
    URL registrationURL;

#if PLATFORM(COCOA)
    static std::optional<WebPushMessage> fromDictionary(NSDictionary *);
    NSDictionary *toDictionary() const;
#endif
};

template<class Encoder>
void WebPushMessage::encode(Encoder& encoder) const
{
    encoder << pushData << registrationURL;
}

template<class Decoder>
std::optional<WebPushMessage> WebPushMessage::decode(Decoder& decoder)
{
    std::optional<Vector<uint8_t>> pushData;
    decoder >> pushData;
    if (!pushData)
        return std::nullopt;

    std::optional<URL> registrationURL;
    decoder >> registrationURL;
    if (!registrationURL)
        return std::nullopt;

    return { {
        WTFMove(*pushData),
        WTFMove(*registrationURL)
    } };
}

} // namespace WebKit
