//
// Created by dolphilia on 25/02/04.
//

#include "static_sk_mesh_result.h"

#include "static_sk_mesh_result-internal.h"

static std::set<int> static_sk_mesh_result_available_keys;
static std::map<int , SkMesh::Result> static_sk_mesh_result;
static int static_sk_mesh_result_index = 0;

int static_sk_mesh_result_make(SkMesh::Result value) {
    int key;
    if (!static_sk_mesh_result_available_keys.empty()) {
        auto it = static_sk_mesh_result_available_keys.begin();
        key = *it;
        static_sk_mesh_result_available_keys.erase(it);
    } else {
        key = static_sk_mesh_result_index++;
    }
    static_sk_mesh_result[key] = value;
    return key;
}

void static_sk_mesh_result_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mesh_result.erase(key);
    static_sk_mesh_result_available_keys.insert(key);
}

SkMesh::Result static_sk_mesh_result_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_mesh_result[key];
}

void * static_sk_mesh_result_get_ptr(int key) { // -> SkPath *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_mesh_result[key];
}

void static_sk_mesh_result_set(int key, SkMesh::Result value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mesh_result[key] = value;
}