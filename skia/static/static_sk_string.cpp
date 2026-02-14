//
// Created by dolphilia on 2024/01/10.
//

#include "static_sk_string.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_string-internal.h"

static reskia::static_registry::HandleTable<SkString> static_sk_string;
//
static reskia::static_registry::HandleTable<SkSpan<SkString>> static_sk_span_sk_string;

// SkString

int static_sk_string_make(SkString value) {
    return static_sk_string.create(std::move(value));
}

void static_sk_string_set(int key, SkString value) {
    static_sk_string.set(key, std::move(value));
}

SkString static_sk_string_get_entity(int key) {
    SkString* entity = static_sk_string.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_string_delete(int key) {
    static_sk_string.erase(key);
}

void * static_sk_string_get_ptr(int key) { // -> SkString *
    return static_sk_string.get_ptr(key);
}

}

// SkSpan<SkString>

int static_sk_span_sk_string_make(SkSpan<SkString> value) {
    return static_sk_span_sk_string.create(value);
}

void static_sk_span_sk_string_set(int key, SkSpan<SkString> value) {
    static_sk_span_sk_string.set(key, value);
}

SkSpan<SkString> static_sk_span_sk_string_get_entity(int key) {
    SkSpan<SkString>* entity = static_sk_span_sk_string.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_span_sk_string_delete(int key) {
    static_sk_span_sk_string.erase(key);
}

void * static_sk_span_sk_string_get_ptr(int key, int index) { // -> SkString *
    SkSpan<SkString>* entity = static_sk_span_sk_string.get_ptr(key);
    if (entity == nullptr || index < 0 || static_cast<size_t>(index) >= entity->size()) {
        return nullptr;
    }
    return &(*entity)[index];
}

}
