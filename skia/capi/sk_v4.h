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

// bool operator==(const SkV4 &v)
// bool operator!=(const SkV4 &v)
// SkV4 operator-()
// SkV4 operator+(const SkV4 &v)
// SkV4 operator-(const SkV4 &v)
// SkV4 operator*(const SkV4 &v)
// float operator[](int i)
// float & operator[](int i)

void SkV4_delete(reskia_v4_t *v4); // (SkV4 *v4)
float SkV4_lengthSquared(reskia_v4_t *v4); // (SkV4 *v4) -> SkScalar
float SkV4_length(reskia_v4_t *v4); // (SkV4 *v4) -> SkScalar
float SkV4_dot(reskia_v4_t *v4, const reskia_v4_t *v); // (SkV4 *v4, const SkV4 *v) -> SkScalar
sk_v4_t SkV4_normalize(reskia_v4_t *v4); // (SkV4 *v4) -> sk_v4_t
const float *SkV4_ptr(reskia_v4_t *v4); // (SkV4 *v4) -> const float *
float *SkV4_ptr_2(reskia_v4_t *v4); // (SkV4 *v4) -> float *

// static

float SkV4_Dot(const reskia_v4_t *a, const reskia_v4_t *b); // (const SkV4 *a, const SkV4 *b) -> SkScalar
sk_v4_t SkV4_Normalize(const reskia_v4_t *v); // (const SkV4 *v) -> sk_v4_t

#ifdef __cplusplus
}
#endif


#endif //RAIA_SKIA_SK_V4_H
