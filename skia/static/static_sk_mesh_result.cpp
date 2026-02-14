//
// Created by dolphilia on 25/02/04.
//

#include "static_sk_mesh_result.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_mesh_result-internal.h"

static reskia::static_registry::HandleTable<SkMesh::Result> static_sk_mesh_result;

int static_sk_mesh_result_make(SkMesh::Result value) {
    return static_sk_mesh_result.create(std::move(value));
}

void static_sk_mesh_result_set(int key, SkMesh::Result value) {
    static_sk_mesh_result.set(key, std::move(value));
}

SkMesh::Result static_sk_mesh_result_get_entity(int key) {
    SkMesh::Result* entity = static_sk_mesh_result.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_mesh_result_delete(int key) {
    static_sk_mesh_result.erase(key);
}

void * static_sk_mesh_result_get_ptr(int key) {
    return static_sk_mesh_result.get_ptr(key);
}

}
