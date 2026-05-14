//
// Created by Codex on 2026/05/15.
//

#include "sk_paragraph_style.h"

#include "include/core/SkString.h"
#include "modules/skparagraph/include/ParagraphStyle.h"

#include "../handles/static_sk_font_style-internal.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace {

using skia::textlayout::ParagraphStyle;
using skia::textlayout::StrutStyle;
using skia::textlayout::TextAlign;
using skia::textlayout::TextDirection;
using skia::textlayout::TextHeightBehavior;
using skia::textlayout::TextStyle;

StrutStyle *as_strut_style(reskia_paragraph_strut_style_t *style) {
    return reinterpret_cast<StrutStyle *>(style);
}

const StrutStyle *as_strut_style(const reskia_paragraph_strut_style_t *style) {
    return reinterpret_cast<const StrutStyle *>(style);
}

ParagraphStyle *as_paragraph_style(reskia_paragraph_style_t *style) {
    return reinterpret_cast<ParagraphStyle *>(style);
}

const ParagraphStyle *as_paragraph_style(const reskia_paragraph_style_t *style) {
    return reinterpret_cast<const ParagraphStyle *>(style);
}

const TextStyle *as_text_style(const reskia_paragraph_text_style_t *style) {
    return reinterpret_cast<const TextStyle *>(style);
}

bool valid_text_align(reskia_paragraph_text_align_t align) {
    return align >= RESKIA_PARAGRAPH_TEXT_ALIGN_LEFT && align <= RESKIA_PARAGRAPH_TEXT_ALIGN_END;
}

bool valid_text_direction(reskia_paragraph_text_direction_t direction) {
    return direction == RESKIA_PARAGRAPH_TEXT_DIRECTION_RTL ||
           direction == RESKIA_PARAGRAPH_TEXT_DIRECTION_LTR;
}

bool valid_text_height_behavior(reskia_paragraph_text_height_behavior_t behavior) {
    return behavior >= RESKIA_PARAGRAPH_TEXT_HEIGHT_ALL &&
           behavior <= RESKIA_PARAGRAPH_TEXT_HEIGHT_DISABLE_ALL;
}

TextAlign as_text_align(reskia_paragraph_text_align_t align) {
    return static_cast<TextAlign>(align);
}

reskia_paragraph_text_align_t from_text_align(TextAlign align) {
    return static_cast<reskia_paragraph_text_align_t>(align);
}

TextDirection as_text_direction(reskia_paragraph_text_direction_t direction) {
    return static_cast<TextDirection>(direction);
}

reskia_paragraph_text_direction_t from_text_direction(TextDirection direction) {
    return static_cast<reskia_paragraph_text_direction_t>(direction);
}

std::vector<SkString> make_strings(const char *values[], int32_t values_count) {
    std::vector<SkString> strings;
    strings.reserve(static_cast<size_t>(values_count));
    for (int32_t i = 0; i < values_count; ++i) {
        if (values[i] != nullptr) {
            strings.emplace_back(values[i]);
        }
    }
    return strings;
}

SkFontStyle font_style_or_normal(sk_font_style_t font_style) {
    if (font_style == 0) {
        return SkFontStyle();
    }
    return static_sk_font_style_get_entity(font_style);
}

}  // namespace

