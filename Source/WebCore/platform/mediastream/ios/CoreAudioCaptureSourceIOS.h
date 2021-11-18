/*
 * Copyright (C) 2017 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)

#include "AudioSession.h"
#include "CoreAudioCaptureSource.h"
#include <wtf/WeakHashSet.h>

OBJC_CLASS WebCoreAudioCaptureSourceIOSListener;

namespace WebCore {

class CoreAudioCaptureSourceFactoryIOS final : public CoreAudioCaptureSourceFactory, public AudioSession::InterruptionObserver  {
public:
    CoreAudioCaptureSourceFactoryIOS();
    ~CoreAudioCaptureSourceFactoryIOS();

private:
    // AudioSession::InterruptionObserver.
    void beginAudioSessionInterruption() { beginInterruption(); }
    void endAudioSessionInterruption(AudioSession::MayResume) { endInterruption(); }

    CaptureSourceOrError createAudioCaptureSource(const CaptureDevice&, String&&, const MediaConstraints*) final;
    void addExtensiveObserver(ExtensiveObserver&) final;
    void removeExtensiveObserver(ExtensiveObserver&) final;

    RetainPtr<WebCoreAudioCaptureSourceIOSListener> m_listener;
    WeakHashSet<ExtensiveObserver> m_observers;
};

} // namespace WebCore

#endif // ENABLE(MEDIA_STREAM) && PLATFORM(IOS_FAMILY)