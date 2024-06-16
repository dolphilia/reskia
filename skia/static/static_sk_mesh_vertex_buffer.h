//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_MESH_VERTEX_BUFFER_H
#define RAIA_SKIA_STATIC_SK_MESH_VERTEX_BUFFER_H

#include <set>
#include <string>
#include <map>
#include "include/core/SkMesh.h"

typedef int sk_mesh_vertex_buffer_t;

int static_sk_mesh_vertex_buffer_make(sk_sp<SkMesh::VertexBuffer> value);
extern "C" void static_sk_mesh_vertex_buffer_delete(int key);
extern "C" SkMesh::VertexBuffer *static_sk_mesh_vertex_buffer_get(int key);
void static_sk_mesh_vertex_buffer_set(int key, sk_sp<SkMesh::VertexBuffer> value);
sk_sp<SkMesh::VertexBuffer> static_sk_mesh_vertex_buffer_move(int key);

#endif //RAIA_SKIA_STATIC_SK_MESH_VERTEX_BUFFER_H
