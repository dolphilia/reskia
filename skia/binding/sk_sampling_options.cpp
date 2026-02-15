//
// Created by dolphilia on 2024/01/11.
//

#include "sk_sampling_options.h"

#include "include/core/SkSamplingOptions.h"

#include "../static/static_sk_sampling_options.h"

#include "../static/static_sk_sampling_options-internal.h"

extern "C" {

//bool operator==(const SkSamplingOptions &other)
//bool operator!=(const SkSamplingOptions &other)
//SkSamplingOptions *SkSamplingOptions_new_3 & operator=(const SkSamplingOptions &that) {
//    return new SkSamplingOptions();
//}

reskia_sampling_options_t *SkSamplingOptions_new() {
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions());
}

reskia_sampling_options_t *SkSamplingOptions_new_2(const reskia_sampling_options_t *options) {
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions(*reinterpret_cast<const SkSamplingOptions *>(options)));
}

reskia_sampling_options_t *SkSamplingOptions_new_3(int fm, int mm) {
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions(static_cast<SkFilterMode>(fm), static_cast<SkMipmapMode>(mm)));
}

reskia_sampling_options_t *SkSamplingOptions_new_4(int fm) {
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions(static_cast<SkFilterMode>(fm)));
}

reskia_sampling_options_t *SkSamplingOptions_new_5(const reskia_cubic_resampler_t *c) {
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions(*reinterpret_cast<const SkCubicResampler *>(c)));
}

void SkSamplingOptions_delete(reskia_sampling_options_t *sampling_options) {
    delete reinterpret_cast<SkSamplingOptions *>(sampling_options);
}

bool SkSamplingOptions_isAniso(reskia_sampling_options_t *sampling_options) {
    return reinterpret_cast<SkSamplingOptions *>(sampling_options)->isAniso();
}

// static

sk_sampling_options_t SkSamplingOptions_Aniso(int maxAniso) {
    return static_sk_sampling_options_make(SkSamplingOptions::Aniso(maxAniso));
}

}
