//
// Created by Codex on 2026/05/15.
//

#ifndef RAIA_SKIA_SK_PARAGRAPH_TEXT_STYLE_H
#define RAIA_SKIA_SK_PARAGRAPH_TEXT_STYLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "sk_color.h"
#include "sk_font.h"
#include "../handles/static_sk_font_style.h"
#include "../handles/static_sk_typeface.h"

typedef struct reskia_font_metrics_t reskia_font_metrics_t;
typedef struct reskia_font_arguments_t reskia_font_arguments_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_paragraph_text_style_t reskia_paragraph_text_style_t;
typedef struct reskia_string_t reskia_string_t;
typedef int32_t reskia_paragraph_style_type_t;
typedef int32_t reskia_paragraph_text_baseline_t;
typedef int32_t reskia_paragraph_text_decoration_mode_t;
typedef int32_t reskia_paragraph_text_decoration_style_t;
typedef int32_t reskia_paragraph_text_decoration_t;
typedef int32_t reskia_paragraph_paint_id_t;

typedef struct reskia_paragraph_paint_or_id_t {
    bool is_paint_id;
    reskia_paragraph_paint_id_t paint_id;
} reskia_paragraph_paint_or_id_t;

typedef struct reskia_paragraph_text_shadow_t {
    reskia_color_t color;
    float offset_x;
    float offset_y;
    double blur_sigma;
} reskia_paragraph_text_shadow_t;

typedef struct reskia_paragraph_font_feature_t {
    char name[5];
    int32_t value;
} reskia_paragraph_font_feature_t;

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RESKIA_PARAGRAPH_TEXT_DECORATION_NONE = 0x0,
    RESKIA_PARAGRAPH_TEXT_DECORATION_UNDERLINE = 0x1,
    RESKIA_PARAGRAPH_TEXT_DECORATION_OVERLINE = 0x2,
    RESKIA_PARAGRAPH_TEXT_DECORATION_LINE_THROUGH = 0x4,
};

enum {
    RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_SOLID = 0,
    RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_DOUBLE = 1,
    RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_DOTTED = 2,
    RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_DASHED = 3,
    RESKIA_PARAGRAPH_TEXT_DECORATION_STYLE_WAVY = 4,
};

enum {
    RESKIA_PARAGRAPH_TEXT_DECORATION_MODE_GAPS = 0,
    RESKIA_PARAGRAPH_TEXT_DECORATION_MODE_THROUGH = 1,
};

enum {
    RESKIA_PARAGRAPH_STYLE_TYPE_NONE = 0,
    RESKIA_PARAGRAPH_STYLE_TYPE_ALL_ATTRIBUTES = 1,
    RESKIA_PARAGRAPH_STYLE_TYPE_FONT = 2,
    RESKIA_PARAGRAPH_STYLE_TYPE_FOREGROUND = 3,
    RESKIA_PARAGRAPH_STYLE_TYPE_BACKGROUND = 4,
    RESKIA_PARAGRAPH_STYLE_TYPE_SHADOW = 5,
    RESKIA_PARAGRAPH_STYLE_TYPE_DECORATIONS = 6,
    RESKIA_PARAGRAPH_STYLE_TYPE_LETTER_SPACING = 7,
    RESKIA_PARAGRAPH_STYLE_TYPE_WORD_SPACING = 8,
};

enum {
    RESKIA_PARAGRAPH_TEXT_BASELINE_ALPHABETIC = 0,
    RESKIA_PARAGRAPH_TEXT_BASELINE_IDEOGRAPHIC = 1,
};

