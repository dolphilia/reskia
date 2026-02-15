//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_W_STREAM_H
#define RAIA_SKIA_SK_W_STREAM_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_stream_t reskia_stream_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkWStream_delete(reskia_w_stream_t *w_stream); // (SkWStream *w_stream)
bool SkWStream_write(reskia_w_stream_t *w_stream, const void *buffer, size_t size); // (SkWStream *w_stream, const void *buffer, size_t size) -> bool
void SkWStream_flush(reskia_w_stream_t *w_stream); // (SkWStream *w_stream)
size_t SkWStream_bytesWritten(reskia_w_stream_t *w_stream); // (SkWStream *w_stream) -> size_t
bool SkWStream_write8(reskia_w_stream_t *w_stream, uint32_t value); // (SkWStream *w_stream, U8CPU value) -> bool
bool SkWStream_write16(reskia_w_stream_t *w_stream, uint32_t value); // (SkWStream *w_stream, U16CPU value) -> bool
bool SkWStream_write32(reskia_w_stream_t *w_stream, uint32_t v); // (SkWStream *w_stream, uint32_t v) -> bool
bool SkWStream_writeText(reskia_w_stream_t *w_stream, const char text[]); // (SkWStream *w_stream, const char text[]) -> bool
bool SkWStream_newline(reskia_w_stream_t *w_stream); // (SkWStream *w_stream) -> bool
bool SkWStream_writeDecAsText(reskia_w_stream_t *w_stream, int32_t i); // (SkWStream *w_stream, int32_t i) -> bool
bool SkWStream_writeBigDecAsText(reskia_w_stream_t *w_stream, int64_t i, int minDigits); // (SkWStream *w_stream, int64_t i, int minDigits) -> bool
bool SkWStream_writeHexAsText(reskia_w_stream_t *w_stream, uint32_t i, int minDigits); // (SkWStream *w_stream, uint32_t i, int minDigits) -> bool
bool SkWStream_writeScalarAsText(reskia_w_stream_t *w_stream, float v); // (SkWStream *w_stream, SkScalar v) -> bool
bool SkWStream_writeBool(reskia_w_stream_t *w_stream, bool v); // (SkWStream *w_stream, bool v) -> bool
bool SkWStream_writeScalar(reskia_w_stream_t *w_stream, float v); // (SkWStream *w_stream, SkScalar v) -> bool
bool SkWStream_writePackedUInt(reskia_w_stream_t *w_stream, size_t size); // (SkWStream *w_stream, size_t size) -> bool
bool SkWStream_writeStream(reskia_w_stream_t *w_stream, reskia_stream_t *input, size_t length); // (SkWStream *w_stream, SkStream *input, size_t length) -> bool

// static

int SkWStream_SizeOfPackedUInt(size_t value); // (size_t value) -> int

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_W_STREAM_H
