//
// Created by dolphilia on 2024/01/10.
//

#include "sk_runtime_blend_builder.h"

#include "include/effects/SkRuntimeEffect.h"

#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_runtime_effect.h"
#include "../handles/static_sk_runtime_effect_child_ptr.h"
#include "../handles/static_std_string_view.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../handles/static_sk_runtime_effect_builder_builder_child.h"

#include "../handles/static_sk_runtime_effect_child_ptr-internal.h"
#include "../handles/static_sk_runtime_effect-internal.h"
#include "../handles/static_sk_runtime_effect_builder_builder_child-internal.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform-internal.h"
#include "../handles/static_std_string_view-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_blender-internal.h"

namespace {

bool has_string_view_handle(string_view_t name) {
    return name != 0 && static_string_view_contains(name);
}

} // namespace

extern "C" {

//SkRuntimeBlendBuilder(const SkRuntimeBlendBuilder &)=delete

reskia_runtime_blend_builder_t *SkRuntimeBlendBuilder_new(sk_runtime_effect_t runtime_effect) {
    sk_sp<SkRuntimeEffect> native_effect = static_sk_runtime_effect_get_entity(runtime_effect);
    return native_effect ? reinterpret_cast<reskia_runtime_blend_builder_t *>(new SkRuntimeBlendBuilder(native_effect)) : nullptr;
}

void SkRuntimeBlendBuilder_delete(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    delete reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
}

sk_blender_t SkRuntimeBlendBuilder_makeBlender(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    auto *native = reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
    if (native == nullptr) {
        return 0;
    }
    sk_sp<SkBlender> blender = native->makeBlender();
    return blender ? static_sk_blender_make(blender) : 0;
}

const reskia_runtime_effect_t *SkRuntimeBlendBuilder_effect(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    auto *native = reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
    return native != nullptr ? reinterpret_cast<const reskia_runtime_effect_t *>(native->effect()) : nullptr;
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeBlendBuilder_uniform(reskia_runtime_blend_builder_t *runtime_blend_builder, string_view_t name) {
    auto *native = reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
    return native != nullptr && has_string_view_handle(name) ? static_sk_runtime_effect_builder_builder_uniform_make(native->uniform(static_string_view_get_entity(name))) : 0;
}

sk_runtime_effect_builder_builder_child_t SkRuntimeBlendBuilder_child(reskia_runtime_blend_builder_t *runtime_blend_builder, string_view_t name) {
    auto *native = reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
    return native != nullptr && has_string_view_handle(name) ? static_sk_runtime_effect_builder_builder_child_make(native->child(static_string_view_get_entity(name))) : 0;
}

const_sk_data_t SkRuntimeBlendBuilder_uniforms(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    auto *native = reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
    return native != nullptr ? static_const_sk_data_make(native->uniforms()) : 0;
}

const_sk_runtime_effect_child_ptr_t SkRuntimeBlendBuilder_children(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    auto *native = reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
    return native != nullptr ? static_const_sk_runtime_effect_child_ptr_make(native->children()) : 0;
}

}
