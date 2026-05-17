#include <cstdio>
#include <cstring>

#include "capi/sk_color.h"
#include "capi/sk_font_arguments.h"
#include "capi/sk_font_metrics.h"
#include "capi/sk_paragraph_font_arguments.h"
#include "capi/sk_paragraph_style.h"
#include "capi/sk_paragraph_text_style.h"
#include "capi/sk_paint.h"
#include "capi/sk_string.h"
#include "capi/sk_typeface.h"
#include "handles/static_sk_typeface.h"

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
           check(SkParagraph_TextStyle_getForeground(nullptr) == nullptr, "get foreground null") &&
           check(!SkParagraph_TextStyle_getForegroundPaintOrID(nullptr, nullptr), "get foreground paint or id null") &&
           check(!SkParagraph_TextStyle_setForegroundPaint(nullptr, nullptr), "set foreground paint null") &&
           check(!SkParagraph_TextStyle_setForegroundPaintID(nullptr, 1), "set foreground paint id null") &&
           check(!SkParagraph_TextStyle_setForegroundColor(nullptr, nullptr), "set foreground color null") &&
           check(!SkParagraph_TextStyle_hasBackground(nullptr), "background null") &&
           check(SkParagraph_TextStyle_getBackground(nullptr) == nullptr, "get background null") &&
           check(!SkParagraph_TextStyle_getBackgroundPaintOrID(nullptr, nullptr), "get background paint or id null") &&
           check(!SkParagraph_TextStyle_setBackgroundPaint(nullptr, nullptr), "set background paint null") &&
           check(!SkParagraph_TextStyle_setBackgroundPaintID(nullptr, 1), "set background paint id null") &&
           check(!SkParagraph_TextStyle_setBackgroundColor(nullptr, nullptr), "set background color null") &&
           check(SkParagraph_TextStyle_getFontSize(nullptr) == 0.0f, "font size null") &&
           check(SkParagraph_TextStyle_getFontFamiliesCount(nullptr) == 0, "families null") &&
           check(SkParagraph_TextStyle_getFontFamilyAt(nullptr, 0) == nullptr, "family at null") &&
           check(!SkParagraph_TextStyle_setFontFamilies(nullptr, nullptr, 0), "set families null") &&
           check(SkParagraph_TextStyle_refTypeface(nullptr) == 0, "typeface null") &&
           check(!SkParagraph_TextStyle_setTypeface(nullptr, 0), "set typeface null") &&
           check(SkParagraph_TextStyle_getLocale(nullptr) == nullptr, "locale null") &&
           check(!SkParagraph_TextStyle_setLocale(nullptr, "en"), "set locale null") &&
           check(SkParagraph_TextStyle_getFontMetrics(nullptr) == nullptr, "font metrics null") &&
           check(!SkParagraph_TextStyle_isPlaceholder(nullptr), "placeholder null") &&
           check(!SkParagraph_TextStyle_getShadowAt(nullptr, 0, nullptr), "shadow at null") &&
           check(SkParagraph_TextStyle_getShadows(nullptr, nullptr, 0) == -1, "get shadows null") &&
           check(!SkParagraph_TextStyle_addShadow(nullptr, nullptr), "add shadow null") &&
           check(SkParagraph_TextStyle_getFontFeatures(nullptr, nullptr, 0) == -1, "get font features null") &&
           check(!SkParagraph_TextStyle_getFontArguments(nullptr), "get font arguments null") &&
           check(!SkParagraph_TextStyle_setFontArguments(nullptr, nullptr), "set font arguments null") &&
           check(!SkParagraph_TextStyle_clearFontArguments(nullptr), "clear font arguments null") &&
           check(SkParagraph_FontArguments_new(nullptr) == nullptr, "paragraph font arguments new null") &&
           check(SkParagraph_FontArguments_copy(nullptr) == nullptr, "paragraph font arguments copy null") &&
           check(SkParagraph_FontArguments_CloneTypeface(nullptr, 0) == 0, "paragraph font arguments clone null") &&
           check(SkParagraph_TextStyle_getTypeface(nullptr) == 0, "get typeface null") &&
           check(!SkParagraph_TextShadow_Make(0, 0.0f, 0.0f, 0.0, nullptr), "make shadow null") &&
           check(!SkParagraph_TextShadow_equals(nullptr, nullptr), "shadow equals null") &&
           check(!SkParagraph_TextShadow_hasShadow(nullptr), "shadow has null");
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

    reskia_paint_t *paint = SkPaint_new();
    if (!check(paint != nullptr, "paint new")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkPaint_setColor(paint, 0xffabcdef);
    if (!check(SkParagraph_TextStyle_setForegroundPaint(style, paint), "set foreground paint") ||
        !check(SkParagraph_TextStyle_hasForeground(style), "has foreground")) {
        SkPaint_delete(paint);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_paint_t *foreground = SkParagraph_TextStyle_getForeground(style);
    if (!check(foreground != nullptr, "get foreground") ||
        !check(SkPaint_getColor(foreground) == 0xffabcdef, "foreground color")) {
        SkPaint_delete(foreground);
        SkPaint_delete(paint);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkPaint_delete(foreground);
    SkPaint_setColor(paint, 0xff123456);
    if (!check(SkParagraph_TextStyle_setBackgroundColor(style, paint), "set background color") ||
        !check(SkParagraph_TextStyle_hasBackground(style), "has background")) {
        SkPaint_delete(paint);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_paint_t *background = SkParagraph_TextStyle_getBackground(style);
    if (!check(background != nullptr, "get background") ||
        !check(SkPaint_getColor(background) == 0xff123456, "background color")) {
        SkPaint_delete(background);
        SkPaint_delete(paint);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkPaint_delete(background);
    reskia_paragraph_paint_or_id_t paint_or_id = {};
    if (!check(SkParagraph_TextStyle_setForegroundPaintID(style, 42), "set foreground paint id") ||
        !check(SkParagraph_TextStyle_getForegroundPaintOrID(style, &paint_or_id), "get foreground paint or id") ||
        !check(paint_or_id.is_paint_id, "foreground paint id variant") ||
        !check(paint_or_id.paint_id == 42, "foreground paint id value")) {
        SkPaint_delete(paint);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    paint_or_id = {};
    if (!check(SkParagraph_TextStyle_setBackgroundPaintID(style, 77), "set background paint id") ||
        !check(SkParagraph_TextStyle_getBackgroundPaintOrID(style, &paint_or_id), "get background paint or id") ||
        !check(paint_or_id.is_paint_id, "background paint id variant") ||
        !check(paint_or_id.paint_id == 77, "background paint id value")) {
        SkPaint_delete(paint);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkParagraph_TextStyle_clearForegroundColor(style);
    SkParagraph_TextStyle_clearBackgroundColor(style);
    if (!check(!SkParagraph_TextStyle_hasForeground(style), "clear foreground") ||
        !check(!SkParagraph_TextStyle_hasBackground(style), "clear background")) {
        SkPaint_delete(paint);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkPaint_delete(paint);

    if (!check(SkParagraph_TextStyle_addFontFeature(style, "kern", 1), "add font feature") ||
        !check(SkParagraph_TextStyle_getFontFeatureNumber(style) == 1, "font feature count")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_paragraph_font_feature_t font_features[2] = {};
    if (!check(SkParagraph_TextStyle_getFontFeatures(style, font_features, 2) == 1, "get font features") ||
        !check(std::strcmp(font_features[0].name, "kern") == 0, "font feature name") ||
        !check(font_features[0].value == 1, "font feature value")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_paragraph_text_shadow_t shadow = {};
    if (!check(SkParagraph_TextShadow_Make(0xff010203, 1.0f, 2.0f, 3.0, &shadow), "make shadow") ||
        !check(SkParagraph_TextShadow_hasShadow(&shadow), "shadow has") ||
        !check(SkParagraph_TextStyle_addShadow(style, &shadow), "add shadow") ||
        !check(SkParagraph_TextStyle_getShadowNumber(style) == 1, "shadow count")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_paragraph_text_shadow_t shadows[2] = {};
    if (!check(SkParagraph_TextStyle_getShadows(style, shadows, 2) == 1, "get shadows") ||
        !check(SkParagraph_TextShadow_equals(&shadow, &shadows[0]), "get shadows equals")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_paragraph_text_shadow_t out_shadow = {};
    if (!check(SkParagraph_TextStyle_getShadowAt(style, 0, &out_shadow), "get shadow") ||
        !check(SkParagraph_TextShadow_equals(&shadow, &out_shadow), "shadow equals")) {
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    reskia_font_arguments_t *font_arguments = SkFontArguments_new();
    if (!check(font_arguments != nullptr, "font arguments new") ||
        !check(SkParagraph_TextStyle_setFontArguments(style, font_arguments), "set font arguments") ||
        !check(SkParagraph_TextStyle_getFontArguments(style), "get font arguments") ||
        !check(SkParagraph_TextStyle_clearFontArguments(style), "clear font arguments")) {
        SkFontArguments_delete(font_arguments);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    if (!check(!SkParagraph_TextStyle_getFontArguments(style), "font arguments cleared")) {
        SkFontArguments_delete(font_arguments);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    SkFontArguments_delete(font_arguments);
    font_arguments = SkFontArguments_new();
    reskia_paragraph_font_arguments_t *paragraph_font_arguments = SkParagraph_FontArguments_new(font_arguments);
    reskia_paragraph_font_arguments_t *paragraph_font_arguments_copy = SkParagraph_FontArguments_copy(paragraph_font_arguments);
    if (!check(paragraph_font_arguments != nullptr, "paragraph font arguments") ||
        !check(paragraph_font_arguments_copy != nullptr, "paragraph font arguments copy")) {
        SkParagraph_FontArguments_delete(paragraph_font_arguments_copy);
        SkParagraph_FontArguments_delete(paragraph_font_arguments);
        SkFontArguments_delete(font_arguments);
        SkParagraph_TextStyle_delete(style);
        return false;
    }
    sk_typeface_t typeface = SkTypeface_MakeDefault();
    sk_typeface_t cloned_typeface = SkParagraph_FontArguments_CloneTypeface(paragraph_font_arguments, typeface);
    if (cloned_typeface != 0) {
        static_sk_typeface_delete(cloned_typeface);
    }
    if (typeface != 0) {
        static_sk_typeface_delete(typeface);
    }
    SkParagraph_FontArguments_delete(paragraph_font_arguments_copy);
    SkParagraph_FontArguments_delete(paragraph_font_arguments);
    SkFontArguments_delete(font_arguments);
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
