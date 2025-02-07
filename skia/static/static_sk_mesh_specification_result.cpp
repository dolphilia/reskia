//
// Created by dolphilia on 25/02/05.
//

#include "static_sk_mesh_specification_result.h"

#include "static_sk_mesh_specification_result-internal.h"

static std::set<int> static_sk_mesh_specification_result_available_keys;
static std::map<int , SkMeshSpecification::Result> static_sk_mesh_specification_result;
static int static_sk_mesh_specification_result_index = 0;

int static_sk_mesh_specification_result_make(SkMeshSpecification::Result value) {
    int key;
    if (!static_sk_mesh_specification_result_available_keys.empty()) {
        auto it = static_sk_mesh_specification_result_available_keys.begin();
        key = *it;
        static_sk_mesh_specification_result_available_keys.erase(it);
    } else {
        key = static_sk_mesh_specification_result_index++;
    }
    static_sk_mesh_specification_result[key] = value;
    return key;
}

void static_sk_mesh_specification_result_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mesh_specification_result.erase(key);
    static_sk_mesh_specification_result_available_keys.insert(key);
}

SkMeshSpecification::Result static_sk_mesh_specification_result_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_mesh_specification_result[key];
}

void * static_sk_mesh_specification_result_get_ptr(int key) { // -> SkPath *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_mesh_specification_result[key];
}

void static_sk_mesh_specification_result_set(int key, SkMeshSpecification::Result value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mesh_specification_result[key] = value;
}