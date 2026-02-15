//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_POINT_3_H
#define RAIA_SKIA_SK_POINT_3_H

#include "../static/static_sk_point_3.h"

typedef struct reskia_point_3_t reskia_point_3_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkPoint3 operator-()
// void operator+=(const SkPoint3 &v)
// void operator-=(const SkPoint3 &v)
void SkPoint3_delete(reskia_point_3_t *point3); // (SkPoint3 *point3)
float SkPoint3_x(reskia_point_3_t *point3); // (SkPoint3 *point3) -> SkScalar
float SkPoint3_y(reskia_point_3_t *point3); // (SkPoint3 *point3) -> SkScalar
float SkPoint3_z(reskia_point_3_t *point3); // (SkPoint3 *point3) -> SkScalar
void SkPoint3_set(reskia_point_3_t *point3, float x, float y, float z); // (SkPoint3 *point3, SkScalar x, SkScalar y, SkScalar z)
float SkPoint3_length(reskia_point_3_t *point3); // (SkPoint3 *point3) -> SkScalar
bool SkPoint3_normalize(reskia_point_3_t *point3); // (SkPoint3 *point3) -> bool
sk_point_3_t SkPoint3_makeScale(reskia_point_3_t *point3, float scale); // (SkPoint3 *point3, SkScalar scale) -> sk_point_3_t
void SkPoint3_scale(reskia_point_3_t *point3, float value); // (SkPoint3 *point3, SkScalar value)
bool SkPoint3_isFinite(reskia_point_3_t *point3); // (SkPoint3 *point3) -> bool
float SkPoint3_dot(reskia_point_3_t *point3, const reskia_point_3_t *vec); // (SkPoint3 *point3, const SkPoint3 *vec) -> SkScalar
sk_point_3_t SkPoint3_cross(reskia_point_3_t *point3, const reskia_point_3_t *vec); // (SkPoint3 *point3, const SkPoint3 *vec) -> sk_point_3_t

// static

sk_point_3_t SkPoint3_Make(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> sk_point_3_t
float SkPoint3_Length(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> SkScalar
float SkPoint3_DotProduct(const reskia_point_3_t *a, const reskia_point_3_t *b); // (const SkPoint3 *a, const SkPoint3 *b) -> SkScalar
sk_point_3_t SkPoint3_CrossProduct(const reskia_point_3_t *a, const reskia_point_3_t *b); // (const SkPoint3 *a, const SkPoint3 *b) -> sk_point_3_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_POINT_3_H
