//
// Created by dolphilia on 25/01/30.
//

#include "static_sk_mask.h"

#include "handle_table.hpp"
#include "static_sk_mask-internal.h"

static reskia::static_registry::HandleTable<std::unique_ptr<SkMask>> static_sk_mask;

int static_sk_mask_make(const SkMask& value) {
    return static_sk_mask.create(std::make_unique<SkMask>(value));
}

void static_sk_mask_set(int key, const SkMask& value) {
    static_sk_mask.set(key, std::make_unique<SkMask>(value));
}

extern "C" {

void static_sk_mask_delete(int key) {
    static_sk_mask.erase(key);
}

void* static_sk_mask_get_ptr(int key) { // -> SkMask*
    std::unique_ptr<SkMask>* entity = static_sk_mask.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
