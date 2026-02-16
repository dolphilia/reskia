//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_memory_stream.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_memory_stream-internal.h"

static reskia::static_registry::HandleTable<std::unique_ptr<SkMemoryStream>> static_sk_memory_stream;

int static_sk_memory_stream_make(std::unique_ptr<SkMemoryStream> value) {
    return static_sk_memory_stream.create(std::move(value));
}

void static_sk_memory_stream_set(int key, std::unique_ptr<SkMemoryStream> value) {
    static_sk_memory_stream.set(key, std::move(value));
}

SkMemoryStream* static_sk_memory_stream_borrow_entity(int key) {
    std::unique_ptr<SkMemoryStream>* entity = static_sk_memory_stream.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkMemoryStream> static_sk_memory_stream_take_entity(int key) {
    return static_sk_memory_stream.take_or_default(key);
}

std::unique_ptr<SkMemoryStream> static_sk_memory_stream_get_entity(int key) {
    return static_sk_memory_stream_take_entity(key);
}

extern "C" {

void static_sk_memory_stream_delete(int key) {
    static_sk_memory_stream.erase(key);
}

void *static_sk_memory_stream_get_ptr(int key) { // -> SkMemoryStream *
    std::unique_ptr<SkMemoryStream>* entity = static_sk_memory_stream.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
