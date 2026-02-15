//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_STREAM_REWINDABLE_H
#define RAIA_SKIA_SK_STREAM_REWINDABLE_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_stream_rewindable_t reskia_stream_rewindable_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkStreamRewindable_delete(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable)
bool SkStreamRewindable_rewind(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> bool
int SkStreamRewindable_duplicate(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> sk_stream_rewindable_t
size_t SkStreamRewindable_read(reskia_stream_rewindable_t *stream_rewindable, void *buffer, size_t size); // (SkStreamRewindable *stream_rewindable, void *buffer, size_t size) -> size_t
size_t SkStreamRewindable_skip(reskia_stream_rewindable_t *stream_rewindable, size_t size); // (SkStreamRewindable *stream_rewindable, size_t size) -> size_t
size_t SkStreamRewindable_peek(reskia_stream_rewindable_t *stream_rewindable, void *buffer, size_t size); // (SkStreamRewindable *stream_rewindable, void *buffer, size_t size) -> size_t
bool SkStreamRewindable_isAtEnd(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> bool
bool SkStreamRewindable_readS8(reskia_stream_rewindable_t *stream_rewindable, int8_t *i); // (SkStreamRewindable *stream_rewindable, int8_t *i) -> bool
bool SkStreamRewindable_readS16(reskia_stream_rewindable_t *stream_rewindable, int16_t *i); // (SkStreamRewindable *stream_rewindable, int16_t *i) -> bool
bool SkStreamRewindable_readS32(reskia_stream_rewindable_t *stream_rewindable, int32_t *i); // (SkStreamRewindable *stream_rewindable, int32_t *i) -> bool
bool SkStreamRewindable_readU8(reskia_stream_rewindable_t *stream_rewindable, uint8_t *i); // (SkStreamRewindable *stream_rewindable, uint8_t *i) -> bool
bool SkStreamRewindable_readU16(reskia_stream_rewindable_t *stream_rewindable, uint16_t *i); // (SkStreamRewindable *stream_rewindable, uint16_t *i) -> bool
bool SkStreamRewindable_readU32(reskia_stream_rewindable_t *stream_rewindable, uint32_t *i); // (SkStreamRewindable *stream_rewindable, uint32_t *i) -> bool
bool SkStreamRewindable_readBool(reskia_stream_rewindable_t *stream_rewindable, bool *b); // (SkStreamRewindable *stream_rewindable, bool *b) -> bool
bool SkStreamRewindable_readScalar(reskia_stream_rewindable_t *stream_rewindable, float *v); // (SkStreamRewindable *stream_rewindable, SkScalar *v) -> bool
bool SkStreamRewindable_readPackedUInt(reskia_stream_rewindable_t *stream_rewindable, size_t *size); // (SkStreamRewindable *stream_rewindable, size_t *size) -> bool
int SkStreamRewindable_fork(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> sk_stream_t
bool SkStreamRewindable_hasPosition(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> bool
size_t SkStreamRewindable_getPosition(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> size_t
bool SkStreamRewindable_seek(reskia_stream_rewindable_t *stream_rewindable, size_t size); // (SkStreamRewindable *stream_rewindable, size_t size) -> bool
bool SkStreamRewindable_move(reskia_stream_rewindable_t *stream_rewindable, long i); // (SkStreamRewindable *stream_rewindable, long i) -> bool
bool SkStreamRewindable_hasLength(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> bool
size_t SkStreamRewindable_getLength(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> size_t
const void *SkStreamRewindable_getMemoryBase(reskia_stream_rewindable_t *stream_rewindable); // (SkStreamRewindable *stream_rewindable) -> const void *

// static

int SkStreamRewindable_MakeFromFile(const char path[]); // (const char path[]) -> sk_stream_asset_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STREAM_REWINDABLE_H
