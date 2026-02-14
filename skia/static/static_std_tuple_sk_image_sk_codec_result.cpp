//
// Created by dolphilia on 2024/02/02.
//

#include "static_std_tuple_sk_image_sk_codec_result.h"

#include <utility>
#include "handle_table.hpp"
#include "static_std_tuple_sk_image_sk_codec_result-internal.h"

static reskia::static_registry::HandleTable<std::tuple<sk_sp<SkImage>, SkCodec::Result>>
    static_tuple_sk_image_sk_codec_result;

int static_tuple_sk_image_sk_codec_result_make(std::tuple<sk_sp<SkImage>, SkCodec::Result> value) {
    return static_tuple_sk_image_sk_codec_result.create(std::move(value));
}

void static_tuple_sk_image_sk_codec_result_set(int key, std::tuple<sk_sp<SkImage>, SkCodec::Result> value) {
    static_tuple_sk_image_sk_codec_result.set(key, std::move(value));
}

std::tuple<sk_sp<SkImage>, SkCodec::Result> static_tuple_sk_image_sk_codec_result_get_entity(int key) {
    std::tuple<sk_sp<SkImage>, SkCodec::Result>* entity = static_tuple_sk_image_sk_codec_result.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_tuple_sk_image_sk_codec_result_delete(int key) {
    static_tuple_sk_image_sk_codec_result.erase(key);
}

}
