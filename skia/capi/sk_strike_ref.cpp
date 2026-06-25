//
// Created by dolphilia on 2026/06/02.
//

#include "sk_strike_ref.h"

#include "include/core/SkRect.h"
#include "include/core/SkStrikeRef.h"

namespace {

SkStrikeRef *as_strike_ref(reskia_strike_ref_t *strike_ref) {
    return reinterpret_cast<SkStrikeRef *>(strike_ref);
}

const SkStrikeRef *as_strike_ref(const reskia_strike_ref_t *strike_ref) {
    return reinterpret_cast<const SkStrikeRef *>(strike_ref);
}

bool has_glyph_input(const uint16_t *glyphs, int count) {
    return count > 0 && glyphs != nullptr;
}

}

extern "C" {

reskia_strike_ref_t *SkStrikeRef_new() {
    return reinterpret_cast<reskia_strike_ref_t *>(new SkStrikeRef());
}

reskia_strike_ref_t *SkStrikeRef_newCopy(const reskia_strike_ref_t *strike_ref) {
    const SkStrikeRef *native = as_strike_ref(strike_ref);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_strike_ref_t *>(new SkStrikeRef(*native));
}

void SkStrikeRef_delete(reskia_strike_ref_t *strike_ref) {
    delete as_strike_ref(strike_ref);
}

bool SkStrikeRef_operator_bool(const reskia_strike_ref_t *strike_ref) {
    const SkStrikeRef *native = as_strike_ref(strike_ref);
    return native != nullptr && static_cast<bool>(*native);
}

bool SkStrikeRef_isValid(const reskia_strike_ref_t *strike_ref) {
    return SkStrikeRef_operator_bool(strike_ref);
}

void SkStrikeRef_getWidths(const reskia_strike_ref_t *strike_ref, const uint16_t *glyphs, int count, float *widths) {
    const SkStrikeRef *native = as_strike_ref(strike_ref);
    if (native == nullptr || !static_cast<bool>(*native) || !has_glyph_input(glyphs, count) || widths == nullptr) {
        return;
    }
    native->getWidths(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {widths, static_cast<size_t>(count)});
}

float SkStrikeRef_getWidth(const reskia_strike_ref_t *strike_ref, uint16_t glyph) {
    const SkStrikeRef *native = as_strike_ref(strike_ref);
    if (native == nullptr || !static_cast<bool>(*native)) {
        return 0.0f;
    }
    return native->getWidth(glyph);
}

void SkStrikeRef_getWidthsStrided(const reskia_strike_ref_t *strike_ref, unsigned count, const uint32_t *first_glyph, unsigned glyph_stride_32, float *first_advance, unsigned advance_stride_32) {
    const SkStrikeRef *native = as_strike_ref(strike_ref);
    if (native == nullptr || !static_cast<bool>(*native) || count == 0 || first_glyph == nullptr || first_advance == nullptr || glyph_stride_32 == 0 || advance_stride_32 == 0) {
        return;
    }
    native->getWidthsStrided(count, first_glyph, glyph_stride_32, first_advance, advance_stride_32);
}

void SkStrikeRef_getWidthsBounds(const reskia_strike_ref_t *strike_ref, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds) {
    const SkStrikeRef *native = as_strike_ref(strike_ref);
    if (native == nullptr || !static_cast<bool>(*native) || !has_glyph_input(glyphs, count) || (widths == nullptr && bounds == nullptr)) {
        return;
    }
    native->getWidthsBounds(
            {reinterpret_cast<const SkGlyphID *>(glyphs), static_cast<size_t>(count)},
            {widths, widths == nullptr ? 0 : static_cast<size_t>(count)},
            {reinterpret_cast<SkRect *>(bounds), bounds == nullptr ? 0 : static_cast<size_t>(count)});
}

}
