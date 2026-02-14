//
// Created by dolphilia on 2024/01/13.
//

#include "static_sk_document.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_document-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkDocument>> static_sk_document;

int static_sk_document_make(sk_sp<SkDocument> value) {
    return static_sk_document.create(std::move(value));
}

void static_sk_document_set(int key, sk_sp<SkDocument> value) {
    static_sk_document.set(key, std::move(value));
}

sk_sp<SkDocument> static_sk_document_borrow_entity(int key) {
    sk_sp<SkDocument>* entity = static_sk_document.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkDocument> static_sk_document_take_entity(int key) {
    return static_sk_document.take_or_default(key);
}

sk_sp<SkDocument> static_sk_document_get_entity(int key) {
    return static_sk_document_borrow_entity(key);
}

extern "C" {

void static_sk_document_delete(int key) {
    static_sk_document.erase(key);
}

void *static_sk_document_get_ptr(int key) { // -> SkDocument *
    sk_sp<SkDocument>* entity = static_sk_document.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
