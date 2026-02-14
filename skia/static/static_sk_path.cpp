//
// Created by dolphilia on 2024/01/09.
//

#include "static_sk_path.h"
#include "handle_table.hpp"
#include "static_sk_path-internal.h"

static reskia::static_registry::HandleTable<SkPath> static_sk_path;

int static_sk_path_make(const SkPath& value) {
    return static_sk_path.create(value);
}

void static_sk_path_set(int key, const SkPath& value) {
    static_sk_path.set(key, value);
}

SkPath static_sk_path_get_entity(int key) {
    SkPath* entity = static_sk_path.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_path_delete(int key) {
    static_sk_path.erase(key);
}

void * static_sk_path_get_ptr(int key) { // -> SkPath *
    return static_sk_path.get_ptr(key);
}

}
