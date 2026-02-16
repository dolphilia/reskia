//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_runtime_effect_result.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_runtime_effect_result-internal.h"

static reskia::static_registry::HandleTable<SkRuntimeEffect::Result> static_sk_runtime_effect_result;

int static_sk_runtime_effect_result_make(SkRuntimeEffect::Result value) {
    return static_sk_runtime_effect_result.create(std::move(value));
}

void static_sk_runtime_effect_result_set(int key, SkRuntimeEffect::Result value) {
    static_sk_runtime_effect_result.set(key, std::move(value));
}

SkRuntimeEffect::Result static_sk_runtime_effect_result_get_entity(int key) {
    SkRuntimeEffect::Result* entity = static_sk_runtime_effect_result.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_runtime_effect_result_delete(int key) {
    static_sk_runtime_effect_result.erase(key);
}

void * static_sk_runtime_effect_result_get_ptr(int key) { // -> SkRuntimeEffect::Result *
    return static_sk_runtime_effect_result.get_ptr(key);
}

}
