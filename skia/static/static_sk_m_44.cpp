//
// Created by dolphilia on 2024/01/06.
//

#include "static_sk_m_44.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_m_44-internal.h"

static reskia::static_registry::HandleTable<SkM44> static_sk_m_44;

int static_sk_m_44_make(SkM44 value) {
    return static_sk_m_44.create(std::move(value));
}

void static_sk_m_44_set(int key, SkM44 value) {
    static_sk_m_44.set(key, std::move(value));
}

SkM44 static_sk_m_44_get_entity(int key) {
    SkM44* entity = static_sk_m_44.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_m_44_delete(int key) {
    static_sk_m_44.erase(key);
}

void * static_sk_m_44_get_ptr(int key) { // -> SkM44 *
    return static_sk_m_44.get_ptr(key);
}

}
