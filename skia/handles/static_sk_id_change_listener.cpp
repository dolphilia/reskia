//
// Created by dolphilia on 2024/01/12.
//

#include "static_sk_id_change_listener.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_id_change_listener-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkIDChangeListener>> static_sk_id_change_listener_table;

int static_sk_id_change_listener_make(sk_sp<SkIDChangeListener> value) {
    return static_sk_id_change_listener_table.create(std::move(value));
}

void static_sk_id_change_listener_set(int key, sk_sp<SkIDChangeListener> value) {
    static_sk_id_change_listener_table.set(key, std::move(value));
}

sk_sp<SkIDChangeListener> static_sk_id_change_listener_borrow_entity(int key) {
    sk_sp<SkIDChangeListener>* entity = static_sk_id_change_listener_table.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkIDChangeListener> static_sk_id_change_listener_take_entity(int key) {
    return static_sk_id_change_listener_table.take_or_default(key);
}

sk_sp<SkIDChangeListener> static_sk_id_change_listener_get_entity(int key) {
    return static_sk_id_change_listener_borrow_entity(key);
}

extern "C" {

void static_sk_id_change_listener_delete(int key) {
    static_sk_id_change_listener_table.erase(key);
}

void *static_sk_id_change_listener_get_ptr(int key) { // -> SkIDChangeListener *
    sk_sp<SkIDChangeListener>* entity = static_sk_id_change_listener_table.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
