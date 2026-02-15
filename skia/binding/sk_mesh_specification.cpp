//
// Created by dolphilia on 25/02/04.
//

#include "sk_mesh_specification.h"

#include "include/core/SkColorSpace.h"
#include "include/core/SkMesh.h"

#include "../static/static_sk_runtime_effect_child.h"
#include "../static/static_sk_runtime_effect_uniform.h"
#include "../static/static_sk_mesh_specification_attribute.h"
#include "../static/static_sk_mesh_specification_result.h"

#include "../static/static_sk_runtime_effect_child-internal.h"
#include "../static/static_sk_runtime_effect_uniform-internal.h"
#include "../static/static_sk_mesh_specification_attribute-internal.h"
#include "../static/static_sk_mesh_specification_result-internal.h"

extern "C" {

void SkMeshSpecification_delete(reskia_mesh_specification_t* spec) {
    delete reinterpret_cast<SkMeshSpecification *>(spec);
}

sk_mesh_specification_attribute_t SkMeshSpecification_attributes(reskia_mesh_specification_t* spec) {
    return static_sk_mesh_specification_attribute_make(reinterpret_cast<SkMeshSpecification *>(spec)->attributes());
}

size_t SkMeshSpecification_uniformSize(reskia_mesh_specification_t* spec) {
    return reinterpret_cast<SkMeshSpecification *>(spec)->uniformSize();
}

const_sk_runtime_effect_uniform_t SkMeshSpecification_uniforms(reskia_mesh_specification_t* spec) {
    return static_const_sk_runtime_effect_uniform_make(reinterpret_cast<SkMeshSpecification *>(spec)->uniforms());
}

const_sk_runtime_effect_child_t SkMeshSpecification_children(reskia_mesh_specification_t* spec) {
    return static_const_sk_runtime_effect_child_make(reinterpret_cast<SkMeshSpecification *>(spec)->children());
}

const reskia_runtime_effect_child_t * SkMeshSpecification_findChild(reskia_mesh_specification_t* spec, const reskia_string_view_t * name) {
    return reinterpret_cast<const reskia_runtime_effect_child_t *>(reinterpret_cast<SkMeshSpecification *>(spec)->findChild(* reinterpret_cast<const std::string_view *>(name)));
}

const reskia_runtime_effect_uniform_t * SkMeshSpecification_findUniform(reskia_mesh_specification_t* spec, const reskia_string_view_t * name) {
    return reinterpret_cast<const reskia_runtime_effect_uniform_t *>(reinterpret_cast<SkMeshSpecification *>(spec)->findUniform(*reinterpret_cast<const std::string_view *>(name)));
}

const reskia_mesh_specification_attribute_t * SkMeshSpecification_findAttribute(reskia_mesh_specification_t* spec, const reskia_string_view_t * name) {
    return reinterpret_cast<const reskia_mesh_specification_attribute_t *>(reinterpret_cast<SkMeshSpecification *>(spec)->findAttribute(*reinterpret_cast<const std::string_view *>(name)));
}

const reskia_mesh_specification_varying_t * SkMeshSpecification_findVarying(reskia_mesh_specification_t* spec, const reskia_string_view_t * name) {
    return reinterpret_cast<const reskia_mesh_specification_varying_t *>(reinterpret_cast<SkMeshSpecification *>(spec)->findVarying(*reinterpret_cast<const std::string_view *>(name)));
}

size_t SkMeshSpecification_stride(reskia_mesh_specification_t* spec) {
    return reinterpret_cast<SkMeshSpecification *>(spec)->stride();
}

// static

sk_mesh_specification_result_t SkMeshSpecification_Make(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs) {
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* reinterpret_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * reinterpret_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * reinterpret_cast<const SkString *>(vs), * reinterpret_cast<const SkString *>(fs)));
}

sk_mesh_specification_result_t SkMeshSpecification_Make_2(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs) {
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* reinterpret_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * reinterpret_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * reinterpret_cast<const SkString *>(vs), * reinterpret_cast<const SkString *>(fs), * reinterpret_cast<sk_sp<SkColorSpace> *>(cs)));
}

sk_mesh_specification_result_t SkMeshSpecification_Make_3(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs, reskia_mesh_specification_alpha_type_t at) {
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* reinterpret_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * reinterpret_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * reinterpret_cast<const SkString *>(vs), * reinterpret_cast<const SkString *>(fs), * reinterpret_cast<sk_sp<SkColorSpace> *>(cs), static_cast<SkAlphaType>(at)));
}

}
