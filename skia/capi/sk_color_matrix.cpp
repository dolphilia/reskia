//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_matrix.h"

#include "include/effects/SkColorMatrix.h"

#include "../handles/static_sk_color_matrix.h"

#include "../handles/static_sk_color_matrix-internal.h"

extern "C" {

reskia_color_matrix_t *SkColorMatrix_new() {
    return reinterpret_cast<reskia_color_matrix_t *>(new SkColorMatrix());
}

reskia_color_matrix_t *SkColorMatrix_newWithComponents(float m00, float m01, float m02, float m03, float m04, float m10, float m11, float m12, float m13, float m14, float m20, float m21, float m22, float m23, float m24, float m30, float m31, float m32, float m33, float m34) {
    return reinterpret_cast<reskia_color_matrix_t *>(new SkColorMatrix(m00, m01, m02, m03, m04, m10, m11, m12, m13, m14, m20, m21, m22, m23, m24, m30, m31, m32, m33, m34));
}

void SkColorMatrix_delete(reskia_color_matrix_t *color_matrix) {
    delete reinterpret_cast<SkColorMatrix *>(color_matrix);
}

void SkColorMatrix_setIdentity(reskia_color_matrix_t *color_matrix) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->setIdentity();
}

void SkColorMatrix_setScale(reskia_color_matrix_t *color_matrix, float rScale, float gScale, float bScale, float aScale) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->setScale(rScale, gScale, bScale, aScale);
}

void SkColorMatrix_postTranslate(reskia_color_matrix_t *color_matrix, float dr, float dg, float db, float da) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->postTranslate(dr, dg, db, da);
}

void SkColorMatrix_setConcat(reskia_color_matrix_t *color_matrix, const reskia_color_matrix_t *a, const reskia_color_matrix_t *b) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->setConcat(*reinterpret_cast<const SkColorMatrix *>(a), *reinterpret_cast<const SkColorMatrix *>(b));
}

void SkColorMatrix_preConcat(reskia_color_matrix_t *color_matrix, const reskia_color_matrix_t *mat) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->preConcat(*reinterpret_cast<const SkColorMatrix *>(mat));
}

void SkColorMatrix_postConcat(reskia_color_matrix_t *color_matrix, const reskia_color_matrix_t *mat) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->postConcat(*reinterpret_cast<const SkColorMatrix *>(mat));
}

void SkColorMatrix_setSaturation(reskia_color_matrix_t *color_matrix, float sat) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->setSaturation(sat);
}

void SkColorMatrix_setRowMajor(reskia_color_matrix_t *color_matrix, const float src[20]) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->setRowMajor(src);
}

void SkColorMatrix_getRowMajor(reskia_color_matrix_t *color_matrix, float dst[20]) {
    reinterpret_cast<SkColorMatrix *>(color_matrix)->getRowMajor(dst);
}

// static

sk_color_matrix_t SkColorMatrix_RGBtoYUV(reskia_color_matrix_yuv_color_space_t color_space) {
    return static_sk_color_matrix_make(SkColorMatrix::RGBtoYUV(static_cast<SkYUVColorSpace>(color_space)));
}

sk_color_matrix_t SkColorMatrix_YUVtoRGB(reskia_color_matrix_yuv_color_space_t color_space) {
    return static_sk_color_matrix_make(SkColorMatrix::YUVtoRGB(static_cast<SkYUVColorSpace>(color_space)));
}

}
