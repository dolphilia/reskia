//
// Created by dolphilia on 2024/01/10.
//

#include "sk_picture.h"

#include "include/core/SkPicture.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_shader.h"
#include "../static/static_sk_picture.h"

#include "../static/static_sk_picture-internal.h"
#include "../static/static_sk_rect-internal.h"
#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkPicture_delete(reskia_picture_t *picture) {
    reinterpret_cast<SkPicture *>(picture)->unref();
}

void SkPicture_playback(reskia_picture_t *picture, reskia_canvas_t *canvas, reskia_picture_abort_callback_t *callback) {
    reinterpret_cast<SkPicture *>(picture)->playback(
        reinterpret_cast<SkCanvas *>(canvas),
        reinterpret_cast<SkPicture::AbortCallback *>(callback));
}

sk_rect_t SkPicture_cullRect(reskia_picture_t *picture) {
    return static_sk_rect_make(reinterpret_cast<SkPicture *>(picture)->cullRect());
}

uint32_t SkPicture_uniqueID(reskia_picture_t *picture) {
    return reinterpret_cast<SkPicture *>(picture)->uniqueID();
}

sk_data_t SkPicture_serialize(reskia_picture_t *picture, const reskia_serial_procs_t *procs) {
    return static_sk_data_make(reinterpret_cast<SkPicture *>(picture)->serialize(reinterpret_cast<const SkSerialProcs *>(procs)));
}

void SkPicture_serialize_2(reskia_picture_t *picture, reskia_w_stream_t *stream, const reskia_serial_procs_t *procs) {
    reinterpret_cast<SkPicture *>(picture)->serialize(
        reinterpret_cast<SkWStream *>(stream),
        reinterpret_cast<const SkSerialProcs *>(procs));
}

size_t SkPicture_approximateOpCount(reskia_picture_t *picture) { //, bool nested
    return reinterpret_cast<SkPicture *>(picture)->approximateOpCount();
}

size_t SkPicture_approximateBytesUsed(reskia_picture_t *picture) { //, SkPicture *picture_2
    return reinterpret_cast<SkPicture *>(picture)->approximateBytesUsed();
}

sk_shader_t SkPicture_makeShader(reskia_picture_t *picture, reskia_picture_tile_mode_t tmx, reskia_picture_tile_mode_t tmy, reskia_picture_filter_mode_t mode, const reskia_matrix_t *localMatrix, const reskia_rect_t *tileRect) {
    return static_sk_shader_make(reinterpret_cast<SkPicture *>(picture)->makeShader(
        static_cast<SkTileMode>(tmx),
        static_cast<SkTileMode>(tmy),
        static_cast<SkFilterMode>(mode),
        reinterpret_cast<const SkMatrix *>(localMatrix),
        reinterpret_cast<const SkRect *>(tileRect)));
}

sk_shader_t SkPicture_makeShader_2(reskia_picture_t *picture, reskia_picture_tile_mode_t tmx, reskia_picture_tile_mode_t tmy, reskia_picture_filter_mode_t mode) {
    return static_sk_shader_make(reinterpret_cast<SkPicture *>(picture)->makeShader(
        static_cast<SkTileMode>(tmx),
        static_cast<SkTileMode>(tmy),
        static_cast<SkFilterMode>(mode)));
}

bool SkPicture_unique(reskia_picture_t *picture) {
    return reinterpret_cast<SkPicture *>(picture)->unique();
}

void SkPicture_ref(reskia_picture_t *picture) {
    reinterpret_cast<SkPicture *>(picture)->ref();
}

void SkPicture_unref(reskia_picture_t *picture) {
    reinterpret_cast<SkPicture *>(picture)->unref();
}

// static

sk_picture_t SkPicture_MakeFromStream(reskia_stream_t *stream, const reskia_deserial_procs_t *procs) {
    return static_sk_picture_make(SkPicture::MakeFromStream(
        reinterpret_cast<SkStream *>(stream),
        reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakeFromData(const reskia_data_t *data, const reskia_deserial_procs_t *procs) {
    return static_sk_picture_make(SkPicture::MakeFromData(
        reinterpret_cast<const SkData *>(data),
        reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakeFromData_2(const void *data, size_t size, const reskia_deserial_procs_t *procs) {
    return static_sk_picture_make(SkPicture::MakeFromData(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakePlaceholder(sk_rect_t cull) {
    return static_sk_picture_make(SkPicture::MakePlaceholder(static_sk_rect_get_entity(cull)));
}

}
