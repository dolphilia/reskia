//
// Created by dolphilia on 2024/01/08.
//

#include "sk_cubic_resampler.h"

#include "include/core/SkSamplingOptions.h"

#include "../static/static_sk_cubic_resampler.h"

#include "../static/static_sk_cubic_resampler-internal.h"

extern "C" {

void SkCubicResampler_delete(void *cubicResampler) {
    delete static_cast<SkCubicResampler *>(cubicResampler);
}

sk_cubic_resampler_t SkCubicResampler_Mitchell() {
    return static_sk_cubic_resampler_make(SkCubicResampler::Mitchell());
}

sk_cubic_resampler_t SkCubicResampler_CatmullRom() {
    return static_sk_cubic_resampler_make(SkCubicResampler::CatmullRom());
}

}
