//
// Created by dolphilia on 2024/01/09.
//

#include "static_sk_blend_mode.h"
#include "static_sk_blend_mode-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<std::optional<SkBlendMode>> static_optional_sk_blend_mode;

int static_optional_sk_blend_mode_make(std::optional<SkBlendMode> value) {
    return static_optional_sk_blend_mode.create(value);
}

void static_optional_sk_blend_mode_set(int key, std::optional<SkBlendMode> value) {
    static_optional_sk_blend_mode.set(key, value);
}

std::optional<SkBlendMode> static_optional_sk_blend_mode_get_entity(int key) {
    std::optional<SkBlendMode>* entity = static_optional_sk_blend_mode.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_optional_sk_blend_mode_delete(int key) {
    static_optional_sk_blend_mode.erase(key);
}

int static_optional_sk_blend_mode_get_ptr(int key) { // // -> (int)SkBlendMode
    std::optional<SkBlendMode>* entity = static_optional_sk_blend_mode.get_ptr(key);
    if (entity == nullptr || !entity->has_value()) {
        return 0;
    }
    return static_cast<int>(**entity);
}

}
