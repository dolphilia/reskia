//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_FILTER_H
#define RAIA_SKIA_SK_COLOR_FILTER_H

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
typedef struct reskia_color_filter_t reskia_color_filter_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef uint32_t reskia_color_t;
typedef int32_t reskia_color_filter_type_t;

void SkColorFilter_release(reskia_color_filter_t *color_filter); // owned: caller が保持する参照を release する。NULL 入力では no-op (SkColorFilter *color_filter)
bool SkColorFilter_asAColorMode(reskia_color_filter_t *color_filter, reskia_color_t *color, int *mode); // out: color/mode は NULL 許可。color_filter NULL では false (SkColorFilter *color_filter, SkColor *color, SkBlendMode *mode) -> bool
bool SkColorFilter_asAColorMatrix(reskia_color_filter_t *color_filter, float matrix[20]); // out: matrix は 20 要素以上、非 NULL。NULL 入力では false (SkColorFilter *color_filter, float matrix[20]) -> bool
bool SkColorFilter_isAlphaUnchanged(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> bool
reskia_color_t SkColorFilter_filterColor(reskia_color_filter_t *color_filter, reskia_color_t color); // color_filter NULL では入力 color を返す (SkColorFilter *color_filter, SkColor color) -> SkColor
sk_color_4f_t SkColorFilter_filterColor4f(reskia_color_filter_t *color_filter, const reskia_color_4f_t *srcColor, reskia_color_space_t *srcCS, reskia_color_space_t *dstCS); // srcColor は非 NULL。srcCS/dstCS は NULL 許可。NULL 入力では 0 (SkColorFilter *color_filter, const SkColor4f *srcColor, SkColorSpace *srcCS, SkColorSpace *dstCS) -> sk_color_4f_t
sk_color_filter_t SkColorFilter_makeComposed(reskia_color_filter_t *color_filter, sk_color_filter_t inner); // inner 0/無効は null filter。生成不能なら 0 (SkColorFilter *color_filter, sk_color_filter_t inner) -> sk_color_filter_t
sk_color_filter_t SkColorFilter_makeWithWorkingColorSpace(reskia_color_filter_t *color_filter, sk_color_space_t colorSpace); // colorSpace 0/無効は null color space。生成不能なら 0 (SkColorFilter *color_filter, sk_color_space_t colorSpace) -> sk_color_filter_t
sk_flattenable_factory_t SkColorFilter_getFactory(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> sk_flattenable_factory_t
const char *SkColorFilter_getTypeName(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> const char *
void SkColorFilter_flatten(reskia_color_filter_t *color_filter, reskia_write_buffer_t *write_buffer); // write_buffer は非 NULL。NULL 入力では no-op (SkColorFilter *color_filter, SkWriteBuffer *write_buffer)
reskia_color_filter_type_t SkColorFilter_getFlattenableType(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> SkColorFilter::Type
sk_data_t SkColorFilter_serialize(reskia_color_filter_t *color_filter, const reskia_serial_procs_t *serial_procs); // retained data handle。serial_procs は NULL 許可。color_filter NULL では 0 (SkColorFilter *color_filter, const SkSerialProcs *serial_procs) -> sk_data_t
size_t SkColorFilter_serializeToMemory(reskia_color_filter_t *color_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs); // raw out buffer: memory は memory_size バイト以上。サイズ取得は serialize() を使う。color_filter NULL では 0
bool SkColorFilter_unique(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> bool
void SkColorFilter_ref(reskia_color_filter_t *color_filter); // retained: 参照カウントを増やす (SkColorFilter *color_filter)
void SkColorFilter_unref(reskia_color_filter_t *color_filter); // owned: 参照カウントを減らす (SkColorFilter *color_filter)

// static

sk_color_filter_t SkColorFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs); // raw input buffer: data は size バイト以上、非 NULL。procs は NULL 許可。生成不能なら 0
sk_flattenable_factory_t SkColorFilter_NameToFactory(const char name[]); // name は非 NULL。見つからない場合は 0
const char *SkColorFilter_FactoryToName(sk_flattenable_factory_t factory); // factory 0/無効では NULL
void SkColorFilter_Register(const char name[], sk_flattenable_factory_t factory); // name/factory は非 NULL/非 0。無効入力では no-op

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_FILTER_H
