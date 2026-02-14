//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_file_stream.h"
#include "static_sk_file_stream-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<std::unique_ptr<SkFILEStream>> static_sk_file_stream;

int static_sk_file_stream_make(std::unique_ptr<SkFILEStream> value) {
    return static_sk_file_stream.create(std::move(value));
}

void static_sk_file_stream_set(int key, std::unique_ptr<SkFILEStream> value) {
    static_sk_file_stream.set(key, std::move(value));
}

SkFILEStream* static_sk_file_stream_borrow_entity(int key) {
    std::unique_ptr<SkFILEStream>* entity = static_sk_file_stream.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkFILEStream> static_sk_file_stream_take_entity(int key) {
    return static_sk_file_stream.take_or_default(key);
}

std::unique_ptr<SkFILEStream> static_sk_file_stream_get_entity(int key) {
    return static_sk_file_stream_take_entity(key);
}

extern "C" {

void static_sk_file_stream_delete(int key) {
    static_sk_file_stream.erase(key);
}

void *static_sk_file_stream_get_ptr(int key) { // -> SkFILEStream *
    std::unique_ptr<SkFILEStream>* entity = static_sk_file_stream.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
