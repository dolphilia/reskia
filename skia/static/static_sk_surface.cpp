//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_surface.h"

#include <utility>
#include "static_sk_surface-internal.h"

static std::set<int> static_sk_surface_available_keys;
static std::map<int , sk_sp<SkSurface>> static_sk_surface;
static int static_sk_surface_index = 0;

int static_sk_surface_make(sk_sp<SkSurface> value) {
    int key;
    if (!static_sk_surface_available_keys.empty()) {
        auto it = static_sk_surface_available_keys.begin();
        key = *it;
        static_sk_surface_available_keys.erase(it);
    } else {
        key = static_sk_surface_index++;
    }
    static_sk_surface[key] = std::move(value);
    return key;
}

void static_sk_surface_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_surface[key].reset();
    static_sk_surface.erase(key);
    static_sk_surface_available_keys.insert(key);
}

void * static_sk_surface_get(int key) { // -> SkSurface *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_surface[key].get();
}

void static_sk_surface_set(int key, sk_sp<SkSurface> value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_surface[key] = std::move(value);
}

sk_sp<SkSurface> static_sk_surface_move(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return std::move(static_sk_surface[key]);
}
