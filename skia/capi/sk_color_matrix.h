//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_MATRIX_H
#define RAIA_SKIA_SK_COLOR_MATRIX_H

#include <stdint.h>
#include "../handles/static_sk_color_matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_matrix_t reskia_color_matrix_t;
typedef int32_t reskia_color_matrix_yuv_color_space_t;

reskia_color_matrix_t *SkColorMatrix_new(); // () -> SkColorMatrix *
reskia_color_matrix_t *SkColorMatrix_newWithComponents(float m00, float m01, float m02, float m03, float m04, float m10, float m11, float m12, float m13, float m14, float m20, float m21, float m22, float m23, float m24, float m30, float m31, float m32, float m33, float m34); // (float m00, float m01, float m02, float m03, float m04, float m10, float m11, float m12, float m13, float m14, float m20, float m21, float m22, float m23, float m24, float m30, float m31, float m32, float m33, float m34) -> SkColorMatrix *
void SkColorMatrix_delete(reskia_color_matrix_t *color_matrix); // NULL 入力では no-op (SkColorMatrix *color_matrix)
void SkColorMatrix_setIdentity(reskia_color_matrix_t *color_matrix); // NULL 入力では no-op (SkColorMatrix *color_matrix)
void SkColorMatrix_setScale(reskia_color_matrix_t *color_matrix, float rScale, float gScale, float bScale, float aScale); // NULL 入力では no-op (SkColorMatrix *color_matrix, float rScale, float gScale, float bScale, float aScale)
void SkColorMatrix_postTranslate(reskia_color_matrix_t *color_matrix, float dr, float dg, float db, float da); // NULL 入力では no-op (SkColorMatrix *color_matrix, float dr, float dg, float db, float da)
void SkColorMatrix_setConcat(reskia_color_matrix_t *color_matrix, const reskia_color_matrix_t *a, const reskia_color_matrix_t *b); // color_matrix/a/b は非 NULL。NULL 入力では no-op (SkColorMatrix *color_matrix, const SkColorMatrix *a, const SkColorMatrix *b)
void SkColorMatrix_preConcat(reskia_color_matrix_t *color_matrix, const reskia_color_matrix_t *mat); // color_matrix/mat は非 NULL。NULL 入力では no-op (SkColorMatrix *color_matrix, const SkColorMatrix *mat)
void SkColorMatrix_postConcat(reskia_color_matrix_t *color_matrix, const reskia_color_matrix_t *mat); // color_matrix/mat は非 NULL。NULL 入力では no-op (SkColorMatrix *color_matrix, const SkColorMatrix *mat)
void SkColorMatrix_setSaturation(reskia_color_matrix_t *color_matrix, float sat); // NULL 入力では no-op (SkColorMatrix *color_matrix, float sat)
void SkColorMatrix_setRowMajor(reskia_color_matrix_t *color_matrix, const float src[20]); // raw input array: src は 20 要素以上、非 NULL。NULL 入力では no-op
void SkColorMatrix_getRowMajor(reskia_color_matrix_t *color_matrix, float dst[20]); // raw output array: dst は 20 要素以上、非 NULL。NULL 入力では no-op

// static

sk_color_matrix_t SkColorMatrix_RGBtoYUV(reskia_color_matrix_yuv_color_space_t color_space); // (SkYUVColorSpace color_space) -> sk_color_matrix_t
sk_color_matrix_t SkColorMatrix_YUVtoRGB(reskia_color_matrix_yuv_color_space_t color_space); // (SkYUVColorSpace color_space) -> sk_color_matrix_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_MATRIX_H
