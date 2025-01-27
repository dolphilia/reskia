//
// Created by dolphilia on 2024/01/11.
//

#include "sk_runtime_shader_builder.h"

#include "include/effects/SkRuntimeEffect.h"

#include "../static/static_sk_shader.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_runtime_effect.h"
#include "../static/static_sk_runtime_effect_child_ptr.h"
#include "../static/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../static/static_sk_runtime_effect_builder_builder_child.h"
#include "../static/static_std_string_view.h"

#include "../static/static_sk_runtime_effect_builder_builder_child-internal.h"
#include "../static/static_std_string_view-internal.h"
#include "../static/static_sk_runtime_effect-internal.h"
#include "../static/static_sk_runtime_effect_builder_builder_uniform-internal.h"
#include "../static/static_sk_runtime_effect_child_ptr-internal.h"
#include "../static/static_sk_shader-internal.h"

#include "../static/static_sk_data-internal.h"

extern "C" {

void *SkRuntimeShaderBuilder_new(sk_runtime_effect_t runtime_effect) {
    return new SkRuntimeShaderBuilder(static_sk_runtime_effect_move(runtime_effect));
}

void *SkRuntimeShaderBuilder_new_2(const void *builder) {
    return new SkRuntimeShaderBuilder(* static_cast<const SkRuntimeShaderBuilder *>(builder));
}

void SkRuntimeShaderBuilder_delete(void *runtime_shader_builder) {
    delete static_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder);
}

sk_shader_t SkRuntimeShaderBuilder_makeShader(void *runtime_shader_builder, const void *localMatrix) {
    return static_sk_shader_make(static_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->makeShader(static_cast<const SkMatrix *>(localMatrix)));
}

const void * SkRuntimeShaderBuilder_effect(void *runtime_shader_builder) {
    return static_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->effect();
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeShaderBuilder_uniform(void *runtime_shader_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_uniform_make(static_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->uniform(static_string_view_get(name)));
}

sk_runtime_effect_builder_builder_child_t SkRuntimeShaderBuilder_child(void *runtime_shader_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_child_make(static_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->child(static_string_view_get(name)));
}

const_sk_data_t SkRuntimeShaderBuilder_uniforms(void *runtime_shader_builder) {
    return static_const_sk_data_make(static_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->uniforms());
}

const_sk_runtime_effect_child_ptr_t SkRuntimeShaderBuilder_children(void *runtime_shader_builder) {
    return static_const_sk_runtime_effect_child_ptr_make(static_cast<SkRuntimeShaderBuilder *>(runtime_shader_builder)->children());
}

}
