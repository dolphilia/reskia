//
// Created by dolphilia on 2024/01/08.
//

#include "sk_file_w_stream.h"

#include "include/core/SkStream.h"

namespace {

SkFILEWStream *as_file_w_stream(reskia_file_w_stream_t *fileWStream) {
    return reinterpret_cast<SkFILEWStream *>(fileWStream);
}

bool has_buffer(const uint8_t *buffer, size_t size) {
    return size == 0 || buffer != nullptr;
}

}  // namespace

extern "C" {

reskia_file_w_stream_t *SkFILEWStream_new(const char path[]) {
    if (path == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_file_w_stream_t *>(new SkFILEWStream(path));
}

void SkFILEWStream_delete(reskia_file_w_stream_t *file_w_stream) {
    delete as_file_w_stream(file_w_stream);
}

bool SkFILEWStream_isValid(reskia_file_w_stream_t *file_w_stream) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->isValid();
}

bool SkFILEWStream_write(reskia_file_w_stream_t *file_w_stream, const uint8_t *buffer, size_t size) {
    return file_w_stream != nullptr && has_buffer(buffer, size) && as_file_w_stream(file_w_stream)->write(buffer, size);
}

void SkFILEWStream_flush(reskia_file_w_stream_t *file_w_stream) {
    if (file_w_stream == nullptr) {
        return;
    }
    as_file_w_stream(file_w_stream)->flush();
}

void SkFILEWStream_fsync(reskia_file_w_stream_t *file_w_stream) {
    if (file_w_stream == nullptr) {
        return;
    }
    as_file_w_stream(file_w_stream)->fsync();
}

size_t SkFILEWStream_bytesWritten(reskia_file_w_stream_t *file_w_stream) {
    if (file_w_stream == nullptr) {
        return 0;
    }
    return as_file_w_stream(file_w_stream)->bytesWritten();
}

bool SkFILEWStream_write8(reskia_file_w_stream_t *file_w_stream, uint8_t value) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->write8(value);
}

bool SkFILEWStream_write16(reskia_file_w_stream_t *file_w_stream, uint16_t value) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->write16(value);
}

bool SkFILEWStream_write32(reskia_file_w_stream_t *file_w_stream, uint32_t v) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->write32(v);
}

bool SkFILEWStream_writeText(reskia_file_w_stream_t *file_w_stream, const char text[]) {
    return file_w_stream != nullptr && text != nullptr && as_file_w_stream(file_w_stream)->writeText(text);
}

bool SkFILEWStream_newline(reskia_file_w_stream_t *file_w_stream) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->newline();
}

bool SkFILEWStream_writeDecAsText(reskia_file_w_stream_t *file_w_stream, int32_t v) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->writeDecAsText(v);
}

bool SkFILEWStream_writeBigDecAsText(reskia_file_w_stream_t *file_w_stream, int64_t v, int minDigits) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->writeBigDecAsText(v, minDigits);
}

bool SkFILEWStream_writeHexAsText(reskia_file_w_stream_t *file_w_stream, uint32_t v, int minDigits) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->writeHexAsText(v, minDigits);
}

bool SkFILEWStream_writeScalarAsText(reskia_file_w_stream_t *file_w_stream, float scalar) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->writeScalarAsText(scalar);
}

bool SkFILEWStream_writeBool(reskia_file_w_stream_t *file_w_stream, bool v) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->writeBool(v);
}

bool SkFILEWStream_writeScalar(reskia_file_w_stream_t *file_w_stream, float scalar) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->writeScalar(scalar);
}

bool SkFILEWStream_writePackedUInt(reskia_file_w_stream_t *file_w_stream, size_t size) {
    return file_w_stream != nullptr && as_file_w_stream(file_w_stream)->writePackedUInt(size);
}

bool SkFILEWStream_writeStream(reskia_file_w_stream_t *file_w_stream, reskia_stream_t *input, size_t length) {
    return file_w_stream != nullptr && input != nullptr && as_file_w_stream(file_w_stream)->writeStream(reinterpret_cast<SkStream *>(input), length);
}

// static

int SkFILEWStream_SizeOfPackedUInt(size_t value) {
    return SkFILEWStream::SizeOfPackedUInt(value);
}

}
