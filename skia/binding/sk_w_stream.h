//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_W_STREAM_H
#define RAIA_SKIA_SK_W_STREAM_H

#include "include/core/SkStream.h"

extern "C" {

void SkWStream_delete(SkWStream *w_stream); // (SkWStream *w_stream)
bool SkWStream_write(SkWStream *w_stream, const void *buffer, size_t size); // (SkWStream *w_stream, const void *buffer, size_t size) -> bool
void SkWStream_flush(SkWStream *w_stream); // (SkWStream *w_stream)
size_t SkWStream_bytesWritten(SkWStream *w_stream); // (SkWStream *w_stream) -> size_t
bool SkWStream_write8(SkWStream *w_stream, U8CPU value); // (SkWStream *w_stream, U8CPU value) -> bool
bool SkWStream_write16(SkWStream *w_stream, U16CPU value); // (SkWStream *w_stream, U16CPU value) -> bool
bool SkWStream_write32(SkWStream *w_stream, uint32_t v); // (SkWStream *w_stream, uint32_t v) -> bool
bool SkWStream_writeText(SkWStream *w_stream, const char text[]); // (SkWStream *w_stream, const char text[]) -> bool
bool SkWStream_newline(SkWStream *w_stream); // (SkWStream *w_stream) -> bool
bool SkWStream_writeDecAsText(SkWStream *w_stream, int32_t i); // (SkWStream *w_stream, int32_t i) -> bool
bool SkWStream_writeBigDecAsText(SkWStream *w_stream, int64_t i, int minDigits); // (SkWStream *w_stream, int64_t i, int minDigits) -> bool
bool SkWStream_writeHexAsText(SkWStream *w_stream, uint32_t i, int minDigits); // (SkWStream *w_stream, uint32_t i, int minDigits) -> bool
bool SkWStream_writeScalarAsText(SkWStream *w_stream, SkScalar v); // (SkWStream *w_stream, SkScalar v) -> bool
bool SkWStream_writeBool(SkWStream *w_stream, bool v); // (SkWStream *w_stream, bool v) -> bool
bool SkWStream_writeScalar(SkWStream *w_stream, SkScalar v); // (SkWStream *w_stream, SkScalar v) -> bool
bool SkWStream_writePackedUInt(SkWStream *w_stream, size_t size); // (SkWStream *w_stream, size_t size) -> bool
bool SkWStream_writeStream(SkWStream *w_stream, SkStream *input, size_t length); // (SkWStream *w_stream, SkStream *input, size_t length) -> bool

// static

int SkWStream_SizeOfPackedUInt(size_t value); // (size_t value) -> int

}

#endif //RAIA_SKIA_SK_W_STREAM_H
