//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_STREAM_ASSET_H
#define RAIA_SKIA_SK_STREAM_ASSET_H

#include <stddef.h>
#include <stdint.h>

#include "../static/static_sk_stream_asset.h"

typedef struct reskia_stream_asset_t reskia_stream_asset_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkStreamAsset_delete(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset)
bool SkStreamAsset_hasLength(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> bool
size_t SkStreamAsset_getLength(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> size_t
sk_stream_asset_t SkStreamAsset_duplicate(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> sk_stream_asset_t
sk_stream_asset_t SkStreamAsset_fork(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> sk_stream_asset_t
bool SkStreamAsset_hasPosition(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> bool
size_t SkStreamAsset_getPosition(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> size_t
bool SkStreamAsset_seek(reskia_stream_asset_t *stream_asset, size_t position); // (SkStreamAsset *stream_asset, size_t position) -> bool
bool SkStreamAsset_move(reskia_stream_asset_t *stream_asset, long offset); // (SkStreamAsset *stream_asset, long offset) -> bool
bool SkStreamAsset_rewind(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> bool
size_t SkStreamAsset_read(reskia_stream_asset_t *stream_asset, void *buffer, size_t size); // (SkStreamAsset *stream_asset, void *buffer, size_t size) -> size_t
size_t SkStreamAsset_skip(reskia_stream_asset_t *stream_asset, size_t size); // (SkStreamAsset *stream_asset, size_t size) -> size_t
size_t SkStreamAsset_peek(reskia_stream_asset_t *stream_asset, void *buffer, size_t size); // (SkStreamAsset *stream_asset, void *buffer, size_t size) -> size_t
bool SkStreamAsset_isAtEnd(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> bool
bool SkStreamAsset_readS8(reskia_stream_asset_t *stream_asset, int8_t *i); // (SkStreamAsset *stream_asset, int8_t *i) -> bool
bool SkStreamAsset_readS16(reskia_stream_asset_t *stream_asset, int16_t *i); // (SkStreamAsset *stream_asset, int16_t *i) -> bool
bool SkStreamAsset_readS32(reskia_stream_asset_t *stream_asset, int32_t *i); // (SkStreamAsset *stream_asset, int32_t *i) -> bool
bool SkStreamAsset_readU8(reskia_stream_asset_t *stream_asset, uint8_t *i); // (SkStreamAsset *stream_asset, uint8_t *i) -> bool
bool SkStreamAsset_readU16(reskia_stream_asset_t *stream_asset, uint16_t *i); // (SkStreamAsset *stream_asset, uint16_t *i) -> bool
bool SkStreamAsset_readU32(reskia_stream_asset_t *stream_asset, uint32_t *i); // (SkStreamAsset *stream_asset, uint32_t *i) -> bool
bool SkStreamAsset_readBool(reskia_stream_asset_t *stream_asset, bool *b); // (SkStreamAsset *stream_asset, bool *b) -> bool
bool SkStreamAsset_readScalar(reskia_stream_asset_t *stream_asset, float *v); // (SkStreamAsset *stream_asset, SkScalar *v) -> bool
bool SkStreamAsset_readPackedUInt(reskia_stream_asset_t *stream_asset, size_t *size); // (SkStreamAsset *stream_asset, size_t *size) -> bool
const void *SkStreamAsset_getMemoryBase(reskia_stream_asset_t *stream_asset); // (SkStreamAsset *stream_asset) -> const void *

// static

sk_stream_asset_t SkStreamAsset_MakeFromFile(const char path[]); // (const char path[]) -> sk_stream_asset_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STREAM_ASSET_H
