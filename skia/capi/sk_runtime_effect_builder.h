//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_RUNTIME_EFFECT_BUILDER_H
#define RAIA_SKIA_SK_RUNTIME_EFFECT_BUILDER_H

#include "../handles/static_sk_runtime_effect_builder_builder_child.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_shader.h"

typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_runtime_effect_builder_t reskia_runtime_effect_builder_t;
typedef struct reskia_runtime_effect_t reskia_runtime_effect_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Invalid runtime_effect handle returns NULL.
 * Skia: (sk_runtime_effect_t runtime_effect) -> SkRuntimeEffectBuilder *.
 */
reskia_runtime_effect_builder_t *SkRuntimeEffectBuilder_new(int runtime_effect);
/**
 * Invalid runtime_effect/uniforms handle returns NULL.
 * Skia: (sk_runtime_effect_t runtime_effect, sk_data_t uniforms) -> SkRuntimeEffectBuilder *.
 */
reskia_runtime_effect_builder_t *SkRuntimeEffectBuilder_newWithUniforms(int runtime_effect, int uniforms);
/**
 * NULL builder returns NULL.
 * Skia: (const SkRuntimeEffectBuilder *builder) -> SkRuntimeEffectBuilder *.
 */
reskia_runtime_effect_builder_t *SkRuntimeEffectBuilder_newCopy(const reskia_runtime_effect_builder_t *builder);
/**
 * NULL builder is no-op.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder).
 */
void SkRuntimeEffectBuilder_delete(reskia_runtime_effect_builder_t *runtime_effect_builder);
/**
 * localMatrix may be NULL.
 * Returns a caller-owned shader handle.
 * NULL builder/factory failure returns 0.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder, const SkMatrix *localMatrix) -> sk_shader_t.
 */
sk_shader_t SkRuntimeEffectBuilder_makeShader(reskia_runtime_effect_builder_t *runtime_effect_builder, const reskia_matrix_t *localMatrix);
/**
 * Returned color filter handle is caller-owned.
 * NULL builder/factory failure returns 0.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder) -> sk_color_filter_t.
 */
sk_color_filter_t SkRuntimeEffectBuilder_makeColorFilter(reskia_runtime_effect_builder_t *runtime_effect_builder);
/**
 * Returned blender handle is caller-owned.
 * NULL builder/factory failure returns 0.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder) -> sk_blender_t.
 */
sk_blender_t SkRuntimeEffectBuilder_makeBlender(reskia_runtime_effect_builder_t *runtime_effect_builder);
/**
 * NULL builder returns NULL.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder) -> const SkRuntimeEffect *.
 */
const reskia_runtime_effect_t *SkRuntimeEffectBuilder_effect(reskia_runtime_effect_builder_t *runtime_effect_builder);
/**
 * builder/name must be valid.
 * Returned proxy handle is caller-owned.
 * Invalid input returns 0.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder, string_view_t name) -> sk_runtime_effect_builder_builder_uniform_t.
 */
sk_runtime_effect_builder_builder_uniform_t SkRuntimeEffectBuilder_uniform(reskia_runtime_effect_builder_t *runtime_effect_builder, int name);
/**
 * builder/name must be valid.
 * Returned proxy handle is caller-owned.
 * Invalid input returns 0.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder, string_view_t name) -> sk_runtime_effect_builder_builder_child_t.
 */
sk_runtime_effect_builder_builder_child_t SkRuntimeEffectBuilder_child(reskia_runtime_effect_builder_t *runtime_effect_builder, int name);
/**
 * Returned handle is caller-owned and deleted with static_const_sk_data_delete.
 * NULL builder returns 0.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder) -> const_sk_data_t.
 */
int SkRuntimeEffectBuilder_uniforms(reskia_runtime_effect_builder_t *runtime_effect_builder);
/**
 * Returned handle is caller-owned and deleted with static_const_sk_runtime_effect_child_ptr_delete.
 * NULL builder returns 0.
 * Skia: (SkRuntimeEffectBuilder *runtime_effect_builder) -> const_sk_runtime_effect_child_ptr_t.
 */
int SkRuntimeEffectBuilder_children(reskia_runtime_effect_builder_t *runtime_effect_builder);

// static

// SkRuntimeEffectBuilder()=delete
// SkRuntimeEffectBuilder(SkRuntimeEffectBuilder &&)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RUNTIME_EFFECT_BUILDER_H