reskia_paragraph_text_style_t *SkParagraph_TextStyle_new(void);
reskia_paragraph_text_style_t *TextStyle_new(void); // compatibility alias for coverage tooling
void SkParagraph_TextStyle_delete(reskia_paragraph_text_style_t *style);
reskia_paragraph_text_style_t *SkParagraph_TextStyle_cloneForPlaceholder(reskia_paragraph_text_style_t *style);
reskia_paragraph_text_style_t *SkParagraph_TextStyle_copy(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_equals(const reskia_paragraph_text_style_t *style, const reskia_paragraph_text_style_t *other);
bool SkParagraph_TextStyle_equalsByFonts(const reskia_paragraph_text_style_t *style, const reskia_paragraph_text_style_t *other);
bool SkParagraph_TextStyle_matchOneAttribute(const reskia_paragraph_text_style_t *style, reskia_paragraph_style_type_t style_type, const reskia_paragraph_text_style_t *other);
reskia_color_t SkParagraph_TextStyle_getColor(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setColor(reskia_paragraph_text_style_t *style, reskia_color_t color);
bool SkParagraph_TextStyle_hasForeground(const reskia_paragraph_text_style_t *style);
reskia_paint_t *SkParagraph_TextStyle_getForeground(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_getForegroundPaintOrID(const reskia_paragraph_text_style_t *style, reskia_paragraph_paint_or_id_t *out_value);
bool SkParagraph_TextStyle_setForegroundPaint(reskia_paragraph_text_style_t *style, const reskia_paint_t *paint);
bool SkParagraph_TextStyle_setForegroundPaintID(reskia_paragraph_text_style_t *style, reskia_paragraph_paint_id_t paint_id);
bool SkParagraph_TextStyle_setForegroundColor(reskia_paragraph_text_style_t *style, const reskia_paint_t *paint);
void SkParagraph_TextStyle_clearForegroundColor(reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_hasBackground(const reskia_paragraph_text_style_t *style);
reskia_paint_t *SkParagraph_TextStyle_getBackground(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_getBackgroundPaintOrID(const reskia_paragraph_text_style_t *style, reskia_paragraph_paint_or_id_t *out_value);
bool SkParagraph_TextStyle_setBackgroundPaint(reskia_paragraph_text_style_t *style, const reskia_paint_t *paint);
bool SkParagraph_TextStyle_setBackgroundPaintID(reskia_paragraph_text_style_t *style, reskia_paragraph_paint_id_t paint_id);
bool SkParagraph_TextStyle_setBackgroundColor(reskia_paragraph_text_style_t *style, const reskia_paint_t *paint);
void SkParagraph_TextStyle_clearBackgroundColor(reskia_paragraph_text_style_t *style);
reskia_paragraph_text_decoration_t SkParagraph_TextStyle_getDecorationType(const reskia_paragraph_text_style_t *style);
reskia_paragraph_text_decoration_mode_t SkParagraph_TextStyle_getDecorationMode(const reskia_paragraph_text_style_t *style);
reskia_color_t SkParagraph_TextStyle_getDecorationColor(const reskia_paragraph_text_style_t *style);
reskia_paragraph_text_decoration_style_t SkParagraph_TextStyle_getDecorationStyle(const reskia_paragraph_text_style_t *style);
float SkParagraph_TextStyle_getDecorationThicknessMultiplier(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_setDecoration(reskia_paragraph_text_style_t *style, reskia_paragraph_text_decoration_t decoration);
bool SkParagraph_TextStyle_setDecorationMode(reskia_paragraph_text_style_t *style, reskia_paragraph_text_decoration_mode_t mode);
bool SkParagraph_TextStyle_setDecorationStyle(reskia_paragraph_text_style_t *style, reskia_paragraph_text_decoration_style_t decoration_style);
void SkParagraph_TextStyle_setDecorationColor(reskia_paragraph_text_style_t *style, reskia_color_t color);
void SkParagraph_TextStyle_setDecorationThicknessMultiplier(reskia_paragraph_text_style_t *style, float multiplier);
sk_font_style_t SkParagraph_TextStyle_getFontStyle(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_setFontStyle(reskia_paragraph_text_style_t *style, sk_font_style_t font_style);
reskia_font_edging_t SkParagraph_TextStyle_getFontEdging(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_setFontEdging(reskia_paragraph_text_style_t *style, reskia_font_edging_t edging);
bool SkParagraph_TextStyle_getSubpixel(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setSubpixel(reskia_paragraph_text_style_t *style, bool subpixel);
reskia_font_hinting_t SkParagraph_TextStyle_getFontHinting(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_setFontHinting(reskia_paragraph_text_style_t *style, reskia_font_hinting_t hinting);
size_t SkParagraph_TextStyle_getShadowNumber(const reskia_paragraph_text_style_t *style);
int32_t SkParagraph_TextStyle_getShadows(const reskia_paragraph_text_style_t *style, reskia_paragraph_text_shadow_t *dst, int32_t dst_count);
bool SkParagraph_TextStyle_getShadowAt(const reskia_paragraph_text_style_t *style, size_t index, reskia_paragraph_text_shadow_t *out_shadow);
bool SkParagraph_TextStyle_addShadow(reskia_paragraph_text_style_t *style, const reskia_paragraph_text_shadow_t *shadow);
void SkParagraph_TextStyle_resetShadows(reskia_paragraph_text_style_t *style);
size_t SkParagraph_TextStyle_getFontFeatureNumber(const reskia_paragraph_text_style_t *style);
int32_t SkParagraph_TextStyle_getFontFeatures(const reskia_paragraph_text_style_t *style, reskia_paragraph_font_feature_t *dst, int32_t dst_count);
bool SkParagraph_TextStyle_addFontFeature(reskia_paragraph_text_style_t *style, const char *font_feature, int32_t value);
bool SkParagraph_TextStyle_getFontArguments(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_setFontArguments(reskia_paragraph_text_style_t *style, const reskia_font_arguments_t *arguments);
bool SkParagraph_TextStyle_clearFontArguments(reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_resetFontFeatures(reskia_paragraph_text_style_t *style);
float SkParagraph_TextStyle_getFontSize(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setFontSize(reskia_paragraph_text_style_t *style, float size);
size_t SkParagraph_TextStyle_getFontFamiliesCount(const reskia_paragraph_text_style_t *style);
reskia_string_t *SkParagraph_TextStyle_getFontFamilyAt(const reskia_paragraph_text_style_t *style, size_t index);
bool SkParagraph_TextStyle_setFontFamilies(reskia_paragraph_text_style_t *style, const char *families[], int32_t families_count);
float SkParagraph_TextStyle_getBaselineShift(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setBaselineShift(reskia_paragraph_text_style_t *style, float baseline_shift);
float SkParagraph_TextStyle_getHeight(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setHeight(reskia_paragraph_text_style_t *style, float height);
bool SkParagraph_TextStyle_getHeightOverride(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setHeightOverride(reskia_paragraph_text_style_t *style, bool height_override);
bool SkParagraph_TextStyle_getHalfLeading(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setHalfLeading(reskia_paragraph_text_style_t *style, bool half_leading);
float SkParagraph_TextStyle_getLetterSpacing(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setLetterSpacing(reskia_paragraph_text_style_t *style, float letter_spacing);
float SkParagraph_TextStyle_getWordSpacing(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setWordSpacing(reskia_paragraph_text_style_t *style, float word_spacing);
sk_typeface_t SkParagraph_TextStyle_refTypeface(const reskia_paragraph_text_style_t *style);
sk_typeface_t SkParagraph_TextStyle_getTypeface(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_setTypeface(reskia_paragraph_text_style_t *style, sk_typeface_t typeface);
reskia_string_t *SkParagraph_TextStyle_getLocale(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_setLocale(reskia_paragraph_text_style_t *style, const char *locale);
reskia_paragraph_text_baseline_t SkParagraph_TextStyle_getTextBaseline(const reskia_paragraph_text_style_t *style);
bool SkParagraph_TextStyle_setTextBaseline(reskia_paragraph_text_style_t *style, reskia_paragraph_text_baseline_t baseline);
reskia_font_metrics_t *SkParagraph_TextStyle_getFontMetrics(const reskia_paragraph_text_style_t *style); // owned; delete with SkFontMetrics_delete
bool SkParagraph_TextStyle_isPlaceholder(const reskia_paragraph_text_style_t *style);
void SkParagraph_TextStyle_setPlaceholder(reskia_paragraph_text_style_t *style);

bool SkParagraph_TextShadow_Make(reskia_color_t color, float offset_x, float offset_y, double blur_sigma, reskia_paragraph_text_shadow_t *out_shadow);
bool SkParagraph_TextShadow_equals(const reskia_paragraph_text_shadow_t *shadow, const reskia_paragraph_text_shadow_t *other);
bool SkParagraph_TextShadow_hasShadow(const reskia_paragraph_text_shadow_t *shadow);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PARAGRAPH_TEXT_STYLE_H
