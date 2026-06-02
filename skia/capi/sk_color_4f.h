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

void SkColor4f_delete(reskia_color_4f_t *color); // No-op for NULL input.

// Public Attributes

float SkColor4f_fR(reskia_color_4f_t *color); // Returns 0 for NULL input. (SkColor4f *color) -> float
float SkColor4f_fG(reskia_color_4f_t *color); // Returns 0 for NULL input. (SkColor4f *color) -> float
float SkColor4f_fB(reskia_color_4f_t *color); // Returns 0 for NULL input. (SkColor4f *color) -> float
float SkColor4f_fA(reskia_color_4f_t *color); // Returns 0 for NULL input. (SkColor4f *color) -> float

// Public Member Functions

bool SkColor4f_equals(reskia_color_4f_t *color, reskia_color_4f_t *other); // Returns true when both inputs are NULL, false when only one is NULL.
bool SkColor4f_notEquals(reskia_color_4f_t *color, reskia_color_4f_t *other); // Returns false when both inputs are NULL, true when only one is NULL.
sk_color_4f_t SkColor4f_mulScalar(reskia_color_4f_t *color, float scale); // Returns 0 for NULL input.
sk_color_4f_t SkColor4f_mulColor(reskia_color_4f_t *color, reskia_color_4f_t *scale); // Returns 0 for NULL input.
float SkColor4f_get(reskia_color_4f_t *color, int index); // index must be 0..3. Returns 0 for invalid input.
void SkColor4f_set(reskia_color_4f_t *color, int index, float value); // index must be 0..3. No-op for invalid input.

const float * SkColor4f_vec(reskia_color_4f_t *color); // borrowed raw array: 4 elements. Returns NULL for NULL input. (SkColor4f *color) -> const float *
float * SkColor4f_vecMutable(reskia_color_4f_t *color); // borrowed mutable raw array: 4 elements. Returns NULL for NULL input. (SkColor4f *color) -> float *
bool SkColor4f_toArray(reskia_color_4f_t *color, float out[4]); // out must be non-NULL. Returns false for invalid input.

bool SkColor4f_isOpaque(reskia_color_4f_t *color); // Returns false for NULL input. (SkColor4f *color) -> bool
bool SkColor4f_fitsInBytes(reskia_color_4f_t *color); // Returns false for NULL input. (SkColor4f *color) -> bool
reskia_color_t SkColor4f_toSkColor(reskia_color_4f_t *color); // Returns 0 for NULL input. (SkColor4f *color) -> SkColor

reskia_u32_t SkColor4f_toBytes_RGBA(reskia_color_4f_t *color); // Returns 0 for NULL input. (SkColor4f *color) -> uint32_t
sk_color_4f_t SkColor4f_makeOpaque(reskia_color_4f_t *color); // Returns 0 for NULL input. (SkColor4f *color) -> SkColor4f

// static

int SkColor4f_FromColor(reskia_color_t color); // (SkColor color) -> SkColor4f
int SkColor4f_FromPMColor(reskia_pmcolor_t color); // (SkPMColor color) -> SkColor4f
int SkColor4f_FromBytes_RGBA(reskia_u32_t color); // (uint32_t color) -> SkColor4f

#ifdef __cplusplus
}
#endif

#endif //SK_COLOR4F_H
