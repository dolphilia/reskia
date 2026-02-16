//
// Created by dolphilia on 2024/01/11.
//

#include "sk_runtime_shader_builder.h"

#include "include/effects/SkRuntimeEffect.h"

#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_runtime_effect.h"
#include "../handles/static_sk_runtime_effect_child_ptr.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../handles/static_sk_runtime_effect_builder_builder_child.h"
#include "../handles/static_std_string_view.h"

#include "../handles/static_sk_runtime_effect_builder_builder_child-internal.h"
#include "../handles/static_std_string_view-internal.h"
#include "../handles/static_sk_runtime_effect-internal.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform-internal.h"
#include "../handles/static_sk_runtime_effect_child_ptr-internal.h"
#include "../handles/static_sk_shader-internal.h"

#include "../handles/static_sk_data-internal.h"

extern "C" {

reskia_runtime_shader_builder_t *SkRuntimeShaderBuilder_new(sk_runtime_effect_t runtime_effect) {
    return reinterpret_cast<reskia_runtime_shader_builder_t *>(new SkRuntimeShaderBuilder(static_sk_runtime_effect_get_entity(runtime_effect)));
}

reskia_runtime_shader_builder_t *SkRuntimeShaderBuilder_newCopy(const reskia_runtime_shader_builder_t *builder) {
    return reinterpret_cast<reskia_runtime_shader_builder_t *>(new SkRuntimeShaderBuilder(*reinterpret_cast<const SkRuntimeShaderBuilder *>(builder)));
}

void SkRuntimeShaderBuilder_delete(reskia_runtime_shader_builder_t *runtime_shader_builder) {
    delete reinterpret_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder);
}

sk_shader_t SkRuntimeShaderBuilder_makeShader(reskia_runtime_shader_builder_t *runtime_shader_builder, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(reinterpret_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->makeShader(reinterpret_cast<const SkMatrix *>(localMatrix)));
}

const reskia_runtime_effect_t *SkRuntimeShaderBuilder_effect(reskia_runtime_shader_builder_t *runtime_shader_builder) {
    return reinterpret_cast<const reskia_runtime_effect_t *>(reinterpret_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->effect());
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeShaderBuilder_uniform(reskia_runtime_shader_builder_t *runtime_shader_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_uniform_make(reinterpret_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->uniform(static_string_view_get_entity(name)));
}

sk_runtime_effect_builder_builder_child_t SkRuntimeShaderBuilder_child(reskia_runtime_shader_builder_t *runtime_shader_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_child_make(reinterpret_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->child(static_string_view_get_entity(name)));
}

const_sk_data_t SkRuntimeShaderBuilder_uniforms(reskia_runtime_shader_builder_t *runtime_shader_builder) {
    return static_const_sk_data_make(reinterpret_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->uniforms());
}

const_sk_runtime_effect_child_ptr_t SkRuntimeShaderBuilder_children(reskia_runtime_shader_builder_t *runtime_shader_builder) {
    return static_const_sk_runtime_effect_child_ptr_make(reinterpret_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->children());
}

}
