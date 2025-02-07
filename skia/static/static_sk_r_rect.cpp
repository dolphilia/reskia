//
// Created by dolphilia on 2024/01/10.
//

#include "static_sk_r_rect.h"
#include "static_sk_r_rect-internal.h"

static std::set<int> static_sk_r_rect_available_keys;
static std::map<int , SkRRect> static_sk_r_rect;
static int static_sk_r_rect_index = 0;

int static_sk_r_rect_make(SkRRect value) {
    int key;
    if (!static_sk_r_rect_available_keys.empty()) {
        auto it = static_sk_r_rect_available_keys.begin();
        key = *it;
        static_sk_r_rect_available_keys.erase(it);
    } else {
        key = static_sk_r_rect_index++;
    }
    static_sk_r_rect[key] = value;
    return key;
}

void static_sk_r_rect_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_r_rect.erase(key);
    static_sk_r_rect_available_keys.insert(key);
}

SkRRect static_sk_r_rect_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_r_rect[key];
}

void * static_sk_r_rect_get_ptr(int key) { // -> SkRRect *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_r_rect[key];
}

void static_sk_r_rect_set(int key, SkRRect value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_r_rect[key] = value;
}
