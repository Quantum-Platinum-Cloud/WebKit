/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "HasSelectorFilter.h"
#include "SelectorFilter.h"
#include <wtf/HashMap.h>

namespace WebCore::Style {

using HasPseudoClassCacheKey = std::pair<const Element*, const CSSSelector*>;
using HasPseudoClassFilterKey = std::pair<const Element*, uint8_t>;

enum class HasPseudoClassMatch : uint8_t { None, Matches, Fails, FailsSubtree };

struct SelectorMatchingState {
    SelectorFilter selectorFilter;

    HashMap<HasPseudoClassCacheKey, HasPseudoClassMatch> hasPseudoClassMatchCache;
    HashMap<HasPseudoClassFilterKey, std::unique_ptr<HasSelectorFilter>> hasPseudoClassSelectorFilters;
};

inline HasPseudoClassCacheKey makeHasPseudoClassCacheKey(const Element& element, const CSSSelector& selector)
{
    return { &element, &selector };
}

inline HasPseudoClassFilterKey makeHasPseudoClassFilterKey(const Element& element, HasSelectorFilter::Type type)
{
    return { &element, static_cast<uint8_t>(type) };
}

}
