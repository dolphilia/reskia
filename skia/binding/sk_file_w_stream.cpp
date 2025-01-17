//
// Created by dolphilia on 2024/01/08.
//

#include "sk_file_w_stream.h"

#include "include/core/SkStream.h"

extern "C" {

void *SkFILEWStream_new(const char path[]) {
    return new SkFILEWStream(path);
}

void SkFILEWStream_delete(void *file_w_stream) {
    delete static_cast<SkFILEWStream *>(file_w_stream);
}

bool SkFILEWStream_isValid(void *file_w_stream) {
    return static_cast<SkFILEWStream *>(file_w_stream)->isValid();
}

bool SkFILEWStream_write(void *file_w_stream, const void *buffer, size_t size) {
    return static_cast<SkFILEWStream *>(file_w_stream)->write(buffer, size);
}

void SkFILEWStream_flush(void *file_w_stream) {
    static_cast<SkFILEWStream *>(file_w_stream)->flush();
}

void SkFILEWStream_fsync(void *file_w_stream) {
    return static_cast<SkFILEWStream *>(file_w_stream)->fsync();
}

size_t SkFILEWStream_bytesWritten(void *file_w_stream) {
    return static_cast<SkFILEWStream *>(file_w_stream)->bytesWritten();
}

bool SkFILEWStream_write8(void *file_w_stream, unsigned int value) {
    return static_cast<SkFILEWStream *>(file_w_stream)->write8(value);
}

bool SkFILEWStream_write16(void *file_w_stream, unsigned int value) {
    return static_cast<SkFILEWStream *>(file_w_stream)->write16(value);
}

bool SkFILEWStream_write32(void *file_w_stream, uint32_t v) {
    return static_cast<SkFILEWStream *>(file_w_stream)->write32(v);
}

bool SkFILEWStream_writeText(void *file_w_stream, const char text[]) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writeText(text);
}

bool SkFILEWStream_newline(void *file_w_stream) {
    return static_cast<SkFILEWStream *>(file_w_stream)->newline();
}

bool SkFILEWStream_writeDecAsText(void *file_w_stream, int32_t v) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writeDecAsText(v);
}

bool SkFILEWStream_writeBigDecAsText(void *file_w_stream, int64_t v, int minDigits) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writeBigDecAsText(v, minDigits);
}

bool SkFILEWStream_writeHexAsText(void *file_w_stream, uint32_t v, int minDigits) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writeHexAsText(v, minDigits);
}

bool SkFILEWStream_writeScalarAsText(void *file_w_stream, float scalar) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writeScalarAsText(scalar);
}

bool SkFILEWStream_writeBool(void *file_w_stream, bool v) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writeBool(v);
}

bool SkFILEWStream_writeScalar(void *file_w_stream, float scalar) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writeScalar(scalar);
}

bool SkFILEWStream_writePackedUInt(void *file_w_stream, size_t size) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writePackedUInt(size);
}

bool SkFILEWStream_writeStream(void *file_w_stream, void *input, size_t length) {
    return static_cast<SkFILEWStream *>(file_w_stream)->writeStream(static_cast<SkStream *>(input), length);
}

// static

int SkFILEWStream_SizeOfPackedUInt(size_t value) {
    return SkFILEWStream::SizeOfPackedUInt(value);
}

}