//
// Created by dolphilia on 2024/01/12.
//

#include "static_std_function_void_void.h"

#include <utility>
#include "handle_table.hpp"
#include "static_std_function_void_void-internal.h"

static reskia::static_registry::HandleTable<std::function<void(void)>> static_function_void_void;

int static_function_void_void_make(std::function<void(void)> value) {
    return static_function_void_void.create(std::move(value));
}

void static_function_void_void_set(int key, std::function<void(void)> value) {
    static_function_void_void.set(key, std::move(value));
}

std::function<void(void)> static_function_void_void_get_entity(int key) {
    std::function<void(void)>* entity = static_function_void_void.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_function_void_void_delete(int key) {
    static_function_void_void.erase(key);
}

}
