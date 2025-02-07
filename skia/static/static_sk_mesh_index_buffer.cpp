//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_mesh_index_buffer.h"

#include <utility>
#include "static_sk_mesh_index_buffer-internal.h"

static std::set<int> static_sk_mesh_index_buffer_available_keys;
static std::map<int , sk_sp<SkMesh::IndexBuffer>> static_sk_mesh_index_buffer;
static int static_sk_mesh_index_buffer_index = 0;

int static_sk_mesh_index_buffer_make(sk_sp<SkMesh::IndexBuffer> value) {
    int key;
    if (!static_sk_mesh_index_buffer_available_keys.empty()) {
        auto it = static_sk_mesh_index_buffer_available_keys.begin();
        key = *it;
        static_sk_mesh_index_buffer_available_keys.erase(it);
    } else {
        key = static_sk_mesh_index_buffer_index++;
    }
    static_sk_mesh_index_buffer[key] = std::move(value);
    return key;
}

void static_sk_mesh_index_buffer_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mesh_index_buffer[key].reset();
    static_sk_mesh_index_buffer.erase(key);
    static_sk_mesh_index_buffer_available_keys.insert(key);
}

void *static_sk_mesh_index_buffer_get(int key) { // -> SkMesh::IndexBuffer *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_mesh_index_buffer[key].get();
}

void static_sk_mesh_index_buffer_set(int key, sk_sp<SkMesh::IndexBuffer> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mesh_index_buffer[key] = std::move(value);
}

sk_sp<SkMesh::IndexBuffer> static_sk_mesh_index_buffer_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_mesh_index_buffer[key]);
}
