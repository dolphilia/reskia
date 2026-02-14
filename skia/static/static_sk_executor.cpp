//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_executor.h"
#include "static_sk_executor-internal.h"
#include "handle_table.hpp"

static reskia::static_registry::HandleTable<std::unique_ptr<SkExecutor>> static_sk_executor;

int static_sk_executor_make(std::unique_ptr<SkExecutor> value) {
    return static_sk_executor.create(std::move(value));
}

void static_sk_executor_set(int key, std::unique_ptr<SkExecutor> value) {
    static_sk_executor.set(key, std::move(value));
}

SkExecutor* static_sk_executor_borrow_entity(int key) {
    std::unique_ptr<SkExecutor>* entity = static_sk_executor.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkExecutor> static_sk_executor_take_entity(int key) {
    return static_sk_executor.take_or_default(key);
}

std::unique_ptr<SkExecutor> static_sk_executor_get_entity(int key) {
    return static_sk_executor_take_entity(key);
}

extern "C" {

void static_sk_executor_delete(int key) {
    static_sk_executor.erase(key);
}

void *static_sk_executor_get_ptr(int key) { // -> SkExecutor *
    std::unique_ptr<SkExecutor>* entity = static_sk_executor.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
