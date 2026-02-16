//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_drawable_gpu_draw_handler.h"
#include "static_sk_drawable_gpu_draw_handler-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<std::unique_ptr<SkDrawable::GpuDrawHandler>> static_sk_drawable_gpu_draw_handler;

int static_sk_drawable_gpu_draw_handler_make(std::unique_ptr<SkDrawable::GpuDrawHandler> value) {
    return static_sk_drawable_gpu_draw_handler.create(std::move(value));
}

void static_sk_drawable_gpu_draw_handler_set(int key, std::unique_ptr<SkDrawable::GpuDrawHandler> value) {
    static_sk_drawable_gpu_draw_handler.set(key, std::move(value));
}

SkDrawable::GpuDrawHandler* static_sk_drawable_gpu_draw_handler_borrow_entity(int key) {
    std::unique_ptr<SkDrawable::GpuDrawHandler>* entity = static_sk_drawable_gpu_draw_handler.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkDrawable::GpuDrawHandler> static_sk_drawable_gpu_draw_handler_take_entity(int key) {
    return static_sk_drawable_gpu_draw_handler.take_or_default(key);
}

std::unique_ptr<SkDrawable::GpuDrawHandler> static_sk_drawable_gpu_draw_handler_get_entity(int key) {
    return static_sk_drawable_gpu_draw_handler_take_entity(key);
}

extern "C" {

void static_sk_drawable_gpu_draw_handler_delete(int key) {
    static_sk_drawable_gpu_draw_handler.erase(key);
}

void *static_sk_drawable_gpu_draw_handler_get_ptr(int key) { // -> SkDrawable::GpuDrawHandler *
    std::unique_ptr<SkDrawable::GpuDrawHandler>* entity = static_sk_drawable_gpu_draw_handler.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
