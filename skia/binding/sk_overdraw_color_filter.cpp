//
// Created by dolphilia on 2024/01/09.
//

#include "sk_overdraw_color_filter.h"

#include "include/effects/SkOverdrawColorFilter.h"

#include "../static/static_sk_color_filter.h"

#include "../static/static_sk_color_filter-internal.h"

extern "C" {

void SkOverdrawColorFilter_delete(void * overdrawColorFilter) {
    delete static_cast<SkOverdrawColorFilter *>(overdrawColorFilter);
}

// static
sk_color_filter_t SkOverdrawColorFilter_MakeWithSkColors(const void * color) {
    return static_sk_color_filter_make(SkOverdrawColorFilter::MakeWithSkColors(static_cast<const SkColor *>(color)));
}

}
