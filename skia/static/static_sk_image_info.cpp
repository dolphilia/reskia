//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_image_info.h"

#include <utility>
#include "static_sk_image_info-internal.h"

static std::set<int> static_sk_image_info_available_keys;
static std::map<int , SkImageInfo> static_sk_image_info;
static int static_sk_image_info_index = 0;

int static_sk_image_info_make(SkImageInfo value) {
    int key;
    if (!static_sk_image_info_available_keys.empty()) {
        auto it = static_sk_image_info_available_keys.begin();
        key = *it;
        static_sk_image_info_available_keys.erase(it);
    } else {
        key = static_sk_image_info_index++;
    }
    static_sk_image_info[key] = std::move(value);
    return key;
}

void static_sk_image_info_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_image_info.erase(key);
    static_sk_image_info_available_keys.insert(key);
}

SkImageInfo static_sk_image_info_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_image_info[key];
}

void * static_sk_image_info_get_ptr(int key) { // -> SkImageInfo *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_image_info[key];
}

void static_sk_image_info_set(int key, SkImageInfo value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_image_info[key] = std::move(value);
}
