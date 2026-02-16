//
// Created by dolphilia on 2024/02/02.
//

#include "static_sk_codec.h"
#include "static_sk_codec-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<std::unique_ptr<SkCodec>> static_sk_codec;

int static_sk_codec_make(std::unique_ptr<SkCodec> value) {
    return static_sk_codec.create(std::move(value));
}

void static_sk_codec_set(int key, std::unique_ptr<SkCodec> value) {
    static_sk_codec.set(key, std::move(value));
}

SkCodec* static_sk_codec_borrow_entity(int key) {
    std::unique_ptr<SkCodec>* entity = static_sk_codec.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkCodec> static_sk_codec_take_entity(int key) {
    return static_sk_codec.take_or_default(key);
}

std::unique_ptr<SkCodec> static_sk_codec_get_entity(int key) {
    return static_sk_codec_take_entity(key);
}

extern "C" {

void static_sk_codec_delete(int key) {
    static_sk_codec.erase(key);
}

void *static_sk_codec_get_ptr(int key) { // -> SkCodec *
    std::unique_ptr<SkCodec>* entity = static_sk_codec.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
