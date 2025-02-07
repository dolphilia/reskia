//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_color_space.h"

#include <utility>
#include "static_sk_color_space-internal.h"

static std::set<int> static_sk_color_space_available_keys;
static std::map<int , sk_sp<SkColorSpace>> static_sk_color_space;
static int static_sk_color_space_index = 0;

int static_sk_color_space_make(sk_sp<SkColorSpace> value) {
    int key;
    if (!static_sk_color_space_available_keys.empty()) {
        auto it = static_sk_color_space_available_keys.begin();
        key = *it;
        static_sk_color_space_available_keys.erase(it);
    } else {
        key = static_sk_color_space_index++;
    }
    static_sk_color_space[key] = std::move(value);
    return key;
}

void static_sk_color_space_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_color_space[key].reset();
    static_sk_color_space.erase(key);
    static_sk_color_space_available_keys.insert(key);
}

void *static_sk_color_space_get(int key) { // -> SkColorSpace *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_color_space[key].get();
}

void static_sk_color_space_set(int key, sk_sp<SkColorSpace> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_color_space[key] = std::move(value);
}

sk_sp<SkColorSpace> static_sk_color_space_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_color_space[key]);
}
