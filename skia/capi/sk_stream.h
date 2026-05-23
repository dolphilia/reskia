//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_STREAM_H
#define RAIA_SKIA_SK_STREAM_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_stream.h"
#include "../handles/static_sk_stream_asset.h"
#include "../handles/static_sk_data.h"

typedef struct reskia_stream_t reskia_stream_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkStream_delete(reskia_stream_t *stream); // (SkStream *stream)
size_t SkStream_read(reskia_stream_t *stream, void *buffer, size_t size); // buffer may be null to skip size bytes
size_t SkStream_skip(reskia_stream_t *stream, size_t size); // (SkStream *stream, size_t size) -> size_t
size_t SkStream_peek(reskia_stream_t *stream, void *buffer, size_t size); // buffer may be null only when size == 0
bool SkStream_isAtEnd(reskia_stream_t *stream); // (SkStream *stream) -> bool
bool SkStream_readS8(reskia_stream_t *stream, int8_t *i); // (SkStream *stream, int8_t *i) -> bool
bool SkStream_readS16(reskia_stream_t *stream, int16_t *i); // (SkStream *stream, int16_t *i) -> bool
bool SkStream_readS32(reskia_stream_t *stream, int32_t *i); // (SkStream *stream, int32_t *i) -> bool
bool SkStream_readU8(reskia_stream_t *stream, uint8_t *i); // (SkStream *stream, uint8_t *i) -> bool
bool SkStream_readU16(reskia_stream_t *stream, uint16_t *i); // (SkStream *stream, uint16_t *i) -> bool
bool SkStream_readU32(reskia_stream_t *stream, uint32_t *i); // (SkStream *stream, uint32_t *i) -> bool
bool SkStream_readBool(reskia_stream_t *stream, bool *b); // (SkStream *stream, bool *b) -> bool
bool SkStream_readScalar(reskia_stream_t *stream, float *v); // (SkStream *stream, SkScalar *v) -> bool
bool SkStream_readPackedUInt(reskia_stream_t *stream, size_t *size); // (SkStream *stream, size_t *size) -> bool
bool SkStream_rewind(reskia_stream_t *stream); // (SkStream *stream) -> bool
sk_stream_t SkStream_duplicate(reskia_stream_t *stream); // (SkStream *stream) -> sk_stream_t
sk_stream_t SkStream_fork(reskia_stream_t *stream); // (SkStream *stream) -> sk_stream_t
bool SkStream_hasPosition(reskia_stream_t *stream); // (SkStream *stream) -> bool
size_t SkStream_getPosition(reskia_stream_t *stream); // (SkStream *stream) -> size_t
bool SkStream_seek(reskia_stream_t *stream, size_t size); // (SkStream *stream, size_t size) -> bool
bool SkStream_move(reskia_stream_t *stream, long i); // (SkStream *stream, long i) -> bool
bool SkStream_hasLength(reskia_stream_t *stream); // (SkStream *stream) -> bool
size_t SkStream_getLength(reskia_stream_t *stream); // (SkStream *stream) -> size_t
/**
 * borrowed memory base when supported.
 * caller must not free.
 */
const void * SkStream_getMemoryBase(reskia_stream_t *stream);
sk_data_t SkStream_getData(reskia_stream_t *stream); // NULL or unsupported stream returns 0.

// static

sk_stream_asset_t SkStream_MakeFromFile(const char path[]); // path: non-null filesystem path

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STREAM_H
