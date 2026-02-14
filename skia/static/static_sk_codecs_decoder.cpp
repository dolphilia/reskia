//
// Created by dolphilia on 2024/02/02.
//

#include "static_sk_codecs_decoder.h"
#include "static_sk_codecs_decoder-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkCodecs::Decoder> static_sk_codecs_decoder;

int static_sk_codecs_decoder_make(SkCodecs::Decoder value) {
    return static_sk_codecs_decoder.create(std::move(value));
}

void static_sk_codecs_decoder_set(int key, SkCodecs::Decoder value) {
    static_sk_codecs_decoder.set(key, std::move(value));
}

SkCodecs::Decoder static_sk_codecs_decoder_get_entity(int key) {
    SkCodecs::Decoder* entity = static_sk_codecs_decoder.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_codecs_decoder_delete(int key) {
    static_sk_codecs_decoder.erase(key);
}

void * static_sk_codecs_decoder_get_ptr(int key) { // -> SkCodecs::Decoder *
    SkCodecs::Decoder* entity = static_sk_codecs_decoder.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
