//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream_memory.h"

#include "include/core/SkStream.h"

#include "../static/static_sk_stream_memory.h"
#include "../static/static_sk_stream_asset.h"

#include "../static/static_sk_stream_asset-internal.h"
#include "../static/static_sk_stream_memory-internal.h"

extern "C" {

void SkStreamMemory_delete(void *stream_memory) {
    delete static_cast<SkStreamMemory *>(stream_memory);
}

const void * SkStreamMemory_getMemoryBase(void *stream_memory) {
    return static_cast<SkStreamMemory *>(stream_memory)->getMemoryBase();
}

sk_stream_memory_t SkStreamMemory_duplicate(void *stream_memory) {
    return static_sk_stream_memory_make(static_cast<SkStreamMemory *>(stream_memory)->duplicate());
}

sk_stream_memory_t SkStreamMemory_fork(void *stream_memory) {
    return static_sk_stream_memory_make(static_cast<SkStreamMemory *>(stream_memory)->fork());
}

bool SkStreamMemory_hasLength(void *stream_memory) {
    return static_cast<SkStreamMemory *>(stream_memory)->hasLength();
}

size_t SkStreamMemory_getLength(void *stream_memory) {
    return static_cast<SkStreamMemory *>(stream_memory)->getLength();
}

bool SkStreamMemory_hasPosition(void *stream_memory) {
    return static_cast<SkStreamMemory *>(stream_memory)->hasPosition();
}

size_t SkStreamMemory_getPosition(void *stream_memory) {
    return static_cast<SkStreamMemory *>(stream_memory)->getPosition();
}

bool SkStreamMemory_seek(void *stream_memory, size_t position) {
    return static_cast<SkStreamMemory *>(stream_memory)->seek(position);
}

bool SkStreamMemory_move(void *stream_memory, long offset) {
    return static_cast<SkStreamMemory *>(stream_memory)->move(offset);
}

bool SkStreamMemory_rewind(void *stream_memory) {
    return static_cast<SkStreamMemory *>(stream_memory)->rewind();
}

size_t SkStreamMemory_read(void *stream_memory, void *buffer, size_t size) {
    return static_cast<SkStreamMemory *>(stream_memory)->read(buffer, size);
}

size_t SkStreamMemory_skip(void *stream_memory, size_t size) {
    return static_cast<SkStreamMemory *>(stream_memory)->skip(size);
}

size_t SkStreamMemory_peek(void *stream_memory, void *buffer, size_t size) {
    return static_cast<SkStreamMemory *>(stream_memory)->peek(buffer, size);
}

bool SkStreamMemory_isAtEnd(void *stream_memory) {
    return static_cast<SkStreamMemory *>(stream_memory)->isAtEnd();
}

bool SkStreamMemory_readS8(void *stream_memory, void *i) {
    return static_cast<SkStreamMemory *>(stream_memory)->readS8(static_cast<int8_t *>(i));
}

bool SkStreamMemory_readS16(void *stream_memory, void *i) {
    return static_cast<SkStreamMemory *>(stream_memory)->readS16(static_cast<int16_t *>(i));
}

bool SkStreamMemory_readS32(void *stream_memory, void *i) {
    return static_cast<SkStreamMemory *>(stream_memory)->readS32(static_cast<int32_t *>(i));
}

bool SkStreamMemory_readU8(void *stream_memory, void *i) {
    return static_cast<SkStreamMemory *>(stream_memory)->readU8(static_cast<uint8_t *>(i));
}

bool SkStreamMemory_readU16(void *stream_memory, void *i) {
    return static_cast<SkStreamMemory *>(stream_memory)->readU16(static_cast<uint16_t *>(i));
}

bool SkStreamMemory_readU32(void *stream_memory, void *i) {
    return static_cast<SkStreamMemory *>(stream_memory)->readU32(static_cast<uint32_t *>(i));
}

bool SkStreamMemory_readBool(void *stream_memory, void *b) {
    return static_cast<SkStreamMemory *>(stream_memory)->readBool(static_cast<bool *>(b));
}

bool SkStreamMemory_readScalar(void *stream_memory, void *v) {
    return static_cast<SkStreamMemory *>(stream_memory)->readScalar(static_cast<SkScalar *>(v));
}

bool SkStreamMemory_readPackedUInt(void *stream_memory, void *size) {
    return static_cast<SkStreamMemory *>(stream_memory)->readPackedUInt(static_cast<size_t *>(size));
}

// static

sk_stream_asset_t SkStreamMemory_MakeFromFile(const char path[]) {
    return static_sk_stream_asset_make(SkStreamMemory::MakeFromFile(path));
}

}
