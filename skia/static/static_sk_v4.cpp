//
// Created by dolphilia on 2024/04/04.
//

#include "static_sk_v4.h"
#include "static_sk_v4-internal.h"

static std::set<int> static_sk_v4_available_keys;
static std::map<int , SkV4> static_sk_v4;
static int static_sk_v4_index = 0;

int static_sk_v4_make(SkV4 value) {
    int key;
    if (!static_sk_v4_available_keys.empty()) {
        auto it = static_sk_v4_available_keys.begin();
        key = *it;
        static_sk_v4_available_keys.erase(it);
    } else {
        key = static_sk_v4_index++;
    }
    static_sk_v4[key] = value;
    return key;
}

void static_sk_v4_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_v4.erase(key);
    static_sk_v4_available_keys.insert(key);
}

SkV4 static_sk_v4_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_v4[key];
}

void * static_sk_v4_get_ptr(int key) { // -> SkV4 *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_v4[key];
}

void static_sk_v4_set(int key, SkV4 value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_v4[key] = value;
}
