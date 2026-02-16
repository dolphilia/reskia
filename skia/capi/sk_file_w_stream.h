//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FILE_W_STREAM_H
#define RAIA_SKIA_SK_FILE_W_STREAM_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_file_w_stream_t reskia_file_w_stream_t;
typedef struct reskia_stream_t reskia_stream_t;

reskia_file_w_stream_t *SkFILEWStream_new(const char path[]); // (const char path[]) -> SkFILEWStream *
void SkFILEWStream_delete(reskia_file_w_stream_t *file_w_stream); // (SkFILEWStream *file_w_stream)
bool SkFILEWStream_isValid(reskia_file_w_stream_t *file_w_stream); // (SkFILEWStream *file_w_stream) -> bool
bool SkFILEWStream_write(reskia_file_w_stream_t *file_w_stream, const uint8_t *buffer, size_t size); // (SkFILEWStream *file_w_stream, const void *buffer, size_t size) -> bool
void SkFILEWStream_flush(reskia_file_w_stream_t *file_w_stream); // (SkFILEWStream *file_w_stream)
void SkFILEWStream_fsync(reskia_file_w_stream_t *file_w_stream); // (SkFILEWStream *file_w_stream)
size_t SkFILEWStream_bytesWritten(reskia_file_w_stream_t *file_w_stream); // (SkFILEWStream *file_w_stream) -> size_t
bool SkFILEWStream_write8(reskia_file_w_stream_t *file_w_stream, uint8_t value); // (SkFILEWStream *file_w_stream, U8CPU value) -> bool
bool SkFILEWStream_write16(reskia_file_w_stream_t *file_w_stream, uint16_t value); // (SkFILEWStream *file_w_stream, U16CPU value) -> bool
bool SkFILEWStream_write32(reskia_file_w_stream_t *file_w_stream, uint32_t v); // (SkFILEWStream *file_w_stream, uint32_t v) -> bool
bool SkFILEWStream_writeText(reskia_file_w_stream_t *file_w_stream, const char text[]); // (SkFILEWStream *file_w_stream, const char text[]) -> bool
bool SkFILEWStream_newline(reskia_file_w_stream_t *file_w_stream); // (SkFILEWStream *file_w_stream) -> bool
bool SkFILEWStream_writeDecAsText(reskia_file_w_stream_t *file_w_stream, int32_t v); // (SkFILEWStream *file_w_stream, int32_t v) -> bool
bool SkFILEWStream_writeBigDecAsText(reskia_file_w_stream_t *file_w_stream, int64_t v, int minDigits); // (SkFILEWStream *file_w_stream, int64_t v, int minDigits) -> bool
bool SkFILEWStream_writeHexAsText(reskia_file_w_stream_t *file_w_stream, uint32_t v, int minDigits); // (SkFILEWStream *file_w_stream, uint32_t v, int minDigits) -> bool
bool SkFILEWStream_writeScalarAsText(reskia_file_w_stream_t *file_w_stream, float scalar); // (SkFILEWStream *file_w_stream, SkScalar scalar) -> bool
bool SkFILEWStream_writeBool(reskia_file_w_stream_t *file_w_stream, bool v); // (SkFILEWStream *file_w_stream, bool v) -> bool
bool SkFILEWStream_writeScalar(reskia_file_w_stream_t *file_w_stream, float scalar); // (SkFILEWStream *file_w_stream, SkScalar scalar) -> bool
bool SkFILEWStream_writePackedUInt(reskia_file_w_stream_t *file_w_stream, size_t size); // (SkFILEWStream *file_w_stream, size_t size) -> bool
bool SkFILEWStream_writeStream(reskia_file_w_stream_t *file_w_stream, reskia_stream_t *input, size_t length); // (SkFILEWStream *file_w_stream, SkStream *input, size_t length) -> bool

// static

int SkFILEWStream_SizeOfPackedUInt(size_t value); // (size_t value) -> int

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FILE_W_STREAM_H
