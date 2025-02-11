//
// Created by dolphilia on 2024/03/30.
//

#include "static_sk_point.h"
#include "static_sk_point-internal.h"

static std::set<int> static_sk_point_available_keys;
static std::map<int , SkPoint> static_sk_point;
static int static_sk_point_index = 0;

int static_sk_point_make(SkPoint value) {
    int key;
    if (!static_sk_point_available_keys.empty()) {
        auto it = static_sk_point_available_keys.begin();
        key = *it;
        static_sk_point_available_keys.erase(it);
    } else {
        key = static_sk_point_index++;
    }
    static_sk_point[key] = value;
    return key;
}

void static_sk_point_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_point.erase(key);
    static_sk_point_available_keys.insert(key);
}

SkPoint static_sk_point_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_point[key];
}

void * static_sk_point_get_ptr(int key) { // -> SkPoint *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_point[key];
}

void static_sk_point_set(int key, SkPoint value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_point[key] = value;
}
