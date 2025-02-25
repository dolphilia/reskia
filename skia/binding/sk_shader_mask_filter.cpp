//
// Created by dolphilia on 2024/01/11.
//

#include "sk_shader_mask_filter.h"

#include "include/effects/SkShaderMaskFilter.h"

#include "../static/static_sk_mask_filter.h"
#include "../static/static_sk_shader.h"

#include "../static/static_sk_mask_filter-internal.h"
#include "../static/static_sk_shader-internal.h"

extern "C" {

void SkShaderMaskFilter_delete(void *shaderMaskFilter) {
    delete static_cast<SkShaderMaskFilter *>(shaderMaskFilter);
}

// static

sk_mask_filter_t SkShaderMaskFilter_Make(sk_shader_t shader) {
    return static_sk_mask_filter_make(SkShaderMaskFilter::Make(static_sk_shader_get_entity(shader)));
}

}
