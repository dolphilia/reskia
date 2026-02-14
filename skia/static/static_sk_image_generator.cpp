//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_image_generator.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_image_generator-internal.h"

static reskia::static_registry::HandleTable<std::unique_ptr<SkImageGenerator>> static_sk_image_generator_table;

int static_sk_image_generator_make(std::unique_ptr<SkImageGenerator> value) {
    return static_sk_image_generator_table.create(std::move(value));
}

void static_sk_image_generator_set(int key, std::unique_ptr<SkImageGenerator> value) {
    static_sk_image_generator_table.set(key, std::move(value));
}

SkImageGenerator* static_sk_image_generator_borrow_entity(int key) {
    std::unique_ptr<SkImageGenerator>* entity = static_sk_image_generator_table.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkImageGenerator> static_sk_image_generator_take_entity(int key) {
    return static_sk_image_generator_table.take_or_default(key);
}

std::unique_ptr<SkImageGenerator> static_sk_image_generator_get_entity(int key) {
    return static_sk_image_generator_take_entity(key);
}

extern "C" {

void static_sk_image_generator_delete(int key) {
    static_sk_image_generator_table.erase(key);
}

void *static_sk_image_generator_get_ptr(int key) { // -> SkImageGenerator *
    std::unique_ptr<SkImageGenerator>* entity = static_sk_image_generator_table.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
