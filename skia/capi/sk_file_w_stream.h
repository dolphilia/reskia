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

reskia_file_w_stream_t *SkFILEWStream_new(const char path[]); // path は非 NULL。invalid 入力では NULL
void SkFILEWStream_delete(reskia_file_w_stream_t *file_w_stream); // NULL 入力では no-op
bool SkFILEWStream_isValid(reskia_file_w_stream_t *file_w_stream); // NULL 入力では false
bool SkFILEWStream_write(reskia_file_w_stream_t *file_w_stream, const uint8_t *buffer, size_t size); // size > 0 では buffer は非 NULL。invalid 入力では false
void SkFILEWStream_flush(reskia_file_w_stream_t *file_w_stream); // NULL 入力では no-op
void SkFILEWStream_fsync(reskia_file_w_stream_t *file_w_stream); // NULL 入力では no-op
size_t SkFILEWStream_bytesWritten(reskia_file_w_stream_t *file_w_stream); // NULL 入力では 0
bool SkFILEWStream_write8(reskia_file_w_stream_t *file_w_stream, uint8_t value); // NULL 入力では false
bool SkFILEWStream_write16(reskia_file_w_stream_t *file_w_stream, uint16_t value); // NULL 入力では false
bool SkFILEWStream_write32(reskia_file_w_stream_t *file_w_stream, uint32_t v); // NULL 入力では false
bool SkFILEWStream_writeText(reskia_file_w_stream_t *file_w_stream, const char text[]); // text は非 NULL。invalid 入力では false
bool SkFILEWStream_newline(reskia_file_w_stream_t *file_w_stream); // NULL 入力では false
bool SkFILEWStream_writeDecAsText(reskia_file_w_stream_t *file_w_stream, int32_t v); // NULL 入力では false
bool SkFILEWStream_writeBigDecAsText(reskia_file_w_stream_t *file_w_stream, int64_t v, int minDigits); // NULL 入力では false
bool SkFILEWStream_writeHexAsText(reskia_file_w_stream_t *file_w_stream, uint32_t v, int minDigits); // NULL 入力では false
bool SkFILEWStream_writeScalarAsText(reskia_file_w_stream_t *file_w_stream, float scalar); // NULL 入力では false
bool SkFILEWStream_writeBool(reskia_file_w_stream_t *file_w_stream, bool v); // NULL 入力では false
bool SkFILEWStream_writeScalar(reskia_file_w_stream_t *file_w_stream, float scalar); // NULL 入力では false
bool SkFILEWStream_writePackedUInt(reskia_file_w_stream_t *file_w_stream, size_t size); // NULL 入力では false
bool SkFILEWStream_writeStream(reskia_file_w_stream_t *file_w_stream, reskia_stream_t *input, size_t length); // input は非 NULL。invalid 入力では false

// static

int SkFILEWStream_SizeOfPackedUInt(size_t value); // (size_t value) -> int

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FILE_W_STREAM_H
