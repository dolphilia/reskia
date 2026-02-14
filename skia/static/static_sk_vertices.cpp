//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_vertices.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_vertices-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkVertices>> static_sk_vertices;

int static_sk_vertices_make(sk_sp<SkVertices> value) {
    return static_sk_vertices.create(std::move(value));
}

void static_sk_vertices_set(int key, sk_sp<SkVertices> value) {
    static_sk_vertices.set(key, std::move(value));
}

sk_sp<SkVertices> static_sk_vertices_borrow_entity(int key) {
    sk_sp<SkVertices>* entity = static_sk_vertices.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkVertices> static_sk_vertices_take_entity(int key) {
    return static_sk_vertices.take_or_default(key);
}

sk_sp<SkVertices> static_sk_vertices_get_entity(int key) {
    return static_sk_vertices_borrow_entity(key);
}

extern "C" {

void static_sk_vertices_delete(int key) {
    static_sk_vertices.erase(key);
}

void * static_sk_vertices_get_ptr(int key) { // -> SkVertices *
    sk_sp<SkVertices>* entity = static_sk_vertices.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
