//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FILE_STREAM_H
#define RAIA_SKIA_SK_FILE_STREAM_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_file_stream.h"
#include "../handles/static_sk_stream_asset.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_file_stream_t reskia_file_stream_t;
typedef struct reskia_file_t reskia_file_t;

reskia_file_stream_t *SkFILEStream_new(const char path[]); // path must be non-NULL. Returns NULL for invalid input.
reskia_file_stream_t *SkFILEStream_newFromFileHandle(reskia_file_t *file); // file must be non-NULL. Returns NULL for invalid input. Ownership is transferred to SkFILEStream.
reskia_file_stream_t *SkFILEStream_newFromFileHandleWithSize(reskia_file_t *file, size_t size); // file must be non-NULL. Returns NULL for invalid input. Ownership is transferred to SkFILEStream.
void SkFILEStream_delete(reskia_file_stream_t *file_stream); // No-op for NULL input.
bool SkFILEStream_isValid(reskia_file_stream_t *file_stream); // Returns false for NULL input.
void SkFILEStream_close(reskia_file_stream_t *file_stream); // No-op for NULL input.
size_t SkFILEStream_read(reskia_file_stream_t *file_stream, uint8_t *buffer, size_t size); // buffer must be non-NULL when size is greater than 0. Returns 0 for invalid input.
bool SkFILEStream_isAtEnd(reskia_file_stream_t *file_stream); // Returns true for NULL input.
bool SkFILEStream_rewind(reskia_file_stream_t *file_stream); // Returns false for NULL input.
sk_stream_asset_t SkFILEStream_duplicate(reskia_file_stream_t *file_stream); // Returns 0 for NULL input.
size_t SkFILEStream_getPosition(reskia_file_stream_t *file_stream); // Returns 0 for NULL input.
bool SkFILEStream_seek(reskia_file_stream_t *file_stream, size_t position); // Returns false for NULL input.
bool SkFILEStream_move(reskia_file_stream_t *file_stream, long offset); // Returns false for NULL input.
sk_stream_asset_t SkFILEStream_fork(reskia_file_stream_t *file_stream); // Returns 0 for NULL input.
size_t SkFILEStream_getLength(reskia_file_stream_t *file_stream); // Returns 0 for NULL input.
bool SkFILEStream_hasLength(reskia_file_stream_t *file_stream); // Returns false for NULL input.
bool SkFILEStream_hasPosition(reskia_file_stream_t *file_stream); // Returns false for NULL input.
size_t SkFILEStream_skip(reskia_file_stream_t *file_stream, size_t size); // Returns 0 for NULL input.
size_t SkFILEStream_peek(reskia_file_stream_t *file_stream, uint8_t *ptr, size_t size); // ptr must be non-NULL when size is greater than 0. Returns 0 for invalid input.
bool SkFILEStream_readS8(reskia_file_stream_t *file_stream, int8_t *i); // i must be non-NULL. Returns false for invalid input.
bool SkFILEStream_readS16(reskia_file_stream_t *file_stream, int16_t *i); // i must be non-NULL. Returns false for invalid input.
bool SkFILEStream_readS32(reskia_file_stream_t *file_stream, int32_t *i); // i must be non-NULL. Returns false for invalid input.
bool SkFILEStream_readU8(reskia_file_stream_t *file_stream, uint8_t *i); // i must be non-NULL. Returns false for invalid input.
bool SkFILEStream_readU16(reskia_file_stream_t *file_stream, uint16_t *i); // i must be non-NULL. Returns false for invalid input.
bool SkFILEStream_readU32(reskia_file_stream_t *file_stream, uint32_t *i); // i must be non-NULL. Returns false for invalid input.
bool SkFILEStream_readBool(reskia_file_stream_t *file_stream, bool *b); // b must be non-NULL. Returns false for invalid input.
bool SkFILEStream_readScalar(reskia_file_stream_t *file_stream, float *scalar); // scalar must be non-NULL. Returns false for invalid input.
bool SkFILEStream_readPackedUInt(reskia_file_stream_t *file_stream, size_t *size); // size must be non-NULL. Returns false for invalid input.
const uint8_t * SkFILEStream_getMemoryBase(reskia_file_stream_t *file_stream); // Borrowed pointer. Returns NULL for NULL input.

// static

sk_file_stream_t SkFILEStream_Make(const char path[]); // path must be non-NULL. Returns 0 for invalid input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FILE_STREAM_H
