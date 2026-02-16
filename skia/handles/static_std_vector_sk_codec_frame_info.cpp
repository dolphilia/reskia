//
// Created by dolphilia on 2024/02/02.
//

#include "static_std_vector_sk_codec_frame_info.h"

#include <utility>
#include "handle_table.hpp"
#include "static_std_vector_sk_codec_frame_info-internal.h"

static reskia::static_registry::HandleTable<std::vector<SkCodec::FrameInfo>> static_vector_sk_codec_frame_into;

int static_vector_sk_codec_frame_info_make(std::vector<SkCodec::FrameInfo> value) {
    return static_vector_sk_codec_frame_into.create(std::move(value));
}

void static_vector_sk_codec_frame_info_set(int key, std::vector<SkCodec::FrameInfo> value) {
    static_vector_sk_codec_frame_into.set(key, std::move(value));
}

SkCodec::FrameInfo static_vector_sk_codec_frame_info_get_entity(int key, int index) {
    std::vector<SkCodec::FrameInfo>* entity = static_vector_sk_codec_frame_into.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return {};
    }
    return (*entity)[index];
}

void static_vector_sk_codec_frame_info_push_back(int key, SkCodec::FrameInfo value) {
    std::vector<SkCodec::FrameInfo>* entity = static_vector_sk_codec_frame_into.get_ptr(key);
    if (entity == nullptr) {
        return;
    }
    entity->push_back(value);
}

void static_vector_sk_codec_frame_info_insert(int key, int index, SkCodec::FrameInfo value) {
    std::vector<SkCodec::FrameInfo>* entity = static_vector_sk_codec_frame_into.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) > entity->size()) {
        return;
    }
    entity->insert(entity->begin() + index, value);
}

extern "C" {

void static_vector_sk_codec_frame_info_delete(int key) {
    static_vector_sk_codec_frame_into.erase(key);
}

void static_vector_sk_codec_frame_info_pop_back(int key) {
    std::vector<SkCodec::FrameInfo>* entity = static_vector_sk_codec_frame_into.get_ptr(key);
    if (entity == nullptr || entity->empty()) {
        return;
    }
    entity->pop_back();
}

void static_vector_sk_codec_frame_info_erase(int key, int index) {
    std::vector<SkCodec::FrameInfo>* entity = static_vector_sk_codec_frame_into.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return;
    }
    entity->erase(entity->begin() + index);
}

}
