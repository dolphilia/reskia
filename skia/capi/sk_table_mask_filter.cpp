//
// Created by dolphilia on 2024/01/11.
//

#include "sk_table_mask_filter.h"

#include "include/effects/SkTableMaskFilter.h"

extern "C" {

void SkTableMaskFilter_delete(reskia_table_mask_filter_t *tableMaskFilter) {
    delete reinterpret_cast<SkTableMaskFilter *>(tableMaskFilter);
}

// static

void SkTableMaskFilter_MakeGammaTable(uint8_t * table, float gamma) {
    SkTableMaskFilter::MakeGammaTable(table, gamma);
}

void SkTableMaskFilter_MakeClipTable(uint8_t * table, uint8_t min, uint8_t max) {
    SkTableMaskFilter::MakeClipTable(table, min, max);
}

reskia_mask_filter_t *SkTableMaskFilter_Create(const uint8_t * table) {
    return reinterpret_cast<reskia_mask_filter_t *>(SkTableMaskFilter::Create(table));
}

reskia_mask_filter_t *SkTableMaskFilter_CreateGamma(float gamma) {
    return reinterpret_cast<reskia_mask_filter_t *>(SkTableMaskFilter::CreateGamma(gamma));
}

reskia_mask_filter_t *SkTableMaskFilter_CreateClip(uint8_t min, uint8_t max) {
    return reinterpret_cast<reskia_mask_filter_t *>(SkTableMaskFilter::CreateClip(min, max));
}

}
