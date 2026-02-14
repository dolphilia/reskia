//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_stream_memory.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_stream_memory-internal.h"

static reskia::static_registry::HandleTable<std::unique_ptr<SkStreamMemory>> static_sk_stream_memory;

int static_sk_stream_memory_make(std::unique_ptr<SkStreamMemory> value) {
    return static_sk_stream_memory.create(std::move(value));
}

void static_sk_stream_memory_set(int key, std::unique_ptr<SkStreamMemory> value) {
    static_sk_stream_memory.set(key, std::move(value));
}

SkStreamMemory* static_sk_stream_memory_borrow_entity(int key) {
    std::unique_ptr<SkStreamMemory>* entity = static_sk_stream_memory.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkStreamMemory> static_sk_stream_memory_take_entity(int key) {
    return static_sk_stream_memory.take_or_default(key);
}

std::unique_ptr<SkStreamMemory> static_sk_stream_memory_get_entity(int key) {
    return static_sk_stream_memory_take_entity(key);
}

extern "C" {

void static_sk_stream_memory_delete(int key) {
    static_sk_stream_memory.erase(key);
}

void *static_sk_stream_memory_get_ptr(int key) { // -> SkStreamMemory *
    std::unique_ptr<SkStreamMemory>* entity = static_sk_stream_memory.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
