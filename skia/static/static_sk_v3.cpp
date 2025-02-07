//
// Created by dolphilia on 2024/04/04.
//

#include "static_sk_v3.h"
#include "static_sk_v3-internal.h"

static std::set<int> static_sk_v3_available_keys;
static std::map<int , SkV3> static_sk_v3;
static int static_sk_v3_index = 0;

int static_sk_v3_make(SkV3 value) {
    int key;
    if (!static_sk_v3_available_keys.empty()) {
        auto it = static_sk_v3_available_keys.begin();
        key = *it;
        static_sk_v3_available_keys.erase(it);
    } else {
        key = static_sk_v3_index++;
    }
    static_sk_v3[key] = value;
    return key;
}

void static_sk_v3_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_v3.erase(key);
    static_sk_v3_available_keys.insert(key);
}

SkV3 static_sk_v3_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_v3[key];
}

void * static_sk_v3_get_ptr(int key) { // -> SkV3 *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_v3[key];
}

void static_sk_v3_set(int key, SkV3 value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_v3[key] = value;
}
