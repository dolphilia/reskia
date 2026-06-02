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
reskia_strike_ref_t *SkStrikeRef_newCopy(const reskia_strike_ref_t *strike_ref); // NULL 入力では NULL
void SkStrikeRef_delete(reskia_strike_ref_t *strike_ref); // NULL 入力では no-op
bool SkStrikeRef_operator_bool(const reskia_strike_ref_t *strike_ref); // NULL 入力では false
bool SkStrikeRef_isValid(const reskia_strike_ref_t *strike_ref); // NULL 入力では false
void SkStrikeRef_getWidths(const reskia_strike_ref_t *strike_ref, const uint16_t *glyphs, int count, float *widths); // count <= 0 では no-op。count > 0 では glyphs/widths は非 NULL
float SkStrikeRef_getWidth(const reskia_strike_ref_t *strike_ref, uint16_t glyph); // NULL/invalid strike_ref では 0
void SkStrikeRef_getWidthsBounds(const reskia_strike_ref_t *strike_ref, const uint16_t *glyphs, int count, float *widths, reskia_rect_t *bounds); // count <= 0 では no-op。widths/bounds は片方以上が非 NULL

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STRIKE_REF_H
