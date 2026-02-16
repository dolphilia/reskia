//
// Created by dolphilia on 2024/01/05.
//

#include "static_sk_stream_asset.h"

#include <utility>
#include "handle_table.hpp"
#include "static_sk_stream_asset-internal.h"

static reskia::static_registry::HandleTable<std::unique_ptr<SkStreamAsset>> static_sk_stream_asset;

int static_sk_stream_asset_make(std::unique_ptr<SkStreamAsset> value) {
    return static_sk_stream_asset.create(std::move(value));
}

void static_sk_stream_asset_set(int key, std::unique_ptr<SkStreamAsset> value) {
    static_sk_stream_asset.set(key, std::move(value));
}

SkStreamAsset* static_sk_stream_asset_borrow_entity(int key) {
    std::unique_ptr<SkStreamAsset>* entity = static_sk_stream_asset.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

std::unique_ptr<SkStreamAsset> static_sk_stream_asset_take_entity(int key) {
    return static_sk_stream_asset.take_or_default(key);
}

std::unique_ptr<SkStreamAsset> static_sk_stream_asset_get_entity(int key) {
    return static_sk_stream_asset_take_entity(key);
}

extern "C" {

void static_sk_stream_asset_delete(int key) {
    static_sk_stream_asset.erase(key);
}

void *static_sk_stream_asset_get_ptr(int key) { // -> SkStreamAsset *
    std::unique_ptr<SkStreamAsset>* entity = static_sk_stream_asset.get_ptr(key);
    if (entity == nullptr) {
        return nullptr;
    }
    return entity->get();
}

}
