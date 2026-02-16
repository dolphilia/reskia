//
// Created by dolphilia on 25/02/05.
//

#include "static_sk_mesh_specification_result.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_mesh_specification_result-internal.h"

static reskia::static_registry::HandleTable<SkMeshSpecification::Result> static_sk_mesh_specification_result;

int static_sk_mesh_specification_result_make(SkMeshSpecification::Result value) {
    return static_sk_mesh_specification_result.create(std::move(value));
}

void static_sk_mesh_specification_result_set(int key, SkMeshSpecification::Result value) {
    static_sk_mesh_specification_result.set(key, std::move(value));
}

SkMeshSpecification::Result static_sk_mesh_specification_result_get_entity(int key) {
    SkMeshSpecification::Result* entity = static_sk_mesh_specification_result.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_mesh_specification_result_delete(int key) {
    static_sk_mesh_specification_result.erase(key);
}

void * static_sk_mesh_specification_result_get_ptr(int key) {
    return static_sk_mesh_specification_result.get_ptr(key);
}

}
