//
// Created by dolphilia on 2024/01/09.
//

#include "sk_matrix.h"

#include "include/core/SkMatrix.h"

#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_i_point.h"

#include "../handles/static_sk_i_point-internal.h"
#include "../handles/static_sk_matrix-internal.h"
#include "../handles/static_sk_point-internal.h"
#include "../handles/static_sk_rect-internal.h"

namespace {

constexpr int kMatrixValueCount = 9;

bool is_valid_index(int index) {
    return 0 <= index && index < kMatrixValueCount;
}

bool is_valid_rc(int r, int c) {
    return 0 <= r && r < 3 && 0 <= c && c < 3;
}

}  // namespace

extern "C" {

// SkScalar operator[](int index)
// SkScalar & operator[](int index)

reskia_matrix_t *SkMatrix_new(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_matrix_t *>(new SkMatrix(*reinterpret_cast<SkMatrix *>(matrix)));
}

void SkMatrix_delete(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return;
    }
    delete reinterpret_cast<SkMatrix *>(matrix);
}

reskia_matrix_type_mask_t SkMatrix_getType(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return -1;
    }
    return static_cast<reskia_matrix_type_mask_t>(reinterpret_cast<SkMatrix *>(matrix)->getType());
}

bool SkMatrix_isIdentity(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->isIdentity();
}

bool SkMatrix_isScaleTranslate(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->isScaleTranslate();
}

bool SkMatrix_isTranslate(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->isTranslate();
}

bool SkMatrix_rectStaysRect(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->rectStaysRect();
}

bool SkMatrix_preservesAxisAlignment(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->preservesAxisAlignment();
}

bool SkMatrix_hasPerspective(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->hasPerspective();
}

bool SkMatrix_isSimilarity(reskia_matrix_t *matrix, float tol) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->isSimilarity(tol);
}

bool SkMatrix_preservesRightAngles(reskia_matrix_t *matrix, float tol) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->preservesRightAngles(tol);
}

float SkMatrix_get(reskia_matrix_t *matrix, int index) {
    if (matrix == nullptr || !is_valid_index(index)) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->get(index);
}

float SkMatrix_rc(reskia_matrix_t *matrix, int r, int c) {
    if (matrix == nullptr || !is_valid_rc(r, c)) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->rc(r, c);
}

float SkMatrix_getScaleX(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getScaleX();
}

float SkMatrix_getScaleY(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getScaleY();
}

float SkMatrix_getSkewY(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getSkewY();
}

float SkMatrix_getSkewX(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getSkewX();
}

float SkMatrix_getTranslateX(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getTranslateX();
}

float SkMatrix_getTranslateY(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getTranslateY();
}

float SkMatrix_getPerspX(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getPerspX();
}

float SkMatrix_getPerspY(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getPerspY();
}

sk_matrix_t SkMatrix_set(reskia_matrix_t *matrix, int index, float value) {
    if (matrix == nullptr || !is_valid_index(index)) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->set(index, value));
}

sk_matrix_t SkMatrix_setScaleX(reskia_matrix_t *matrix, float v) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setScaleX(v));
}

sk_matrix_t SkMatrix_setScaleY(reskia_matrix_t *matrix, float v) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setScaleY(v));
}

sk_matrix_t SkMatrix_setSkewY(reskia_matrix_t *matrix, float v) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSkewY(v));
}

sk_matrix_t SkMatrix_setSkewX(reskia_matrix_t *matrix, float v) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSkewX(v));
}

sk_matrix_t SkMatrix_setTranslateX(reskia_matrix_t *matrix, float v) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setTranslateX(v));
}

sk_matrix_t SkMatrix_setTranslateY(reskia_matrix_t *matrix, float v) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setTranslateY(v));
}

sk_matrix_t SkMatrix_setPerspX(reskia_matrix_t *matrix, float v) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setPerspX(v));
}

sk_matrix_t SkMatrix_setPerspY(reskia_matrix_t *matrix, float v) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setPerspY(v));
}

sk_matrix_t SkMatrix_setAll(reskia_matrix_t *matrix, float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float persp0, float persp1, float persp2) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setAll(scaleX, skewX, transX, skewY, scaleY, transY, persp0, persp1, persp2));
}

void SkMatrix_get9(reskia_matrix_t *matrix, float *buffer) {
    if (matrix == nullptr || buffer == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->get9(buffer);
}

sk_matrix_t SkMatrix_set9(reskia_matrix_t *matrix, const float *buffer) {
    if (matrix == nullptr || buffer == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->set9(buffer));
}

sk_matrix_t SkMatrix_reset(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->reset());
}

