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

void SkMeshSpecification_delete(void* spec) {
    delete static_cast<SkMeshSpecification *>(spec);
}

sk_mesh_specification_attribute_t SkMeshSpecification_attributes(void* spec) {
    return static_sk_mesh_specification_attribute_make(static_cast<SkMeshSpecification *>(spec)->attributes());
}

size_t SkMeshSpecification_uniformSize(void* spec) {
    return static_cast<SkMeshSpecification *>(spec)->uniformSize();
}

const_sk_runtime_effect_uniform_t SkMeshSpecification_uniforms(void* spec) {
    return static_const_sk_runtime_effect_uniform_make(static_cast<SkMeshSpecification *>(spec)->uniforms());
}

const_sk_runtime_effect_child_t SkMeshSpecification_children(void* spec) {
    return static_const_sk_runtime_effect_child_make(static_cast<SkMeshSpecification *>(spec)->children());
}

const void * SkMeshSpecification_findChild(void* spec, void * name) {
    return static_cast<SkMeshSpecification *>(spec)->findChild(* static_cast<std::string_view *>(name));
}

const void * SkMeshSpecification_findUniform(void* spec, void * name) {
    return static_cast<SkMeshSpecification *>(spec)->findUniform(*static_cast<std::string_view *>(name));
}

const void * SkMeshSpecification_findAttribute(void* spec, void * name) {
    return static_cast<SkMeshSpecification *>(spec)->findAttribute(*static_cast<std::string_view *>(name));
}

const void * SkMeshSpecification_findVarying(void* spec, void * name) {
    return static_cast<SkMeshSpecification *>(spec)->findVarying(*static_cast<std::string_view *>(name));
}

size_t SkMeshSpecification_stride(void* spec) {
    return static_cast<SkMeshSpecification *>(spec)->stride();
}

// static

sk_mesh_specification_result_t SkMeshSpecification_Make(void * attributes, size_t vertexStride, void * varyings, const void * vs, const void * fs) {
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* static_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * static_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * static_cast<const SkString *>(vs), * static_cast<const SkString *>(fs)));
}

sk_mesh_specification_result_t SkMeshSpecification_Make_2(void * attributes, size_t vertexStride, void * varyings, const void * vs, const void * fs, void * cs) {
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* static_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * static_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * static_cast<const SkString *>(vs), * static_cast<const SkString *>(fs), * static_cast<sk_sp<SkColorSpace> *>(cs)));
}

sk_mesh_specification_result_t SkMeshSpecification_Make_3(void * attributes, size_t vertexStride, void * varyings, const void * vs, const void * fs, void * cs, int at) {
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* static_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * static_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * static_cast<const SkString *>(vs), * static_cast<const SkString *>(fs), * static_cast<sk_sp<SkColorSpace> *>(cs), static_cast<SkAlphaType>(at)));
}

}