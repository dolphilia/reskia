//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font.h"

#include "include/core/SkFont.h"

#include "../handles/static_sk_typeface.h"
#include "../handles/static_std_vector_sk_scalar.h"
#include "../handles/static_sk_font.h"
#include "../handles/static_sk_point.h"

#include "../handles/static_sk_font-internal.h"
#include "../handles/static_sk_point-internal.h"
#include "../handles/static_std_vector_sk_scalar-internal.h"
#include "../handles/static_sk_typeface-internal.h"

extern "C" {

reskia_font_t *SkFont_new() {
    return reinterpret_cast<reskia_font_t *>(new SkFont());
}

reskia_font_t *SkFont_newWithTypefaceAndSize(sk_typeface_t typeface, float size) {
    return reinterpret_cast<reskia_font_t *>(new SkFont(static_sk_typeface_get_entity(typeface), size));
}

reskia_font_t *SkFont_newWithTypeface(sk_typeface_t typeface) {
    return reinterpret_cast<reskia_font_t *>(new SkFont(static_sk_typeface_get_entity(typeface)));
}

reskia_font_t *SkFont_newWithTypefaceSizeScaleXSkewX(sk_typeface_t typeface, float size, float scaleX, float skewX) {
    return reinterpret_cast<reskia_font_t *>(new SkFont(static_sk_typeface_get_entity(typeface), size, scaleX, skewX));
}

void SkFont_delete(reskia_font_t *font) {
    delete reinterpret_cast<SkFont *>(font);
}

bool SkFont_isForceAutoHinting(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->isForceAutoHinting();
}

bool SkFont_isEmbeddedBitmaps(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->isEmbeddedBitmaps();
}

bool SkFont_isSubpixel(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->isSubpixel();
}

bool SkFont_isLinearMetrics(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->isLinearMetrics();
}

bool SkFont_isEmbolden(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->isEmbolden();
}

bool SkFont_isBaselineSnap(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->isBaselineSnap();
}

void SkFont_setForceAutoHinting(reskia_font_t *font, bool forceAutoHinting) {
    reinterpret_cast<SkFont *>(font)->setForceAutoHinting(forceAutoHinting);
}

void SkFont_setEmbeddedBitmaps(reskia_font_t *font, bool embeddedBitmaps) {
    reinterpret_cast<SkFont *>(font)->setEmbeddedBitmaps(embeddedBitmaps);
}

void SkFont_setSubpixel(reskia_font_t *font, bool subpixel) {
    reinterpret_cast<SkFont *>(font)->setSubpixel(subpixel);
}

void SkFont_setLinearMetrics(reskia_font_t *font, bool linearMetrics) {
    reinterpret_cast<SkFont *>(font)->setLinearMetrics(linearMetrics);
}

void SkFont_setEmbolden(reskia_font_t *font, bool embolden) {
    reinterpret_cast<SkFont *>(font)->setEmbolden(embolden);
}

void SkFont_setBaselineSnap(reskia_font_t *font, bool baselineSnap) {
    reinterpret_cast<SkFont *>(font)->setBaselineSnap(baselineSnap);
}

reskia_font_edging_t SkFont_getEdging(reskia_font_t *font) {
    return static_cast<reskia_font_edging_t>(reinterpret_cast<SkFont *>(font)->getEdging());
}

void SkFont_setEdging(reskia_font_t *font, reskia_font_edging_t edging) {
    reinterpret_cast<SkFont *>(font)->setEdging(static_cast<SkFont::Edging>(edging));
}

void SkFont_setHinting(reskia_font_t *font, reskia_font_hinting_t hintingLevel) {
    reinterpret_cast<SkFont *>(font)->setHinting(static_cast<SkFontHinting>(hintingLevel));
}

reskia_font_hinting_t SkFont_getHinting(reskia_font_t *font) {
    return static_cast<reskia_font_hinting_t>(reinterpret_cast<SkFont *>(font)->getHinting());
}

sk_font_t SkFont_makeWithSize(reskia_font_t *font, float size) {
    return static_sk_font_make(reinterpret_cast<SkFont *>(font)->makeWithSize(size));
}

reskia_typeface_t * SkFont_getTypeface(reskia_font_t *font) {
    return reinterpret_cast<reskia_typeface_t *>(reinterpret_cast<SkFont *>(font)->getTypeface());
}

float SkFont_getSize(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->getSize();
}

float SkFont_getScaleX(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->getScaleX();
}

float SkFont_getSkewX(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->getSkewX();
}

sk_typeface_t SkFont_refTypeface(reskia_font_t *font) {
    return static_sk_typeface_make(reinterpret_cast<SkFont *>(font)->refTypeface());
}

// TODO
void SkFont_setTypeface(reskia_font_t *font, sk_typeface_t typeface) {
    //reinterpret_cast<SkFont *>(font)->setTypeface(static_sk_typeface_move(typeface));
}

void SkFont_setSize(reskia_font_t *font, float textSize) {
    reinterpret_cast<SkFont *>(font)->setSize(textSize);
}

void SkFont_setScaleX(reskia_font_t *font, float scaleX) {
    reinterpret_cast<SkFont *>(font)->setScaleX(scaleX);
}

void SkFont_setSkewX(reskia_font_t *font, float skewX) {
    reinterpret_cast<SkFont *>(font)->setSkewX(skewX);
}

int SkFont_textToGlyphs(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, uint16_t *glyphs, int maxGlyphCount) {
    return reinterpret_cast<SkFont *>(font)->textToGlyphs(text, byteLength, static_cast<SkTextEncoding>(encoding), glyphs, maxGlyphCount);
}

uint16_t SkFont_unicharToGlyph(reskia_font_t *font, reskia_unichar_t uni) {
    return reinterpret_cast<SkFont *>(font)->unicharToGlyph(static_cast<SkUnichar>(uni));
}

void SkFont_unicharsToGlyphs(reskia_font_t *font, const int32_t *uni, int count, uint16_t *glyphs) {
    reinterpret_cast<SkFont *>(font)->unicharsToGlyphs(reinterpret_cast<const SkUnichar *>(uni), count, glyphs);
}

int SkFont_countText(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding) {
    return reinterpret_cast<SkFont *>(font)->countText(text, byteLength, static_cast<SkTextEncoding>(encoding));
}

float SkFont_measureText(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, reskia_rect_t *bounds) {
    return reinterpret_cast<SkFont *>(font)->measureText(text, byteLength, static_cast<SkTextEncoding>(encoding), reinterpret_cast<SkRect *>(bounds));
}

float SkFont_measureTextWithPaint(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, reskia_rect_t *bounds, const reskia_paint_t *paint) {
    return reinterpret_cast<SkFont *>(font)->measureText(text, byteLength, static_cast<SkTextEncoding>(encoding), reinterpret_cast<SkRect *>(bounds), reinterpret_cast<const SkPaint *>(paint));
}

void SkFont_getWidths(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds) {
    reinterpret_cast<SkFont *>(font)->getWidths(glyphs, count, widths, reinterpret_cast<SkRect *>(bounds));
}

// TODO
void SkFont_getWidths_2(reskia_font_t *font, const void * glyphs, int count, void * widths, std::nullptr_t ptr) {
    reinterpret_cast<SkFont *>(font)->getWidths(static_cast<const SkGlyphID *>(glyphs), count, static_cast<SkScalar *>(widths), ptr);
}

void SkFont_getWidthsWithoutBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths) {
    reinterpret_cast<SkFont *>(font)->getWidths(glyphs, count, widths);
}