sk_matrix_t SkMatrix_setIdentity(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setIdentity());
}

sk_matrix_t SkMatrix_setTranslate(reskia_matrix_t *matrix, float dx, float dy) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setTranslate(dx, dy));
}

sk_matrix_t SkMatrix_setTranslateWithVector(reskia_matrix_t *matrix, const reskia_vector_t *v) {
    if (matrix == nullptr || v == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setTranslate(* reinterpret_cast<const SkVector *>(v)));
}

sk_matrix_t SkMatrix_setScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_setScaleXY(reskia_matrix_t *matrix, float sx, float sy) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setScale(sx, sy));
}

sk_matrix_t SkMatrix_setRotate(reskia_matrix_t *matrix, float degrees, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_setRotateDegrees(reskia_matrix_t *matrix, float degrees) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setRotate(degrees));
}

sk_matrix_t SkMatrix_setSinCos(reskia_matrix_t *matrix, float sinValue, float cosValue, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSinCos(sinValue, cosValue, px, py));
}

sk_matrix_t SkMatrix_setSinCosValues(reskia_matrix_t *matrix, float sinValue, float cosValue) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSinCos(sinValue, cosValue));
}

sk_matrix_t SkMatrix_setRSXform(reskia_matrix_t *matrix, const reskia_rsxform_t *rsxForm) {
    if (matrix == nullptr || rsxForm == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setRSXform(*reinterpret_cast<const SkRSXform *>(rsxForm)));
}

sk_matrix_t SkMatrix_setSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_setSkewXY(reskia_matrix_t *matrix, float kx, float ky) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setSkew(kx, ky));
}

sk_matrix_t SkMatrix_setConcat(reskia_matrix_t *matrix, const reskia_matrix_t *a, const reskia_matrix_t *b) {
    if (matrix == nullptr || a == nullptr || b == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setConcat(*reinterpret_cast<const SkMatrix *>(a), *reinterpret_cast<const SkMatrix *>(b)));
}

sk_matrix_t SkMatrix_preTranslate(reskia_matrix_t *matrix, float dx, float dy) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preTranslate(dx, dy));
}

sk_matrix_t SkMatrix_preScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_preScaleXY(reskia_matrix_t *matrix, float sx, float sy) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preScale(sx, sy));
}

sk_matrix_t SkMatrix_preRotate(reskia_matrix_t *matrix, float degrees, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_preRotateDegrees(reskia_matrix_t *matrix, float degrees) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preRotate(degrees));
}

sk_matrix_t SkMatrix_preSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_preSkewXY(reskia_matrix_t *matrix, float kx, float ky) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preSkew(kx, ky));
}

sk_matrix_t SkMatrix_preConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other) {
    if (matrix == nullptr || other == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->preConcat(*reinterpret_cast<const SkMatrix *>(other)));
}

sk_matrix_t SkMatrix_postTranslate(reskia_matrix_t *matrix, float dx, float dy) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postTranslate(dx, dy));
}

sk_matrix_t SkMatrix_postScale(reskia_matrix_t *matrix, float sx, float sy, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postScale(sx, sy, px, py));
}

sk_matrix_t SkMatrix_postScaleXY(reskia_matrix_t *matrix, float sx, float sy) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postScale(sx, sy));
}

sk_matrix_t SkMatrix_postRotate(reskia_matrix_t *matrix, float degrees, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postRotate(degrees, px, py));
}

sk_matrix_t SkMatrix_postRotateDegrees(reskia_matrix_t *matrix, float degrees) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postRotate(degrees));
}

sk_matrix_t SkMatrix_postSkew(reskia_matrix_t *matrix, float kx, float ky, float px, float py) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postSkew(kx, ky, px, py));
}

sk_matrix_t SkMatrix_postSkewXY(reskia_matrix_t *matrix, float kx, float ky) {
    if (matrix == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postSkew(kx, ky));
}

sk_matrix_t SkMatrix_postConcat(reskia_matrix_t *matrix, const reskia_matrix_t *other) {
    if (matrix == nullptr || other == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->postConcat(*reinterpret_cast<const SkMatrix *>(other)));
}

