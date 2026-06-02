//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FONT_H
#define RAIA_SKIA_SK_FONT_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_font.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_strike_ref.h"
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
reskia_font_t *SkFont_newWithTypefaceAndSize(int typeface, float size); // Invalid or 0 typeface handles are treated as the default/null typeface.
reskia_font_t *SkFont_newWithTypeface(int typeface); // Invalid or 0 typeface handles are treated as the default/null typeface.
reskia_font_t *SkFont_newWithTypefaceSizeScaleXSkewX(int typeface, float size, float scaleX, float skewX); // Invalid or 0 typeface handles are treated as the default/null typeface.
void SkFont_delete(reskia_font_t *font); // No-op for NULL input.
bool SkFont_equals(reskia_font_t *font, const reskia_font_t *other); // Returns false for NULL input.
bool SkFont_notEquals(reskia_font_t *font, const reskia_font_t *other); // Returns false for NULL input.
bool SkFont_isForceAutoHinting(reskia_font_t *font); // Returns false for NULL input.
bool SkFont_isEmbeddedBitmaps(reskia_font_t *font); // Returns false for NULL input.
bool SkFont_isSubpixel(reskia_font_t *font); // Returns false for NULL input.
bool SkFont_isLinearMetrics(reskia_font_t *font); // Returns false for NULL input.
bool SkFont_isEmbolden(reskia_font_t *font); // Returns false for NULL input.
bool SkFont_isBaselineSnap(reskia_font_t *font); // Returns false for NULL input.
void SkFont_setForceAutoHinting(reskia_font_t *font, bool forceAutoHinting); // No-op for NULL input.
void SkFont_setEmbeddedBitmaps(reskia_font_t *font, bool embeddedBitmaps); // No-op for NULL input.
void SkFont_setSubpixel(reskia_font_t *font, bool subpixel); // No-op for NULL input.
void SkFont_setLinearMetrics(reskia_font_t *font, bool linearMetrics); // No-op for NULL input.
void SkFont_setEmbolden(reskia_font_t *font, bool embolden); // No-op for NULL input.
void SkFont_setBaselineSnap(reskia_font_t *font, bool baselineSnap); // No-op for NULL input.
reskia_font_edging_t SkFont_getEdging(reskia_font_t *font); // Returns -1 for NULL input.
void SkFont_setEdging(reskia_font_t *font, reskia_font_edging_t edging); // No-op for NULL or invalid enum input.
void SkFont_setHinting(reskia_font_t *font, reskia_font_hinting_t hintingLevel); // No-op for NULL or invalid enum input.
reskia_font_hinting_t SkFont_getHinting(reskia_font_t *font); // Returns -1 for NULL input.
sk_font_t SkFont_makeWithSize(reskia_font_t *font, float size); // Returns 0 for NULL input.
sk_strike_ref_t SkFont_makeStrikeRef(reskia_font_t *font); // Returns 0 for NULL input or strike creation failure.
reskia_typeface_t * SkFont_getTypeface(reskia_font_t *font); // Borrowed pointer. Returns NULL for NULL input or when unset. The caller must not free it.
float SkFont_getSize(reskia_font_t *font); // Returns 0 for NULL input.
float SkFont_getScaleX(reskia_font_t *font); // Returns 0 for NULL input.
float SkFont_getSkewX(reskia_font_t *font); // Returns 0 for NULL input.
sk_typeface_t SkFont_refTypeface(reskia_font_t *font); // Returns 0 for NULL input or when unset.

void SkFont_setTypeface(reskia_font_t *font, sk_typeface_t typeface); // No-op for NULL font. Invalid or 0 typeface handles are set as the null typeface.
void SkFont_setSize(reskia_font_t *font, float textSize); // No-op for NULL input.
void SkFont_setScaleX(reskia_font_t *font, float scaleX); // No-op for NULL input.
void SkFont_setSkewX(reskia_font_t *font, float skewX); // No-op for NULL input.
/**
 * Returns 0 when byteLength is 0. text must be non-NULL when byteLength is greater than 0.
 * encoding must be 0..3, and glyphs may be NULL. Returns 0 for invalid input.
 */
