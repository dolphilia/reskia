//
// Created by dolphilia on 2024/04/02.
//

#include "static_sk_flattenable_factory.h"
#include "static_sk_flattenable_factory-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkFlattenable::Factory> static_sk_flattenable_factory;

int static_sk_flattenable_factory_make(SkFlattenable::Factory value) {
    return static_sk_flattenable_factory.create(value);
}

SkFlattenable::Factory static_sk_flattenable_factory_get_entity(int key) {
    SkFlattenable::Factory* entity = static_sk_flattenable_factory.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_flattenable_factory_delete(int key) {
    static_sk_flattenable_factory.erase(key);
}

void * static_sk_flattenable_factory_get_ptr(int key) {
    SkFlattenable::Factory* entity = static_sk_flattenable_factory.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return (void *)*entity;
}

}
