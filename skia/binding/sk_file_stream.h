//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FILE_STREAM_H
#define RAIA_SKIA_SK_FILE_STREAM_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_file_stream.h"
#include "../static/static_sk_stream_asset.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_file_stream_t reskia_file_stream_t;
typedef struct reskia_file_t reskia_file_t;

reskia_file_stream_t *SkFILEStream_new(const char path[]); // (const char path[]) -> SkFILEStream *
reskia_file_stream_t *SkFILEStream_new_2(reskia_file_t *file); // (FILE *file) -> SkFILEStream *
reskia_file_stream_t *SkFILEStream_new_3(reskia_file_t *file, size_t size); // (FILE *file, size_t size) -> SkFILEStream *
void SkFILEStream_delete(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream)
bool SkFILEStream_isValid(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> bool
void SkFILEStream_close(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream)
size_t SkFILEStream_read(reskia_file_stream_t *file_stream, uint8_t *buffer, size_t size); // (SkFILEStream *file_stream, void *buffer, size_t size) -> size_t
bool SkFILEStream_isAtEnd(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> bool
bool SkFILEStream_rewind(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> bool
sk_stream_asset_t SkFILEStream_duplicate(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> sk_stream_asset_t
size_t SkFILEStream_getPosition(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> size_t
bool SkFILEStream_seek(reskia_file_stream_t *file_stream, size_t position); // (SkFILEStream *file_stream, size_t position) -> bool
bool SkFILEStream_move(reskia_file_stream_t *file_stream, long offset); // (SkFILEStream *file_stream, long offset) -> bool
sk_stream_asset_t SkFILEStream_fork(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> sk_stream_asset_t
size_t SkFILEStream_getLength(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> size_t
bool SkFILEStream_hasLength(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> bool
bool SkFILEStream_hasPosition(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> bool
size_t SkFILEStream_skip(reskia_file_stream_t *file_stream, size_t size); // (SkFILEStream *file_stream, size_t size) -> size_t
size_t SkFILEStream_peek(reskia_file_stream_t *file_stream, uint8_t *ptr, size_t size); // (SkFILEStream *file_stream, void *ptr, size_t size) -> size_t
bool SkFILEStream_readS8(reskia_file_stream_t *file_stream, int8_t *i); // (SkFILEStream *file_stream, int8_t *i) -> bool
bool SkFILEStream_readS16(reskia_file_stream_t *file_stream, int16_t *i); // (SkFILEStream *file_stream, int16_t *i) -> bool
bool SkFILEStream_readS32(reskia_file_stream_t *file_stream, int32_t *i); // (SkFILEStream *file_stream, int32_t *i) -> bool
bool SkFILEStream_readU8(reskia_file_stream_t *file_stream, uint8_t *i); // (SkFILEStream *file_stream, uint8_t *i) -> bool
bool SkFILEStream_readU16(reskia_file_stream_t *file_stream, uint16_t *i); // (SkFILEStream *file_stream, uint16_t *i) -> bool
bool SkFILEStream_readU32(reskia_file_stream_t *file_stream, uint32_t *i); // (SkFILEStream *file_stream, uint32_t *i) -> bool
bool SkFILEStream_readBool(reskia_file_stream_t *file_stream, bool *b); // (SkFILEStream *file_stream, bool *b) -> bool
bool SkFILEStream_readScalar(reskia_file_stream_t *file_stream, float *scalar); // (SkFILEStream *file_stream, SkScalar *scalar) -> bool
bool SkFILEStream_readPackedUInt(reskia_file_stream_t *file_stream, size_t *size); // (SkFILEStream *file_stream, size_t *size) -> bool
const uint8_t * SkFILEStream_getMemoryBase(reskia_file_stream_t *file_stream); // (SkFILEStream *file_stream) -> const void *

// static

sk_file_stream_t SkFILEStream_Make(const char path[]); // (const char path[]) -> sk_file_stream_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FILE_STREAM_H
