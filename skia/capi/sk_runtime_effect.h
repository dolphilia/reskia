//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_RUNTIME_EFFECT_H
#define RAIA_SKIA_SK_RUNTIME_EFFECT_H

#include <stddef.h>

#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_runtime_effect_child.h"
#include "../handles/static_sk_runtime_effect_child_ptr.h"
#include "../handles/static_sk_runtime_effect_result.h"
#include "../handles/static_sk_runtime_effect_traced_shader.h"
#include "../handles/static_sk_runtime_effect_uniform.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_string.h"

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

/**
 * Releases the caller-held reference. NULL runtime_effect is no-op.
 * Skia: (SkRuntimeEffect *runtime_effect).
 */
void SkRuntimeEffect_release(reskia_runtime_effect_t *runtime_effect);
/**
 * data handle 0 is allowed as empty data.
 * Non-zero data must be a valid handle.
 * children must be non-null when childCount > 0.
 * localMatrix may be NULL.
 * Returns a caller-owned shader handle.
 * NULL runtime_effect/invalid input/factory failure returns 0.
 * Skia:
 *   (SkRuntimeEffect *runtime_effect,
 *    sk_data_t data,
 *    sk_sp<SkShader> children[],
 *    size_t childCount,
 *    const SkMatrix *localMatrix) -> sk_shader_t.
 */
sk_shader_t SkRuntimeEffect_makeShader(reskia_runtime_effect_t *runtime_effect, sk_data_t data, reskia_shader_sp_t *children, size_t childCount, const reskia_matrix_t *localMatrix);
/**
 * data handle 0 and child pointer handle 0 are allowed as empty inputs.
 * Non-zero data/child pointer must be valid handles.
 * localMatrix may be NULL.
 * Returns a caller-owned shader handle.
 * NULL runtime_effect/invalid input/factory failure returns 0.
 * Skia:
 *   (SkRuntimeEffect *runtime_effect,
 *    sk_data_t data,
 *    const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr,
 *    const SkMatrix *localMatrix) -> sk_shader_t.
 */
sk_shader_t SkRuntimeEffect_makeShaderWithChildPtr(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr, const reskia_matrix_t *localMatrix);
/**
 * data handle 0 is allowed as empty data.
 * Non-zero data must be a valid handle.
 * NULL runtime_effect/invalid input/factory failure returns 0.
 * Skia: (SkRuntimeEffect *runtime_effect, sk_data_t data) -> sk_color_filter_t.
 */
sk_color_filter_t SkRuntimeEffect_makeColorFilter(reskia_runtime_effect_t *runtime_effect, sk_data_t data);
/**
 * data handle 0 is allowed as empty data.
 * Non-zero data must be a valid handle.
 * children must be non-null when childCount > 0.
 * NULL runtime_effect/invalid input/factory failure returns 0.
 * Skia: (SkRuntimeEffect *runtime_effect, sk_data_t data, sk_sp<SkColorFilter> children[], size_t childCount) -> sk_color_filter_t.
 */
sk_color_filter_t SkRuntimeEffect_makeColorFilterWithChildren(reskia_runtime_effect_t *runtime_effect, sk_data_t data, reskia_color_filter_sp_t *children, size_t childCount);
/**
 * data handle 0 and child pointer handle 0 are allowed as empty inputs.
 * Non-zero data/child pointer must be valid handles.
 * NULL runtime_effect/invalid input/factory failure returns 0.
 * Skia: (SkRuntimeEffect *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) -> sk_color_filter_t.
 */
sk_color_filter_t SkRuntimeEffect_makeColorFilterWithChildPtr(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr);
/**
 * data handle 0 and child pointer handle 0 are allowed as empty inputs.
 * Non-zero data/child pointer must be valid handles.
 * NULL runtime_effect/invalid input/factory failure returns 0.
 * Skia: (SkRuntimeEffect *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr) -> sk_blender_t.
 */
sk_blender_t SkRuntimeEffect_makeBlender(reskia_runtime_effect_t *runtime_effect, sk_data_t data, const_sk_runtime_effect_child_ptr_t runtime_effect_child_ptr);
/**
 * Borrowed pointer; caller must not free. NULL runtime_effect returns NULL.
 * Skia: (SkRuntimeEffect *runtime_effect) -> const std::string *.
 */
const reskia_std_string_t *SkRuntimeEffect_source(reskia_runtime_effect_t *runtime_effect);
/**
 * NULL runtime_effect returns 0.
 * Skia: (SkRuntimeEffect *runtime_effect) -> size_t.
 */
size_t SkRuntimeEffect_uniformSize(reskia_runtime_effect_t *runtime_effect);
/**
 * Borrowed span handle.
 * Caller deletes handle with static_const_sk_runtime_effect_uniform_delete.
 * NULL runtime_effect returns 0.
 * Skia: (SkRuntimeEffect *runtime_effect) -> int.
 */
