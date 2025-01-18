//
// Created by dolphilia on 2024/01/08.
//

#include "sk_high_contrast_filter.h"

#include "include/effects/SkHighContrastFilter.h"

#include "../static/static_sk_color_filter.h"

#include "../static/static_sk_color_filter-internal.h"

extern "C" {

void SkHighContrastFilter_delete(void * highContrastFilter) {
    delete static_cast<SkHighContrastFilter *>(highContrastFilter);
}

// static

sk_color_filter_t SkHighContrastFilter_Make(const void * config) {
    return static_sk_color_filter_make(SkHighContrastFilter::Make(* static_cast<const SkHighContrastConfig *>(config)));
}

}
