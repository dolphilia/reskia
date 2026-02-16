//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream_seekable.h"

#include "include/core/SkStream.h"

#include "../handles/static_sk_stream_seekable.h"
#include "../handles/static_sk_stream_asset.h"

#include "../handles/static_sk_stream_asset-internal.h"
#include "../handles/static_sk_stream_seekable-internal.h"

extern "C" {

void SkStreamSeekable_delete(reskia_stream_seekable_t *stream_seekable) {
    delete reinterpret_cast<SkStreamSeekable *>(stream_seekable);
}

sk_stream_seekable_t SkStreamSeekable_duplicate(reskia_stream_seekable_t *stream_seekable) {
    return static_sk_stream_seekable_make(reinterpret_cast<SkStreamSeekable *>(stream_seekable)->duplicate());
}

bool SkStreamSeekable_hasPosition(reskia_stream_seekable_t *stream_seekable) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->hasPosition();
}

size_t SkStreamSeekable_getPosition(reskia_stream_seekable_t *stream_seekable) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->getPosition();
}

bool SkStreamSeekable_seek(reskia_stream_seekable_t *stream_seekable, size_t position) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->seek(position);
}

bool SkStreamSeekable_move(reskia_stream_seekable_t *stream_seekable, long offset) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->move(offset);
}

sk_stream_seekable_t SkStreamSeekable_fork(reskia_stream_seekable_t *stream_seekable) {
    return static_sk_stream_seekable_make(reinterpret_cast<SkStreamSeekable *>(stream_seekable)->fork());
}

bool SkStreamSeekable_rewind(reskia_stream_seekable_t *stream_seekable) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->rewind();
}

size_t SkStreamSeekable_read(reskia_stream_seekable_t *stream_seekable, void *buffer, size_t size) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->read(buffer, size);
}

size_t SkStreamSeekable_skip(reskia_stream_seekable_t *stream_seekable, size_t size) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->skip(size);
}

size_t SkStreamSeekable_peek(reskia_stream_seekable_t *stream_seekable, void *buffer, size_t size) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->peek(buffer, size);
}

bool SkStreamSeekable_isAtEnd(reskia_stream_seekable_t *stream_seekable) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->isAtEnd();
}

bool SkStreamSeekable_readS8(reskia_stream_seekable_t *stream_seekable, int8_t *i) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readS8(i);
}

bool SkStreamSeekable_readS16(reskia_stream_seekable_t *stream_seekable, int16_t *i) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readS16(i);
}

bool SkStreamSeekable_readS32(reskia_stream_seekable_t *stream_seekable, int32_t *i) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readS32(i);
}

bool SkStreamSeekable_readU8(reskia_stream_seekable_t *stream_seekable, uint8_t *i) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readU8(i);
}

bool SkStreamSeekable_readU16(reskia_stream_seekable_t *stream_seekable, uint16_t *i) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readU16(i);
}

bool SkStreamSeekable_readU32(reskia_stream_seekable_t *stream_seekable, uint32_t *i) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readU32(i);
}

bool SkStreamSeekable_readBool(reskia_stream_seekable_t *stream_seekable, bool *b) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readBool(b);
}

bool SkStreamSeekable_readScalar(reskia_stream_seekable_t *stream_seekable, float *v) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readScalar(v);
}

bool SkStreamSeekable_readPackedUInt(reskia_stream_seekable_t *stream_seekable, size_t *size) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->readPackedUInt(size);
}

bool SkStreamSeekable_hasLength(reskia_stream_seekable_t *stream_seekable) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->hasLength();
}

size_t SkStreamSeekable_getLength(reskia_stream_seekable_t *stream_seekable) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->getLength();
}

const void * SkStreamSeekable_getMemoryBase(reskia_stream_seekable_t *stream_seekable) {
    return reinterpret_cast<SkStreamSeekable *>(stream_seekable)->getMemoryBase();
}

// static

sk_stream_asset_t SkStreamSeekable_MakeFromFile(const char path[]) {
    return static_sk_stream_asset_make(SkStreamSeekable::MakeFromFile(path));
}

}
