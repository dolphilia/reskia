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

void *SkRuntimeColorFilterBuilder_new(sk_runtime_effect_t runtime_effect) {
    return new SkRuntimeColorFilterBuilder(static_sk_runtime_effect_get_entity(runtime_effect));
}

void SkRuntimeColorFilterBuilder_delete(void *runtime_color_filter_builder) {
    delete static_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder);
}

sk_color_filter_t SkRuntimeColorFilterBuilder_makeColorFilter(void *runtime_color_filter_builder) {
    return static_sk_color_filter_make(static_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->makeColorFilter());
}

const void * SkRuntimeColorFilterBuilder_effect(void *runtime_color_filter_builder) {
    return static_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->effect();
}

sk_runtime_effect_builder_builder_uniform_t SkRuntimeColorFilterBuilder_uniform(void *runtime_color_filter_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_uniform_make(static_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->uniform(static_string_view_get_entity(name)));
}

sk_runtime_effect_builder_builder_child_t SkRuntimeColorFilterBuilder_child(void *runtime_color_filter_builder, string_view_t name) {
    return static_sk_runtime_effect_builder_builder_child_make(static_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->child(static_string_view_get_entity(name)));
}

const_sk_data_t SkRuntimeColorFilterBuilder_uniforms(void *runtime_color_filter_builder) {
    return static_const_sk_data_make(static_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->uniforms());
}

const_sk_runtime_effect_child_ptr_t SkRuntimeColorFilterBuilder_children(void *runtime_color_filter_builder) {
    return static_const_sk_runtime_effect_child_ptr_make(static_cast<SkRuntimeColorFilterBuilder *>(runtime_color_filter_builder)->children());
}

}
