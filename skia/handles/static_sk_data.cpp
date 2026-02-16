//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_data.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_data-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkData>> static_sk_data;
static reskia::static_registry::HandleTable<sk_sp<const SkData>> static_const_sk_data;

int static_sk_data_make(sk_sp<SkData> value) {
    return static_sk_data.create(std::move(value));
}

void static_sk_data_set(int key, sk_sp<SkData> value) {
    static_sk_data.set(key, std::move(value));
}

sk_sp<SkData> static_sk_data_borrow_entity(int key) {
    sk_sp<SkData>* entity = static_sk_data.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkData> static_sk_data_take_entity(int key) {
    return static_sk_data.take_or_default(key);
}

sk_sp<SkData> static_sk_data_get_entity(int key) {
    return static_sk_data_borrow_entity(key);
}

extern "C" {

void static_sk_data_delete(int key) {
    static_sk_data.erase(key);
}

void *static_sk_data_get_ptr(int key) { // -> SkData *
    sk_sp<SkData>* entity = static_sk_data.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}

// const

int static_const_sk_data_make(sk_sp<const SkData> value) {
    return static_const_sk_data.create(std::move(value));
}

void static_const_sk_data_set(int key, sk_sp<const SkData> value) {
    static_const_sk_data.set(key, std::move(value));
}

sk_sp<const SkData> static_const_sk_data_borrow_entity(int key) {
    sk_sp<const SkData>* entity = static_const_sk_data.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<const SkData> static_const_sk_data_take_entity(int key) {
    return static_const_sk_data.take_or_default(key);
}

sk_sp<const SkData> static_const_sk_data_get_entity(int key) {
    return static_const_sk_data_borrow_entity(key);
}

extern "C" {

void static_const_sk_data_delete(int key) {
    static_const_sk_data.erase(key);
}

const void *static_const_sk_data_get_ptr(int key) { // -> const SkData *
    sk_sp<const SkData>* entity = static_const_sk_data.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
