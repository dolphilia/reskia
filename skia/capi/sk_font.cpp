//
// Created by dolphilia on 2024/01/08.
//

#include "sk_font.h"

#include "include/core/SkFont.h"
#include "include/core/SkFontTypes.h"

#include "../handles/static_sk_typeface.h"
#include "../handles/static_std_vector_sk_scalar.h"
#include "../handles/static_sk_font.h"
#include "../handles/static_sk_point.h"

#include "../handles/static_sk_font-internal.h"
#include "../handles/static_sk_point-internal.h"
#include "../handles/static_std_vector_sk_scalar-internal.h"
#include "../handles/static_sk_typeface-internal.h"

#include <optional>
#include <utility>
#include <vector>

namespace {

struct ReskiaFontGetPathsCallback {
    reskia_font_glyph_path_proc_t proc;
    void *ctx;
};

void reskia_font_get_paths_bridge(const SkPath *pathOrNull, const SkMatrix &mx, void *ctx) {
    auto *callback = static_cast<ReskiaFontGetPathsCallback *>(ctx);
    if (callback == nullptr || callback->proc == nullptr) {
        return;
    }
    callback->proc(
            reinterpret_cast<const reskia_path_t *>(pathOrNull),
            reinterpret_cast<const reskia_matrix_t *>(&mx),
            callback->ctx);
}

sk_font_t make_font_handle(SkFont font) {
    return static_sk_font_make(std::move(font));
}

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

SkFont *as_font(reskia_font_t *font) {
    return reinterpret_cast<SkFont *>(font);
}

const SkFont *as_font(const reskia_font_t *font) {
    return reinterpret_cast<const SkFont *>(font);
}

bool has_text_encoding(reskia_font_text_encoding_t encoding) {
    return encoding >= 0 && encoding <= static_cast<reskia_font_text_encoding_t>(SkTextEncoding::kGlyphID);
}

bool has_text_input(const void *text, size_t byteLength, reskia_font_text_encoding_t encoding) {
    return byteLength > 0 && text != nullptr && has_text_encoding(encoding);
}

bool has_required_glyph_input(const uint16_t *glyphs, int count) {
    return count > 0 && glyphs != nullptr;
}

}

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
    delete as_font(font);
}

bool SkFont_equals(reskia_font_t *font, const reskia_font_t *other) {
    if (font == nullptr || other == nullptr) {
        return false;
    }
    return *as_font(font) == *as_font(other);
}

bool SkFont_notEquals(reskia_font_t *font, const reskia_font_t *other) {
    if (font == nullptr || other == nullptr) {
        return false;
    }
    return *as_font(font) != *as_font(other);
}

bool SkFont_isForceAutoHinting(reskia_font_t *font) {
    return font != nullptr && as_font(font)->isForceAutoHinting();
}

bool SkFont_isEmbeddedBitmaps(reskia_font_t *font) {
    return font != nullptr && as_font(font)->isEmbeddedBitmaps();
}

bool SkFont_isSubpixel(reskia_font_t *font) {
    return font != nullptr && as_font(font)->isSubpixel();
}

bool SkFont_isLinearMetrics(reskia_font_t *font) {
    return font != nullptr && as_font(font)->isLinearMetrics();
}

bool SkFont_isEmbolden(reskia_font_t *font) {
    return font != nullptr && as_font(font)->isEmbolden();
}

bool SkFont_isBaselineSnap(reskia_font_t *font) {
    return font != nullptr && as_font(font)->isBaselineSnap();
}

void SkFont_setForceAutoHinting(reskia_font_t *font, bool forceAutoHinting) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setForceAutoHinting(forceAutoHinting);
}

void SkFont_setEmbeddedBitmaps(reskia_font_t *font, bool embeddedBitmaps) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setEmbeddedBitmaps(embeddedBitmaps);
}

void SkFont_setSubpixel(reskia_font_t *font, bool subpixel) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setSubpixel(subpixel);
}

void SkFont_setLinearMetrics(reskia_font_t *font, bool linearMetrics) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setLinearMetrics(linearMetrics);
}

void SkFont_setEmbolden(reskia_font_t *font, bool embolden) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setEmbolden(embolden);
}

void SkFont_setBaselineSnap(reskia_font_t *font, bool baselineSnap) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setBaselineSnap(baselineSnap);
}

reskia_font_edging_t SkFont_getEdging(reskia_font_t *font) {
    if (font == nullptr) {
        return -1;
    }
    return static_cast<reskia_font_edging_t>(as_font(font)->getEdging());
}

void SkFont_setEdging(reskia_font_t *font, reskia_font_edging_t edging) {
    if (font == nullptr || edging < 0 || edging > static_cast<reskia_font_edging_t>(SkFont::Edging::kSubpixelAntiAlias)) {
        return;
    }
    as_font(font)->setEdging(static_cast<SkFont::Edging>(edging));
}

