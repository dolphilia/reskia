//
// Created by dolphilia on 2024/01/11.
//

#include "sk_runtime_effect_builder.h"

#include "include/effects/SkRuntimeEffect.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_runtime_effect_child_ptr.h"
#include "../static/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../static/static_sk_runtime_effect_builder_builder_child.h"
#include "../static/static_std_string_view.h"

#include "../static/static_sk_runtime_effect_builder_builder_child-internal.h"
#include "../static/static_sk_runtime_effect_builder_builder_uniform-internal.h"
#include "../static/static_sk_runtime_effect_child_ptr-internal.h"
#include "../static/static_std_string_view-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkRuntimeEffectBuilder_delete(void *runtime_effect_builder) {
    delete static_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder);
}

const void * SkRuntimeEffectBuilder_effect(void *runtime_effect_builder) {
    return static_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder)->effect();
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeEffectBuilder_uniform(void *runtime_effect_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_uniform_make(static_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder)->uniform(static_string_view_get_entity(name)));
}

sk_runtime_effect_builder_builder_child_t SkRuntimeEffectBuilder_child(void *runtime_effect_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_child_make(static_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder)->child(static_string_view_get_entity(name)));
}

const_sk_data_t SkRuntimeEffectBuilder_uniforms(void *runtime_effect_builder) {
    return static_const_sk_data_make(static_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder)->uniforms());
}

const_sk_runtime_effect_child_ptr_t SkRuntimeEffectBuilder_children(void *runtime_effect_builder) {
    return static_const_sk_runtime_effect_child_ptr_make(static_cast<SkRuntimeEffectBuilder *>(runtime_effect_builder)->children());
}

// static

// SkRuntimeEffectBuilder()=delete
// SkRuntimeEffectBuilder(sk_sp<SkRuntimeEffect> effect)
// SkRuntimeEffectBuilder(sk_sp<SkRuntimeEffect> effect, sk_sp<SkData> uniforms)
// SkRuntimeEffectBuilder(SkRuntimeEffectBuilder &&)
// SkRuntimeEffectBuilder(const SkRuntimeEffectBuilder &)
// SkRuntimeEffectBuilder & operator=(SkRuntimeEffectBuilder &&)=delete
// SkRuntimeEffectBuilder & operator=(const SkRuntimeEffectBuilder &)=delete

}
