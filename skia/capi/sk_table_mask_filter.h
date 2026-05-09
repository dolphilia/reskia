//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TABLE_MASK_FILTER_H
#define RAIA_SKIA_SK_TABLE_MASK_FILTER_H

#include <stdint.h>

typedef struct reskia_mask_filter_t reskia_mask_filter_t;
typedef struct reskia_table_mask_filter_t reskia_table_mask_filter_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkTableMaskFilter_delete(reskia_table_mask_filter_t *tableMaskFilter); // NULL 入力では no-op

// static

void SkTableMaskFilter_MakeGammaTable(uint8_t * table, float gamma); // table は 256 要素以上、非 NULL。NULL 入力では no-op
void SkTableMaskFilter_MakeClipTable(uint8_t * table, uint8_t min, uint8_t max); // table は 256 要素以上、非 NULL。NULL 入力では no-op
reskia_mask_filter_t *SkTableMaskFilter_Create(const uint8_t * table); // table は 256 要素以上、非 NULL。NULL 入力や生成不能では NULL。owned ref
reskia_mask_filter_t *SkTableMaskFilter_CreateGamma(float gamma); // 生成不能では NULL。owned ref
reskia_mask_filter_t *SkTableMaskFilter_CreateClip(uint8_t min, uint8_t max); // 生成不能では NULL。owned ref

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TABLE_MASK_FILTER_H
