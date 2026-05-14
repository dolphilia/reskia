//
// Created by Codex on 2026/05/15.
//

#ifndef RAIA_SKIA_SK_PARAGRAPH_STYLE_H
#define RAIA_SKIA_SK_PARAGRAPH_STYLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_font_style.h"

typedef struct reskia_paragraph_strut_style_t reskia_paragraph_strut_style_t;
typedef struct reskia_paragraph_style_t reskia_paragraph_style_t;
typedef struct reskia_paragraph_text_style_t reskia_paragraph_text_style_t;
typedef struct reskia_string_t reskia_string_t;
typedef int32_t reskia_paragraph_text_align_t;
typedef int32_t reskia_paragraph_text_direction_t;
typedef int32_t reskia_paragraph_text_height_behavior_t;

#ifdef __cplusplus
extern "C" {
#endif

enum {
    RESKIA_PARAGRAPH_TEXT_ALIGN_LEFT = 0,
    RESKIA_PARAGRAPH_TEXT_ALIGN_RIGHT = 1,
    RESKIA_PARAGRAPH_TEXT_ALIGN_CENTER = 2,
    RESKIA_PARAGRAPH_TEXT_ALIGN_JUSTIFY = 3,
    RESKIA_PARAGRAPH_TEXT_ALIGN_START = 4,
    RESKIA_PARAGRAPH_TEXT_ALIGN_END = 5,
};

enum {
    RESKIA_PARAGRAPH_TEXT_DIRECTION_RTL = 0,
    RESKIA_PARAGRAPH_TEXT_DIRECTION_LTR = 1,
};

enum {
    RESKIA_PARAGRAPH_TEXT_HEIGHT_ALL = 0x0,
    RESKIA_PARAGRAPH_TEXT_HEIGHT_DISABLE_FIRST_ASCENT = 0x1,
    RESKIA_PARAGRAPH_TEXT_HEIGHT_DISABLE_LAST_DESCENT = 0x2,
    RESKIA_PARAGRAPH_TEXT_HEIGHT_DISABLE_ALL = 0x3,
};

reskia_paragraph_strut_style_t *SkParagraph_StrutStyle_new(void);
reskia_paragraph_strut_style_t *StrutStyle_new(void); // compatibility alias for coverage tooling
void SkParagraph_StrutStyle_delete(reskia_paragraph_strut_style_t *style);
reskia_paragraph_strut_style_t *SkParagraph_StrutStyle_copy(const reskia_paragraph_strut_style_t *style);
bool SkParagraph_StrutStyle_equals(const reskia_paragraph_strut_style_t *style, const reskia_paragraph_strut_style_t *other);
size_t SkParagraph_StrutStyle_getFontFamiliesCount(const reskia_paragraph_strut_style_t *style);
reskia_string_t *SkParagraph_StrutStyle_getFontFamilyAt(const reskia_paragraph_strut_style_t *style, size_t index);
bool SkParagraph_StrutStyle_setFontFamilies(reskia_paragraph_strut_style_t *style, const char *families[], int32_t families_count);
sk_font_style_t SkParagraph_StrutStyle_getFontStyle(const reskia_paragraph_strut_style_t *style);
bool SkParagraph_StrutStyle_setFontStyle(reskia_paragraph_strut_style_t *style, sk_font_style_t font_style);
float SkParagraph_StrutStyle_getFontSize(const reskia_paragraph_strut_style_t *style);
void SkParagraph_StrutStyle_setFontSize(reskia_paragraph_strut_style_t *style, float size);
float SkParagraph_StrutStyle_getHeight(const reskia_paragraph_strut_style_t *style);
void SkParagraph_StrutStyle_setHeight(reskia_paragraph_strut_style_t *style, float height);
float SkParagraph_StrutStyle_getLeading(const reskia_paragraph_strut_style_t *style);
void SkParagraph_StrutStyle_setLeading(reskia_paragraph_strut_style_t *style, float leading);
bool SkParagraph_StrutStyle_getStrutEnabled(const reskia_paragraph_strut_style_t *style);
void SkParagraph_StrutStyle_setStrutEnabled(reskia_paragraph_strut_style_t *style, bool enabled);
bool SkParagraph_StrutStyle_getForceStrutHeight(const reskia_paragraph_strut_style_t *style);
void SkParagraph_StrutStyle_setForceStrutHeight(reskia_paragraph_strut_style_t *style, bool force);
bool SkParagraph_StrutStyle_getHeightOverride(const reskia_paragraph_strut_style_t *style);
void SkParagraph_StrutStyle_setHeightOverride(reskia_paragraph_strut_style_t *style, bool override_height);
bool SkParagraph_StrutStyle_getHalfLeading(const reskia_paragraph_strut_style_t *style);
void SkParagraph_StrutStyle_setHalfLeading(reskia_paragraph_strut_style_t *style, bool half_leading);

reskia_paragraph_style_t *SkParagraph_ParagraphStyle_new(void);
reskia_paragraph_style_t *ParagraphStyle_new(void); // compatibility alias for coverage tooling
void SkParagraph_ParagraphStyle_delete(reskia_paragraph_style_t *style);
reskia_paragraph_style_t *SkParagraph_ParagraphStyle_copy(const reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_equals(const reskia_paragraph_style_t *style, const reskia_paragraph_style_t *other);
reskia_paragraph_strut_style_t *SkParagraph_ParagraphStyle_getStrutStyle(const reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_setStrutStyle(reskia_paragraph_style_t *style, const reskia_paragraph_strut_style_t *strut_style);
reskia_paragraph_text_style_t *SkParagraph_ParagraphStyle_getTextStyle(const reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_setTextStyle(reskia_paragraph_style_t *style, const reskia_paragraph_text_style_t *text_style);
reskia_paragraph_text_direction_t SkParagraph_ParagraphStyle_getTextDirection(const reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_setTextDirection(reskia_paragraph_style_t *style, reskia_paragraph_text_direction_t direction);
reskia_paragraph_text_align_t SkParagraph_ParagraphStyle_getTextAlign(const reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_setTextAlign(reskia_paragraph_style_t *style, reskia_paragraph_text_align_t align);
size_t SkParagraph_ParagraphStyle_getMaxLines(const reskia_paragraph_style_t *style);
void SkParagraph_ParagraphStyle_setMaxLines(reskia_paragraph_style_t *style, size_t max_lines);
reskia_string_t *SkParagraph_ParagraphStyle_getEllipsis(const reskia_paragraph_style_t *style);
int32_t SkParagraph_ParagraphStyle_getEllipsisUtf16(const reskia_paragraph_style_t *style, uint16_t *dst, int32_t dst_units);
bool SkParagraph_ParagraphStyle_setEllipsis(reskia_paragraph_style_t *style, const char *ellipsis);
bool SkParagraph_ParagraphStyle_setEllipsisUtf16(reskia_paragraph_style_t *style, const uint16_t *ellipsis, int32_t units);
float SkParagraph_ParagraphStyle_getHeight(const reskia_paragraph_style_t *style);
void SkParagraph_ParagraphStyle_setHeight(reskia_paragraph_style_t *style, float height);
reskia_paragraph_text_height_behavior_t SkParagraph_ParagraphStyle_getTextHeightBehavior(const reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_setTextHeightBehavior(reskia_paragraph_style_t *style, reskia_paragraph_text_height_behavior_t behavior);
bool SkParagraph_ParagraphStyle_unlimited_lines(const reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_ellipsized(const reskia_paragraph_style_t *style);
reskia_paragraph_text_align_t SkParagraph_ParagraphStyle_effective_align(const reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_hintingIsOn(const reskia_paragraph_style_t *style);
void SkParagraph_ParagraphStyle_turnHintingOff(reskia_paragraph_style_t *style);
bool SkParagraph_ParagraphStyle_getReplaceTabCharacters(const reskia_paragraph_style_t *style);
void SkParagraph_ParagraphStyle_setReplaceTabCharacters(reskia_paragraph_style_t *style, bool value);
bool SkParagraph_ParagraphStyle_getApplyRoundingHack(const reskia_paragraph_style_t *style);
void SkParagraph_ParagraphStyle_setApplyRoundingHack(reskia_paragraph_style_t *style, bool value);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PARAGRAPH_STYLE_H
