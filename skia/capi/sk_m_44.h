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

reskia_m_44_t *SkM44_new(const reskia_m_44_t *src); // src must be non-NULL. Returns NULL for NULL input.
reskia_m_44_t *SkM44_newFromMatrix(const reskia_matrix_t *src); // src must be non-NULL. Returns NULL for NULL input.
reskia_m_44_t *SkM44_newDefault(); // () -> SkM44 *
reskia_m_44_t *SkM44_newFromConcat(const reskia_m_44_t *a, const reskia_m_44_t *b); // a and b must be non-NULL. Returns NULL for NULL input.
reskia_m_44_t *SkM44_newFromScalars(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15); // (SkScalar m0, SkScalar m4, SkScalar m8, SkScalar m12, SkScalar m1, SkScalar m5, SkScalar m9, SkScalar m13, SkScalar m2, SkScalar m6, SkScalar m10, SkScalar m14, SkScalar m3, SkScalar m7, SkScalar m11, SkScalar m15) -> SkM44 *
void SkM44_delete(reskia_m_44_t *m44); // No-op for NULL input.
bool SkM44_equals(reskia_m_44_t *m44, const reskia_m_44_t *other); // Returns false for NULL input.
bool SkM44_notEquals(reskia_m_44_t *m44, const reskia_m_44_t *other); // Returns false for NULL input.
void SkM44_getColMajor(reskia_m_44_t *m44, float *v); // v must contain at least 16 elements and be non-NULL. No-op for NULL input.
void SkM44_getRowMajor(reskia_m_44_t *m44, float *v); // v must contain at least 16 elements and be non-NULL. No-op for NULL input.
float SkM44_rc(reskia_m_44_t *m44, int r, int c); // r and c must be 0..3. Returns 0 for NULL/out-of-range input.
void SkM44_setRC(reskia_m_44_t *m44, int r, int c, float value); // r and c must be 0..3. No-op for NULL/out-of-range input.
sk_v4_t SkM44_row(reskia_m_44_t *m44, int i); // i must be 0..3. Returns default vector handle for NULL/out-of-range input.
sk_v4_t SkM44_col(reskia_m_44_t *m44, int i); // i must be 0..3. Returns default vector handle for NULL/out-of-range input.
void SkM44_setRow(reskia_m_44_t *m44, int i, const reskia_v4_t *v); // i must be 0..3 and v must be non-NULL. No-op for NULL/out-of-range input.
void SkM44_setCol(reskia_m_44_t *m44, int i, const reskia_v4_t *v); // i must be 0..3 and v must be non-NULL. No-op for NULL/out-of-range input.
sk_m_44_t SkM44_setIdentity(reskia_m_44_t *m44); // Returns 0 for NULL input.
sk_m_44_t SkM44_setTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_setScale(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_setRotateUnitSinCos(reskia_m_44_t *m44, sk_v3_t axis, float sinAngle, float cosAngle); // (SkM44 *m44, sk_v3_t axis, SkScalar sinAngle, SkScalar cosAngle) -> sk_m_44_t
sk_m_44_t SkM44_setRotateUnit(reskia_m_44_t *m44, sk_v3_t axis, float radians); // (SkM44 *m44, sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_setRotate(reskia_m_44_t *m44, sk_v3_t axis, float radians); // (SkM44 *m44, sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_setConcat(reskia_m_44_t *m44, const reskia_m_44_t *a, const reskia_m_44_t *b); // a and b must be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_preConcat(reskia_m_44_t *m44, const reskia_m_44_t *m); // m must be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_preConcatMatrix(reskia_m_44_t *m44, const reskia_matrix_t *matrix); // matrix must be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_postConcat(reskia_m_44_t *m44, const reskia_m_44_t *m); // m must be non-NULL. Returns 0 for NULL input.
void SkM44_normalizePerspective(reskia_m_44_t *m44); // No-op for NULL input.
bool SkM44_isFinite(reskia_m_44_t *m44); // Returns false for NULL input.
bool SkM44_invert(reskia_m_44_t *m44, reskia_m_44_t *inverse); // inverse may be NULL. Returns false when m44 is NULL.
sk_m_44_t SkM44_transpose(reskia_m_44_t *m44); // Returns 0 for NULL input.
void SkM44_dump(reskia_m_44_t *m44); // No-op for NULL input.
sk_v4_t SkM44_map(reskia_m_44_t *m44, float x, float y, float z, float w); // Returns default vector handle for NULL input.
sk_v4_t SkM44_multiplyV4(reskia_m_44_t *m44, const reskia_v4_t *v); // Returns default vector handle for NULL input.
sk_v3_t SkM44_multiplyV3(reskia_m_44_t *m44, const reskia_v3_t *v); // Returns default vector handle for NULL input.
sk_matrix_t SkM44_asM33(reskia_m_44_t *m44); // Returns 0 for NULL input.
sk_m_44_t SkM44_preTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_postTranslate(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_preScale(reskia_m_44_t *m44, float x, float y); // (SkM44 *m44, SkScalar x, SkScalar y) -> sk_m_44_t
sk_m_44_t SkM44_preScale3D(reskia_m_44_t *m44, float x, float y, float z); // (SkM44 *m44, SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t

// static

sk_m_44_t SkM44_Rows(const reskia_v4_t *r0, const reskia_v4_t *r1, const reskia_v4_t *r2, const reskia_v4_t *r3); // Each row must be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_Cols(const reskia_v4_t *c0, const reskia_v4_t *c1, const reskia_v4_t *c2, const reskia_v4_t *c3); // Each column must be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_RowMajor(const float *r); // r must contain at least 16 elements and be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_ColMajor(const float *c); // c must contain at least 16 elements and be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_Translate(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_Scale(float x, float y, float z); // (SkScalar x, SkScalar y, SkScalar z) -> sk_m_44_t
sk_m_44_t SkM44_Rotate(sk_v3_t axis, float radians); // (sk_v3_t axis, SkScalar radians) -> sk_m_44_t
sk_m_44_t SkM44_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst); // src and dst must be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_LookAt(const reskia_v3_t *eye, const reskia_v3_t *center, const reskia_v3_t *up); // eye, center, and up must be non-NULL. Returns 0 for NULL input.
sk_m_44_t SkM44_Perspective(float near, float far, float angle); // (float near, float far, float angle) -> sk_m_44_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_M_44_H
