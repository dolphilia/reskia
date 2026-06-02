//
// Created by dolphilia on 25/02/04.
//

#ifndef SK_MESH_H
#define SK_MESH_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_mesh_child_ptr.h"
#include "../handles/static_sk_mesh_index_buffer.h"
#include "../handles/static_sk_mesh_result.h"
#include "../handles/static_sk_mesh_specification.h"
#include "../handles/static_sk_mesh_vertex_buffer.h"
#include "../handles/static_sk_rect.h"

typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_mesh_index_buffer_t reskia_mesh_index_buffer_t;
typedef struct reskia_mesh_specification_t reskia_mesh_specification_t;
typedef struct reskia_mesh_t reskia_mesh_t;
typedef struct reskia_mesh_vertex_buffer_t reskia_mesh_vertex_buffer_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef int32_t reskia_mesh_mode_t;

void SkMesh_delete(reskia_mesh_t * mesh); // No-op for NULL input.
sk_mesh_specification_t SkMesh_refSpec(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
reskia_mesh_specification_t * SkMesh_spec(reskia_mesh_t * mesh); // Borrowed pointer. Returns NULL for NULL mesh.
reskia_mesh_mode_t SkMesh_mode(reskia_mesh_t * mesh); // Returns -1 for NULL mesh.
sk_mesh_vertex_buffer_t SkMesh_refVertexBuffer(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
reskia_mesh_vertex_buffer_t * SkMesh_vertexBuffer(reskia_mesh_t * mesh); // Borrowed pointer. Returns NULL for NULL mesh.
size_t SkMesh_vertexOffset(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
size_t SkMesh_vertexCount(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
sk_mesh_index_buffer_t SkMesh_refIndexBuffer(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
reskia_mesh_index_buffer_t * SkMesh_indexBuffer(reskia_mesh_t * mesh); // Borrowed pointer. Returns NULL for NULL mesh.
size_t SkMesh_indexOffset(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
size_t SkMesh_indexCount(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
const_sk_data_t SkMesh_refUniforms(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
const reskia_data_t * SkMesh_uniforms(reskia_mesh_t * mesh); // Borrowed pointer. Returns NULL for NULL mesh.
const_sk_mesh_child_ptr_t SkMesh_children(reskia_mesh_t * mesh); // Returns 0 for NULL mesh. Returned span is borrowed from mesh.
sk_rect_t SkMesh_bounds(reskia_mesh_t * mesh); // Returns 0 for NULL mesh.
bool SkMesh_isValid(reskia_mesh_t * mesh); // Returns false for NULL mesh.
// static
/**
 * bounds must be non-NULL.
 * Returns 0 or an invalid result for invalid input.
 */
sk_mesh_result_t SkMesh_Make(sk_mesh_specification_t spec, reskia_mesh_mode_t mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const reskia_rect_t * bounds);
/**
 * bounds must be non-NULL.
 * Returns 0 or an invalid result for invalid input.
 */
sk_mesh_result_t SkMesh_MakeIndexed(sk_mesh_specification_t spec, reskia_mesh_mode_t mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, sk_mesh_index_buffer_t iBuffer, size_t indexCount, size_t indexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const reskia_rect_t * bounds);

#ifdef __cplusplus
}
#endif

#endif //SK_MESH_H
