//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_V3_H
#define RAIA_SKIA_SK_V3_H

#include "../handles/static_sk_v3.h"

typedef struct reskia_v3_t reskia_v3_t;

#ifdef __cplusplus
extern "C" {
#endif

// bool operator==(const SkV3 &v)
// bool operator!=(const SkV3 &v)
// SkV3 operator-()
// SkV3 operator+(const SkV3 &v)
// SkV3 operator-(const SkV3 &v)
// SkV3 operator*(const SkV3 &v)
// void operator+=(SkV3 v)
// void operator-=(SkV3 v)
// void operator*=(SkV3 v)
// void operator*=(SkScalar s)

void SkV3_delete(reskia_v3_t *v3); // (SkV3 *v3)
float SkV3_lengthSquared(reskia_v3_t *v3); // (SkV3 *v3) -> SkScalar
float SkV3_length(reskia_v3_t *v3); // (SkV3 *v3) -> SkScalar
float SkV3_dot(reskia_v3_t *v3, const reskia_v3_t *v); // (SkV3 *v3, const SkV3 *v) -> SkScalar
sk_v3_t SkV3_cross(reskia_v3_t *v3, const reskia_v3_t *v); // (SkV3 *v3, const SkV3 *v) -> sk_v3_t
sk_v3_t SkV3_normalize(reskia_v3_t *v3); // (SkV3 *v3) -> sk_v3_t
const float *SkV3_ptr(reskia_v3_t *v3); // (SkV3 *v3) -> const float *
float *SkV3_ptrMutable(reskia_v3_t *v3); // (SkV3 *v3) -> float *

// static

float SkV3_Dot(const reskia_v3_t *a, const reskia_v3_t *b); // (const SkV3 *a, const SkV3 *b) -> SkScalar
sk_v3_t SkV3_Cross(const reskia_v3_t *a, const reskia_v3_t *b); // (const SkV3 *a, const SkV3 *b) -> sk_v3_t
sk_v3_t SkV3_Normalize(const reskia_v3_t *v); // (const SkV3 *v) -> sk_v3_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_V3_H