int SkFont_textToGlyphs(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, uint16_t *glyphs, int maxGlyphCount);
uint16_t SkFont_unicharToGlyph(reskia_font_t *font, reskia_unichar_t uni); // Returns 0 for NULL input.
/**
 * uni and glyphs must contain at least count elements and be non-NULL when count is greater than 0.
 * No-op for invalid input.
 */
void SkFont_unicharsToGlyphs(reskia_font_t *font, const int32_t *uni, int count, uint16_t *glyphs);
/**
 * Returns 0 when byteLength is 0. text must be non-NULL when byteLength is greater than 0.
 * encoding must be 0..3. Returns 0 for invalid input.
 */
int SkFont_countText(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding);
/**
 * Returns 0 when byteLength is 0. text must be non-NULL when byteLength is greater than 0.
 * encoding must be 0..3, and bounds may be NULL. Returns 0 for invalid input.
 */
float SkFont_measureText(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, reskia_rect_t *bounds);
/**
 * Returns 0 when byteLength is 0. text must be non-NULL when byteLength is greater than 0.
 * encoding must be 0..3, and bounds/paint may be NULL. Returns 0 for invalid input.
 */
float SkFont_measureTextWithPaint(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, reskia_rect_t *bounds, const reskia_paint_t *paint);
/**
 * No-op when count is <= 0. glyphs must contain at least count elements and be non-NULL
 * when count is greater than 0. widths and bounds may be NULL.
 */
void SkFont_getWidths(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds);
float SkFont_getWidth(reskia_font_t *font, uint16_t glyph); // Returns 0 for NULL input.

/**
 * No-op when count is <= 0. glyphs must contain at least count elements and be non-NULL
 * when count is greater than 0. widths may be NULL.
 */
void SkFont_getWidthsWithoutBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths);
/**
 * No-op when count is <= 0. glyphs must contain at least count elements and be non-NULL
 * when count is greater than 0. widths, bounds, and paint may be NULL.
 */
void SkFont_getWidthsBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds, const reskia_paint_t *paint);
/**
 * No-op when count is <= 0. glyphs must contain at least count elements and be non-NULL
 * when count is greater than 0. bounds and paint may be NULL.
 */
void SkFont_getBounds(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_rect_t *bounds, const reskia_paint_t *paint);
/**
 * No-op when count is <= 0. glyphs and pos must contain at least count elements and be non-NULL
 * when count is greater than 0. Origin handle 0 is treated as {0,0}.
 */
void SkFont_getPos(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_point_t *pos, sk_point_t origin);
/**
 * No-op when count is <= 0. glyphs and xpos must contain at least count elements and be non-NULL
 * when count is greater than 0.
 */
void SkFont_getXPos(reskia_font_t *font, const uint16_t *glyphs, int count, float *xpos, float origin);
/**
 * Returns 0 when count is <= 0. glyphs and pos must contain at least count elements and be non-NULL
 * when count is greater than 0. paint may be NULL. Returns 0 for invalid input or an empty result.
 */
int SkFont_getIntercepts(reskia_font_t *font, const uint16_t *glyphs, int count, const reskia_point_t *pos, float top, float bottom, const reskia_paint_t *paint);
bool SkFont_getPath(reskia_font_t *font, uint16_t glyphID, reskia_path_t *path); // path must be non-NULL. Returns false for invalid input.

/**
 * glyphIDs and glyphPathProc must be non-NULL when count is greater than 0.
 * path_or_null and matrix passed to the callback are borrowed and must not be retained.
 * No-op for invalid input.
 */
void SkFont_getPaths(reskia_font_t *font, const uint16_t *glyphIDs, int count, reskia_font_glyph_path_proc_t glyphPathProc, void *ctx);
float SkFont_getMetrics(reskia_font_t *font, reskia_font_metrics_t *metrics); // metrics may be NULL. Returns 0 for NULL font.
float SkFont_getSpacing(reskia_font_t *font); // Returns 0 for NULL input.
void SkFont_dump(reskia_font_t *font); // No-op for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FONT_H
