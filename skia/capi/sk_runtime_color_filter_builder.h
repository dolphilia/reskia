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

reskia_runtime_color_filter_builder_t *SkRuntimeColorFilterBuilder_new(int runtime_effect); // invalid runtime_effect handle なら NULL (sk_runtime_effect_t runtime_effect) -> SkRuntimeColorFilterBuilder *
void SkRuntimeColorFilterBuilder_delete(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder); // NULL builder は no-op (SkRuntimeColorFilterBuilder *runtime_color_filter_builder)
sk_color_filter_t SkRuntimeColorFilterBuilder_makeColorFilter(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder); // NULL builder/生成不能なら 0 (SkRuntimeColorFilterBuilder *runtime_color_filter_builder) -> sk_color_filter_t
const reskia_runtime_effect_t *SkRuntimeColorFilterBuilder_effect(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder); // NULL builder なら NULL (SkRuntimeColorFilterBuilder *runtime_color_filter_builder) -> const SkRuntimeEffect *
sk_runtime_effect_builder_builder_uniform_t SkRuntimeColorFilterBuilder_uniform(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder, int name); // builder/name must be valid; invalid input returns 0 (SkRuntimeColorFilterBuilder *runtime_color_filter_builder, string_view_t name) -> sk_runtime_effect_builder_builder_uniform_t
sk_runtime_effect_builder_builder_child_t SkRuntimeColorFilterBuilder_child(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder, int name); // builder/name must be valid; invalid input returns 0 (SkRuntimeColorFilterBuilder *runtime_color_filter_builder, string_view_t name) -> sk_runtime_effect_builder_builder_child_t
int SkRuntimeColorFilterBuilder_uniforms(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder); // NULL builder なら 0 (SkRuntimeColorFilterBuilder *runtime_color_filter_builder) -> const_sk_data_t
int SkRuntimeColorFilterBuilder_children(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder); // NULL builder なら 0 (SkRuntimeColorFilterBuilder *runtime_color_filter_builder) -> const_sk_runtime_effect_child_ptr_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RUNTIME_COLOR_FILTER_BUILDER_H
