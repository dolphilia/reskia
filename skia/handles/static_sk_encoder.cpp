//
// Created by dolphilia on 2024/02/01.
//

#include "static_sk_encoder.h"
#include "static_sk_encoder-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<std::unique_ptr<SkEncoder>> static_sk_encoder;

int static_sk_encoder_make(std::unique_ptr<SkEncoder> value) {
    return static_sk_encoder.create(std::move(value));
}

void static_sk_encoder_set(int key, std::unique_ptr<SkEncoder> value) {
    static_sk_encoder.set(key, std::move(value));
}

SkEncoder* static_sk_encoder_borrow_entity(int key) {
    std::unique_ptr<SkEncoder>* entity = static_sk_encoder.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkEncoder> static_sk_encoder_take_entity(int key) {
    return static_sk_encoder.take_or_default(key);
}

std::unique_ptr<SkEncoder> static_sk_encoder_get_entity(int key) {
    return static_sk_encoder_take_entity(key);
}

extern "C" {

void static_sk_encoder_delete(int key) {
    static_sk_encoder.erase(key);
}

void *static_sk_encoder_get_ptr(int key) { // -> SkEncoder *
    std::unique_ptr<SkEncoder>* entity = static_sk_encoder.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
