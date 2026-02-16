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

void SkMeshSpecification_delete(reskia_mesh_specification_t* spec); // (SkMeshSpecification* spec)
sk_mesh_specification_attribute_t SkMeshSpecification_attributes(reskia_mesh_specification_t* spec); // (SkMeshSpecification* spec) -> sk_mesh_specification_attribute_t
size_t SkMeshSpecification_uniformSize(reskia_mesh_specification_t* spec); // (SkMeshSpecification* spec) -> size_t
int SkMeshSpecification_uniforms(reskia_mesh_specification_t* spec); // (SkMeshSpecification* spec) -> const_sk_runtime_effect_uniform_t
int SkMeshSpecification_children(reskia_mesh_specification_t* spec); // (SkMeshSpecification* spec) -> const_sk_runtime_effect_child_t
const reskia_runtime_effect_child_t * SkMeshSpecification_findChild(reskia_mesh_specification_t* spec, const reskia_string_view_t * name); // (SkMeshSpecification* spec, std::string_view* name) -> const SkRuntimeEffect::Child*
const reskia_runtime_effect_uniform_t * SkMeshSpecification_findUniform(reskia_mesh_specification_t* spec, const reskia_string_view_t * name); // (SkMeshSpecification* spec, std::string_view* name) -> const SkRuntimeEffect::Uniform*
const reskia_mesh_specification_attribute_t * SkMeshSpecification_findAttribute(reskia_mesh_specification_t* spec, const reskia_string_view_t * name); // (SkMeshSpecification* spec, std::string_view* name) -> const SkMeshSpecification::Attribute*
const reskia_mesh_specification_varying_t * SkMeshSpecification_findVarying(reskia_mesh_specification_t* spec, const reskia_string_view_t * name); // (SkMeshSpecification* spec, std::string_view* name) -> const SkMeshSpecification::Varying*
size_t SkMeshSpecification_stride(reskia_mesh_specification_t* spec); // (SkMeshSpecification* spec) -> size_t
// static
sk_mesh_specification_result_t SkMeshSpecification_Make(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs); // (SkSpan<const SkMeshSpecification::Attribute>* attributes, size_t vertexStride, SkSpan<const SkMeshSpecification::Varying>* varyings, const SkString* vs, const SkString* fs) -> sk_mesh_specification_result_t
sk_mesh_specification_result_t SkMeshSpecification_Make_2(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs); // (SkSpan<const SkMeshSpecification::Attribute>* attributes, size_t vertexStride, SkSpan<const SkMeshSpecification::Varying>* varyings, const SkString* vs, const SkString* fs, sk_sp<SkColorSpace>* cs) -> sk_mesh_specification_result_t
sk_mesh_specification_result_t SkMeshSpecification_Make_3(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs, reskia_mesh_specification_alpha_type_t at); // (SkSpan<const SkMeshSpecification::Attribute>* attributes, size_t vertexStride, SkSpan<const SkMeshSpecification::Varying>* varyings, const SkString* vs, const SkString* fs, sk_sp<SkColorSpace>* cs, SkAlphaType at) -> sk_mesh_specification_result_t

#ifdef __cplusplus
}
#endif

#endif //SK_MESH_SPECIFICATION_H
