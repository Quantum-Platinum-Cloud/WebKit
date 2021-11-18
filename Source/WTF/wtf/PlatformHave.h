/*
 * Copyright (C) 2006-2021 Apple Inc. All rights reserved.
 * Copyright (C) 2007-2009 Torch Mobile, Inc.
 * Copyright (C) 2010, 2011 Research In Motion Limited. All rights reserved.
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

#ifndef WTF_PLATFORM_GUARD_AGAINST_INDIRECT_INCLUSION
#error "Please #include <wtf/Platform.h> instead of this file directly."
#endif


/* HAVE() - specific system features (headers, functions or similar) that are present or not */
#define HAVE(WTF_FEATURE) (defined HAVE_##WTF_FEATURE && HAVE_##WTF_FEATURE)


#if defined(HAVE_FEATURES_H) && HAVE_FEATURES_H
/* If the included features.h is glibc's one, __GLIBC__ is defined. */
#include <features.h>
#endif


#if CPU(ARM_NEON)
/* All NEON intrinsics usage can be disabled by this macro. */
#define HAVE_ARM_NEON_INTRINSICS 1
#endif

/* FIXME: This should be renamed to WTF_CPU_ARM_IDIV_INSTRUCTIONS and moved to CPU.h */
#if defined(__ARM_ARCH_EXT_IDIV__) || CPU(APPLE_ARMV7S)
#define HAVE_ARM_IDIV_INSTRUCTIONS 1
#endif

#if PLATFORM(COCOA)
#define HAVE_OUT_OF_PROCESS_LAYER_HOSTING 1
#endif

#if PLATFORM(COCOA)
#define HAVE_REMAP_JIT 1
#endif

#if PLATFORM(MAC)
#define HAVE_SEC_KEYCHAIN 1
#endif

#if PLATFORM(MAC)
#define HAVE_HISERVICES 1
#endif

#if PLATFORM(IOS_FAMILY)
#define HAVE_READLINE 1
#endif

#if PLATFORM(IOS_FAMILY) && CPU(ARM_NEON)
#undef HAVE_ARM_NEON_INTRINSICS
#define HAVE_ARM_NEON_INTRINSICS 0
#endif

#if !defined(HAVE_VISIBILITY_PROPAGATION_VIEW) && PLATFORM(IOS_FAMILY)
#define HAVE_VISIBILITY_PROPAGATION_VIEW 1
#endif

#if !defined(HAVE_AVSTREAMSESSION) && PLATFORM(MAC)
#define HAVE_AVSTREAMSESSION 1
#endif

#if !defined(USE_UIKIT_KEYBOARD_ADDITIONS) && (PLATFORM(IOS) || PLATFORM(MACCATALYST))
#define USE_UIKIT_KEYBOARD_ADDITIONS 1
#endif

#if !defined(HAVE_ACCESSIBILITY) && (PLATFORM(COCOA) || PLATFORM(WIN) || PLATFORM(GTK) || PLATFORM(WPE))
#define HAVE_ACCESSIBILITY 1
#endif

#if !defined(HAVE_TIMINGSAFE_BCMP) && (PLATFORM(COCOA) || OS(OPENBSD) || OS(FREEBSD))
#define HAVE_TIMINGSAFE_BCMP 1
#endif

#if !defined(HAVE_STD_FILESYSTEM)
#if __has_include(<filesystem>)
#define HAVE_STD_FILESYSTEM 1
#else
#define HAVE_STD_FILESYSTEM 0
#endif
#endif

#if !defined(HAVE_STD_EXPERIMENTAL_FILESYSTEM)
#if __has_include(<experimental/filesystem>)
#define STD_EXPERIMENTAL_FILESYSTEM 1
#else
#define STD_EXPERIMENTAL_FILESYSTEM 0
#endif
#endif

/* FIXME: Remove after CMake build enabled on Darwin */
#if OS(DARWIN)
#define HAVE_ERRNO_H 1
#endif

#if OS(DARWIN)
#define HAVE_LANGINFO_H 1
#endif

#if OS(DARWIN)
#define HAVE_LOCALTIME_R 1
#endif

#if OS(DARWIN)
#define HAVE_MMAP 1
#endif

#if OS(DARWIN)
#define HAVE_REGEX_H 1
#endif

#if OS(DARWIN)
#define HAVE_SIGNAL_H 1
#endif

#if OS(DARWIN)
#define HAVE_STAT_BIRTHTIME 1
#endif

#if OS(DARWIN)
#define HAVE_STRNSTR 1
#endif

