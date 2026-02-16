//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_capabilities.h"
#include "static_sk_capabilities-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<sk_sp<const SkCapabilities>> static_const_sk_capabilities;

int static_const_sk_capabilities_make(sk_sp<const SkCapabilities> value) {
    return static_const_sk_capabilities.create(std::move(value));
}

void static_const_sk_capabilities_set(int key, sk_sp<const SkCapabilities> value) {
    static_const_sk_capabilities.set(key, std::move(value));
}

sk_sp<const SkCapabilities> static_const_sk_capabilities_borrow_entity(int key) {
    sk_sp<const SkCapabilities>* entity = static_const_sk_capabilities.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<const SkCapabilities> static_const_sk_capabilities_take_entity(int key) {
    return static_const_sk_capabilities.take_or_default(key);
}

sk_sp<const SkCapabilities> static_const_sk_capabilities_get_entity(int key) {
    return static_const_sk_capabilities_borrow_entity(key);
}

extern "C" {

void static_const_sk_capabilities_delete(int key) {
    static_const_sk_capabilities.erase(key);
}

const void *static_const_sk_capabilities_get_ptr(int key) { // -> const SkCapabilities *
    sk_sp<const SkCapabilities>* entity = static_const_sk_capabilities.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
