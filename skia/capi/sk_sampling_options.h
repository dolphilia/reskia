//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_SAMPLING_OPTIONS_H
#define RAIA_SKIA_SK_SAMPLING_OPTIONS_H

#include "../handles/static_sk_sampling_options.h"

typedef struct reskia_cubic_resampler_t reskia_cubic_resampler_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;

#ifdef __cplusplus
extern "C" {
#endif

//bool operator==(const SkSamplingOptions &other)
//bool operator!=(const SkSamplingOptions &other)
//SkSamplingOptions *SkSamplingOptions_newCopy & operator=(const SkSamplingOptions &that)

reskia_sampling_options_t *SkSamplingOptions_new(); // () -> SkSamplingOptions *
reskia_sampling_options_t *SkSamplingOptions_newCopy(const reskia_sampling_options_t *options); // (const SkSamplingOptions *options) -> SkSamplingOptions *
reskia_sampling_options_t *SkSamplingOptions_newWithFilterAndMipmapModes(int fm, int mm); // (SkFilterMode fm, SkMipmapMode mm) -> SkSamplingOptions *
reskia_sampling_options_t *SkSamplingOptions_newWithFilterMode(int fm); // (SkFilterMode fm) -> SkSamplingOptions *
reskia_sampling_options_t *SkSamplingOptions_new_5(const reskia_cubic_resampler_t *c); // (const SkCubicResampler *c) -> SkSamplingOptions *
void SkSamplingOptions_delete(reskia_sampling_options_t *sampling_options); // (SkSamplingOptions *sampling_options)
bool SkSamplingOptions_isAniso(reskia_sampling_options_t *sampling_options); // (SkSamplingOptions *sampling_options) -> bool

// static

sk_sampling_options_t SkSamplingOptions_Aniso(int maxAniso); // (int maxAniso) -> sk_sampling_options_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SAMPLING_OPTIONS_H
