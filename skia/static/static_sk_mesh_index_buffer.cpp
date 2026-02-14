//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_mesh_index_buffer.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_mesh_index_buffer-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkMesh::IndexBuffer>> static_sk_mesh_index_buffer;

int static_sk_mesh_index_buffer_make(sk_sp<SkMesh::IndexBuffer> value) {
    return static_sk_mesh_index_buffer.create(std::move(value));
}

void static_sk_mesh_index_buffer_set(int key, sk_sp<SkMesh::IndexBuffer> value) {
    static_sk_mesh_index_buffer.set(key, std::move(value));
}

sk_sp<SkMesh::IndexBuffer> static_sk_mesh_index_buffer_borrow_entity(int key) {
    sk_sp<SkMesh::IndexBuffer>* entity = static_sk_mesh_index_buffer.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkMesh::IndexBuffer> static_sk_mesh_index_buffer_take_entity(int key) {
    return static_sk_mesh_index_buffer.take_or_default(key);
}

sk_sp<SkMesh::IndexBuffer> static_sk_mesh_index_buffer_get_entity(int key) {
    return static_sk_mesh_index_buffer_borrow_entity(key);
}

extern "C" {

void static_sk_mesh_index_buffer_delete(int key) {
    static_sk_mesh_index_buffer.erase(key);
}

void *static_sk_mesh_index_buffer_get_ptr(int key) { // -> SkMesh::IndexBuffer *
    sk_sp<SkMesh::IndexBuffer>* entity = static_sk_mesh_index_buffer.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
