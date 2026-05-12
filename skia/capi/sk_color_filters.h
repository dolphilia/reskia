//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_FILTERS_H
#define RAIA_SKIA_SK_COLOR_FILTERS_H

#include <stdint.h>
#include "sk_blend_mode.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_color_table.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_color_filters_t reskia_color_filters_t;
typedef struct reskia_color_matrix_t reskia_color_matrix_t;
typedef uint32_t reskia_color_t;

void SkColorFilters_delete(reskia_color_filters_t *colorFilters); // (SkColorFilters *colorFilters)

// static

/**
 * c は非 NULL。color_space 0/無効は sRGB 扱い。生成不能なら 0 (const SkColor4f *c, sk_color_space_t color_space, SkBlendMode mode) -> sk_color_filter_t
 */
sk_color_filter_t SkColorFilters_Blend(const reskia_color_4f_t *c, sk_color_space_t color_space, reskia_blend_mode_t mode);
sk_color_filter_t SkColorFilters_BlendColor(reskia_color_t c, reskia_blend_mode_t mode); // (SkColor c, SkBlendMode mode) -> sk_color_filter_t
sk_color_filter_t SkColorFilters_Compose(sk_color_filter_t color_filter1, sk_color_filter_t color_filter2); // handle 0/無効は null filter。生成不能なら 0 (sk_color_filter_t color_filter1, sk_color_filter_t color_filter2) -> sk_color_filter_t
/**
 * raw input array: rowMajor は 20 要素以上、非 NULL。生成不能なら 0 (const float rowMajor[20]) -> sk_color_filter_t
 */
sk_color_filter_t SkColorFilters_HSLAMatrix(const float rowMajor[20]);
/**
 * matrix は非 NULL。生成不能なら 0 (const SkColorMatrix *matrix) -> sk_color_filter_t
 */
sk_color_filter_t SkColorFilters_HSLAMatrixFromMatrix(const reskia_color_matrix_t *matrix);
sk_color_filter_t SkColorFilters_Lerp(float t, sk_color_filter_t color_filter1, sk_color_filter_t color_filter2); // handle 0/無効は null filter。生成不能なら 0 (float t, sk_color_filter_t color_filter1, sk_color_filter_t color_filter2) -> sk_color_filter_t
sk_color_filter_t SkColorFilters_Lighting(reskia_color_t mul, reskia_color_t add); // (SkColor mul, SkColor add) -> sk_color_filter_t
sk_color_filter_t SkColorFilters_LinearToSRGBGamma(); // () -> sk_color_filter_t
/**
 * raw input array: rowMajor は 20 要素以上、非 NULL。生成不能なら 0 (const float rowMajor[20]) -> sk_color_filter_t
 */
sk_color_filter_t SkColorFilters_Matrix(const float rowMajor[20]);
/**
 * matrix は非 NULL。生成不能なら 0 (const SkColorMatrix *matrix) -> sk_color_filter_t
 */
sk_color_filter_t SkColorFilters_MatrixFromMatrix(const reskia_color_matrix_t *matrix);
sk_color_filter_t SkColorFilters_SRGBToLinearGamma(); // () -> sk_color_filter_t
/**
 * raw input array: table は 256 要素以上、非 NULL。生成不能なら 0 (const uint8_t table[256]) -> sk_color_filter_t
 */
sk_color_filter_t SkColorFilters_Table(const uint8_t table[256]);
sk_color_filter_t SkColorFilters_TableFromColorTable(sk_color_table_t color_table); // color_table 0/無効は null table。生成不能なら 0 (sk_color_table_t color_table) -> sk_color_filter_t
/**
 * 各 table は NULL 許可で identity 扱い (const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]) -> sk_color_filter_t
 */
sk_color_filter_t SkColorFilters_TableARGB(const uint8_t tableA[256], const uint8_t tableR[256], const uint8_t tableG[256], const uint8_t tableB[256]);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_FILTERS_H
