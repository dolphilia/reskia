//
// Created by dolphilia on 2024/01/09.
//

#include "sk_luma_color_filter.h"

#include "include/effects/SkLumaColorFilter.h"

#include "../static/static_sk_color_filter.h"

#include "../static/static_sk_color_filter-internal.h"

extern "C" {

void SkLumaColorFilter_delete(void * lumaColorFilter) {
    reinterpret_cast<SkColorFilter *>(lumaColorFilter)->unref();
}

// static

sk_color_filter_t SkLumaColorFilter_Make() {
    return static_sk_color_filter_make(SkLumaColorFilter::Make());
}

}
