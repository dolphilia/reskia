//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_H
#define RAIA_SKIA_SK_FONT_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_font_t reskia_font_t;
typedef struct reskia_font_metrics_t reskia_font_metrics_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_typeface_t reskia_typeface_t;

reskia_font_t *SkFont_new(); // () -> SkFont *
reskia_font_t *SkFont_new_2(int typeface, float size); // (sk_typeface_t typeface, SkScalar size) -> SkFont *
reskia_font_t *SkFont_new_3(int typeface); // (sk_typeface_t typeface) -> SkFont *
reskia_font_t *SkFont_new_4(int typeface, float size, float scaleX, float skewX); // (sk_typeface_t typeface, SkScalar size, SkScalar scaleX, SkScalar skewX) -> SkFont *
void SkFont_delete(reskia_font_t *font); // (SkFont *font)
bool SkFont_isForceAutoHinting(reskia_font_t *font); // (SkFont *font) -> bool
bool SkFont_isEmbeddedBitmaps(reskia_font_t *font); // (SkFont *font) -> bool
bool SkFont_isSubpixel(reskia_font_t *font); // (SkFont *font) -> bool
bool SkFont_isLinearMetrics(reskia_font_t *font); // (SkFont *font) -> bool
bool SkFont_isEmbolden(reskia_font_t *font); // (SkFont *font) -> bool
bool SkFont_isBaselineSnap(reskia_font_t *font); // (SkFont *font) -> bool
void SkFont_setForceAutoHinting(reskia_font_t *font, bool forceAutoHinting); // (SkFont *font, bool forceAutoHinting)
void SkFont_setEmbeddedBitmaps(reskia_font_t *font, bool embeddedBitmaps); // (SkFont *font, bool embeddedBitmaps)
void SkFont_setSubpixel(reskia_font_t *font, bool subpixel); // (SkFont *font, bool subpixel)
void SkFont_setLinearMetrics(reskia_font_t *font, bool linearMetrics); // (SkFont *font, bool linearMetrics)
void SkFont_setEmbolden(reskia_font_t *font, bool embolden); // (SkFont *font, bool embolden)
void SkFont_setBaselineSnap(reskia_font_t *font, bool baselineSnap); // (SkFont *font, bool baselineSnap)
int SkFont_getEdging(reskia_font_t *font); // (SkFont *font) -> SkFont::Edging
void SkFont_setEdging(reskia_font_t *font, int edging); // (SkFont *font, SkFont::Edging edging)
void SkFont_setHinting(reskia_font_t *font, int hintingLevel); // (SkFont *font, SkFontHinting hintingLevel)
int SkFont_getHinting(reskia_font_t *font); // (SkFont *font) -> SkFontHinting
int SkFont_makeWithSize(reskia_font_t *font, float size); // (SkFont *font, SkScalar size) -> sk_font_t
reskia_typeface_t * SkFont_getTypeface(reskia_font_t *font); // (SkFont *font) -> SkTypeface *
float SkFont_getSize(reskia_font_t *font); // (SkFont *font) -> SkScalar
float SkFont_getScaleX(reskia_font_t *font); // (SkFont *font) -> SkScalar
float SkFont_getSkewX(reskia_font_t *font); // (SkFont *font) -> SkScalar
int SkFont_refTypeface(reskia_font_t *font); // (SkFont *font) -> sk_typeface_t

