//
// Created by dolphilia on 2024/01/08.
//

#include "sk_file_stream.h"

#include "include/core/SkStream.h"

#include "../static/static_sk_file_stream.h"
#include "../static/static_sk_stream_asset.h"

#include "../static/static_sk_stream_asset-internal.h"
#include "../static/static_sk_file_stream-internal.h"

extern "C" {

void *SkFILEStream_new(const char path[]) {
    return new SkFILEStream(path);
}

void *SkFILEStream_new_2(void *file) {
    return new SkFILEStream(static_cast<FILE *>(file));
}

void *SkFILEStream_new_3(void *file, size_t size) {
    return new SkFILEStream(static_cast<FILE *>(file), size);
}

void SkFILEStream_delete(void *file_stream) {
    delete static_cast<SkFILEStream *>(file_stream);
}

bool SkFILEStream_isValid(void *file_stream) {
    return static_cast<SkFILEStream *>(file_stream)->isValid();
}

void SkFILEStream_close(void *file_stream) {
    static_cast<SkFILEStream *>(file_stream)->close();
}

size_t SkFILEStream_read(void *file_stream, void *buffer, size_t size) {
    return static_cast<SkFILEStream *>(file_stream)->read(buffer, size);
}

bool SkFILEStream_isAtEnd(void *file_stream) {
    return static_cast<SkFILEStream *>(file_stream)->isAtEnd();
}

bool SkFILEStream_rewind(void *file_stream) {
    return static_cast<SkFILEStream *>(file_stream)->rewind();
}

sk_stream_asset_t SkFILEStream_duplicate(void *file_stream) {
    return static_sk_stream_asset_make(static_cast<SkFILEStream *>(file_stream)->duplicate());
}

size_t SkFILEStream_getPosition(void *file_stream) {
    return static_cast<SkFILEStream *>(file_stream)->getPosition();
}

bool SkFILEStream_seek(void *file_stream, size_t position) {
    return static_cast<SkFILEStream *>(file_stream)->seek(position);
}

bool SkFILEStream_move(void *file_stream, long offset) {
    return static_cast<SkFILEStream *>(file_stream)->move(offset);
}

sk_stream_asset_t SkFILEStream_fork(void *file_stream) {
    return static_sk_stream_asset_make(static_cast<SkFILEStream *>(file_stream)->fork());
}

size_t SkFILEStream_getLength(void *file_stream) {
    return static_cast<SkFILEStream *>(file_stream)->getLength();
}

bool SkFILEStream_hasLength(void *file_stream) {
    return static_cast<SkFILEStream *>(file_stream)->hasLength();
}

bool SkFILEStream_hasPosition(void *file_stream) {
    return static_cast<SkFILEStream *>(file_stream)->hasPosition();
}

size_t SkFILEStream_skip(void *file_stream, size_t size) {
    return static_cast<SkFILEStream *>(file_stream)->skip(size);
}

size_t SkFILEStream_peek(void *file_stream, void *ptr, size_t size) {
    return static_cast<SkFILEStream *>(file_stream)->peek(ptr, size);
}

bool SkFILEStream_readS8(void *file_stream, void *i) {
    return static_cast<SkFILEStream *>(file_stream)->readS8(static_cast<int8_t *>(i));
}

bool SkFILEStream_readS16(void *file_stream, void *i) {
    return static_cast<SkFILEStream *>(file_stream)->readS16(static_cast<int16_t *>(i));
}

bool SkFILEStream_readS32(void *file_stream, void *i) {
    return static_cast<SkFILEStream *>(file_stream)->readS32(static_cast<int32_t *>(i));
}

bool SkFILEStream_readU8(void *file_stream, void *i) {
    return static_cast<SkFILEStream *>(file_stream)->readU8(static_cast<uint8_t *>(i));
}

bool SkFILEStream_readU16(void *file_stream, void *i) {
    return static_cast<SkFILEStream *>(file_stream)->readU16(static_cast<uint16_t *>(i));
}

bool SkFILEStream_readU32(void *file_stream, void *i) {
    return static_cast<SkFILEStream *>(file_stream)->readU32(static_cast<uint32_t *>(i));
}

bool SkFILEStream_readBool(void *file_stream, void *b) {
    return static_cast<SkFILEStream *>(file_stream)->readBool(static_cast<bool *>(b));
}

bool SkFILEStream_readScalar(void *file_stream, void *scalar) {
    return static_cast<SkFILEStream *>(file_stream)->readScalar(static_cast<SkScalar *>(scalar));
}

bool SkFILEStream_readPackedUInt(void *file_stream, void *size) {
    return static_cast<SkFILEStream *>(file_stream)->readPackedUInt(static_cast<size_t *>(size));
}

const void * SkFILEStream_getMemoryBase(void *file_stream) {
    return static_cast<SkFILEStream *>(file_stream)->getMemoryBase();
}

// static

sk_file_stream_t SkFILEStream_Make(const char path[]) {
    return static_sk_file_stream_make(SkFILEStream::Make(path));
}

}
