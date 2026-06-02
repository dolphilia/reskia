//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_MATRIX_H
#define RAIA_SKIA_SK_MATRIX_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_i_point.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_rect.h"

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_point3_t reskia_point3_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_rsxform_t reskia_rsxform_t;
typedef struct reskia_size_t reskia_size_t;
typedef struct reskia_vector_t reskia_vector_t;
typedef int32_t reskia_matrix_type_mask_t;
typedef int32_t reskia_matrix_scale_to_fit_t;
typedef int32_t reskia_matrix_apply_perspective_clip_t;

reskia_matrix_t *SkMatrix_new(reskia_matrix_t *matrix); // copy constructor. Returns NULL for NULL input.
void SkMatrix_delete(reskia_matrix_t *matrix); // No-op for NULL input.
reskia_matrix_type_mask_t SkMatrix_getType(reskia_matrix_t *matrix); // Returns -1 for NULL input.
bool SkMatrix_isIdentity(reskia_matrix_t *matrix); // Returns false for NULL input.
bool SkMatrix_isScaleTranslate(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_isTranslate(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_rectStaysRect(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_preservesAxisAlignment(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_hasPerspective(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_isSimilarity(reskia_matrix_t *matrix, float tol); // (SkMatrix *matrix, SkScalar tol) -> bool
bool SkMatrix_preservesRightAngles(reskia_matrix_t *matrix, float tol); // (SkMatrix *matrix, SkScalar tol) -> bool
float SkMatrix_get(reskia_matrix_t *matrix, int index); // index must be 0..8. Returns 0 for NULL/out-of-range input.
float SkMatrix_rc(reskia_matrix_t *matrix, int r, int c); // r and c must be 0..2. Returns 0 for NULL/out-of-range input.
float SkMatrix_getScaleX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getScaleY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getSkewY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getSkewX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getTranslateX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getTranslateY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getPerspX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getPerspY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
sk_matrix_t SkMatrix_set(reskia_matrix_t *matrix, int index, float value); // index must be 0..8. Returns 0 for NULL/out-of-range input.
sk_matrix_t SkMatrix_setScaleX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setScaleY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setSkewY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setSkewX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setTranslateX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setTranslateY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setPerspX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setPerspY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setAll(reskia_matrix_t *matrix, float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float persp0, float persp1, float persp2); // (SkMatrix *matrix, SkScalar scaleX, SkScalar skewX, SkScalar transX, SkScalar skewY, SkScalar scaleY, SkScalar transY, SkScalar persp0, SkScalar persp1, SkScalar persp2) -> sk_matrix_t
void SkMatrix_get9(reskia_matrix_t *matrix, float *buffer); // buffer must contain at least 9 elements and be non-NULL. No-op for NULL input.
sk_matrix_t SkMatrix_set9(reskia_matrix_t *matrix, const float *buffer); // buffer must contain at least 9 elements and be non-NULL. Returns 0 for NULL input.
sk_matrix_t SkMatrix_reset(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_matrix_t
sk_matrix_t SkMatrix_setIdentity(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_matrix_t
sk_matrix_t SkMatrix_setTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
sk_matrix_t SkMatrix_setTranslateWithVector(reskia_matrix_t *matrix, const reskia_vector_t *v); // v must be non-NULL. Returns 0 for NULL input.
sk_matrix_t SkMatrix_setScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_setScaleXY(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
sk_matrix_t SkMatrix_setRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_setRotateDegrees(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
sk_matrix_t SkMatrix_setSinCos(reskia_matrix_t *matrix, float sinValue, float cosValue, float px, float py); // (SkMatrix *matrix, SkScalar sinValue, SkScalar cosValue, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_setSinCosValues(reskia_matrix_t *matrix, float sinValue, float cosValue); // (SkMatrix *matrix, SkScalar sinValue, SkScalar cosValue) -> sk_matrix_t
sk_matrix_t SkMatrix_setRSXform(reskia_matrix_t *matrix, const reskia_rsxform_t *rsxForm); // rsxForm must be non-NULL. Returns 0 for NULL input.
sk_matrix_t SkMatrix_setSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_setSkewXY(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
sk_matrix_t SkMatrix_setConcat(reskia_matrix_t *matrix, const reskia_matrix_t *a, const reskia_matrix_t *b); // a and b must be non-NULL. Returns 0 for NULL input.
sk_matrix_t SkMatrix_preTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
sk_matrix_t SkMatrix_preScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_preScaleXY(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
sk_matrix_t SkMatrix_preRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_preRotateDegrees(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
sk_matrix_t SkMatrix_preSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_preSkewXY(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
sk_matrix_t SkMatrix_preConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other); // other must be non-NULL. Returns 0 for NULL input.
sk_matrix_t SkMatrix_postTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
sk_matrix_t SkMatrix_postScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_postScaleXY(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
sk_matrix_t SkMatrix_postRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_postRotateDegrees(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
sk_matrix_t SkMatrix_postSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_postSkewXY(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
sk_matrix_t SkMatrix_postConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other); // other must be non-NULL. Returns 0 for NULL input.
/**
 * src and dst must be non-NULL. Returns false for NULL input.
 */
bool SkMatrix_setRectToRect(reskia_matrix_t *matrix, const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t stf);
/**
 * count must be 0..4. src and dst must be non-NULL when count > 0. Returns false for invalid input.
 */
bool SkMatrix_setPolyToPoly(reskia_matrix_t *matrix, const reskia_point_t *src, const reskia_point_t *dst, int count);
sk_matrix_t SkMatrix_PolyToPoly(const reskia_point_t *src, const reskia_point_t *dst, int count); // count must be 0..4. Returns 0 for invalid/unsolvable input.
bool SkMatrix_invert(reskia_matrix_t *matrix, reskia_matrix_t *inverse); // inverse may be NULL. Returns false when matrix is NULL.
bool SkMatrix_asAffine(reskia_matrix_t *matrix, float *affine); // affine must contain at least 6 elements and be non-NULL. Returns false for NULL input.
sk_matrix_t SkMatrix_setAffine(reskia_matrix_t *matrix, const float *affine); // affine must contain at least 6 elements and be non-NULL. Returns 0 for NULL input.
void SkMatrix_normalizePerspective(reskia_matrix_t *matrix); // No-op for NULL input.
/**
 * dst and src must contain at least count elements. No-op when count <= 0 or input is NULL.
 */
void SkMatrix_mapPoints(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_point_t *src, int count);
void SkMatrix_mapPointsInPlace(reskia_matrix_t *matrix, reskia_point_t *pts, int count); // pts must contain at least count elements. No-op when count <= 0 or input is NULL.
/**
 * dst and src must contain at least count elements. No-op when count <= 0 or input is NULL.
 */
void SkMatrix_mapHomogeneousPoints(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point3_t *src, int count);
void SkMatrix_mapHomogeneousPoint(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point3_t *src); // dst and src must be non-NULL. No-op for NULL input.
/**
 * dst and src must contain at least count elements. No-op when count <= 0 or input is NULL.
 */
void SkMatrix_mapHomogeneousPointsFromPoints(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src, int count);
void SkMatrix_mapPointsToHomogeneous(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src, int count);
void SkMatrix_mapPointToHomogeneous(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src); // dst and src must be non-NULL. No-op for NULL input.
sk_point_t SkMatrix_mapPoint(reskia_matrix_t *matrix, sk_point_t pt); // (SkMatrix *matrix, sk_point_t pt) -> sk_point_t
sk_point_t SkMatrix_mapPointAffine(reskia_matrix_t *matrix, sk_point_t pt); // Returns 0 for NULL input.
sk_point_t SkMatrix_mapXYToPoint(reskia_matrix_t *matrix, float x, float y); // (SkMatrix *matrix, SkScalar x, SkScalar y) -> sk_point_t
sk_point_t SkMatrix_mapOrigin(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_point_t
/**
 * dst and src must contain at least count elements. No-op when count <= 0 or input is NULL.
 */
void SkMatrix_mapVectors(reskia_matrix_t *matrix, reskia_vector_t *dst, const reskia_vector_t *src, int count);
void SkMatrix_mapVectorsInPlace(reskia_matrix_t *matrix, reskia_vector_t *vecs, int count); // vecs must contain at least count elements. No-op when count <= 0 or input is NULL.
void SkMatrix_mapVector(reskia_matrix_t *matrix, float dx, float dy, reskia_vector_t *result); // result must be non-NULL. No-op for NULL input.
sk_point_t SkMatrix_mapVectorToPoint(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_point_t
/**
 * dst and src must be non-NULL. Returns false for NULL input.
 */
bool SkMatrix_mapRect(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src, reskia_matrix_apply_perspective_clip_t pc);
bool SkMatrix_mapRectInPlace(reskia_matrix_t *matrix, reskia_rect_t *rect, reskia_matrix_apply_perspective_clip_t pc); // rect must be non-NULL. Returns false for NULL input.
/**
 * src must be non-NULL. Returns empty rect handle for NULL input.
 */
sk_rect_t SkMatrix_mapRectFromSource(reskia_matrix_t *matrix, const reskia_rect_t *src, reskia_matrix_apply_perspective_clip_t pc);
void SkMatrix_mapRectToQuad(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_rect_t *rect); // dst must contain at least 4 elements and rect must be non-NULL. No-op for NULL input.
void SkMatrix_mapRectScaleTranslate(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src); // dst and src must be non-NULL. No-op for NULL input.
float SkMatrix_mapRadius(reskia_matrix_t *matrix, float radius); // (SkMatrix *matrix, SkScalar radius) -> SkScalar
void SkMatrix_dump(reskia_matrix_t *matrix); // (SkMatrix *matrix)
float SkMatrix_getMinScale(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getMaxScale(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
bool SkMatrix_getMinMaxScales(reskia_matrix_t *matrix, float *scaleFactors); // scaleFactors must contain at least 2 elements and be non-NULL. Returns false for NULL input.
bool SkMatrix_decomposeScale(reskia_matrix_t *matrix, reskia_size_t *scale, reskia_matrix_t *remaining); // scale must be non-NULL. remaining may be NULL. Returns false for NULL input.
void SkMatrix_dirtyMatrixTypeCache(reskia_matrix_t *matrix); // No-op for NULL input.
void SkMatrix_setScaleTranslate(reskia_matrix_t *matrix, float sx, float sy, float tx, float ty); // No-op for NULL input.
bool SkMatrix_isFinite(reskia_matrix_t *matrix); // Returns false for NULL input.

// static

sk_matrix_t SkMatrix_Scale(float sx, float sy); // (SkScalar sx, SkScalar sy) -> sk_matrix_t
sk_matrix_t SkMatrix_ScaleTranslate(float sx, float sy, float tx, float ty); // (SkScalar sx, SkScalar sy, SkScalar tx, SkScalar ty) -> sk_matrix_t
sk_matrix_t SkMatrix_Translate(float dx, float dy); // (SkScalar dx, SkScalar dy) -> sk_matrix_t
sk_matrix_t SkMatrix_TranslateFromPoint(sk_point_t t); // (sk_point_t t) -> sk_matrix_t
sk_matrix_t SkMatrix_TranslateFromIPoint(sk_i_point_t t); // (sk_i_point_t t) -> sk_matrix_t
sk_matrix_t SkMatrix_RotateDeg(float deg); // (SkScalar deg) -> sk_matrix_t
sk_matrix_t SkMatrix_RotateDegAroundPoint(float deg, sk_point_t pt); // (SkScalar deg, sk_point_t pt) -> sk_matrix_t
sk_matrix_t SkMatrix_RotateRad(float rad); // (SkScalar rad) -> sk_matrix_t
sk_matrix_t SkMatrix_Skew(float kx, float ky); // (SkScalar kx, SkScalar ky) -> sk_matrix_t
bool SkMatrix_Rect2Rect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t mode, reskia_matrix_t *result); // src, dst, and result must be non-NULL. Returns false for invalid input.
sk_matrix_t SkMatrix_RectToRectOrIdentity(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t mode); // Returns identity when src or dst is NULL.
sk_matrix_t SkMatrix_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t mode); // src and dst must be non-NULL. Returns 0 for NULL input.
sk_matrix_t SkMatrix_MakeAll(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float pers0, float pers1, float pers2); // (SkScalar scaleX, SkScalar skewX, SkScalar transX, SkScalar skewY, SkScalar scaleY, SkScalar transY, SkScalar pers0, SkScalar pers1, SkScalar pers2) -> sk_matrix_t
sk_matrix_t SkMatrix_MakeRectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t stf); // src and dst must be non-NULL. Returns 0 for NULL input.
void SkMatrix_SetAffineIdentity(float *affine); // affine must contain at least 6 elements and be non-NULL. No-op for NULL input.
sk_matrix_t SkMatrix_I(); // () -> sk_matrix_t
sk_matrix_t SkMatrix_InvalidMatrix(); // () -> sk_matrix_t
sk_matrix_t SkMatrix_Concat(const reskia_matrix_t *a, const reskia_matrix_t *b); // a and b must be non-NULL. Returns 0 for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MATRIX_H
