//
// Created by dolphilia on 2024/01/13.
//

#include "sk_meshes.h"

#include "include/core/SkMesh.h"
#include "../handles/static_sk_mesh_index_buffer.h"
#include "../handles/static_sk_mesh_vertex_buffer.h"

#include "../handles/static_sk_mesh_vertex_buffer-internal.h"
#include "../handles/static_sk_mesh_index_buffer-internal.h"

extern "C" {

sk_mesh_index_buffer_t SkMeshes_MakeIndexBuffer(const uint8_t *data, size_t size) {
    return static_sk_mesh_index_buffer_make(SkMeshes::MakeIndexBuffer(data, size));
}

sk_mesh_index_buffer_t SkMeshes_CopyIndexBuffer(const reskia_mesh_index_buffer_sp_t *indexBuffer) {
    return static_sk_mesh_index_buffer_make(SkMeshes::CopyIndexBuffer(* reinterpret_cast<const sk_sp<SkMesh::IndexBuffer> *>(indexBuffer)));
}

sk_mesh_vertex_buffer_t SkMeshes_MakeVertexBuffer(const uint8_t *data, size_t size) {
    return static_sk_mesh_vertex_buffer_make(SkMeshes::MakeVertexBuffer(data, size));
}

sk_mesh_vertex_buffer_t SkMeshes_CopyVertexBuffer(const reskia_mesh_vertex_buffer_sp_t *vertexBuffer) {
    return static_sk_mesh_vertex_buffer_make(SkMeshes::CopyVertexBuffer(* reinterpret_cast<const sk_sp<SkMesh::VertexBuffer> *>(vertexBuffer)));
}

}