void SkFont_setHinting(reskia_font_t *font, reskia_font_hinting_t hintingLevel) {
    if (font == nullptr || hintingLevel < 0 || hintingLevel > 3) {
        return;
    }
    as_font(font)->setHinting(static_cast<SkFontHinting>(hintingLevel));
}

reskia_font_hinting_t SkFont_getHinting(reskia_font_t *font) {
    if (font == nullptr) {
        return -1;
    }
    return static_cast<reskia_font_hinting_t>(as_font(font)->getHinting());
}

sk_font_t SkFont_makeWithSize(reskia_font_t *font, float size) {
    if (font == nullptr) {
        return 0;
    }
    return make_font_handle(as_font(font)->makeWithSize(size));
}

reskia_typeface_t * SkFont_getTypeface(reskia_font_t *font) {
    if (font == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_typeface_t *>(as_font(font)->getTypeface());
}

float SkFont_getSize(reskia_font_t *font) {
    if (font == nullptr) {
        return 0.0f;
    }
    return as_font(font)->getSize();
}

float SkFont_getScaleX(reskia_font_t *font) {
    if (font == nullptr) {
        return 0.0f;
    }
    return as_font(font)->getScaleX();
}

float SkFont_getSkewX(reskia_font_t *font) {
    if (font == nullptr) {
        return 0.0f;
    }
    return as_font(font)->getSkewX();
}

sk_typeface_t SkFont_refTypeface(reskia_font_t *font) {
    if (font == nullptr) {
        return 0;
    }
    return make_typeface_handle(as_font(font)->refTypeface());
}

void SkFont_setTypeface(reskia_font_t *font, sk_typeface_t typeface) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setTypeface(static_sk_typeface_get_entity(typeface));
}

void SkFont_setSize(reskia_font_t *font, float textSize) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setSize(textSize);
}

void SkFont_setScaleX(reskia_font_t *font, float scaleX) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setScaleX(scaleX);
}

void SkFont_setSkewX(reskia_font_t *font, float skewX) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->setSkewX(skewX);
}

int SkFont_textToGlyphs(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, uint16_t *glyphs, int maxGlyphCount) {
    if (font == nullptr || !has_text_input(text, byteLength, encoding) || maxGlyphCount < 0 || (maxGlyphCount > 0 && glyphs == nullptr)) {
        return 0;
    }
    return as_font(font)->textToGlyphs(
            text,
            byteLength,
            static_cast<SkTextEncoding>(encoding),
            {reinterpret_cast<SkGlyphID *>(glyphs), static_cast<size_t>(maxGlyphCount)});
}

uint16_t SkFont_unicharToGlyph(reskia_font_t *font, reskia_unichar_t uni) {
    if (font == nullptr) {
        return 0;
    }
    return as_font(font)->unicharToGlyph(static_cast<SkUnichar>(uni));
}

void SkFont_unicharsToGlyphs(reskia_font_t *font, const int32_t *uni, int count, uint16_t *glyphs) {
    if (font == nullptr || count <= 0 || uni == nullptr || glyphs == nullptr) {
        return;
    }
    as_font(font)->unicharsToGlyphs(
            {reinterpret_cast<const SkUnichar *>(uni), static_cast<size_t>(count)},
            {reinterpret_cast<SkGlyphID *>(glyphs), static_cast<size_t>(count)});
}

int SkFont_countText(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding) {
    if (font == nullptr || !has_text_input(text, byteLength, encoding)) {
        return 0;
    }
    return as_font(font)->countText(text, byteLength, static_cast<SkTextEncoding>(encoding));
}

float SkFont_measureText(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, reskia_rect_t *bounds) {
    if (font == nullptr || !has_text_input(text, byteLength, encoding)) {
        return 0.0f;
    }
    return as_font(font)->measureText(text, byteLength, static_cast<SkTextEncoding>(encoding), reinterpret_cast<SkRect *>(bounds));
}

float SkFont_measureTextWithPaint(reskia_font_t *font, const uint8_t *text, size_t byteLength, reskia_font_text_encoding_t encoding, reskia_rect_t *bounds, const reskia_paint_t *paint) {
    if (font == nullptr || !has_text_input(text, byteLength, encoding)) {
        return 0.0f;
    }
    return as_font(font)->measureText(text, byteLength, static_cast<SkTextEncoding>(encoding), reinterpret_cast<SkRect *>(bounds), reinterpret_cast<const SkPaint *>(paint));
}

void SkFont_getWidths(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds) {
    if (font == nullptr || !has_required_glyph_input(glyphs, count)) {
        return;
    }
    as_font(font)->getWidthsBounds(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {widths, widths == nullptr ? 0 : static_cast<size_t>(count)},
            {reinterpret_cast<SkRect *>(bounds), bounds == nullptr ? 0 : static_cast<size_t>(count)},
            nullptr);
}

