//
// Created by dolphilia on 25/02/04.
//

#ifndef SK_MESH_SPECIFICATION_H
#define SK_MESH_SPECIFICATION_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_mesh_specification_attribute.h"
#include "../handles/static_sk_mesh_specification_result.h"

typedef struct reskia_color_space_sp_t reskia_color_space_sp_t;
typedef struct reskia_mesh_specification_attribute_span_t reskia_mesh_specification_attribute_span_t;
typedef struct reskia_mesh_specification_attribute_t reskia_mesh_specification_attribute_t;
typedef struct reskia_mesh_specification_t reskia_mesh_specification_t;
typedef struct reskia_mesh_specification_varying_span_t reskia_mesh_specification_varying_span_t;
typedef struct reskia_mesh_specification_varying_t reskia_mesh_specification_varying_t;
typedef struct reskia_runtime_effect_child_t reskia_runtime_effect_child_t;
typedef struct reskia_runtime_effect_uniform_t reskia_runtime_effect_uniform_t;
typedef struct reskia_string_t reskia_string_t;
typedef struct reskia_string_view_t reskia_string_view_t;
typedef int32_t reskia_mesh_specification_alpha_type_t;

void SkMeshSpecification_delete(reskia_mesh_specification_t* spec); // NULL 入力では no-op
sk_mesh_specification_attribute_t SkMeshSpecification_attributes(reskia_mesh_specification_t* spec); // spec NULL では 0。戻り値 span handle は spec に借用依存
size_t SkMeshSpecification_uniformSize(reskia_mesh_specification_t* spec); // spec NULL では 0
int SkMeshSpecification_uniforms(reskia_mesh_specification_t* spec); // spec NULL では 0。戻り値 span handle は spec に借用依存
int SkMeshSpecification_children(reskia_mesh_specification_t* spec); // spec NULL では 0。戻り値 span handle は spec に借用依存
/**
 * spec/name NULL や未検出では NULL。戻り値は spec に借用依存
 */
const reskia_runtime_effect_child_t * SkMeshSpecification_findChild(reskia_mesh_specification_t* spec, const reskia_string_view_t * name);
/**
 * spec/name NULL や未検出では NULL。戻り値は spec に借用依存
 */
const reskia_runtime_effect_uniform_t * SkMeshSpecification_findUniform(reskia_mesh_specification_t* spec, const reskia_string_view_t * name);
/**
 * spec/name NULL や未検出では NULL。戻り値は spec に借用依存
 */
const reskia_mesh_specification_attribute_t * SkMeshSpecification_findAttribute(reskia_mesh_specification_t* spec, const reskia_string_view_t * name);
/**
 * spec/name NULL や未検出では NULL。戻り値は spec に借用依存
 */
const reskia_mesh_specification_varying_t * SkMeshSpecification_findVarying(reskia_mesh_specification_t* spec, const reskia_string_view_t * name);
size_t SkMeshSpecification_stride(reskia_mesh_specification_t* spec); // spec NULL では 0
// static
/**
 * attributes/varyings/vs/fs は非 NULL。invalid 入力では 0
 */
sk_mesh_specification_result_t SkMeshSpecification_Make(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs);
/**
 * attributes/varyings/vs/fs は非 NULL。cs は NULL 許可。invalid 入力では 0
 */
sk_mesh_specification_result_t SkMeshSpecification_MakeWithColorSpace(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs);
/**
 * attributes/varyings/vs/fs は非 NULL。cs は NULL 許可。invalid 入力では 0
 */
sk_mesh_specification_result_t SkMeshSpecification_MakeWithColorSpaceAndAlphaType(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs, reskia_mesh_specification_alpha_type_t at);

#ifdef __cplusplus
}
#endif

#endif //SK_MESH_SPECIFICATION_H
