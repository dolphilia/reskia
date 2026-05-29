//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_MATRIX_FILTER_H
#define RAIA_SKIA_SK_COLOR_MATRIX_FILTER_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_color_4f.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable_factory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_color_matrix_filter_t reskia_color_matrix_filter_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef uint32_t reskia_color_t;
typedef int32_t reskia_color_matrix_filter_type_t;

/**
 * owned: caller が保持する参照を release する。NULL 入力では no-op (SkColorMatrixFilter *color_matrix_filter)
 */
void SkColorMatrixFilter_release(reskia_color_matrix_filter_t *color_matrix_filter);
/**
 * out: color/mode は NULL 許可。color_matrix_filter NULL では false
 */
bool SkColorMatrixFilter_asAColorMode(reskia_color_matrix_filter_t *color_matrix_filter, reskia_color_t *color, int *mode);
bool SkColorMatrixFilter_asAColorMatrix(reskia_color_matrix_filter_t *color_matrix_filter, float matrix[20]); // out: matrix は 20 要素以上、非 NULL。NULL 入力では false
bool SkColorMatrixFilter_isAlphaUnchanged(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> bool
/**
 * srcColor は非 NULL。srcCS/dstCS は NULL 許可。NULL 入力では 0
 */
sk_color_4f_t SkColorMatrixFilter_filterColor4f(reskia_color_matrix_filter_t *color_matrix_filter, const reskia_color_4f_t *srcColor, reskia_color_space_t *srcCS, reskia_color_space_t *dstCS);
sk_color_filter_t SkColorMatrixFilter_makeComposed(reskia_color_matrix_filter_t *color_matrix_filter, sk_color_filter_t colorFilter); // colorFilter 0/無効は null filter。生成不能なら 0
sk_color_filter_t SkColorMatrixFilter_makeWithWorkingColorSpace(reskia_color_matrix_filter_t *color_matrix_filter, sk_color_space_t colorSpace); // colorSpace 0/無効は null color space。生成不能なら 0
sk_flattenable_factory_t SkColorMatrixFilter_getFactory(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> sk_flattenable_factory_t
const char *SkColorMatrixFilter_getTypeName(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> const char *
/**
 * write_buffer は非 NULL。NULL 入力では no-op
 */
void SkColorMatrixFilter_flatten(reskia_color_matrix_filter_t *color_matrix_filter, reskia_write_buffer_t *write_buffer);
reskia_color_matrix_filter_type_t SkColorMatrixFilter_getFlattenableType(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> SkColorMatrixFilter::Type
/**
 * retained data handle。serial_procs は NULL 許可。color_matrix_filter NULL では 0
 */
sk_data_t SkColorMatrixFilter_serialize(reskia_color_matrix_filter_t *color_matrix_filter, const reskia_serial_procs_t *serial_procs);
/**
 * raw out buffer: memory は memory_size バイト以上。サイズ取得は serialize() を使う。NULL 入力では 0
 */
size_t SkColorMatrixFilter_serializeToMemory(reskia_color_matrix_filter_t *color_matrix_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs);
bool SkColorMatrixFilter_unique(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> bool
void SkColorMatrixFilter_ref(reskia_color_matrix_filter_t *color_matrix_filter); // retained: 参照カウントを増やす (SkColorMatrixFilter *color_matrix_filter)
void SkColorMatrixFilter_unref(reskia_color_matrix_filter_t *color_matrix_filter); // owned: 参照カウントを減らす (SkColorMatrixFilter *color_matrix_filter)

// static

sk_color_filter_t SkColorMatrixFilter_MakeLightingFilter(reskia_color_t mul, reskia_color_t add); // 生成不能なら 0 (SkColor mul, SkColor add) -> sk_color_filter_t
/**
 * raw input buffer: data は size バイト以上、非 NULL。procs は NULL 許可。生成不能なら 0
 */
sk_color_filter_t SkColorMatrixFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs);
sk_flattenable_factory_t SkColorMatrixFilter_NameToFactory(const char name[]); // name は非 NULL。見つからない場合は 0
const char * SkColorMatrixFilter_FactoryToName(sk_flattenable_factory_t factory); // factory 0/無効では NULL
void SkColorMatrixFilter_Register(const char name[], sk_flattenable_factory_t factory); // name/factory は非 NULL/非 0。無効入力では no-op

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_MATRIX_FILTER_H
