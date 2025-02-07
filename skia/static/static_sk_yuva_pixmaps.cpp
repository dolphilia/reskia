//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_yuva_pixmaps.h"

#include <utility>
#include "static_sk_yuva_pixmaps-internal.h"

static std::set<int> static_sk_yuva_pixmaps_available_keys;
static std::map<int , SkYUVAPixmaps> static_sk_yuva_pixmaps;
static int static_sk_yuva_pixmaps_index = 0;

int static_sk_yuva_pixmaps_make(SkYUVAPixmaps value) {
    int key;
    if (!static_sk_yuva_pixmaps_available_keys.empty()) {
        auto it = static_sk_yuva_pixmaps_available_keys.begin();
        key = *it;
        static_sk_yuva_pixmaps_available_keys.erase(it);
    } else {
        key = static_sk_yuva_pixmaps_index++;
    }
    static_sk_yuva_pixmaps[key] = std::move(value);
    return key;
}

void static_sk_yuva_pixmaps_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_yuva_pixmaps.erase(key);
    static_sk_yuva_pixmaps_available_keys.insert(key);
}

SkYUVAPixmaps static_sk_yuva_pixmaps_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_yuva_pixmaps[key];
}

void * static_sk_yuva_pixmaps_get_ptr(int key) { // -> SkYUVAPixmaps *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_yuva_pixmaps[key];
}

void static_sk_yuva_pixmaps_set(int key, SkYUVAPixmaps value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_yuva_pixmaps[key] = std::move(value);
}
