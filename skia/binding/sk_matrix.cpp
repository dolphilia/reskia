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

void *SkMatrix_new(void *matrix) {
    return new SkMatrix(* static_cast<SkMatrix *>(matrix));
}

void SkMatrix_delete(void *matrix) {
    delete static_cast<SkMatrix *>(matrix);
}

int SkMatrix_getType(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getType();
}

bool SkMatrix_isIdentity(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->isIdentity();
}

bool SkMatrix_isScaleTranslate(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->isScaleTranslate();
}

bool SkMatrix_isTranslate(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->isTranslate();
}

bool SkMatrix_rectStaysRect(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->rectStaysRect();
}

bool SkMatrix_preservesAxisAlignment(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->preservesAxisAlignment();
}

bool SkMatrix_hasPerspective(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->hasPerspective();
}

bool SkMatrix_isSimilarity(void *matrix, float tol) {
    return static_cast<SkMatrix *>(matrix)->isSimilarity(tol);
}

bool SkMatrix_preservesRightAngles(void *matrix, float tol) {
    return static_cast<SkMatrix *>(matrix)->preservesRightAngles(tol);
}

float SkMatrix_get(void *matrix, int index) {
    return static_cast<SkMatrix *>(matrix)->get(index);
}

float SkMatrix_rc(void *matrix, int r, int c) {
    return static_cast<SkMatrix *>(matrix)->rc(r, c);
}

float SkMatrix_getScaleX(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getScaleX();
}

float SkMatrix_getScaleY(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getScaleY();
}

float SkMatrix_getSkewY(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getSkewY();
}

float SkMatrix_getSkewX(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getSkewX();
}

float SkMatrix_getTranslateX(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getTranslateX();
}

float SkMatrix_getTranslateY(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getTranslateY();
}

float SkMatrix_getPerspX(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getPerspX();
}

float SkMatrix_getPerspY(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getPerspY();
}

sk_matrix_t SkMatrix_set(void *matrix, int index, float value) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->set(index, value));
}

sk_matrix_t SkMatrix_setScaleX(void *matrix, float v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setScaleX(v));
}

sk_matrix_t SkMatrix_setScaleY(void *matrix, float v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setScaleY(v));
}

sk_matrix_t SkMatrix_setSkewY(void *matrix, float v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setSkewY(v));
}

sk_matrix_t SkMatrix_setSkewX(void *matrix, float v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setSkewX(v));
}

sk_matrix_t SkMatrix_setTranslateX(void *matrix, float v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setTranslateX(v));
}

sk_matrix_t SkMatrix_setTranslateY(void *matrix, float v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setTranslateY(v));
}

sk_matrix_t SkMatrix_setPerspX(void *matrix, float v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setPerspX(v));
}

sk_matrix_t SkMatrix_setPerspY(void *matrix, float v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setPerspY(v));
}

sk_matrix_t SkMatrix_setAll(void *matrix, float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float persp0, float persp1, float persp2) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setAll(scaleX, skewX, transX, skewY, scaleY, transY, persp0, persp1, persp2));
}

void SkMatrix_get9(void *matrix, void * buffer) {
    static_cast<SkMatrix *>(matrix)->get9(static_cast<SkScalar *>(buffer));
}

sk_matrix_t SkMatrix_set9(void *matrix, const void *buffer) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->set9(static_cast<const SkScalar *>(buffer)));
}

sk_matrix_t SkMatrix_reset(void *matrix) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->reset());
}

sk_matrix_t SkMatrix_setIdentity(void *matrix) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setIdentity());
}

sk_matrix_t SkMatrix_setTranslate(void *matrix, float dx, float dy) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setTranslate(dx, dy));
}

sk_matrix_t SkMatrix_setTranslate_2(void *matrix, const void *v) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setTranslate(* static_cast<const SkVector *>(v)));
}

sk_matrix_t SkMatrix_setScale(void *matrix, float sx, float sy, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_setScale_2(void *matrix, float sx, float sy) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setScale(sx, sy));
}

