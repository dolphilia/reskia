//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_RUNTIME_EFFECT_H
#define RAIA_SKIA_SK_RUNTIME_EFFECT_H

#include <stddef.h>

typedef struct reskia_color_filter_sp_t reskia_color_filter_sp_t;
typedef struct reskia_i_point_t reskia_i_point_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_runtime_effect_child_t reskia_runtime_effect_child_t;
typedef struct reskia_runtime_effect_options_t reskia_runtime_effect_options_t;
typedef struct reskia_runtime_effect_t reskia_runtime_effect_t;
typedef struct reskia_runtime_effect_uniform_t reskia_runtime_effect_uniform_t;
typedef struct reskia_shader_sp_t reskia_shader_sp_t;
typedef struct reskia_std_string_t reskia_std_string_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkRuntimeEffect_delete(reskia_runtime_effect_t *runtime_effect); // owned: caller が保持する参照を release する (SkRuntimeEffect *runtime_effect)
int SkRuntimeEffect_makeShader(reskia_runtime_effect_t *runtime_effect, int data, reskia_shader_sp_t *children, size_t childCount, const reskia_matrix_t *localMatrix); // (SkRuntimeEffect *runtime_effect, sk_data_t data, sk_sp<SkShader> children[], size_t childCount, const SkMatrix *localMatrix) -> sk_shader_t
int SkRuntimeEffect_makeShader_2(reskia_runtime_effect_t *runtime_effect, int data, int runtime_effect_child_ptr, const reskia_matrix_t *localMatrix); // (SkRuntimeEffect *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr, const SkMatrix *localMatrix) -> sk_shader_t
int SkRuntimeEffect_makeColorFilter(reskia_runtime_effect_t *runtime_effect, int data); // (SkRuntimeEffect *runtime_effect, sk_data_t data) -> sk_color_filter_t
int SkRuntimeEffect_makeColorFilter_2(reskia_runtime_effect_t *runtime_effect, int data, reskia_color_filter_sp_t *children, size_t childCount); // (SkRuntimeEffect *runtime_effect, sk_data_t data, sk_sp<SkColorFilter> children[], size_t childCount) -> sk_color_filter_t
int SkRuntimeEffect_makeColorFilter_3(reskia_runtime_effect_t *runtime_effect, int data, int runtime_effect_child_ptr); // (SkRuntimeEffect *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) -> sk_color_filter_t
int SkRuntimeEffect_makeBlender(reskia_runtime_effect_t *runtime_effect, int data, int runtime_effect_child_ptr); // (SkRuntimeEffect *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) -> sk_blender_t
const reskia_std_string_t *SkRuntimeEffect_source(reskia_runtime_effect_t *runtime_effect); // borrowed: 解放不要の借用ポインタ (SkRuntimeEffect *runtime_effect) -> const std::string *
size_t SkRuntimeEffect_uniformSize(reskia_runtime_effect_t *runtime_effect); // (SkRuntimeEffect *runtime_effect) -> size_t
int SkRuntimeEffect_uniforms(reskia_runtime_effect_t *runtime_effect); // (SkRuntimeEffect *runtime_effect) -> int
int SkRuntimeEffect_children(reskia_runtime_effect_t *runtime_effect); // (SkRuntimeEffect *runtime_effect) -> int
const reskia_runtime_effect_uniform_t *SkRuntimeEffect_findUniform(reskia_runtime_effect_t *runtime_effect, int name); // borrowed: 解放不要の借用ポインタ (SkRuntimeEffect *runtime_effect, string_view_t name) -> const SkRuntimeEffect::Uniform *
const reskia_runtime_effect_child_t *SkRuntimeEffect_findChild(reskia_runtime_effect_t *runtime_effect, int name); // borrowed: 解放不要の借用ポインタ (SkRuntimeEffect *runtime_effect, string_view_t name) -> const SkRuntimeEffect::Child *
bool SkRuntimeEffect_allowShader(reskia_runtime_effect_t *runtime_effect); // (SkRuntimeEffect *runtime_effect) -> bool
bool SkRuntimeEffect_allowColorFilter(reskia_runtime_effect_t *runtime_effect); // (SkRuntimeEffect *runtime_effect) -> bool
bool SkRuntimeEffect_allowBlender(reskia_runtime_effect_t *runtime_effect); // (SkRuntimeEffect *runtime_effect) -> bool
bool SkRuntimeEffect_unique(reskia_runtime_effect_t *runtime_effect); // (SkRuntimeEffect *runtime_effect) -> bool
void SkRuntimeEffect_ref(reskia_runtime_effect_t *runtime_effect); // retained: 参照カウントを増やす (SkRuntimeEffect *runtime_effect)
void SkRuntimeEffect_unref(reskia_runtime_effect_t *runtime_effect); // owned: 参照カウントを減らす (SkRuntimeEffect *runtime_effect)

// static

int SkRuntimeEffect_MakeForColorFilter(int string, const reskia_runtime_effect_options_t *options); // (sk_string_t string, const SkRuntimeEffect::Options *options) -> sk_runtime_effect_result_t
int SkRuntimeEffect_MakeForColorFilter_2(int string); // (sk_string_t string) -> sk_runtime_effect_result_t
int SkRuntimeEffect_MakeForShader(int string, const reskia_runtime_effect_options_t *options); // (sk_string_t string, const SkRuntimeEffect::Options *options) -> sk_runtime_effect_result_t
int SkRuntimeEffect_MakeForShader_2(int string); // (sk_string_t string) -> sk_runtime_effect_result_t
int SkRuntimeEffect_MakeForBlender(int string, const reskia_runtime_effect_options_t *options); // (sk_string_t string, const SkRuntimeEffect::Options *options) -> sk_runtime_effect_result_t
int SkRuntimeEffect_MakeForBlender_2(int string); // (sk_string_t string) -> sk_runtime_effect_result_t
int SkRuntimeEffect_MakeTraced(int shader, const reskia_i_point_t *traceCoord); // (sk_shader_t shader, const SkIPoint *traceCoord) -> sk_runtime_effect_result_t
void SkRuntimeEffect_RegisterFlattenables(); // ()

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RUNTIME_EFFECT_H
