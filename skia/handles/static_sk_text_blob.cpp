//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_text_blob.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_text_blob-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkTextBlob>> static_sk_text_blob;

int static_sk_text_blob_make(sk_sp<SkTextBlob> value) {
    return static_sk_text_blob.create(std::move(value));
}

void static_sk_text_blob_set(int key, sk_sp<SkTextBlob> value) {
    static_sk_text_blob.set(key, std::move(value));
}

sk_sp<SkTextBlob> static_sk_text_blob_borrow_entity(int key) {
    sk_sp<SkTextBlob>* entity = static_sk_text_blob.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkTextBlob> static_sk_text_blob_take_entity(int key) {
    return static_sk_text_blob.take_or_default(key);
}

sk_sp<SkTextBlob> static_sk_text_blob_get_entity(int key) {
    return static_sk_text_blob_borrow_entity(key);
}

extern "C" {

void static_sk_text_blob_delete(int key) {
    static_sk_text_blob.erase(key);
}

void * static_sk_text_blob_get_ptr(int key) { // -> SkTextBlob *
    sk_sp<SkTextBlob>* entity = static_sk_text_blob.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
