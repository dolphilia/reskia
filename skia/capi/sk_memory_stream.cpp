//
// Created by dolphilia on 2024/01/09.
//

#include "sk_memory_stream.h"

#include "include/core/SkStream.h"

#include "../handles/static_sk_memory_stream.h"
#include "../handles/static_sk_data.h"

#include "../handles/static_sk_memory_stream-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

reskia_memory_stream_t *SkMemoryStream_new() {
    return reinterpret_cast<reskia_memory_stream_t *>(new SkMemoryStream());
}

reskia_memory_stream_t *SkMemoryStream_new_2(size_t length) {
    return reinterpret_cast<reskia_memory_stream_t *>(new SkMemoryStream(length));
}

reskia_memory_stream_t *SkMemoryStream_new_3(const uint8_t *data, size_t length, bool copyData) {
    return reinterpret_cast<reskia_memory_stream_t *>(new SkMemoryStream(data, length, copyData));
}

reskia_memory_stream_t *SkMemoryStream_new_4(sk_data_t data) {
    return reinterpret_cast<reskia_memory_stream_t *>(new SkMemoryStream(static_sk_data_get_entity(data)));
}

void SkMemoryStream_delete(reskia_memory_stream_t *memory_stream) {
    delete reinterpret_cast<SkMemoryStream *>(memory_stream);
}

void SkMemoryStream_setMemory(reskia_memory_stream_t *memory_stream, const uint8_t *data, size_t length, bool copyData) {
    reinterpret_cast<SkMemoryStream *>(memory_stream)->setMemory(data, length, copyData);
}

void SkMemoryStream_setMemoryOwned(reskia_memory_stream_t *memory_stream, const uint8_t *data, size_t length) {
    reinterpret_cast<SkMemoryStream *>(memory_stream)->setMemoryOwned(data, length);
}

sk_data_t SkMemoryStream_asData(reskia_memory_stream_t *memory_stream) {
    return static_sk_data_make(reinterpret_cast<SkMemoryStream *>(memory_stream)->asData());
}

void SkMemoryStream_setData(reskia_memory_stream_t *memory_stream, sk_data_t data) {
    reinterpret_cast<SkMemoryStream *>(memory_stream)->setData(static_sk_data_get_entity(data));
}

void SkMemoryStream_skipToAlign4(reskia_memory_stream_t *memory_stream) {
    reinterpret_cast<SkMemoryStream *>(memory_stream)->skipToAlign4();
}

const uint8_t * SkMemoryStream_getAtPos(reskia_memory_stream_t *memory_stream) {
    return reinterpret_cast<const uint8_t *>(reinterpret_cast<SkMemoryStream *>(memory_stream)->getAtPos());
}

size_t SkMemoryStream_read(reskia_memory_stream_t *memory_stream, uint8_t *buffer, size_t size) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->read(buffer, size);
}

bool SkMemoryStream_isAtEnd(reskia_memory_stream_t *memory_stream) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->isAtEnd();
}

size_t SkMemoryStream_peek(reskia_memory_stream_t *memory_stream, uint8_t *buffer, size_t size) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->peek(buffer, size);
}

bool SkMemoryStream_rewind(reskia_memory_stream_t *memory_stream) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->rewind();
}

sk_memory_stream_t SkMemoryStream_duplicate(reskia_memory_stream_t *memory_stream) {
    return static_sk_memory_stream_make(reinterpret_cast<SkMemoryStream *>(memory_stream)->duplicate());
}

size_t SkMemoryStream_getPosition(reskia_memory_stream_t *memory_stream) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->getPosition();
}

bool SkMemoryStream_seek(reskia_memory_stream_t *memory_stream, size_t position) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->seek(position);
}

bool SkMemoryStream_move(reskia_memory_stream_t *memory_stream, long offset) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->move(offset);
}

sk_memory_stream_t SkMemoryStream_fork(reskia_memory_stream_t *memory_stream) {
    return static_sk_memory_stream_make(reinterpret_cast<SkMemoryStream *>(memory_stream)->fork());
}

size_t SkMemoryStream_getLength(reskia_memory_stream_t *memory_stream) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->getLength();
}

const uint8_t * SkMemoryStream_getMemoryBase(reskia_memory_stream_t *memory_stream) {
    return reinterpret_cast<const uint8_t *>(reinterpret_cast<SkMemoryStream *>(memory_stream)->getMemoryBase());
}

bool SkMemoryStream_hasLength(reskia_memory_stream_t *memory_stream) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->hasLength();
}

bool SkMemoryStream_hasPosition(reskia_memory_stream_t *memory_stream) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->hasPosition();
}

size_t SkMemoryStream_skip(reskia_memory_stream_t *memory_stream, size_t size) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->skip(size);
}

bool SkMemoryStream_readS8(reskia_memory_stream_t *memory_stream, int8_t *i) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readS8(i);
}

bool SkMemoryStream_readS16(reskia_memory_stream_t *memory_stream, int16_t *i) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readS16(i);
}

bool SkMemoryStream_readS32(reskia_memory_stream_t *memory_stream, int32_t *i) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readS32(i);
}

bool SkMemoryStream_readU8(reskia_memory_stream_t *memory_stream, uint8_t *i) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readU8(i);
}

bool SkMemoryStream_readU16(reskia_memory_stream_t *memory_stream, uint16_t *i) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readU16(i);
}

bool SkMemoryStream_readU32(reskia_memory_stream_t *memory_stream, uint32_t *i) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readU32(i);
}

bool SkMemoryStream_readBool(reskia_memory_stream_t *memory_stream, bool *b) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readBool(b);
}

bool SkMemoryStream_readScalar(reskia_memory_stream_t *memory_stream, float *v) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readScalar(v);
}

bool SkMemoryStream_readPackedUInt(reskia_memory_stream_t *memory_stream, size_t *size) {
    return reinterpret_cast<SkMemoryStream *>(memory_stream)->readPackedUInt(size);
}

// static

sk_memory_stream_t SkMemoryStream_MakeCopy(const uint8_t *data, size_t length) {
    return static_sk_memory_stream_make(SkMemoryStream::MakeCopy(data, length));
}

sk_memory_stream_t SkMemoryStream_MakeDirect(const uint8_t *data, size_t length) {
    return static_sk_memory_stream_make(SkMemoryStream::MakeDirect(data, length));
}

sk_memory_stream_t SkMemoryStream_Make(sk_data_t data) {
    return static_sk_memory_stream_make(SkMemoryStream::Make(static_sk_data_get_entity(data)));
}

}
