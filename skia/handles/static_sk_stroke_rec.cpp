//
// Created by dolphilia on 2024/01/11.
//

#include "static_sk_stroke_rec.h"
#include "handle_table.hpp"
#include "static_sk_stroke_rec-internal.h"

static reskia::static_registry::HandleTable<SkStrokeRec> static_sk_stroke_rec;

int static_sk_stroke_rec_make(SkStrokeRec value) {
    return static_sk_stroke_rec.create(value);
}

void static_sk_stroke_rec_set(int key, SkStrokeRec value) {
    static_sk_stroke_rec.set(key, value);
}

SkStrokeRec static_sk_stroke_rec_get_entity(int key) {
    SkStrokeRec* entity = static_sk_stroke_rec.get_ptr(key);
    if (entity == nullptr) {
        return SkStrokeRec(SkStrokeRec::kFill_InitStyle);
    }
    return *entity;
}

extern "C" {

void static_sk_stroke_rec_delete(int key) {
    static_sk_stroke_rec.erase(key);
}

void * static_sk_stroke_rec_get_ptr(int key) { // -> SkStrokeRec *
    return static_sk_stroke_rec.get_ptr(key);
}

}
