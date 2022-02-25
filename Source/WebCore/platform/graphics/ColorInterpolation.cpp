/*
 * Copyright (C) 2021 Apple Inc. All rights reserved.
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
#include "ColorInterpolation.h"

namespace WebCore {

std::pair<float, float> fixupHueComponentsPriorToInterpolation(HueInterpolationMethod method, float component1, float component2)
{
    auto normalizeAnglesUsingShorterAlgorithm = [] (auto theta1, auto theta2) -> std::pair<float, float> {
        // https://drafts.csswg.org/css-color-4/#hue-shorter
        auto difference = theta2 - theta1;
        if (difference > 180.0)
            return { theta1 + 360.0, theta2 };
        if (difference < -180.0)
            return { theta1, theta2 + 360.0 };
        return { theta1, theta2 };
    };

    auto normalizeAnglesUsingLongerAlgorithm = [] (auto theta1, auto theta2) -> std::pair<float, float> {
        // https://drafts.csswg.org/css-color-4/#hue-longer
        auto difference = theta2 - theta1;
        if (difference > 0.0 && difference < 180.0)
            return { theta1 + 360.0, theta2 };
        if (difference > -180.0 && difference < 0)
            return { theta1, theta2 + 360.0 };
        return { theta1, theta2 };
    };

    auto normalizeAnglesUsingIncreasingAlgorithm = [] (auto theta1, auto theta2) -> std::pair<float, float> {
        // https://drafts.csswg.org/css-color-4/#hue-increasing
        if (theta2 < theta1)
            return { theta1, theta2 + 360.0 };
        return { theta1, theta2 };
    };

    auto normalizeAnglesUsingDecreasingAlgorithm = [] (auto theta1, auto theta2) -> std::pair<float, float> {
        // https://drafts.csswg.org/css-color-4/#hue-decreasing
        if (theta1 < theta2)
            return { theta1 + 360.0, theta2 };
        return { theta1, theta2 };
    };

    auto normalizeAnglesUsingSpecifiedAlgorithm = [] (auto theta1, auto theta2) -> std::pair<float, float> {
        // https://drafts.csswg.org/css-color-4/#hue-specified
        return { theta1, theta2 };
    };

    switch (method) {
    case HueInterpolationMethod::Shorter:
        return normalizeAnglesUsingShorterAlgorithm(component1, component2);
    case HueInterpolationMethod::Longer:
        return normalizeAnglesUsingLongerAlgorithm(component1, component2);
    case HueInterpolationMethod::Increasing:
        return normalizeAnglesUsingIncreasingAlgorithm(component1, component2);
    case HueInterpolationMethod::Decreasing:
        return normalizeAnglesUsingDecreasingAlgorithm(component1, component2);
    case HueInterpolationMethod::Specified:
        return normalizeAnglesUsingSpecifiedAlgorithm(component1, component2);
    }
}

}
