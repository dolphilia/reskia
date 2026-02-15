//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_HIGH_CONTRAST_FILTER_H
#define RAIA_SKIA_SK_HIGH_CONTRAST_FILTER_H

#include "../static/static_sk_color_filter.h"

#ifdef __cplusplus
extern "C" {
#endif

void SkHighContrastFilter_delete(void * highContrastFilter); // (SkHighContrastFilter * highContrastFilter)

// static

sk_color_filter_t SkHighContrastFilter_Make(const void * config); // (const SkHighContrastConfig * config) -> sk_color_filter_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_HIGH_CONTRAST_FILTER_H