#if OS(DARWIN)
#define HAVE_SYS_PARAM_H 1
#endif

#if OS(DARWIN)
#define HAVE_SYS_TIME_H 1
#endif

#if OS(DARWIN)
#define HAVE_TM_GMTOFF 1
#endif

#if OS(DARWIN)
#define HAVE_TM_ZONE 1
#endif

#if OS(DARWIN)
#define HAVE_TIMEGM 1
#endif

#if OS(DARWIN)
#define HAVE_PTHREAD_MAIN_NP 1
#endif

#if OS(DARWIN) && (CPU(X86_64) || CPU(ARM64))
#define HAVE_INT128_T 1
#endif

#if OS(UNIX) && !OS(FUCHSIA)
#define HAVE_RESOURCE_H 1
#endif

#if OS(UNIX) && !OS(FUCHSIA)
#define HAVE_PTHREAD_SETSCHEDPARAM 1
#endif

#if OS(DARWIN)
#define HAVE_DISPATCH_H 1
#endif

#if OS(DARWIN)
#define HAVE_MADV_FREE 1
#endif

#if OS(DARWIN)
#define HAVE_MADV_FREE_REUSE 1
#endif

#if OS(DARWIN)
#define HAVE_MADV_DONTNEED 1
#endif

#if OS(DARWIN)
#define HAVE_PTHREAD_SETNAME_NP 1
#endif

#if OS(DARWIN)
#define HAVE_READLINE 1
#endif

#if OS(DARWIN)
#define HAVE_SYS_TIMEB_H 1
#endif

#if OS(DARWIN)
#define HAVE_AUDIT_TOKEN 1
#endif

#if OS(DARWIN) && __has_include(<mach/mach_exc.defs>) && !PLATFORM(GTK)
#define HAVE_MACH_EXCEPTIONS 1
#endif

#if OS(DARWIN) && __has_include(<mach/memory_entry.h>)
#define HAVE_MACH_MEMORY_ENTRY 1
#endif

#if PLATFORM(MAC)
#define HAVE_HOSTED_CORE_ANIMATION 1
#endif

#if OS(DARWIN) || OS(FUCHSIA) || ((OS(FREEBSD) || OS(LINUX)) && (CPU(X86) || CPU(X86_64) || CPU(ARM) || CPU(ARM64) || CPU(MIPS)))
#define HAVE_MACHINE_CONTEXT 1
#endif

#if OS(DARWIN) || (OS(LINUX) && defined(__GLIBC__) && !defined(__UCLIBC__) && !CPU(MIPS))
#define HAVE_BACKTRACE 1
#endif

#if (OS(DARWIN) || OS(LINUX)) && (PLATFORM(GTK) || PLATFORM(WPE)) && defined(__GLIBC__) && !defined(__UCLIBC__) && !CPU(MIPS)
#define HAVE_BACKTRACE_SYMBOLS 1
#endif

#if OS(DARWIN) || OS(LINUX)
#define HAVE_DLADDR 1
#endif

#if __has_include(<System/pthread_machdep.h>)
#define HAVE_FAST_TLS 1
#endif

#if COMPILER(GCC_COMPATIBLE)
#define HAVE_COMPUTED_GOTO 1
#endif

#if CPU(ARM64E) && OS(DARWIN)
#define HAVE_FJCVTZS_INSTRUCTION 1
#endif

#if PLATFORM(IOS) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
#define HAVE_APP_LINKS 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
#define HAVE_CELESTIAL 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000
#define HAVE_FIG_PHOTO_DECOMPRESSION_SET_HARDWARE_CUTOFF 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
#define HAVE_CORE_ANIMATION_RENDER_SERVER 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST) && !PLATFORM(APPLETV)
#define HAVE_PARENTAL_CONTROLS_WITH_UNBLOCK_HANDLER 1
#endif

#if PLATFORM(COCOA) && (!PLATFORM(APPLETV) && (!PLATFORM(WATCHOS) || !PLATFORM(IOS_FAMILY_SIMULATOR) || __WATCH_OS_VERSION_MIN_REQUIRED >= 70000))
#define HAVE_PARENTAL_CONTROLS 1
#endif

#if PLATFORM(COCOA) && !PLATFORM(APPLETV)
#define HAVE_AVKIT 1
#endif

#if PLATFORM(COCOA)
#define HAVE_MEDIA_ACCESSIBILITY_FRAMEWORK 1
#endif

#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
#define HAVE_APPLE_GRAPHICS_CONTROL 1
#endif

#if PLATFORM(MAC) || PLATFORM(MACCATALYST)
#define HAVE_NSCURSOR 1
#endif

