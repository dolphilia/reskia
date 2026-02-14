//
// Created by dolphilia on 2024/04/01.
//

#include "static_std_chrono_milliseconds.h"
#include "handle_table.hpp"
#include "static_std_chrono_milliseconds-internal.h"

static reskia::static_registry::HandleTable<std::chrono::milliseconds> static_chrono_milliseconds;

int static_chrono_milliseconds_make(std::chrono::milliseconds value) {
    return static_chrono_milliseconds.create(value);
}

void static_chrono_milliseconds_set(int key, std::chrono::milliseconds value) {
    static_chrono_milliseconds.set(key, value);
}

std::chrono::milliseconds static_chrono_milliseconds_get_entity(int key) {
    std::chrono::milliseconds* entity = static_chrono_milliseconds.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_chrono_milliseconds_delete(int key) {
    static_chrono_milliseconds.erase(key);
}

}
