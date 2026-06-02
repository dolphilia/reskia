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

reskia_m_44_t *SkM44_new(const reskia_m_44_t *src); // src は非 NULL。NULL 入力では NULL
reskia_m_44_t *SkM44_newFromMatrix(const reskia_matrix_t *src); // src は非 NULL。NULL 入力では NULL
reskia_m_44_t *SkM44_newDefault(); // () -> SkM44 *
reskia_m_44_t *SkM44_newFromConcat(const reskia_m_44_t *a, const reskia_m_44_t *b); // a/b は非 NULL。NULL 入力では NULL
reskia_m_44_t *SkM44_newFromScalars(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15); // (SkScalar m0, SkScalar m4, SkScalar m8, SkScalar m12, SkScalar m1, SkScalar m5, SkScalar m9, SkScalar m13, SkScalar m2, SkScalar m6, SkScalar m10, SkScalar m14, SkScalar m3, SkScalar m7, SkScalar m11, SkScalar m15) -> SkM44 *
void SkM44_delete(reskia_m_44_t *m44); // NULL 入力では no-op
bool SkM44_equals(reskia_m_44_t *m44, const reskia_m_44_t *other); // NULL 入力では false
bool SkM44_notEquals(reskia_m_44_t *m44, const reskia_m_44_t *other); // NULL 入力では false
void SkM44_getColMajor(reskia_m_44_t *m44, float *v); // v は 16 要素以上、非 NULL。NULL 入力では no-op
void SkM44_getRowMajor(reskia_m_44_t *m44, float *v); // v は 16 要素以上、非 NULL。NULL 入力では no-op
float SkM44_rc(reskia_m_44_t *m44, int r, int c); // r/c は 0..3。NULL/範囲外入力では 0
void SkM44_setRC(reskia_m_44_t *m44, int r, int c, float value); // r/c は 0..3。NULL/範囲外入力では no-op
sk_v4_t SkM44_row(reskia_m_44_t *m44, int i); // i は 0..3。NULL/範囲外入力では default vector handle
sk_v4_t SkM44_col(reskia_m_44_t *m44, int i); // i は 0..3。NULL/範囲外入力では default vector handle
void SkM44_setRow(reskia_m_44_t *m44, int i, const reskia_v4_t *v); // i は 0..3、v 非 NULL。NULL/範囲外入力では no-op
void SkM44_setCol(reskia_m_44_t *m44, int i, const reskia_v4_t *v); // i は 0..3、v 非 NULL。NULL/範囲外入力では no-op
sk_m_44_t SkM44_setIdentity(reskia_m_44_t *m44); // NULL 入力では 0
sk_m_44_t SkM44_setTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_setScale(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_setRotateUnitSinCos(reskia_m_44_t *m44, sk_v3_t axis, float sinAngle, float cosAngle); // (SkM44 *m44, sk_v3_t axis, SkScalar sinAngle, SkScalar cosAngle) -> sk_m_44_t
sk_m_44_t SkM44_setRotateUnit(reskia_m_44_t *m44, sk_v3_t axis, float radians); // (SkM44 *m44, sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_setRotate(reskia_m_44_t *m44, sk_v3_t axis, float radians); // (SkM44 *m44, sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_setConcat(reskia_m_44_t *m44, const reskia_m_44_t *a, const reskia_m_44_t *b); // a/b は非 NULL。NULL 入力では 0
sk_m_44_t SkM44_preConcat(reskia_m_44_t *m44, const reskia_m_44_t *m); // m は非 NULL。NULL 入力では 0
sk_m_44_t SkM44_preConcatMatrix(reskia_m_44_t *m44, const reskia_matrix_t *matrix); // matrix は非 NULL。NULL 入力では 0
sk_m_44_t SkM44_postConcat(reskia_m_44_t *m44, const reskia_m_44_t *m); // m は非 NULL。NULL 入力では 0
void SkM44_normalizePerspective(reskia_m_44_t *m44); // NULL 入力では no-op
bool SkM44_isFinite(reskia_m_44_t *m44); // NULL 入力では false
bool SkM44_invert(reskia_m_44_t *m44, reskia_m_44_t *inverse); // inverse は NULL 許可。m44 NULL では false
sk_m_44_t SkM44_transpose(reskia_m_44_t *m44); // NULL 入力では 0
void SkM44_dump(reskia_m_44_t *m44); // NULL 入力では no-op
sk_v4_t SkM44_map(reskia_m_44_t *m44, float x, float y, float z, float w); // NULL 入力では default vector handle
sk_v4_t SkM44_multiplyV4(reskia_m_44_t *m44, const reskia_v4_t *v); // NULL 入力では default vector handle
sk_v3_t SkM44_multiplyV3(reskia_m_44_t *m44, const reskia_v3_t *v); // NULL 入力では default vector handle
sk_matrix_t SkM44_asM33(reskia_m_44_t *m44); // NULL 入力では 0
sk_m_44_t SkM44_preTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_postTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_preScale(reskia_m_44_t *m44, float x, float y); // (SkM44 *m44, SkScalar x, SkScalar y) -> sk_m_44_t
sk_m_44_t SkM44_preScale3D(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t

// static

sk_m_44_t SkM44_Rows(const reskia_v4_t *r0, const reskia_v4_t *r1, const reskia_v4_t *r2, const reskia_v4_t *r3); // 各 row は非 NULL。NULL 入力では 0
sk_m_44_t SkM44_Cols(const reskia_v4_t *c0, const reskia_v4_t *c1, const reskia_v4_t *c2, const reskia_v4_t *c3); // 各 col は非 NULL。NULL 入力では 0
sk_m_44_t SkM44_RowMajor(const float *r); // r は 16 要素以上、非 NULL。NULL 入力では 0
sk_m_44_t SkM44_ColMajor(const float *c); // c は 16 要素以上、非 NULL。NULL 入力では 0
sk_m_44_t SkM44_Translate(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_Scale(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_Rotate(sk_v3_t axis, float radians); // (sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst); // src/dst は非 NULL。NULL 入力では 0
sk_m_44_t SkM44_LookAt(const reskia_v3_t *eye, const reskia_v3_t *center, const reskia_v3_t *up); // eye/center/up は非 NULL。NULL 入力では 0
sk_m_44_t SkM44_Perspective(float near, float far, float angle); // (float near, float far, float angle) -> sk_m_44_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_M_44_H
