//
// Created by dolphilia on 25/01/30.
//

#ifndef SK_COLOR4F_H
#define SK_COLOR4F_H

#include <stdint.h>
#include "../handles/static_sk_color_4f.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef uint32_t reskia_u32_t;
typedef uint32_t reskia_color_t;
typedef uint32_t reskia_pmcolor_t;

void SkColor4f_delete(reskia_color_4f_t *color); // NULL 入力では no-op

// Public Attributes

float SkColor4f_fR(reskia_color_4f_t *color); // NULL 入力では 0 (SkColor4f *color) -> float
float SkColor4f_fG(reskia_color_4f_t *color); // NULL 入力では 0 (SkColor4f *color) -> float
float SkColor4f_fB(reskia_color_4f_t *color); // NULL 入力では 0 (SkColor4f *color) -> float
float SkColor4f_fA(reskia_color_4f_t *color); // NULL 入力では 0 (SkColor4f *color) -> float

// Public Member Functions

bool SkColor4f_equals(reskia_color_4f_t *color, reskia_color_4f_t *other); // NULL 同士は true、片方 NULL は false
bool SkColor4f_notEquals(reskia_color_4f_t *color, reskia_color_4f_t *other); // NULL 同士は false、片方 NULL は true
sk_color_4f_t SkColor4f_mulScalar(reskia_color_4f_t *color, float scale); // NULL 入力では 0
sk_color_4f_t SkColor4f_mulColor(reskia_color_4f_t *color, reskia_color_4f_t *scale); // NULL 入力では 0
float SkColor4f_get(reskia_color_4f_t *color, int index); // index は 0..3。invalid 入力では 0
void SkColor4f_set(reskia_color_4f_t *color, int index, float value); // index は 0..3。invalid 入力では no-op

const float * SkColor4f_vec(reskia_color_4f_t *color); // borrowed raw array: 4 要素。NULL 入力では NULL (SkColor4f *color) -> const float *
float * SkColor4f_vecMutable(reskia_color_4f_t *color); // borrowed mutable raw array: 4 要素。NULL 入力では NULL (SkColor4f *color) -> float *
bool SkColor4f_toArray(reskia_color_4f_t *color, float out[4]); // out は非 NULL。invalid 入力では false

bool SkColor4f_isOpaque(reskia_color_4f_t *color); // NULL 入力では false (SkColor4f *color) -> bool
bool SkColor4f_fitsInBytes(reskia_color_4f_t *color); // NULL 入力では false (SkColor4f *color) -> bool
reskia_color_t SkColor4f_toSkColor(reskia_color_4f_t *color); // NULL 入力では 0 (SkColor4f *color) -> SkColor

reskia_u32_t SkColor4f_toBytes_RGBA(reskia_color_4f_t *color); // NULL 入力では 0 (SkColor4f *color) -> uint32_t
sk_color_4f_t SkColor4f_makeOpaque(reskia_color_4f_t *color); // NULL 入力では 0 (SkColor4f *color) -> SkColor4f

// static

int SkColor4f_FromColor(reskia_color_t color); // (SkColor color) -> SkColor4f
int SkColor4f_FromPMColor(reskia_pmcolor_t color); // (SkPMColor color) -> SkColor4f
int SkColor4f_FromBytes_RGBA(reskia_u32_t color); // (uint32_t color) -> SkColor4f

#ifdef __cplusplus
}
#endif

#endif //SK_COLOR4F_H
