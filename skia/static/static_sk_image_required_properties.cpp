//
// Created by dolphilia on 2024/04/03.
//

#include "static_sk_image_required_properties.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_image_required_properties-internal.h"

static reskia::static_registry::HandleTable<SkImage::RequiredProperties> static_sk_image_required_properties;

int static_sk_image_required_properties_make(SkImage::RequiredProperties value) {
    return static_sk_image_required_properties.create(std::move(value));
}

void static_sk_image_required_properties_set(int key, SkImage::RequiredProperties value) {
    static_sk_image_required_properties.set(key, std::move(value));
}

SkImage::RequiredProperties static_sk_image_required_properties_get_entity(int key) {
    SkImage::RequiredProperties* entity = static_sk_image_required_properties.get_ptr(key);
    if (entity == nullptr) {
        return {};
    }
    return *entity;
}

extern "C" {

void static_sk_image_required_properties_delete(int key) {
    static_sk_image_required_properties.erase(key);
}

void * static_sk_image_required_properties_get_ptr(int key) { // -> SkImage::RequiredProperties *
    return static_sk_image_required_properties.get_ptr(key);
}

}
