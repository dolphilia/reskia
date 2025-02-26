//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_capabilities.h"
#include "static_sk_capabilities-internal.h"

static std::set<int> static_const_sk_capabilities_available_keys;
static std::map<int , sk_sp<const SkCapabilities>> static_const_sk_capabilities;
static int static_const_sk_capabilities_index = 0;

int static_const_sk_capabilities_make(sk_sp<const SkCapabilities> value) {
    int key;
    if (!static_const_sk_capabilities_available_keys.empty()) {
        auto it = static_const_sk_capabilities_available_keys.begin();
        key = *it;
        static_const_sk_capabilities_available_keys.erase(it);
    } else {
        key = static_const_sk_capabilities_index++;
    }
    static_const_sk_capabilities[key] = std::move(value);
    return key;
}

void static_const_sk_capabilities_set(int key, sk_sp<const SkCapabilities> value) {

    static_const_sk_capabilities[key] = std::move(value);
}

sk_sp<const SkCapabilities> static_const_sk_capabilities_get_entity(int key) {

    return std::move(static_const_sk_capabilities[key]);
}

extern "C" {

void static_const_sk_capabilities_delete(int key) {

    static_const_sk_capabilities[key].reset();
    static_const_sk_capabilities.erase(key);
    static_const_sk_capabilities_available_keys.insert(key);
}

const void *static_const_sk_capabilities_get_ptr(int key) { // -> const SkCapabilities *

    return static_const_sk_capabilities[key].get();
}

}