/*
 * Copyright (C) 2019 Apple Inc. All rights reserved.
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

#include "LegacyInlineTextBox.h"
#include "LegacyRootInlineBox.h"
#include "RenderText.h"
#include "TextBoxSelectableRange.h"
#include <wtf/Vector.h>

namespace WebCore {
namespace InlineIterator {

enum class CreateTextRunMode { Painting, Editing };

class BoxLegacyPath {
public:
    BoxLegacyPath(const LegacyInlineBox* inlineBox)
        : m_inlineBox(inlineBox)
    { }

    bool isText() const { return m_inlineBox->isInlineTextBox(); }
    bool isInlineBox() const { return m_inlineBox->isInlineFlowBox(); }
    bool isRootInlineBox() const { return m_inlineBox->isRootInlineBox(); }

    FloatRect rect() const { return m_inlineBox->frameRect(); }

    bool isHorizontal() const { return m_inlineBox->isHorizontal(); }
    bool isLineBreak() const { return m_inlineBox->isLineBreak(); }

    unsigned minimumCaretOffset() const { return m_inlineBox->caretMinOffset(); }
    unsigned maximumCaretOffset() const { return m_inlineBox->caretMaxOffset(); }

    unsigned char bidiLevel() const { return m_inlineBox->bidiLevel(); }

    bool hasHyphen() const { return inlineTextBox()->hasHyphen(); }
    StringView text() const { return StringView(inlineTextBox()->renderer().text()).substring(inlineTextBox()->start(), inlineTextBox()->len()); }
    unsigned start() const { return inlineTextBox()->start(); }
    unsigned end() const { return inlineTextBox()->end(); }
    unsigned length() const { return inlineTextBox()->len(); }

    TextBoxSelectableRange selectableRange() const { return inlineTextBox()->selectableRange(); }

    TextRun createTextRun(CreateTextRunMode mode) const
    {
        bool ignoreCombinedText = mode == CreateTextRunMode::Editing;
        bool ignoreHyphen = mode == CreateTextRunMode::Editing;
        return inlineTextBox()->createTextRun(ignoreCombinedText, ignoreHyphen);
    }

    const RenderObject& renderer() const
    {
        return m_inlineBox->renderer();
    }

    void traverseNextTextBox() { m_inlineBox = inlineTextBox()->nextTextBox(); }

    void traverseNextOnLine()
    {
        m_inlineBox = m_inlineBox->nextLeafOnLine();
    }

    void traversePreviousOnLine()
    {
        m_inlineBox = m_inlineBox->previousLeafOnLine();
    }

    void traverseNextInlineBox()
    {
        m_inlineBox = inlineFlowBox()->nextLineBox();
    }

    void traversePreviousInlineBox()
    {
        m_inlineBox = inlineFlowBox()->prevLineBox();
    }

    BoxLegacyPath firstLeafBoxForInlineBox() const
    {
        return { inlineFlowBox()->firstLeafDescendant() };
    }

    BoxLegacyPath lastLeafBoxForInlineBox() const
    {
        return { inlineFlowBox()->lastLeafDescendant() };
    }

    bool operator==(const BoxLegacyPath& other) const { return m_inlineBox == other.m_inlineBox; }

    bool atEnd() const { return !m_inlineBox; }

    LegacyInlineBox* legacyInlineBox() const { return const_cast<LegacyInlineBox*>(m_inlineBox); }
    const LegacyRootInlineBox& rootInlineBox() const { return m_inlineBox->root(); }

private:
    const LegacyInlineTextBox* inlineTextBox() const { return downcast<LegacyInlineTextBox>(m_inlineBox); }
    const LegacyInlineFlowBox* inlineFlowBox() const { return downcast<LegacyInlineFlowBox>(m_inlineBox); }

    const LegacyInlineBox* m_inlineBox { nullptr };
};

}
}
