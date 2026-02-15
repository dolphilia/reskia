//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PICTURE_H
#define RAIA_SKIA_SK_PICTURE_H

#include <stddef.h>
#include <stdint.h>

#include "../static/static_sk_data.h"
#include "../static/static_sk_picture.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_shader.h"

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

#ifdef __cplusplus
extern "C" {
#endif

void SkPicture_delete(reskia_picture_t *picture); // owned: caller が保持する参照を release する (SkPicture *picture)
void SkPicture_playback(reskia_picture_t *picture, reskia_canvas_t *canvas, reskia_picture_abort_callback_t *callback); // (SkPicture *picture, SkCanvas *canvas, SkPicture::AbortCallback *callback)
sk_rect_t SkPicture_cullRect(reskia_picture_t *picture); // (SkPicture *picture) -> sk_rect_t
uint32_t SkPicture_uniqueID(reskia_picture_t *picture); // (SkPicture *picture) -> uint32_t
sk_data_t SkPicture_serialize(reskia_picture_t *picture, const reskia_serial_procs_t *procs); // (SkPicture *picture, const SkSerialProcs *procs) -> sk_data_t
void SkPicture_serialize_2(reskia_picture_t *picture, reskia_w_stream_t *stream, const reskia_serial_procs_t *procs); // (SkPicture *picture, SkWStream *stream, const SkSerialProcs *procs)
size_t SkPicture_approximateOpCount(reskia_picture_t *picture); // (SkPicture *picture) -> size_t
size_t SkPicture_approximateBytesUsed(reskia_picture_t *picture); // (SkPicture *picture) -> size_t
sk_shader_t SkPicture_makeShader(reskia_picture_t *picture, int tmx, int tmy, int mode, const reskia_matrix_t *localMatrix, const reskia_rect_t *tileRect); // (SkPicture *picture, SkTileMode tmx, SkTileMode tmy, SkFilterMode mode, const SkMatrix *localMatrix, const SkRect *tileRect) -> sk_shader_t
sk_shader_t SkPicture_makeShader_2(reskia_picture_t *picture, int tmx, int tmy, int mode); // (SkPicture *picture, SkTileMode tmx, SkTileMode tmy, SkFilterMode mode) -> sk_shader_t
bool SkPicture_unique(reskia_picture_t *picture); // (SkPicture *picture) -> bool
void SkPicture_ref(reskia_picture_t *picture); // retained: 参照カウントを増やす (SkPicture *picture)
void SkPicture_unref(reskia_picture_t *picture); // owned: 参照カウントを減らす (SkPicture *picture)

// static

sk_picture_t SkPicture_MakeFromStream(reskia_stream_t *stream, const reskia_deserial_procs_t *procs); // (SkStream *stream, const SkDeserialProcs *procs) -> sk_picture_t
sk_picture_t SkPicture_MakeFromData(const reskia_data_t *data, const reskia_deserial_procs_t *procs); // (const SkData *data, const SkDeserialProcs *procs) -> sk_picture_t
sk_picture_t SkPicture_MakeFromData_2(const void *data, size_t size, const reskia_deserial_procs_t *procs); // (const void *data, size_t size, const SkDeserialProcs *procs) -> sk_picture_t
sk_picture_t SkPicture_MakePlaceholder(sk_rect_t cull); // (sk_rect_t cull) -> sk_picture_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PICTURE_H
