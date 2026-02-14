//
// Created by dolphilia on 2024/02/02.
//

#include "static_sk_android_codec.h"
#include "static_sk_android_codec-internal.h"

#include "handle_table.hpp"

static reskia::static_registry::HandleTable<std::unique_ptr<SkAndroidCodec>> static_sk_android_codec;

int static_sk_android_codec_make(std::unique_ptr<SkAndroidCodec> value) {
    return static_sk_android_codec.create(std::move(value));
}

void static_sk_android_codec_set(int key, std::unique_ptr<SkAndroidCodec> value) {
    static_sk_android_codec.set(key, std::move(value));
}

SkAndroidCodec* static_sk_android_codec_borrow_entity(int key) {
    std::unique_ptr<SkAndroidCodec>* entity = static_sk_android_codec.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkAndroidCodec> static_sk_android_codec_take_entity(int key) {
    return static_sk_android_codec.take_or_default(key);
}

std::unique_ptr<SkAndroidCodec> static_sk_android_codec_get_entity(int key) {
    return static_sk_android_codec_take_entity(key);
}

extern "C" {

void static_sk_android_codec_delete(int key) {
    static_sk_android_codec.erase(key);
}

void *static_sk_android_codec_get_ptr(int key) {
    std::unique_ptr<SkAndroidCodec>* entity = static_sk_android_codec.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
