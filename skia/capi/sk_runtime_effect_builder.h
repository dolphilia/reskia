//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_RUNTIME_EFFECT_BUILDER_H
#define RAIA_SKIA_SK_RUNTIME_EFFECT_BUILDER_H

#include "../handles/static_sk_runtime_effect_builder_builder_child.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform.h"

typedef struct reskia_runtime_effect_builder_t reskia_runtime_effect_builder_t;
typedef struct reskia_runtime_effect_t reskia_runtime_effect_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkRuntimeEffectBuilder_delete(reskia_runtime_effect_builder_t *runtime_effect_builder); // NULL builder は no-op (SkRuntimeEffectBuilder *runtime_effect_builder)
const reskia_runtime_effect_t *SkRuntimeEffectBuilder_effect(reskia_runtime_effect_builder_t *runtime_effect_builder); // NULL builder なら NULL (SkRuntimeEffectBuilder *runtime_effect_builder) -> const SkRuntimeEffect *
sk_runtime_effect_builder_builder_uniform_t SkRuntimeEffectBuilder_uniform(reskia_runtime_effect_builder_t *runtime_effect_builder, int name); // builder/name must be valid; returned proxy handle is caller-owned; invalid input returns 0 (SkRuntimeEffectBuilder *runtime_effect_builder, string_view_t name) -> sk_runtime_effect_builder_builder_uniform_t
sk_runtime_effect_builder_builder_child_t SkRuntimeEffectBuilder_child(reskia_runtime_effect_builder_t *runtime_effect_builder, int name); // builder/name must be valid; returned proxy handle is caller-owned; invalid input returns 0 (SkRuntimeEffectBuilder *runtime_effect_builder, string_view_t name) -> sk_runtime_effect_builder_builder_child_t
int SkRuntimeEffectBuilder_uniforms(reskia_runtime_effect_builder_t *runtime_effect_builder); // returned handle is caller-owned and deleted with static_const_sk_data_delete; NULL builder なら 0 (SkRuntimeEffectBuilder *runtime_effect_builder) -> const_sk_data_t
int SkRuntimeEffectBuilder_children(reskia_runtime_effect_builder_t *runtime_effect_builder); // returned handle is caller-owned and deleted with static_const_sk_runtime_effect_child_ptr_delete; NULL builder なら 0 (SkRuntimeEffectBuilder *runtime_effect_builder) -> const_sk_runtime_effect_child_ptr_t

// static

// SkRuntimeEffectBuilder()=delete
// SkRuntimeEffectBuilder(sk_sp<SkRuntimeEffect> effect)
// SkRuntimeEffectBuilder(sk_sp<SkRuntimeEffect> effect, sk_sp<SkData> uniforms)
// SkRuntimeEffectBuilder(SkRuntimeEffectBuilder &&)
// SkRuntimeEffectBuilder(const SkRuntimeEffectBuilder &)
// SkRuntimeEffectBuilder & operator=(SkRuntimeEffectBuilder &&)=delete
// SkRuntimeEffectBuilder & operator=(const SkRuntimeEffectBuilder &)=delete

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RUNTIME_EFFECT_BUILDER_H
