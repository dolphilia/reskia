//
// Created by dolphilia on 2024/04/05.
//

#include "static_sk_rsx_form.h"
#include "handle_table.hpp"
#include "static_sk_rsx_form-internal.h"

static reskia::static_registry::HandleTable<SkRSXform> static_sk_rsx_form;

int static_sk_rsx_form_make(SkRSXform value) {
    return static_sk_rsx_form.create(value);
}

void static_sk_rsx_form_set(int key, SkRSXform value) {
    static_sk_rsx_form.set(key, value);
}

SkRSXform static_sk_rsx_form_get_entity(int key) {
    SkRSXform* entity = static_sk_rsx_form.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_rsx_form_delete(int key) {
    static_sk_rsx_form.erase(key);
}

void * static_sk_rsx_form_get_ptr(int key) { // -> SkRSXform *
    return static_sk_rsx_form.get_ptr(key);
}

}
