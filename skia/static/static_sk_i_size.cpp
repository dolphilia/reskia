//
// Created by dolphilia on 2024/03/30.
//

#include "static_sk_i_size.h"
#include "static_sk_i_size-internal.h"

static std::set<int> static_sk_i_size_available_keys;
static std::map<int , SkISize> static_sk_i_size;
static int static_sk_i_size_index = 0;

int static_sk_i_size_make(SkISize value) {
    int key;
    if (!static_sk_i_size_available_keys.empty()) {
        auto it = static_sk_i_size_available_keys.begin();
        key = *it;
        static_sk_i_size_available_keys.erase(it);
    } else {
        key = static_sk_i_size_index++;
    }
    static_sk_i_size[key] = value;
    return key;
}

void static_sk_i_size_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_i_size.erase(key);
    static_sk_i_size_available_keys.insert(key);
}

SkISize static_sk_i_size_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_i_size[key];
}

void * static_sk_i_size_get_ptr(int key) { // -> SkISize *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_i_size[key];
}

void static_sk_i_size_set(int key, SkISize value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_i_size[key] = value;
}
