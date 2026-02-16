//
// Created by dolphilia on 2024/01/29.
//

#ifndef RAIA_SKIA_SK_POINT_H
#define RAIA_SKIA_SK_POINT_H

#include "../handles/static_sk_point.h"

typedef struct reskia_i_point_t reskia_i_point_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_vector_t reskia_vector_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkPoint_delete(reskia_point_t *point); // (SkPoint *point)
float SkPoint_x(sk_point_t point); // (sk_point_t point) -> float
float SkPoint_y(sk_point_t point); // (sk_point_t point) -> float
float SkPoint_dot(sk_point_t point, const reskia_vector_t *vec); // (sk_point_t point, const SkVector *vec) -> float
float SkPoint_length(sk_point_t point); // (sk_point_t point) -> float
float SkPoint_cross(sk_point_t point, const reskia_vector_t *vec); // (sk_point_t point, const SkVector *vec) -> float
void SkPoint_set(sk_point_t point, float x, float y); // (sk_point_t point, float x, float y)
bool SkPoint_equals(sk_point_t point, float x, float y); // (sk_point_t point, float x, float y) -> bool
bool SkPoint_isZero(sk_point_t point); // (sk_point_t point) -> bool
void SkPoint_scale(sk_point_t point, float value); // (sk_point_t point, float value)
void SkPoint_scale_2(sk_point_t point, float scale, reskia_point_t *dst); // (sk_point_t point, float scale, SkPoint *dst)
bool SkPoint_isFinite(sk_point_t point); // (sk_point_t point) -> bool
float SkPoint_distanceToOrigin(sk_point_t point); // (sk_point_t point) -> float
void SkPoint_iset(sk_point_t point, const reskia_i_point_t *p); // (sk_point_t point, const SkIPoint *p)
void SkPoint_iset_2(sk_point_t point, int x, int y); // (sk_point_t point, int32_t x, int32_t y)
void SkPoint_negate(sk_point_t point); // (sk_point_t point)
void SkPoint_setAbs(sk_point_t point, const reskia_point_t *pt); // (sk_point_t point, const SkPoint *pt)
bool SkPoint_setLength(sk_point_t point, float length); // (sk_point_t point, float length) -> bool
bool SkPoint_setNormalize(sk_point_t point, float x, float y); // (sk_point_t point, float x, float y) -> bool

// static

sk_point_t SkPoint_Make(float x, float y); // (float x, float y) -> sk_point_t
float SkPoint_Normalize(reskia_vector_t *vec); // (SkVector *vec) -> float
float SkPoint_Length(float x, float y); // (float x, float y) -> float
float SkPoint_CrossProduct(const reskia_vector_t *a, const reskia_vector_t *b); // (const SkVector *a, const SkVector *b) -> float
float SkPoint_DotProduct(const reskia_vector_t *a, const reskia_vector_t *b); // (const SkVector *a, const SkVector *b) -> float
float SkPoint_Distance(const reskia_point_t *a, const reskia_point_t *b); // (const SkPoint *a, const SkPoint *b) -> float
void SkPoint_Offset(reskia_point_t *points, int count, float dx, float dy); // (SkPoint *points, int count, float dx, float dy)
void SkPoint_Offset_2(reskia_point_t *points, int count, const reskia_vector_t *offset); // (SkPoint *points, int count, const SkVector *offset)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_POINT_H
