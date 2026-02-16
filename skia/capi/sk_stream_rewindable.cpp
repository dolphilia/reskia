//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream_rewindable.h"

#include "include/core/SkStream.h"

#include "../handles/static_sk_stream_rewindable.h"
#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_stream_asset.h"

#include "../handles/static_sk_stream-internal.h"
#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_stream_rewindable-internal.h"

extern "C" {

void SkStreamRewindable_delete(reskia_stream_rewindable_t *stream_rewindable) {
    delete reinterpret_cast<SkStreamRewindable *>(stream_rewindable);
}

bool SkStreamRewindable_rewind(reskia_stream_rewindable_t *stream_rewindable) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->rewind();
}

sk_stream_rewindable_t SkStreamRewindable_duplicate(reskia_stream_rewindable_t *stream_rewindable) {
    return static_sk_stream_rewindable_make(reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->duplicate());
}

size_t SkStreamRewindable_read(reskia_stream_rewindable_t *stream_rewindable, void *buffer, size_t size) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->read(buffer, size);
}

size_t SkStreamRewindable_skip(reskia_stream_rewindable_t *stream_rewindable, size_t size) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->skip(size);
}

size_t SkStreamRewindable_peek(reskia_stream_rewindable_t *stream_rewindable, void *buffer, size_t size) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->peek(buffer, size);
}

bool SkStreamRewindable_isAtEnd(reskia_stream_rewindable_t *stream_rewindable) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->isAtEnd();
}

bool SkStreamRewindable_readS8(reskia_stream_rewindable_t *stream_rewindable, int8_t *i) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readS8(i);
}

bool SkStreamRewindable_readS16(reskia_stream_rewindable_t *stream_rewindable, int16_t *i) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readS16(i);
}

bool SkStreamRewindable_readS32(reskia_stream_rewindable_t *stream_rewindable, int32_t *i) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readS32(i);
}

bool SkStreamRewindable_readU8(reskia_stream_rewindable_t *stream_rewindable, uint8_t *i) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readU8(i);
}

bool SkStreamRewindable_readU16(reskia_stream_rewindable_t *stream_rewindable, uint16_t *i) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readU16(i);
}

bool SkStreamRewindable_readU32(reskia_stream_rewindable_t *stream_rewindable, uint32_t *i) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readU32(i);
}

bool SkStreamRewindable_readBool(reskia_stream_rewindable_t *stream_rewindable, bool *b) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readBool(b);
}

bool SkStreamRewindable_readScalar(reskia_stream_rewindable_t *stream_rewindable, float *v) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readScalar(v);
}

bool SkStreamRewindable_readPackedUInt(reskia_stream_rewindable_t *stream_rewindable, size_t *size) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->readPackedUInt(size);
}

sk_stream_t SkStreamRewindable_fork(reskia_stream_rewindable_t *stream_rewindable) {
    return static_sk_stream_make(reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->fork());
}

bool SkStreamRewindable_hasPosition(reskia_stream_rewindable_t *stream_rewindable) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->hasPosition();
}

size_t SkStreamRewindable_getPosition(reskia_stream_rewindable_t *stream_rewindable) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->getPosition();
}

bool SkStreamRewindable_seek(reskia_stream_rewindable_t *stream_rewindable, size_t size) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->seek(size);
}

bool SkStreamRewindable_move(reskia_stream_rewindable_t *stream_rewindable, long i) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->move(i);
}

bool SkStreamRewindable_hasLength(reskia_stream_rewindable_t *stream_rewindable) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->hasLength();
}

size_t SkStreamRewindable_getLength(reskia_stream_rewindable_t *stream_rewindable) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->getLength();
}

const void * SkStreamRewindable_getMemoryBase(reskia_stream_rewindable_t *stream_rewindable) {
    return reinterpret_cast<SkStreamRewindable *>(stream_rewindable)->getMemoryBase();
}

// static

sk_stream_asset_t SkStreamRewindable_MakeFromFile(const char path[]) {
    return static_sk_stream_asset_make(SkStreamRewindable::MakeFromFile(path));
}

}