void SkFont_getWidthsBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds, const reskia_paint_t *paint) {
    reinterpret_cast<SkFont *>(font)->getWidthsBounds(glyphs, count, widths, reinterpret_cast<SkRect *>(bounds), reinterpret_cast<const SkPaint *>(paint));
}

void SkFont_getBounds(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_rect_t *bounds, const reskia_paint_t *paint) {
    reinterpret_cast<SkFont *>(font)->getBounds(glyphs, count, reinterpret_cast<SkRect *>(bounds), reinterpret_cast<const SkPaint *>(paint));
}

void SkFont_getPos(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_point_t *pos, sk_point_t origin) {
    reinterpret_cast<SkFont *>(font)->getPos(glyphs, count, reinterpret_cast<SkPoint *>(pos), static_sk_point_get_entity(origin));
}

void SkFont_getXPos(reskia_font_t *font, const uint16_t *glyphs, int count, float *xpos, float origin) {
    reinterpret_cast<SkFont *>(font)->getXPos(glyphs, count, xpos, origin);
}

int SkFont_getIntercepts(reskia_font_t *font, const uint16_t *glyphs, int count, const reskia_point_t *pos, float top, float bottom, const reskia_paint_t *paint) { // @TODO
    return static_vector_sk_scalar_make(reinterpret_cast<SkFont *>(font)->getIntercepts(glyphs, count, reinterpret_cast<const SkPoint *>(pos), top, bottom, reinterpret_cast<const SkPaint *>(paint)));
}

bool SkFont_getPath(reskia_font_t *font, uint16_t glyphID, reskia_path_t *path) {
    return reinterpret_cast<SkFont *>(font)->getPath(glyphID, reinterpret_cast<SkPath *>(path));
}

void SkFont_getPaths(reskia_font_t *font, const void * glyphIDs, int count, void(*glyphPathProc)(const SkPath *pathOrNull, const SkMatrix &mx, void *ctx), void *ctx) { // @TODO
    reinterpret_cast<SkFont *>(font)->getPaths(static_cast<const SkGlyphID *>(glyphIDs), count, glyphPathProc, ctx);
}

float SkFont_getMetrics(reskia_font_t *font, reskia_font_metrics_t *metrics) {
    return reinterpret_cast<SkFont *>(font)->getMetrics(reinterpret_cast<SkFontMetrics *>(metrics));
}

float SkFont_getSpacing(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font)->getSpacing();
}

void SkFont_dump(reskia_font_t *font) {
    reinterpret_cast<SkFont *>(font)->dump();
}

}