sk_matrix_t SkMatrix_setRotate(void *matrix, float degrees, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_setRotate_2(void *matrix, float degrees) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setRotate(degrees));
}

sk_matrix_t SkMatrix_setSinCos(void *matrix, float sinValue, float cosValue, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setSinCos(sinValue, cosValue, px, py));
}

sk_matrix_t SkMatrix_setSinCos_2(void *matrix, float sinValue, float cosValue) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setSinCos(sinValue, cosValue));
}

sk_matrix_t SkMatrix_setRSXform(void *matrix, const void * rsxForm) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setRSXform(* static_cast<const SkRSXform *>(rsxForm)));
}

sk_matrix_t SkMatrix_setSkew(void *matrix, float kx, float ky, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_setSkew_2(void *matrix, float kx, float ky) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setSkew(kx, ky));
}

sk_matrix_t SkMatrix_setConcat(void *matrix, const void * a, const void * b) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setConcat(* static_cast<const SkMatrix *>(a), * static_cast<const SkMatrix *>(b)));
}

sk_matrix_t SkMatrix_preTranslate(void *matrix, float dx, float dy) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->preTranslate(dx, dy));
}

sk_matrix_t SkMatrix_preScale(void *matrix, float sx, float sy, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->preScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_preScale_2(void *matrix, float sx, float sy) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->preScale(sx, sy));
}

sk_matrix_t SkMatrix_preRotate(void *matrix, float degrees, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->preRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_preRotate_2(void *matrix, float degrees) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->preRotate(degrees));
}

sk_matrix_t SkMatrix_preSkew(void *matrix, float kx, float ky, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->preSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_preSkew_2(void *matrix, float kx, float ky) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->preSkew(kx, ky));
}

sk_matrix_t SkMatrix_preConcat(void *matrix, const void * other) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->preConcat(* static_cast<const SkMatrix *>(other)));
}

sk_matrix_t SkMatrix_postTranslate(void *matrix, float dx, float dy) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->postTranslate(dx, dy));
}

sk_matrix_t SkMatrix_postScale(void *matrix, float sx, float sy, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->postScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_postScale_2(void *matrix, float sx, float sy) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->postScale(sx, sy));
}

sk_matrix_t SkMatrix_postRotate(void *matrix, float degrees, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->postRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_postRotate_2(void *matrix, float degrees) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->postRotate(degrees));
}

sk_matrix_t SkMatrix_postSkew(void *matrix, float kx, float ky, float px, float py) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->postSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_postSkew_2(void *matrix, float kx, float ky) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->postSkew(kx, ky));
}

sk_matrix_t SkMatrix_postConcat(void *matrix, const void * other) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->postConcat(* static_cast<const SkMatrix *>(other)));
}

bool SkMatrix_setRectToRect(void *matrix, const void * src, const void *dst, int stf) {
    return static_cast<SkMatrix *>(matrix)->setRectToRect(* static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(stf));
}

bool SkMatrix_setPolyToPoly(void * matrix, const void * src, const void * dst, int count) {
    return static_cast<SkMatrix *>(matrix)->setPolyToPoly(static_cast<const SkPoint *>(src), static_cast<const SkPoint *>(dst), count);
}

bool SkMatrix_invert(void *matrix, void * inverse) {
    return static_cast<SkMatrix *>(matrix)->invert(static_cast<SkMatrix *>(inverse));
}

bool SkMatrix_asAffine(void *matrix, void * affine) {
    return static_cast<SkMatrix *>(matrix)->asAffine(static_cast<SkScalar *>(affine));
}

sk_matrix_t SkMatrix_setAffine(void *matrix, const void * affine) {
    return static_sk_matrix_make(static_cast<SkMatrix *>(matrix)->setAffine(static_cast<const SkScalar *>(affine)));
}

void SkMatrix_normalizePerspective(void *matrix) {
    static_cast<SkMatrix *>(matrix)->normalizePerspective();
}

