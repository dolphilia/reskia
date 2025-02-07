//
// Created by dolphilia on 2024/04/04.
//

#include "static_sk_v2.h"
#include "static_sk_v2-internal.h"

static std::set<int> static_sk_v2_available_keys;
static std::map<int , SkV2> static_sk_v2;
static int static_sk_v2_index = 0;

int static_sk_v2_make(SkV2 value) {
    int key;
    if (!static_sk_v2_available_keys.empty()) {
        auto it = static_sk_v2_available_keys.begin();
        key = *it;
        static_sk_v2_available_keys.erase(it);
    } else {
        key = static_sk_v2_index++;
    }
    static_sk_v2[key] = value;
    return key;
}

void static_sk_v2_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_v2.erase(key);
    static_sk_v2_available_keys.insert(key);
}

SkV2 static_sk_v2_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_v2[key];
}

void * static_sk_v2_get_ptr(int key) { // -> SkV2 *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_v2[key];
}

void static_sk_v2_set(int key, SkV2 value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_v2[key] = value;
}
