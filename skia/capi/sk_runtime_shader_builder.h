//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_RUNTIME_SHADER_BUILDER_H
#define RAIA_SKIA_SK_RUNTIME_SHADER_BUILDER_H

#include "../handles/static_sk_runtime_effect_builder_builder_child.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../handles/static_sk_shader.h"

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_runtime_effect_t reskia_runtime_effect_t;
typedef struct reskia_runtime_shader_builder_t reskia_runtime_shader_builder_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_runtime_shader_builder_t *SkRuntimeShaderBuilder_new(int runtime_effect); // (sk_runtime_effect_t runtime_effect) -> SkRuntimeShaderBuilder *
reskia_runtime_shader_builder_t *SkRuntimeShaderBuilder_newCopy(const reskia_runtime_shader_builder_t *builder); // (const SkRuntimeShaderBuilder *builder) -> SkRuntimeShaderBuilder *
void SkRuntimeShaderBuilder_delete(reskia_runtime_shader_builder_t *runtime_shader_builder); // (SkRuntimeShaderBuilder *runtime_shader_builder)
sk_shader_t SkRuntimeShaderBuilder_makeShader(reskia_runtime_shader_builder_t *runtime_shader_builder, const reskia_matrix_t *localMatrix); // (SkRuntimeShaderBuilder *runtime_shader_builder, const SkMatrix *localMatrix) -> sk_shader_t
const reskia_runtime_effect_t *SkRuntimeShaderBuilder_effect(reskia_runtime_shader_builder_t *runtime_shader_builder); // (SkRuntimeShaderBuilder *runtime_shader_builder) -> const SkRuntimeEffect *
sk_runtime_effect_builder_builder_uniform_t SkRuntimeShaderBuilder_uniform(reskia_runtime_shader_builder_t *runtime_shader_builder, int name); // (SkRuntimeShaderBuilder *runtime_shader_builder, string_view_t name) -> sk_runtime_effect_builder_builder_uniform_t
sk_runtime_effect_builder_builder_child_t SkRuntimeShaderBuilder_child(reskia_runtime_shader_builder_t *runtime_shader_builder, int name); // (SkRuntimeShaderBuilder *runtime_shader_builder, string_view_t name) -> sk_runtime_effect_builder_builder_child_t
int SkRuntimeShaderBuilder_uniforms(reskia_runtime_shader_builder_t *runtime_shader_builder); // (SkRuntimeShaderBuilder *runtime_shader_builder) -> const_sk_data_t
int SkRuntimeShaderBuilder_children(reskia_runtime_shader_builder_t *runtime_shader_builder); // (SkRuntimeShaderBuilder *runtime_shader_builder) -> const_sk_runtime_effect_child_ptr_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RUNTIME_SHADER_BUILDER_H