#if !defined(HAVE_QOS_CLASSES) && PLATFORM(COCOA)
#define HAVE_QOS_CLASSES 1
#endif

#if PLATFORM(COCOA)
#define HAVE_AVASSETREADER 1
#endif

#if PLATFORM(COCOA)
#define HAVE_IOSURFACE 1
#endif

#if PLATFORM(MAC)
#define HAVE_CVDISPLAYLINK 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(IOS_FAMILY_SIMULATOR)
#define HAVE_IOSURFACE_COREIMAGE_SUPPORT 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(IOS_FAMILY_SIMULATOR) && !PLATFORM(MACCATALYST)
#define HAVE_IOSURFACE_ACCELERATOR 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) \
    || (((PLATFORM(IOS) && !PLATFORM(IOS_FAMILY_SIMULATOR)) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130000) \
    || (PLATFORM(WATCHOS) && !PLATFORM(IOS_FAMILY_SIMULATOR) && __WATCH_OS_VERSION_MIN_REQUIRED >= 60000) \
    || (PLATFORM(APPLETV) && !PLATFORM(IOS_FAMILY_SIMULATOR) && __TV_OS_VERSION_MIN_REQUIRED >= 130000)
#define HAVE_IOSURFACE_SET_OWNERSHIP 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) \
    || (((PLATFORM(IOS) && !PLATFORM(IOS_FAMILY_SIMULATOR)) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000) \
    || (PLATFORM(WATCHOS) && !PLATFORM(IOS_FAMILY_SIMULATOR) && __WATCH_OS_VERSION_MIN_REQUIRED >= 80000) \
    || (PLATFORM(APPLETV) && !PLATFORM(IOS_FAMILY_SIMULATOR) && __TV_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_IOSURFACE_SET_OWNERSHIP_IDENTITY 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 80000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_NETWORK_CONNECTION_PRIVACY_STANCE 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 110300) \
    || (((PLATFORM(IOS) && !PLATFORM(IOS_FAMILY_SIMULATOR)) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 140500) \
    || (PLATFORM(WATCHOS) && !PLATFORM(IOS_FAMILY_SIMULATOR) && __WATCH_OS_VERSION_MAX_ALLOWED >= 70500) \
    || (PLATFORM(APPLETV) && !PLATFORM(IOS_FAMILY_SIMULATOR) && __TV_OS_VERSION_MAX_ALLOWED >= 140500)
#define HAVE_TASK_IDENTITY_TOKEN 1
#endif

#if PLATFORM(MAC)
#define HAVE_NS_ACTIVITY 1
#endif

#if PLATFORM(COCOA)
#define HAVE_SEC_TRUST_SERIALIZATION 1
#endif

#if PLATFORM(MAC)
#define HAVE_TOUCH_BAR 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define HAVE_HSTS_STORAGE_PATH 1
#endif

#if PLATFORM(MAC) || PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_URL_FORMATTING 1
#endif

#if !OS(WINDOWS)
#define HAVE_STACK_BOUNDS_FOR_NEW_THREAD 1
#endif

#if !OS(WINDOWS) && !PLATFORM(PLAYSTATION)
#define HAVE_MEMMEM 1
#endif

#if PLATFORM(MAC) || PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_AVCONTENTKEYSESSION 1
#endif

#if PLATFORM(MAC) || PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_SEC_KEY_PROXY 1
#endif

/* FIXME: Should this be enabled for IOS_FAMILY, not just IOS? */
#if PLATFORM(MAC) || PLATFORM(IOS)
#define HAVE_FOUNDATION_WITH_SAME_SITE_COOKIE_SUPPORT 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED < 101400
#define HAVE_NSHTTPCOOKIESTORAGE__INITWITHIDENTIFIER_WITH_INACCURATE_NULLABILITY 1
#endif

#if PLATFORM(MAC) || PLATFORM(IOS) || PLATFORM(MACCATALYST) || PLATFORM(GTK) || PLATFORM(WPE)
#define HAVE_OS_DARK_MODE_SUPPORT 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 110000
#define HAVE_CG_FONT_RENDERING_GET_FONT_SMOOTHING_DISABLED 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500
#define HAVE_READ_ONLY_SYSTEM_VOLUME 1
#endif

#ifdef __APPLE__
#define HAVE_FUNC_USLEEP 1
#endif

#if PLATFORM(COCOA)
#define HAVE_SEC_ACCESS_CONTROL 1
#endif

#if PLATFORM(IOS)
/* FIXME: SafariServices.framework exists on macOS. It is only used by WebKit on iOS, so the behavior is correct, but the name is misleading. */
#define HAVE_SAFARI_SERVICES_FRAMEWORK 1
#endif

#if PLATFORM(MAC) || PLATFORM(IOS) || PLATFORM(WATCHOS) || PLATFORM(MACCATALYST)
#define HAVE_SAFE_BROWSING 1
#endif

#if PLATFORM(IOS) || (PLATFORM(MACCATALYST) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_LINK_PREVIEW 1
#endif

#if (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(MACCATALYST) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_ACCESSIBILITY_BUNDLES_PATH 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && !(__MAC_OS_X_VERSION_MIN_REQUIRED >= 101400 && __MAC_OS_X_VERSION_MAX_ALLOWED >= 101404))
#define HAVE_CFNETWORK_OVERRIDE_SESSION_COOKIE_ACCEPT_POLICY 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define HAVE_CFNETWORK_NSURLSESSION_STRICTRUSTEVALUATE 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_CFNETWORK_NSURLSESSION_CONNECTION_CACHE_LIMITS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || PLATFORM(IOS_FAMILY)
#define HAVE_CFNETWORK_NEGOTIATED_SSL_PROTOCOL_CIPHER 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130000) || PLATFORM(MACCATALYST) || PLATFORM(WATCHOS) || PLATFORM(APPLETV)
#define HAVE_CFNETWORK_SAMESITE_COOKIE_API 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 60000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 130000)
#define HAVE_CFNETWORK_METRICS_CONNECTION_PROPERTIES 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 110300
#define HAVE_SAFARI_FOR_WEBKIT_DEVELOPMENT_REQUIRING_EXTRA_SYMBOLS 1
#endif

#if PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED < 140000
#define HAVE_BROKEN_DOWNLOAD_RESUME_UNLINK 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_CFNETWORK_METRICS_APIS_V4 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_CFNETWORK_ALTERNATIVE_SERVICE 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500
#define HAVE_CSCHECKFIXDISABLE 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define HAVE_MDNS_FAST_REGISTRATION 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define HAVE_CTFONTCREATEFORCHARACTERSWITHLANGUAGEANDOPTION 1
#endif

#if PLATFORM(IOS)
#define HAVE_ARKIT_QUICK_LOOK_PREVIEW_ITEM 1
#endif

#if PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_UI_WK_DOCUMENT_CONTEXT 1
#endif

#if (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130400)
#define HAVE_UI_POINTER_INTERACTION 1
#endif

#if (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130400) || PLATFORM(WATCHOS) || PLATFORM(APPLETV)
#define HAVE_UI_GESTURE_RECOGNIZER_MODIFIER_FLAGS 1
#endif

#if (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130400) || PLATFORM(MACCATALYST)
#define HAVE_UIKIT_WITH_MOUSE_SUPPORT 1
#define HAVE_UI_PARALLAX_TRANSITION_GESTURE_RECOGNIZER 1
#endif

#if PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130400
#define HAVE_MOUSE_DEVICE_OBSERVATION 1
#endif

#if (PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000
#define HAVE_UI_HOVER_EVENT_RESPONDABLE 1
#endif

#if PLATFORM(MACCATALYST)
#define HAVE_LOOKUP_GESTURE_RECOGNIZER 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || PLATFORM(IOS_FAMILY)
#define HAVE_ALLOWS_SENSITIVE_LOGGING 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || PLATFORM(IOS_FAMILY)
#define HAVE_FAIRPLAYSTREAMING_CENC_INITDATA 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
#define HAVE_APP_LINKS_WITH_ISENABLED 1
#endif

#if PLATFORM(IOS)
#define HAVE_ROUTE_SHARING_POLICY_LONG_FORM_VIDEO 1
#endif

#if PLATFORM(IOS) && !PLATFORM(IOS_SIMULATOR)
#define HAVE_DEVICE_MANAGEMENT 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_NSURLSESSION_WEBSOCKET 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_NWPARAMETERS_TRACKER_API 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500) && !PLATFORM(MACCATALYST)
#define HAVE_AVPLAYER_RESOURCE_CONSERVATION_LEVEL 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_AVPLAYER_SUPRESSES_AUDIO_RENDERING 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED < 101404)
#define HAVE_VIDEO_PERFORMANCE_METRICS 1
#endif

#if PLATFORM(COCOA) && !PLATFORM(MACCATALYST)
#define HAVE_CORETEXT_AUTO_OPTICAL_SIZING 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500)
#define HAVE_NSFONT_WITH_OPTICAL_SIZING_BUG 1
#endif

#if (PLATFORM(IOS) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500))
#define HAVE_APP_SSO 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500)
#define HAVE_TLS_PROTOCOL_VERSION_T 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500
#define HAVE_SUBVIEWS_IVAR_SPI 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED < 101500
#define HAVE_SUBVIEWS_IVAR_DECLARED_BY_SDK 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 101500
#define HAVE_AX_CLIENT_TYPE 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500) && !PLATFORM(MACCATALYST)
#define HAVE_DESIGN_SYSTEM_UI_FONTS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_COOKIE_CHANGE_LISTENER_API 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || PLATFORM(IOS_FAMILY)
#define HAVE_DATA_PROTECTION_KEYCHAIN 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || (PLATFORM(IOS_FAMILY) && !PLATFORM(IOS_FAMILY_SIMULATOR))
#define HAVE_NEAR_FIELD 1
#endif

#if PLATFORM(COCOA)
#define HAVE_OS_SIGNPOST 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130000)
#define HAVE_AVASSETWRITERDELEGATE 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_AVASSETWRITERDELEGATE_API 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000
#define HAVE_AVPLAYER_VIDEORANGEOVERRIDE 1
#endif

#if PLATFORM(COCOA) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define HAVE_CG_PATH_UNEVEN_CORNERS_ROUNDEDRECT 1
#endif

#if PLATFORM(WATCHOS) || PLATFORM(APPLETV) || (PLATFORM(IOS_FAMILY) && !(defined __has_include && __has_include(<CoreFoundation/CFPriv.h>)))
#define HAVE_NSPROGRESS_PUBLISHING_SPI 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130000)
#define HAVE_GCEXTENDEDGAMEPAD_BUTTONS_OPTIONS_MENU 1
#endif

#if PLATFORM(COCOA)
#define HAVE_GCEXTENDEDGAMEPAD_BUTTONS_THUMBSTICK 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
#define HAVE_MULTIGAMEPADPROVIDER_SUPPORT 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
#define HAVE_HID_FRAMEWORK 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_GCEXTENDEDGAMEPAD_HOME_BUTTON 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000)
#define HAVE_GCCONTROLLER_HID_DEVICE_CHECK 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_INCREMENTAL_PDF_APIS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_ALTERNATE_ICONS 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000
#define HAVE_LARGE_CONTROL_SIZE 1
#endif

#if (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_UICONTEXTMENU_LOCATION 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) \
    || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000) \
    || PLATFORM(WIN)
#define HAVE_SYSTEM_FEATURE_FLAGS 1
#endif

#if PLATFORM(IOS)
#define HAVE_AVOBSERVATIONCONTROLLER 1
#endif

// FIXME: Should this be enabled on other iOS-family platforms?
#if PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_CANCEL_WEB_TOUCH_EVENTS_GESTURE 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_DD_HIGHLIGHT_CREATE_WITH_SCALE 1
#endif

#if PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 130400
#define HAVE_UISCENE_BASED_VIEW_SERVICE_STATE_NOTIFICATIONS 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(IOS_FAMILY_SIMULATOR) && !PLATFORM(MACCATALYST)
#define HAVE_IOS_JIT_RESTRICTIONS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_AVAUDIO_ROUTING_ARBITER 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(MACCATALYST) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_MEDIA_USAGE_FRAMEWORK 1
#endif

#if PLATFORM(IOS) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
#define HAVE_PASSKIT_BOUND_INTERFACE_IDENTIFIER 1
#endif

#if PLATFORM(IOS) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
#define HAVE_PASSKIT_INSTALLMENTS 1
#endif

#if PLATFORM(IOS) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
#define HAVE_PASSKIT_PAYMENT_METHOD_BILLING_ADDRESS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_PASSKIT_RECURRING_SUMMARY_ITEM 1
#define HAVE_PASSKIT_DEFERRED_SUMMARY_ITEM 1
#define HAVE_PASSKIT_SHIPPING_METHOD_DATE_COMPONENTS_RANGE 1
#define HAVE_PASSKIT_COUPON_CODE 1
#define HAVE_PASSKIT_SHIPPING_CONTACT_EDITING_MODE 1
#define HAVE_PASSKIT_UPDATE_SHIPPING_METHODS_WHEN_CHANGING_SUMMARY_ITEMS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500) || PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_QUICKLOOK_THUMBNAILING 1
#endif

#if PLATFORM(IOS) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_DISPLAY_LAYER_BIPLANAR_SUPPORT 1
#endif

#if PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000
#define HAVE_NONDESTRUCTIVE_IMAGE_PASTE_SUPPORT_QUERY 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_LOGGING_PRIVACY_LEVEL 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
#define HAVE_FRONTBOARD_SYSTEM_APP_SERVICES 1
#endif

#if OS(DARWIN) && CPU(X86_64) && ((PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) || (PLATFORM(MACCATALYST) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000))
#define HAVE_CPU_TRANSLATION_CAPABILITY 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000
#define HAVE_APP_ACCENT_COLORS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_AVROUTEPICKERVIEW 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_NSTABLEVIEWSTYLE 1
#endif

#if PLATFORM(MAC)
#define HAVE_AUDIO_OUTPUT_DEVICE_UNIQUE_ID 1
#endif

#if ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_UIKEYBOARDIMPL_SMARTINSERTDELETE_CLASS_METHOD 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_CF_PREFS_SET_READ_ONLY 1
#define HAVE_CFNETWORK_CNAME_AND_COOKIE_TRANSFORM_SPI 1
#define HAVE_CGIMAGESOURCE_WITH_ACCURATE_LOOP_COUNT 1
#define HAVE_CGIMAGESOURCE_WITH_SET_ALLOWABLE_TYPES 1
#define HAVE_HSTS_STORAGE 1
#define HAVE_LSDATABASECONTEXT 1
#define HAVE_PRECONNECT_PING 1
#define HAVE_WEBP 1
#define HAVE_IMAGEIO_FIX_FOR_RADAR_59589723 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_CTFONTISSYSTEMUIFONT 1
#endif

#if PLATFORM(COCOA) && !(PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED < 101500)
#define HAVE_CTFONTGETPHYSICALSYMBOLICTRAITS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_CTFONTDESCRIPTOR_CREATE_WITH_TEXT_STYLE_AND_ATTRIBUTES 1
#endif

#if ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 80000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_RUNNINGBOARD_WEBKIT_PRIORITY_SUPPORT 1
#endif

// FIXME: This should include PLATFORM(MACCATALYST) but our internal bots have not updated enough yet.
// Try again when they do.  See rdar://problem/73940814
#if PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000
#define HAVE_UI_EVENT_ATTRIBUTION 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 80000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_NETWORK_LOADER 1
#define HAVE_SEC_TRUST_COPY_CERTIFICATE_CHAIN 1
#endif

#if PLATFORM(MACCATALYST) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000
#define HAVE_CATALYST_USER_INTERFACE_IDIOM_AND_SCALE_FACTOR 1
#endif

#if (PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000
#define HAVE_PENCILKIT_TEXT_INPUT 1
#endif

#if PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000
#define HAVE_STYLUS_DEVICE_OBSERVATION 1
#endif

#if (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000 || PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#if !defined(HAVE_APPLE_ATTESTATION)
#define HAVE_APPLE_ATTESTATION 1
#endif
#endif

#if (PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140300
#if !defined(HAVE_AVSPEECHSYNTHESIS_SYSTEMVOICE)
#define HAVE_AVSPEECHSYNTHESIS_SYSTEMVOICE 1
#endif
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000
#if !defined(HAVE_SPEECHSYNTHESIS_MONTEREY_SPI)
#define HAVE_SPEECHSYNTHESIS_MONTEREY_SPI 1
#endif
#endif

#if PLATFORM(COCOA)
#if !defined(HAVE_CG_CONTEXT_DRAW_PATH_DIRECT)
#define HAVE_CG_CONTEXT_DRAW_PATH_DIRECT 1
#endif
#endif

#if PLATFORM(COCOA) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define HAVE_CONTACTSUI 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define HAVE_CNCONTACTPICKERVIEWCONTROLLER 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_AVOUTPUTDEVICE_SPATIALAUDIO 1
#endif

#if PLATFORM(IOS) || PLATFORM(MACCATALYST) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101500)
#define HAVE_SPEECHRECOGNIZER 1
#endif

#if PLATFORM(IOS) || PLATFORM(MACCATALYST) || PLATFORM(MAC)
#define HAVE_AVCAPTUREDEVICE 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED > 110000 && defined __has_include && __has_include(<CoreFoundation/CFPriv.h>)
#define HAVE_SANDBOX_MESSAGE_FILTERING 1
#endif

#if (PLATFORM(IOS) && !PLATFORM(IOS_FAMILY_SIMULATOR)) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_COREVIDEO_COMPRESSED_PIXEL_FORMAT_TYPES 1
#endif

#if PLATFORM(IOS_FAMILY)
#define HAVE_APPLE_LOW_POWER_MODE_SUPPORT 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 110200) \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 140400) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MAX_ALLOWED >= 70300) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MAX_ALLOWED >= 140400)
#define HAVE_LIBXSLT_FIX_FOR_RADAR_71864140 1
#endif

#if (PLATFORM(IOS) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 140400)
#define HAVE_ASC_AUTH_UI 1
#endif

#if PLATFORM(MAC)
#if !defined(HAVE_MT_PLUGIN_FORMAT_READER)
#define HAVE_MT_PLUGIN_FORMAT_READER 1
#endif
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 110300
#if !defined(HAVE_MT_PLUGIN_SAMPLE_CURSOR_PLAYABLE_HORIZON)
#define HAVE_MT_PLUGIN_SAMPLE_CURSOR_PLAYABLE_HORIZON 1
#endif
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 110200) \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 140400)
#define HAVE_AVCONTENTKEYREQUEST_PENDING_PROTECTION_STATUS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000)
#if !defined(HAVE_CORE_ANIMATION_SEPARATED_LAYERS)
#define HAVE_CORE_ANIMATION_SEPARATED_LAYERS 1
#define HAVE_CORE_ANIMATION_SEPARATED_PORTALS 1
#endif
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 80000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_LEVEL_3_SYSTEM_FONT_WIDTH_VALUES 1
#elif (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_LEVEL_2_SYSTEM_FONT_WIDTH_VALUES 1
#endif

