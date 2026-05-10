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

reskia_file_stream_t *SkFILEStream_new(const char path[]); // path は非 NULL。invalid 入力では NULL
reskia_file_stream_t *SkFILEStream_newFromFileHandle(reskia_file_t *file); // file は非 NULL。invalid 入力では NULL。所有権は SkFILEStream に移る
reskia_file_stream_t *SkFILEStream_newFromFileHandleWithSize(reskia_file_t *file, size_t size); // file は非 NULL。invalid 入力では NULL。所有権は SkFILEStream に移る
void SkFILEStream_delete(reskia_file_stream_t *file_stream); // NULL 入力では no-op
bool SkFILEStream_isValid(reskia_file_stream_t *file_stream); // NULL 入力では false
void SkFILEStream_close(reskia_file_stream_t *file_stream); // NULL 入力では no-op
size_t SkFILEStream_read(reskia_file_stream_t *file_stream, uint8_t *buffer, size_t size); // size > 0 では buffer は非 NULL。invalid 入力では 0
bool SkFILEStream_isAtEnd(reskia_file_stream_t *file_stream); // NULL 入力では true
bool SkFILEStream_rewind(reskia_file_stream_t *file_stream); // NULL 入力では false
sk_stream_asset_t SkFILEStream_duplicate(reskia_file_stream_t *file_stream); // NULL 入力では 0
size_t SkFILEStream_getPosition(reskia_file_stream_t *file_stream); // NULL 入力では 0
bool SkFILEStream_seek(reskia_file_stream_t *file_stream, size_t position); // NULL 入力では false
bool SkFILEStream_move(reskia_file_stream_t *file_stream, long offset); // NULL 入力では false
sk_stream_asset_t SkFILEStream_fork(reskia_file_stream_t *file_stream); // NULL 入力では 0
size_t SkFILEStream_getLength(reskia_file_stream_t *file_stream); // NULL 入力では 0
bool SkFILEStream_hasLength(reskia_file_stream_t *file_stream); // NULL 入力では false
bool SkFILEStream_hasPosition(reskia_file_stream_t *file_stream); // NULL 入力では false
size_t SkFILEStream_skip(reskia_file_stream_t *file_stream, size_t size); // NULL 入力では 0
size_t SkFILEStream_peek(reskia_file_stream_t *file_stream, uint8_t *ptr, size_t size); // size > 0 では ptr は非 NULL。invalid 入力では 0
bool SkFILEStream_readS8(reskia_file_stream_t *file_stream, int8_t *i); // i は非 NULL。invalid 入力では false
bool SkFILEStream_readS16(reskia_file_stream_t *file_stream, int16_t *i); // i は非 NULL。invalid 入力では false
bool SkFILEStream_readS32(reskia_file_stream_t *file_stream, int32_t *i); // i は非 NULL。invalid 入力では false
bool SkFILEStream_readU8(reskia_file_stream_t *file_stream, uint8_t *i); // i は非 NULL。invalid 入力では false
bool SkFILEStream_readU16(reskia_file_stream_t *file_stream, uint16_t *i); // i は非 NULL。invalid 入力では false
bool SkFILEStream_readU32(reskia_file_stream_t *file_stream, uint32_t *i); // i は非 NULL。invalid 入力では false
bool SkFILEStream_readBool(reskia_file_stream_t *file_stream, bool *b); // b は非 NULL。invalid 入力では false
bool SkFILEStream_readScalar(reskia_file_stream_t *file_stream, float *scalar); // scalar は非 NULL。invalid 入力では false
bool SkFILEStream_readPackedUInt(reskia_file_stream_t *file_stream, size_t *size); // size は非 NULL。invalid 入力では false
const uint8_t * SkFILEStream_getMemoryBase(reskia_file_stream_t *file_stream); // borrowed pointer。NULL 入力では NULL

// static

sk_file_stream_t SkFILEStream_Make(const char path[]); // path は非 NULL。invalid 入力では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FILE_STREAM_H
