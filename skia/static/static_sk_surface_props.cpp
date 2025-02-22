//
// Created by dolphilia on 2024/01/06.
//

#include "static_sk_surface_props.h"
#include "static_sk_surface_props-internal.h"

static std::set<int> static_sk_surface_props_available_keys;
static std::map<int , SkSurfaceProps> static_sk_surface_props;
static int static_sk_surface_props_index = 0;

int static_sk_surface_props_make(SkSurfaceProps value) {
    int key;
    if (!static_sk_surface_props_available_keys.empty()) {
        auto it = static_sk_surface_props_available_keys.begin();
        key = *it;
        static_sk_surface_props_available_keys.erase(it);
    } else {
        key = static_sk_surface_props_index++;
    }
    static_sk_surface_props[key] = value;
    return key;
}

void static_sk_surface_props_delete(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_surface_props.erase(key);
    static_sk_surface_props_available_keys.insert(key);
}

SkSurfaceProps static_sk_surface_props_get(int key) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return static_sk_surface_props[key];
}

void * static_sk_surface_props_get_ptr(int key) { // -> SkSurfaceProps *
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    return &static_sk_surface_props[key];
}

void static_sk_surface_props_set(int key, SkSurfaceProps value) {
    if (key < 0) {
        throw std::runtime_error("Error in " + std::string(__func__) + " at " + std::string(__FILE__) + ":" + std::to_string(__LINE__) + " - Invalid key: " + std::to_string(key));
    }
    static_sk_surface_props[key] = value;
}
