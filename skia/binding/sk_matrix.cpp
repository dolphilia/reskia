//
// Created by dolphilia on 2024/01/09.
//

#include "sk_matrix.h"

#include "include/core/SkMatrix.h"

#include "../static/static_sk_matrix.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_point.h"
#include "../static/static_sk_i_point.h"

#include "../static/static_sk_i_point-internal.h"
#include "../static/static_sk_matrix-internal.h"
#include "../static/static_sk_point-internal.h"
#include "../static/static_sk_rect-internal.h"

extern "C" {

// SkScalar operator[](int index)
// SkScalar & operator[](int index)

reskia_matrix_t *SkMatrix_new(reskia_matrix_t *matrix) {
    return reinterpret_cast<reskia_matrix_t *>(new SkMatrix(*reinterpret_cast<SkMatrix *>(matrix)));
}

void SkMatrix_delete(reskia_matrix_t *matrix) {
    delete reinterpret_cast<SkMatrix *>(matrix);
}

reskia_matrix_type_mask_t SkMatrix_getType(reskia_matrix_t *matrix) {
    return static_cast<reskia_matrix_type_mask_t>(reinterpret_cast<SkMatrix *>(matrix)->getType());
}

bool SkMatrix_isIdentity(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->isIdentity();
}

bool SkMatrix_isScaleTranslate(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->isScaleTranslate();
}

bool SkMatrix_isTranslate(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->isTranslate();
}

bool SkMatrix_rectStaysRect(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->rectStaysRect();
}

bool SkMatrix_preservesAxisAlignment(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->preservesAxisAlignment();
}

bool SkMatrix_hasPerspective(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->hasPerspective();
}

bool SkMatrix_isSimilarity(reskia_matrix_t *matrix, float tol) {
    return reinterpret_cast<SkMatrix *>(matrix)->isSimilarity(tol);
}

bool SkMatrix_preservesRightAngles(reskia_matrix_t *matrix, float tol) {
    return reinterpret_cast<SkMatrix *>(matrix)->preservesRightAngles(tol);
}

float SkMatrix_get(reskia_matrix_t *matrix, int index) {
    return reinterpret_cast<SkMatrix *>(matrix)->get(index);
}

float SkMatrix_rc(reskia_matrix_t *matrix, int r, int c) {
    return reinterpret_cast<SkMatrix *>(matrix)->rc(r, c);
}

float SkMatrix_getScaleX(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getScaleX();
}

float SkMatrix_getScaleY(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getScaleY();
}

float SkMatrix_getSkewY(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getSkewY();
}

float SkMatrix_getSkewX(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getSkewX();
}

float SkMatrix_getTranslateX(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getTranslateX();
}

float SkMatrix_getTranslateY(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getTranslateY();
}

float SkMatrix_getPerspX(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getPerspX();
}

float SkMatrix_getPerspY(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getPerspY();
}

sk_matrix_t SkMatrix_set(reskia_matrix_t *matrix, int index, float value) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->set(index, value));
}

sk_matrix_t SkMatrix_setScaleX(reskia_matrix_t *matrix, float v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setScaleX(v));
}

sk_matrix_t SkMatrix_setScaleY(reskia_matrix_t *matrix, float v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setScaleY(v));
}

sk_matrix_t SkMatrix_setSkewY(reskia_matrix_t *matrix, float v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSkewY(v));
}

sk_matrix_t SkMatrix_setSkewX(reskia_matrix_t *matrix, float v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSkewX(v));
}

sk_matrix_t SkMatrix_setTranslateX(reskia_matrix_t *matrix, float v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setTranslateX(v));
}

sk_matrix_t SkMatrix_setTranslateY(reskia_matrix_t *matrix, float v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setTranslateY(v));
}

sk_matrix_t SkMatrix_setPerspX(reskia_matrix_t *matrix, float v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setPerspX(v));
}

sk_matrix_t SkMatrix_setPerspY(reskia_matrix_t *matrix, float v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setPerspY(v));
}

sk_matrix_t SkMatrix_setAll(reskia_matrix_t *matrix, float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float persp0, float persp1, float persp2) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setAll(scaleX, skewX, transX, skewY, scaleY, transY, persp0, persp1, persp2));
}

void SkMatrix_get9(reskia_matrix_t *matrix, float *buffer) {
    reinterpret_cast<SkMatrix *>(matrix)->get9(buffer);
}

sk_matrix_t SkMatrix_set9(reskia_matrix_t *matrix, const float *buffer) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->set9(buffer));
}

