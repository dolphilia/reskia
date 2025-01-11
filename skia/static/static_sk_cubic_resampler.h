//
// Created by dolphilia on 2024/04/03.
//

#ifndef RAIA_SKIA_STATIC_SK_CUBIC_RESAMPLER_H
#define RAIA_SKIA_STATIC_SK_CUBIC_RESAMPLER_H

#include <set>
#include <map>
#include "include/core/SkSamplingOptions.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_cubic_resampler_t;
void static_sk_cubic_resampler_delete(int key);
SkCubicResampler * static_sk_cubic_resampler_get_ptr(int key);
#ifdef __cplusplus
}
#endif

int static_sk_cubic_resampler_make(SkCubicResampler value);
SkCubicResampler static_sk_cubic_resampler_get(int key);

#endif //RAIA_SKIA_STATIC_SK_CUBIC_RESAMPLER_H