#if __has_include(<AVFoundation/AVPlayerInterstitialEventController.h>)
#if !defined(HAVE_AVFOUNDATION_INTERSTITIAL_EVENTS)
#define HAVE_AVFOUNDATION_INTERSTITIAL_EVENTS 1
#endif
#endif

#if PLATFORM(WATCHOS)
#define HAVE_PEPPER_UI_CORE 1
#endif

#if PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 80000
#define HAVE_QUICKBOARD_CONTROLLER 1
#define HAVE_PUIC_BUTTON_TYPE_PILL 1
#endif

#if PLATFORM(COCOA)
#define HAVE_CORE_GRAPHICS_ADOBE_RGB_1998_COLOR_SPACE 1
#define HAVE_CORE_GRAPHICS_DISPLAY_P3_COLOR_SPACE 1
#define HAVE_CORE_GRAPHICS_EXTENDED_SRGB_COLOR_SPACE 1
#define HAVE_CORE_GRAPHICS_ITUR_2020_COLOR_SPACE 1
#define HAVE_CORE_GRAPHICS_LINEAR_SRGB_COLOR_SPACE 1
#define HAVE_CORE_GRAPHICS_ROMMRGB_COLOR_SPACE 1
#define HAVE_CORE_GRAPHICS_XYZ_COLOR_SPACE 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000
#define HAVE_STATIC_FONT_REGISTRY 1
#define HAVE_DATA_DETECTORS_MAC_ACTION 1
#define HAVE_NSSCROLLVIEW_SEPARATOR_TRACKING_ADAPTER 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_RSA_BSSA 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV)
#define HAVE_PASTEBOARD_ITEM_PROVIDERS 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(WATCHOS) && !PLATFORM(APPLETV) && !PLATFORM(MACCATALYST)
#define HAVE_PASTEBOARD_PRESENTATION_STYLE_AND_TEAM_DATA 1
#endif

