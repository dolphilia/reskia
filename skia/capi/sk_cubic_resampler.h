//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_CUBIC_RESAMPLER_H
#define RAIA_SKIA_SK_CUBIC_RESAMPLER_H

#include "../handles/static_sk_cubic_resampler.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_cubic_resampler_t reskia_cubic_resampler_t;

void SkCubicResampler_delete(reskia_cubic_resampler_t *cubicResampler); // No-op for NULL input.
sk_cubic_resampler_t SkCubicResampler_Mitchell(); // Returns a nonzero handle on success.
sk_cubic_resampler_t SkCubicResampler_CatmullRom(); // Returns a nonzero handle on success.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CUBIC_RESAMPLER_H
