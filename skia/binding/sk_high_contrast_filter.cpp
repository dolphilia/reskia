//
// Created by dolphilia on 2024/01/08.
//

#include "sk_high_contrast_filter.h"

#include "../static/static_sk_color_filter-internal.h"

extern "C" {

void SkHighContrastFilter_delete(SkHighContrastFilter * highContrastFilter) {
    delete highContrastFilter;
}

// static

sk_color_filter_t SkHighContrastFilter_Make(const SkHighContrastConfig * config) {
    return static_sk_color_filter_make(SkHighContrastFilter::Make(*config));
}

}
