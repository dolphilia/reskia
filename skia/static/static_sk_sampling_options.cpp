//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_sampling_options.h"
#include "handle_table.hpp"
#include "static_sk_sampling_options-internal.h"

static reskia::static_registry::HandleTable<SkSamplingOptions> static_sk_sampling_options;

int static_sk_sampling_options_make(SkSamplingOptions value) {
    return static_sk_sampling_options.create(value);
}

void static_sk_sampling_options_set(int key, SkSamplingOptions value) {
    static_sk_sampling_options.set(key, value);
}

SkSamplingOptions static_sk_sampling_options_get_entity(int key) {
    SkSamplingOptions* entity = static_sk_sampling_options.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_sampling_options_delete(int key) {
    static_sk_sampling_options.erase(key);
}

void * static_sk_sampling_options_get_ptr(int key) { // -> SkSamplingOptions *
    return static_sk_sampling_options.get_ptr(key);
}

}