sk_matrix_t SkMatrix_reset(reskia_matrix_t *matrix) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->reset());
}

sk_matrix_t SkMatrix_setIdentity(reskia_matrix_t *matrix) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setIdentity());
}

sk_matrix_t SkMatrix_setTranslate(reskia_matrix_t *matrix, float dx, float dy) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setTranslate(dx, dy));
}

sk_matrix_t SkMatrix_setTranslate_2(reskia_matrix_t *matrix, const reskia_vector_t *v) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setTranslate(* reinterpret_cast<const SkVector *>(v)));
}

sk_matrix_t SkMatrix_setScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_setScale_2(reskia_matrix_t *matrix, float sx, float sy) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setScale(sx, sy));
}

sk_matrix_t SkMatrix_setRotate(reskia_matrix_t *matrix, float degrees, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_setRotate_2(reskia_matrix_t *matrix, float degrees) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setRotate(degrees));
}

sk_matrix_t SkMatrix_setSinCos(reskia_matrix_t *matrix, float sinValue, float cosValue, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSinCos(sinValue, cosValue, px, py));
}

sk_matrix_t SkMatrix_setSinCos_2(reskia_matrix_t *matrix, float sinValue, float cosValue) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSinCos(sinValue, cosValue));
}

sk_matrix_t SkMatrix_setRSXform(reskia_matrix_t *matrix, const reskia_rsxform_t *rsxForm) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setRSXform(*reinterpret_cast<const SkRSXform *>(rsxForm)));
}

sk_matrix_t SkMatrix_setSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_setSkew_2(reskia_matrix_t *matrix, float kx, float ky) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSkew(kx, ky));
}

sk_matrix_t SkMatrix_setConcat(reskia_matrix_t *matrix, const reskia_matrix_t *a, const reskia_matrix_t *b) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setConcat(*reinterpret_cast<const SkMatrix *>(a), *reinterpret_cast<const SkMatrix *>(b)));
}

sk_matrix_t SkMatrix_preTranslate(reskia_matrix_t *matrix, float dx, float dy) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preTranslate(dx, dy));
}

sk_matrix_t SkMatrix_preScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_preScale_2(reskia_matrix_t *matrix, float sx, float sy) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preScale(sx, sy));
}

sk_matrix_t SkMatrix_preRotate(reskia_matrix_t *matrix, float degrees, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_preRotate_2(reskia_matrix_t *matrix, float degrees) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preRotate(degrees));
}

sk_matrix_t SkMatrix_preSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_preSkew_2(reskia_matrix_t *matrix, float kx, float ky) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preSkew(kx, ky));
}

sk_matrix_t SkMatrix_preConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preConcat(*reinterpret_cast<const SkMatrix *>(other)));
}

sk_matrix_t SkMatrix_postTranslate(reskia_matrix_t *matrix, float dx, float dy) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postTranslate(dx, dy));
}

sk_matrix_t SkMatrix_postScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_postScale_2(reskia_matrix_t *matrix, float sx, float sy) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postScale(sx, sy));
}

sk_matrix_t SkMatrix_postRotate(reskia_matrix_t *matrix, float degrees, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_postRotate_2(reskia_matrix_t *matrix, float degrees) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postRotate(degrees));
}

sk_matrix_t SkMatrix_postSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_postSkew_2(reskia_matrix_t *matrix, float kx, float ky) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postSkew(kx, ky));
}

sk_matrix_t SkMatrix_postConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postConcat(*reinterpret_cast<const SkMatrix *>(other)));
}

bool SkMatrix_setRectToRect(reskia_matrix_t *matrix, const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t stf) {
    return reinterpret_cast<SkMatrix *>(matrix)->setRectToRect(* reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(stf));
}

bool SkMatrix_setPolyToPoly(reskia_matrix_t *matrix, const reskia_point_t *src, const reskia_point_t *dst, int count) {
    return reinterpret_cast<SkMatrix *>(matrix)->setPolyToPoly(reinterpret_cast<const SkPoint *>(src), reinterpret_cast<const SkPoint *>(dst), count);
}

bool SkMatrix_invert(reskia_matrix_t *matrix, reskia_matrix_t *inverse) {
    return reinterpret_cast<SkMatrix *>(matrix)->invert(reinterpret_cast<SkMatrix *>(inverse));
}

bool SkMatrix_asAffine(reskia_matrix_t *matrix, float *affine) {
    return reinterpret_cast<SkMatrix *>(matrix)->asAffine(static_cast<SkScalar *>(affine));
}

