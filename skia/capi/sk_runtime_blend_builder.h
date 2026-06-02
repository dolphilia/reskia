//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_RUNTIME_BLEND_BUILDER_H
#define RAIA_SKIA_SK_RUNTIME_BLEND_BUILDER_H

#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_runtime_effect_builder_builder_child.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform.h"

typedef struct reskia_runtime_blend_builder_t reskia_runtime_blend_builder_t;
typedef struct reskia_runtime_effect_t reskia_runtime_effect_t;

#ifdef __cplusplus
extern "C" {
#endif

//SkRuntimeBlendBuilder(const SkRuntimeBlendBuilder &)=delete

/**
 * Invalid runtime_effect handle returns NULL.
 * Skia: (sk_runtime_effect_t runtime_effect) -> SkRuntimeBlendBuilder *.
 */
reskia_runtime_blend_builder_t *SkRuntimeBlendBuilder_new(int runtime_effect);
/**
 * NULL builder is no-op.
 * Skia: (SkRuntimeBlendBuilder *runtime_blend_builder).
 */
void SkRuntimeBlendBuilder_delete(reskia_runtime_blend_builder_t *runtime_blend_builder);
/**
 * Returned blender handle is caller-owned.
 * NULL builder/factory failure returns 0.
 * Skia: (SkRuntimeBlendBuilder *runtime_blend_builder) -> sk_blender_t.
 */
sk_blender_t SkRuntimeBlendBuilder_makeBlender(reskia_runtime_blend_builder_t *runtime_blend_builder);
/**
 * NULL builder returns NULL.
 * Skia: (SkRuntimeBlendBuilder *runtime_blend_builder) -> const SkRuntimeEffect *.
 */
const reskia_runtime_effect_t *SkRuntimeBlendBuilder_effect(reskia_runtime_blend_builder_t *runtime_blend_builder);
/**
 * builder/name must be valid.
 * Returned proxy handle is caller-owned.
 * Invalid input returns 0.
 * Skia: (SkRuntimeBlendBuilder *runtime_blend_builder, string_view_t name) -> sk_runtime_effect_builder_builder_uniform_t.
 */
sk_runtime_effect_builder_builder_uniform_t SkRuntimeBlendBuilder_uniform(reskia_runtime_blend_builder_t *runtime_blend_builder, int name);
/**
 * builder/name must be valid.
 * Returned proxy handle is caller-owned.
 * Invalid input returns 0.
 * Skia: (SkRuntimeBlendBuilder *runtime_blend_builder, string_view_t name) -> sk_runtime_effect_builder_builder_child_t.
 */
sk_runtime_effect_builder_builder_child_t SkRuntimeBlendBuilder_child(reskia_runtime_blend_builder_t *runtime_blend_builder, int name);
/**
 * Returned handle is caller-owned and deleted with static_const_sk_data_delete.
 * NULL builder returns 0.
 * Skia: (SkRuntimeBlendBuilder *runtime_blend_builder) -> const_sk_data_t.
 */
int SkRuntimeBlendBuilder_uniforms(reskia_runtime_blend_builder_t *runtime_blend_builder);
/**
 * Returned handle is caller-owned and deleted with static_const_sk_runtime_effect_child_ptr_delete.
 * NULL builder returns 0.
 * Skia: (SkRuntimeBlendBuilder *runtime_blend_builder) -> const_sk_runtime_effect_child_ptr_t.
 */
int SkRuntimeBlendBuilder_children(reskia_runtime_blend_builder_t *runtime_blend_builder);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RUNTIME_BLEND_BUILDER_H