#if PLATFORM(IOS_FAMILY) && !PLATFORM(MACCATALYST)
#define HAVE_NSURL_TITLE 1
#endif

#if PLATFORM(MAC) || PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_PDFKIT 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000 && __MAC_OS_X_VERSION_MAX_ALLOWED >= 110300) \
    || (PLATFORM(IOS_FAMILY) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 140500) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MAX_ALLOWED >= 140500) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MAX_ALLOWED >= 70400)
#define HAVE_VM_FLAGS_PERMANENT 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101600) \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000)
#define HAVE_VIDEO_RESTRICTED_DECODING 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 80000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 150000)
#define HAVE_CFNETWORK_NSURLSESSION_ATTRIBUTED_BUNDLE_IDENTIFIER 1
#define HAVE_AUDIO_OBJECT_PROPERTY_ELEMENT_MAIN 1
#define HAVE_IMAGE_RESTRICTED_DECODING 1
#endif

#if defined __has_include && __has_include(<AssetViewer/ASVInlinePreview.h>)
#if (PLATFORM(IOS) || PLATFORM(MACCATALYST)) && !PLATFORM(IOS_SIMULATOR) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000
#define HAVE_ARKIT_INLINE_PREVIEW_IOS 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000
#define HAVE_ARKIT_INLINE_PREVIEW_MAC 1
#endif

