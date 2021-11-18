/*
 * Copyright (C) 2006-2020 Apple Inc. All rights reserved.
 * Copyright (C) 2007 Alp Toker <alp@atoker.com>
 * Copyright (C) 2008 Torch Mobile, Inc.
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

#include "AffineTransform.h"
#include "Color.h"
#include "FloatPoint.h"
#include "GraphicsTypes.h"
#include <wtf/Variant.h>
#include <wtf/Vector.h>

#if USE(CG)
#include <wtf/RetainPtr.h>
#endif

#if USE(DIRECT2D)
#include "COMPtr.h"
#endif

#if USE(CG)
typedef struct CGContext* CGContextRef;
typedef struct CGGradient* CGGradientRef;
#endif

#if USE(DIRECT2D)
interface ID2D1Brush;
interface ID2D1RenderTarget;
#endif

#if USE(CAIRO)
typedef struct _cairo_pattern cairo_pattern_t;
#endif

namespace WebCore {

class FloatRect;
class GraphicsContext;

class Gradient : public RefCounted<Gradient> {
public:
    struct ColorStop {
        float offset { 0 };
        Color color;

        template<typename Encoder> void encode(Encoder&) const;
        template<typename Decoder> static std::optional<ColorStop> decode(Decoder&);
    };

    using ColorStopVector = Vector<ColorStop, 2>;

    struct LinearData {
        FloatPoint point0;
        FloatPoint point1;

        template<typename Encoder> void encode(Encoder&) const;
        template<typename Decoder> static std::optional<LinearData> decode(Decoder&);
    };

    struct RadialData {
        FloatPoint point0;
        FloatPoint point1;
        float startRadius;
        float endRadius;
        float aspectRatio; // For elliptical gradient, width / height.

        template<typename Encoder> void encode(Encoder&) const;
        template<typename Decoder> static std::optional<RadialData> decode(Decoder&);
    };

    struct ConicData {
        FloatPoint point0;
        float angleRadians;

        template<typename Encoder> void encode(Encoder&) const;
        template<typename Decoder> static std::optional<ConicData> decode(Decoder&);
    };

    using Data = Variant<LinearData, RadialData, ConicData>;

    WEBCORE_EXPORT static Ref<Gradient> create(Data&&);

    bool isZeroSize() const;

    const Data& data() const { return m_data; }

    WEBCORE_EXPORT void addColorStop(ColorStop&&);
    WEBCORE_EXPORT void setSortedColorStops(ColorStopVector&&);

    const ColorStopVector& stops() const { return m_stops; }

    WEBCORE_EXPORT void setSpreadMethod(GradientSpreadMethod);
    GradientSpreadMethod spreadMethod() const { return m_spreadMethod; }

    void fill(GraphicsContext&, const FloatRect&);
    void adjustParametersForTiledDrawing(FloatSize&, FloatRect&, const FloatSize& spacing);

    unsigned hash() const;

#if USE(CAIRO)
    RefPtr<cairo_pattern_t> createPattern(float globalAlpha, const AffineTransform&);
#endif

#if USE(CG)
    void paint(GraphicsContext&);
    void paint(CGContextRef);
#endif

#if USE(DIRECT2D)
    ID2D1Brush* createBrush(ID2D1RenderTarget*);
#endif

    template<typename Encoder> void encode(Encoder&) const;
    template<typename Decoder> static std::optional<Ref<Gradient>> decode(Decoder&);

private:
    explicit Gradient(Data&&);

    void sortStops() const;
    void stopsChanged();

#if USE(CG)
    void createCGGradient();
#endif

    Data m_data;
    mutable ColorStopVector m_stops;
    mutable bool m_stopsSorted { false };
    GradientSpreadMethod m_spreadMethod { GradientSpreadMethod::Pad };
    mutable unsigned m_cachedHash { 0 };

#if USE(CG)
    RetainPtr<CGGradientRef> m_gradient;
#endif

#if USE(DIRECT2D)
    COMPtr<ID2D1Brush> m_brush;
#endif
};

template<typename Encoder> void Gradient::ColorStop::encode(Encoder& encoder) const
{
    encoder << offset;
    encoder << color;
}

template<typename Decoder> std::optional<Gradient::ColorStop> Gradient::ColorStop::decode(Decoder& decoder)
{
    std::optional<float> offset;
    decoder >> offset;
    if (!offset)
        return std::nullopt;

    std::optional<Color> color;
    decoder >> color;
    if (!color)
        return std::nullopt;

    return {{ *offset, *color }};
}

template<typename Encoder> void Gradient::LinearData::encode(Encoder& encoder) const
{
    encoder << point0;
    encoder << point1;
}

template<typename Decoder> std::optional<Gradient::LinearData> Gradient::LinearData::decode(Decoder& decoder)
{
    std::optional<FloatPoint> point0;
    decoder >> point0;
    if (!point0)
        return std::nullopt;

    std::optional<FloatPoint> point1;
    decoder >> point1;
    if (!point1)
        return std::nullopt;

    return {{ *point0, *point1 }};
}

template<typename Encoder> void Gradient::RadialData::encode(Encoder& encoder) const
{
    encoder << point0;
    encoder << point1;
    encoder << startRadius;
    encoder << endRadius;
    encoder << aspectRatio;
}

template<typename Decoder> std::optional<Gradient::RadialData> Gradient::RadialData::decode(Decoder& decoder)
{
    std::optional<FloatPoint> point0;
    decoder >> point0;
    if (!point0)
        return std::nullopt;

    std::optional<FloatPoint> point1;
    decoder >> point1;
    if (!point1)
        return std::nullopt;

    std::optional<float> startRadius;
    decoder >> startRadius;
    if (!startRadius)
        return std::nullopt;

    std::optional<float> endRadius;
    decoder >> endRadius;
    if (!endRadius)
        return std::nullopt;

    std::optional<float> aspectRatio;
    decoder >> aspectRatio;
    if (!aspectRatio)
        return std::nullopt;

    return {{ *point0, *point1, *startRadius, *endRadius, *aspectRatio }};
}

template<typename Encoder> void Gradient::ConicData::encode(Encoder& encoder) const
{
    encoder << point0;
    encoder << angleRadians;
}

template<typename Decoder> std::optional<Gradient::ConicData> Gradient::ConicData::decode(Decoder& decoder)
{
    std::optional<FloatPoint> point0;
    decoder >> point0;
    if (!point0)
        return std::nullopt;

    std::optional<float> angleRadians;
    decoder >> angleRadians;
    if (!angleRadians)
        return std::nullopt;

    return {{ *point0, *angleRadians }};
}

template<typename Encoder> void Gradient::encode(Encoder& encoder) const
{
    encoder << m_data;
    encoder << m_stops;
    encoder << m_stopsSorted;
    encoder << m_spreadMethod;
}

template<typename Decoder> std::optional<Ref<Gradient>> Gradient::decode(Decoder& decoder)
{
    std::optional<Data> data;
    decoder >> data;
    if (!data)
        return std::nullopt;
    auto gradient = Gradient::create(WTFMove(*data));

    std::optional<ColorStopVector> stops;
    decoder >> stops;
    if (!stops)
        return std::nullopt;
    std::optional<bool> stopsSorted;
    decoder >> stopsSorted;
    if (!stopsSorted.has_value())
        return std::nullopt;
    if (*stopsSorted)
        gradient->setSortedColorStops(WTFMove(*stops));
    else {
        for (auto& stop : *stops)
            gradient->addColorStop(WTFMove(stop));
    }

    GradientSpreadMethod spreadMethod;
    if (!decoder.decode(spreadMethod))
        return std::nullopt;
    gradient->setSpreadMethod(spreadMethod);

    return gradient;
}

} // namespace WebCore
