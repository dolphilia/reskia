//
// Created by dolphilia on 2024/01/11.
//

#include "sk_runtime_effect.h"

#include <string>
#include <map>

#include "include/effects/SkRuntimeEffect.h"

#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_runtime_effect_uniform.h"
#include "../handles/static_sk_runtime_effect_child.h"
#include "../handles/static_sk_runtime_effect_child_ptr.h"
#include "../handles/static_sk_runtime_effect_result.h"
#include "../handles/static_sk_runtime_effect_traced_shader.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_string.h"
#include "../handles/static_sk_runtime_effect_child_ptr.h"
#include "../handles/static_std_string_view.h"

#include "../handles/static_sk_runtime_effect_child-internal.h"
#include "../handles/static_sk_runtime_effect_child_ptr-internal.h"
#include "../handles/static_sk_runtime_effect_result-internal.h"
#include "../handles/static_sk_runtime_effect_traced_shader-internal.h"
#include "../handles/static_sk_runtime_effect_uniform-internal.h"
#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_string-internal.h"
#include "../handles/static_std_string_view-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_filter-internal.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_string.h"
#include "../handles/static_sk_blender-internal.h"

namespace {

SkRuntimeEffect *as_effect(reskia_runtime_effect_t *runtime_effect) {
    return reinterpret_cast<SkRuntimeEffect *>(runtime_effect);
}

sk_shader_t make_shader_handle(sk_sp<SkShader> shader) {
    return shader ? static_sk_shader_make(shader) : 0;
}

sk_color_filter_t make_color_filter_handle(sk_sp<SkColorFilter> color_filter) {
    return color_filter ? static_sk_color_filter_make(color_filter) : 0;
}

sk_blender_t make_blender_handle(sk_sp<SkBlender> blender) {
    return blender ? static_sk_blender_make(blender) : 0;
}

} // namespace

extern "C" {

void SkRuntimeEffect_release(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    if (native != nullptr) {
        native->unref();
    }
}

sk_shader_t SkRuntimeEffect_makeShader(reskia_runtime_effect_t *runtime_effect, sk_data_t data, reskia_shader_sp_t *children, size_t childCount, const reskia_matrix_t *localMatrix) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    if (native == nullptr || (children == nullptr && childCount != 0)) {
        return 0;
    }
    return make_shader_handle(native->makeShader(static_const_sk_data_get_entity(data), reinterpret_cast<sk_sp<SkShader> *>(children), childCount, reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkRuntimeEffect_makeShaderWithChildPtr(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr, const reskia_matrix_t *localMatrix) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? make_shader_handle(native->makeShader(static_const_sk_data_get_entity(data), static_const_sk_runtime_effect_child_ptr_get_entity(runtime_effect_child_ptr), reinterpret_cast<const SkMatrix *>(localMatrix))) : 0;
}

sk_color_filter_t SkRuntimeEffect_makeColorFilter(reskia_runtime_effect_t *runtime_effect, sk_data_t data) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? make_color_filter_handle(native->makeColorFilter(static_const_sk_data_get_entity(data))) : 0;
}

sk_color_filter_t SkRuntimeEffect_makeColorFilterWithChildren(reskia_runtime_effect_t *runtime_effect, sk_data_t data, reskia_color_filter_sp_t *children, size_t childCount) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    if (native == nullptr || (children == nullptr && childCount != 0)) {
        return 0;
    }
    return make_color_filter_handle(native->makeColorFilter(static_const_sk_data_get_entity(data), reinterpret_cast<sk_sp<SkColorFilter> *>(children), childCount));
}

sk_color_filter_t SkRuntimeEffect_makeColorFilterWithChildPtr(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? make_color_filter_handle(native->makeColorFilter(static_const_sk_data_get_entity(data), static_const_sk_runtime_effect_child_ptr_get_entity(runtime_effect_child_ptr))) : 0;
}

sk_blender_t SkRuntimeEffect_makeBlender(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? make_blender_handle(native->makeBlender(static_const_sk_data_get_entity(data), static_const_sk_runtime_effect_child_ptr_get_entity(runtime_effect_child_ptr))) : 0;
}

const reskia_std_string_t *SkRuntimeEffect_source(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? reinterpret_cast<const reskia_std_string_t *>(&native->source()) : nullptr;
}

size_t SkRuntimeEffect_uniformSize(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? native->uniformSize() : 0;
}

const_sk_runtime_effect_uniform_t SkRuntimeEffect_uniforms(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? static_const_sk_runtime_effect_uniform_make(native->uniforms()) : 0;
}

const_sk_runtime_effect_child_t SkRuntimeEffect_children(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? static_const_sk_runtime_effect_child_make(native->children()) : 0;
}

const reskia_runtime_effect_uniform_t *SkRuntimeEffect_findUniform(reskia_runtime_effect_t *runtime_effect, string_view_t name) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? reinterpret_cast<const reskia_runtime_effect_uniform_t *>(native->findUniform(static_string_view_get_entity(name))) : nullptr;
}

const reskia_runtime_effect_child_t *SkRuntimeEffect_findChild(reskia_runtime_effect_t *runtime_effect, string_view_t name) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? reinterpret_cast<const reskia_runtime_effect_child_t *>(native->findChild(static_string_view_get_entity(name))) : nullptr;
}

bool SkRuntimeEffect_allowShader(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? native->allowShader() : false;
}

bool SkRuntimeEffect_allowColorFilter(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? native->allowColorFilter() : false;
}

bool SkRuntimeEffect_allowBlender(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? native->allowBlender() : false;
}

bool SkRuntimeEffect_unique(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    return native != nullptr ? native->unique() : false;
}

void SkRuntimeEffect_ref(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    if (native != nullptr) {
        native->ref();
    }
}

void SkRuntimeEffect_unref(reskia_runtime_effect_t *runtime_effect) {
    SkRuntimeEffect *native = as_effect(runtime_effect);
    if (native != nullptr) {
        native->unref();
    }
}

// static

sk_runtime_effect_result_t SkRuntimeEffect_MakeForColorFilter(sk_string_t string, const reskia_runtime_effect_options_t *options) {
    return options != nullptr ? static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForColorFilter(static_sk_string_get_entity(string), *reinterpret_cast<const SkRuntimeEffect::Options *>(options))) : 0;
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForColorFilterDefault(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForColorFilter(static_sk_string_get_entity(string)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForShader(sk_string_t string, const reskia_runtime_effect_options_t *options) {
    return options != nullptr ? static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForShader(static_sk_string_get_entity(string), *reinterpret_cast<const SkRuntimeEffect::Options *>(options))) : 0;
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForShaderDefault(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForShader(static_sk_string_get_entity(string)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForBlender(sk_string_t string, const reskia_runtime_effect_options_t *options) {
    return options != nullptr ? static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForBlender(static_sk_string_get_entity(string), *reinterpret_cast<const SkRuntimeEffect::Options *>(options))) : 0;
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForBlenderDefault(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForBlender(static_sk_string_get_entity(string)));
}

sk_runtime_effect_traced_shader_t SkRuntimeEffect_MakeTraced(sk_shader_t shader, const reskia_i_point_t *traceCoord) {
    if (traceCoord == nullptr) {
        return 0;
    }
    return static_sk_runtime_effect_traced_shader_make(SkRuntimeEffect::MakeTraced(static_sk_shader_get_entity(shader), *reinterpret_cast<const SkIPoint *>(traceCoord)));
}

void SkRuntimeEffect_RegisterFlattenables() {
    SkRuntimeEffect::RegisterFlattenables();
}

}
