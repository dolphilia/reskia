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

void SkPicture_release(reskia_picture_t *picture); // owned: caller が保持する参照を release する。NULL 入力では no-op
void SkPicture_playback(reskia_picture_t *picture, reskia_canvas_t *canvas, reskia_picture_abort_callback_t *callback); // canvas は非 NULL。callback は NULL 許可。invalid 入力では no-op
sk_rect_t SkPicture_cullRect(reskia_picture_t *picture); // NULL 入力では 0
uint32_t SkPicture_uniqueID(reskia_picture_t *picture); // NULL 入力では 0
sk_data_t SkPicture_serialize(reskia_picture_t *picture, const reskia_serial_procs_t *procs); // procs は NULL 許可。NULL 入力や生成不能では 0
void SkPicture_serializeToStream(reskia_picture_t *picture, reskia_w_stream_t *stream, const reskia_serial_procs_t *procs); // stream は非 NULL。invalid 入力では no-op
size_t SkPicture_approximateOpCount(reskia_picture_t *picture); // NULL 入力では 0
size_t SkPicture_approximateBytesUsed(reskia_picture_t *picture); // NULL 入力では 0
sk_shader_t SkPicture_makeShader(reskia_picture_t *picture, reskia_picture_tile_mode_t tmx, reskia_picture_tile_mode_t tmy, reskia_picture_filter_mode_t mode, const reskia_matrix_t *localMatrix, const reskia_rect_t *tileRect); // localMatrix/tileRect は NULL 許可。invalid enum/NULL picture/生成不能では 0
sk_shader_t SkPicture_makeShaderWithoutLocalMatrixAndTileRect(reskia_picture_t *picture, reskia_picture_tile_mode_t tmx, reskia_picture_tile_mode_t tmy, reskia_picture_filter_mode_t mode); // invalid enum/NULL picture/生成不能では 0
bool SkPicture_unique(reskia_picture_t *picture); // NULL 入力では false
void SkPicture_ref(reskia_picture_t *picture); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkPicture_unref(reskia_picture_t *picture); // owned: 参照カウントを減らす。NULL 入力では no-op

// static

sk_picture_t SkPicture_MakeFromStream(reskia_stream_t *stream, const reskia_deserial_procs_t *procs); // stream は非 NULL。生成不能では 0
sk_picture_t SkPicture_MakeFromData(const reskia_data_t *data, const reskia_deserial_procs_t *procs); // data は非 NULL。生成不能では 0
sk_picture_t SkPicture_MakeFromMemory(const void *data, size_t size, const reskia_deserial_procs_t *procs); // data 非 NULL、size > 0。invalid 入力や生成不能では 0
sk_picture_t SkPicture_MakePlaceholder(sk_rect_t cull); // invalid cull handle は empty rect。生成不能では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PICTURE_H
