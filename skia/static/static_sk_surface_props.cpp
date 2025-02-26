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

void static_sk_surface_props_set(int key, SkSurfaceProps value) {
    static_sk_surface_props[key] = value;
}

SkSurfaceProps static_sk_surface_props_get_entity(int key) {
    return static_sk_surface_props[key];
}

extern "C" {

void static_sk_surface_props_delete(int key) {
    static_sk_surface_props.erase(key);
    static_sk_surface_props_available_keys.insert(key);
}

void * static_sk_surface_props_get_ptr(int key) { // -> SkSurfaceProps *
    return &static_sk_surface_props[key];
}

}