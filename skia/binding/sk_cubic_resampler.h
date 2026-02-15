//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_CUBIC_RESAMPLER_H
#define RAIA_SKIA_SK_CUBIC_RESAMPLER_H

#include "../static/static_sk_cubic_resampler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_cubic_resampler_t reskia_cubic_resampler_t;

void SkCubicResampler_delete(reskia_cubic_resampler_t *cubicResampler); // (SkCubicResampler *cubicResampler)
sk_cubic_resampler_t SkCubicResampler_Mitchell(); // () -> sk_cubic_resampler_t
sk_cubic_resampler_t SkCubicResampler_CatmullRom(); // () -> sk_cubic_resampler_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CUBIC_RESAMPLER_H
