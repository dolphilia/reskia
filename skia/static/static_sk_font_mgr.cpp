//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_font_mgr.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_font_mgr-internal.h"

static reskia::static_registry::HandleTable<sk_sp<SkFontMgr>> static_sk_font_mgr;

int static_sk_font_mgr_make(sk_sp<SkFontMgr> value) {
    return static_sk_font_mgr.create(std::move(value));
}

void static_sk_font_mgr_set(int key, sk_sp<SkFontMgr> value) {
    static_sk_font_mgr.set(key, std::move(value));
}

sk_sp<SkFontMgr> static_sk_font_mgr_borrow_entity(int key) {
    sk_sp<SkFontMgr>* entity = static_sk_font_mgr.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

sk_sp<SkFontMgr> static_sk_font_mgr_take_entity(int key) {
    return static_sk_font_mgr.take_or_default(key);
}

sk_sp<SkFontMgr> static_sk_font_mgr_get_entity(int key) {
    return static_sk_font_mgr_borrow_entity(key);
}

extern "C" {

void static_sk_font_mgr_delete(int key) {
    static_sk_font_mgr.erase(key);
}

void *static_sk_font_mgr_get_ptr(int key) { // -> SkFontMgr *
    sk_sp<SkFontMgr>* entity = static_sk_font_mgr.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