sk_matrix_t SkMatrix_setAffine(reskia_matrix_t *matrix, const float *affine) {
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setAffine(static_cast<const SkScalar *>(affine)));
}

void SkMatrix_normalizePerspective(reskia_matrix_t *matrix) {
    reinterpret_cast<SkMatrix *>(matrix)->normalizePerspective();
}

void SkMatrix_mapPoints(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_point_t *src, int count) {
    reinterpret_cast<SkMatrix *>(matrix)->mapPoints(reinterpret_cast<SkPoint *>(dst), reinterpret_cast<const SkPoint *>(src), count);
}

void SkMatrix_mapPoints_2(reskia_matrix_t *matrix, reskia_point_t *pts, int count) {
    reinterpret_cast<SkMatrix *>(matrix)->mapPoints(reinterpret_cast<SkPoint *>(pts), count);
}

void SkMatrix_mapHomogeneousPoints(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point3_t *src, int count) {
    reinterpret_cast<SkMatrix *>(matrix)->mapHomogeneousPoints(reinterpret_cast<SkPoint3 *>(dst), reinterpret_cast<const SkPoint3 *>(src), count);
}

void SkMatrix_mapHomogeneousPoints_2(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src, int count) {
    reinterpret_cast<SkMatrix *>(matrix)->mapHomogeneousPoints(reinterpret_cast<SkPoint3 *>(dst), reinterpret_cast<const SkPoint *>(src), count);
}

sk_point_t SkMatrix_mapPoint(reskia_matrix_t *matrix, sk_point_t pt) {
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapPoint(static_sk_point_get_entity(pt)));
}

void SkMatrix_mapXY(reskia_matrix_t *matrix, float x, float y, reskia_point_t *result) {
    reinterpret_cast<SkMatrix *>(matrix)->mapXY(x, y, reinterpret_cast<SkPoint *>(result));
}

sk_point_t SkMatrix_mapXY_2(reskia_matrix_t *matrix, float x, float y) {
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapXY(x, y));
}

sk_point_t SkMatrix_mapOrigin(reskia_matrix_t *matrix) {
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapOrigin());
}

void SkMatrix_mapVectors(reskia_matrix_t *matrix, reskia_vector_t *dst, const reskia_vector_t *src, int count) {
    reinterpret_cast<SkMatrix *>(matrix)->mapVectors(reinterpret_cast<SkVector *>(dst), reinterpret_cast<const SkVector *>(src), count);
}

void SkMatrix_mapVectors_2(reskia_matrix_t *matrix, reskia_vector_t *vecs, int count) {
    reinterpret_cast<SkMatrix *>(matrix)->mapVectors(reinterpret_cast<SkVector *>(vecs), count);
}

void SkMatrix_mapVector(reskia_matrix_t *matrix, float dx, float dy, reskia_vector_t *result) {
    reinterpret_cast<SkMatrix *>(matrix)->mapVector(dx, dy, reinterpret_cast<SkVector *>(result));
}

sk_point_t SkMatrix_mapVector_2(reskia_matrix_t *matrix, float dx, float dy) {
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapVector(dx, dy));
}

bool SkMatrix_mapRect(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src, reskia_matrix_apply_perspective_clip_t pc) {
    return reinterpret_cast<SkMatrix *>(matrix)->mapRect(reinterpret_cast<SkRect *>(dst), * reinterpret_cast<const SkRect *>(src), static_cast<SkApplyPerspectiveClip>(pc));
}

bool SkMatrix_mapRect_2(reskia_matrix_t *matrix, reskia_rect_t *rect, reskia_matrix_apply_perspective_clip_t pc) {
    return reinterpret_cast<SkMatrix *>(matrix)->mapRect(reinterpret_cast<SkRect *>(rect), static_cast<SkApplyPerspectiveClip>(pc));
}

sk_rect_t SkMatrix_mapRect_3(reskia_matrix_t *matrix, const reskia_rect_t *src, reskia_matrix_apply_perspective_clip_t pc) {
    return static_sk_rect_make(reinterpret_cast<SkMatrix *>(matrix)->mapRect(*reinterpret_cast<const SkRect *>(src), static_cast<SkApplyPerspectiveClip>(pc)));
}

void SkMatrix_mapRectToQuad(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_rect_t *rect) {
    reinterpret_cast<SkMatrix *>(matrix)->mapRectToQuad(reinterpret_cast<SkPoint *>(dst), * reinterpret_cast<const SkRect *>(rect));
}

