#include <cstdio>

#include "capi/sk_color.h"
#include "capi/sk_font_metrics.h"
#include "capi/sk_paragraph_style.h"
#include "capi/sk_paragraph_text_style.h"
#include "capi/sk_string.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[paragraph-text-style-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_null_inputs() {
    return check(SkParagraph_TextStyle_copy(nullptr) == nullptr, "copy null") &&
           check(SkParagraph_TextStyle_cloneForPlaceholder(nullptr) == nullptr, "clone placeholder null") &&
           check(!SkParagraph_TextStyle_equals(nullptr, nullptr), "equals null") &&
           check(SkParagraph_TextStyle_getColor(nullptr) == 0, "color null") &&
           check(!SkParagraph_TextStyle_hasForeground(nullptr), "foreground null") &&
           check(!SkParagraph_TextStyle_hasBackground(nullptr), "background null") &&
           check(SkParagraph_TextStyle_getFontSize(nullptr) == 0.0f, "font size null") &&
           check(SkParagraph_TextStyle_getFontFamiliesCount(nullptr) == 0, "families null") &&
           check(SkParagraph_TextStyle_getFontFamilyAt(nullptr, 0) == nullptr, "family at null") &&
           check(!SkParagraph_TextStyle_setFontFamilies(nullptr, nullptr, 0), "set families null") &&
           check(SkParagraph_TextStyle_refTypeface(nullptr) == 0, "typeface null") &&
           check(!SkParagraph_TextStyle_setTypeface(nullptr, 0), "set typeface null") &&
           check(SkParagraph_TextStyle_getLocale(nullptr) == nullptr, "locale null") &&
           check(!SkParagraph_TextStyle_setLocale(nullptr, "en"), "set locale null") &&
           check(SkParagraph_TextStyle_getFontMetrics(nullptr) == nullptr, "font metrics null") &&
           check(!SkParagraph_TextStyle_isPlaceholder(nullptr), "placeholder null");
}

