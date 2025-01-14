//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font.h"

#include "include/core/SkFont.h"

#include "../static/static_sk_typeface.h"
#include "../static/static_std_vector_sk_scalar.h"
#include "../static/static_sk_font.h"
#include "../static/static_sk_point.h"

#include "../static/static_sk_font-internal.h"
#include "../static/static_sk_point-internal.h"
#include "../static/static_std_vector_sk_scalar-internal.h"
#include "../static/static_sk_typeface-internal.h"

extern "C" {

void *SkFont_new() {
    return new SkFont();
}

void *SkFont_new_2(sk_typeface_t typeface, float size) {
    return new SkFont(static_sk_typeface_move(typeface), size);
}

void *SkFont_new_3(sk_typeface_t typeface) {
    return new SkFont(static_sk_typeface_move(typeface));
}

void *SkFont_new_4(sk_typeface_t typeface, float size, float scaleX, float skewX) {
    return new SkFont(static_sk_typeface_move(typeface), size, scaleX, skewX);
}

void SkFont_delete(void *font) {
    delete static_cast<SkFont *>(font);
}

bool SkFont_isForceAutoHinting(void *font) {
    return static_cast<SkFont *>(font)->isForceAutoHinting();
}

bool SkFont_isEmbeddedBitmaps(void *font) {
    return static_cast<SkFont *>(font)->isEmbeddedBitmaps();
}

bool SkFont_isSubpixel(void *font) {
    return static_cast<SkFont *>(font)->isSubpixel();
}

bool SkFont_isLinearMetrics(void *font) {
    return static_cast<SkFont *>(font)->isLinearMetrics();
}

bool SkFont_isEmbolden(void *font) {
    return static_cast<SkFont *>(font)->isEmbolden();
}

bool SkFont_isBaselineSnap(void *font) {
    return static_cast<SkFont *>(font)->isBaselineSnap();
}

void SkFont_setForceAutoHinting(void *font, bool forceAutoHinting) {
    static_cast<SkFont *>(font)->setForceAutoHinting(forceAutoHinting);
}

void SkFont_setEmbeddedBitmaps(void *font, bool embeddedBitmaps) {
    static_cast<SkFont *>(font)->setEmbeddedBitmaps(embeddedBitmaps);
}

void SkFont_setSubpixel(void *font, bool subpixel) {
    static_cast<SkFont *>(font)->setSubpixel(subpixel);
}

void SkFont_setLinearMetrics(void *font, bool linearMetrics) {
    static_cast<SkFont *>(font)->setLinearMetrics(linearMetrics);
}

void SkFont_setEmbolden(void *font, bool embolden) {
    static_cast<SkFont *>(font)->setEmbolden(embolden);
}

void SkFont_setBaselineSnap(void *font, bool baselineSnap) {
    static_cast<SkFont *>(font)->setBaselineSnap(baselineSnap);
}

int SkFont_getEdging(void *font) {
    return static_cast<int>(static_cast<SkFont *>(font)->getEdging());
}

void SkFont_setEdging(void *font, int edging) {
    static_cast<SkFont *>(font)->setEdging(static_cast<SkFont::Edging>(edging));
}

void SkFont_setHinting(void *font, int hintingLevel) {
    static_cast<SkFont *>(font)->setHinting(static_cast<SkFontHinting>(hintingLevel));
}

int SkFont_getHinting(void *font) {
    return static_cast<int>(static_cast<SkFont *>(font)->getHinting());
}

sk_font_t SkFont_makeWithSize(void *font, float size) {
    return static_sk_font_make(static_cast<SkFont *>(font)->makeWithSize(size));
}

void * SkFont_getTypeface(void *font) {
    return static_cast<SkFont *>(font)->getTypeface();
}

float SkFont_getSize(void *font) {
    return static_cast<SkFont *>(font)->getSize();
}

float SkFont_getScaleX(void *font) {
    return static_cast<SkFont *>(font)->getScaleX();
}

float SkFont_getSkewX(void *font) {
    return static_cast<SkFont *>(font)->getSkewX();
}

sk_typeface_t SkFont_refTypeface(void *font) {
    return static_sk_typeface_make(static_cast<SkFont *>(font)->refTypeface());
}

// TODO
void SkFont_setTypeface(void *font, sk_typeface_t typeface) {
    //static_cast<SkFont *>(font)->setTypeface(static_sk_typeface_move(typeface));
}

void SkFont_setSize(void *font, float textSize) {
    static_cast<SkFont *>(font)->setSize(textSize);
}

void SkFont_setScaleX(void *font, float scaleX) {
    static_cast<SkFont *>(font)->setScaleX(scaleX);
}

void SkFont_setSkewX(void *font, float skewX) {
    static_cast<SkFont *>(font)->setSkewX(skewX);
}

int SkFont_textToGlyphs(void *font, const void *text, size_t byteLength, int encoding, void * glyphs, int maxGlyphCount) {
    return static_cast<SkFont *>(font)->textToGlyphs(text, byteLength, static_cast<SkTextEncoding>(encoding), static_cast<SkGlyphID *>(glyphs), maxGlyphCount);
}

unsigned short SkFont_unicharToGlyph(void *font, int uni) {
    return static_cast<SkFont *>(font)->unicharToGlyph(uni);
}

void SkFont_unicharsToGlyphs(void *font, const void * uni, int count, void * glyphs) {
    static_cast<SkFont *>(font)->unicharsToGlyphs(static_cast<const SkUnichar *>(uni), count, static_cast<SkGlyphID *>(glyphs));
}

int SkFont_countText(void *font, const void *text, size_t byteLength, int encoding) {
    return static_cast<SkFont *>(font)->countText(text, byteLength, static_cast<SkTextEncoding>(encoding));
}

float SkFont_measureText(void *font, const void *text, size_t byteLength, int encoding, void *bounds) {
    return static_cast<SkFont *>(font)->measureText(text, byteLength, static_cast<SkTextEncoding>(encoding), static_cast<SkRect *>(bounds));
}

float SkFont_measureText_2(void *font, const void *text, size_t byteLength, int encoding, void *bounds, const void *paint) {
    return static_cast<SkFont *>(font)->measureText(text, byteLength, static_cast<SkTextEncoding>(encoding), static_cast<SkRect *>(bounds), static_cast<const SkPaint *>(paint));
}

void SkFont_getWidths(void *font, const void * glyphs, int count, void * widths, void * bounds) {
    static_cast<SkFont *>(font)->getWidths(static_cast<const SkGlyphID *>(glyphs), count, static_cast<SkScalar *>(widths), static_cast<SkRect *>(bounds));
}

// TODO
void SkFont_getWidths_2(void *font, const void * glyphs, int count, void * widths, std::nullptr_t ptr) {
    static_cast<SkFont *>(font)->getWidths(static_cast<const SkGlyphID *>(glyphs), count, static_cast<SkScalar *>(widths), ptr);
}

void SkFont_getWidths_3(void *font, const void * glyphs, int count, void * widths) {
    static_cast<SkFont *>(font)->getWidths(static_cast<const SkGlyphID *>(glyphs), count, static_cast<SkScalar *>(widths));
}

void SkFont_getWidthsBounds(void *font, const void * glyphs, int count, void * widths, void * bounds, const void *paint) {
    static_cast<SkFont *>(font)->getWidthsBounds(static_cast<const SkGlyphID *>(glyphs), count, static_cast<SkScalar *>(widths), static_cast<SkRect *>(bounds), static_cast<const SkPaint *>(paint));
}

void SkFont_getBounds(void *font, const void * glyphs, int count, void * bounds, const void *paint) {
    static_cast<SkFont *>(font)->getBounds(static_cast<const SkGlyphID *>(glyphs), count, static_cast<SkRect *>(bounds), static_cast<const SkPaint *>(paint));
}

void SkFont_getPos(void *font, const void * glyphs, int count, void * pos, sk_point_t origin) {
    static_cast<SkFont *>(font)->getPos(static_cast<const SkGlyphID *>(glyphs), count, static_cast<SkPoint *>(pos), static_sk_point_get(origin));
}

void SkFont_getXPos(void *font, const void * glyphs, int count, void * xpos, float origin) {
    static_cast<SkFont *>(font)->getXPos(static_cast<const SkGlyphID *>(glyphs), count, static_cast<SkScalar *>(xpos), origin);
}

int SkFont_getIntercepts(void *font, const void * glyphs, int count, const void * pos, float top, float bottom, const void *paint) { // @TODO
    return static_vector_sk_scalar_make(static_cast<SkFont *>(font)->getIntercepts(static_cast<const SkGlyphID *>(glyphs), count, static_cast<const SkPoint *>(pos), top, bottom, static_cast<const SkPaint *>(paint)));
}

bool SkFont_getPath(void *font, unsigned short glyphID, void *path) {
    return static_cast<SkFont *>(font)->getPath(glyphID, static_cast<SkPath *>(path));
}

void SkFont_getPaths(void *font, const void * glyphIDs, int count, void(*glyphPathProc)(const SkPath *pathOrNull, const SkMatrix &mx, void *ctx), void *ctx) { // @TODO
    static_cast<SkFont *>(font)->getPaths(static_cast<const SkGlyphID *>(glyphIDs), count, glyphPathProc, ctx);
}

float SkFont_getMetrics(void *font, void *metrics) {
    return static_cast<SkFont *>(font)->getMetrics(static_cast<SkFontMetrics *>(metrics));
}

float SkFont_getSpacing(void *font) {
    return static_cast<SkFont *>(font)->getSpacing();
}

void SkFont_dump(void *font) {
    static_cast<SkFont *>(font)->dump();
}

}
