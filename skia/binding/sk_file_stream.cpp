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

reskia_file_stream_t *SkFILEStream_new(const char path[]) {
    return reinterpret_cast<reskia_file_stream_t *>(new SkFILEStream(path));
}

reskia_file_stream_t *SkFILEStream_new_2(reskia_file_t *file) {
    return reinterpret_cast<reskia_file_stream_t *>(new SkFILEStream(reinterpret_cast<FILE *>(file)));
}

reskia_file_stream_t *SkFILEStream_new_3(reskia_file_t *file, size_t size) {
    return reinterpret_cast<reskia_file_stream_t *>(new SkFILEStream(reinterpret_cast<FILE *>(file), size));
}

void SkFILEStream_delete(reskia_file_stream_t *file_stream) {
    delete reinterpret_cast<SkFILEStream *>(file_stream);
}

bool SkFILEStream_isValid(reskia_file_stream_t *file_stream) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->isValid();
}

void SkFILEStream_close(reskia_file_stream_t *file_stream) {
    reinterpret_cast<SkFILEStream *>(file_stream)->close();
}

size_t SkFILEStream_read(reskia_file_stream_t *file_stream, uint8_t *buffer, size_t size) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->read(buffer, size);
}

bool SkFILEStream_isAtEnd(reskia_file_stream_t *file_stream) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->isAtEnd();
}

bool SkFILEStream_rewind(reskia_file_stream_t *file_stream) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->rewind();
}

sk_stream_asset_t SkFILEStream_duplicate(reskia_file_stream_t *file_stream) {
    return static_sk_stream_asset_make(reinterpret_cast<SkFILEStream *>(file_stream)->duplicate());
}

size_t SkFILEStream_getPosition(reskia_file_stream_t *file_stream) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->getPosition();
}

bool SkFILEStream_seek(reskia_file_stream_t *file_stream, size_t position) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->seek(position);
}

bool SkFILEStream_move(reskia_file_stream_t *file_stream, long offset) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->move(offset);
}

sk_stream_asset_t SkFILEStream_fork(reskia_file_stream_t *file_stream) {
    return static_sk_stream_asset_make(reinterpret_cast<SkFILEStream *>(file_stream)->fork());
}

size_t SkFILEStream_getLength(reskia_file_stream_t *file_stream) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->getLength();
}

bool SkFILEStream_hasLength(reskia_file_stream_t *file_stream) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->hasLength();
}

bool SkFILEStream_hasPosition(reskia_file_stream_t *file_stream) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->hasPosition();
}

size_t SkFILEStream_skip(reskia_file_stream_t *file_stream, size_t size) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->skip(size);
}

size_t SkFILEStream_peek(reskia_file_stream_t *file_stream, uint8_t *ptr, size_t size) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->peek(ptr, size);
}

bool SkFILEStream_readS8(reskia_file_stream_t *file_stream, int8_t *i) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readS8(i);
}

bool SkFILEStream_readS16(reskia_file_stream_t *file_stream, int16_t *i) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readS16(i);
}

bool SkFILEStream_readS32(reskia_file_stream_t *file_stream, int32_t *i) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readS32(i);
}

bool SkFILEStream_readU8(reskia_file_stream_t *file_stream, uint8_t *i) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readU8(i);
}

bool SkFILEStream_readU16(reskia_file_stream_t *file_stream, uint16_t *i) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readU16(i);
}

bool SkFILEStream_readU32(reskia_file_stream_t *file_stream, uint32_t *i) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readU32(i);
}

bool SkFILEStream_readBool(reskia_file_stream_t *file_stream, bool *b) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readBool(b);
}

bool SkFILEStream_readScalar(reskia_file_stream_t *file_stream, float *scalar) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readScalar(scalar);
}

bool SkFILEStream_readPackedUInt(reskia_file_stream_t *file_stream, size_t *size) {
    return reinterpret_cast<SkFILEStream *>(file_stream)->readPackedUInt(size);
}

const uint8_t * SkFILEStream_getMemoryBase(reskia_file_stream_t *file_stream) {
    return reinterpret_cast<const uint8_t *>(reinterpret_cast<SkFILEStream *>(file_stream)->getMemoryBase());
}

// static

sk_file_stream_t SkFILEStream_Make(const char path[]) {
    return static_sk_file_stream_make(SkFILEStream::Make(path));
}

}