#if defined(HAVE_ARKIT_INLINE_PREVIEW_IOS) || defined(HAVE_ARKIT_INLINE_PREVIEW_MAC)
#define HAVE_ARKIT_INLINE_PREVIEW 1
#endif
#endif

#if PLATFORM(IOS) || PLATFORM(MACCATALYST) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_NSURLPROTOCOL_WITH_SKIPAPPSSO 1
#endif

#if (PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000
#define HAVE_UICONTEXTMENU_STYLE_CUSTOM_PRESENTATION 1
#define HAVE_UIDATEPICKER_INSETS 1
#define HAVE_UIMENUOPTIONS_SINGLE_SELECTION 1
#endif

#if (((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000) \
    || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000))
#define HAVE_UPDATE_WEB_ACCESSIBILITY_SETTINGS 1
#endif

#if PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_UIBLUREFFECT_STYLE_SYSTEM_MATERIAL 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000 \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MIN_REQUIRED >= 70000) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MIN_REQUIRED >= 140000) \
    || (PLATFORM(MACCATALYST) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 140000))
#define HAVE_CORE_TEXT_SBIX_IMAGE_SIZE_FUNCTIONS 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000) \
    || ((PLATFORM(IOS) || PLATFORM(MACCATALYST)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000)
#if !defined(HAVE_VK_IMAGE_ANALYSIS)
#define HAVE_VK_IMAGE_ANALYSIS 1
#endif
#endif

#if PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000
#if !defined(HAVE_VK_IMAGE_ANALYSIS_FOR_MACHINE_READABLE_CODES)
#define HAVE_VK_IMAGE_ANALYSIS_FOR_MACHINE_READABLE_CODES 1
#endif
#endif

#if PLATFORM(IOS) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000
#define HAVE_PER_APP_ACCESSIBILITY_PREFERENCES 1
#endif

#if (PLATFORM(IOS_FAMILY) && !PLATFORM(IOS_FAMILY_SIMULATOR)) || PLATFORM(MACCATALYST) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 110000)
#define HAVE_PAC_SHARED_REGION_ID 1
#endif

#if !defined(HAVE_QUICKLOOK_PREVIEW_ITEM_DATA_PROVIDER) \
    && (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000)
#define HAVE_QUICKLOOK_PREVIEW_ITEM_DATA_PROVIDER 1
#define HAVE_QUICKLOOK_ITEM_PREVIEW_OPTIONS 1
#define HAVE_QUICKLOOK_PREVIEW_ACTIVITY 1
#endif

// FIXME: Replace the __has_include check with a version check once internal bots are updated (webkit.org/b/227298).
#if PLATFORM(IOS_FAMILY) && defined __has_include && __has_include(<UIKit/_UIDatePickerOverlayPresentation.h>)
#define HAVE_UIDATEPICKER_OVERLAY_PRESENTATION 1
#endif

#if PLATFORM(IOS) || PLATFORM(MACCATALYST)
#define HAVE_UITOOLBAR_STANDARD_APPEARANCE 1
#endif

#if !PLATFORM(IOS_FAMILY_SIMULATOR) && !PLATFORM(WATCHOS)
#define HAVE_SYMPTOMS_FRAMEWORK 1
#endif

#if !defined(HAVE_GROUP_ACTIVITIES) && PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000
#define HAVE_GROUP_ACTIVITIES 1
#endif

#if PLATFORM(IOS_FAMILY) || (PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000)
#define HAVE_WEBGL_COMPATIBLE_METAL 1
#endif

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 120000
#define HAVE_CMPHOTO_TILE_DECODER_AVAILABLE 1
#endif

#if (PLATFORM(MAC) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 110300 \
    || (PLATFORM(IOS) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 140500) \
    || (PLATFORM(WATCHOS) && __WATCH_OS_VERSION_MAX_ALLOWED >= 70400) \
    || (PLATFORM(APPLETV) && __TV_OS_VERSION_MAX_ALLOWED >= 140500) \
    || (PLATFORM(MACCATALYST) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 140500))
#define HAVE_AVSAMPLEBUFFERRENDERSYNCHRONIZER_RATEATHOSTTIME 1
#endif

#if (PLATFORM(IOS) && !PLATFORM(IOS_FAMILY_SIMULATOR)) && __IPHONE_OS_VERSION_MIN_REQUIRED >= 150000
#define HAVE_SYSTEM_STATUS 1
#endif
