//
// Created by dolphilia on 2024/01/11.
//

#include "sk_sampling_options.h"

#include "include/core/SkSamplingOptions.h"

#include "../handles/static_sk_sampling_options.h"

#include "../handles/static_sk_sampling_options-internal.h"

namespace {

bool is_valid_filter_mode(int fm) {
    return fm >= 0 && fm < kSkFilterModeCount;
}

bool is_valid_mipmap_mode(int mm) {
    return mm >= 0 && mm < kSkMipmapModeCount;
}

} // namespace

extern "C" {

//bool operator==(const SkSamplingOptions &other)
//bool operator!=(const SkSamplingOptions &other)
//SkSamplingOptions *SkSamplingOptions_newCopy & operator=(const SkSamplingOptions &that) {
//    return new SkSamplingOptions();
//}

reskia_sampling_options_t *SkSamplingOptions_new() {
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions());
}

reskia_sampling_options_t *SkSamplingOptions_newCopy(const reskia_sampling_options_t *options) {
    if (options == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions(*reinterpret_cast<const SkSamplingOptions *>(options)));
}

reskia_sampling_options_t *SkSamplingOptions_newWithFilterAndMipmapModes(int fm, int mm) {
    if (!is_valid_filter_mode(fm) || !is_valid_mipmap_mode(mm)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions(static_cast<SkFilterMode>(fm), static_cast<SkMipmapMode>(mm)));
}

reskia_sampling_options_t *SkSamplingOptions_newWithFilterMode(int fm) {
    if (!is_valid_filter_mode(fm)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions(static_cast<SkFilterMode>(fm)));
}

reskia_sampling_options_t *SkSamplingOptions_new_5(const reskia_cubic_resampler_t *c) {
    if (c == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_sampling_options_t *>(new SkSamplingOptions(*reinterpret_cast<const SkCubicResampler *>(c)));
}

void SkSamplingOptions_delete(reskia_sampling_options_t *sampling_options) {
    delete reinterpret_cast<SkSamplingOptions *>(sampling_options);
}

bool SkSamplingOptions_isAniso(reskia_sampling_options_t *sampling_options) {
    if (sampling_options == nullptr) {
        return false;
    }
    return reinterpret_cast<SkSamplingOptions *>(sampling_options)->isAniso();
}

// static

sk_sampling_options_t SkSamplingOptions_Aniso(int maxAniso) {
    return static_sk_sampling_options_make(SkSamplingOptions::Aniso(maxAniso));
}

}
