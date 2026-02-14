//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_stream.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_stream-internal.h"

static reskia::static_registry::HandleTable<std::unique_ptr<SkStream>> static_sk_stream;

// static_sk_stream

int static_sk_stream_make(std::unique_ptr<SkStream> value) {
    return static_sk_stream.create(std::move(value));
}

void static_sk_stream_set(int key, std::unique_ptr<SkStream> value) {
    static_sk_stream.set(key, std::move(value));
}

SkStream* static_sk_stream_borrow_entity(int key) {
    std::unique_ptr<SkStream>* entity = static_sk_stream.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkStream> static_sk_stream_take_entity(int key) {
    return static_sk_stream.take_or_default(key);
}

std::unique_ptr<SkStream> static_sk_stream_get_entity(int key) {
    return static_sk_stream_take_entity(key);
}

extern "C" {

void static_sk_stream_delete(int key) {
    static_sk_stream.erase(key);
}

void *static_sk_stream_get_ptr(int key) { // -> SkStream *
    std::unique_ptr<SkStream>* entity = static_sk_stream.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}

// static_sk_stream_ptr

static reskia::static_registry::HandleTable<std::unique_ptr<SkStream>*> static_sk_stream_ptr;

int static_sk_stream_ptr_make(std::unique_ptr<SkStream>* value) {
    return static_sk_stream_ptr.create(value);
}

void static_sk_stream_ptr_set(int key, std::unique_ptr<SkStream>* value) {
    static_sk_stream_ptr.set(key, value);
}

std::unique_ptr<SkStream>* static_sk_stream_ptr_get_entity(int key) {
    return static_sk_stream_ptr.take_or_default(key);
}

extern "C" {

void static_sk_stream_ptr_delete(int key) {
    static_sk_stream_ptr.erase(key);
}

void* static_sk_stream_ptr_get_ptr(int key) { // -> SkStream*
    std::unique_ptr<SkStream>** entity = static_sk_stream_ptr.get_ptr(key);
    if (entity == nullptr || *entity == nullptr) {
        return nullptr;
    }
    return (*entity)->get();
}

}
