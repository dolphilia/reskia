//
// Created by dolphilia on 2024/01/11.
//

#include "static_std_tuple_int_int.h"
#include "handle_table.hpp"
#include "static_std_tuple_int_int-internal.h"

static reskia::static_registry::HandleTable<std::tuple<int, int>> static_tuple_int_int;

int static_tuple_int_int_make(std::tuple<int, int> value) {
    return static_tuple_int_int.create(value);
}

void static_tuple_int_int_set(int key, std::tuple<int, int> value) {
    static_tuple_int_int.set(key, value);
}

std::tuple<int, int> static_tuple_int_int_get_entity(int key) {
    std::tuple<int, int>* entity = static_tuple_int_int.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_tuple_int_int_delete(int key) {
    static_tuple_int_int.erase(key);
}

}
