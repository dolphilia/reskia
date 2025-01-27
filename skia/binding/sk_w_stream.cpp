//
// Created by dolphilia on 2024/01/11.
//

#include "sk_w_stream.h"

#include "include/core/SkStream.h"

extern "C" {

void SkWStream_delete(void *w_stream) {
    delete static_cast<SkWStream *>(w_stream);
}

bool SkWStream_write(void *w_stream, const void *buffer, size_t size) {
    return static_cast<SkWStream *>(w_stream)->write(buffer, size);
}

void SkWStream_flush(void *w_stream) {
    return static_cast<SkWStream *>(w_stream)->flush();
}

size_t SkWStream_bytesWritten(void *w_stream) {
    return static_cast<SkWStream *>(w_stream)->bytesWritten();
}

bool SkWStream_write8(void *w_stream, unsigned int value) {
    return static_cast<SkWStream *>(w_stream)->write8(value);
}

bool SkWStream_write16(void *w_stream, unsigned int value) {
    return static_cast<SkWStream *>(w_stream)->write16(value);
}

bool SkWStream_write32(void *w_stream, uint32_t v) {
    return static_cast<SkWStream *>(w_stream)->write32(v);
}

bool SkWStream_writeText(void *w_stream, const char text[]) {
    return static_cast<SkWStream *>(w_stream)->writeText(text);
}

bool SkWStream_newline(void *w_stream) {
    return static_cast<SkWStream *>(w_stream)->newline();
}

bool SkWStream_writeDecAsText(void *w_stream, int32_t i) {
    return static_cast<SkWStream *>(w_stream)->writeDecAsText(i);
}

bool SkWStream_writeBigDecAsText(void *w_stream, int64_t i, int minDigits) {
    return static_cast<SkWStream *>(w_stream)->writeBigDecAsText(i, minDigits);
}

bool SkWStream_writeHexAsText(void *w_stream, uint32_t i, int minDigits) {
    return static_cast<SkWStream *>(w_stream)->writeHexAsText(i, minDigits);
}

bool SkWStream_writeScalarAsText(void *w_stream, float v) {
    return static_cast<SkWStream *>(w_stream)->writeScalarAsText(v);
}

bool SkWStream_writeBool(void *w_stream, bool v) {
    return static_cast<SkWStream *>(w_stream)->writeBool(v);
}

bool SkWStream_writeScalar(void *w_stream, float v) {
    return static_cast<SkWStream *>(w_stream)->writeScalar(v);
}

bool SkWStream_writePackedUInt(void *w_stream, size_t size) {
    return static_cast<SkWStream *>(w_stream)->writePackedUInt(size);
}

bool SkWStream_writeStream(void *w_stream, void *input, size_t length) {
    return static_cast<SkWStream *>(w_stream)->writeStream(static_cast<SkStream *>(input), length);
}

// static

int SkWStream_SizeOfPackedUInt(size_t value) {
    return SkWStream::SizeOfPackedUInt(value);
}

}