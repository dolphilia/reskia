//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_mesh_child_ptr.h"

#include <string>
#include "handle_table.hpp"
#include "include/core/SkMesh.h"
#include "static_sk_mesh_child_ptr-internal.h"

static reskia::static_registry::HandleTable<SkSpan<SkMesh::ChildPtr>> static_sk_mesh_child_ptr;

static reskia::static_registry::HandleTable<SkSpan<const SkMesh::ChildPtr>> static_const_sk_mesh_child_ptr;

int static_sk_mesh_child_ptr_make(SkSpan<SkMesh::ChildPtr> value) {
    return static_sk_mesh_child_ptr.create(value);
}

void static_sk_mesh_child_ptr_set(int key, SkSpan<SkMesh::ChildPtr> value) {
    static_sk_mesh_child_ptr.set(key, value);
}

SkSpan<SkMesh::ChildPtr> static_sk_mesh_child_ptr_get_entity(int key) {
    SkSpan<SkMesh::ChildPtr>* entity = static_sk_mesh_child_ptr.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_mesh_child_ptr_delete(int key) {
    static_sk_mesh_child_ptr.erase(key);
}

void * static_sk_mesh_child_ptr_get_ptr(int key, int index) { // -> SkString *
    SkSpan<SkMesh::ChildPtr>* entity = static_sk_mesh_child_ptr.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return nullptr;
    }
    return &(*entity)[index];
}

}

// const

int static_const_sk_mesh_child_ptr_make(SkSpan<const SkMesh::ChildPtr> value) {
    return static_const_sk_mesh_child_ptr.create(value);
}

void static_const_sk_mesh_child_ptr_set(int key, SkSpan<const SkMesh::ChildPtr> value) {
    static_const_sk_mesh_child_ptr.set(key, value);
}

SkSpan<const SkMesh::ChildPtr> static_const_sk_mesh_child_ptr_get_entity(int key) {
    SkSpan<const SkMesh::ChildPtr>* entity = static_const_sk_mesh_child_ptr.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_const_sk_mesh_child_ptr_delete(int key) {
    static_const_sk_mesh_child_ptr.erase(key);
}

void * static_const_sk_mesh_child_ptr_get_ptr(int key, int index) { // -> SkString *
    SkSpan<const SkMesh::ChildPtr>* entity = static_const_sk_mesh_child_ptr.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return nullptr;
    }
    return const_cast<SkMesh::ChildPtr*>(&(*entity)[index]);
}

}
