//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_MEMORY_STREAM_H
#define RAIA_SKIA_SK_MEMORY_STREAM_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_memory_stream.h"

typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_memory_stream_t reskia_memory_stream_t;

reskia_memory_stream_t *SkMemoryStream_new(); // () -> SkMemoryStream *
reskia_memory_stream_t *SkMemoryStream_newWithLength(size_t length); // (size_t length) -> SkMemoryStream *
reskia_memory_stream_t *SkMemoryStream_newWithDataAndCopyFlag(const uint8_t *data, size_t length, bool copyData); // (const void *data, size_t length, bool copyData) -> SkMemoryStream *
reskia_memory_stream_t *SkMemoryStream_newWithData(sk_data_t data); // (sk_data_t data) -> SkMemoryStream *
void SkMemoryStream_delete(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream)
void SkMemoryStream_setMemory(reskia_memory_stream_t *memory_stream, const uint8_t *data, size_t length, bool copyData); // (SkMemoryStream *memory_stream, const void *data, size_t length, bool copyData)
void SkMemoryStream_setMemoryOwned(reskia_memory_stream_t *memory_stream, const uint8_t *data, size_t length); // (SkMemoryStream *memory_stream, const void *data, size_t length)
sk_data_t SkMemoryStream_asData(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> sk_data_t
void SkMemoryStream_setData(reskia_memory_stream_t *memory_stream, sk_data_t data); // (SkMemoryStream *memory_stream, sk_data_t data)
void SkMemoryStream_skipToAlign4(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream)
const uint8_t * SkMemoryStream_getAtPos(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> const void *
size_t SkMemoryStream_read(reskia_memory_stream_t *memory_stream, uint8_t *buffer, size_t size); // (SkMemoryStream *memory_stream, void *buffer, size_t size) -> size_t
bool SkMemoryStream_isAtEnd(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> bool
size_t SkMemoryStream_peek(reskia_memory_stream_t *memory_stream, uint8_t *buffer, size_t size); // (SkMemoryStream *memory_stream, void *buffer, size_t size) -> size_t
bool SkMemoryStream_rewind(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> bool
sk_memory_stream_t SkMemoryStream_duplicate(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> sk_memory_stream_t
size_t SkMemoryStream_getPosition(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> size_t
bool SkMemoryStream_seek(reskia_memory_stream_t *memory_stream, size_t position); // (SkMemoryStream *memory_stream, size_t position) -> bool
bool SkMemoryStream_move(reskia_memory_stream_t *memory_stream, long offset); // (SkMemoryStream *memory_stream, long offset) -> bool
sk_memory_stream_t SkMemoryStream_fork(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> sk_memory_stream_t
size_t SkMemoryStream_getLength(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> size_t
const uint8_t * SkMemoryStream_getMemoryBase(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> const void *
bool SkMemoryStream_hasLength(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> bool
bool SkMemoryStream_hasPosition(reskia_memory_stream_t *memory_stream); // (SkMemoryStream *memory_stream) -> bool
size_t SkMemoryStream_skip(reskia_memory_stream_t *memory_stream, size_t size); // (SkMemoryStream *memory_stream, size_t size) -> size_t
bool SkMemoryStream_readS8(reskia_memory_stream_t *memory_stream, int8_t *i); // (SkMemoryStream *memory_stream, int8_t *i) -> bool
bool SkMemoryStream_readS16(reskia_memory_stream_t *memory_stream, int16_t *i); // (SkMemoryStream *memory_stream, int16_t *i) -> bool
bool SkMemoryStream_readS32(reskia_memory_stream_t *memory_stream, int32_t *i); // (SkMemoryStream *memory_stream, int32_t *i) -> bool
bool SkMemoryStream_readU8(reskia_memory_stream_t *memory_stream, uint8_t *i); // (SkMemoryStream *memory_stream, uint8_t *i) -> bool
bool SkMemoryStream_readU16(reskia_memory_stream_t *memory_stream, uint16_t *i); // (SkMemoryStream *memory_stream, uint16_t *i) -> bool
bool SkMemoryStream_readU32(reskia_memory_stream_t *memory_stream, uint32_t *i); // (SkMemoryStream *memory_stream, uint32_t *i) -> bool
bool SkMemoryStream_readBool(reskia_memory_stream_t *memory_stream, bool *b); // (SkMemoryStream *memory_stream, bool *b) -> bool
bool SkMemoryStream_readScalar(reskia_memory_stream_t *memory_stream, float *v); // (SkMemoryStream *memory_stream, SkScalar *v) -> bool
bool SkMemoryStream_readPackedUInt(reskia_memory_stream_t *memory_stream, size_t *size); // (SkMemoryStream *memory_stream, size_t *size) -> bool

// static

sk_memory_stream_t SkMemoryStream_MakeCopy(const uint8_t *data, size_t length); // (const void *data, size_t length) -> sk_memory_stream_t
sk_memory_stream_t SkMemoryStream_MakeDirect(const uint8_t *data, size_t length); // (const void *data, size_t length) -> sk_memory_stream_t
sk_memory_stream_t SkMemoryStream_Make(sk_data_t data); // (sk_data_t data) -> sk_memory_stream_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MEMORY_STREAM_H
