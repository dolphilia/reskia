//
// Created by dolphilia on 2024/04/02.
//

#include "static_sk_flattenable_factory.h"
#include "static_sk_flattenable_factory-internal.h"

static std::set<int> static_sk_flattenable_factory_available_keys;
static std::map<int , SkFlattenable::Factory> static_sk_flattenable_factory;
static int static_sk_flattenable_factory_index = 0;

int static_sk_flattenable_factory_make(SkFlattenable::Factory value) {
    int key;
    if (!static_sk_flattenable_factory_available_keys.empty()) {
        auto it = static_sk_flattenable_factory_available_keys.begin();
        key = *it;
        static_sk_flattenable_factory_available_keys.erase(it);
    } else {
        key = static_sk_flattenable_factory_index++;
    }
    static_sk_flattenable_factory[key] = value;
    return key;
}

SkFlattenable::Factory static_sk_flattenable_factory_get_entity(int key) {
    return static_sk_flattenable_factory[key];
}

extern "C" {

void static_sk_flattenable_factory_delete(int key) {
    static_sk_flattenable_factory.erase(key);
    static_sk_flattenable_factory_available_keys.insert(key);
}

void * static_sk_flattenable_factory_get_ptr(int key) {
    return (void *)static_sk_flattenable_factory[key];
}

}