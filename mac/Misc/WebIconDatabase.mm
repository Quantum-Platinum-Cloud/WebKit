/*
 * Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 Apple Inc. All rights reserved.
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
 * 3.  Neither the name of Apple Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission. 
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

#if !PLATFORM(IOS_FAMILY)

#import "WebIconDatabase.h"

#import "WebKitVersionChecks.h"
#import <JavaScriptCore/InitializeThreading.h>
#import <WebCore/Image.h>
#import <WebCore/ThreadCheck.h>
#import <wtf/MainThread.h>
#import <wtf/NeverDestroyed.h>
#import <wtf/RunLoop.h>

using namespace WebCore;

NSString *WebIconDatabaseDidAddIconNotification =          @"WebIconDatabaseDidAddIconNotification";
NSString *WebIconNotificationUserInfoURLKey =              @"WebIconNotificationUserInfoURLKey";
NSString *WebIconDatabaseDidRemoveAllIconsNotification =   @"WebIconDatabaseDidRemoveAllIconsNotification";

NSString *WebIconDatabaseDirectoryDefaultsKey = @"WebIconDatabaseDirectoryDefaultsKey";
NSString *WebIconDatabaseEnabledDefaultsKey =   @"WebIconDatabaseEnabled";

NSString *WebIconDatabasePath = @"~/Library/Icons";

NSSize WebIconSmallSize = {16, 16};
NSSize WebIconMediumSize = {32, 32};
NSSize WebIconLargeSize = {128, 128};

static const unsigned char defaultIconData[] = { 0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x03, 0x32, 0x80, 0x00, 0x20, 0x50, 0x38, 0x24, 0x16, 0x0D, 0x07, 0x84, 0x42, 0x61, 0x50, 0xB8,
    0x64, 0x08, 0x18, 0x0D, 0x0A, 0x0B, 0x84, 0xA2, 0xA1, 0xE2, 0x08, 0x5E, 0x39, 0x28, 0xAF, 0x48, 0x24, 0xD3, 0x53, 0x9A, 0x37, 0x1D, 0x18, 0x0E, 0x8A, 0x4B, 0xD1, 0x38, 
    0xB0, 0x7C, 0x82, 0x07, 0x03, 0x82, 0xA2, 0xE8, 0x6C, 0x2C, 0x03, 0x2F, 0x02, 0x82, 0x41, 0xA1, 0xE2, 0xF8, 0xC8, 0x84, 0x68, 0x6D, 0x1C, 0x11, 0x0A, 0xB7, 0xFA, 0x91, 
    0x6E, 0xD1, 0x7F, 0xAF, 0x9A, 0x4E, 0x87, 0xFB, 0x19, 0xB0, 0xEA, 0x7F, 0xA4, 0x95, 0x8C, 0xB7, 0xF9, 0xA9, 0x0A, 0xA9, 0x7F, 0x8C, 0x88, 0x66, 0x96, 0xD4, 0xCA, 0x69, 
    0x2F, 0x00, 0x81, 0x65, 0xB0, 0x29, 0x90, 0x7C, 0xBA, 0x2B, 0x21, 0x1E, 0x5C, 0xE6, 0xB4, 0xBD, 0x31, 0xB6, 0xE7, 0x7A, 0xBF, 0xDD, 0x6F, 0x37, 0xD3, 0xFD, 0xD8, 0xF2, 
    0xB6, 0xDB, 0xED, 0xAC, 0xF7, 0x03, 0xC5, 0xFE, 0x77, 0x53, 0xB6, 0x1F, 0xE6, 0x24, 0x8B, 0x1D, 0xFE, 0x26, 0x20, 0x9E, 0x1C, 0xE0, 0x80, 0x65, 0x7A, 0x18, 0x02, 0x01, 
    0x82, 0xC5, 0xA0, 0xC0, 0xF1, 0x89, 0xBA, 0x23, 0x30, 0xAD, 0x1F, 0xE7, 0xE5, 0x5B, 0x6D, 0xFE, 0xE7, 0x78, 0x3E, 0x1F, 0xEE, 0x97, 0x8B, 0xE7, 0x37, 0x9D, 0xCF, 0xE7, 
    0x92, 0x8B, 0x87, 0x0B, 0xFC, 0xA0, 0x8E, 0x68, 0x3F, 0xC6, 0x27, 0xA6, 0x33, 0xFC, 0x36, 0x5B, 0x59, 0x3F, 0xC1, 0x02, 0x63, 0x3B, 0x74, 0x00, 0x03, 0x07, 0x0B, 0x61, 
    0x00, 0x20, 0x60, 0xC9, 0x08, 0x00, 0x1C, 0x25, 0x9F, 0xE0, 0x12, 0x8A, 0xD5, 0xFE, 0x6B, 0x4F, 0x35, 0x9F, 0xED, 0xD7, 0x4B, 0xD9, 0xFE, 0x8A, 0x59, 0xB8, 0x1F, 0xEC, 
    0x56, 0xD3, 0xC1, 0xFE, 0x63, 0x4D, 0xF2, 0x83, 0xC6, 0xB6, 0x1B, 0xFC, 0x34, 0x68, 0x61, 0x3F, 0xC1, 0xA6, 0x25, 0xEB, 0xFC, 0x06, 0x58, 0x5C, 0x3F, 0xC0, 0x03, 0xE4, 
    0xC3, 0xFC, 0x04, 0x0F, 0x1A, 0x6F, 0xE0, 0xE0, 0x20, 0xF9, 0x61, 0x7A, 0x02, 0x28, 0x2B, 0xBC, 0x46, 0x25, 0xF3, 0xFC, 0x66, 0x3D, 0x99, 0x27, 0xF9, 0x7E, 0x6B, 0x1D, 
    0xC7, 0xF9, 0x2C, 0x5E, 0x1C, 0x87, 0xF8, 0xC0, 0x4D, 0x9A, 0xE7, 0xF8, 0xDA, 0x51, 0xB2, 0xC1, 0x68, 0xF2, 0x64, 0x1F, 0xE1, 0x50, 0xED, 0x0A, 0x04, 0x23, 0x79, 0x8A, 
    0x7F, 0x82, 0xA3, 0x39, 0x80, 0x7F, 0x80, 0xC2, 0xB1, 0x5E, 0xF7, 0x04, 0x2F, 0xB2, 0x10, 0x02, 0x86, 0x63, 0xC9, 0xCC, 0x07, 0xBF, 0x87, 0xF8, 0x4A, 0x38, 0xAF, 0xC1, 
    0x88, 0xF8, 0x66, 0x1F, 0xE1, 0xD9, 0x08, 0xD4, 0x8F, 0x25, 0x5B, 0x4A, 0x49, 0x97, 0x87, 0x39, 0xFE, 0x25, 0x12, 0x10, 0x68, 0xAA, 0x4A, 0x2F, 0x42, 0x29, 0x12, 0x69, 
    0x9F, 0xE1, 0xC1, 0x00, 0x67, 0x1F, 0xE1, 0x58, 0xED, 0x00, 0x83, 0x23, 0x49, 0x82, 0x7F, 0x81, 0x21, 0xE0, 0xFC, 0x73, 0x21, 0x00, 0x50, 0x7D, 0x2B, 0x84, 0x03, 0x83, 
    0xC2, 0x1B, 0x90, 0x06, 0x69, 0xFE, 0x23, 0x91, 0xAE, 0x50, 0x9A, 0x49, 0x32, 0xC2, 0x89, 0x30, 0xE9, 0x0A, 0xC4, 0xD9, 0xC4, 0x7F, 0x94, 0xA6, 0x51, 0xDE, 0x7F, 0x9D, 
    0x07, 0x89, 0xF6, 0x7F, 0x91, 0x85, 0xCA, 0x88, 0x25, 0x11, 0xEE, 0x50, 0x7C, 0x43, 0x35, 0x21, 0x60, 0xF1, 0x0D, 0x82, 0x62, 0x39, 0x07, 0x2C, 0x20, 0xE0, 0x80, 0x72, 
    0x34, 0x17, 0xA1, 0x80, 0xEE, 0xF0, 0x89, 0x24, 0x74, 0x1A, 0x2C, 0x93, 0xB3, 0x78, 0xCC, 0x52, 0x9D, 0x6A, 0x69, 0x56, 0xBB, 0x0D, 0x85, 0x69, 0xE6, 0x7F, 0x9E, 0x27, 
    0xB9, 0xFD, 0x50, 0x54, 0x47, 0xF9, 0xCC, 0x78, 0x9F, 0x87, 0xF9, 0x98, 0x70, 0xB9, 0xC2, 0x91, 0x2C, 0x6D, 0x1F, 0xE1, 0xE1, 0x00, 0xBF, 0x02, 0xC1, 0xF5, 0x18, 0x84,
    0x01, 0xE1, 0x48, 0x8C, 0x42, 0x07, 0x43, 0xC9, 0x76, 0x7F, 0x8B, 0x04, 0xE4, 0xDE, 0x35, 0x95, 0xAB, 0xB0, 0xF0, 0x5C, 0x55, 0x23, 0xF9, 0x7E, 0x7E, 0x9F, 0xE4, 0x0C, 
    0xA7, 0x55, 0x47, 0xC7, 0xF9, 0xE6, 0xCF, 0x1F, 0xE7, 0x93, 0x35, 0x52, 0x54, 0x63, 0x19, 0x46, 0x73, 0x1F, 0xE2, 0x61, 0x08, 0xF0, 0x82, 0xE1, 0x80, 0x92, 0xF9, 0x20, 
    0xC0, 0x28, 0x18, 0x0A, 0x05, 0xA1, 0xA2, 0xF8, 0x6E, 0xDB, 0x47, 0x49, 0xFE, 0x3E, 0x17, 0xB6, 0x61, 0x13, 0x1A, 0x29, 0x26, 0xA9, 0xFE, 0x7F, 0x92, 0x70, 0x69, 0xFE, 
    0x4C, 0x2F, 0x55, 0x01, 0xF1, 0x54, 0xD4, 0x35, 0x49, 0x4A, 0x69, 0x59, 0x83, 0x81, 0x58, 0x76, 0x9F, 0xE2, 0x20, 0xD6, 0x4C, 0x9B, 0xA0, 0x48, 0x1E, 0x0B, 0xB7, 0x48, 
    0x58, 0x26, 0x11, 0x06, 0x42, 0xE8, 0xA4, 0x40, 0x17, 0x27, 0x39, 0x00, 0x60, 0x2D, 0xA4, 0xC3, 0x2C, 0x7F, 0x94, 0x56, 0xE4, 0xE1, 0x77, 0x1F, 0xE5, 0xB9, 0xD7, 0x66, 
    0x1E, 0x07, 0xB3, 0x3C, 0x63, 0x1D, 0x35, 0x49, 0x0E, 0x63, 0x2D, 0xA2, 0xF1, 0x12, 0x60, 0x1C, 0xE0, 0xE0, 0x52, 0x1B, 0x8B, 0xAC, 0x38, 0x0E, 0x07, 0x03, 0x60, 0x28, 
    0x1C, 0x0E, 0x87, 0x00, 0xF0, 0x66, 0x27, 0x11, 0xA2, 0xC1, 0x02, 0x5A, 0x1C, 0xE4, 0x21, 0x83, 0x1F, 0x13, 0x86, 0xFA, 0xD2, 0x55, 0x1D, 0xD6, 0x61, 0xBC, 0x77, 0xD3, 
    0xE6, 0x91, 0xCB, 0x4C, 0x90, 0xA6, 0x25, 0xB8, 0x2F, 0x90, 0xC5, 0xA9, 0xCE, 0x12, 0x07, 0x02, 0x91, 0x1B, 0x9F, 0x68, 0x00, 0x16, 0x76, 0x0D, 0xA1, 0x00, 0x08, 0x06, 
    0x03, 0x81, 0xA0, 0x20, 0x1A, 0x0D, 0x06, 0x80, 0x30, 0x24, 0x12, 0x89, 0x20, 0x98, 0x4A, 0x1F, 0x0F, 0x21, 0xA0, 0x9E, 0x36, 0x16, 0xC2, 0x88, 0xE6, 0x48, 0x9B, 0x83, 
    0x31, 0x1C, 0x55, 0x1E, 0x43, 0x59, 0x1A, 0x56, 0x1E, 0x42, 0xF0, 0xFA, 0x4D, 0x1B, 0x9B, 0x08, 0xDC, 0x5B, 0x02, 0xA1, 0x30, 0x7E, 0x3C, 0xEE, 0x5B, 0xA6, 0xDD, 0xB8, 
    0x6D, 0x5B, 0x62, 0xB7, 0xCD, 0xF3, 0x9C, 0xEA, 0x04, 0x80, 0x80, 0x00, 0x00, 0x0E, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x01, 0x01, 
    0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x01, 0x02, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x03, 0xE0, 0x01, 0x03, 0x00, 0x03, 0x00, 0x00, 
    0x00, 0x01, 0x00, 0x05, 0x00, 0x00, 0x01, 0x06, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x01, 0x11, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
    0x00, 0x08, 0x01, 0x15, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x01, 0x16, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x01, 0x17, 
    0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x29, 0x01, 0x1A, 0x00, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0xE8, 0x01, 0x1B, 0x00, 0x05, 0x00, 0x00, 
    0x00, 0x01, 0x00, 0x00, 0x03, 0xF0, 0x01, 0x1C, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x28, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 
    0x00, 0x00, 0x01, 0x52, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x0A, 
    0xFC, 0x80, 0x00, 0x00, 0x27, 0x10, 0x00, 0x0A, 0xFC, 0x80, 0x00, 0x00, 0x27, 0x10 };

ALLOW_DEPRECATED_IMPLEMENTATIONS_BEGIN
@implementation WebIconDatabase
ALLOW_DEPRECATED_IMPLEMENTATIONS_END

+ (void)initialize
{
    JSC::initializeThreading();
    RunLoop::initializeMainRunLoop();
}

+ (WebIconDatabase *)sharedIconDatabase
{
    static WebIconDatabase *database;
    static dispatch_once_t once;
    dispatch_once(&once, ^ {
        if (linkedOnOrAfter(SDKVersion::FirstWithWebIconDatabaseWarning))
            NSLog(@"+[WebIconDatabase sharedIconDatabase] is not API and should not be used. WebIconDatabase no longer handles icon loading and it will be removed in a future release.");

        database = [[WebIconDatabase alloc] init];
    });

    return database;
}

- (id)init
{
    WebCoreThreadViolationCheckRoundOne();

    return [super init];
}

- (NSImage *)iconForURL:(NSString *)URL withSize:(NSSize)size cache:(BOOL)cache
{
    return [self defaultIconWithSize:size];
}

- (NSImage *)iconForURL:(NSString *)URL withSize:(NSSize)size
{
    return [self defaultIconWithSize:size];
}

- (NSImage *)defaultIconWithSize:(NSSize)size
{
    static NeverDestroyed<RetainPtr<NSImage>> defaultImage;

    static dispatch_once_t once;
    dispatch_once(&once, ^ {
        auto imageData = adoptNS([[NSData alloc] initWithBytes:defaultIconData length:sizeof(defaultIconData)]);
        defaultImage.get() = adoptNS([[NSImage alloc] initWithData:imageData.get()]);
    });
    
    return defaultImage.get().get();
}

- (NSImage *)defaultIconForURL:(NSString *)URL withSize:(NSSize)size
{
    return [self defaultIconWithSize:size];
}

- (NSString *)iconURLForURL:(NSString *)URL
{
    return nil;
}

- (void)retainIconForURL:(NSString *)URL
{
}

- (void)releaseIconForURL:(NSString *)pageURL
{
}

+ (void)delayDatabaseCleanup
{
}

+ (void)allowDatabaseCleanup
{
}

- (void)setDelegate:(id)delegate
{
}

- (id)delegate
{
    return nil;
}

@end

#endif // !PLATFORM(IOS_FAMILY)
