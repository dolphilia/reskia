//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream_rewindable.h"

#include "include/core/SkStream.h"

#include "../static/static_sk_stream_rewindable.h"
#include "../static/static_sk_stream.h"
#include "../static/static_sk_stream_asset.h"

#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_stream_asset-internal.h"
#include "../static/static_sk_stream_rewindable-internal.h"

extern "C" {

void SkStreamRewindable_delete(void *stream_rewindable) {
    delete static_cast<SkStreamRewindable *>(stream_rewindable);
}

bool SkStreamRewindable_rewind(void *stream_rewindable) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->rewind();
}

sk_stream_rewindable_t SkStreamRewindable_duplicate(void *stream_rewindable) {
    return static_sk_stream_rewindable_make(static_cast<SkStreamRewindable *>(stream_rewindable)->duplicate());
}

size_t SkStreamRewindable_read(void *stream_rewindable, void *buffer, size_t size) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->read(buffer, size);
}

size_t SkStreamRewindable_skip(void *stream_rewindable, size_t size) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->skip(size);
}

size_t SkStreamRewindable_peek(void *stream_rewindable, void *buffer, size_t size) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->peek(buffer, size);
}

bool SkStreamRewindable_isAtEnd(void *stream_rewindable) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->isAtEnd();
}

bool SkStreamRewindable_readS8(void *stream_rewindable, void *i) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readS8(static_cast<int8_t *>(i));
}

bool SkStreamRewindable_readS16(void *stream_rewindable, void *i) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readS16(static_cast<int16_t *>(i));
}

bool SkStreamRewindable_readS32(void *stream_rewindable, void *i) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readS32(static_cast<int32_t *>(i));
}

bool SkStreamRewindable_readU8(void *stream_rewindable, void *i) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readU8(static_cast<uint8_t *>(i));
}

bool SkStreamRewindable_readU16(void *stream_rewindable, void *i) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readU16(static_cast<uint16_t *>(i));
}

bool SkStreamRewindable_readU32(void *stream_rewindable, void *i) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readU32(static_cast<uint32_t *>(i));
}

bool SkStreamRewindable_readBool(void *stream_rewindable, void *b) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readBool(static_cast<bool *>(b));
}

bool SkStreamRewindable_readScalar(void *stream_rewindable, void *v) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readScalar(static_cast<SkScalar *>(v));
}

bool SkStreamRewindable_readPackedUInt(void *stream_rewindable, void *size) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->readPackedUInt(static_cast<size_t *>(size));
}

sk_stream_t SkStreamRewindable_fork(void *stream_rewindable) {
    return static_sk_stream_make(static_cast<SkStreamRewindable *>(stream_rewindable)->fork());
}

bool SkStreamRewindable_hasPosition(void *stream_rewindable) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->hasPosition();
}

size_t SkStreamRewindable_getPosition(void *stream_rewindable) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->getPosition();
}

bool SkStreamRewindable_seek(void *stream_rewindable, size_t size) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->seek(size);
}

bool SkStreamRewindable_move(void *stream_rewindable, long i) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->move(i);
}

bool SkStreamRewindable_hasLength(void *stream_rewindable) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->hasLength();
}

size_t SkStreamRewindable_getLength(void *stream_rewindable) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->getLength();
}

const void * SkStreamRewindable_getMemoryBase(void *stream_rewindable) {
    return static_cast<SkStreamRewindable *>(stream_rewindable)->getMemoryBase();
}

// static

sk_stream_asset_t SkStreamRewindable_MakeFromFile(const char path[]) {
    return static_sk_stream_asset_make(SkStreamRewindable::MakeFromFile(path));
}

}
