//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_M_44_H
#define RAIA_SKIA_SK_M_44_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_m_44.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_v3.h"
#include "../handles/static_sk_v4.h"

typedef struct reskia_m_44_t reskia_m_44_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_v3_t reskia_v3_t;
typedef struct reskia_v4_t reskia_v4_t;

//SkM44 & operator=(const SkM44 &src)
//bool operator==(const SkM44 &other)
//bool operator!=(const SkM44 &other)
//SkV4 operator*(const SkV4 &v)
//SkV3 operator*(SkV3 v)

reskia_m_44_t *SkM44_new(const reskia_m_44_t *src); // (const SkM44 *src) -> SkM44 *
reskia_m_44_t *SkM44_new_2(const reskia_matrix_t *src); // (const SkMatrix *src) -> SkM44 *
reskia_m_44_t *SkM44_new_3(); // () -> SkM44 *
reskia_m_44_t *SkM44_new_4(const reskia_m_44_t *a, const reskia_m_44_t *b); // (const SkM44 *a, const SkM44 *b) -> SkM44 *
reskia_m_44_t *SkM44_new_5(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15); // (SkScalar m0, SkScalar m4, SkScalar m8, SkScalar m12, SkScalar m1, SkScalar m5, SkScalar m9, SkScalar m13, SkScalar m2, SkScalar m6, SkScalar m10, SkScalar m14, SkScalar m3, SkScalar m7, SkScalar m11, SkScalar m15) -> SkM44 *
void SkM44_delete(reskia_m_44_t *m44); // (SkM44 *m44)
void SkM44_getColMajor(reskia_m_44_t *m44, float *v); // (SkM44 *m44, SkScalar v[])
void SkM44_getRowMajor(reskia_m_44_t *m44, float *v); // (SkM44 *m44, SkScalar v[])
float SkM44_rc(reskia_m_44_t *m44, int r, int c); // (SkM44 *m44, int r, int c) -> SkScalar
void SkM44_setRC(reskia_m_44_t *m44, int r, int c, float value); // (SkM44 *m44, int r, int c, SkScalar value)
sk_v4_t SkM44_row(reskia_m_44_t *m44, int i); // (SkM44 *m44, int i) -> sk_v4_t
sk_v4_t SkM44_col(reskia_m_44_t *m44, int i); // (SkM44 *m44, int i) -> sk_v4_t
void SkM44_setRow(reskia_m_44_t *m44, int i, const reskia_v4_t *v); // (SkM44 *m44, int i, const SkV4 *v)
void SkM44_setCol(reskia_m_44_t *m44, int i, const reskia_v4_t *v); // (SkM44 *m44, int i, const SkV4 *v)
sk_m_44_t SkM44_setIdentity(reskia_m_44_t *m44); // (SkM44 *m44) -> sk_m_44_t
sk_m_44_t SkM44_setTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_setScale(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_setRotateUnitSinCos(reskia_m_44_t *m44, sk_v3_t axis, float sinAngle, float cosAngle); // (SkM44 *m44, sk_v3_t axis, SkScalar sinAngle, SkScalar cosAngle) -> sk_m_44_t
sk_m_44_t SkM44_setRotateUnit(reskia_m_44_t *m44, sk_v3_t axis, float radians); // (SkM44 *m44, sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_setRotate(reskia_m_44_t *m44, sk_v3_t axis, float radians); // (SkM44 *m44, sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_setConcat(reskia_m_44_t *m44, const reskia_m_44_t *a, const reskia_m_44_t *b); // (SkM44 *m44, const SkM44 *a, const SkM44 *b) -> sk_m_44_t
sk_m_44_t SkM44_preConcat(reskia_m_44_t *m44, const reskia_m_44_t *m); // (SkM44 *m44, const SkM44 *m) -> sk_m_44_t
sk_m_44_t SkM44_preConcat_2(reskia_m_44_t *m44, const reskia_matrix_t *matrix); // (SkM44 *m44, const SkMatrix *matrix) -> sk_m_44_t
sk_m_44_t SkM44_postConcat(reskia_m_44_t *m44, const reskia_m_44_t *m); // (SkM44 *m44, const SkM44 *m) -> sk_m_44_t
void SkM44_normalizePerspective(reskia_m_44_t *m44); // (SkM44 *m44)
bool SkM44_isFinite(reskia_m_44_t *m44); // (SkM44 *m44) -> bool
bool SkM44_invert(reskia_m_44_t *m44, reskia_m_44_t *inverse); // (SkM44 *m44, SkM44 *inverse) -> bool
sk_m_44_t SkM44_transpose(reskia_m_44_t *m44); // (SkM44 *m44) -> sk_m_44_t
void SkM44_dump(reskia_m_44_t *m44); // (SkM44 *m44)
sk_v4_t SkM44_map(reskia_m_44_t *m44, float x, float y, float z, float w); // (SkM44 *m44, float x, float y, float z, float w) -> sk_v4_t
sk_matrix_t SkM44_asM33(reskia_m_44_t *m44); // (SkM44 *m44) -> sk_matrix_t
sk_m_44_t SkM44_preTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_postTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_preScale(reskia_m_44_t *m44, float x, float y); // (SkM44 *m44, SkScalar x, SkScalar y) -> sk_m_44_t
sk_m_44_t SkM44_preScale_2(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t

// static

sk_m_44_t SkM44_Rows(const reskia_v4_t *r0, const reskia_v4_t *r1, const reskia_v4_t *r2, const reskia_v4_t *r3); // (const SkV4 *r0, const SkV4 *r1, const SkV4 *r2, const SkV4 *r3) -> sk_m_44_t
sk_m_44_t SkM44_Cols(const reskia_v4_t *c0, const reskia_v4_t *c1, const reskia_v4_t *c2, const reskia_v4_t *c3); // (const SkV4 *c0, const SkV4 *c1, const SkV4 *c2, const SkV4 *c3) -> sk_m_44_t
sk_m_44_t SkM44_RowMajor(const float *r); // (const SkScalar r[16]) -> sk_m_44_t
sk_m_44_t SkM44_ColMajor(const float *c); // (const SkScalar c[16]) -> sk_m_44_t
sk_m_44_t SkM44_Translate(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_Scale(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_Rotate(sk_v3_t axis, float radians); // (sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst); // (const SkRect *src, const SkRect *dst) -> sk_m_44_t
sk_m_44_t SkM44_LookAt(const reskia_v3_t *eye, const reskia_v3_t *center, const reskia_v3_t *up); // (const SkV3 *eye, const SkV3 *center, const SkV3 *up) -> sk_m_44_t
sk_m_44_t SkM44_Perspective(float near, float far, float angle); // (float near, float far, float angle) -> sk_m_44_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_M_44_H
