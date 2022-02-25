/*
 * Copyright (C) 2004, 2005, 2006, 2007 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005 Rob Buis <buis@kde.org>
 * Copyright (C) 2005 Eric Seidel <eric@webkit.org>
 * Copyright (C) 2021 Apple Inc.  All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#pragma once

#include "FilterEffectApplier.h"

namespace WebCore {

class FEComponentTransfer;
class PixelBuffer;
struct ComponentTransferFunction;

class FEComponentTransferSoftwareApplier : public FilterEffectConcreteApplier<FEComponentTransfer> {
    WTF_MAKE_FAST_ALLOCATED;
    using Base = FilterEffectConcreteApplier<FEComponentTransfer>;

public:
    using Base::Base;

    bool apply(const Filter&, const FilterImageVector& inputs, FilterImage& result) const override;

private:
    using LookupTable = std::array<uint8_t, 256>;

    static void computeIdentityTable(LookupTable&, const ComponentTransferFunction&);
    static void computeTabularTable(LookupTable&, const ComponentTransferFunction&);
    static void computeDiscreteTable(LookupTable&, const ComponentTransferFunction&);
    static void computeLinearTable(LookupTable&, const ComponentTransferFunction&);
    static void computeGammaTable(LookupTable&, const ComponentTransferFunction&);

    static LookupTable computeLookupTable(const ComponentTransferFunction&);

    void applyPlatform(PixelBuffer&) const;
};

} // namespace WebCore
