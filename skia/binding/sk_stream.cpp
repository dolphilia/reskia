//
// Created by dolphilia on 2024/01/11.
//

#include "sk_stream.h"

#include "include/core/SkStream.h"

#include "../static/static_sk_stream.h"
#include "../static/static_sk_stream_asset.h"

#include "../static/static_sk_stream-internal.h"
#include "../static/static_sk_stream_asset-internal.h"
#include "../static/static_sk_stream_asset.h"

extern "C" {

void SkStream_delete(void *stream) {
    delete static_cast<SkStream *>(stream);
}

size_t SkStream_read(void *stream, void *buffer, size_t size) {
    return static_cast<SkStream *>(stream)->read(buffer, size);
}

size_t SkStream_skip(void *stream, size_t size) {
    return static_cast<SkStream *>(stream)->skip(size);
}

size_t SkStream_peek(void *stream, void *buffer, size_t size) {
    return static_cast<SkStream *>(stream)->peek(buffer, size);
}

bool SkStream_isAtEnd(void *stream) {
    return static_cast<SkStream *>(stream)->isAtEnd();
}

bool SkStream_readS8(void *stream, void *i) {
    return static_cast<SkStream *>(stream)->readS8(static_cast<int8_t *>(i));
}

bool SkStream_readS16(void *stream, void *i) {
    return static_cast<SkStream *>(stream)->readS16(static_cast<int16_t *>(i));
}

bool SkStream_readS32(void *stream, void *i) {
    return static_cast<SkStream *>(stream)->readS32(static_cast<int32_t *>(i));
}

bool SkStream_readU8(void *stream, void *i) {
    return static_cast<SkStream *>(stream)->readU8(static_cast<uint8_t *>(i));
}

bool SkStream_readU16(void *stream, void *i) {
    return static_cast<SkStream *>(stream)->readU16(static_cast<uint16_t *>(i));
}

bool SkStream_readU32(void *stream, void *i) {
    return static_cast<SkStream *>(stream)->readU32(static_cast<uint32_t *>(i));
}

bool SkStream_readBool(void *stream, void *b) {
    return static_cast<SkStream *>(stream)->readBool(static_cast<bool *>(b));
}

bool SkStream_readScalar(void *stream, void *v) {
    return static_cast<SkStream *>(stream)->readScalar(static_cast<SkScalar *>(v));
}

bool SkStream_readPackedUInt(void *stream, void *size) {
    return static_cast<SkStream *>(stream)->readPackedUInt(static_cast<size_t *>(size));
}

bool SkStream_rewind(void *stream) {
    return static_cast<SkStream *>(stream)->rewind();
}

sk_stream_t SkStream_duplicate(void *stream) {
    return static_sk_stream_make(static_cast<SkStream *>(stream)->duplicate());
}

sk_stream_t SkStream_fork(void *stream) {
    return static_sk_stream_make(static_cast<SkStream *>(stream)->fork());
}

bool SkStream_hasPosition(void *stream) {
    return static_cast<SkStream *>(stream)->hasPosition();
}

size_t SkStream_getPosition(void *stream) {
    return static_cast<SkStream *>(stream)->getPosition();
}

bool SkStream_seek(void *stream, size_t size) {
    return static_cast<SkStream *>(stream)->seek(size);
}

bool SkStream_move(void *stream, long i) {
    return static_cast<SkStream *>(stream)->move(i);
}

bool SkStream_hasLength(void *stream) {
    return static_cast<SkStream *>(stream)->hasLength();
}

size_t SkStream_getLength(void *stream) {
    return static_cast<SkStream *>(stream)->getLength();
}

const void * SkStream_getMemoryBase(void *stream) {
    return static_cast<SkStream *>(stream)->getMemoryBase();
}

// static

sk_stream_asset_t SkStream_MakeFromFile(const char path[]) { // static
    return static_sk_stream_asset_make(SkStream::MakeFromFile(path));
}

}