//
// Created by dolphilia on 2024/01/11.
//

#include "sk_table_mask_filter.h"

#include "include/effects/SkTableMaskFilter.h"

extern "C" {

void SkTableMaskFilter_delete(void *tableMaskFilter) {
    delete static_cast<SkTableMaskFilter *>(tableMaskFilter);
}

// static

void SkTableMaskFilter_MakeGammaTable(void * table, float gamma) {
    SkTableMaskFilter::MakeGammaTable(static_cast<uint8_t *>(table), gamma);
}

void SkTableMaskFilter_MakeClipTable(void * table, uint8_t min, uint8_t max) {
    SkTableMaskFilter::MakeClipTable(static_cast<uint8_t *>(table), min, max);
}

void * SkTableMaskFilter_Create(const void * table) {
    return SkTableMaskFilter::Create(static_cast<const uint8_t *>(table));
}

void * SkTableMaskFilter_CreateGamma(float gamma) {
    return SkTableMaskFilter::CreateGamma(gamma);
}

void * SkTableMaskFilter_CreateClip(uint8_t min, uint8_t max) {
    return SkTableMaskFilter::CreateClip(min, max);
}

}