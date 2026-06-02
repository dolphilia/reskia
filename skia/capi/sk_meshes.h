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

#include "../handles/static_sk_mesh_index_buffer.h"
#include "../handles/static_sk_mesh_vertex_buffer.h"

typedef struct reskia_mesh_index_buffer_sp_t reskia_mesh_index_buffer_sp_t;
typedef struct reskia_mesh_vertex_buffer_sp_t reskia_mesh_vertex_buffer_sp_t;

// static

sk_mesh_index_buffer_t SkMeshes_MakeIndexBuffer(const uint8_t *data, size_t size); // data must be non-NULL when size is greater than 0. Returns 0 for invalid input.
sk_mesh_index_buffer_t SkMeshes_CopyIndexBuffer(const reskia_mesh_index_buffer_sp_t *indexBuffer); // indexBuffer must be non-NULL. Returns 0 for invalid input.
sk_mesh_vertex_buffer_t SkMeshes_MakeVertexBuffer(const uint8_t *data, size_t size); // data must be non-NULL when size is greater than 0. Returns 0 for invalid input.
sk_mesh_vertex_buffer_t SkMeshes_CopyVertexBuffer(const reskia_mesh_vertex_buffer_sp_t *vertexBuffer); // vertexBuffer must be non-NULL. Returns 0 for invalid input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MESHES_H
