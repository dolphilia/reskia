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

extern "C" {

//SkRuntimeBlendBuilder(const SkRuntimeBlendBuilder &)=delete
//SkRuntimeBlendBuilder & operator=(const SkRuntimeBlendBuilder &)=delete

reskia_runtime_blend_builder_t *SkRuntimeBlendBuilder_new(sk_runtime_effect_t runtime_effect) {
    return reinterpret_cast<reskia_runtime_blend_builder_t *>(new SkRuntimeBlendBuilder(static_sk_runtime_effect_get_entity(runtime_effect)));
}

void SkRuntimeBlendBuilder_delete(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    delete reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
}

sk_blender_t SkRuntimeBlendBuilder_makeBlender(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    return static_sk_blender_make(reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->makeBlender());
}

const reskia_runtime_effect_t *SkRuntimeBlendBuilder_effect(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    return reinterpret_cast<const reskia_runtime_effect_t *>(reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->effect());
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeBlendBuilder_uniform(reskia_runtime_blend_builder_t *runtime_blend_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_uniform_make(reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->uniform(static_string_view_get_entity(name)));
}

sk_runtime_effect_builder_builder_child_t SkRuntimeBlendBuilder_child(reskia_runtime_blend_builder_t *runtime_blend_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_child_make(reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->child(static_string_view_get_entity(name)));
}

const_sk_data_t SkRuntimeBlendBuilder_uniforms(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    return static_const_sk_data_make(reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->uniforms());
}

const_sk_runtime_effect_child_ptr_t SkRuntimeBlendBuilder_children(reskia_runtime_blend_builder_t *runtime_blend_builder) {
    return static_const_sk_runtime_effect_child_ptr_make(reinterpret_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->children());
}

}