void SkMatrix_mapPoints(void *matrix, void * dst, const void * src, int count) {
    static_cast<SkMatrix *>(matrix)->mapPoints(static_cast<SkPoint *>(dst), static_cast<const SkPoint *>(src), count);
}

void SkMatrix_mapPoints_2(void *matrix, void * pts, int count) {
    static_cast<SkMatrix *>(matrix)->mapPoints(static_cast<SkPoint *>(pts), count);
}

void SkMatrix_mapHomogeneousPoints(void *matrix, void * dst, const void * src, int count) {
    static_cast<SkMatrix *>(matrix)->mapHomogeneousPoints(static_cast<SkPoint3 *>(dst), static_cast<const SkPoint3 *>(src), count);
}

void SkMatrix_mapHomogeneousPoints_2(void *matrix, void * dst, const void * src, int count) {
    static_cast<SkMatrix *>(matrix)->mapHomogeneousPoints(static_cast<SkPoint3 *>(dst), static_cast<const SkPoint *>(src), count);
}

sk_point_t SkMatrix_mapPoint(void *matrix, sk_point_t pt) {
    return static_sk_point_make(static_cast<SkMatrix *>(matrix)->mapPoint(static_sk_point_get(pt)));
}

void SkMatrix_mapXY(void *matrix, float x, float y, void *result) {
    static_cast<SkMatrix *>(matrix)->mapXY(x, y, static_cast<SkPoint *>(result));
}

sk_point_t SkMatrix_mapXY_2(void *matrix, float x, float y) {
    return static_sk_point_make(static_cast<SkMatrix *>(matrix)->mapXY(x, y));
}

sk_point_t SkMatrix_mapOrigin(void *matrix) {
    return static_sk_point_make(static_cast<SkMatrix *>(matrix)->mapOrigin());
}

void SkMatrix_mapVectors(void *matrix, void * dst, const void * src, int count) {
    static_cast<SkMatrix *>(matrix)->mapVectors(static_cast<SkVector *>(dst), static_cast<const SkVector *>(src), count);
}

void SkMatrix_mapVectors_2(void *matrix, void * vecs, int count) {
    static_cast<SkMatrix *>(matrix)->mapVectors(static_cast<SkVector *>(vecs), count);
}

void SkMatrix_mapVector(void *matrix, float dx, float dy, void * result) {
    static_cast<SkMatrix *>(matrix)->mapVector(dx, dy, static_cast<SkVector *>(result));
}

sk_point_t SkMatrix_mapVector_2(void *matrix, float dx, float dy) {
    return static_sk_point_make(static_cast<SkMatrix *>(matrix)->mapVector(dx, dy));
}

bool SkMatrix_mapRect(void *matrix, void *dst, const void *src, int pc) {
    return static_cast<SkMatrix *>(matrix)->mapRect(static_cast<SkRect *>(dst), * static_cast<const SkRect *>(src), static_cast<SkApplyPerspectiveClip>(pc));
}

bool SkMatrix_mapRect_2(void *matrix, void *rect, int pc) {
    return static_cast<SkMatrix *>(matrix)->mapRect(static_cast<SkRect *>(rect), static_cast<SkApplyPerspectiveClip>(pc));
}

sk_rect_t SkMatrix_mapRect_3(void *matrix, const void *src, int pc) {
    return static_sk_rect_make(static_cast<SkMatrix *>(matrix)->mapRect(* static_cast<const SkRect *>(src), static_cast<SkApplyPerspectiveClip>(pc)));
}

void SkMatrix_mapRectToQuad(void *matrix, void * dst, const void *rect) {
    static_cast<SkMatrix *>(matrix)->mapRectToQuad(static_cast<SkPoint *>(dst), * static_cast<const SkRect *>(rect));
}

void SkMatrix_mapRectScaleTranslate(void *matrix, void *dst, const void *src) {
    static_cast<SkMatrix *>(matrix)->mapRectScaleTranslate(static_cast<SkRect *>(dst), * static_cast<const SkRect *>(src));
}

