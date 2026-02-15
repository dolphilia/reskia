//
// Created by dolphilia on 2024/01/10.
//

#include "sk_runtime_color_filter_builder.h"

#include "include/effects/SkRuntimeEffect.h"

#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_runtime_effect.h"
#include "../static/static_sk_runtime_effect_child_ptr.h"
#include "../static/static_sk_runtime_effect_builder_builder_uniform.h"
#include "../static/static_sk_runtime_effect_builder_builder_child.h"
#include "../static/static_std_string_view.h"

#include "../static/static_sk_runtime_effect-internal.h"
#include "../static/static_sk_runtime_effect_builder_builder_child-internal.h"
#include "../static/static_sk_runtime_effect_builder_builder_uniform-internal.h"
#include "../static/static_sk_runtime_effect_child_ptr-internal.h"
#include "../static/static_std_string_view-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_filter-internal.h"

extern "C" {

//SkRuntimeColorFilterBuilder(const SkRuntimeColorFilterBuilder &)=delete
//SkRuntimeColorFilterBuilder & operator=(const SkRuntimeColorFilterBuilder &)=delete

reskia_runtime_color_filter_builder_t *SkRuntimeColorFilterBuilder_new(sk_runtime_effect_t runtime_effect) {
    return reinterpret_cast<reskia_runtime_color_filter_builder_t *>(new SkRuntimeColorFilterBuilder(static_sk_runtime_effect_get_entity(runtime_effect)));
}

void SkRuntimeColorFilterBuilder_delete(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder) {
    delete reinterpret_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder);
}

sk_color_filter_t SkRuntimeColorFilterBuilder_makeColorFilter(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder) {
    return static_sk_color_filter_make(reinterpret_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->makeColorFilter());
}

const reskia_runtime_effect_t *SkRuntimeColorFilterBuilder_effect(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder) {
    return reinterpret_cast<const reskia_runtime_effect_t *>(reinterpret_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->effect());
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeColorFilterBuilder_uniform(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_uniform_make(reinterpret_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->uniform(static_string_view_get_entity(name)));
}

sk_runtime_effect_builder_builder_child_t SkRuntimeColorFilterBuilder_child(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_child_make(reinterpret_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->child(static_string_view_get_entity(name)));
}

const_sk_data_t SkRuntimeColorFilterBuilder_uniforms(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder) {
    return static_const_sk_data_make(reinterpret_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->uniforms());
}

const_sk_runtime_effect_child_ptr_t SkRuntimeColorFilterBuilder_children(reskia_runtime_color_filter_builder_t *runtime_color_filter_builder) {
    return static_const_sk_runtime_effect_child_ptr_make(reinterpret_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->children());
}

}
