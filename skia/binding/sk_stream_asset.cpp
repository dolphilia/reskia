//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream_asset.h"

#include "include/core/SkStream.h"

#include "../static/static_sk_stream_asset.h"

#include "../static/static_sk_stream_asset-internal.h"

extern "C" {

void SkStreamAsset_delete(void *stream_asset) {
    delete static_cast<SkStreamAsset *>(stream_asset);
}

bool SkStreamAsset_hasLength(void *stream_asset) {
    return static_cast<SkStreamAsset *>(stream_asset)->hasLength();
}

size_t SkStreamAsset_getLength(void *stream_asset) {
    return static_cast<SkStreamAsset *>(stream_asset)->getLength();
}

sk_stream_asset_t SkStreamAsset_duplicate(void *stream_asset) {
    return static_sk_stream_asset_make(static_cast<SkStreamAsset *>(stream_asset)->duplicate());
}

sk_stream_asset_t SkStreamAsset_fork(void *stream_asset) {
    return static_sk_stream_asset_make(static_cast<SkStreamAsset *>(stream_asset)->fork());
}

bool SkStreamAsset_hasPosition(void *stream_asset) {
    return static_cast<SkStreamAsset *>(stream_asset)->hasPosition();
}

size_t SkStreamAsset_getPosition(void *stream_asset) {
    return static_cast<SkStreamAsset *>(stream_asset)->getPosition();
}

bool SkStreamAsset_seek(void *stream_asset, size_t position) {
    return static_cast<SkStreamAsset *>(stream_asset)->seek(position);
}

bool SkStreamAsset_move(void *stream_asset, long offset) {
    return static_cast<SkStreamAsset *>(stream_asset)->move(offset);
}

bool SkStreamAsset_rewind(void *stream_asset) {
    return static_cast<SkStreamAsset *>(stream_asset)->rewind();
}

size_t SkStreamAsset_read(void *stream_asset, void *buffer, size_t size) {
    return static_cast<SkStreamAsset *>(stream_asset)->read(buffer, size);
}

size_t SkStreamAsset_skip(void *stream_asset, size_t size) {
    return static_cast<SkStreamAsset *>(stream_asset)->skip(size);
}

size_t SkStreamAsset_peek(void *stream_asset, void *buffer, size_t size) {
    return static_cast<SkStreamAsset *>(stream_asset)->peek(buffer, size);
}

bool SkStreamAsset_isAtEnd(void *stream_asset) {
    return static_cast<SkStreamAsset *>(stream_asset)->isAtEnd();
}

bool SkStreamAsset_readS8(void *stream_asset, void *i) {
    return static_cast<SkStreamAsset *>(stream_asset)->readS8(static_cast<int8_t *>(i));
}

bool SkStreamAsset_readS16(void *stream_asset, void *i) {
    return static_cast<SkStreamAsset *>(stream_asset)->readS16(static_cast<int16_t *>(i));
}

bool SkStreamAsset_readS32(void *stream_asset, void *i) {
    return static_cast<SkStreamAsset *>(stream_asset)->readS32(static_cast<int32_t *>(i));
}

bool SkStreamAsset_readU8(void *stream_asset, void *i) {
    return static_cast<SkStreamAsset *>(stream_asset)->readU8(static_cast<uint8_t *>(i));
}

bool SkStreamAsset_readU16(void *stream_asset, void *i) {
    return static_cast<SkStreamAsset *>(stream_asset)->readU16(static_cast<uint16_t *>(i));
}

bool SkStreamAsset_readU32(void *stream_asset, void *i) {
    return static_cast<SkStreamAsset *>(stream_asset)->readU32(static_cast<uint32_t *>(i));
}

bool SkStreamAsset_readBool(void *stream_asset, void *b) {
    return static_cast<SkStreamAsset *>(stream_asset)->readBool(static_cast<bool *>(b));
}

bool SkStreamAsset_readScalar(void *stream_asset, void *v) {
    return static_cast<SkStreamAsset *>(stream_asset)->readScalar(static_cast<SkScalar *>(v));
}

bool SkStreamAsset_readPackedUInt(void *stream_asset, void *size) {
    return static_cast<SkStreamAsset *>(stream_asset)->readPackedUInt(static_cast<size_t *>(size));
}

const void * SkStreamAsset_getMemoryBase(void *stream_asset) {
    return static_cast<SkStreamAsset *>(stream_asset)->getMemoryBase();
}

// static

sk_stream_asset_t SkStreamAsset_MakeFromFile(const char path[]) {
    return static_sk_stream_asset_make(SkStreamAsset::MakeFromFile(path));
}

}
