//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_canvas.h"
#include "static_sk_canvas-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<std::unique_ptr<SkCanvas>> static_sk_canvas;

int static_sk_canvas_make(std::unique_ptr<SkCanvas> value) {
    return static_sk_canvas.create(std::move(value));
}

void static_sk_canvas_set(int key, std::unique_ptr<SkCanvas> value) {
    static_sk_canvas.set(key, std::move(value));
}

SkCanvas* static_sk_canvas_borrow_entity(int key) {
    std::unique_ptr<SkCanvas>* entity = static_sk_canvas.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkCanvas> static_sk_canvas_take_entity(int key) {
    return static_sk_canvas.take_or_default(key);
}

std::unique_ptr<SkCanvas> static_sk_canvas_get_entity(int key) {
    return static_sk_canvas_take_entity(key);
}

extern "C" {

void static_sk_canvas_delete(int key) {
    static_sk_canvas.erase(key);
}

void *static_sk_canvas_get_ptr(int key) {  // -> SkCanvas *
    std::unique_ptr<SkCanvas>* entity = static_sk_canvas.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
