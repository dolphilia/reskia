//
// Created by Codex on 2026/05/15.
//

#include "sk_paragraph_text_style.h"

#include "include/core/SkFontMetrics.h"
#include "include/core/SkString.h"
#include "modules/skparagraph/include/TextStyle.h"

#include "../handles/static_sk_font_style-internal.h"
#include "../handles/static_sk_typeface-internal.h"

#include <vector>
#include <utility>

namespace {

using skia::textlayout::StyleType;
using skia::textlayout::TextBaseline;
using skia::textlayout::TextDecoration;
using skia::textlayout::TextDecorationMode;
using skia::textlayout::TextDecorationStyle;
using skia::textlayout::TextStyle;

TextStyle *as_text_style(reskia_paragraph_text_style_t *style) {
    return reinterpret_cast<TextStyle *>(style);
}

const TextStyle *as_text_style(const reskia_paragraph_text_style_t *style) {
    return reinterpret_cast<const TextStyle *>(style);
}

bool valid_decoration(reskia_paragraph_text_decoration_t decoration) {
    return (decoration & ~(RESKIA_PARAGRAPH_TEXT_DECORATION_UNDERLINE |
                           RESKIA_PARAGRAPH_TEXT_DECORATION_OVERLINE |
                           RESKIA_PARAGRAPH_TEXT_DECORATION_LINE_THROUGH)) == 0;
}

bool valid_decoration_style(reskia_paragraph_text_decoration_style_t style) {
    return style >= RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_SOLID &&
           style <= RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_WAVY;
}

bool valid_decoration_mode(reskia_paragraph_text_decoration_mode_t mode) {
    return mode == RESKIA_PARAGRAPH_TEXT_DECORATION_MODE_GAPS ||
           mode == RESKIA_PARAGRAPH_TEXT_DECORATION_MODE_THROUGH;
}

bool valid_style_type(reskia_paragraph_style_type_t style_type) {
    return style_type >= RESKIA_PARAGRAPH_STYLE_TYPE_NONE &&
           style_type <= RESKIA_PARAGRAPH_STYLE_TYPE_WORD_SPACING;
}

bool valid_text_baseline(reskia_paragraph_text_baseline_t baseline) {
    return baseline == RESKIA_PARAGRAPH_TEXT_BASELINE_ALPHABETIC ||
           baseline == RESKIA_PARAGRAPH_TEXT_BASELINE_IDEOGRAPHIC;
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

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

}  // namespace

extern "C" {

reskia_paragraph_text_style_t *SkParagraph_TextStyle_new(void) {
    return reinterpret_cast<reskia_paragraph_text_style_t *>(new TextStyle());
}

reskia_paragraph_text_style_t *TextStyle_new(void) {
    return SkParagraph_TextStyle_new();
}

void SkParagraph_TextStyle_delete(reskia_paragraph_text_style_t *style) {
    delete as_text_style(style);
}

reskia_paragraph_text_style_t *SkParagraph_TextStyle_cloneForPlaceholder(reskia_paragraph_text_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_text_style_t *>(new TextStyle(as_text_style(style)->cloneForPlaceholder()));
}

reskia_paragraph_text_style_t *SkParagraph_TextStyle_copy(const reskia_paragraph_text_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paragraph_text_style_t *>(new TextStyle(*as_text_style(style)));
}

bool SkParagraph_TextStyle_equals(const reskia_paragraph_text_style_t *style, const reskia_paragraph_text_style_t *other) {
    return style != nullptr && other != nullptr && as_text_style(style)->equals(*as_text_style(other));
}

bool SkParagraph_TextStyle_equalsByFonts(const reskia_paragraph_text_style_t *style, const reskia_paragraph_text_style_t *other) {
    return style != nullptr && other != nullptr && as_text_style(style)->equalsByFonts(*as_text_style(other));
}

bool SkParagraph_TextStyle_matchOneAttribute(const reskia_paragraph_text_style_t *style, reskia_paragraph_style_type_t style_type, const reskia_paragraph_text_style_t *other) {
    if (style == nullptr || other == nullptr || !valid_style_type(style_type)) {
        return false;
    }
    return as_text_style(style)->matchOneAttribute(static_cast<StyleType>(style_type), *as_text_style(other));
}

reskia_color_t SkParagraph_TextStyle_getColor(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0 : as_text_style(style)->getColor();
}

void SkParagraph_TextStyle_setColor(reskia_paragraph_text_style_t *style, reskia_color_t color) {
    if (style != nullptr) {
        as_text_style(style)->setColor(static_cast<SkColor>(color));
    }
}

bool SkParagraph_TextStyle_hasForeground(const reskia_paragraph_text_style_t *style) {
    return style != nullptr && as_text_style(style)->hasForeground();
}

void SkParagraph_TextStyle_clearForegroundColor(reskia_paragraph_text_style_t *style) {
    if (style != nullptr) {
        as_text_style(style)->clearForegroundColor();
    }
}

bool SkParagraph_TextStyle_hasBackground(const reskia_paragraph_text_style_t *style) {
    return style != nullptr && as_text_style(style)->hasBackground();
}

void SkParagraph_TextStyle_clearBackgroundColor(reskia_paragraph_text_style_t *style) {
    if (style != nullptr) {
        as_text_style(style)->clearBackgroundColor();
    }
}

reskia_paragraph_text_decoration_t SkParagraph_TextStyle_getDecorationType(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? RESKIA_PARAGRAPH_TEXT_DECORATION_NONE : static_cast<reskia_paragraph_text_decoration_t>(as_text_style(style)->getDecorationType());
}

reskia_paragraph_text_decoration_mode_t SkParagraph_TextStyle_getDecorationMode(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? RESKIA_PARAGRAPH_TEXT_DECORATION_MODE_THROUGH : static_cast<reskia_paragraph_text_decoration_mode_t>(as_text_style(style)->getDecorationMode());
}

reskia_color_t SkParagraph_TextStyle_getDecorationColor(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0 : as_text_style(style)->getDecorationColor();
}

reskia_paragraph_text_decoration_style_t SkParagraph_TextStyle_getDecorationStyle(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_SOLID : static_cast<reskia_paragraph_text_decoration_style_t>(as_text_style(style)->getDecorationStyle());
}

float SkParagraph_TextStyle_getDecorationThicknessMultiplier(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0.0f : as_text_style(style)->getDecorationThicknessMultiplier();
}

bool SkParagraph_TextStyle_setDecoration(reskia_paragraph_text_style_t *style, reskia_paragraph_text_decoration_t decoration) {
    if (style == nullptr || !valid_decoration(decoration)) {
        return false;
    }
    as_text_style(style)->setDecoration(static_cast<TextDecoration>(decoration));
    return true;
}

bool SkParagraph_TextStyle_setDecorationMode(reskia_paragraph_text_style_t *style, reskia_paragraph_text_decoration_mode_t mode) {
    if (style == nullptr || !valid_decoration_mode(mode)) {
        return false;
    }
    as_text_style(style)->setDecorationMode(static_cast<TextDecorationMode>(mode));
    return true;
}

bool SkParagraph_TextStyle_setDecorationStyle(reskia_paragraph_text_style_t *style, reskia_paragraph_text_decoration_style_t decoration_style) {
    if (style == nullptr || !valid_decoration_style(decoration_style)) {
        return false;
    }
    as_text_style(style)->setDecorationStyle(static_cast<TextDecorationStyle>(decoration_style));
    return true;
}

void SkParagraph_TextStyle_setDecorationColor(reskia_paragraph_text_style_t *style, reskia_color_t color) {
    if (style != nullptr) {
        as_text_style(style)->setDecorationColor(static_cast<SkColor>(color));
    }
}

void SkParagraph_TextStyle_setDecorationThicknessMultiplier(reskia_paragraph_text_style_t *style, float multiplier) {
    if (style != nullptr) {
        as_text_style(style)->setDecorationThicknessMultiplier(multiplier);
    }
}

sk_font_style_t SkParagraph_TextStyle_getFontStyle(const reskia_paragraph_text_style_t *style) {
    if (style == nullptr) {
        return 0;
    }
    return static_sk_font_style_make(as_text_style(style)->getFontStyle());
}

bool SkParagraph_TextStyle_setFontStyle(reskia_paragraph_text_style_t *style, sk_font_style_t font_style) {
    if (style == nullptr) {
        return false;
    }
    as_text_style(style)->setFontStyle(font_style_or_normal(font_style));
    return true;
}

size_t SkParagraph_TextStyle_getShadowNumber(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0 : as_text_style(style)->getShadowNumber();
}

void SkParagraph_TextStyle_resetShadows(reskia_paragraph_text_style_t *style) {
    if (style != nullptr) {
        as_text_style(style)->resetShadows();
    }
}

size_t SkParagraph_TextStyle_getFontFeatureNumber(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0 : as_text_style(style)->getFontFeatureNumber();
}

bool SkParagraph_TextStyle_addFontFeature(reskia_paragraph_text_style_t *style, const char *font_feature, int32_t value) {
    if (style == nullptr || font_feature == nullptr) {
        return false;
    }
    as_text_style(style)->addFontFeature(SkString(font_feature), value);
    return true;
}

void SkParagraph_TextStyle_resetFontFeatures(reskia_paragraph_text_style_t *style) {
    if (style != nullptr) {
        as_text_style(style)->resetFontFeatures();
    }
}

float SkParagraph_TextStyle_getFontSize(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0.0f : as_text_style(style)->getFontSize();
}

void SkParagraph_TextStyle_setFontSize(reskia_paragraph_text_style_t *style, float size) {
    if (style != nullptr) {
        as_text_style(style)->setFontSize(size);
    }
}

size_t SkParagraph_TextStyle_getFontFamiliesCount(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0 : as_text_style(style)->getFontFamilies().size();
}

reskia_string_t *SkParagraph_TextStyle_getFontFamilyAt(const reskia_paragraph_text_style_t *style, size_t index) {
    if (style == nullptr || index >= as_text_style(style)->getFontFamilies().size()) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(as_text_style(style)->getFontFamilies()[index]));
}

bool SkParagraph_TextStyle_setFontFamilies(reskia_paragraph_text_style_t *style, const char *families[], int32_t families_count) {
    if (style == nullptr || families_count < 0 || (families_count > 0 && families == nullptr)) {
        return false;
    }
    as_text_style(style)->setFontFamilies(make_strings(families, families_count));
    return true;
}

float SkParagraph_TextStyle_getBaselineShift(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0.0f : as_text_style(style)->getBaselineShift();
}

void SkParagraph_TextStyle_setBaselineShift(reskia_paragraph_text_style_t *style, float baseline_shift) {
    if (style != nullptr) {
        as_text_style(style)->setBaselineShift(baseline_shift);
    }
}

float SkParagraph_TextStyle_getHeight(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0.0f : as_text_style(style)->getHeight();
}

void SkParagraph_TextStyle_setHeight(reskia_paragraph_text_style_t *style, float height) {
    if (style != nullptr) {
        as_text_style(style)->setHeight(height);
    }
}

bool SkParagraph_TextStyle_getHeightOverride(const reskia_paragraph_text_style_t *style) {
    return style != nullptr && as_text_style(style)->getHeightOverride();
}

void SkParagraph_TextStyle_setHeightOverride(reskia_paragraph_text_style_t *style, bool height_override) {
    if (style != nullptr) {
        as_text_style(style)->setHeightOverride(height_override);
    }
}

bool SkParagraph_TextStyle_getHalfLeading(const reskia_paragraph_text_style_t *style) {
    return style != nullptr && as_text_style(style)->getHalfLeading();
}

void SkParagraph_TextStyle_setHalfLeading(reskia_paragraph_text_style_t *style, bool half_leading) {
    if (style != nullptr) {
        as_text_style(style)->setHalfLeading(half_leading);
    }
}

float SkParagraph_TextStyle_getLetterSpacing(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0.0f : as_text_style(style)->getLetterSpacing();
}

void SkParagraph_TextStyle_setLetterSpacing(reskia_paragraph_text_style_t *style, float letter_spacing) {
    if (style != nullptr) {
        as_text_style(style)->setLetterSpacing(letter_spacing);
    }
}

float SkParagraph_TextStyle_getWordSpacing(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? 0.0f : as_text_style(style)->getWordSpacing();
}

void SkParagraph_TextStyle_setWordSpacing(reskia_paragraph_text_style_t *style, float word_spacing) {
    if (style != nullptr) {
        as_text_style(style)->setWordSpacing(word_spacing);
    }
}

sk_typeface_t SkParagraph_TextStyle_refTypeface(const reskia_paragraph_text_style_t *style) {
    if (style == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_text_style(style)->refTypeface());
}

bool SkParagraph_TextStyle_setTypeface(reskia_paragraph_text_style_t *style, sk_typeface_t typeface) {
    if (style == nullptr) {
        return false;
    }
    as_text_style(style)->setTypeface(typeface == 0 ? nullptr : static_sk_typeface_borrow_entity(typeface));
    return true;
}

reskia_string_t *SkParagraph_TextStyle_getLocale(const reskia_paragraph_text_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_string_t *>(new SkString(as_text_style(style)->getLocale()));
}

bool SkParagraph_TextStyle_setLocale(reskia_paragraph_text_style_t *style, const char *locale) {
    if (style == nullptr || locale == nullptr) {
        return false;
    }
    as_text_style(style)->setLocale(SkString(locale));
    return true;
}

reskia_paragraph_text_baseline_t SkParagraph_TextStyle_getTextBaseline(const reskia_paragraph_text_style_t *style) {
    return style == nullptr ? RESKIA_PARAGRAPH_TEXT_BASELINE_ALPHABETIC : static_cast<reskia_paragraph_text_baseline_t>(as_text_style(style)->getTextBaseline());
}

bool SkParagraph_TextStyle_setTextBaseline(reskia_paragraph_text_style_t *style, reskia_paragraph_text_baseline_t baseline) {
    if (style == nullptr || !valid_text_baseline(baseline)) {
        return false;
    }
    as_text_style(style)->setTextBaseline(static_cast<TextBaseline>(baseline));
    return true;
}

reskia_font_metrics_t *SkParagraph_TextStyle_getFontMetrics(const reskia_paragraph_text_style_t *style) {
    if (style == nullptr) {
        return nullptr;
    }
    auto *metrics = new SkFontMetrics();
    as_text_style(style)->getFontMetrics(metrics);
    return reinterpret_cast<reskia_font_metrics_t *>(metrics);
}

bool SkParagraph_TextStyle_isPlaceholder(const reskia_paragraph_text_style_t *style) {
    return style != nullptr && as_text_style(style)->isPlaceholder();
}

void SkParagraph_TextStyle_setPlaceholder(reskia_paragraph_text_style_t *style) {
    if (style != nullptr) {
        as_text_style(style)->setPlaceholder();
    }
}

} // extern "C"
