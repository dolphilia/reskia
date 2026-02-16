//
// Created by dolphilia on 2024/01/12.
//

#include "static_std_string_view.h"

#include "handle_table.hpp"
#include "static_std_string_view-internal.h"

static reskia::static_registry::HandleTable<std::string_view> static_string_view;

int static_string_view_make(std::string_view value) {
    return static_string_view.create(value);
}

void static_string_view_set(int key, std::string_view value) {
    static_string_view.set(key, value);
}

std::string_view static_string_view_get_entity(int key) {
    std::string_view* entity = static_string_view.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_string_view_delete(int key) {
    static_string_view.erase(key);
}

}
