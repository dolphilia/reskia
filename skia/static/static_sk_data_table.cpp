//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_data_table.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_data_table-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkDataTable>> static_sk_data_table;

int static_sk_data_table_make(sk_sp<SkDataTable> value) {
    return static_sk_data_table.create(std::move(value));
}

void static_sk_data_table_set(int key, sk_sp<SkDataTable> value) {
    static_sk_data_table.set(key, std::move(value));
}

sk_sp<SkDataTable> static_sk_data_table_borrow_entity(int key) {
    sk_sp<SkDataTable>* entity = static_sk_data_table.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkDataTable> static_sk_data_table_take_entity(int key) {
    return static_sk_data_table.take_or_default(key);
}

sk_sp<SkDataTable> static_sk_data_table_get_entity(int key) {
    return static_sk_data_table_borrow_entity(key);
}

extern "C" {

void static_sk_data_table_delete(int key) {
    static_sk_data_table.erase(key);
}

void *static_sk_data_table_get_ptr(int key) { // -> SkDataTable *
    sk_sp<SkDataTable>* entity = static_sk_data_table.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
