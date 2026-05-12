//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_MASK_FILTER_H
#define RAIA_SKIA_SK_MASK_FILTER_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable_factory.h"
#include "../handles/static_sk_mask_filter.h"
#include "../handles/static_sk_rect.h"

typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_mask_filter_t reskia_mask_filter_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef int32_t reskia_mask_filter_type_t;
typedef int32_t reskia_mask_filter_blur_style_t;

void SkMaskFilter_release(reskia_mask_filter_t *maskFilter); // owned: caller が保持する参照を release する。NULL 入力では no-op
sk_rect_t SkMaskFilter_approximateFilteredBounds(reskia_mask_filter_t *mask_filter, const reskia_rect_t *src); // src は非 NULL。NULL 入力では empty rect handle
sk_flattenable_factory_t SkMaskFilter_getFactory(reskia_mask_filter_t *mask_filter); // NULL 入力や factory なしでは 0
const char *SkMaskFilter_getTypeName(reskia_mask_filter_t *mask_filter); // borrowed: 解放不要。NULL 入力では NULL
void SkMaskFilter_flatten(reskia_mask_filter_t *mask_filter, reskia_write_buffer_t *buffer); // buffer は非 NULL。NULL 入力では no-op
reskia_mask_filter_type_t SkMaskFilter_getFlattenableType(reskia_mask_filter_t *mask_filter); // NULL 入力では -1
sk_data_t SkMaskFilter_serialize(reskia_mask_filter_t *mask_filter, const reskia_serial_procs_t *procs); // procs は NULL 許可。NULL 入力や生成不能では 0
/**
 * memory は memory_size > 0 で非 NULL。NULL 入力では 0
 */
size_t SkMaskFilter_serializeToMemory(reskia_mask_filter_t *mask_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs);
bool SkMaskFilter_unique(reskia_mask_filter_t *mask_filter); // NULL 入力では false
void SkMaskFilter_ref(reskia_mask_filter_t *mask_filter); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkMaskFilter_unref(reskia_mask_filter_t *mask_filter); // owned: 参照カウントを減らす。NULL 入力では no-op

// static

sk_mask_filter_t SkMaskFilter_MakeBlur(reskia_mask_filter_blur_style_t style, float sigma, bool respectCTM); // 生成不能では 0
sk_mask_filter_t SkMaskFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs); // data は size > 0 で非 NULL。NULL/空/生成不能では 0
sk_flattenable_factory_t SkMaskFilter_NameToFactory(const char name[]); // name は NUL 終端、非 NULL。未登録/NULL 入力では 0
const char *SkMaskFilter_FactoryToName(sk_flattenable_factory_t factory); // borrowed: 解放不要。factory 0 では NULL
void SkMaskFilter_Register(const char name[], sk_flattenable_factory_t factory); // name 非 NULL、factory 非 0。NULL 入力では no-op

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MASK_FILTER_H
