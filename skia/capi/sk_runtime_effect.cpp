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

extern "C" {

void SkRuntimeEffect_release(reskia_runtime_effect_t *runtime_effect) {
    reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->unref();
}

sk_shader_t SkRuntimeEffect_makeShader(reskia_runtime_effect_t *runtime_effect, sk_data_t data, reskia_shader_sp_t *children, size_t childCount, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->makeShader(static_const_sk_data_get_entity(data), reinterpret_cast<sk_sp<SkShader> *>(children), childCount, reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkRuntimeEffect_makeShaderWithChildPtr(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr, const reskia_matrix_t *localMatrix) {
    return static_sk_shader_make(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->makeShader(static_const_sk_data_get_entity(data), static_const_sk_runtime_effect_child_ptr_get_entity(runtime_effect_child_ptr), reinterpret_cast<const SkMatrix *>(localMatrix)));
}

sk_color_filter_t SkRuntimeEffect_makeColorFilter(reskia_runtime_effect_t *runtime_effect, sk_data_t data) {
    return static_sk_color_filter_make(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->makeColorFilter(static_const_sk_data_get_entity(data)));
}

sk_color_filter_t SkRuntimeEffect_makeColorFilterWithChildren(reskia_runtime_effect_t *runtime_effect, sk_data_t data, reskia_color_filter_sp_t *children, size_t childCount) {
    return static_sk_color_filter_make(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->makeColorFilter(static_const_sk_data_get_entity(data), reinterpret_cast<sk_sp<SkColorFilter> *>(children), childCount));
}

sk_color_filter_t SkRuntimeEffect_makeColorFilterWithChildPtr(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) {
    return static_sk_color_filter_make(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->makeColorFilter(static_const_sk_data_get_entity(data), static_const_sk_runtime_effect_child_ptr_get_entity(runtime_effect_child_ptr)));
}

sk_blender_t SkRuntimeEffect_makeBlender(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) {
    return static_sk_blender_make(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->makeBlender(static_const_sk_data_get_entity(data), static_const_sk_runtime_effect_child_ptr_get_entity(runtime_effect_child_ptr)));
}

const reskia_std_string_t *SkRuntimeEffect_source(reskia_runtime_effect_t *runtime_effect) {
    return reinterpret_cast<const reskia_std_string_t *>(&reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->source());
}

size_t SkRuntimeEffect_uniformSize(reskia_runtime_effect_t *runtime_effect) {
    return reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->uniformSize();
}

const_sk_runtime_effect_uniform_t SkRuntimeEffect_uniforms(reskia_runtime_effect_t *runtime_effect) {
    return static_const_sk_runtime_effect_uniform_make(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->uniforms());
}

const_sk_runtime_effect_child_t SkRuntimeEffect_children(reskia_runtime_effect_t *runtime_effect) {
    return static_const_sk_runtime_effect_child_make(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->children());
}

const reskia_runtime_effect_uniform_t *SkRuntimeEffect_findUniform(reskia_runtime_effect_t *runtime_effect, string_view_t name) {
    return reinterpret_cast<const reskia_runtime_effect_uniform_t *>(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->findUniform(static_string_view_get_entity(name)));
}

const reskia_runtime_effect_child_t *SkRuntimeEffect_findChild(reskia_runtime_effect_t *runtime_effect, string_view_t name) {
    return reinterpret_cast<const reskia_runtime_effect_child_t *>(reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->findChild(static_string_view_get_entity(name)));
}

bool SkRuntimeEffect_allowShader(reskia_runtime_effect_t *runtime_effect) {
    return reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->allowShader();
}

bool SkRuntimeEffect_allowColorFilter(reskia_runtime_effect_t *runtime_effect) {
    return reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->allowColorFilter();
}

bool SkRuntimeEffect_allowBlender(reskia_runtime_effect_t *runtime_effect) {
    return reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->allowBlender();
}

bool SkRuntimeEffect_unique(reskia_runtime_effect_t *runtime_effect) {
    return reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->unique();
}

void SkRuntimeEffect_ref(reskia_runtime_effect_t *runtime_effect) {
    reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->ref();
}

void SkRuntimeEffect_unref(reskia_runtime_effect_t *runtime_effect) {
    reinterpret_cast<SkRuntimeEffect *>(runtime_effect)->unref();
}

// static

sk_runtime_effect_result_t SkRuntimeEffect_MakeForColorFilter(sk_string_t string, const reskia_runtime_effect_options_t *options) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForColorFilter(static_sk_string_get_entity(string), *reinterpret_cast<const SkRuntimeEffect::Options *>(options)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForColorFilterDefault(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForColorFilter(static_sk_string_get_entity(string)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForShader(sk_string_t string, const reskia_runtime_effect_options_t *options) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForShader(static_sk_string_get_entity(string), *reinterpret_cast<const SkRuntimeEffect::Options *>(options)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForShaderDefault(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForShader(static_sk_string_get_entity(string)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForBlender(sk_string_t string, const reskia_runtime_effect_options_t *options) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForBlender(static_sk_string_get_entity(string), *reinterpret_cast<const SkRuntimeEffect::Options *>(options)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForBlenderDefault(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForBlender(static_sk_string_get_entity(string)));
}

sk_runtime_effect_traced_shader_t SkRuntimeEffect_MakeTraced(sk_shader_t shader, const reskia_i_point_t *traceCoord) {
    return static_sk_runtime_effect_traced_shader_make(SkRuntimeEffect::MakeTraced(static_sk_shader_get_entity(shader), *reinterpret_cast<const SkIPoint *>(traceCoord)));
}

void SkRuntimeEffect_RegisterFlattenables() {
    SkRuntimeEffect::RegisterFlattenables();
}

}
