//
// Created by dolphilia on 2024/01/08.
//

#include "sk_dynamic_memory_w_stream.h"

#include "include/core/SkStream.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_stream_asset.h"

#include "../static/static_sk_stream_asset-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void *SkDynamicMemoryWStream_new() {
    return new SkDynamicMemoryWStream();
}

//SkDynamicMemoryWStream * SkDynamicMemoryWStream_new_2(SkDynamicMemoryWStream &&stream) {
//    return new SkDynamicMemoryWStream(&stream);
//}

void SkDynamicMemoryWStream_delete(void *dynamic_memory_w_stream) {
    delete static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream);
}

bool SkDynamicMemoryWStream_write(void *dynamic_memory_w_stream, const void *buffer, size_t size) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->write(buffer, size);
}

size_t SkDynamicMemoryWStream_bytesWritten(void *dynamic_memory_w_stream) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->bytesWritten();
}

bool SkDynamicMemoryWStream_read(void *dynamic_memory_w_stream, void *buffer, size_t offset, size_t size) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->read(buffer, offset, size);
}

void SkDynamicMemoryWStream_copyTo(void *dynamic_memory_w_stream, void *dst) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->copyTo(dst);
}

bool SkDynamicMemoryWStream_writeToStream(void *dynamic_memory_w_stream, void *dst) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeToStream(static_cast<SkWStream *>(dst));
}

void SkDynamicMemoryWStream_copyToAndReset(void *dynamic_memory_w_stream, void *dst) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->copyToAndReset(dst);
}

bool SkDynamicMemoryWStream_writeToAndReset(void *dynamic_memory_w_stream, void *dst) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeToAndReset(static_cast<SkWStream *>(dst));
}

bool SkDynamicMemoryWStream_writeToAndReset_2(void *dynamic_memory_w_stream, void *dst) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeToAndReset(static_cast<SkDynamicMemoryWStream *>(dst));
}

void SkDynamicMemoryWStream_prependToAndReset(void *dynamic_memory_w_stream, void *dst) {
    static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->prependToAndReset(static_cast<SkDynamicMemoryWStream *>(dst));
}

sk_data_t SkDynamicMemoryWStream_detachAsData(void *dynamic_memory_w_stream) {
    return static_sk_data_make(static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->detachAsData());
}

sk_stream_asset_t SkDynamicMemoryWStream_detachAsStream(void *dynamic_memory_w_stream) {
    return static_sk_stream_asset_make(static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->detachAsStream());
}

void SkDynamicMemoryWStream_reset(void *dynamic_memory_w_stream) {
    static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->reset();
}

void SkDynamicMemoryWStream_padToAlign4(void *dynamic_memory_w_stream) {
    static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->padToAlign4();
}

void SkDynamicMemoryWStream_flush(void *dynamic_memory_w_stream) {
    static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->flush();
}

bool SkDynamicMemoryWStream_write8(void *dynamic_memory_w_stream, unsigned int value) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->write8(value);
}

bool SkDynamicMemoryWStream_write16(void *dynamic_memory_w_stream, unsigned int value) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->write16(value);
}

bool SkDynamicMemoryWStream_write32(void *dynamic_memory_w_stream, uint32_t v) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->write32(v);
}

bool SkDynamicMemoryWStream_writeText(void *dynamic_memory_w_stream, const char text[]) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeText(text);
}

bool SkDynamicMemoryWStream_newline(void *dynamic_memory_w_stream) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->newline();
}

bool SkDynamicMemoryWStream_writeDecAsText(void *dynamic_memory_w_stream, int32_t v) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeDecAsText(v);
}

bool SkDynamicMemoryWStream_writeBigDecAsText(void *dynamic_memory_w_stream, int64_t v, int minDigits) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeBigDecAsText(v, minDigits);
}

bool SkDynamicMemoryWStream_writeHexAsText(void *dynamic_memory_w_stream, uint32_t v, int minDigits) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeHexAsText(v, minDigits);
}

bool SkDynamicMemoryWStream_writeScalarAsText(void *dynamic_memory_w_stream, float scalar) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeScalarAsText(scalar);
}

bool SkDynamicMemoryWStream_writeBool(void *dynamic_memory_w_stream, bool v) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeBool(v);
}

bool SkDynamicMemoryWStream_writeScalar(void *dynamic_memory_w_stream, float scalar) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeScalar(scalar);
}

bool SkDynamicMemoryWStream_writePackedUInt(void *dynamic_memory_w_stream, size_t length) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writePackedUInt(length);
}

bool SkDynamicMemoryWStream_writeStream(void *dynamic_memory_w_stream, void *input, size_t length) {
    return static_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeStream(static_cast<SkStream *>(input), length);
}

// static

int SkDynamicMemoryWStream_SizeOfPackedUInt(size_t value) {
    return SkDynamicMemoryWStream::SizeOfPackedUInt(value);
}

}
