//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_mesh_child_ptr.h"

#include <string>
#include <map>
#include "include/core/SkMesh.h"
#include "static_sk_mesh_child_ptr-internal.h"

static std::set<int> static_sk_mesh_child_ptr_available_keys;
static std::map<int , SkSpan<SkMesh::ChildPtr>> static_sk_mesh_child_ptr;
static int static_sk_mesh_child_ptr_index = 0;

static std::set<int> static_const_sk_mesh_child_ptr_available_keys;
static std::map<int , SkSpan<const SkMesh::ChildPtr>> static_const_sk_mesh_child_ptr;
static int static_const_sk_mesh_child_ptr_index = 0;

int static_sk_mesh_child_ptr_make(SkSpan<SkMesh::ChildPtr> value) {
    int key;
    if (!static_sk_mesh_child_ptr_available_keys.empty()) {
        auto it = static_sk_mesh_child_ptr_available_keys.begin();
        key = *it;
        static_sk_mesh_child_ptr_available_keys.erase(it);
    } else {
        key = static_sk_mesh_child_ptr_index++;
    }
    static_sk_mesh_child_ptr[key] = value;
    return key;
}

void static_sk_mesh_child_ptr_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mesh_child_ptr.erase(key);
    static_sk_mesh_child_ptr_available_keys.insert(key);
}

SkSpan<SkMesh::ChildPtr> static_sk_mesh_child_ptr_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_mesh_child_ptr[key];
}

void * static_sk_mesh_child_ptr_get_ptr(int key, int index) { // -> SkString *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_mesh_child_ptr[key][index];
}

void static_sk_mesh_child_ptr_set(int key, SkSpan<SkMesh::ChildPtr> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_mesh_child_ptr[key] = value;
}

//

int static_const_sk_mesh_child_ptr_make(SkSpan<const SkMesh::ChildPtr> value) {
    int key;
    if (!static_const_sk_mesh_child_ptr_available_keys.empty()) {
        auto it = static_const_sk_mesh_child_ptr_available_keys.begin();
        key = *it;
        static_const_sk_mesh_child_ptr_available_keys.erase(it);
    } else {
        key = static_const_sk_mesh_child_ptr_index++;
    }
    static_const_sk_mesh_child_ptr[key] = value;
    return key;
}

void static_const_sk_mesh_child_ptr_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_const_sk_mesh_child_ptr.erase(key);
    static_const_sk_mesh_child_ptr_available_keys.insert(key);
}

SkSpan<const SkMesh::ChildPtr> static_const_sk_mesh_child_ptr_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_const_sk_mesh_child_ptr[key];
}

void * static_const_sk_mesh_child_ptr_get_ptr(int key, int index) { // -> SkString *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return (void *)&static_const_sk_mesh_child_ptr[key][index];
}

void static_const_sk_mesh_child_ptr_set(int key, SkSpan<const SkMesh::ChildPtr> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_const_sk_mesh_child_ptr[key] = value;
}