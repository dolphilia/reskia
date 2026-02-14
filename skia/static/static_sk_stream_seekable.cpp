//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_stream_seekable.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_stream_seekable-internal.h"

static reskia::static_registry::HandleTable<std::unique_ptr<SkStreamSeekable>> static_sk_stream_seekable;

int static_sk_stream_seekable_make(std::unique_ptr<SkStreamSeekable> value) {
    return static_sk_stream_seekable.create(std::move(value));
}

void static_sk_stream_seekable_set(int key, std::unique_ptr<SkStreamSeekable> value) {
    static_sk_stream_seekable.set(key, std::move(value));
}

SkStreamSeekable* static_sk_stream_seekable_borrow_entity(int key) {
    std::unique_ptr<SkStreamSeekable>* entity = static_sk_stream_seekable.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkStreamSeekable> static_sk_stream_seekable_take_entity(int key) {
    return static_sk_stream_seekable.take_or_default(key);
}

std::unique_ptr<SkStreamSeekable> static_sk_stream_seekable_get_entity(int key) {
    return static_sk_stream_seekable_take_entity(key);
}

extern "C" {

void static_sk_stream_seekable_delete(int key) {
    static_sk_stream_seekable.erase(key);
}

void *static_sk_stream_seekable_get_ptr(int key) { // -> SkStreamSeekable *
    std::unique_ptr<SkStreamSeekable>* entity = static_sk_stream_seekable.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
