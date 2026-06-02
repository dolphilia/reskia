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

reskia_file_w_stream_t *SkFILEWStream_new(const char path[]); // path must be non-NULL. Returns NULL for invalid input.
void SkFILEWStream_delete(reskia_file_w_stream_t *file_w_stream); // No-op for NULL input.
bool SkFILEWStream_isValid(reskia_file_w_stream_t *file_w_stream); // Returns false for NULL input.
bool SkFILEWStream_write(reskia_file_w_stream_t *file_w_stream, const uint8_t *buffer, size_t size); // buffer must be non-NULL when size is greater than 0. Returns false for invalid input.
void SkFILEWStream_flush(reskia_file_w_stream_t *file_w_stream); // No-op for NULL input.
void SkFILEWStream_fsync(reskia_file_w_stream_t *file_w_stream); // No-op for NULL input.
size_t SkFILEWStream_bytesWritten(reskia_file_w_stream_t *file_w_stream); // Returns 0 for NULL input.
bool SkFILEWStream_write8(reskia_file_w_stream_t *file_w_stream, uint8_t value); // Returns false for NULL input.
bool SkFILEWStream_write16(reskia_file_w_stream_t *file_w_stream, uint16_t value); // Returns false for NULL input.
bool SkFILEWStream_write32(reskia_file_w_stream_t *file_w_stream, uint32_t v); // Returns false for NULL input.
bool SkFILEWStream_writeText(reskia_file_w_stream_t *file_w_stream, const char text[]); // text must be non-NULL. Returns false for invalid input.
bool SkFILEWStream_newline(reskia_file_w_stream_t *file_w_stream); // Returns false for NULL input.
bool SkFILEWStream_writeDecAsText(reskia_file_w_stream_t *file_w_stream, int32_t v); // Returns false for NULL input.
bool SkFILEWStream_writeBigDecAsText(reskia_file_w_stream_t *file_w_stream, int64_t v, int minDigits); // Returns false for NULL input.
bool SkFILEWStream_writeHexAsText(reskia_file_w_stream_t *file_w_stream, uint32_t v, int minDigits); // Returns false for NULL input.
bool SkFILEWStream_writeScalarAsText(reskia_file_w_stream_t *file_w_stream, float scalar); // Returns false for NULL input.
bool SkFILEWStream_writeBool(reskia_file_w_stream_t *file_w_stream, bool v); // Returns false for NULL input.
bool SkFILEWStream_writeScalar(reskia_file_w_stream_t *file_w_stream, float scalar); // Returns false for NULL input.
bool SkFILEWStream_writePackedUInt(reskia_file_w_stream_t *file_w_stream, size_t size); // Returns false for NULL input.
bool SkFILEWStream_writeStream(reskia_file_w_stream_t *file_w_stream, reskia_stream_t *input, size_t length); // input must be non-NULL. Returns false for invalid input.

// static

int SkFILEWStream_SizeOfPackedUInt(size_t value); // (size_t value) -> int

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FILE_W_STREAM_H
