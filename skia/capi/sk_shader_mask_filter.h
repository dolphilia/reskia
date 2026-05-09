//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_SHADER_MASK_FILTER_H
#define RAIA_SKIA_SK_SHADER_MASK_FILTER_H

#include "../handles/static_sk_mask_filter.h"
#include "../handles/static_sk_shader.h"

typedef struct reskia_shader_mask_filter_t reskia_shader_mask_filter_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkShaderMaskFilter_delete(reskia_shader_mask_filter_t *shaderMaskFilter); // NULL 入力では no-op

// static

sk_mask_filter_t SkShaderMaskFilter_Make(sk_shader_t shader); // shader handle 0 や生成不能では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SHADER_MASK_FILTER_H
