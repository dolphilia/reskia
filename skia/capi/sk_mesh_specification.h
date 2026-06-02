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
typedef struct reskia_color_space_t reskia_color_space_t;
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

void SkMeshSpecification_delete(reskia_mesh_specification_t* spec); // No-op for NULL input.
sk_mesh_specification_attribute_t SkMeshSpecification_attributes(reskia_mesh_specification_t* spec); // Returns 0 for NULL spec. Returned span handle is borrowed from spec.
size_t SkMeshSpecification_uniformSize(reskia_mesh_specification_t* spec); // Returns 0 for NULL spec.
int SkMeshSpecification_uniforms(reskia_mesh_specification_t* spec); // Returns 0 for NULL spec. Returned span handle is borrowed from spec.
int SkMeshSpecification_children(reskia_mesh_specification_t* spec); // Returns 0 for NULL spec. Returned span handle is borrowed from spec.
/**
 * Returns NULL for NULL spec/name or when not found.
 * Returned pointer is borrowed from spec.
 */
const reskia_runtime_effect_child_t * SkMeshSpecification_findChild(reskia_mesh_specification_t* spec, const reskia_string_view_t * name);
/**
 * Returns NULL for NULL spec/name or when not found.
 * Returned pointer is borrowed from spec.
 */
const reskia_runtime_effect_uniform_t * SkMeshSpecification_findUniform(reskia_mesh_specification_t* spec, const reskia_string_view_t * name);
/**
 * Returns NULL for NULL spec/name or when not found.
 * Returned pointer is borrowed from spec.
 */
const reskia_mesh_specification_attribute_t * SkMeshSpecification_findAttribute(reskia_mesh_specification_t* spec, const reskia_string_view_t * name);
/**
 * Returns NULL for NULL spec/name or when not found.
 * Returned pointer is borrowed from spec.
 */
const reskia_mesh_specification_varying_t * SkMeshSpecification_findVarying(reskia_mesh_specification_t* spec, const reskia_string_view_t * name);
size_t SkMeshSpecification_stride(reskia_mesh_specification_t* spec); // Returns 0 for NULL spec.
reskia_color_space_t *SkMeshSpecification_colorSpace(reskia_mesh_specification_t* spec); // Borrowed pointer. Returns NULL for NULL spec.
// static
/**
 * attributes, varyings, vs, and fs must be non-NULL.
 * Returns 0 for invalid input.
 */
sk_mesh_specification_result_t SkMeshSpecification_Make(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs);
/**
 * attributes, varyings, vs, and fs must be non-NULL. cs may be NULL.
 * Returns 0 for invalid input.
 */
sk_mesh_specification_result_t SkMeshSpecification_MakeWithColorSpace(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs);
/**
 * attributes, varyings, vs, and fs must be non-NULL. cs may be NULL.
 * Returns 0 for invalid input.
 */
sk_mesh_specification_result_t SkMeshSpecification_MakeWithColorSpaceAndAlphaType(reskia_mesh_specification_attribute_span_t * attributes, size_t vertexStride, reskia_mesh_specification_varying_span_t * varyings, const reskia_string_t * vs, const reskia_string_t * fs, reskia_color_space_sp_t * cs, reskia_mesh_specification_alpha_type_t at);

#ifdef __cplusplus
}
#endif

#endif //SK_MESH_SPECIFICATION_H
