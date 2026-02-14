//
// Created by dolphilia on 2024/01/12.
//

#include "static_sk_b_box_hierarchy.h"
#include "static_sk_b_box_hierarchy-internal.h"

#include "handle_table.hpp"

static reskia::static_registry::HandleTable<sk_sp<SkBBoxHierarchy>> static_sk_b_box_hierarchy;

int static_sk_b_box_hierarchy_make(sk_sp<SkBBoxHierarchy> value) {
    return static_sk_b_box_hierarchy.create(std::move(value));
}

void static_sk_b_box_hierarchy_set(int key, sk_sp<SkBBoxHierarchy> value) {
    static_sk_b_box_hierarchy.set(key, std::move(value));
}

sk_sp<SkBBoxHierarchy> static_sk_b_box_hierarchy_borrow_entity(int key) {
    sk_sp<SkBBoxHierarchy>* entity = static_sk_b_box_hierarchy.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkBBoxHierarchy> static_sk_b_box_hierarchy_take_entity(int key) {
    return static_sk_b_box_hierarchy.take_or_default(key);
}

sk_sp<SkBBoxHierarchy> static_sk_b_box_hierarchy_get_entity(int key) {
    return static_sk_b_box_hierarchy_borrow_entity(key);
}

extern "C" {

void static_sk_b_box_hierarchy_delete(int key) {
    static_sk_b_box_hierarchy.erase(key);
}

void *static_sk_b_box_hierarchy_get_ptr(int key) { // -> SkBBoxHierarchy
    sk_sp<SkBBoxHierarchy>* entity = static_sk_b_box_hierarchy.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
