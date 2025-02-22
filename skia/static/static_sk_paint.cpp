//
// Created by dolphilia on 25/02/17.
//

#include "static_sk_paint.h"

#include "static_sk_paint-internal.h"

static std::set<int> static_sk_paint_available_keys;
static std::map<int, SkPaint> static_sk_paint;
static int static_sk_paint_index = 0;

int static_sk_paint_make(SkPaint value) {
    int key;
    if (!static_sk_paint_available_keys.empty()) {
        auto it = static_sk_paint_available_keys.begin();
        key = *it;
        static_sk_paint_available_keys.erase(it);
    } else {
        key = static_sk_paint_index++;
    }
    static_sk_paint[key] = value;
    return key;
}

void static_sk_paint_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_paint.erase(key);
    static_sk_paint_available_keys.insert(key);
}

SkPaint static_sk_paint_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_paint[key];
}

void static_sk_paint_set(int key, SkPaint value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_paint[key] = value;
}

void *static_sk_paint_get_ptr(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_paint[key];
}
