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

// SkScalar operator[](int index)
// SkScalar & operator[](int index)

reskia_matrix_t *SkMatrix_new(reskia_matrix_t *matrix); // copy constructor。NULL 入力では NULL
void SkMatrix_delete(reskia_matrix_t *matrix); // NULL 入力では no-op
reskia_matrix_type_mask_t SkMatrix_getType(reskia_matrix_t *matrix); // NULL 入力では -1
bool SkMatrix_isIdentity(reskia_matrix_t *matrix); // NULL 入力では false
bool SkMatrix_isScaleTranslate(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_isTranslate(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_rectStaysRect(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_preservesAxisAlignment(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_hasPerspective(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_isSimilarity(reskia_matrix_t *matrix, float tol); // (SkMatrix *matrix, SkScalar tol) -> bool
bool SkMatrix_preservesRightAngles(reskia_matrix_t *matrix, float tol); // (SkMatrix *matrix, SkScalar tol) -> bool
float SkMatrix_get(reskia_matrix_t *matrix, int index); // index は 0..8。NULL/範囲外入力では 0
float SkMatrix_rc(reskia_matrix_t *matrix, int r, int c); // r/c は 0..2。NULL/範囲外入力では 0
float SkMatrix_getScaleX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getScaleY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getSkewY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getSkewX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getTranslateX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getTranslateY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getPerspX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getPerspY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
sk_matrix_t SkMatrix_set(reskia_matrix_t *matrix, int index, float value); // index は 0..8。NULL/範囲外入力では 0
sk_matrix_t SkMatrix_setScaleX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setScaleY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setSkewY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setSkewX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setTranslateX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setTranslateY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setPerspX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setPerspY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
sk_matrix_t SkMatrix_setAll(reskia_matrix_t *matrix, float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float persp0, float persp1, float persp2); // (SkMatrix *matrix, SkScalar scaleX, SkScalar skewX, SkScalar transX, SkScalar skewY, SkScalar scaleY, SkScalar transY, SkScalar persp0, SkScalar persp1, SkScalar persp2) -> sk_matrix_t
void SkMatrix_get9(reskia_matrix_t *matrix, float *buffer); // buffer は 9 要素以上、非 NULL。NULL 入力では no-op
sk_matrix_t SkMatrix_set9(reskia_matrix_t *matrix, const float *buffer); // buffer は 9 要素以上、非 NULL。NULL 入力では 0
sk_matrix_t SkMatrix_reset(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_matrix_t
sk_matrix_t SkMatrix_setIdentity(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_matrix_t
sk_matrix_t SkMatrix_setTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
sk_matrix_t SkMatrix_setTranslateWithVector(reskia_matrix_t *matrix, const reskia_vector_t *v); // v は非 NULL。NULL 入力では 0
sk_matrix_t SkMatrix_setScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_setScaleXY(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
sk_matrix_t SkMatrix_setRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_setRotateDegrees(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
sk_matrix_t SkMatrix_setSinCos(reskia_matrix_t *matrix, float sinValue, float cosValue, float px, float py); // (SkMatrix *matrix, SkScalar sinValue, SkScalar cosValue, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_setSinCosValues(reskia_matrix_t *matrix, float sinValue, float cosValue); // (SkMatrix *matrix, SkScalar sinValue, SkScalar cosValue) -> sk_matrix_t
sk_matrix_t SkMatrix_setRSXform(reskia_matrix_t *matrix, const reskia_rsxform_t *rsxForm); // rsxForm は非 NULL。NULL 入力では 0
sk_matrix_t SkMatrix_setSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_setSkewXY(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
sk_matrix_t SkMatrix_setConcat(reskia_matrix_t *matrix, const reskia_matrix_t *a, const reskia_matrix_t *b); // a/b は非 NULL。NULL 入力では 0
sk_matrix_t SkMatrix_preTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
sk_matrix_t SkMatrix_preScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_preScaleXY(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
sk_matrix_t SkMatrix_preRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_preRotateDegrees(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
sk_matrix_t SkMatrix_preSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_preSkewXY(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
sk_matrix_t SkMatrix_preConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other); // other は非 NULL。NULL 入力では 0
sk_matrix_t SkMatrix_postTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
sk_matrix_t SkMatrix_postScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_postScaleXY(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
sk_matrix_t SkMatrix_postRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_postRotateDegrees(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
sk_matrix_t SkMatrix_postSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
sk_matrix_t SkMatrix_postSkewXY(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
sk_matrix_t SkMatrix_postConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other); // other は非 NULL。NULL 入力では 0
/**
 * src/dst は非 NULL。NULL 入力では false
 */
bool SkMatrix_setRectToRect(reskia_matrix_t *matrix, const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t stf);
/**
 * count は 0..4。count > 0 では src/dst 非 NULL。invalid 入力では false
 */
bool SkMatrix_setPolyToPoly(reskia_matrix_t *matrix, const reskia_point_t *src, const reskia_point_t *dst, int count);
bool SkMatrix_invert(reskia_matrix_t *matrix, reskia_matrix_t *inverse); // inverse は NULL 許可。matrix NULL では false
bool SkMatrix_asAffine(reskia_matrix_t *matrix, float *affine); // affine は 6 要素以上、非 NULL。NULL 入力では false
sk_matrix_t SkMatrix_setAffine(reskia_matrix_t *matrix, const float *affine); // affine は 6 要素以上、非 NULL。NULL 入力では 0
void SkMatrix_normalizePerspective(reskia_matrix_t *matrix); // NULL 入力では no-op
/**
 * dst/src は count 要素以上。count <= 0 や NULL 入力では no-op
 */
void SkMatrix_mapPoints(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_point_t *src, int count);
void SkMatrix_mapPointsInPlace(reskia_matrix_t *matrix, reskia_point_t *pts, int count); // pts は count 要素以上。count <= 0 や NULL 入力では no-op
/**
 * dst/src は count 要素以上。count <= 0 や NULL 入力では no-op
 */
void SkMatrix_mapHomogeneousPoints(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point3_t *src, int count);
void SkMatrix_mapHomogeneousPoint(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point3_t *src); // dst/src は非 NULL。NULL 入力では no-op
/**
 * dst/src は count 要素以上。count <= 0 や NULL 入力では no-op
 */
void SkMatrix_mapHomogeneousPointsFromPoints(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src, int count);
void SkMatrix_mapPointsToHomogeneous(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src, int count);
void SkMatrix_mapPointToHomogeneous(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src); // dst/src は非 NULL。NULL 入力では no-op
sk_point_t SkMatrix_mapPoint(reskia_matrix_t *matrix, sk_point_t pt); // (SkMatrix *matrix, sk_point_t pt) -> sk_point_t
sk_point_t SkMatrix_mapPointAffine(reskia_matrix_t *matrix, sk_point_t pt); // NULL 入力では 0
void SkMatrix_mapXY(reskia_matrix_t *matrix, float x, float y, reskia_point_t *result); // result は非 NULL。NULL 入力では no-op
sk_point_t SkMatrix_mapXYToPoint(reskia_matrix_t *matrix, float x, float y); // (SkMatrix *matrix, SkScalar x, SkScalar y) -> sk_point_t
sk_point_t SkMatrix_mapOrigin(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_point_t
/**
 * dst/src は count 要素以上。count <= 0 や NULL 入力では no-op
 */
void SkMatrix_mapVectors(reskia_matrix_t *matrix, reskia_vector_t *dst, const reskia_vector_t *src, int count);
void SkMatrix_mapVectorsInPlace(reskia_matrix_t *matrix, reskia_vector_t *vecs, int count); // vecs は count 要素以上。count <= 0 や NULL 入力では no-op
void SkMatrix_mapVector(reskia_matrix_t *matrix, float dx, float dy, reskia_vector_t *result); // result は非 NULL。NULL 入力では no-op
sk_point_t SkMatrix_mapVectorToPoint(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_point_t
/**
 * dst/src は非 NULL。NULL 入力では false
 */
bool SkMatrix_mapRect(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src, reskia_matrix_apply_perspective_clip_t pc);
bool SkMatrix_mapRectInPlace(reskia_matrix_t *matrix, reskia_rect_t *rect, reskia_matrix_apply_perspective_clip_t pc); // rect は非 NULL。NULL 入力では false
/**
 * src は非 NULL。NULL 入力では empty rect handle
 */
sk_rect_t SkMatrix_mapRectFromSource(reskia_matrix_t *matrix, const reskia_rect_t *src, reskia_matrix_apply_perspective_clip_t pc);
void SkMatrix_mapRectToQuad(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_rect_t *rect); // dst は 4 要素以上、rect 非 NULL。NULL 入力では no-op
void SkMatrix_mapRectScaleTranslate(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src); // dst/src は非 NULL。NULL 入力では no-op
float SkMatrix_mapRadius(reskia_matrix_t *matrix, float radius); // (SkMatrix *matrix, SkScalar radius) -> SkScalar
void SkMatrix_dump(reskia_matrix_t *matrix); // (SkMatrix *matrix)
float SkMatrix_getMinScale(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getMaxScale(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
bool SkMatrix_getMinMaxScales(reskia_matrix_t *matrix, float *scaleFactors); // scaleFactors は 2 要素以上、非 NULL。NULL 入力では false
bool SkMatrix_decomposeScale(reskia_matrix_t *matrix, reskia_size_t *scale, reskia_matrix_t *remaining); // scale は非 NULL、remaining は NULL 許可。NULL 入力では false
void SkMatrix_dirtyMatrixTypeCache(reskia_matrix_t *matrix); // NULL 入力では no-op
void SkMatrix_setScaleTranslate(reskia_matrix_t *matrix, float sx, float sy, float tx, float ty); // NULL 入力では no-op
bool SkMatrix_isFinite(reskia_matrix_t *matrix); // NULL 入力では false

// static

sk_matrix_t SkMatrix_Scale(float sx, float sy); // (SkScalar sx, SkScalar sy) -> sk_matrix_t
sk_matrix_t SkMatrix_Translate(float dx, float dy); // (SkScalar dx, SkScalar dy) -> sk_matrix_t
sk_matrix_t SkMatrix_TranslateFromPoint(sk_point_t t); // (sk_point_t t) -> sk_matrix_t
sk_matrix_t SkMatrix_TranslateFromIPoint(sk_i_point_t t); // (sk_i_point_t t) -> sk_matrix_t
sk_matrix_t SkMatrix_RotateDeg(float deg); // (SkScalar deg) -> sk_matrix_t
sk_matrix_t SkMatrix_RotateDegAroundPoint(float deg, sk_point_t pt); // (SkScalar deg, sk_point_t pt) -> sk_matrix_t
sk_matrix_t SkMatrix_RotateRad(float rad); // (SkScalar rad) -> sk_matrix_t
sk_matrix_t SkMatrix_Skew(float kx, float ky); // (SkScalar kx, SkScalar ky) -> sk_matrix_t
sk_matrix_t SkMatrix_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t mode); // src/dst は非 NULL。NULL 入力では 0
sk_matrix_t SkMatrix_MakeAll(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float pers0, float pers1, float pers2); // (SkScalar scaleX, SkScalar skewX, SkScalar transX, SkScalar skewY, SkScalar scaleY, SkScalar transY, SkScalar pers0, SkScalar pers1, SkScalar pers2) -> sk_matrix_t
sk_matrix_t SkMatrix_MakeRectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t stf); // src/dst は非 NULL。NULL 入力では 0
void SkMatrix_SetAffineIdentity(float *affine); // affine は 6 要素以上、非 NULL。NULL 入力では no-op
sk_matrix_t SkMatrix_I(); // () -> sk_matrix_t
sk_matrix_t SkMatrix_InvalidMatrix(); // () -> sk_matrix_t
sk_matrix_t SkMatrix_Concat(const reskia_matrix_t *a, const reskia_matrix_t *b); // a/b は非 NULL。NULL 入力では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MATRIX_H