bool SkMatrix_setRectToRect(reskia_matrix_t *matrix, const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t stf) {
    if (matrix == nullptr || src == nullptr || dst == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->setRectToRect(* reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(stf));
}

bool SkMatrix_setPolyToPoly(reskia_matrix_t *matrix, const reskia_point_t *src, const reskia_point_t *dst, int count) {
    if (matrix == nullptr || count < 0 || count > 4 || (count > 0 && (src == nullptr || dst == nullptr))) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->setPolyToPoly(
            {reinterpret_cast<const SkPoint *>(src), static_cast<size_t>(count)},
            {reinterpret_cast<const SkPoint *>(dst), static_cast<size_t>(count)});
}

sk_matrix_t SkMatrix_PolyToPoly(const reskia_point_t *src, const reskia_point_t *dst, int count) {
    if (count < 0 || count > 4 || (count > 0 && (src == nullptr || dst == nullptr))) {
        return 0;
    }
    std::optional<SkMatrix> matrix = SkMatrix::PolyToPoly(
            {reinterpret_cast<const SkPoint *>(src), static_cast<size_t>(count)},
            {reinterpret_cast<const SkPoint *>(dst), static_cast<size_t>(count)});
    return matrix.has_value() ? static_sk_matrix_make(*matrix) : 0;
}

bool SkMatrix_invert(reskia_matrix_t *matrix, reskia_matrix_t *inverse) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->invert(reinterpret_cast<SkMatrix *>(inverse));
}

