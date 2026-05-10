//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_H
#define RAIA_SKIA_SK_FONT_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_font.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_typeface.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_t reskia_font_t;
typedef struct reskia_font_metrics_t reskia_font_metrics_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_typeface_t reskia_typeface_t;
typedef int32_t reskia_font_edging_t;
typedef int32_t reskia_font_hinting_t;
typedef int32_t reskia_font_text_encoding_t;
typedef int32_t reskia_unichar_t;
typedef void (*reskia_font_glyph_path_proc_t)(const reskia_path_t *path_or_null, const reskia_matrix_t *matrix, void *ctx);

reskia_font_t *SkFont_new(); // () -> SkFont *
reskia_font_t *SkFont_newWithTypefaceAndSize(int typeface, float size); // invalid/0 typeface handle は default/null typeface として扱う
reskia_font_t *SkFont_newWithTypeface(int typeface); // invalid/0 typeface handle は default/null typeface として扱う
reskia_font_t *SkFont_newWithTypefaceSizeScaleXSkewX(int typeface, float size, float scaleX, float skewX); // invalid/0 typeface handle は default/null typeface として扱う
void SkFont_delete(reskia_font_t *font); // NULL 入力では no-op
bool SkFont_equals(reskia_font_t *font, const reskia_font_t *other); // NULL 入力では false
bool SkFont_notEquals(reskia_font_t *font, const reskia_font_t *other); // NULL 入力では false
bool SkFont_isForceAutoHinting(reskia_font_t *font); // NULL 入力では false
bool SkFont_isEmbeddedBitmaps(reskia_font_t *font); // NULL 入力では false
bool SkFont_isSubpixel(reskia_font_t *font); // NULL 入力では false
bool SkFont_isLinearMetrics(reskia_font_t *font); // NULL 入力では false
bool SkFont_isEmbolden(reskia_font_t *font); // NULL 入力では false
bool SkFont_isBaselineSnap(reskia_font_t *font); // NULL 入力では false
void SkFont_setForceAutoHinting(reskia_font_t *font, bool forceAutoHinting); // NULL 入力では no-op
void SkFont_setEmbeddedBitmaps(reskia_font_t *font, bool embeddedBitmaps); // NULL 入力では no-op
void SkFont_setSubpixel(reskia_font_t *font, bool subpixel); // NULL 入力では no-op
void SkFont_setLinearMetrics(reskia_font_t *font, bool linearMetrics); // NULL 入力では no-op
void SkFont_setEmbolden(reskia_font_t *font, bool embolden); // NULL 入力では no-op
void SkFont_setBaselineSnap(reskia_font_t *font, bool baselineSnap); // NULL 入力では no-op
reskia_font_edging_t SkFont_getEdging(reskia_font_t *font); // NULL 入力では -1
void SkFont_setEdging(reskia_font_t *font, reskia_font_edging_t edging); // NULL/invalid enum 入力では no-op
void SkFont_setHinting(reskia_font_t *font, reskia_font_hinting_t hintingLevel); // NULL/invalid enum 入力では no-op
reskia_font_hinting_t SkFont_getHinting(reskia_font_t *font); // NULL 入力では -1
sk_font_t SkFont_makeWithSize(reskia_font_t *font, float size); // NULL 入力では 0
reskia_typeface_t * SkFont_getTypeface(reskia_font_t *font); // borrowed pointer。NULL 入力や未設定では NULL。caller は解放しない
float SkFont_getSize(reskia_font_t *font); // NULL 入力では 0
float SkFont_getScaleX(reskia_font_t *font); // NULL 入力では 0
float SkFont_getSkewX(reskia_font_t *font); // NULL 入力では 0
sk_typeface_t SkFont_refTypeface(reskia_font_t *font); // NULL 入力や未設定では 0

// TODO
//void SkFont_setTypeface(void *font, sk_typeface_t typeface); // (SkFont *font, sk_typeface_t typeface)
void SkFont_setSize(reskia_font_t *font, float textSize); // NULL 入力では no-op
void SkFont_setScaleX(reskia_font_t *font, float scaleX); // NULL 入力では no-op
void SkFont_setSkewX(reskia_font_t *font, float skewX); // NULL 入力では no-op
int SkFont_textToGlyphs(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, uint16_t *glyphs, int maxGlyphCount); // byteLength > 0 では text 非 NULL。glyphs は NULL 許可。invalid 入力では 0
uint16_t SkFont_unicharToGlyph(reskia_font_t *font, reskia_unichar_t uni); // NULL 入力では 0
void SkFont_unicharsToGlyphs(reskia_font_t *font, const int32_t *uni, int count, uint16_t *glyphs); // count > 0 では uni/glyphs は count 要素以上、非 NULL。invalid 入力では no-op
int SkFont_countText(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding); // byteLength > 0 では text 非 NULL。invalid 入力では 0
float SkFont_measureText(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, reskia_rect_t *bounds); // bounds は NULL 許可。invalid 入力では 0
float SkFont_measureTextWithPaint(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, reskia_rect_t *bounds, const reskia_paint_t *paint); // bounds/paint は NULL 許可。invalid 入力では 0
void SkFont_getWidths(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds); // count <= 0 では no-op。count > 0 では glyphs は count 要素以上、非 NULL。widths/bounds は NULL 許可

// TODO
//void SkFont_getWidths_2(void *font, const void * glyphs, int count, void * widths, std::nullptr_t ptr); // (SkFont *font, const SkGlyphID glyphs[], int count, SkScalar widths[], std::nullptr_t ptr)
void SkFont_getWidthsWithoutBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths); // count <= 0 では no-op。count > 0 では glyphs は count 要素以上、非 NULL。widths は NULL 許可
void SkFont_getWidthsBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds, const reskia_paint_t *paint); // count <= 0 では no-op。count > 0 では glyphs は count 要素以上、非 NULL。widths/bounds/paint は NULL 許可
void SkFont_getBounds(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_rect_t *bounds, const reskia_paint_t *paint); // count <= 0 では no-op。count > 0 では glyphs は count 要素以上、非 NULL。bounds/paint は NULL 許可
void SkFont_getPos(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_point_t *pos, sk_point_t origin); // count <= 0 では no-op。count > 0 では glyphs/pos は count 要素以上、非 NULL。origin handle 0 は {0,0} として扱う
void SkFont_getXPos(reskia_font_t *font, const uint16_t *glyphs, int count, float *xpos, float origin); // count <= 0 では no-op。count > 0 では glyphs/xpos は count 要素以上、非 NULL
int SkFont_getIntercepts(reskia_font_t *font, const uint16_t *glyphs, int count, const reskia_point_t *pos, float top, float bottom, const reskia_paint_t *paint); // count <= 0 では 0。count > 0 では glyphs/pos は count 要素以上、非 NULL。paint は NULL 許可。invalid/empty 結果では 0
bool SkFont_getPath(reskia_font_t *font, uint16_t glyphID, reskia_path_t *path); // path は非 NULL。invalid 入力では false

void SkFont_getPaths(reskia_font_t *font, const uint16_t *glyphIDs, int count, reskia_font_glyph_path_proc_t glyphPathProc, void *ctx); // count > 0 では glyphIDs/glyphPathProc は非 NULL。callback 中の path_or_null/matrix は借用で保持不可。invalid 入力では no-op
float SkFont_getMetrics(reskia_font_t *font, reskia_font_metrics_t *metrics); // metrics は NULL 許可。NULL font では 0
float SkFont_getSpacing(reskia_font_t *font); // NULL 入力では 0
void SkFont_dump(reskia_font_t *font); // NULL 入力では no-op

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_H