bool smoke_text_style() {
    reskia_paragraph_text_style_t *style = SkParagraph_TextStyle_new();
    if (!check(style != nullptr, "TextStyle new")) {
        return false;
    }

    SkParagraph_TextStyle_setColor(style, 0xff112233);
    SkParagraph_TextStyle_setFontSize(style, 21.0f);
    SkParagraph_TextStyle_setBaselineShift(style, 2.0f);
    SkParagraph_TextStyle_setHeightOverride(style, true);
    SkParagraph_TextStyle_setHeight(style, 1.4f);
    SkParagraph_TextStyle_setHalfLeading(style, true);
    SkParagraph_TextStyle_setLetterSpacing(style, 0.5f);
    SkParagraph_TextStyle_setWordSpacing(style, 1.5f);
    if (!check(SkParagraph_TextStyle_getColor(style) == 0xff112233, "color") ||
        !check(SkParagraph_TextStyle_getFontSize(style) == 21.0f, "font size") ||
        !check(SkParagraph_TextStyle_getBaselineShift(style) == 2.0f, "baseline shift") ||
        !check(SkParagraph_TextStyle_getHeightOverride(style), "height override") ||
        !check(SkParagraph_TextStyle_getHeight(style) == 1.4f, "height") ||
        !check(SkParagraph_TextStyle_getHalfLeading(style), "half leading") ||
        !check(SkParagraph_TextStyle_getLetterSpacing(style) == 0.5f, "letter spacing") ||
        !check(SkParagraph_TextStyle_getWordSpacing(style) == 1.5f, "word spacing")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }

    const char *families[] = {"sans-serif"};
    if (!check(SkParagraph_TextStyle_setFontFamilies(style, families, 1), "set families") ||
        !check(SkParagraph_TextStyle_getFontFamiliesCount(style) == 1, "family count")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_string_t *family = SkParagraph_TextStyle_getFontFamilyAt(style, 0);
    if (!check(family != nullptr && SkString_equalsTextWithLength(family, "sans-serif", 10), "family at")) {
        SkString_delete(family);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkString_delete(family);

    if (!check(SkParagraph_TextStyle_setDecoration(style, RESKIA_PARAGRAPH_TEXT_DECORATION_UNDERLINE), "set decoration") ||
        !check(SkParagraph_TextStyle_setDecorationMode(style, RESKIA_PARAGRAPH_TEXT_DECORATION_MODE_THROUGH), "set decoration mode") ||
        !check(SkParagraph_TextStyle_setDecorationStyle(style, RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_WAVY), "set decoration style")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkParagraph_TextStyle_setDecorationColor(style, 0xff445566);
    SkParagraph_TextStyle_setDecorationThicknessMultiplier(style, 2.0f);
    if (!check(SkParagraph_TextStyle_getDecorationType(style) == RESKIA_PARAGRAPH_TEXT_DECORATION_UNDERLINE, "decoration") ||
        !check(SkParagraph_TextStyle_getDecorationMode(style) == RESKIA_PARAGRAPH_TEXT_DECORATION_MODE_THROUGH, "decoration mode") ||
        !check(SkParagraph_TextStyle_getDecorationStyle(style) == RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_WAVY, "decoration style") ||
        !check(SkParagraph_TextStyle_getDecorationColor(style) == 0xff445566, "decoration color") ||
        !check(SkParagraph_TextStyle_getDecorationThicknessMultiplier(style) == 2.0f, "decoration thickness")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }

    if (!check(SkParagraph_TextStyle_addFontFeature(style, "kern", 1), "add font feature") ||
        !check(SkParagraph_TextStyle_getFontFeatureNumber(style) == 1, "font feature count")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkParagraph_TextStyle_resetFontFeatures(style);
    SkParagraph_TextStyle_resetShadows(style);
    if (!check(SkParagraph_TextStyle_getFontFeatureNumber(style) == 0, "font feature reset") ||
        !check(SkParagraph_TextStyle_getShadowNumber(style) == 0, "shadow reset")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }

    if (!check(SkParagraph_TextStyle_setLocale(style, "en"), "set locale") ||
        !check(SkParagraph_TextStyle_setTextBaseline(style, RESKIA_PARAGRAPH_TEXT_BASELINE_IDEOGRAPHIC), "set baseline") ||
        !check(SkParagraph_TextStyle_getTextBaseline(style) == RESKIA_PARAGRAPH_TEXT_BASELINE_IDEOGRAPHIC, "get baseline")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_string_t *locale = SkParagraph_TextStyle_getLocale(style);
    if (!check(locale != nullptr && SkString_equalsTextWithLength(locale, "en", 2), "locale")) {
        SkString_delete(locale);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkString_delete(locale);

    reskia_font_metrics_t *metrics = SkParagraph_TextStyle_getFontMetrics(style);
    if (!check(metrics != nullptr, "font metrics")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkFontMetrics_delete(metrics);

    SkParagraph_TextStyle_setPlaceholder(style);
    if (!check(SkParagraph_TextStyle_isPlaceholder(style), "set placeholder")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_paragraph_text_style_t *copy = SkParagraph_TextStyle_copy(style);
    if (!check(copy != nullptr, "copy")) {
        SkParagraph_TextStyle_delete(copy);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    (void)SkParagraph_TextStyle_equals(style, copy);
    (void)SkParagraph_TextStyle_equalsByFonts(style, copy);
    (void)SkParagraph_TextStyle_matchOneAttribute(style, RESKIA_PARAGRAPH_STYLE_TYPE_FONT, copy);
    SkParagraph_TextStyle_delete(copy);

    reskia_paragraph_text_style_t *placeholder = SkParagraph_TextStyle_cloneForPlaceholder(style);
    if (!check(placeholder != nullptr, "clone placeholder")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkParagraph_TextStyle_delete(placeholder);

    reskia_paragraph_style_t *paragraph_style = SkParagraph_ParagraphStyle_new();
    if (!check(paragraph_style != nullptr, "paragraph style new") ||
        !check(SkParagraph_ParagraphStyle_setTextStyle(paragraph_style, style), "paragraph set text style")) {
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_paragraph_text_style_t *from_paragraph = SkParagraph_ParagraphStyle_getTextStyle(paragraph_style);
    if (!check(from_paragraph != nullptr, "paragraph get text style") ||
        !check(SkParagraph_TextStyle_getFontSize(from_paragraph) == 21.0f, "paragraph text style font size")) {
        SkParagraph_TextStyle_delete(from_paragraph);
        SkParagraph_ParagraphStyle_delete(paragraph_style);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkParagraph_TextStyle_delete(from_paragraph);
    SkParagraph_ParagraphStyle_delete(paragraph_style);

    SkParagraph_TextStyle_delete(style);
    return true;
}

}  // namespace

int main() {
    return smoke_null_inputs() && smoke_text_style() ? 0 : 1;
}
