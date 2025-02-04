//
// Created by dolphilia on 25/02/04.
//

#include "static_sk_mesh_specification.h"

#include <map>
#include <set>
#include <utility>
#include "include/core/SkMesh.h"
//#include "static_sk_mesh-internal.h"

static std::set<int> static_sk_mesh_specification_available_keys;
static std::map<int , sk_sp<SkMeshSpecification>> static_sk_mesh_specification;
static int static_sk_mesh_specification_index = 0;

int static_sk_mesh_specification_make(sk_sp<SkMeshSpecification> value) {
    int key;
    if (!static_sk_mesh_specification_available_keys.empty()) {
        auto it = static_sk_mesh_specification_available_keys.begin();
        key = *it;
        static_sk_mesh_specification_available_keys.erase(it);
    } else {
        key = static_sk_mesh_specification_index++;
    }
    static_sk_mesh_specification[key] = std::move(value);
    return key;
}

void static_sk_mesh_delete(int key) {
    static_sk_mesh_specification[key].reset();
    static_sk_mesh_specification.erase(key);
    static_sk_mesh_specification_available_keys.insert(key);
}

void *static_sk_mesh_get(int key) { // -> SkMesh::IndexBuffer *
    return static_sk_mesh_specification[key].get();
}

void static_sk_mesh_set(int key, sk_sp<SkMeshSpecification> value) {
    static_sk_mesh_specification[key] = std::move(value);
}

sk_sp<SkMeshSpecification> static_sk_mesh_move(int key) {
    return std::move(static_sk_mesh_specification[key]);
}