bool SkMatrix_asAffine(reskia_matrix_t *matrix, float *affine) {
    if (matrix == nullptr || affine == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->asAffine(static_cast<SkScalar *>(affine));
}

sk_matrix_t SkMatrix_setAffine(reskia_matrix_t *matrix, const float *affine) {
    if (matrix == nullptr || affine == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkMatrix *>(matrix)->setAffine(static_cast<const SkScalar *>(affine)));
}

void SkMatrix_normalizePerspective(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->normalizePerspective();
}

void SkMatrix_mapPoints(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_point_t *src, int count) {
    if (matrix == nullptr || count <= 0 || dst == nullptr || src == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapPoints(
            {reinterpret_cast<SkPoint *>(dst), static_cast<size_t>(count)},
            {reinterpret_cast<const SkPoint *>(src), static_cast<size_t>(count)});
}

void SkMatrix_mapPointsInPlace(reskia_matrix_t *matrix, reskia_point_t *pts, int count) {
    if (matrix == nullptr || count <= 0 || pts == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapPoints(
            {reinterpret_cast<SkPoint *>(pts), static_cast<size_t>(count)});
}

void SkMatrix_mapHomogeneousPoints(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point3_t *src, int count) {
    if (matrix == nullptr || count <= 0 || dst == nullptr || src == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapHomogeneousPoints(
            {reinterpret_cast<SkPoint3 *>(dst), static_cast<size_t>(count)},
            {reinterpret_cast<const SkPoint3 *>(src), static_cast<size_t>(count)});
}

void SkMatrix_mapHomogeneousPoint(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point3_t *src) {
    if (matrix == nullptr || dst == nullptr || src == nullptr) {
        return;
    }
    *reinterpret_cast<SkPoint3 *>(dst) = reinterpret_cast<SkMatrix *>(matrix)->mapHomogeneousPoint(*reinterpret_cast<const SkPoint3 *>(src));
}

void SkMatrix_mapHomogeneousPointsFromPoints(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src, int count) {
    if (matrix == nullptr || count <= 0 || dst == nullptr || src == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapPointsToHomogeneous(
            {reinterpret_cast<SkPoint3 *>(dst), static_cast<size_t>(count)},
            {reinterpret_cast<const SkPoint *>(src), static_cast<size_t>(count)});
}

void SkMatrix_mapPointsToHomogeneous(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src, int count) {
    if (matrix == nullptr || count <= 0 || dst == nullptr || src == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapPointsToHomogeneous(
            {reinterpret_cast<SkPoint3 *>(dst), static_cast<size_t>(count)},
            {reinterpret_cast<const SkPoint *>(src), static_cast<size_t>(count)});
}

void SkMatrix_mapPointToHomogeneous(reskia_matrix_t *matrix, reskia_point3_t *dst, const reskia_point_t *src) {
    if (matrix == nullptr || dst == nullptr || src == nullptr) {
        return;
    }
    *reinterpret_cast<SkPoint3 *>(dst) = reinterpret_cast<SkMatrix *>(matrix)->mapPointToHomogeneous(*reinterpret_cast<const SkPoint *>(src));
}

sk_point_t SkMatrix_mapPoint(reskia_matrix_t *matrix, sk_point_t pt) {
    if (matrix == nullptr) {
        return static_sk_point_make({});
    }
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapPoint(static_sk_point_get_entity(pt)));
}

sk_point_t SkMatrix_mapPointAffine(reskia_matrix_t *matrix, sk_point_t pt) {
    if (matrix == nullptr) {
        return static_sk_point_make({});
    }
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapPointAffine(static_sk_point_get_entity(pt)));
}

void SkMatrix_mapXY(reskia_matrix_t *matrix, float x, float y, reskia_point_t *result) {
    if (matrix == nullptr || result == nullptr) {
        return;
    }
    *reinterpret_cast<SkPoint *>(result) =
            reinterpret_cast<SkMatrix *>(matrix)->mapPoint(SkPoint::Make(x, y));
}

sk_point_t SkMatrix_mapXYToPoint(reskia_matrix_t *matrix, float x, float y) {
    if (matrix == nullptr) {
        return static_sk_point_make({});
    }
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapPoint(SkPoint::Make(x, y)));
}

sk_point_t SkMatrix_mapOrigin(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return static_sk_point_make({});
    }
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapOrigin());
}

void SkMatrix_mapVectors(reskia_matrix_t *matrix, reskia_vector_t *dst, const reskia_vector_t *src, int count) {
    if (matrix == nullptr || count <= 0 || dst == nullptr || src == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapVectors(
            {reinterpret_cast<SkVector *>(dst), static_cast<size_t>(count)},
            {reinterpret_cast<const SkVector *>(src), static_cast<size_t>(count)});
}

void SkMatrix_mapVectorsInPlace(reskia_matrix_t *matrix, reskia_vector_t *vecs, int count) {
    if (matrix == nullptr || count <= 0 || vecs == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapVectors(
            {reinterpret_cast<SkVector *>(vecs), static_cast<size_t>(count)});
}

void SkMatrix_mapVector(reskia_matrix_t *matrix, float dx, float dy, reskia_vector_t *result) {
    if (matrix == nullptr || result == nullptr) {
        return;
    }
    *reinterpret_cast<SkVector *>(result) =
            reinterpret_cast<SkMatrix *>(matrix)->mapVector(dx, dy);
}

sk_point_t SkMatrix_mapVectorToPoint(reskia_matrix_t *matrix, float dx, float dy) {
    if (matrix == nullptr) {
        return static_sk_point_make({});
    }
    return static_sk_point_make(reinterpret_cast<SkMatrix *>(matrix)->mapVector(dx, dy));
}

bool SkMatrix_mapRect(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src, reskia_matrix_apply_perspective_clip_t pc) {
    if (matrix == nullptr || dst == nullptr || src == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->mapRect(reinterpret_cast<SkRect *>(dst), * reinterpret_cast<const SkRect *>(src), static_cast<SkApplyPerspectiveClip>(pc));
}

bool SkMatrix_mapRectInPlace(reskia_matrix_t *matrix, reskia_rect_t *rect, reskia_matrix_apply_perspective_clip_t pc) {
    if (matrix == nullptr || rect == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->mapRect(reinterpret_cast<SkRect *>(rect), static_cast<SkApplyPerspectiveClip>(pc));
}

sk_rect_t SkMatrix_mapRectFromSource(reskia_matrix_t *matrix, const reskia_rect_t *src, reskia_matrix_apply_perspective_clip_t pc) {
    if (matrix == nullptr || src == nullptr) {
        return static_sk_rect_make(SkRect::MakeEmpty());
    }
    return static_sk_rect_make(reinterpret_cast<SkMatrix *>(matrix)->mapRect(*reinterpret_cast<const SkRect *>(src), static_cast<SkApplyPerspectiveClip>(pc)));
}

void SkMatrix_mapRectToQuad(reskia_matrix_t *matrix, reskia_point_t *dst, const reskia_rect_t *rect) {
    if (matrix == nullptr || dst == nullptr || rect == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapRectToQuad(reinterpret_cast<SkPoint *>(dst), * reinterpret_cast<const SkRect *>(rect));
}

void SkMatrix_mapRectScaleTranslate(reskia_matrix_t *matrix, reskia_rect_t *dst, const reskia_rect_t *src) {
    if (matrix == nullptr || dst == nullptr || src == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->mapRectScaleTranslate(reinterpret_cast<SkRect *>(dst), * reinterpret_cast<const SkRect *>(src));
}

float SkMatrix_mapRadius(reskia_matrix_t *matrix, float radius) {
    if (matrix == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->mapRadius(radius);
}

void SkMatrix_dump(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->dump();
}

float SkMatrix_getMinScale(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return -1.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getMinScale();
}

float SkMatrix_getMaxScale(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return -1.0f;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getMaxScale();
}

bool SkMatrix_getMinMaxScales(reskia_matrix_t *matrix, float *scaleFactors) {
    if (matrix == nullptr || scaleFactors == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->getMinMaxScales(static_cast<SkScalar *>(scaleFactors));
}

bool SkMatrix_decomposeScale(reskia_matrix_t *matrix, reskia_size_t *scale, reskia_matrix_t *remaining) {
    if (matrix == nullptr || scale == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->decomposeScale(reinterpret_cast<SkSize *>(scale), reinterpret_cast<SkMatrix *>(remaining));
}

void SkMatrix_dirtyMatrixTypeCache(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->dirtyMatrixTypeCache();
}

void SkMatrix_setScaleTranslate(reskia_matrix_t *matrix, float sx, float sy, float tx, float ty) {
    if (matrix == nullptr) {
        return;
    }
    reinterpret_cast<SkMatrix *>(matrix)->setScaleTranslate(sx, sy, tx, ty);
}

bool SkMatrix_isFinite(reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMatrix *>(matrix)->isFinite();
}


// static

sk_matrix_t SkMatrix_Scale(float sx, float sy) {
    return static_sk_matrix_make(SkMatrix::Scale(sx, sy));
}

sk_matrix_t SkMatrix_Translate(float dx, float dy) {
    return static_sk_matrix_make(SkMatrix::Translate(dx, dy));
}

sk_matrix_t SkMatrix_TranslateFromPoint(sk_point_t t) {
    return static_sk_matrix_make(SkMatrix::Translate(static_sk_point_get_entity(t)));
}

sk_matrix_t SkMatrix_TranslateFromIPoint(sk_i_point_t t) {
    return static_sk_matrix_make(SkMatrix::Translate(static_sk_i_point_get_entity(t)));
}

sk_matrix_t SkMatrix_RotateDeg(float deg) {
    return static_sk_matrix_make(SkMatrix::RotateDeg(deg));
}

sk_matrix_t SkMatrix_RotateDegAroundPoint(float deg, sk_point_t pt) {
    return static_sk_matrix_make(SkMatrix::RotateDeg(deg, static_sk_point_get_entity(pt)));
}

sk_matrix_t SkMatrix_RotateRad(float rad) {
    return static_sk_matrix_make(SkMatrix::RotateRad(rad));
}

sk_matrix_t SkMatrix_Skew(float kx, float ky) {
    return static_sk_matrix_make(SkMatrix::Skew(kx, ky));
}

sk_matrix_t SkMatrix_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t mode) {
    if (src == nullptr || dst == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(SkMatrix::RectToRect(* reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(mode)));
}

sk_matrix_t SkMatrix_MakeAll(float scaleX, float skewX, float transX, float skewY, float scaleY, float transY, float pers0, float pers1, float pers2) {
    return static_sk_matrix_make(SkMatrix::MakeAll(scaleX, skewX, transX, skewY, scaleY, transY, pers0, pers1, pers2));
}

sk_matrix_t SkMatrix_MakeRectToRect(const reskia_rect_t *src, const reskia_rect_t *dst, reskia_matrix_scale_to_fit_t stf) {
    if (src == nullptr || dst == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(SkMatrix::MakeRectToRect(* reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), static_cast<SkMatrix::ScaleToFit>(stf)));
}

void SkMatrix_SetAffineIdentity(float *affine) {
    if (affine == nullptr) {
        return;
    }
    SkMatrix::SetAffineIdentity(static_cast<SkScalar *>(affine));
}

sk_matrix_t SkMatrix_I() {
    return static_sk_matrix_make(SkMatrix::I());
}

sk_matrix_t SkMatrix_InvalidMatrix() {
    return static_sk_matrix_make(SkMatrix::InvalidMatrix());
}

sk_matrix_t SkMatrix_Concat(const reskia_matrix_t *a, const reskia_matrix_t *b) {
    if (a == nullptr || b == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(SkMatrix::Concat(* reinterpret_cast<const SkMatrix *>(a), * reinterpret_cast<const SkMatrix *>(b)));
}

}
