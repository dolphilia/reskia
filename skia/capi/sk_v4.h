//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_V4_H
#define RAIA_SKIA_SK_V4_H

#include "../handles/static_sk_v4.h"

typedef struct reskia_v4_t reskia_v4_t;

#ifdef __cplusplus
extern "C" {
#endif

bool SkV4_equals(reskia_v4_t *v4, const reskia_v4_t *v); // NULL input returns false.
bool SkV4_notEquals(reskia_v4_t *v4, const reskia_v4_t *v); // NULL input returns false.
sk_v4_t SkV4_negate(reskia_v4_t *v4); // NULL input returns default vector handle.
sk_v4_t SkV4_add(reskia_v4_t *v4, const reskia_v4_t *v); // NULL input returns default vector handle.
sk_v4_t SkV4_subtract(reskia_v4_t *v4, const reskia_v4_t *v); // NULL input returns default vector handle.
sk_v4_t SkV4_multiply(reskia_v4_t *v4, const reskia_v4_t *v); // NULL input returns default vector handle.

void SkV4_delete(reskia_v4_t *v4); // No-op for NULL input.
float SkV4_lengthSquared(reskia_v4_t *v4); // Returns 0 for NULL input.
float SkV4_length(reskia_v4_t *v4); // Returns 0 for NULL input.
float SkV4_dot(reskia_v4_t *v4, const reskia_v4_t *v); // v must be non-NULL. Returns 0 for NULL input.
sk_v4_t SkV4_normalize(reskia_v4_t *v4); // Returns default vector handle for NULL input.
const float *SkV4_ptr(reskia_v4_t *v4); // borrowed: 4 elements. Do not free. Returns NULL for NULL input.
float *SkV4_ptrMutable(reskia_v4_t *v4); // borrowed mutable: 4 elements. Do not free. Returns NULL for NULL input.

// static

float SkV4_Dot(const reskia_v4_t *a, const reskia_v4_t *b); // a and b must be non-NULL. Returns 0 for NULL input.
sk_v4_t SkV4_Normalize(const reskia_v4_t *v); // v must be non-NULL. Returns default vector handle for NULL input.

#ifdef __cplusplus
}
#endif


#endif //RAIA_SKIA_SK_V4_H
