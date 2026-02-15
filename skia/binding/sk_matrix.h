//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_MATRIX_H
#define RAIA_SKIA_SK_MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_point3_t reskia_point3_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_rsxform_t reskia_rsxform_t;
typedef struct reskia_size_t reskia_size_t;
typedef struct reskia_vector_t reskia_vector_t;

// SkScalar operator[](int index)
// SkScalar & operator[](int index)

reskia_matrix_t *SkMatrix_new(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkMatrix *
void SkMatrix_delete(reskia_matrix_t *matrix); // (SkMatrix *matrix)
int SkMatrix_getType(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkMatrix::TypeMask
bool SkMatrix_isIdentity(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_isScaleTranslate(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_isTranslate(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_rectStaysRect(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_preservesAxisAlignment(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_hasPerspective(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool
bool SkMatrix_isSimilarity(reskia_matrix_t *matrix, float tol); // (SkMatrix *matrix, SkScalar tol) -> bool
bool SkMatrix_preservesRightAngles(reskia_matrix_t *matrix, float tol); // (SkMatrix *matrix, SkScalar tol) -> bool
float SkMatrix_get(reskia_matrix_t *matrix, int index); // (SkMatrix *matrix, int index) -> SkScalar
float SkMatrix_rc(reskia_matrix_t *matrix, int r, int c); // (SkMatrix *matrix, int r, int c) -> SkScalar
float SkMatrix_getScaleX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getScaleY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getSkewY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getSkewX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getTranslateX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getTranslateY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getPerspX(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getPerspY(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
int SkMatrix_set(reskia_matrix_t *matrix, int index, float value); // (SkMatrix *matrix, int index, SkScalar value) -> sk_matrix_t
int SkMatrix_setScaleX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
int SkMatrix_setScaleY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
int SkMatrix_setSkewY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
int SkMatrix_setSkewX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
int SkMatrix_setTranslateX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
int SkMatrix_setTranslateY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
int SkMatrix_setPerspX(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
int SkMatrix_setPerspY(reskia_matrix_t *matrix, float v); // (SkMatrix *matrix, SkScalar v) -> sk_matrix_t
int SkMatrix_setAll(reskia_matrix_t *matrix, float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float persp0, float persp1, float persp2); // (SkMatrix *matrix, SkScalar scaleX, SkScalar skewX, SkScalar transX, SkScalar skewY, SkScalar scaleY, SkScalar transY, SkScalar persp0, SkScalar persp1, SkScalar persp2) -> sk_matrix_t
void SkMatrix_get9(reskia_matrix_t *matrix, float *buffer); // (SkMatrix *matrix, SkScalar buffer[9])
int SkMatrix_set9(reskia_matrix_t *matrix, const float *buffer); // (SkMatrix *matrix, const SkScalar buffer[9]) -> sk_matrix_t
int SkMatrix_reset(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_matrix_t
int SkMatrix_setIdentity(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_matrix_t
int SkMatrix_setTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
int SkMatrix_setTranslate_2(reskia_matrix_t *matrix, const reskia_vector_t *v); // (SkMatrix *matrix, const SkVector *v) -> sk_matrix_t
int SkMatrix_setScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_setScale_2(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
int SkMatrix_setRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_setRotate_2(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
int SkMatrix_setSinCos(reskia_matrix_t *matrix, float sinValue, float cosValue, float px, float py); // (SkMatrix *matrix, SkScalar sinValue, SkScalar cosValue, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_setSinCos_2(reskia_matrix_t *matrix, float sinValue, float cosValue); // (SkMatrix *matrix, SkScalar sinValue, SkScalar cosValue) -> sk_matrix_t
int SkMatrix_setRSXform(reskia_matrix_t *matrix, const reskia_rsxform_t *rsxForm); // (SkMatrix *matrix, const SkRSXform *rsxForm) -> sk_matrix_t
int SkMatrix_setSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_setSkew_2(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
int SkMatrix_setConcat(reskia_matrix_t *matrix, const reskia_matrix_t *a, const reskia_matrix_t *b); // (SkMatrix *matrix, const SkMatrix *a, const SkMatrix *b) -> sk_matrix_t
int SkMatrix_preTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
int SkMatrix_preScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_preScale_2(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
int SkMatrix_preRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_preRotate_2(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
int SkMatrix_preSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_preSkew_2(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
int SkMatrix_preConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other); // (SkMatrix *matrix, const SkMatrix *other) -> sk_matrix_t
int SkMatrix_postTranslate(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_matrix_t
int SkMatrix_postScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_postScale_2(reskia_matrix_t *matrix, float sx, float sy); // (SkMatrix *matrix, SkScalar sx, SkScalar sy) -> sk_matrix_t
int SkMatrix_postRotate(reskia_matrix_t *matrix, float degrees, float px, float py); // (SkMatrix *matrix, SkScalar degrees, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_postRotate_2(reskia_matrix_t *matrix, float degrees); // (SkMatrix *matrix, SkScalar degrees) -> sk_matrix_t
int SkMatrix_postSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py); // (SkMatrix *matrix, SkScalar kx, SkScalar ky, SkScalar px, SkScalar py) -> sk_matrix_t
int SkMatrix_postSkew_2(reskia_matrix_t *matrix, float kx, float ky); // (SkMatrix *matrix, SkScalar kx, SkScalar ky) -> sk_matrix_t
int SkMatrix_postConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other); // (SkMatrix *matrix, const SkMatrix *other) -> sk_matrix_t
bool SkMatrix_setRectToRect(reskia_matrix_t *matrix, const reskia_rect_t *src, const reskia_rect_t *dst, int stf); // (SkMatrix *matrix, const SkRect *src, const SkRect *dst, SkMatrix::ScaleToFit stf) -> bool
bool SkMatrix_setPolyToPoly(reskia_matrix_t *matrix, const reskia_point_t *src, const reskia_point_t *dst, int count); // (SkMatrix *matrix, const SkPoint src[], const SkPoint dst[], int count) -> bool
bool SkMatrix_invert(reskia_matrix_t *matrix, reskia_matrix_t *inverse); // (SkMatrix *matrix, SkMatrix *inverse) -> bool
bool SkMatrix_asAffine(reskia_matrix_t *matrix, float *affine); // (SkMatrix *matrix, SkScalar affine[6]) -> bool
int SkMatrix_setAffine(reskia_matrix_t *matrix, const float *affine); // (SkMatrix *matrix, const SkScalar affine[6]) -> sk_matrix_t
void SkMatrix_normalizePerspective(reskia_matrix_t *matrix); // (SkMatrix *matrix)
void SkMatrix_mapPoints(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_point_t *src, int count); // (SkMatrix *matrix, SkPoint dst[], const SkPoint src[], int count)
void SkMatrix_mapPoints_2(reskia_matrix_t *matrix, reskia_point_t *pts, int count); // (SkMatrix *matrix, SkPoint pts[], int count)
void SkMatrix_mapHomogeneousPoints(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point3_t *src, int count); // (SkMatrix *matrix, SkPoint3 dst[], const SkPoint3 src[], int count)
void SkMatrix_mapHomogeneousPoints_2(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src, int count); // (SkMatrix *matrix, SkPoint3 dst[], const SkPoint src[], int count)
int SkMatrix_mapPoint(reskia_matrix_t *matrix, int pt); // (SkMatrix *matrix, sk_point_t pt) -> sk_point_t
void SkMatrix_mapXY(reskia_matrix_t *matrix, float x, float y, reskia_point_t *result); // (SkMatrix *matrix, SkScalar x, SkScalar y, SkPoint *result)
int SkMatrix_mapXY_2(reskia_matrix_t *matrix, float x, float y); // (SkMatrix *matrix, SkScalar x, SkScalar y) -> sk_point_t
int SkMatrix_mapOrigin(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> sk_point_t
void SkMatrix_mapVectors(reskia_matrix_t *matrix, reskia_vector_t *dst, const reskia_vector_t *src, int count); // (SkMatrix *matrix, SkVector dst[], const SkVector src[], int count)
void SkMatrix_mapVectors_2(reskia_matrix_t *matrix, reskia_vector_t *vecs, int count); // (SkMatrix *matrix, SkVector vecs[], int count)
void SkMatrix_mapVector(reskia_matrix_t *matrix, float dx, float dy, reskia_vector_t *result); // (SkMatrix *matrix, SkScalar dx, SkScalar dy, SkVector *result)
int SkMatrix_mapVector_2(reskia_matrix_t *matrix, float dx, float dy); // (SkMatrix *matrix, SkScalar dx, SkScalar dy) -> sk_point_t
bool SkMatrix_mapRect(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src, int pc); // (SkMatrix *matrix, SkRect *dst, const SkRect *src, SkApplyPerspectiveClip pc) -> bool
bool SkMatrix_mapRect_2(reskia_matrix_t *matrix, reskia_rect_t *rect, int pc); // (SkMatrix *matrix, SkRect *rect, SkApplyPerspectiveClip pc) -> bool
int SkMatrix_mapRect_3(reskia_matrix_t *matrix, const reskia_rect_t *src, int pc); // (SkMatrix *matrix, const SkRect *src, SkApplyPerspectiveClip pc) -> sk_matrix_t
void SkMatrix_mapRectToQuad(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_rect_t *rect); // (SkMatrix *matrix, SkPoint dst[4], const SkRect *rect)
void SkMatrix_mapRectScaleTranslate(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src); // (SkMatrix *matrix, SkRect *dst, const SkRect *src)
float SkMatrix_mapRadius(reskia_matrix_t *matrix, float radius); // (SkMatrix *matrix, SkScalar radius) -> SkScalar
void SkMatrix_dump(reskia_matrix_t *matrix); // (SkMatrix *matrix)
float SkMatrix_getMinScale(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
float SkMatrix_getMaxScale(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> SkScalar
bool SkMatrix_getMinMaxScales(reskia_matrix_t *matrix, float *scaleFactors); // (SkMatrix *matrix, SkScalar scaleFactors[2]) -> bool
bool SkMatrix_decomposeScale(reskia_matrix_t *matrix, reskia_size_t *scale, reskia_matrix_t *remaining); // (SkMatrix *matrix, SkSize *scale, SkMatrix *remaining) -> bool
void SkMatrix_dirtyMatrixTypeCache(reskia_matrix_t *matrix); // (SkMatrix *matrix)
void SkMatrix_setScaleTranslate(reskia_matrix_t *matrix, float sx, float sy, float tx, float ty); // (SkMatrix *matrix, SkScalar sx, SkScalar sy, SkScalar tx, SkScalar ty)
bool SkMatrix_isFinite(reskia_matrix_t *matrix); // (SkMatrix *matrix) -> bool

// static

int SkMatrix_Scale(float sx, float sy); // (SkScalar sx, SkScalar sy) -> sk_matrix_t
int SkMatrix_Translate(float dx, float dy); // (SkScalar dx, SkScalar dy) -> sk_matrix_t
int SkMatrix_Translate_2(int t); // (sk_point_t t) -> sk_matrix_t
int SkMatrix_Translate_3(int t); // (sk_i_point_t t) -> sk_matrix_t
int SkMatrix_RotateDeg(float deg); // (SkScalar deg) -> sk_matrix_t
int SkMatrix_RotateDeg_2(float deg, int pt); // (SkScalar deg, sk_point_t pt) -> sk_matrix_t
int SkMatrix_RotateRad(float rad); // (SkScalar rad) -> sk_matrix_t
int SkMatrix_Skew(float kx, float ky); // (SkScalar kx, SkScalar ky) -> sk_matrix_t
int SkMatrix_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, int mode); // (const SkRect *src, const SkRect *dst, SkMatrix::ScaleToFit mode) -> sk_matrix_t
int SkMatrix_MakeAll(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float pers0, float pers1, float pers2); // (SkScalar scaleX, SkScalar skewX, SkScalar transX, SkScalar skewY, SkScalar scaleY, SkScalar transY, SkScalar pers0, SkScalar pers1, SkScalar pers2) -> sk_matrix_t
int SkMatrix_MakeRectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, int stf); // (const SkRect *src, const SkRect *dst, SkMatrix::ScaleToFit stf) -> sk_matrix_t
void SkMatrix_SetAffineIdentity(float *affine); // (SkScalar affine[6])
int SkMatrix_I(); // () -> sk_matrix_t
int SkMatrix_InvalidMatrix(); // () -> sk_matrix_t
int SkMatrix_Concat(const reskia_matrix_t *a, const reskia_matrix_t *b); // (const SkMatrix *a, const SkMatrix *b) -> sk_matrix_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MATRIX_H
