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

void SkTableMaskFilter_delete(reskia_table_mask_filter_t *tableMaskFilter); // No-op for NULL input.

// static

void SkTableMaskFilter_MakeGammaTable(uint8_t * table, float gamma); // table must contain at least 256 elements and be non-NULL. No-op for NULL input.
void SkTableMaskFilter_MakeClipTable(uint8_t * table, uint8_t min, uint8_t max); // table must contain at least 256 elements and be non-NULL. No-op for NULL input.
reskia_mask_filter_t *SkTableMaskFilter_Create(const uint8_t * table); // table must contain at least 256 elements and be non-NULL. Returns NULL for NULL input or creation failure. Owned reference.
reskia_mask_filter_t *SkTableMaskFilter_CreateGamma(float gamma); // Returns NULL on creation failure. Owned reference.
reskia_mask_filter_t *SkTableMaskFilter_CreateClip(uint8_t min, uint8_t max); // Returns NULL on creation failure. Owned reference.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TABLE_MASK_FILTER_H
