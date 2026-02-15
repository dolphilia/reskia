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

void SkStream_delete(reskia_stream_t *stream) {
    delete reinterpret_cast<SkStream *>(stream);
}

size_t SkStream_read(reskia_stream_t *stream, void *buffer, size_t size) {
    return reinterpret_cast<SkStream *>(stream)->read(buffer, size);
}

size_t SkStream_skip(reskia_stream_t *stream, size_t size) {
    return reinterpret_cast<SkStream *>(stream)->skip(size);
}

size_t SkStream_peek(reskia_stream_t *stream, void *buffer, size_t size) {
    return reinterpret_cast<SkStream *>(stream)->peek(buffer, size);
}

bool SkStream_isAtEnd(reskia_stream_t *stream) {
    return reinterpret_cast<SkStream *>(stream)->isAtEnd();
}

bool SkStream_readS8(reskia_stream_t *stream, int8_t *i) {
    return reinterpret_cast<SkStream *>(stream)->readS8(i);
}

bool SkStream_readS16(reskia_stream_t *stream, int16_t *i) {
    return reinterpret_cast<SkStream *>(stream)->readS16(i);
}

bool SkStream_readS32(reskia_stream_t *stream, int32_t *i) {
    return reinterpret_cast<SkStream *>(stream)->readS32(i);
}

bool SkStream_readU8(reskia_stream_t *stream, uint8_t *i) {
    return reinterpret_cast<SkStream *>(stream)->readU8(i);
}

bool SkStream_readU16(reskia_stream_t *stream, uint16_t *i) {
    return reinterpret_cast<SkStream *>(stream)->readU16(i);
}

bool SkStream_readU32(reskia_stream_t *stream, uint32_t *i) {
    return reinterpret_cast<SkStream *>(stream)->readU32(i);
}

bool SkStream_readBool(reskia_stream_t *stream, bool *b) {
    return reinterpret_cast<SkStream *>(stream)->readBool(b);
}

bool SkStream_readScalar(reskia_stream_t *stream, float *v) {
    return reinterpret_cast<SkStream *>(stream)->readScalar(v);
}

bool SkStream_readPackedUInt(reskia_stream_t *stream, size_t *size) {
    return reinterpret_cast<SkStream *>(stream)->readPackedUInt(size);
}

bool SkStream_rewind(reskia_stream_t *stream) {
    return reinterpret_cast<SkStream *>(stream)->rewind();
}

sk_stream_t SkStream_duplicate(reskia_stream_t *stream) {
    return static_sk_stream_make(reinterpret_cast<SkStream *>(stream)->duplicate());
}

sk_stream_t SkStream_fork(reskia_stream_t *stream) {
    return static_sk_stream_make(reinterpret_cast<SkStream *>(stream)->fork());
}

bool SkStream_hasPosition(reskia_stream_t *stream) {
    return reinterpret_cast<SkStream *>(stream)->hasPosition();
}

size_t SkStream_getPosition(reskia_stream_t *stream) {
    return reinterpret_cast<SkStream *>(stream)->getPosition();
}

bool SkStream_seek(reskia_stream_t *stream, size_t size) {
    return reinterpret_cast<SkStream *>(stream)->seek(size);
}

bool SkStream_move(reskia_stream_t *stream, long i) {
    return reinterpret_cast<SkStream *>(stream)->move(i);
}

bool SkStream_hasLength(reskia_stream_t *stream) {
    return reinterpret_cast<SkStream *>(stream)->hasLength();
}

size_t SkStream_getLength(reskia_stream_t *stream) {
    return reinterpret_cast<SkStream *>(stream)->getLength();
}

const void * SkStream_getMemoryBase(reskia_stream_t *stream) {
    return reinterpret_cast<SkStream *>(stream)->getMemoryBase();
}

// static

sk_stream_asset_t SkStream_MakeFromFile(const char path[]) { // static
    return static_sk_stream_asset_make(SkStream::MakeFromFile(path));
}

}
