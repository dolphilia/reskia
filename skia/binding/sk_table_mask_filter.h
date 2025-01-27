//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TABLE_MASK_FILTER_H
#define RAIA_SKIA_SK_TABLE_MASK_FILTER_H

#include "include/effects/SkTableMaskFilter.h"

extern "C" {

void SkTableMaskFilter_delete(SkTableMaskFilter *tableMaskFilter); // (SkTableMaskFilter *tableMaskFilter)

// static

void SkTableMaskFilter_MakeGammaTable(uint8_t table[256], SkScalar gamma); // (uint8_t table[256], SkScalar gamma)
void SkTableMaskFilter_MakeClipTable(uint8_t table[256], uint8_t min, uint8_t max); // (uint8_t table[256], uint8_t min, uint8_t max)
SkMaskFilter * SkTableMaskFilter_Create(const uint8_t table[256]); // (const uint8_t table[256]) -> SkMaskFilter *
SkMaskFilter * SkTableMaskFilter_CreateGamma(SkScalar gamma); // (SkScalar gamma) -> SkMaskFilter *
SkMaskFilter * SkTableMaskFilter_CreateClip(uint8_t min, uint8_t max); // (uint8_t min, uint8_t max) -> SkMaskFilter *

}

#endif //RAIA_SKIA_SK_TABLE_MASK_FILTER_H
