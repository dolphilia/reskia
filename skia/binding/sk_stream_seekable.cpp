//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream_seekable.h"

#include "include/core/SkStream.h"

#include "../static/static_sk_stream_seekable.h"
#include "../static/static_sk_stream_asset.h"

#include "../static/static_sk_stream_asset-internal.h"
#include "../static/static_sk_stream_seekable-internal.h"

extern "C" {

void SkStreamSeekable_delete(void *stream_seekable) {
    delete static_cast<SkStreamSeekable *>(stream_seekable);
}

sk_stream_seekable_t SkStreamSeekable_duplicate(void *stream_seekable) {
    return static_sk_stream_seekable_make(static_cast<SkStreamSeekable *>(stream_seekable)->duplicate());
}

bool SkStreamSeekable_hasPosition(void *stream_seekable) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->hasPosition();
}

size_t SkStreamSeekable_getPosition(void *stream_seekable) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->getPosition();
}

bool SkStreamSeekable_seek(void *stream_seekable, size_t position) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->seek(position);
}

bool SkStreamSeekable_move(void *stream_seekable, long offset) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->move(offset);
}

sk_stream_seekable_t SkStreamSeekable_fork(void *stream_seekable) {
    return static_sk_stream_seekable_make(static_cast<SkStreamSeekable *>(stream_seekable)->fork());
}

bool SkStreamSeekable_rewind(void *stream_seekable) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->rewind();
}

size_t SkStreamSeekable_read(void *stream_seekable, void *buffer, size_t size) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->read(buffer, size);
}

size_t SkStreamSeekable_skip(void *stream_seekable, size_t size) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->skip(size);
}

size_t SkStreamSeekable_peek(void *stream_seekable, void *buffer, size_t size) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->peek(buffer, size);
}

bool SkStreamSeekable_isAtEnd(void *stream_seekable) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->isAtEnd();
}

bool SkStreamSeekable_readS8(void *stream_seekable, void *i) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readS8(static_cast<int8_t *>(i));
}

bool SkStreamSeekable_readS16(void *stream_seekable, void *i) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readS16(static_cast<int16_t *>(i));
}

bool SkStreamSeekable_readS32(void *stream_seekable, void *i) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readS32(static_cast<int32_t *>(i));
}

bool SkStreamSeekable_readU8(void *stream_seekable, void *i) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readU8(static_cast<uint8_t *>(i));
}

bool SkStreamSeekable_readU16(void *stream_seekable, void *i) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readU16(static_cast<uint16_t *>(i));
}

bool SkStreamSeekable_readU32(void *stream_seekable, void *i) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readU32(static_cast<uint32_t *>(i));
}

bool SkStreamSeekable_readBool(void *stream_seekable, void *b) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readBool(static_cast<bool *>(b));
}

bool SkStreamSeekable_readScalar(void *stream_seekable, void *v) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readScalar(static_cast<SkScalar *>(v));
}

bool SkStreamSeekable_readPackedUInt(void *stream_seekable, void *size) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->readPackedUInt(static_cast<size_t *>(size));
}

bool SkStreamSeekable_hasLength(void *stream_seekable) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->hasLength();
}

size_t SkStreamSeekable_getLength(void *stream_seekable) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->getLength();
}

const void * SkStreamSeekable_getMemoryBase(void *stream_seekable) {
    return static_cast<SkStreamSeekable *>(stream_seekable)->getMemoryBase();
}

// static

sk_stream_asset_t SkStreamSeekable_MakeFromFile(const char path[]) {
    return static_sk_stream_asset_make(SkStreamSeekable::MakeFromFile(path));
}

}
