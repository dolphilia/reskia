//
// Created by dolphilia on 2026/06/02.
//

#ifndef RAIA_SKIA_SK_STRIKE_REF_H
#define RAIA_SKIA_SK_STRIKE_REF_H

#include <stdbool.h>
#include <stdint.h>

#include "../handles/static_sk_strike_ref.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_strike_ref_t reskia_strike_ref_t;

reskia_strike_ref_t *SkStrikeRef_new(); // () -> SkStrikeRef *
reskia_strike_ref_t *SkStrikeRef_newCopy(const reskia_strike_ref_t *strike_ref); // Returns NULL for NULL input.
void SkStrikeRef_delete(reskia_strike_ref_t *strike_ref); // No-op for NULL input.
bool SkStrikeRef_operator_bool(const reskia_strike_ref_t *strike_ref); // Returns false for NULL input.
bool SkStrikeRef_isValid(const reskia_strike_ref_t *strike_ref); // Returns false for NULL input.
void SkStrikeRef_getWidths(const reskia_strike_ref_t *strike_ref, const uint16_t *glyphs, int count, float *widths); // No-op when count is <= 0. glyphs and widths must be non-NULL when count is greater than 0.
float SkStrikeRef_getWidth(const reskia_strike_ref_t *strike_ref, uint16_t glyph); // Returns 0 for NULL or invalid strike_ref.
void SkStrikeRef_getWidthsBounds(const reskia_strike_ref_t *strike_ref, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds); // No-op when count is <= 0. At least one of widths or bounds must be non-NULL.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STRIKE_REF_H
