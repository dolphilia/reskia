//
// Created by dolphilia on 25/02/04.
//

#ifndef SK_MESH_H
#define SK_MESH_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../static/static_sk_data.h"
#include "../static/static_sk_mesh_child_ptr.h"
#include "../static/static_sk_mesh_index_buffer.h"
#include "../static/static_sk_mesh_result.h"
#include "../static/static_sk_mesh_specification.h"
#include "../static/static_sk_mesh_vertex_buffer.h"
#include "../static/static_sk_rect.h"

typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_mesh_index_buffer_t reskia_mesh_index_buffer_t;
typedef struct reskia_mesh_specification_t reskia_mesh_specification_t;
typedef struct reskia_mesh_t reskia_mesh_t;
typedef struct reskia_mesh_vertex_buffer_t reskia_mesh_vertex_buffer_t;
typedef struct reskia_rect_t reskia_rect_t;

void SkMesh_delete(reskia_mesh_t * mesh); // (SkMesh * mesh)
sk_mesh_specification_t SkMesh_refSpec(reskia_mesh_t * mesh); // (SkMesh *mesh) -> sk_mesh_specification_t
reskia_mesh_specification_t * SkMesh_spec(reskia_mesh_t * mesh); // (SkMesh *mesh) -> SkMeshSpecification*
int SkMesh_mode(reskia_mesh_t * mesh); // (SkMesh *mesh) -> SkMesh::Mode
sk_mesh_vertex_buffer_t SkMesh_refVertexBuffer(reskia_mesh_t * mesh); // (SkMesh *mesh) -> sk_mesh_vertex_buffer_t
reskia_mesh_vertex_buffer_t * SkMesh_vertexBuffer(reskia_mesh_t * mesh); // (SkMesh *mesh) -> SkMesh::VertexBuffer*
size_t SkMesh_vertexOffset(reskia_mesh_t * mesh); // (SkMesh *mesh) -> size_t
size_t SkMesh_vertexCount(reskia_mesh_t * mesh); // (SkMesh *mesh) -> size_t
sk_mesh_index_buffer_t SkMesh_refIndexBuffer(reskia_mesh_t * mesh); // (SkMesh *mesh) -> sk_mesh_index_buffer_t
reskia_mesh_index_buffer_t * SkMesh_indexBuffer(reskia_mesh_t * mesh); // (SkMesh *mesh) -> SkMesh::IndexBuffer*
size_t SkMesh_indexOffset(reskia_mesh_t * mesh); // (SkMesh *mesh) -> size_t
size_t SkMesh_indexCount(reskia_mesh_t * mesh); // (SkMesh *mesh) -> size_t
const_sk_data_t SkMesh_refUniforms(reskia_mesh_t * mesh); // (SkMesh *mesh) -> const_sk_data_t
const reskia_data_t * SkMesh_uniforms(reskia_mesh_t * mesh); // (SkMesh *mesh) -> const SkData*
const_sk_mesh_child_ptr_t SkMesh_children(reskia_mesh_t * mesh); // (SkMesh *mesh) -> const_sk_mesh_child_ptr_t
sk_rect_t SkMesh_bounds(reskia_mesh_t * mesh); // (SkMesh *mesh) -> sk_rect_t
bool SkMesh_isValid(reskia_mesh_t * mesh); // (SkMesh *mesh) -> bool
// static
sk_mesh_result_t SkMesh_Make(sk_mesh_specification_t spec, int mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const reskia_rect_t * bounds); // (sk_mesh_specification_t spec, SkMesh::Mode mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const SkRect *bounds) -> sk_mesh_result_t
sk_mesh_result_t SkMesh_MakeIndexed(sk_mesh_specification_t spec, int mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, sk_mesh_index_buffer_t iBuffer, size_t indexCount, size_t indexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const reskia_rect_t * bounds); // (sk_mesh_specification_t spec, SkMesh::Mode mode, sk_mesh_vertex_buffer_t vBuffer, size_t vertexCount, size_t vertexOffset, sk_mesh_index_buffer_t iBuffer, size_t indexCount, size_t indexOffset, const_sk_data_t uniforms, sk_mesh_child_ptr_t children, const SkRect *bounds) -> sk_mesh_result_t

#ifdef __cplusplus
}
#endif

#endif //SK_MESH_H