float SkMatrix_mapRadius(void *matrix, float radius) {
    return static_cast<SkMatrix *>(matrix)->mapRadius(radius);
}

void SkMatrix_dump(void *matrix) {
    static_cast<SkMatrix *>(matrix)->dump();
}

float SkMatrix_getMinScale(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getMinScale();
}

float SkMatrix_getMaxScale(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->getMaxScale();
}

bool SkMatrix_getMinMaxScales(void *matrix, void * scaleFactors) {
    return static_cast<SkMatrix *>(matrix)->getMinMaxScales(static_cast<SkScalar *>(scaleFactors));
}

bool SkMatrix_decomposeScale(void *matrix, void *scale, void *remaining) {
    return static_cast<SkMatrix *>(matrix)->decomposeScale(static_cast<SkSize *>(scale), static_cast<SkMatrix *>(remaining));
}

void SkMatrix_dirtyMatrixTypeCache(void *matrix) {
    static_cast<SkMatrix *>(matrix)->dirtyMatrixTypeCache();
}

void SkMatrix_setScaleTranslate(void *matrix, float sx, float sy, float tx, float ty) {
    static_cast<SkMatrix *>(matrix)->setScaleTranslate(sx, sy, tx, ty);
}

bool SkMatrix_isFinite(void *matrix) {
    return static_cast<SkMatrix *>(matrix)->isFinite();
}


// static

sk_matrix_t SkMatrix_Scale(float sx, float sy) {
    return static_sk_matrix_make(SkMatrix::Scale(sx, sy));
}

sk_matrix_t SkMatrix_Translate(float dx, float dy) {
    return static_sk_matrix_make(SkMatrix::Translate(dx, dy));
}

sk_matrix_t SkMatrix_Translate_2(sk_point_t t) {
    return static_sk_matrix_make(SkMatrix::Translate(static_sk_point_get(t)));
}

sk_matrix_t SkMatrix_Translate_3(sk_i_point_t t) {
    return static_sk_matrix_make(SkMatrix::Translate(static_sk_i_point_get(t)));
}

sk_matrix_t SkMatrix_RotateDeg(float deg) {
    return static_sk_matrix_make(SkMatrix::RotateDeg(deg));
}

sk_matrix_t SkMatrix_RotateDeg_2(float deg, sk_point_t pt) {
    return static_sk_matrix_make(SkMatrix::RotateDeg(deg, static_sk_point_get(pt)));
}

sk_matrix_t SkMatrix_RotateRad(float rad) {
    return static_sk_matrix_make(SkMatrix::RotateRad(rad));
}

sk_matrix_t SkMatrix_Skew(float kx, float ky) {
    return static_sk_matrix_make(SkMatrix::Skew(kx, ky));
}

sk_matrix_t SkMatrix_RectToRect(const void *src, const void *dst, int mode) {
    return static_sk_matrix_make(SkMatrix::RectToRect(* static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(mode)));
}

sk_matrix_t SkMatrix_MakeAll(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float pers0, float pers1, float pers2) {
    return static_sk_matrix_make(SkMatrix::MakeAll(scaleX, skewX, transX, skewY, scaleY, transY, pers0, pers1, pers2));
}

sk_matrix_t SkMatrix_MakeRectToRect(const void *src, const void *dst, int stf) {
    return static_sk_matrix_make(SkMatrix::MakeRectToRect(* static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(stf)));
}

void SkMatrix_SetAffineIdentity(void * affine) {
    SkMatrix::SetAffineIdentity(static_cast<SkScalar *>(affine));
}

sk_matrix_t SkMatrix_I() {
    return static_sk_matrix_make(SkMatrix::I());
}

sk_matrix_t SkMatrix_InvalidMatrix() {
    return static_sk_matrix_make(SkMatrix::InvalidMatrix());
}

sk_matrix_t SkMatrix_Concat(const void *a, const void *b) {
    return static_sk_matrix_make(SkMatrix::Concat(* static_cast<const SkMatrix *>(a), * static_cast<const SkMatrix *>(b)));
}

}
