//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_LUMA_COLOR_FILTER_H
#define RAIA_SKIA_SK_LUMA_COLOR_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../static/static_sk_color_filter.h"

void SkLumaColorFilter_delete(void * lumaColorFilter); // (SkLumaColorFilter * lumaColorFilter)

// static

sk_color_filter_t SkLumaColorFilter_Make(); // () -> sk_color_filter_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_LUMA_COLOR_FILTER_H
