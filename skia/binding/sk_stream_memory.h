//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_STREAM_MEMORY_H
#define RAIA_SKIA_SK_STREAM_MEMORY_H

#include <stddef.h>
#include <stdint.h>

#include "../static/static_sk_stream_asset.h"
#include "../static/static_sk_stream_memory.h"

typedef struct reskia_stream_memory_t reskia_stream_memory_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkStreamMemory_delete(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory)
const void *SkStreamMemory_getMemoryBase(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> const void *
sk_stream_memory_t SkStreamMemory_duplicate(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> sk_stream_memory_t
sk_stream_memory_t SkStreamMemory_fork(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> sk_stream_memory_t
bool SkStreamMemory_hasLength(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> bool
size_t SkStreamMemory_getLength(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> size_t
bool SkStreamMemory_hasPosition(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> bool
size_t SkStreamMemory_getPosition(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> size_t
bool SkStreamMemory_seek(reskia_stream_memory_t *stream_memory, size_t position); // (SkStreamMemory *stream_memory, size_t position) -> bool
bool SkStreamMemory_move(reskia_stream_memory_t *stream_memory, long offset); // (SkStreamMemory *stream_memory, long offset) -> bool
bool SkStreamMemory_rewind(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> bool
size_t SkStreamMemory_read(reskia_stream_memory_t *stream_memory, void *buffer, size_t size); // (SkStreamMemory *stream_memory, void *buffer, size_t size) -> size_t
size_t SkStreamMemory_skip(reskia_stream_memory_t *stream_memory, size_t size); // (SkStreamMemory *stream_memory, size_t size) -> size_t
size_t SkStreamMemory_peek(reskia_stream_memory_t *stream_memory, void *buffer, size_t size); // (SkStreamMemory *stream_memory, void *buffer, size_t size) -> size_t
bool SkStreamMemory_isAtEnd(reskia_stream_memory_t *stream_memory); // (SkStreamMemory *stream_memory) -> bool
bool SkStreamMemory_readS8(reskia_stream_memory_t *stream_memory, int8_t *i); // (SkStreamMemory *stream_memory, int8_t *i) -> bool
bool SkStreamMemory_readS16(reskia_stream_memory_t *stream_memory, int16_t *i); // (SkStreamMemory *stream_memory, int16_t *i) -> bool
bool SkStreamMemory_readS32(reskia_stream_memory_t *stream_memory, int32_t *i); // (SkStreamMemory *stream_memory, int32_t *i) -> bool
bool SkStreamMemory_readU8(reskia_stream_memory_t *stream_memory, uint8_t *i); // (SkStreamMemory *stream_memory, uint8_t *i) -> bool
bool SkStreamMemory_readU16(reskia_stream_memory_t *stream_memory, uint16_t *i); // (SkStreamMemory *stream_memory, uint16_t *i) -> bool
bool SkStreamMemory_readU32(reskia_stream_memory_t *stream_memory, uint32_t *i); // (SkStreamMemory *stream_memory, uint32_t *i) -> bool
bool SkStreamMemory_readBool(reskia_stream_memory_t *stream_memory, bool *b); // (SkStreamMemory *stream_memory, bool *b) -> bool
bool SkStreamMemory_readScalar(reskia_stream_memory_t *stream_memory, float *v); // (SkStreamMemory *stream_memory, SkScalar *v) -> bool
bool SkStreamMemory_readPackedUInt(reskia_stream_memory_t *stream_memory, size_t *size); // (SkStreamMemory *stream_memory, size_t *size) -> bool

// static

sk_stream_asset_t SkStreamMemory_MakeFromFile(const char path[]); // (const char path[]) -> sk_stream_asset_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STREAM_MEMORY_H
