//
// Created by dolphilia on 2024/01/13.
//

#ifndef RAIA_SKIA_SK_MESHES_H
#define RAIA_SKIA_SK_MESHES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../static/static_sk_mesh_index_buffer.h"
#include "../static/static_sk_mesh_vertex_buffer.h"

typedef struct reskia_mesh_index_buffer_sp_t reskia_mesh_index_buffer_sp_t;
typedef struct reskia_mesh_vertex_buffer_sp_t reskia_mesh_vertex_buffer_sp_t;

// static

sk_mesh_index_buffer_t SkMeshes_MakeIndexBuffer(const uint8_t *data, size_t size); // // (const void *data, size_t size) -> sk_mesh_index_buffer_t
sk_mesh_index_buffer_t SkMeshes_CopyIndexBuffer(const reskia_mesh_index_buffer_sp_t *indexBuffer); // // (const sk_sp< SkMesh::IndexBuffer > *indexBuffer) -> sk_mesh_index_buffer_t
sk_mesh_vertex_buffer_t SkMeshes_MakeVertexBuffer(const uint8_t *data, size_t size); // // (const void *data, size_t size) -> sk_mesh_vertex_buffer_t
sk_mesh_vertex_buffer_t SkMeshes_CopyVertexBuffer(const reskia_mesh_vertex_buffer_sp_t *vertexBuffer); // // (const sk_sp< SkMesh::VertexBuffer > *vertexBuffer) -> sk_mesh_vertex_buffer_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MESHES_H
