//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_typeface.h"

#include <utility>
#include "static_sk_typeface-internal.h"

static std::set<int> static_sk_typeface_available_keys;
static std::map<int , sk_sp<SkTypeface>> static_sk_typeface;
static int static_sk_typeface_index = 0;

int static_sk_typeface_make(sk_sp<SkTypeface> value) {
    int key;
    if (!static_sk_typeface_available_keys.empty()) {
        auto it = static_sk_typeface_available_keys.begin();
        key = *it;
        static_sk_typeface_available_keys.erase(it);
    } else {
        key = static_sk_typeface_index++;
    }
    static_sk_typeface[key] = std::move(value);
    return key;
}

void static_sk_typeface_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_typeface[key].reset();
    static_sk_typeface.erase(key);
    static_sk_typeface_available_keys.insert(key);
}

void * static_sk_typeface_get(int key) { // -> SkTypeface *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_typeface[key].get();
}

void static_sk_typeface_set(int key, sk_sp<SkTypeface> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_typeface[key] = std::move(value);
}

sk_sp<SkTypeface> static_sk_typeface_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_typeface[key]);
}
