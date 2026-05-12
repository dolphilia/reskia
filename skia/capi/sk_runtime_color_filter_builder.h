//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_RUNTIME_COLOR_FILTER_BUILDER_H
#define RAIA_SKIA_SK_RUNTIME_COLOR_FILTER_BUILDER_H

#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_runtime_effect_builder_builder_child.h"
#include "../handles/static_sk_runtime_effect_builder_builder_uniform.h"

typedef struct reskia_runtime_color_filter_builder_t reskia_runtime_color_filter_builder_t;
typedef struct reskia_runtime_effect_t reskia_runtime_effect_t;

#ifdef __cplusplus
extern "C" {
#endif

//SkRuntimeColorFilterBuilder(const SkRuntimeColorFilterBuilder &)=delete
//SkRuntimeColorFilterBuilder & operator=(const SkRuntimeColorFilterBuilder &)=delete

/**
 * Invalid runtime_effect handle returns NULL.
 * Skia: (sk_runtime_effect_t runtime_effect) -> SkRuntimeColorFilterBuilder *.
 */
reskia_runtime_color_filter_builder_t *SkRuntimeColorFilterBuilder_new(int runtime_effect);
/**
 * NULL builder is no-op.
 * Skia: (SkRuntimeColorFilterBuilder *runtime_color_filter_builder).
 */
void SkRuntimeColorFilterBuilder_delete(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder);
/**
 * Returned color filter handle is caller-owned.
 * NULL builder/factory failure returns 0.
 * Skia: (SkRuntimeColorFilterBuilder *runtime_color_filter_builder) -> sk_color_filter_t.
 */
sk_color_filter_t SkRuntimeColorFilterBuilder_makeColorFilter(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder);
/**
 * NULL builder returns NULL.
 * Skia: (SkRuntimeColorFilterBuilder *runtime_color_filter_builder) -> const SkRuntimeEffect *.
 */
const reskia_runtime_effect_t *SkRuntimeColorFilterBuilder_effect(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder);
/**
 * builder/name must be valid.
 * Returned proxy handle is caller-owned.
 * Invalid input returns 0.
 * Skia: (SkRuntimeColorFilterBuilder *runtime_color_filter_builder, string_view_t name) -> sk_runtime_effect_builder_builder_uniform_t.
 */
sk_runtime_effect_builder_builder_uniform_t SkRuntimeColorFilterBuilder_uniform(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder, int name);
/**
 * builder/name must be valid.
 * Returned proxy handle is caller-owned.
 * Invalid input returns 0.
 * Skia: (SkRuntimeColorFilterBuilder *runtime_color_filter_builder, string_view_t name) -> sk_runtime_effect_builder_builder_child_t.
 */
sk_runtime_effect_builder_builder_child_t SkRuntimeColorFilterBuilder_child(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder, int name);
/**
 * Returned handle is caller-owned and deleted with static_const_sk_data_delete.
 * NULL builder returns 0.
 * Skia: (SkRuntimeColorFilterBuilder *runtime_color_filter_builder) -> const_sk_data_t.
 */
int SkRuntimeColorFilterBuilder_uniforms(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder);
/**
 * Returned handle is caller-owned and deleted with static_const_sk_runtime_effect_child_ptr_delete.
 * NULL builder returns 0.
 * Skia: (SkRuntimeColorFilterBuilder *runtime_color_filter_builder) -> const_sk_runtime_effect_child_ptr_t.
 */
int SkRuntimeColorFilterBuilder_children(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RUNTIME_COLOR_FILTER_BUILDER_H
