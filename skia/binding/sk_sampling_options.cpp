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

void *SkSamplingOptions_new() {
    return new SkSamplingOptions();
}

void *SkSamplingOptions_new_2(const void *options) {
    return new SkSamplingOptions(* static_cast<const SkSamplingOptions *>(options));
}

void *SkSamplingOptions_new_3(int fm, int mm) {
    return new SkSamplingOptions(static_cast<SkFilterMode>(fm), static_cast<SkMipmapMode>(mm));
}

void *SkSamplingOptions_new_4(int fm) {
    return new SkSamplingOptions(static_cast<SkFilterMode>(fm));
}

void *SkSamplingOptions_new_5(const void *c) {
    return new SkSamplingOptions(* static_cast<const SkCubicResampler *>(c));
}

void SkSamplingOptions_delete(void *sampling_options) {
    delete static_cast<SkSamplingOptions *>(sampling_options);
}

bool SkSamplingOptions_isAniso(void *sampling_options) {
    return static_cast<SkSamplingOptions *>(sampling_options)->isAniso();
}

// static

sk_sampling_options_t SkSamplingOptions_Aniso(int maxAniso) {
    return static_sk_sampling_options_make(SkSamplingOptions::Aniso(maxAniso));
}

}
