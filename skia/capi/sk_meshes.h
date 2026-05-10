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

sk_mesh_index_buffer_t SkMeshes_MakeIndexBuffer(const uint8_t *data, size_t size); // size > 0 では data は非 NULL。invalid 入力では 0
sk_mesh_index_buffer_t SkMeshes_CopyIndexBuffer(const reskia_mesh_index_buffer_sp_t *indexBuffer); // indexBuffer は非 NULL。invalid 入力では 0
sk_mesh_vertex_buffer_t SkMeshes_MakeVertexBuffer(const uint8_t *data, size_t size); // size > 0 では data は非 NULL。invalid 入力では 0
sk_mesh_vertex_buffer_t SkMeshes_CopyVertexBuffer(const reskia_mesh_vertex_buffer_sp_t *vertexBuffer); // vertexBuffer は非 NULL。invalid 入力では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MESHES_H
