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

//SkSamplingOptions *SkSamplingOptions_newCopy & operator=(const SkSamplingOptions &that)

reskia_sampling_options_t *SkSamplingOptions_new(); // Returns a caller-owned sampling options pointer.
reskia_sampling_options_t *SkSamplingOptions_newCopy(const reskia_sampling_options_t *options); // options is required; NULL returns NULL.
reskia_sampling_options_t *SkSamplingOptions_newWithFilterAndMipmapModes(int fm, int mm); // Invalid filter or mipmap mode returns NULL.
reskia_sampling_options_t *SkSamplingOptions_newWithFilterMode(int fm); // Invalid filter mode returns NULL.
reskia_sampling_options_t *SkSamplingOptions_new_5(const reskia_cubic_resampler_t *c); // c is required; NULL returns NULL.
void SkSamplingOptions_delete(reskia_sampling_options_t *sampling_options); // NULL sampling_options is no-op.
bool SkSamplingOptions_equals(reskia_sampling_options_t *sampling_options, const reskia_sampling_options_t *other); // NULL input returns false.
bool SkSamplingOptions_notEquals(reskia_sampling_options_t *sampling_options, const reskia_sampling_options_t *other); // NULL input returns false.
bool SkSamplingOptions_isAniso(reskia_sampling_options_t *sampling_options); // NULL sampling_options returns false.

// static

sk_sampling_options_t SkSamplingOptions_Aniso(int maxAniso); // Returns a caller-owned handle; Skia clamps maxAniso to at least 1.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SAMPLING_OPTIONS_H
