//
// Created by dolphilia on 25/02/04.
//

#include "static_sk_mesh_specification.h"

#include <utility>
#include "include/core/SkMesh.h"
#include "handle_table.hpp"
//#include "static_sk_mesh-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkMeshSpecification>> static_sk_mesh_specification;

int static_sk_mesh_specification_make(sk_sp<SkMeshSpecification> value) {
    return static_sk_mesh_specification.create(std::move(value));
}

void static_sk_mesh_specification_set(int key, sk_sp<SkMeshSpecification> value) {
    static_sk_mesh_specification.set(key, std::move(value));
}

sk_sp<SkMeshSpecification> static_sk_mesh_specification_borrow_entity(int key) {
    sk_sp<SkMeshSpecification>* entity = static_sk_mesh_specification.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkMeshSpecification> static_sk_mesh_specification_take_entity(int key) {
    return static_sk_mesh_specification.take_or_default(key);
}

sk_sp<SkMeshSpecification> static_sk_mesh_specification_get_entity(int key) {
    return static_sk_mesh_specification_borrow_entity(key);
}

extern "C" {

void static_sk_mesh_specification_delete(int key) {
    static_sk_mesh_specification.erase(key);
}

void *static_sk_mesh_specification_get_ptr(int key) {
    sk_sp<SkMeshSpecification>* entity = static_sk_mesh_specification.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
