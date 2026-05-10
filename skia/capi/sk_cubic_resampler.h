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

void SkCubicResampler_delete(reskia_cubic_resampler_t *cubicResampler); // NULL 入力では no-op
sk_cubic_resampler_t SkCubicResampler_Mitchell(); // 成功時は non-zero handle
sk_cubic_resampler_t SkCubicResampler_CatmullRom(); // 成功時は non-zero handle

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CUBIC_RESAMPLER_H
