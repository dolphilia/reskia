//
// Created by dolphilia on 2024/02/01.
//

#include "static_sk_encoder_frame.h"
#include "static_sk_encoder_frame-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkSpan<const SkEncoder::Frame>> static_const_sk_encoder_frame;

int static_const_sk_encoder_frame_make(SkSpan<const SkEncoder::Frame> value) {
    return static_const_sk_encoder_frame.create(value);
}

void static_const_encoder_frame_set(int key, SkSpan<const SkEncoder::Frame> value) {
    static_const_sk_encoder_frame.set(key, value);
}

SkSpan<const SkEncoder::Frame> static_const_sk_encoder_frame_get_entity(int key) {
    SkSpan<const SkEncoder::Frame>* entity = static_const_sk_encoder_frame.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_const_sk_encoder_frame_delete(int key) {
    static_const_sk_encoder_frame.erase(key);
}

const void * static_const_sk_encoder_frame_get_ptr(int key, int index) { // -> const SkEncoder::Frame *
    SkSpan<const SkEncoder::Frame>* entity = static_const_sk_encoder_frame.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return nullptr;
    }
    return &(*entity)[index];
}

}
