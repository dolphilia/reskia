//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_matrix.h"

#include "include/effects/SkColorMatrix.h"

#include "../static/static_sk_color_matrix.h"

#include "../static/static_sk_color_matrix-internal.h"

extern "C" {

void *SkColorMatrix_new() {
    return new SkColorMatrix();
}

void *SkColorMatrix_new_2(float m00, float m01, float m02, float m03, float m04, float m10, float m11, float m12, float m13, float m14, float m20, float m21, float m22, float m23, float m24, float m30, float m31, float m32, float m33, float m34) {
    return new SkColorMatrix(m00, m01, m02, m03, m04, m10, m11, m12, m13, m14, m20, m21, m22, m23, m24, m30, m31, m32, m33, m34);
}

void SkColorMatrix_delete(void *color_matrix) {
    delete static_cast<SkColorMatrix *>(color_matrix);
}

void SkColorMatrix_setIdentity(void *color_matrix) {
    static_cast<SkColorMatrix *>(color_matrix)->setIdentity();
}

void SkColorMatrix_setScale(void *color_matrix, float rScale, float gScale, float bScale, float aScale) {
    static_cast<SkColorMatrix *>(color_matrix)->setScale(rScale, gScale, bScale, aScale);
}

void SkColorMatrix_postTranslate(void *color_matrix, float dr, float dg, float db, float da) {
    static_cast<SkColorMatrix *>(color_matrix)->postTranslate(dr, dg, db, da);
}

void SkColorMatrix_setConcat(void *color_matrix, const void *a, const void *b) {
    static_cast<SkColorMatrix *>(color_matrix)->setConcat(* static_cast<const SkColorMatrix *>(a), * static_cast<const SkColorMatrix *>(b));
}

void SkColorMatrix_preConcat(void *color_matrix, const void *mat) {
    static_cast<SkColorMatrix *>(color_matrix)->preConcat(* static_cast<const SkColorMatrix *>(mat));
}

void SkColorMatrix_postConcat(void *color_matrix, const void *mat) {
    static_cast<SkColorMatrix *>(color_matrix)->postConcat(* static_cast<const SkColorMatrix *>(mat));
}

void SkColorMatrix_setSaturation(void *color_matrix, float sat) {
    static_cast<SkColorMatrix *>(color_matrix)->setSaturation(sat);
}

void SkColorMatrix_setRowMajor(void *color_matrix, const void * src) {
    static_cast<SkColorMatrix *>(color_matrix)->setRowMajor(static_cast<const float *>(src));
}

void SkColorMatrix_getRowMajor(void *color_matrix, void * dst) {
    static_cast<SkColorMatrix *>(color_matrix)->getRowMajor(static_cast<float *>(dst));
}

// static

sk_color_matrix_t SkColorMatrix_RGBtoYUV(int color_space) {
    return static_sk_color_matrix_make(SkColorMatrix::RGBtoYUV(static_cast<SkYUVColorSpace>(color_space)));
}

sk_color_matrix_t SkColorMatrix_YUVtoRGB(int color_space) {
    return static_sk_color_matrix_make(SkColorMatrix::YUVtoRGB(static_cast<SkYUVColorSpace>(color_space)));
}

}
