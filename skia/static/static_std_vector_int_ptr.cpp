//
// Created by dolphilia on 25/01/12.
//

#include "static_std_vector_int_ptr.h"
#include "handle_table.hpp"
#include "static_std_vector_int_ptr-internal.h"

static reskia::static_registry::HandleTable<std::vector<int>*> static_int_vector_ptr_map;

int static_int_vector_ptr_make(std::vector<int>* value) {
    return static_int_vector_ptr_map.create(value);
}

void static_int_vector_ptr_set(int key, std::vector<int>* value) {
    static_int_vector_ptr_map.set(key, value);
}

std::vector<int>* static_int_vector_ptr_get_entity(int key) {
    return static_int_vector_ptr_map.take_or_default(key);
}

extern "C" {

void static_int_vector_ptr_delete(int key) {
    static_int_vector_ptr_map.erase(key);
}

void* static_int_vector_ptr_get_ptr(int key) {
    std::vector<int>** entity = static_int_vector_ptr_map.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return *entity;
}

}
