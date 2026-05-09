//
// Created by dolphilia on 2024/01/11.
//

#include "sk_shader_mask_filter.h"

#include "include/effects/SkShaderMaskFilter.h"

#include "../handles/static_sk_mask_filter.h"
#include "../handles/static_sk_shader.h"

#include "../handles/static_sk_mask_filter-internal.h"
#include "../handles/static_sk_shader-internal.h"

#include <utility>

namespace {

sk_mask_filter_t make_mask_filter_handle(sk_sp<SkMaskFilter> mask_filter) {
    if (!mask_filter) {
        return 0;
    }
    return static_sk_mask_filter_make(std::move(mask_filter));
}

}  // namespace

extern "C" {

void SkShaderMaskFilter_delete(reskia_shader_mask_filter_t *shaderMaskFilter) {
    if (shaderMaskFilter == nullptr) {
        return;
    }
    delete reinterpret_cast<SkShaderMaskFilter *>(shaderMaskFilter);
}

// static

sk_mask_filter_t SkShaderMaskFilter_Make(sk_shader_t shader) {
    if (shader == 0) {
        return 0;
    }
    return make_mask_filter_handle(SkShaderMaskFilter::Make(static_sk_shader_get_entity(shader)));
}

}
