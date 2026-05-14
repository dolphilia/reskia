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
// float operator[](int i)
// float & operator[](int i)

void SkV4_delete(reskia_v4_t *v4); // NULL 入力では no-op
float SkV4_lengthSquared(reskia_v4_t *v4); // NULL 入力では 0
float SkV4_length(reskia_v4_t *v4); // NULL 入力では 0
float SkV4_dot(reskia_v4_t *v4, const reskia_v4_t *v); // v は非 NULL。NULL 入力では 0
sk_v4_t SkV4_normalize(reskia_v4_t *v4); // NULL 入力では default vector handle
const float *SkV4_ptr(reskia_v4_t *v4); // borrowed: 4 要素、解放不要。NULL 入力では NULL
float *SkV4_ptrMutable(reskia_v4_t *v4); // borrowed mutable: 4 要素、解放不要。NULL 入力では NULL

// static

float SkV4_Dot(const reskia_v4_t *a, const reskia_v4_t *b); // a/b は非 NULL。NULL 入力では 0
sk_v4_t SkV4_Normalize(const reskia_v4_t *v); // v は非 NULL。NULL 入力では default vector handle

#ifdef __cplusplus
}
#endif


#endif //RAIA_SKIA_SK_V4_H