extern "C" {

reskia_paragraph_strut_style_t *SkParagraph_StrutStyle_new(void) {
    return reinterpret_cast<reskia_paragraph_strut_style_t *>(new StrutStyle());
}

reskia_paragraph_strut_style_t *StrutStyle_new(void) {
    return SkParagraph_StrutStyle_new();
}

void SkParagraph_StrutStyle_delete(reskia_paragraph_strut_style_t *style) {
    delete as_strut_style(style);
}

reskia_paragraph_strut_style_t *SkParagraph_StrutStyle_copy(const reskia_paragraph_strut_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_strut_style_t *>(new StrutStyle(*as_strut_style(style)));
}

bool SkParagraph_StrutStyle_equals(const reskia_paragraph_strut_style_t *style, const reskia_paragraph_strut_style_t *other) {
    return style != nullptr && other != nullptr && *as_strut_style(style) == *as_strut_style(other);
}

size_t SkParagraph_StrutStyle_getFontFamiliesCount(const reskia_paragraph_strut_style_t *style) {
    if (style == nullptr) {
        return 0;
    }
    return as_strut_style(style)->getFontFamilies().size();
}

reskia_string_t *SkParagraph_StrutStyle_getFontFamilyAt(const reskia_paragraph_strut_style_t *style, size_t index) {
    if (style == nullptr || index >= as_strut_style(style)->getFontFamilies().size()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(as_strut_style(style)->getFontFamilies()[index]));
}

bool SkParagraph_StrutStyle_setFontFamilies(reskia_paragraph_strut_style_t *style, const char *families[], int32_t families_count) {
    if (style == nullptr || families_count < 0 || (families_count > 0 && families == nullptr)) {
        return false;
    }
    as_strut_style(style)->setFontFamilies(make_strings(families, families_count));
    return true;
}

sk_font_style_t SkParagraph_StrutStyle_getFontStyle(const reskia_paragraph_strut_style_t *style) {
    if (style == nullptr) {
        return 0;
    }
    return static_sk_font_style_make(as_strut_style(style)->getFontStyle());
}

bool SkParagraph_StrutStyle_setFontStyle(reskia_paragraph_strut_style_t *style, sk_font_style_t font_style) {
    if (style == nullptr) {
        return false;
    }
    as_strut_style(style)->setFontStyle(font_style_or_normal(font_style));
    return true;
}

float SkParagraph_StrutStyle_getFontSize(const reskia_paragraph_strut_style_t *style) {
    return style == nullptr ? 0.0f : as_strut_style(style)->getFontSize();
}

void SkParagraph_StrutStyle_setFontSize(reskia_paragraph_strut_style_t *style, float size) {
    if (style != nullptr) {
        as_strut_style(style)->setFontSize(size);
    }
}

float SkParagraph_StrutStyle_getHeight(const reskia_paragraph_strut_style_t *style) {
    return style == nullptr ? 0.0f : as_strut_style(style)->getHeight();
}

void SkParagraph_StrutStyle_setHeight(reskia_paragraph_strut_style_t *style, float height) {
    if (style != nullptr) {
        as_strut_style(style)->setHeight(height);
    }
}

float SkParagraph_StrutStyle_getLeading(const reskia_paragraph_strut_style_t *style) {
    return style == nullptr ? 0.0f : as_strut_style(style)->getLeading();
}

void SkParagraph_StrutStyle_setLeading(reskia_paragraph_strut_style_t *style, float leading) {
    if (style != nullptr) {
        as_strut_style(style)->setLeading(leading);
    }
}

bool SkParagraph_StrutStyle_getStrutEnabled(const reskia_paragraph_strut_style_t *style) {
    return style != nullptr && as_strut_style(style)->getStrutEnabled();
}

void SkParagraph_StrutStyle_setStrutEnabled(reskia_paragraph_strut_style_t *style, bool enabled) {
    if (style != nullptr) {
        as_strut_style(style)->setStrutEnabled(enabled);
    }
}

bool SkParagraph_StrutStyle_getForceStrutHeight(const reskia_paragraph_strut_style_t *style) {
    return style != nullptr && as_strut_style(style)->getForceStrutHeight();
}

void SkParagraph_StrutStyle_setForceStrutHeight(reskia_paragraph_strut_style_t *style, bool force) {
    if (style != nullptr) {
        as_strut_style(style)->setForceStrutHeight(force);
    }
}

bool SkParagraph_StrutStyle_getHeightOverride(const reskia_paragraph_strut_style_t *style) {
    return style != nullptr && as_strut_style(style)->getHeightOverride();
}

void SkParagraph_StrutStyle_setHeightOverride(reskia_paragraph_strut_style_t *style, bool override_height) {
    if (style != nullptr) {
        as_strut_style(style)->setHeightOverride(override_height);
    }
}

bool SkParagraph_StrutStyle_getHalfLeading(const reskia_paragraph_strut_style_t *style) {
    return style != nullptr && as_strut_style(style)->getHalfLeading();
}

void SkParagraph_StrutStyle_setHalfLeading(reskia_paragraph_strut_style_t *style, bool half_leading) {
    if (style != nullptr) {
        as_strut_style(style)->setHalfLeading(half_leading);
    }
}

reskia_paragraph_style_t *SkParagraph_ParagraphStyle_new(void) {
    return reinterpret_cast<reskia_paragraph_style_t *>(new ParagraphStyle());
}

reskia_paragraph_style_t *ParagraphStyle_new(void) {
    return SkParagraph_ParagraphStyle_new();
}

void SkParagraph_ParagraphStyle_delete(reskia_paragraph_style_t *style) {
    delete as_paragraph_style(style);
}

reskia_paragraph_style_t *SkParagraph_ParagraphStyle_copy(const reskia_paragraph_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_style_t *>(new ParagraphStyle(*as_paragraph_style(style)));
}

bool SkParagraph_ParagraphStyle_equals(const reskia_paragraph_style_t *style, const reskia_paragraph_style_t *other) {
    return style != nullptr && other != nullptr && *as_paragraph_style(style) == *as_paragraph_style(other);
}

reskia_paragraph_strut_style_t *SkParagraph_ParagraphStyle_getStrutStyle(const reskia_paragraph_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_strut_style_t *>(new StrutStyle(as_paragraph_style(style)->getStrutStyle()));
}

bool SkParagraph_ParagraphStyle_setStrutStyle(reskia_paragraph_style_t *style, const reskia_paragraph_strut_style_t *strut_style) {
    if (style == nullptr || strut_style == nullptr) {
        return false;
    }
    as_paragraph_style(style)->setStrutStyle(*as_strut_style(strut_style));
    return true;
}

reskia_paragraph_text_style_t *SkParagraph_ParagraphStyle_getTextStyle(const reskia_paragraph_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_text_style_t *>(new TextStyle(as_paragraph_style(style)->getTextStyle()));
}

bool SkParagraph_ParagraphStyle_setTextStyle(reskia_paragraph_style_t *style, const reskia_paragraph_text_style_t *text_style) {
    if (style == nullptr || text_style == nullptr) {
        return false;
    }
    as_paragraph_style(style)->setTextStyle(*as_text_style(text_style));
    return true;
}

reskia_paragraph_text_direction_t SkParagraph_ParagraphStyle_getTextDirection(const reskia_paragraph_style_t *style) {
    return style == nullptr ? RESKIA_PARAGRAPH_TEXT_DIRECTION_LTR : from_text_direction(as_paragraph_style(style)->getTextDirection());
}

bool SkParagraph_ParagraphStyle_setTextDirection(reskia_paragraph_style_t *style, reskia_paragraph_text_direction_t direction) {
    if (style == nullptr || !valid_text_direction(direction)) {
        return false;
    }
    as_paragraph_style(style)->setTextDirection(as_text_direction(direction));
    return true;
}

reskia_paragraph_text_align_t SkParagraph_ParagraphStyle_getTextAlign(const reskia_paragraph_style_t *style) {
    return style == nullptr ? RESKIA_PARAGRAPH_TEXT_ALIGN_START : from_text_align(as_paragraph_style(style)->getTextAlign());
}

bool SkParagraph_ParagraphStyle_setTextAlign(reskia_paragraph_style_t *style, reskia_paragraph_text_align_t align) {
    if (style == nullptr || !valid_text_align(align)) {
        return false;
    }
    as_paragraph_style(style)->setTextAlign(as_text_align(align));
    return true;
}

size_t SkParagraph_ParagraphStyle_getMaxLines(const reskia_paragraph_style_t *style) {
    return style == nullptr ? 0 : as_paragraph_style(style)->getMaxLines();
}

void SkParagraph_ParagraphStyle_setMaxLines(reskia_paragraph_style_t *style, size_t max_lines) {
    if (style != nullptr) {
        as_paragraph_style(style)->setMaxLines(max_lines);
    }
}

reskia_string_t *SkParagraph_ParagraphStyle_getEllipsis(const reskia_paragraph_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(as_paragraph_style(style)->getEllipsis()));
}

