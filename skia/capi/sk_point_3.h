//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_POINT_3_H
#define RAIA_SKIA_SK_POINT_3_H

#include "../handles/static_sk_point_3.h"

typedef struct reskia_point_3_t reskia_point_3_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkPoint3 operator-()
// void operator+=(const SkPoint3 &v)
// void operator-=(const SkPoint3 &v)
void SkPoint3_delete(reskia_point_3_t *point3); // NULL point3 is no-op.
float SkPoint3_x(reskia_point_3_t *point3); // NULL point3 returns 0.
float SkPoint3_y(reskia_point_3_t *point3); // NULL point3 returns 0.
float SkPoint3_z(reskia_point_3_t *point3); // NULL point3 returns 0.
void SkPoint3_set(reskia_point_3_t *point3, float x, float y, float z); // NULL point3 is no-op.
float SkPoint3_length(reskia_point_3_t *point3); // NULL point3 returns 0.
bool SkPoint3_normalize(reskia_point_3_t *point3); // NULL point3 returns false.
sk_point_3_t SkPoint3_makeScale(reskia_point_3_t *point3, float scale); // NULL point3 returns 0.
void SkPoint3_scale(reskia_point_3_t *point3, float value); // NULL point3 is no-op.
bool SkPoint3_isFinite(reskia_point_3_t *point3); // NULL point3 returns false.
float SkPoint3_dot(reskia_point_3_t *point3, const reskia_point_3_t *vec); // NULL input returns 0.
sk_point_3_t SkPoint3_cross(reskia_point_3_t *point3, const reskia_point_3_t *vec); // NULL input returns 0.

// static

sk_point_3_t SkPoint3_Make(float x, float y, float z); // Returns a caller-owned SkPoint3 handle.
float SkPoint3_Length(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> SkScalar
float SkPoint3_DotProduct(const reskia_point_3_t *a, const reskia_point_3_t *b); // NULL input returns 0.
sk_point_3_t SkPoint3_CrossProduct(const reskia_point_3_t *a, const reskia_point_3_t *b); // NULL input returns 0.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_POINT_3_H
