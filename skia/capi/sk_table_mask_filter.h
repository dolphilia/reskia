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

void SkTableMaskFilter_delete(reskia_table_mask_filter_t *tableMaskFilter); // (SkTableMaskFilter *tableMaskFilter)

// static

void SkTableMaskFilter_MakeGammaTable(uint8_t * table, float gamma); // (uint8_t table[256], SkScalar gamma)
void SkTableMaskFilter_MakeClipTable(uint8_t * table, uint8_t min, uint8_t max); // (uint8_t table[256], uint8_t min, uint8_t max)
reskia_mask_filter_t *SkTableMaskFilter_Create(const uint8_t * table); // (const uint8_t table[256]) -> SkMaskFilter *
reskia_mask_filter_t *SkTableMaskFilter_CreateGamma(float gamma); // (SkScalar gamma) -> SkMaskFilter *
reskia_mask_filter_t *SkTableMaskFilter_CreateClip(uint8_t min, uint8_t max); // (uint8_t min, uint8_t max) -> SkMaskFilter *

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TABLE_MASK_FILTER_H