int32_t SkParagraph_ParagraphStyle_getEllipsisUtf16(const reskia_paragraph_style_t *style, uint16_t *dst, int32_t dst_units) {
    if (style == nullptr || dst_units < 0) {
        return -1;
    }
    const auto ellipsis = as_paragraph_style(style)->getEllipsisUtf16();
    if (dst != nullptr && dst_units > 0) {
        const int32_t copy_count = std::min<int32_t>(dst_units, static_cast<int32_t>(ellipsis.size()));
        std::copy_n(reinterpret_cast<const uint16_t *>(ellipsis.data()), copy_count, dst);
    }
    return static_cast<int32_t>(ellipsis.size());
}

bool SkParagraph_ParagraphStyle_setEllipsis(reskia_paragraph_style_t *style, const char *ellipsis) {
    if (style == nullptr || ellipsis == nullptr) {
        return false;
    }
    as_paragraph_style(style)->setEllipsis(SkString(ellipsis));
    return true;
}

bool SkParagraph_ParagraphStyle_setEllipsisUtf16(reskia_paragraph_style_t *style, const uint16_t *ellipsis, int32_t units) {
    if (style == nullptr || units < 0 || (ellipsis == nullptr && units != 0)) {
        return false;
    }
    if (units == 0) {
        as_paragraph_style(style)->setEllipsis(std::u16string());
        return true;
    }
    as_paragraph_style(style)->setEllipsis(std::u16string(reinterpret_cast<const char16_t *>(ellipsis), static_cast<size_t>(units)));
    return true;
}

