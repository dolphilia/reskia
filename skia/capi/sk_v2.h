//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_V2_H
#define RAIA_SKIA_SK_V2_H

#include "../handles/static_sk_v2.h"

typedef struct reskia_v2_t reskia_v2_t;

#ifdef __cplusplus
extern "C" {
#endif

// bool operator==(const SkV2 v)
// bool operator!=(const SkV2 v)
// SkV2 operator-()
// SkV2 operator+(SkV2 v)
// SkV2 operator-(SkV2 v)
// SkV2 operator*(SkV2 v)
// void operator+=(SkV2 v)
// void operator-=(SkV2 v)
// void operator*=(SkV2 v)
// void operator*=(SkScalar s)
// void operator/=(SkScalar s)

void SkV2_delete(reskia_v2_t *v2); // NULL 入力では no-op
float SkV2_lengthSquared(reskia_v2_t *v2); // NULL 入力では 0
float SkV2_length(reskia_v2_t *v2); // NULL 入力では 0
float SkV2_dot(reskia_v2_t *v2, sk_v2_t v); // v handle 0 は default vector。v2 NULL では 0
float SkV2_cross(reskia_v2_t *v2, sk_v2_t v); // v handle 0 は default vector。v2 NULL では 0
sk_v2_t SkV2_normalize(reskia_v2_t *v2); // NULL 入力では default vector handle
const float *SkV2_ptr(reskia_v2_t *v2); // borrowed: 2 要素、解放不要。NULL 入力では NULL
float *SkV2_ptrMutable(reskia_v2_t *v2); // borrowed mutable: 2 要素、解放不要。NULL 入力では NULL

// static

float SkV2_Dot(sk_v2_t a, sk_v2_t b); // (sk_v2_t a, sk_v2_t b) -> SkScalar
float SkV2_Cross(sk_v2_t a, sk_v2_t b); // (sk_v2_t a, sk_v2_t b) -> SkScalar
sk_v2_t SkV2_Normalize(sk_v2_t v); // (sk_v2_t v) -> sk_v2_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_V2_H
