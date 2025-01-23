//
// Created by dolphilia on 2024/01/09.
//

#include "sk_memory_stream.h"

#include "include/core/SkStream.h"

#include "../static/static_sk_memory_stream.h"
#include "../static/static_sk_data.h"

#include "../static/static_sk_memory_stream-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void *SkMemoryStream_new() {
    return new SkMemoryStream();
}

void *SkMemoryStream_new_2(size_t length) {
    return new SkMemoryStream(length);
}

void *SkMemoryStream_new_3(const void *data, size_t length, bool copyData) {
    return new SkMemoryStream(data, length, copyData);
}

void *SkMemoryStream_new_4(sk_data_t data) {
    return new SkMemoryStream(static_sk_data_move(data));
}

void SkMemoryStream_delete(void *memoryStream) {
    delete static_cast<SkMemoryStream *>(memoryStream);
}

void SkMemoryStream_setMemory(void *memory_stream, const void *data, size_t length, bool copyData) {
    static_cast<SkMemoryStream *>(memory_stream)->setMemory(data, length, copyData);
}

void SkMemoryStream_setMemoryOwned(void *memory_stream, const void *data, size_t length) {
    static_cast<SkMemoryStream *>(memory_stream)->setMemoryOwned(data, length);
}

sk_data_t SkMemoryStream_asData(void *memory_stream) {
    return static_sk_data_make(static_cast<SkMemoryStream *>(memory_stream)->asData());
}

void SkMemoryStream_setData(void *memory_stream, sk_data_t data) {
    static_cast<SkMemoryStream *>(memory_stream)->setData(static_sk_data_move(data));
}

void SkMemoryStream_skipToAlign4(void *memory_stream) {
    static_cast<SkMemoryStream *>(memory_stream)->skipToAlign4();
}

const void * SkMemoryStream_getAtPos(void *memory_stream) {
    return static_cast<SkMemoryStream *>(memory_stream)->getAtPos();
}

size_t SkMemoryStream_read(void *memory_stream, void *buffer, size_t size) {
    return static_cast<SkMemoryStream *>(memory_stream)->read(buffer, size);
}

bool SkMemoryStream_isAtEnd(void *memory_stream) {
    return static_cast<SkMemoryStream *>(memory_stream)->isAtEnd();
}

size_t SkMemoryStream_peek(void *memory_stream, void *buffer, size_t size) {
    return static_cast<SkMemoryStream *>(memory_stream)->peek(buffer, size);
}

bool SkMemoryStream_rewind(void *memory_stream) {
    return static_cast<SkMemoryStream *>(memory_stream)->rewind();
}

sk_memory_stream_t SkMemoryStream_duplicate(void *memory_stream) {
    return static_sk_memory_stream_make(static_cast<SkMemoryStream *>(memory_stream)->duplicate());
}

size_t SkMemoryStream_getPosition(void *memory_stream) {
    return static_cast<SkMemoryStream *>(memory_stream)->getPosition();
}

bool SkMemoryStream_seek(void *memory_stream, size_t position) {
    return static_cast<SkMemoryStream *>(memory_stream)->seek(position);
}

bool SkMemoryStream_move(void *memory_stream, long offset) {
    return static_cast<SkMemoryStream *>(memory_stream)->move(offset);
}

sk_memory_stream_t SkMemoryStream_fork(void *memory_stream) {
    return static_sk_memory_stream_make(static_cast<SkMemoryStream *>(memory_stream)->fork());
}

size_t SkMemoryStream_getLength(void *memory_stream) {
    return static_cast<SkMemoryStream *>(memory_stream)->getLength();
}

const void * SkMemoryStream_getMemoryBase(void *memory_stream) {
    return static_cast<SkMemoryStream *>(memory_stream)->getMemoryBase();
}

bool SkMemoryStream_hasLength(void *memory_stream) {
    return static_cast<SkMemoryStream *>(memory_stream)->hasLength();
}

bool SkMemoryStream_hasPosition(void *memory_stream) {
    return static_cast<SkMemoryStream *>(memory_stream)->hasPosition();
}

size_t SkMemoryStream_skip(void *memory_stream, size_t size) {
    return static_cast<SkMemoryStream *>(memory_stream)->skip(size);
}

bool SkMemoryStream_readS8(void *memory_stream, void *i) {
    return static_cast<SkMemoryStream *>(memory_stream)->readS8(static_cast<int8_t *>(i));
}

bool SkMemoryStream_readS16(void *memory_stream, void *i) {
    return static_cast<SkMemoryStream *>(memory_stream)->readS16(static_cast<int16_t *>(i));
}

bool SkMemoryStream_readS32(void *memory_stream, void *i) {
    return static_cast<SkMemoryStream *>(memory_stream)->readS32(static_cast<int32_t *>(i));
}

bool SkMemoryStream_readU8(void *memory_stream, void *i) {
    return static_cast<SkMemoryStream *>(memory_stream)->readU8(static_cast<uint8_t *>(i));
}

bool SkMemoryStream_readU16(void *memory_stream, void *i) {
    return static_cast<SkMemoryStream *>(memory_stream)->readU16(static_cast<uint16_t *>(i));
}

bool SkMemoryStream_readU32(void *memory_stream, void *i) {
    return static_cast<SkMemoryStream *>(memory_stream)->readU32(static_cast<uint32_t *>(i));
}

bool SkMemoryStream_readBool(void *memory_stream, void *b) {
    return static_cast<SkMemoryStream *>(memory_stream)->readBool(static_cast<bool *>(b));
}

bool SkMemoryStream_readScalar(void *memory_stream, void *v) {
    return static_cast<SkMemoryStream *>(memory_stream)->readScalar(static_cast<SkScalar *>(v));
}

bool SkMemoryStream_readPackedUInt(void *memory_stream, void *size) {
    return static_cast<SkMemoryStream *>(memory_stream)->readPackedUInt(static_cast<size_t *>(size));
}

// static

sk_memory_stream_t SkMemoryStream_MakeCopy(const void *data, size_t length) {
    return static_sk_memory_stream_make(SkMemoryStream::MakeCopy(data, length));
}

sk_memory_stream_t SkMemoryStream_MakeDirect(const void *data, size_t length) {
    return static_sk_memory_stream_make(SkMemoryStream::MakeDirect(data, length));
}

sk_memory_stream_t SkMemoryStream_Make(sk_data_t data) {
    return static_sk_memory_stream_make(SkMemoryStream::Make(static_sk_data_move(data)));
}

}
