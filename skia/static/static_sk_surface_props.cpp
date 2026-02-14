//
// Created by dolphilia on 2024/01/06.
//

#include "static_sk_surface_props.h"
#include "handle_table.hpp"
#include "static_sk_surface_props-internal.h"

static reskia::static_registry::HandleTable<SkSurfaceProps> static_sk_surface_props;

int static_sk_surface_props_make(SkSurfaceProps value) {
    return static_sk_surface_props.create(value);
}

void static_sk_surface_props_set(int key, SkSurfaceProps value) {
    static_sk_surface_props.set(key, value);
}

SkSurfaceProps static_sk_surface_props_get_entity(int key) {
    SkSurfaceProps* entity = static_sk_surface_props.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_surface_props_delete(int key) {
    static_sk_surface_props.erase(key);
}

void * static_sk_surface_props_get_ptr(int key) { // -> SkSurfaceProps *
    return static_sk_surface_props.get_ptr(key);
}

}
