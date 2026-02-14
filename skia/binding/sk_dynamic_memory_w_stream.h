//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DYNAMIC_MEMORY_W_STREAM_H
#define RAIA_SKIA_SK_DYNAMIC_MEMORY_W_STREAM_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_dynamic_memory_w_stream_t reskia_dynamic_memory_w_stream_t;
typedef struct reskia_stream_t reskia_stream_t;
typedef struct reskia_stream_asset_t reskia_stream_asset_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;

reskia_dynamic_memory_w_stream_t *SkDynamicMemoryWStream_new(); // () -> SkDynamicMemoryWStream *
// SkDynamicMemoryWStream * SkDynamicMemoryWStream_new_2(SkDynamicMemoryWStream &&stream)
void SkDynamicMemoryWStream_delete(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream); // (SkDynamicMemoryWStream *dynamic_memory_w_stream)
bool SkDynamicMemoryWStream_write(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, const uint8_t *buffer, size_t size); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, const void *buffer, size_t size) -> bool
size_t SkDynamicMemoryWStream_bytesWritten(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream); // (SkDynamicMemoryWStream *dynamic_memory_w_stream) -> size_t
bool SkDynamicMemoryWStream_read(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint8_t *buffer, size_t offset, size_t size); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, void *buffer, size_t offset, size_t size) -> bool
void SkDynamicMemoryWStream_copyTo(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint8_t *dst); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, void *dst)
bool SkDynamicMemoryWStream_writeToStream(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_w_stream_t *dst); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, SkWStream *dst) -> bool
void SkDynamicMemoryWStream_copyToAndReset(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint8_t *dst); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, void *dst)
bool SkDynamicMemoryWStream_writeToAndReset(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_w_stream_t *dst); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, SkWStream *dst) -> bool
bool SkDynamicMemoryWStream_writeToAndReset_2(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_dynamic_memory_w_stream_t *dst); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, SkDynamicMemoryWStream *dst) -> bool
void SkDynamicMemoryWStream_prependToAndReset(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_dynamic_memory_w_stream_t *dst); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, SkDynamicMemoryWStream *dst)
int SkDynamicMemoryWStream_detachAsData(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream); // (SkDynamicMemoryWStream *dynamic_memory_w_stream) -> sk_data_t
int SkDynamicMemoryWStream_detachAsStream(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream); // (SkDynamicMemoryWStream *dynamic_memory_w_stream) -> sk_stream_asset_t
void SkDynamicMemoryWStream_reset(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream); // (SkDynamicMemoryWStream *dynamic_memory_w_stream)
void SkDynamicMemoryWStream_padToAlign4(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream); // (SkDynamicMemoryWStream *dynamic_memory_w_stream)
void SkDynamicMemoryWStream_flush(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream); // (SkDynamicMemoryWStream *dynamic_memory_w_stream)
bool SkDynamicMemoryWStream_write8(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint8_t value); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, U8CPU value) -> bool
bool SkDynamicMemoryWStream_write16(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint16_t value); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, U16CPU value) -> bool
bool SkDynamicMemoryWStream_write32(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint32_t v); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, uint32_t v) -> bool
bool SkDynamicMemoryWStream_writeText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, const char text[]); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, const char text[]) -> bool
bool SkDynamicMemoryWStream_newline(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream); // (SkDynamicMemoryWStream *dynamic_memory_w_stream) -> bool
bool SkDynamicMemoryWStream_writeDecAsText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, int32_t v); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, int32_t v) -> bool
bool SkDynamicMemoryWStream_writeBigDecAsText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, int64_t v, int minDigits); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, int64_t v, int minDigits) -> bool
bool SkDynamicMemoryWStream_writeHexAsText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, uint32_t v, int minDigits); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, uint32_t v, int minDigits) -> bool
bool SkDynamicMemoryWStream_writeScalarAsText(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, float scalar); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, SkScalar scalar) -> bool
bool SkDynamicMemoryWStream_writeBool(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, bool v); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, bool v) -> bool
bool SkDynamicMemoryWStream_writeScalar(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, float scalar); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, SkScalar scalar) -> bool
bool SkDynamicMemoryWStream_writePackedUInt(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, size_t length); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, size_t length) -> bool
bool SkDynamicMemoryWStream_writeStream(reskia_dynamic_memory_w_stream_t *dynamic_memory_w_stream, reskia_stream_t *input, size_t length); // (SkDynamicMemoryWStream *dynamic_memory_w_stream, SkStream *input, size_t length) -> bool

// static

int SkDynamicMemoryWStream_SizeOfPackedUInt(size_t value); // (size_t value) -> int

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DYNAMIC_MEMORY_W_STREAM_H
