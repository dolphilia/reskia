//
// Created by dolphilia on 25/02/04.
//

#include "sk_mesh_specification.h"

#include "include/Core/SkColorSpace.h"
#include "include/core/SkMesh.h"

#include "../static/static_sk_runtime_effect_child.h"
#include "../static/static_sk_runtime_effect_uniform.h"

#include "../static/static_sk_runtime_effect_child-internal.h"
#include "../static/static_sk_runtime_effect_uniform-internal.h"


extern "C" {

SkSpan<const SkMeshSpecification::Attribute> SkMeshSpecification_attributes(SkMeshSpecification* spec) {
    return spec->attributes();
}

size_t SkMeshSpecification_uniformSize(SkMeshSpecification* spec) {
    return spec->uniformSize();
}

const_sk_runtime_effect_uniform_t SkMeshSpecification_uniforms(SkMeshSpecification* spec) {
    return static_const_sk_runtime_effect_uniform_make(spec->uniforms());
}

const_sk_runtime_effect_child_t SkMeshSpecification_children(SkMeshSpecification* spec) {
    return static_const_sk_runtime_effect_child_make(spec->children());
}

const SkRuntimeEffect::Child* SkMeshSpecification_findChild(SkMeshSpecification* spec, std::string_view * name) {
    return spec->findChild(*name);
}

const SkRuntimeEffect::Uniform* SkMeshSpecification_findUniform(SkMeshSpecification* spec, std::string_view * name) {
    return spec->findUniform(*name);
}

const SkMeshSpecification::Attribute* SkMeshSpecification_findAttribute(SkMeshSpecification* spec, std::string_view * name) {
    return spec->findAttribute(*name);
}

const SkMeshSpecification::Varying* SkMeshSpecification_findVarying(SkMeshSpecification* spec, std::string_view * name) {
    return spec->findVarying(*name);
}

size_t SkMeshSpecification_stride(SkMeshSpecification* spec) {
    return spec->stride();
}

// static

SkMeshSpecification::Result SkMeshSpecification_Make(SkSpan<const SkMeshSpecification::Attribute> * attributes, size_t vertexStride, SkSpan<const SkMeshSpecification::Varying> * varyings, const SkString * vs, const SkString * fs) {
    return SkMeshSpecification::Make(*attributes, vertexStride, *varyings, *vs, *fs);
}

SkMeshSpecification::Result SkMeshSpecification_Make_2(SkSpan<const SkMeshSpecification::Attribute> * attributes, size_t vertexStride, SkSpan<const SkMeshSpecification::Varying> * varyings, const SkString * vs, const SkString * fs, sk_sp<SkColorSpace> * cs) {
    return SkMeshSpecification::Make(*attributes, vertexStride, *varyings, *vs, *fs, *cs);
}

SkMeshSpecification::Result SkMeshSpecification_Make_3(SkSpan<const SkMeshSpecification::Attribute> * attributes, size_t vertexStride, SkSpan<const SkMeshSpecification::Varying> * varyings, const SkString * vs, const SkString * fs, sk_sp<SkColorSpace> * cs, SkAlphaType at) {
    return SkMeshSpecification::Make(*attributes, vertexStride, *varyings, *vs, *fs, *cs, at);
}

}