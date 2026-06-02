//
// Created by dolphilia on 2026/06/02.
//

#include "static_sk_strike_ref.h"

#include <utility>

#include "handle_table.hpp"
#include "static_sk_strike_ref-internal.h"

static reskia::static_registry::HandleTable<SkStrikeRef> static_sk_strike_ref;

int static_sk_strike_ref_make(SkStrikeRef value) {
    return static_sk_strike_ref.create(std::move(value));
}

void static_sk_strike_ref_set(int key, SkStrikeRef value) {
    static_sk_strike_ref.set(key, std::move(value));
}

SkStrikeRef static_sk_strike_ref_get_entity(int key) {
    SkStrikeRef *entity = static_sk_strike_ref.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_strike_ref_delete(int key) {
    static_sk_strike_ref.erase(key);
}

void *static_sk_strike_ref_get_ptr(int key) { // -> SkStrikeRef *
    SkStrikeRef *entity = static_sk_strike_ref.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
