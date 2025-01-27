//
// Created by dolphilia on 2024/01/11.
//

#include "sk_runtime_effect.h"

#include <string>
#include <map>

#include "include/effects/SkRuntimeEffect.h"

#include "../static/static_sk_shader.h"
#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_blender.h"
#include "../static/static_sk_runtime_effect_uniform.h"
#include "../static/static_sk_runtime_effect_child.h"
#include "../static/static_sk_runtime_effect_child_ptr.h"
#include "../static/static_sk_runtime_effect_result.h"
#include "../static/static_sk_runtime_effect_traced_shader.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_string.h"
#include "../static/static_sk_runtime_effect_child_ptr.h"
#include "../static/static_std_string_view.h"

#include "../static/static_sk_runtime_effect_child-internal.h"
#include "../static/static_sk_runtime_effect_child_ptr-internal.h"
#include "../static/static_sk_runtime_effect_result-internal.h"
#include "../static/static_sk_runtime_effect_traced_shader-internal.h"
#include "../static/static_sk_runtime_effect_uniform-internal.h"
#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_string-internal.h"
#include "../static/static_std_string_view-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_filter-internal.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_string.h"
#include "../static/static_sk_blender-internal.h"

extern "C" {

void SkRuntimeEffect_delete(void *runtime_effect) {
    delete static_cast<SkRuntimeEffect *>(runtime_effect);
}

sk_shader_t SkRuntimeEffect_makeShader(void *runtime_effect, sk_data_t data, void * children, size_t childCount, const void *localMatrix) {
    return static_sk_shader_make(static_cast<SkRuntimeEffect *>(runtime_effect)->makeShader(static_const_sk_data_move(data), static_cast<sk_sp<SkShader> *>(children), childCount, static_cast<const SkMatrix *>(localMatrix)));
}

sk_shader_t SkRuntimeEffect_makeShader_2(void *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr, const void *localMatrix) {
    return static_sk_shader_make(static_cast<SkRuntimeEffect *>(runtime_effect)->makeShader(static_const_sk_data_move(data), static_const_sk_runtime_effect_child_ptr_get(runtime_effect_child_ptr), static_cast<const SkMatrix *>(localMatrix)));
}

sk_color_filter_t SkRuntimeEffect_makeColorFilter(void *runtime_effect, sk_data_t data) {
    return static_sk_color_filter_make(static_cast<SkRuntimeEffect *>(runtime_effect)->makeColorFilter(static_const_sk_data_move(data)));
}

sk_color_filter_t SkRuntimeEffect_makeColorFilter_2(void *runtime_effect, sk_data_t data, void * children, size_t childCount) {
    return static_sk_color_filter_make(static_cast<SkRuntimeEffect *>(runtime_effect)->makeColorFilter(static_const_sk_data_move(data), static_cast<sk_sp<SkColorFilter> *>(children), childCount));
}

sk_color_filter_t SkRuntimeEffect_makeColorFilter_3(void *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) {
    return static_sk_color_filter_make(static_cast<SkRuntimeEffect *>(runtime_effect)->makeColorFilter(static_const_sk_data_move(data), static_const_sk_runtime_effect_child_ptr_get(runtime_effect_child_ptr)));
}

sk_blender_t SkRuntimeEffect_makeBlender(void *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) {
    return static_sk_blender_make(static_cast<SkRuntimeEffect *>(runtime_effect)->makeBlender(static_const_sk_data_move(data), static_const_sk_runtime_effect_child_ptr_get(runtime_effect_child_ptr)));
}

const void * SkRuntimeEffect_source(void *runtime_effect) {
    return &static_cast<SkRuntimeEffect *>(runtime_effect)->source();
}

size_t SkRuntimeEffect_uniformSize(void *runtime_effect) {
    return static_cast<SkRuntimeEffect *>(runtime_effect)->uniformSize();
}

const_sk_runtime_effect_uniform_t SkRuntimeEffect_uniforms(void *runtime_effect) {
    return static_const_sk_runtime_effect_uniform_make(static_cast<SkRuntimeEffect *>(runtime_effect)->uniforms());
}

const_sk_runtime_effect_child_t SkRuntimeEffect_children(void *runtime_effect) {
    return static_const_sk_runtime_effect_child_make(static_cast<SkRuntimeEffect *>(runtime_effect)->children());
}

const void * SkRuntimeEffect_findUniform(void *runtime_effect, string_view_t name) {
    return static_cast<SkRuntimeEffect *>(runtime_effect)->findUniform(static_string_view_get(name));
}

const void * SkRuntimeEffect_findChild(void *runtime_effect, string_view_t name) {
    return static_cast<SkRuntimeEffect *>(runtime_effect)->findChild(static_string_view_get(name));
}

bool SkRuntimeEffect_allowShader(void *runtime_effect) {
    return static_cast<SkRuntimeEffect *>(runtime_effect)->allowShader();
}

bool SkRuntimeEffect_allowColorFilter(void *runtime_effect) {
    return static_cast<SkRuntimeEffect *>(runtime_effect)->allowColorFilter();
}

bool SkRuntimeEffect_allowBlender(void *runtime_effect) {
    return static_cast<SkRuntimeEffect *>(runtime_effect)->allowBlender();
}

bool SkRuntimeEffect_unique(void *runtime_effect) {
    return static_cast<SkRuntimeEffect *>(runtime_effect)->unique();
}

void SkRuntimeEffect_ref(void *runtime_effect) {
    static_cast<SkRuntimeEffect *>(runtime_effect)->ref();
}

void SkRuntimeEffect_unref(void *runtime_effect) {
    static_cast<SkRuntimeEffect *>(runtime_effect)->unref();
}

// static

sk_runtime_effect_result_t SkRuntimeEffect_MakeForColorFilter(sk_string_t string, const void *options) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForColorFilter(static_sk_string_get(string), * static_cast<const SkRuntimeEffect::Options *>(options)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForColorFilter_2(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForColorFilter(static_sk_string_get(string)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForShader(sk_string_t string, const void *options) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForShader(static_sk_string_get(string), * static_cast<const SkRuntimeEffect::Options *>(options)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForShader_2(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForShader(static_sk_string_get(string)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForBlender(sk_string_t string, const void *options) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForBlender(static_sk_string_get(string), * static_cast<const SkRuntimeEffect::Options *>(options)));
}

sk_runtime_effect_result_t SkRuntimeEffect_MakeForBlender_2(sk_string_t string) {
    return static_sk_runtime_effect_result_make(SkRuntimeEffect::MakeForBlender(static_sk_string_get(string)));
}

sk_runtime_effect_traced_shader_t SkRuntimeEffect_MakeTraced(sk_shader_t shader, const void *traceCoord) {
    return static_sk_runtime_effect_traced_shader_make(SkRuntimeEffect::MakeTraced(static_sk_shader_move(shader), * static_cast<const SkIPoint *>(traceCoord)));
}

void SkRuntimeEffect_RegisterFlattenables() {
    SkRuntimeEffect::RegisterFlattenables();
}

}