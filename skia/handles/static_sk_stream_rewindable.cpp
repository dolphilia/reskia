//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_stream_rewindable.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_stream_rewindable-internal.h"

static reskia::static_registry::HandleTable<std::unique_ptr<SkStreamRewindable>> static_sk_stream_rewindable;

int static_sk_stream_rewindable_make(std::unique_ptr<SkStreamRewindable> value) {
    return static_sk_stream_rewindable.create(std::move(value));
}

void static_sk_stream_rewindable_set(int key, std::unique_ptr<SkStreamRewindable> value) {
    static_sk_stream_rewindable.set(key, std::move(value));
}

SkStreamRewindable* static_sk_stream_rewindable_borrow_entity(int key) {
    std::unique_ptr<SkStreamRewindable>* entity = static_sk_stream_rewindable.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkStreamRewindable> static_sk_stream_rewindable_take_entity(int key) {
    return static_sk_stream_rewindable.take_or_default(key);
}

std::unique_ptr<SkStreamRewindable> static_sk_stream_rewindable_get_entity(int key) {
    return static_sk_stream_rewindable_take_entity(key);
}

extern "C" {

void static_sk_stream_rewindable_delete(int key) {
    static_sk_stream_rewindable.erase(key);
}

void *static_sk_stream_rewindable_get_ptr(int key) { // -> SkStreamRewindable *
    std::unique_ptr<SkStreamRewindable>* entity = static_sk_stream_rewindable.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
