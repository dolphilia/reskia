//
// Created by dolphilia on 25/02/17.
//

#include "static_sk_paint.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_paint-internal.h"

static reskia::static_registry::HandleTable<SkPaint> static_sk_paint;

int static_sk_paint_make(SkPaint value) {
    return static_sk_paint.create(std::move(value));
}

void static_sk_paint_set(int key, SkPaint value) {
    static_sk_paint.set(key, std::move(value));
}

SkPaint static_sk_paint_get_entity(int key) {
    SkPaint* entity = static_sk_paint.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_paint_delete(int key) {
    static_sk_paint.erase(key);
}

void *static_sk_paint_get_ptr(int key) {
    return static_sk_paint.get_ptr(key);
}

}
