//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PICTURE_H
#define RAIA_SKIA_SK_PICTURE_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_shader.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_picture_abort_callback_t reskia_picture_abort_callback_t;
typedef struct reskia_picture_t reskia_picture_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_stream_t reskia_stream_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;
typedef int32_t reskia_picture_tile_mode_t;
typedef int32_t reskia_picture_filter_mode_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkPicture_release(reskia_picture_t *picture); // Owned reference: releases the caller-held reference. No-op for NULL input.
/**
 * canvas must be non-NULL. callback may be NULL.
 * No-op for invalid input.
 */
void SkPicture_playback(reskia_picture_t *picture, reskia_canvas_t *canvas, reskia_picture_abort_callback_t *callback);
sk_rect_t SkPicture_cullRect(reskia_picture_t *picture); // Returns 0 for NULL input.
uint32_t SkPicture_uniqueID(reskia_picture_t *picture); // Returns 0 for NULL input.
sk_data_t SkPicture_serialize(reskia_picture_t *picture, const reskia_serial_procs_t *procs); // procs may be NULL. Returns 0 for NULL input or creation failure.
/**
 * stream must be non-NULL.
 * No-op for invalid input.
 */
void SkPicture_serializeToStream(reskia_picture_t *picture, reskia_w_stream_t *stream, const reskia_serial_procs_t *procs);
size_t SkPicture_approximateOpCount(reskia_picture_t *picture); // Returns 0 for NULL input.
size_t SkPicture_approximateBytesUsed(reskia_picture_t *picture); // Returns 0 for NULL input.
/**
 * localMatrix and tileRect may be NULL.
 * Returns 0 for invalid enum values, NULL picture, or creation failure.
 */
sk_shader_t SkPicture_makeShader(reskia_picture_t *picture, reskia_picture_tile_mode_t tmx, reskia_picture_tile_mode_t tmy, reskia_picture_filter_mode_t mode, const reskia_matrix_t *localMatrix, const reskia_rect_t *tileRect);
/**
 * Returns 0 for invalid enum values, NULL picture, or creation failure.
 */
sk_shader_t SkPicture_makeShaderWithoutLocalMatrixAndTileRect(reskia_picture_t *picture, reskia_picture_tile_mode_t tmx, reskia_picture_tile_mode_t tmy, reskia_picture_filter_mode_t mode);
bool SkPicture_unique(reskia_picture_t *picture); // Returns false for NULL input.
void SkPicture_ref(reskia_picture_t *picture); // Retains the object by incrementing the reference count. No-op for NULL input.
void SkPicture_unref(reskia_picture_t *picture); // Releases the object by decrementing the reference count. No-op for NULL input.

// static

sk_picture_t SkPicture_MakeFromStream(reskia_stream_t *stream, const reskia_deserial_procs_t *procs); // stream must be non-NULL. Returns 0 on creation failure.
sk_picture_t SkPicture_MakeFromData(const reskia_data_t *data, const reskia_deserial_procs_t *procs); // data must be non-NULL. Returns 0 on creation failure.
sk_picture_t SkPicture_MakeFromMemory(const void *data, size_t size, const reskia_deserial_procs_t *procs); // data must be non-NULL, and size must be greater than 0. Returns 0 for invalid input or creation failure.
sk_picture_t SkPicture_MakePlaceholder(sk_rect_t cull); // Invalid cull handles are treated as an empty rect. Returns 0 on creation failure.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PICTURE_H
