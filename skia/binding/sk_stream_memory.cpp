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

void SkStreamMemory_delete(reskia_stream_memory_t *stream_memory) {
    delete reinterpret_cast<SkStreamMemory *>(stream_memory);
}

const void * SkStreamMemory_getMemoryBase(reskia_stream_memory_t *stream_memory) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->getMemoryBase();
}

sk_stream_memory_t SkStreamMemory_duplicate(reskia_stream_memory_t *stream_memory) {
    return static_sk_stream_memory_make(reinterpret_cast<SkStreamMemory *>(stream_memory)->duplicate());
}

sk_stream_memory_t SkStreamMemory_fork(reskia_stream_memory_t *stream_memory) {
    return static_sk_stream_memory_make(reinterpret_cast<SkStreamMemory *>(stream_memory)->fork());
}

bool SkStreamMemory_hasLength(reskia_stream_memory_t *stream_memory) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->hasLength();
}

size_t SkStreamMemory_getLength(reskia_stream_memory_t *stream_memory) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->getLength();
}

bool SkStreamMemory_hasPosition(reskia_stream_memory_t *stream_memory) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->hasPosition();
}

size_t SkStreamMemory_getPosition(reskia_stream_memory_t *stream_memory) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->getPosition();
}

bool SkStreamMemory_seek(reskia_stream_memory_t *stream_memory, size_t position) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->seek(position);
}

bool SkStreamMemory_move(reskia_stream_memory_t *stream_memory, long offset) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->move(offset);
}

bool SkStreamMemory_rewind(reskia_stream_memory_t *stream_memory) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->rewind();
}

size_t SkStreamMemory_read(reskia_stream_memory_t *stream_memory, void *buffer, size_t size) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->read(buffer, size);
}

size_t SkStreamMemory_skip(reskia_stream_memory_t *stream_memory, size_t size) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->skip(size);
}

size_t SkStreamMemory_peek(reskia_stream_memory_t *stream_memory, void *buffer, size_t size) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->peek(buffer, size);
}

bool SkStreamMemory_isAtEnd(reskia_stream_memory_t *stream_memory) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->isAtEnd();
}

bool SkStreamMemory_readS8(reskia_stream_memory_t *stream_memory, int8_t *i) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readS8(i);
}

bool SkStreamMemory_readS16(reskia_stream_memory_t *stream_memory, int16_t *i) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readS16(i);
}

bool SkStreamMemory_readS32(reskia_stream_memory_t *stream_memory, int32_t *i) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readS32(i);
}

bool SkStreamMemory_readU8(reskia_stream_memory_t *stream_memory, uint8_t *i) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readU8(i);
}

bool SkStreamMemory_readU16(reskia_stream_memory_t *stream_memory, uint16_t *i) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readU16(i);
}

bool SkStreamMemory_readU32(reskia_stream_memory_t *stream_memory, uint32_t *i) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readU32(i);
}

bool SkStreamMemory_readBool(reskia_stream_memory_t *stream_memory, bool *b) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readBool(b);
}

bool SkStreamMemory_readScalar(reskia_stream_memory_t *stream_memory, float *v) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readScalar(v);
}

bool SkStreamMemory_readPackedUInt(reskia_stream_memory_t *stream_memory, size_t *size) {
    return reinterpret_cast<SkStreamMemory *>(stream_memory)->readPackedUInt(size);
}

// static

sk_stream_asset_t SkStreamMemory_MakeFromFile(const char path[]) {
    return static_sk_stream_asset_make(SkStreamMemory::MakeFromFile(path));
}

}