// TODO
//void SkFont_setTypeface(void *font, sk_typeface_t typeface); // (SkFont *font, sk_typeface_t typeface)
void SkFont_setSize(reskia_font_t *font, float textSize); // (SkFont *font, SkScalar textSize)
void SkFont_setScaleX(reskia_font_t *font, float scaleX); // (SkFont *font, SkScalar scaleX)
void SkFont_setSkewX(reskia_font_t *font, float skewX); // (SkFont *font, SkScalar skewX)
int SkFont_textToGlyphs(reskia_font_t *font, const uint8_t *text, size_t byteLength, int encoding, uint16_t *glyphs, int maxGlyphCount); // (SkFont *font, const void *text, size_t byteLength, SkTextEncoding encoding, SkGlyphID glyphs[], int maxGlyphCount) -> int
uint16_t SkFont_unicharToGlyph(reskia_font_t *font, int uni); // (SkFont *font, SkUnichar uni) -> SkGlyphID
void SkFont_unicharsToGlyphs(reskia_font_t *font, const int32_t *uni, int count, uint16_t *glyphs); // (SkFont *font, const SkUnichar uni[], int count, SkGlyphID glyphs[])
int SkFont_countText(reskia_font_t *font, const uint8_t *text, size_t byteLength, int encoding); // (SkFont *font, const void *text, size_t byteLength, SkTextEncoding encoding) -> int
float SkFont_measureText(reskia_font_t *font, const uint8_t *text, size_t byteLength, int encoding, reskia_rect_t *bounds); // (SkFont *font, const void *text, size_t byteLength, SkTextEncoding encoding, SkRect *bounds) -> SkScalar
float SkFont_measureText_2(reskia_font_t *font, const uint8_t *text, size_t byteLength, int encoding, reskia_rect_t *bounds, const reskia_paint_t *paint); // (SkFont *font, const void *text, size_t byteLength, SkTextEncoding encoding, SkRect *bounds, const SkPaint *paint) -> SkScalar
void SkFont_getWidths(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds); // (SkFont *font, const SkGlyphID glyphs[], int count, SkScalar widths[], SkRect bounds[])

// TODO
//void SkFont_getWidths_2(void *font, const void * glyphs, int count, void * widths, std::nullptr_t ptr); // (SkFont *font, const SkGlyphID glyphs[], int count, SkScalar widths[], std::nullptr_t ptr)
void SkFont_getWidths_3(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths); // (SkFont *font, const SkGlyphID glyphs[], int count, SkScalar widths[])
void SkFont_getWidthsBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds, const reskia_paint_t *paint); // (SkFont *font, const SkGlyphID glyphs[], int count, SkScalar widths[], SkRect bounds[], const SkPaint *paint)
void SkFont_getBounds(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_rect_t *bounds, const reskia_paint_t *paint); // (SkFont *font, const SkGlyphID glyphs[], int count, SkRect bounds[], const SkPaint *paint)
void SkFont_getPos(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_point_t *pos, int origin); // (SkFont *font, const SkGlyphID glyphs[], int count, SkPoint pos[], sk_point_t origin)
void SkFont_getXPos(reskia_font_t *font, const uint16_t *glyphs, int count, float *xpos, float origin); // (SkFont *font, const SkGlyphID glyphs[], int count, SkScalar xpos[], SkScalar origin)
int SkFont_getIntercepts(reskia_font_t *font, const uint16_t *glyphs, int count, const reskia_point_t *pos, float top, float bottom, const reskia_paint_t *paint); // (SkFont *font, const SkGlyphID glyphs[], int count, const SkPoint pos[], SkScalar top, SkScalar bottom, const SkPaint *paint) -> int
bool SkFont_getPath(reskia_font_t *font, uint16_t glyphID, reskia_path_t *path); // (SkFont *font, SkGlyphID glyphID, SkPath *path) -> bool

// TODO
//void SkFont_getPaths(void *font, const void * glyphIDs, int count, void(*glyphPathProc)(const SkPath *pathOrNull, const SkMatrix &mx, void *ctx), void *ctx); // (SkFont *font, const SkGlyphID glyphIDs[], int count, void(*glyphPathProc)(const SkPath *pathOrNull, const SkMatrix &mx, void *ctx), void *ctx)
float SkFont_getMetrics(reskia_font_t *font, reskia_font_metrics_t *metrics); // (SkFont *font, SkFontMetrics *metrics) -> SkScalar
float SkFont_getSpacing(reskia_font_t *font); // (SkFont *font) -> SkScalar
void SkFont_dump(reskia_font_t *font); // (SkFont *font)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_H
