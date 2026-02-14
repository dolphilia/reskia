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

reskia_dynamic_memory_w_stream_t *SkDynamicMemoryWStream_new() {
    return reinterpret_cast<reskia_dynamic_memory_w_stream_t *>(new SkDynamicMemoryWStream());
}

//SkDynamicMemoryWStream * SkDynamicMemoryWStream_new_2(SkDynamicMemoryWStream &&stream) {
//    return new SkDynamicMemoryWStream(&stream);
//}

void SkDynamicMemoryWStream_delete(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream) {
    delete reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream);
}

bool SkDynamicMemoryWStream_write(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, const uint8_t *buffer, size_t size) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->write(buffer, size);
}

size_t SkDynamicMemoryWStream_bytesWritten(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->bytesWritten();
}

bool SkDynamicMemoryWStream_read(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint8_t *buffer, size_t offset, size_t size) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->read(buffer, offset, size);
}

void SkDynamicMemoryWStream_copyTo(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint8_t *dst) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->copyTo(dst);
}

bool SkDynamicMemoryWStream_writeToStream(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_w_stream_t *dst) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeToStream(reinterpret_cast<SkWStream *>(dst));
}

void SkDynamicMemoryWStream_copyToAndReset(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint8_t *dst) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->copyToAndReset(dst);
}

bool SkDynamicMemoryWStream_writeToAndReset(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_w_stream_t *dst) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeToAndReset(reinterpret_cast<SkWStream *>(dst));
}

bool SkDynamicMemoryWStream_writeToAndReset_2(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_dynamic_memory_w_stream_t *dst) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeToAndReset(reinterpret_cast<SkDynamicMemoryWStream *>(dst));
}

void SkDynamicMemoryWStream_prependToAndReset(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_dynamic_memory_w_stream_t *dst) {
    reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->prependToAndReset(reinterpret_cast<SkDynamicMemoryWStream *>(dst));
}

sk_data_t SkDynamicMemoryWStream_detachAsData(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream) {
    return static_sk_data_make(reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->detachAsData());
}

sk_stream_asset_t SkDynamicMemoryWStream_detachAsStream(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream) {
    return static_sk_stream_asset_make(reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->detachAsStream());
}

void SkDynamicMemoryWStream_reset(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream) {
    reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->reset();
}

void SkDynamicMemoryWStream_padToAlign4(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream) {
    reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->padToAlign4();
}

void SkDynamicMemoryWStream_flush(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream) {
    reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->flush();
}

bool SkDynamicMemoryWStream_write8(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint8_t value) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->write8(value);
}

bool SkDynamicMemoryWStream_write16(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint16_t value) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->write16(value);
}

bool SkDynamicMemoryWStream_write32(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint32_t v) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->write32(v);
}

bool SkDynamicMemoryWStream_writeText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, const char text[]) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeText(text);
}

bool SkDynamicMemoryWStream_newline(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->newline();
}

bool SkDynamicMemoryWStream_writeDecAsText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, int32_t v) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeDecAsText(v);
}

bool SkDynamicMemoryWStream_writeBigDecAsText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, int64_t v, int minDigits) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeBigDecAsText(v, minDigits);
}

bool SkDynamicMemoryWStream_writeHexAsText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint32_t v, int minDigits) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeHexAsText(v, minDigits);
}

bool SkDynamicMemoryWStream_writeScalarAsText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, float scalar) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeScalarAsText(scalar);
}

bool SkDynamicMemoryWStream_writeBool(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, bool v) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeBool(v);
}

bool SkDynamicMemoryWStream_writeScalar(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, float scalar) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeScalar(scalar);
}

bool SkDynamicMemoryWStream_writePackedUInt(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, size_t length) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writePackedUInt(length);
}

bool SkDynamicMemoryWStream_writeStream(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_stream_t *input, size_t length) {
    return reinterpret_cast<SkDynamicMemoryWStream *>(dynamic_memory_w_stream)->writeStream(reinterpret_cast<SkStream *>(input), length);
}

// static

int SkDynamicMemoryWStream_SizeOfPackedUInt(size_t value) {
    return SkDynamicMemoryWStream::SizeOfPackedUInt(value);
}

}