int SkRuntimeEffect_uniforms(reskia_runtime_effect_t *runtime_effect);
/**
 * Borrowed span handle.
 * Caller deletes handle with static_const_sk_runtime_effect_child_delete.
 * NULL runtime_effect returns 0.
 * Skia: (SkRuntimeEffect *runtime_effect) -> int.
 */
int SkRuntimeEffect_children(reskia_runtime_effect_t *runtime_effect);
/**
 * Borrowed pointer; caller must not free. runtime_effect/name must be valid.
 * Invalid input or missing uniform returns NULL.
 * Skia: (SkRuntimeEffect *runtime_effect, string_view_t name) -> const SkRuntimeEffect::Uniform *.
 */
const reskia_runtime_effect_uniform_t *SkRuntimeEffect_findUniform(reskia_runtime_effect_t *runtime_effect, int name);
/**
 * Borrowed pointer; caller must not free. runtime_effect/name must be valid.
 * Invalid input or missing child returns NULL.
 * Skia: (SkRuntimeEffect *runtime_effect, string_view_t name) -> const SkRuntimeEffect::Child *.
 */
const reskia_runtime_effect_child_t *SkRuntimeEffect_findChild(reskia_runtime_effect_t *runtime_effect, int name);
/**
 * NULL runtime_effect returns false.
 * Skia: (SkRuntimeEffect *runtime_effect) -> bool.
 */
bool SkRuntimeEffect_allowShader(reskia_runtime_effect_t *runtime_effect);
/**
 * NULL runtime_effect returns false.
 * Skia: (SkRuntimeEffect *runtime_effect) -> bool.
 */
bool SkRuntimeEffect_allowColorFilter(reskia_runtime_effect_t *runtime_effect);
/**
 * NULL runtime_effect returns false.
 * Skia: (SkRuntimeEffect *runtime_effect) -> bool.
 */
bool SkRuntimeEffect_allowBlender(reskia_runtime_effect_t *runtime_effect);
/**
 * NULL runtime_effect returns false.
 * Skia: (SkRuntimeEffect *runtime_effect) -> bool.
 */
bool SkRuntimeEffect_unique(reskia_runtime_effect_t *runtime_effect);
/**
 * Retains runtime_effect. NULL runtime_effect is no-op.
 * Skia: (SkRuntimeEffect *runtime_effect).
 */
void SkRuntimeEffect_ref(reskia_runtime_effect_t *runtime_effect);
/**
 * Releases runtime_effect. NULL runtime_effect is no-op.
 * Skia: (SkRuntimeEffect *runtime_effect).
 */
void SkRuntimeEffect_unref(reskia_runtime_effect_t *runtime_effect);

// static

/**
 * string must be a valid handle.
 * options is non-null.
 * Invalid input returns 0.
 * Skia: (sk_string_t string, const SkRuntimeEffect::Options *options) -> sk_runtime_effect_result_t.
 */
sk_runtime_effect_result_t SkRuntimeEffect_MakeForColorFilter(sk_string_t string, const reskia_runtime_effect_options_t *options);
/**
 * string must be a valid handle.
 * Invalid input returns 0.
 * Skia: (sk_string_t string) -> sk_runtime_effect_result_t.
 */
sk_runtime_effect_result_t SkRuntimeEffect_MakeForColorFilterDefault(sk_string_t string);
/**
 * string must be a valid handle.
 * options is non-null.
 * Invalid input returns 0.
 * Skia: (sk_string_t string, const SkRuntimeEffect::Options *options) -> sk_runtime_effect_result_t.
 */
sk_runtime_effect_result_t SkRuntimeEffect_MakeForShader(sk_string_t string, const reskia_runtime_effect_options_t *options);
/**
 * string must be a valid handle.
 * Invalid input returns 0.
 * Skia: (sk_string_t string) -> sk_runtime_effect_result_t.
 */
sk_runtime_effect_result_t SkRuntimeEffect_MakeForShaderDefault(sk_string_t string);
/**
 * string must be a valid handle.
 * options is non-null.
 * Invalid input returns 0.
 * Skia: (sk_string_t string, const SkRuntimeEffect::Options *options) -> sk_runtime_effect_result_t.
 */
sk_runtime_effect_result_t SkRuntimeEffect_MakeForBlender(sk_string_t string, const reskia_runtime_effect_options_t *options);
/**
 * string must be a valid handle.
 * Invalid input returns 0.
 * Skia: (sk_string_t string) -> sk_runtime_effect_result_t.
 */
sk_runtime_effect_result_t SkRuntimeEffect_MakeForBlenderDefault(sk_string_t string);
/**
 * shader must be a valid handle.
 * traceCoord is non-null.
 * Invalid input returns 0.
 * Returns a caller-owned trace handle.
 * Skia: (sk_shader_t shader, const SkIPoint *traceCoord) -> sk_runtime_effect_traced_shader_t.
 */
sk_runtime_effect_traced_shader_t SkRuntimeEffect_MakeTraced(sk_shader_t shader, const reskia_i_point_t *traceCoord);
void SkRuntimeEffect_RegisterFlattenables(); // ()

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_RUNTIME_EFFECT_H
