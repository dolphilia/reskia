//
// Created by dolphilia on 25/02/04.
//

#include "sk_mesh_specification.h"

#include "include/core/SkColorSpace.h"
#include "include/core/SkMesh.h"

#include "../handles/static_sk_runtime_effect_child.h"
#include "../handles/static_sk_runtime_effect_uniform.h"
#include "../handles/static_sk_mesh_specification_attribute.h"
#include "../handles/static_sk_mesh_specification_result.h"

#include "../handles/static_sk_runtime_effect_child-internal.h"
#include "../handles/static_sk_runtime_effect_uniform-internal.h"
#include "../handles/static_sk_mesh_specification_attribute-internal.h"
#include "../handles/static_sk_mesh_specification_result-internal.h"

#include <utility>

namespace {

SkMeshSpecification *as_mesh_specification(reskia_mesh_specification_t *spec) {
    return reinterpret_cast<SkMeshSpecification *>(spec);
}

const SkMeshSpecification *as_mesh_specification(const reskia_mesh_specification_t *spec) {
    return reinterpret_cast<const SkMeshSpecification *>(spec);
}

bool has_make_inputs(reskia_mesh_specification_attribute_span_t *attributes,
                     reskia_mesh_specification_varying_span_t *varyings,
                     const reskia_string_t *vs,
                     const reskia_string_t *fs) {
    return attributes != nullptr && varyings != nullptr && vs != nullptr && fs != nullptr;
}

}  // namespace

extern "C" {

void SkMeshSpecification_delete(reskia_mesh_specification_t* spec) {
    delete as_mesh_specification(spec);
}

sk_mesh_specification_attribute_t SkMeshSpecification_attributes(reskia_mesh_specification_t* spec) {
    if (spec == nullptr) {
        return 0;
    }
    return static_sk_mesh_specification_attribute_make(as_mesh_specification(spec)->attributes());
}

size_t SkMeshSpecification_uniformSize(reskia_mesh_specification_t* spec) {
    if (spec == nullptr) {
        return 0;
    }
    return as_mesh_specification(spec)->uniformSize();
}

const_sk_runtime_effect_uniform_t SkMeshSpecification_uniforms(reskia_mesh_specification_t* spec) {
    if (spec == nullptr) {
        return 0;
    }
    return static_const_sk_runtime_effect_uniform_make(as_mesh_specification(spec)->uniforms());
}

const_sk_runtime_effect_child_t SkMeshSpecification_children(reskia_mesh_specification_t* spec) {
    if (spec == nullptr) {
        return 0;
    }
    return static_const_sk_runtime_effect_child_make(as_mesh_specification(spec)->children());
}

const reskia_runtime_effect_child_t * SkMeshSpecification_findChild(reskia_mesh_specification_t* spec, const reskia_string_view_t * name) {
    if (spec == nullptr || name == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_runtime_effect_child_t *>(as_mesh_specification(spec)->findChild(* reinterpret_cast<const std::string_view *>(name)));
}

const reskia_runtime_effect_uniform_t * SkMeshSpecification_findUniform(reskia_mesh_specification_t* spec, const reskia_string_view_t * name) {
    if (spec == nullptr || name == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_runtime_effect_uniform_t *>(as_mesh_specification(spec)->findUniform(*reinterpret_cast<const std::string_view *>(name)));
}

const reskia_mesh_specification_attribute_t * SkMeshSpecification_findAttribute(reskia_mesh_specification_t* spec, const reskia_string_view_t * name) {
    if (spec == nullptr || name == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_mesh_specification_attribute_t *>(as_mesh_specification(spec)->findAttribute(*reinterpret_cast<const std::string_view *>(name)));
}

const reskia_mesh_specification_varying_t * SkMeshSpecification_findVarying(reskia_mesh_specification_t* spec, const reskia_string_view_t * name) {
    if (spec == nullptr || name == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_mesh_specification_varying_t *>(as_mesh_specification(spec)->findVarying(*reinterpret_cast<const std::string_view *>(name)));
}

size_t SkMeshSpecification_stride(reskia_mesh_specification_t* spec) {
    if (spec == nullptr) {
        return 0;
    }
    return as_mesh_specification(spec)->stride();
}

// static

sk_mesh_specification_result_t SkMeshSpecification_Make(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs) {
    if (!has_make_inputs(attributes, varyings, vs, fs)) {
        return 0;
    }
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* reinterpret_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * reinterpret_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * reinterpret_cast<const SkString *>(vs), * reinterpret_cast<const SkString *>(fs)));
}

sk_mesh_specification_result_t SkMeshSpecification_MakeWithColorSpace(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs) {
    if (!has_make_inputs(attributes, varyings, vs, fs)) {
        return 0;
    }
    sk_sp<SkColorSpace> colorSpace;
    if (cs != nullptr) {
        colorSpace = *reinterpret_cast<sk_sp<SkColorSpace> *>(cs);
    }
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* reinterpret_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * reinterpret_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * reinterpret_cast<const SkString *>(vs), * reinterpret_cast<const SkString *>(fs), std::move(colorSpace)));
}

sk_mesh_specification_result_t SkMeshSpecification_MakeWithColorSpaceAndAlphaType(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs, reskia_mesh_specification_alpha_type_t at) {
    if (!has_make_inputs(attributes, varyings, vs, fs)) {
        return 0;
    }
    sk_sp<SkColorSpace> colorSpace;
    if (cs != nullptr) {
        colorSpace = *reinterpret_cast<sk_sp<SkColorSpace> *>(cs);
    }
    return static_sk_mesh_specification_result_make(SkMeshSpecification::Make(* reinterpret_cast<SkSpan<const SkMeshSpecification::Attribute> *>(attributes), vertexStride, * reinterpret_cast<SkSpan<const SkMeshSpecification::Varying> *>(varyings), * reinterpret_cast<const SkString *>(vs), * reinterpret_cast<const SkString *>(fs), std::move(colorSpace), static_cast<SkAlphaType>(at)));
}

}