float SkFont_getWidth(reskia_font_t *font, uint16_t glyph) {
    if (font == nullptr) {
        return 0.0f;
    }
    return as_font(font)->getWidth(glyph);
}

// TODO
void SkFont_getWidths_2(reskia_font_t *font, const void * glyphs, int count, void * widths, std::nullptr_t ptr) {
    if (font == nullptr || count <= 0 || glyphs == nullptr || widths == nullptr) {
        return;
    }
    as_font(font)->getWidths(
            {static_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {static_cast<SkScalar *>(widths), static_cast<size_t>(count)});
}

void SkFont_getWidthsWithoutBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths) {
    if (font == nullptr || !has_required_glyph_input(glyphs, count)) {
        return;
    }
    if (widths == nullptr) {
        return;
    }
    as_font(font)->getWidths(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {widths, static_cast<size_t>(count)});
}

void SkFont_getWidthsBounds(reskia_font_t *font, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds, const reskia_paint_t *paint) {
    if (font == nullptr || !has_required_glyph_input(glyphs, count)) {
        return;
    }
    as_font(font)->getWidthsBounds(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {widths, widths == nullptr ? 0 : static_cast<size_t>(count)},
            {reinterpret_cast<SkRect *>(bounds), bounds == nullptr ? 0 : static_cast<size_t>(count)},
            reinterpret_cast<const SkPaint *>(paint));
}

void SkFont_getBounds(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_rect_t *bounds, const reskia_paint_t *paint) {
    if (font == nullptr || !has_required_glyph_input(glyphs, count)) {
        return;
    }
    if (bounds == nullptr) {
        return;
    }
    as_font(font)->getBounds(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {reinterpret_cast<SkRect *>(bounds), static_cast<size_t>(count)},
            reinterpret_cast<const SkPaint *>(paint));
}

void SkFont_getPos(reskia_font_t *font, const uint16_t *glyphs, int count, reskia_point_t *pos, sk_point_t origin) {
    if (font == nullptr || !has_required_glyph_input(glyphs, count) || pos == nullptr) {
        return;
    }
    as_font(font)->getPos(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {reinterpret_cast<SkPoint *>(pos), static_cast<size_t>(count)},
            static_sk_point_get_entity(origin));
}

void SkFont_getXPos(reskia_font_t *font, const uint16_t *glyphs, int count, float *xpos, float origin) {
    if (font == nullptr || !has_required_glyph_input(glyphs, count) || xpos == nullptr) {
        return;
    }
    as_font(font)->getXPos(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {xpos, static_cast<size_t>(count)},
            origin);
}

int SkFont_getIntercepts(reskia_font_t *font, const uint16_t *glyphs, int count, const reskia_point_t *pos, float top, float bottom, const reskia_paint_t *paint) { // @TODO
    if (font == nullptr || !has_required_glyph_input(glyphs, count) || pos == nullptr) {
        return 0;
    }
    std::vector<SkScalar> intercepts = as_font(font)->getIntercepts(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {reinterpret_cast<const SkPoint *>(pos), static_cast<size_t>(count)},
            top,
            bottom,
            reinterpret_cast<const SkPaint *>(paint));
    if (intercepts.empty()) {
        return 0;
    }
    return static_vector_sk_scalar_make(std::move(intercepts));
}

bool SkFont_getPath(reskia_font_t *font, uint16_t glyphID, reskia_path_t *path) {
    if (font == nullptr || path == nullptr) {
        return false;
    }
    std::optional<SkPath> glyphPath = as_font(font)->getPath(glyphID);
    if (!glyphPath.has_value()) {
        return false;
    }
    *reinterpret_cast<SkPath *>(path) = std::move(*glyphPath);
    return true;
}

void SkFont_getPaths(reskia_font_t *font, const uint16_t *glyphIDs, int count, reskia_font_glyph_path_proc_t glyphPathProc, void *ctx) {
    if (!font || !glyphIDs || count <= 0 || !glyphPathProc) {
        return;
    }
    ReskiaFontGetPathsCallback callback = {glyphPathProc, ctx};
    reinterpret_cast<SkFont *>(font)->getPaths(
            {reinterpret_cast<const SkGlyphID *>(glyphIDs), static_cast<size_t>(count)},
            reskia_font_get_paths_bridge,
            &callback);
}

float SkFont_getMetrics(reskia_font_t *font, reskia_font_metrics_t *metrics) {
    if (font == nullptr) {
        return 0.0f;
    }
    return as_font(font)->getMetrics(reinterpret_cast<SkFontMetrics *>(metrics));
}

float SkFont_getSpacing(reskia_font_t *font) {
    if (font == nullptr) {
        return 0.0f;
    }
    return as_font(font)->getSpacing();
}

void SkFont_dump(reskia_font_t *font) {
    if (font == nullptr) {
        return;
    }
    as_font(font)->dump();
}

}
