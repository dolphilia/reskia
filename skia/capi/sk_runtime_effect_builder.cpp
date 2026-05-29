//
// Created by dolphilia on 2024/01/11.
//

#include "sk_runtime_effect_builder.h"

#include "include/effects/SkRuntimeEffect.h"

#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_runtime_effect.h"
#include "../handles/static_sk_runtime_effect_child_ptr.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../handles/static_sk_runtime_effect_builder_builder_child.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_std_string_view.h"

#include "../handles/static_sk_blender-internal.h"
#include "../handles/static_sk_color_filter-internal.h"
#include "../handles/static_sk_runtime_effect_builder_builder_child-internal.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform-internal.h"
#include "../handles/static_sk_runtime_effect_child_ptr-internal.h"
#include "../handles/static_sk_runtime_effect-internal.h"
#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_std_string_view-internal.h"
#include "../handles/static_sk_data-internal.h"

namespace {

bool has_string_view_handle(string_view_t name) {
    return name != 0 && static_string_view_contains(name);
}

} // namespace

extern "C" {

reskia_runtime_effect_builder_t *SkRuntimeEffectBuilder_new(sk_runtime_effect_t runtime_effect) {
    sk_sp<SkRuntimeEffect> native_effect = static_sk_runtime_effect_get_entity(runtime_effect);
    return native_effect ? reinterpret_cast<reskia_runtime_effect_builder_t *>(new SkRuntimeEffectBuilder(native_effect)) : nullptr;
}

reskia_runtime_effect_builder_t *SkRuntimeEffectBuilder_newWithUniforms(sk_runtime_effect_t runtime_effect, sk_data_t uniforms) {
    sk_sp<SkRuntimeEffect> native_effect = static_sk_runtime_effect_get_entity(runtime_effect);
    sk_sp<SkData> native_uniforms = static_sk_data_get_entity(uniforms);
    if (!native_effect || !native_uniforms) {
        return nullptr;
    }
    return reinterpret_cast<reskia_runtime_effect_builder_t *>(new SkRuntimeEffectBuilder(native_effect, native_uniforms));
}

reskia_runtime_effect_builder_t *SkRuntimeEffectBuilder_newCopy(const reskia_runtime_effect_builder_t *builder) {
    return builder != nullptr ? reinterpret_cast<reskia_runtime_effect_builder_t *>(new SkRuntimeEffectBuilder(*reinterpret_cast<const SkRuntimeEffectBuilder *>(builder))) : nullptr;
}

void SkRuntimeEffectBuilder_delete(reskia_runtime_effect_builder_t *runtime_effect_builder) {
    delete reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
}

sk_shader_t SkRuntimeEffectBuilder_makeShader(reskia_runtime_effect_builder_t *runtime_effect_builder, const reskia_matrix_t *localMatrix) {
    auto *native = reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
    if (native == nullptr) {
        return 0;
    }
    sk_sp<SkShader> shader = native->makeShader(reinterpret_cast<const SkMatrix *>(localMatrix));
    return shader ? static_sk_shader_make(shader) : 0;
}

sk_color_filter_t SkRuntimeEffectBuilder_makeColorFilter(reskia_runtime_effect_builder_t *runtime_effect_builder) {
    auto *native = reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
    if (native == nullptr) {
        return 0;
    }
    sk_sp<SkColorFilter> color_filter = native->makeColorFilter();
    return color_filter ? static_sk_color_filter_make(color_filter) : 0;
}

sk_blender_t SkRuntimeEffectBuilder_makeBlender(reskia_runtime_effect_builder_t *runtime_effect_builder) {
    auto *native = reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
    if (native == nullptr) {
        return 0;
    }
    sk_sp<SkBlender> blender = native->makeBlender();
    return blender ? static_sk_blender_make(blender) : 0;
}

const reskia_runtime_effect_t *SkRuntimeEffectBuilder_effect(reskia_runtime_effect_builder_t *runtime_effect_builder) {
    auto *native = reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
    return native != nullptr ? reinterpret_cast<const reskia_runtime_effect_t *>(native->effect()) : nullptr;
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeEffectBuilder_uniform(reskia_runtime_effect_builder_t *runtime_effect_builder, string_view_t name) {
    auto *native = reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
    return native != nullptr && has_string_view_handle(name) ? static_sk_runtime_effect_builder_builder_uniform_make(native->uniform(static_string_view_get_entity(name))) : 0;
}

sk_runtime_effect_builder_builder_child_t SkRuntimeEffectBuilder_child(reskia_runtime_effect_builder_t *runtime_effect_builder, string_view_t name) {
    auto *native = reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
    return native != nullptr && has_string_view_handle(name) ? static_sk_runtime_effect_builder_builder_child_make(native->child(static_string_view_get_entity(name))) : 0;
}

const_sk_data_t SkRuntimeEffectBuilder_uniforms(reskia_runtime_effect_builder_t *runtime_effect_builder) {
    auto *native = reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
    return native != nullptr ? static_const_sk_data_make(native->uniforms()) : 0;
}

const_sk_runtime_effect_child_ptr_t SkRuntimeEffectBuilder_children(reskia_runtime_effect_builder_t *runtime_effect_builder) {
    auto *native = reinterpret_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
    return native != nullptr ? static_const_sk_runtime_effect_child_ptr_make(native->children()) : 0;
}

// static

// SkRuntimeEffectBuilder()=delete
// SkRuntimeEffectBuilder(SkRuntimeEffectBuilder &&)
// SkRuntimeEffectBuilder & operator=(SkRuntimeEffectBuilder &&)=delete
// SkRuntimeEffectBuilder & operator=(const SkRuntimeEffectBuilder &)=delete

}
