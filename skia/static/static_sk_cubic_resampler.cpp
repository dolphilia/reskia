//
// Created by dolphilia on 2024/04/03.
//

#include "static_sk_cubic_resampler.h"
#include "static_sk_cubic_resampler-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<SkCubicResampler> static_sk_cubic_resampler;

int static_sk_cubic_resampler_make(SkCubicResampler value) {
    return static_sk_cubic_resampler.create(value);
}

SkCubicResampler static_sk_cubic_resampler_get_entity(int key) {
    SkCubicResampler* entity = static_sk_cubic_resampler.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_cubic_resampler_delete(int key) {
    static_sk_cubic_resampler.erase(key);
}

void * static_sk_cubic_resampler_get_ptr(int key) { // -> SkCubicResampler *
    SkCubicResampler* entity = static_sk_cubic_resampler.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity;
}

}
