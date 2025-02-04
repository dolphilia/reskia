//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_mesh_child_ptr.h"

#include <string>
#include <map>
#include "include/core/SkMesh.h"
#include "static_sk_mesh_child_ptr-internal.h"

static std::set<int> static_sk_mesh_available_keys;
static std::map<int , SkSpan<SkMesh::ChildPtr>> static_sk_mesh_child_ptr;
static int static_sk_mesh_index = 0;

static std::set<int> static_const_sk_mesh_available_keys;
static std::map<int , SkSpan<const SkMesh::ChildPtr>> static_const_sk_mesh_child_ptr;
static int static_const_sk_mesh_index = 0;

int static_sk_span_sk_mesh_make(SkSpan<SkMesh::ChildPtr> value) {
    int key;
    if (!static_sk_mesh_available_keys.empty()) {
        auto it = static_sk_mesh_available_keys.begin();
        key = *it;
        static_sk_mesh_available_keys.erase(it);
    } else {
        key = static_sk_mesh_index++;
    }
    static_sk_mesh_child_ptr[key] = value;
    return key;
}

void static_sk_span_sk_mesh_delete(int key) {
    static_sk_mesh_child_ptr.erase(key);
    static_sk_mesh_available_keys.insert(key);
}

SkSpan<SkMesh::ChildPtr> static_sk_span_sk_mesh_get(int key) {
    return static_sk_mesh_child_ptr[key];
}

void * static_sk_span_sk_mesh_get_ptr(int key, int index) { // -> SkString *
    return &static_sk_mesh_child_ptr[key][index];
}

void static_sk_span_sk_mesh_set(int key, SkSpan<SkMesh::ChildPtr> value) {
    static_sk_mesh_child_ptr[key] = value;
}

//

int static_sk_span_const_sk_mesh_make(SkSpan<const SkMesh::ChildPtr> value) {
    int key;
    if (!static_const_sk_mesh_available_keys.empty()) {
        auto it = static_const_sk_mesh_available_keys.begin();
        key = *it;
        static_const_sk_mesh_available_keys.erase(it);
    } else {
        key = static_const_sk_mesh_index++;
    }
    static_const_sk_mesh_child_ptr[key] = value;
    return key;
}

void static_sk_span_const_sk_mesh_delete(int key) {
    static_const_sk_mesh_child_ptr.erase(key);
    static_const_sk_mesh_available_keys.insert(key);
}

SkSpan<const SkMesh::ChildPtr> static_sk_span_const_sk_mesh_get(int key) {
    return static_const_sk_mesh_child_ptr[key];
}

void * static_sk_span_const_sk_mesh_get_ptr(int key, int index) { // -> SkString *
    return (void *)&static_const_sk_mesh_child_ptr[key][index];
}

void static_sk_span_const_sk_mesh_set(int key, SkSpan<const SkMesh::ChildPtr> value) {
    static_const_sk_mesh_child_ptr[key] = value;
}