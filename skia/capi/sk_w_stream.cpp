//
// Created by dolphilia on 2024/01/11.
//

#include "sk_w_stream.h"

#include "include/core/SkStream.h"

extern "C" {

void SkWStream_delete(reskia_w_stream_t *w_stream) {
    delete reinterpret_cast<SkWStream *>(w_stream);
}

bool SkWStream_write(reskia_w_stream_t *w_stream, const void *buffer, size_t size) {
    return reinterpret_cast<SkWStream *>(w_stream)->write(buffer, size);
}

void SkWStream_flush(reskia_w_stream_t *w_stream) {
    return reinterpret_cast<SkWStream *>(w_stream)->flush();
}

size_t SkWStream_bytesWritten(reskia_w_stream_t *w_stream) {
    return reinterpret_cast<SkWStream *>(w_stream)->bytesWritten();
}

bool SkWStream_write8(reskia_w_stream_t *w_stream, uint32_t value) {
    return reinterpret_cast<SkWStream *>(w_stream)->write8(value);
}

bool SkWStream_write16(reskia_w_stream_t *w_stream, uint32_t value) {
    return reinterpret_cast<SkWStream *>(w_stream)->write16(value);
}

bool SkWStream_write32(reskia_w_stream_t *w_stream, uint32_t v) {
    return reinterpret_cast<SkWStream *>(w_stream)->write32(v);
}

bool SkWStream_writeText(reskia_w_stream_t *w_stream, const char text[]) {
    return reinterpret_cast<SkWStream *>(w_stream)->writeText(text);
}

bool SkWStream_newline(reskia_w_stream_t *w_stream) {
    return reinterpret_cast<SkWStream *>(w_stream)->newline();
}

bool SkWStream_writeDecAsText(reskia_w_stream_t *w_stream, int32_t i) {
    return reinterpret_cast<SkWStream *>(w_stream)->writeDecAsText(i);
}

bool SkWStream_writeBigDecAsText(reskia_w_stream_t *w_stream, int64_t i, int minDigits) {
    return reinterpret_cast<SkWStream *>(w_stream)->writeBigDecAsText(i, minDigits);
}

bool SkWStream_writeHexAsText(reskia_w_stream_t *w_stream, uint32_t i, int minDigits) {
    return reinterpret_cast<SkWStream *>(w_stream)->writeHexAsText(i, minDigits);
}

bool SkWStream_writeScalarAsText(reskia_w_stream_t *w_stream, float v) {
    return reinterpret_cast<SkWStream *>(w_stream)->writeScalarAsText(v);
}

bool SkWStream_writeBool(reskia_w_stream_t *w_stream, bool v) {
    return reinterpret_cast<SkWStream *>(w_stream)->writeBool(v);
}

bool SkWStream_writeScalar(reskia_w_stream_t *w_stream, float v) {
    return reinterpret_cast<SkWStream *>(w_stream)->writeScalar(v);
}

bool SkWStream_writePackedUInt(reskia_w_stream_t *w_stream, size_t size) {
    return reinterpret_cast<SkWStream *>(w_stream)->writePackedUInt(size);
}

bool SkWStream_writeStream(reskia_w_stream_t *w_stream, reskia_stream_t *input, size_t length) {
    return reinterpret_cast<SkWStream *>(w_stream)->writeStream(reinterpret_cast<SkStream *>(input), length);
}

// static

int SkWStream_SizeOfPackedUInt(size_t value) {
    return SkWStream::SizeOfPackedUInt(value);
}

}