float SkParagraph_ParagraphStyle_getHeight(const reskia_paragraph_style_t *style) {
    return style == nullptr ? 0.0f : as_paragraph_style(style)->getHeight();
}

void SkParagraph_ParagraphStyle_setHeight(reskia_paragraph_style_t *style, float height) {
    if (style != nullptr) {
        as_paragraph_style(style)->setHeight(height);
    }
}

reskia_paragraph_text_height_behavior_t SkParagraph_ParagraphStyle_getTextHeightBehavior(const reskia_paragraph_style_t *style) {
    return style == nullptr ? RESKIA_PARAGRAPH_TEXT_HEIGHT_ALL : static_cast<reskia_paragraph_text_height_behavior_t>(as_paragraph_style(style)->getTextHeightBehavior());
}

bool SkParagraph_ParagraphStyle_setTextHeightBehavior(reskia_paragraph_style_t *style, reskia_paragraph_text_height_behavior_t behavior) {
    if (style == nullptr || !valid_text_height_behavior(behavior)) {
        return false;
    }
    as_paragraph_style(style)->setTextHeightBehavior(static_cast<TextHeightBehavior>(behavior));
    return true;
}

bool SkParagraph_ParagraphStyle_unlimited_lines(const reskia_paragraph_style_t *style) {
    return style != nullptr && as_paragraph_style(style)->unlimited_lines();
}

bool SkParagraph_ParagraphStyle_ellipsized(const reskia_paragraph_style_t *style) {
    return style != nullptr && as_paragraph_style(style)->ellipsized();
}

reskia_paragraph_text_align_t SkParagraph_ParagraphStyle_effective_align(const reskia_paragraph_style_t *style) {
    return style == nullptr ? RESKIA_PARAGRAPH_TEXT_ALIGN_START : from_text_align(as_paragraph_style(style)->effective_align());
}

bool SkParagraph_ParagraphStyle_hintingIsOn(const reskia_paragraph_style_t *style) {
    return style != nullptr && as_paragraph_style(style)->hintingIsOn();
}

void SkParagraph_ParagraphStyle_turnHintingOff(reskia_paragraph_style_t *style) {
    if (style != nullptr) {
        as_paragraph_style(style)->turnHintingOff();
    }
}

bool SkParagraph_ParagraphStyle_getReplaceTabCharacters(const reskia_paragraph_style_t *style) {
    return style != nullptr && as_paragraph_style(style)->getReplaceTabCharacters();
}

void SkParagraph_ParagraphStyle_setReplaceTabCharacters(reskia_paragraph_style_t *style, bool value) {
    if (style != nullptr) {
        as_paragraph_style(style)->setReplaceTabCharacters(value);
    }
}

bool SkParagraph_ParagraphStyle_getApplyRoundingHack(const reskia_paragraph_style_t *style) {
    return style != nullptr && as_paragraph_style(style)->getApplyRoundingHack();
}

void SkParagraph_ParagraphStyle_setApplyRoundingHack(reskia_paragraph_style_t *style, bool value) {
    if (style != nullptr) {
        as_paragraph_style(style)->setApplyRoundingHack(value);
    }
}

} // extern "C"
