//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_color_table.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_color_table-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkColorTable>> static_sk_color_table;

int static_sk_color_table_make(sk_sp<SkColorTable> value) {
    return static_sk_color_table.create(std::move(value));
}

void static_sk_color_table_set(int key, sk_sp<SkColorTable> value) {
    static_sk_color_table.set(key, std::move(value));
}

sk_sp<SkColorTable> static_sk_color_table_borrow_entity(int key) {
    sk_sp<SkColorTable>* entity = static_sk_color_table.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkColorTable> static_sk_color_table_take_entity(int key) {
    return static_sk_color_table.take_or_default(key);
}

sk_sp<SkColorTable> static_sk_color_table_get_entity(int key) {
    return static_sk_color_table_borrow_entity(key);
}

extern "C" {

void static_sk_color_table_delete(int key) {
    static_sk_color_table.erase(key);
}

void *static_sk_color_table_get_ptr(int key) { // -> SkColorTable *
    sk_sp<SkColorTable>* entity = static_sk_color_table.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
