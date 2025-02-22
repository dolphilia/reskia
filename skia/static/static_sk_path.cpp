//
// Created by dolphilia on 2024/01/09.
//

#include "static_sk_path.h"
#include "static_sk_path-internal.h"

static std::set<int> static_sk_path_available_keys;
static std::map<int , SkPath> static_sk_path;
static int static_sk_path_index = 0;

int static_sk_path_make(const SkPath& value) {
    int key;
    if (!static_sk_path_available_keys.empty()) {
        auto it = static_sk_path_available_keys.begin();
        key = *it;
        static_sk_path_available_keys.erase(it);
    } else {
        key = static_sk_path_index++;
    }
    static_sk_path[key] = value;
    return key;
}

void static_sk_path_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_path.erase(key);
    static_sk_path_available_keys.insert(key);
}

SkPath static_sk_path_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_path[key];
}

void * static_sk_path_get_ptr(int key) { // -> SkPath *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_path[key];
}

void static_sk_path_set(int key, const SkPath& value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_path[key] = value;
}