void SkMatrix_mapRectScaleTranslate(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src) {
    reinterpret_cast<SkMatrix *>(matrix)->mapRectScaleTranslate(reinterpret_cast<SkRect *>(dst), * reinterpret_cast<const SkRect *>(src));
}

float SkMatrix_mapRadius(reskia_matrix_t *matrix, float radius) {
    return reinterpret_cast<SkMatrix *>(matrix)->mapRadius(radius);
}

void SkMatrix_dump(reskia_matrix_t *matrix) {
    reinterpret_cast<SkMatrix *>(matrix)->dump();
}

float SkMatrix_getMinScale(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getMinScale();
}

float SkMatrix_getMaxScale(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->getMaxScale();
}

bool SkMatrix_getMinMaxScales(reskia_matrix_t *matrix, float *scaleFactors) {
    return reinterpret_cast<SkMatrix *>(matrix)->getMinMaxScales(static_cast<SkScalar *>(scaleFactors));
}

bool SkMatrix_decomposeScale(reskia_matrix_t *matrix, reskia_size_t *scale, reskia_matrix_t *remaining) {
    return reinterpret_cast<SkMatrix *>(matrix)->decomposeScale(reinterpret_cast<SkSize *>(scale), reinterpret_cast<SkMatrix *>(remaining));
}

void SkMatrix_dirtyMatrixTypeCache(reskia_matrix_t *matrix) {
    reinterpret_cast<SkMatrix *>(matrix)->dirtyMatrixTypeCache();
}

void SkMatrix_setScaleTranslate(reskia_matrix_t *matrix, float sx, float sy, float tx, float ty) {
    reinterpret_cast<SkMatrix *>(matrix)->setScaleTranslate(sx, sy, tx, ty);
}

bool SkMatrix_isFinite(reskia_matrix_t *matrix) {
    return reinterpret_cast<SkMatrix *>(matrix)->isFinite();
}


// static

sk_matrix_t SkMatrix_Scale(float sx, float sy) {
    return static_sk_matrix_make(SkMatrix::Scale(sx, sy));
}

sk_matrix_t SkMatrix_Translate(float dx, float dy) {
    return static_sk_matrix_make(SkMatrix::Translate(dx, dy));
}

sk_matrix_t SkMatrix_Translate_2(sk_point_t t) {
    return static_sk_matrix_make(SkMatrix::Translate(static_sk_point_get_entity(t)));
}

sk_matrix_t SkMatrix_Translate_3(sk_i_point_t t) {
    return static_sk_matrix_make(SkMatrix::Translate(static_sk_i_point_get_entity(t)));
}

sk_matrix_t SkMatrix_RotateDeg(float deg) {
    return static_sk_matrix_make(SkMatrix::RotateDeg(deg));
}

sk_matrix_t SkMatrix_RotateDeg_2(float deg, sk_point_t pt) {
    return static_sk_matrix_make(SkMatrix::RotateDeg(deg, static_sk_point_get_entity(pt)));
}

sk_matrix_t SkMatrix_RotateRad(float rad) {
    return static_sk_matrix_make(SkMatrix::RotateRad(rad));
}

sk_matrix_t SkMatrix_Skew(float kx, float ky) {
    return static_sk_matrix_make(SkMatrix::Skew(kx, ky));
}

sk_matrix_t SkMatrix_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t mode) {
    return static_sk_matrix_make(SkMatrix::RectToRect(* reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(mode)));
}

sk_matrix_t SkMatrix_MakeAll(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float pers0, float pers1, float pers2) {
    return static_sk_matrix_make(SkMatrix::MakeAll(scaleX, skewX, transX, skewY, scaleY, transY, pers0, pers1, pers2));
}

sk_matrix_t SkMatrix_MakeRectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t stf) {
    return static_sk_matrix_make(SkMatrix::MakeRectToRect(* reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(stf)));
}

void SkMatrix_SetAffineIdentity(float *affine) {
    SkMatrix::SetAffineIdentity(static_cast<SkScalar *>(affine));
}

sk_matrix_t SkMatrix_I() {
    return static_sk_matrix_make(SkMatrix::I());
}

sk_matrix_t SkMatrix_InvalidMatrix() {
    return static_sk_matrix_make(SkMatrix::InvalidMatrix());
}

sk_matrix_t SkMatrix_Concat(const reskia_matrix_t *a, const reskia_matrix_t *b) {
    return static_sk_matrix_make(SkMatrix::Concat(* reinterpret_cast<const SkMatrix *>(a), * reinterpret_cast<const SkMatrix *>(b)));
}

}
