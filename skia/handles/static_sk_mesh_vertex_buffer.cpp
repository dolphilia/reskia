//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_mesh_vertex_buffer.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_mesh_vertex_buffer-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkMesh::VertexBuffer>> static_sk_mesh_vertex_buffer;

int static_sk_mesh_vertex_buffer_make(sk_sp<SkMesh::VertexBuffer> value) {
    return static_sk_mesh_vertex_buffer.create(std::move(value));
}

void static_sk_mesh_vertex_buffer_set(int key, sk_sp<SkMesh::VertexBuffer> value) {
    static_sk_mesh_vertex_buffer.set(key, std::move(value));
}

sk_sp<SkMesh::VertexBuffer> static_sk_mesh_vertex_buffer_borrow_entity(int key) {
    sk_sp<SkMesh::VertexBuffer>* entity = static_sk_mesh_vertex_buffer.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkMesh::VertexBuffer> static_sk_mesh_vertex_buffer_take_entity(int key) {
    return static_sk_mesh_vertex_buffer.take_or_default(key);
}

sk_sp<SkMesh::VertexBuffer> static_sk_mesh_vertex_buffer_get_entity(int key) {
    return static_sk_mesh_vertex_buffer_borrow_entity(key);
}

extern "C" {

void static_sk_mesh_vertex_buffer_delete(int key) {
    static_sk_mesh_vertex_buffer.erase(key);
}

void *static_sk_mesh_vertex_buffer_get_ptr(int key) { // -> SkMesh::VertexBuffer *
    sk_sp<SkMesh::VertexBuffer>* entity = static_sk_mesh_vertex_buffer.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
