//
// Created by dolphilia on 2024/01/10.
//

#include "sk_runtime_blend_builder.h"

#include "include/effects/SkRuntimeEffect.h"

#include "../static/static_sk_blender.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_runtime_effect.h"
#include "../static/static_sk_runtime_effect_child_ptr.h"
#include "../static/static_std_string_view.h"
#include "../static/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../static/static_sk_runtime_effect_builder_builder_child.h"

#include "../static/static_sk_runtime_effect_child_ptr-internal.h"
#include "../static/static_sk_runtime_effect-internal.h"
#include "../static/static_sk_runtime_effect_builder_builder_child-internal.h"
#include "../static/static_sk_runtime_effect_builder_builder_uniform-internal.h"
#include "../static/static_std_string_view-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_blender-internal.h"

extern "C" {

//SkRuntimeBlendBuilder(const SkRuntimeBlendBuilder &)=delete
//SkRuntimeBlendBuilder & operator=(const SkRuntimeBlendBuilder &)=delete

void *SkRuntimeBlendBuilder_new(sk_runtime_effect_t runtime_effect) {
    return new SkRuntimeBlendBuilder(static_sk_runtime_effect_get_entity(runtime_effect));
}

void SkRuntimeBlendBuilder_delete(void *runtime_blend_builder) {
    delete static_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder);
}

sk_blender_t SkRuntimeBlendBuilder_makeBlender(void *runtime_blend_builder) {
    return static_sk_blender_make(static_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->makeBlender());
}

const void * SkRuntimeBlendBuilder_effect(void *runtime_blend_builder) {
    return static_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->effect();
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeBlendBuilder_uniform(void *runtime_blend_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_uniform_make(static_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->uniform(static_string_view_get_entity(name)));
}

sk_runtime_effect_builder_builder_child_t SkRuntimeBlendBuilder_child(void *runtime_blend_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_child_make(static_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->child(static_string_view_get_entity(name)));
}

const_sk_data_t SkRuntimeBlendBuilder_uniforms(void *runtime_blend_builder) {
    return static_const_sk_data_make(static_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->uniforms());
}

const_sk_runtime_effect_child_ptr_t SkRuntimeBlendBuilder_children(void *runtime_blend_builder) {
    return static_const_sk_runtime_effect_child_ptr_make(static_cast<SkRuntimeBlendBuilder *>(runtime_blend_builder)->children());
}

}
