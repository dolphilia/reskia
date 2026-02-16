//
// Created by dolphilia on 2024/01/08.
//

#include "sk_high_contrast_filter.h"

#include "include/effects/SkHighContrastFilter.h"

#include "../handles/static_sk_color_filter.h"

#include "../handles/static_sk_color_filter-internal.h"

extern "C" {

void SkHighContrastFilter_delete(void * highContrastFilter) {
    reinterpret_cast<SkColorFilter *>(highContrastFilter)->unref();
}

// static

sk_color_filter_t SkHighContrastFilter_Make(const void * config) {
    return static_sk_color_filter_make(SkHighContrastFilter::Make(* static_cast<const SkHighContrastConfig *>(config)));
}

}
