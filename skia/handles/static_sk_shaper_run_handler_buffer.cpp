//
// Created by dolphilia on 2026/02/17.
//

#include "static_sk_shaper_run_handler_buffer.h"

#include "handle_table.hpp"
#include "static_sk_shaper_run_handler_buffer-internal.h"

static reskia::static_registry::HandleTable<SkShaper::RunHandler::Buffer> static_sk_shaper_run_handler_buffer;

int static_sk_shaper_run_handler_buffer_make(SkShaper::RunHandler::Buffer value) {
    return static_sk_shaper_run_handler_buffer.create(value);
}

void static_sk_shaper_run_handler_buffer_set(int key, SkShaper::RunHandler::Buffer value) {
    static_sk_shaper_run_handler_buffer.set(key, value);
}

SkShaper::RunHandler::Buffer static_sk_shaper_run_handler_buffer_get_entity(int key) {
    SkShaper::RunHandler::Buffer* entity = static_sk_shaper_run_handler_buffer.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_shaper_run_handler_buffer_delete(int key) {
    static_sk_shaper_run_handler_buffer.erase(key);
}

void * static_sk_shaper_run_handler_buffer_get_ptr(int key) { // -> SkShaper::RunHandler::Buffer *
    return static_sk_shaper_run_handler_buffer.get_ptr(key);
}

}
