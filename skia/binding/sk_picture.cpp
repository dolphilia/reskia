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

void SkPicture_delete(void *picture) {
    static_cast<SkPicture *>(picture)->unref();
}

void SkPicture_playback(void *picture, void *canvas, void *callback) {
    static_cast<SkPicture *>(picture)->playback(static_cast<SkCanvas *>(canvas), static_cast<SkPicture::AbortCallback *>(callback));
}

sk_rect_t SkPicture_cullRect(void *picture) {
    return static_sk_rect_make(static_cast<SkPicture *>(picture)->cullRect());
}

uint32_t SkPicture_uniqueID(void *picture) {
    return static_cast<SkPicture *>(picture)->uniqueID();
}

sk_data_t SkPicture_serialize(void *picture, const void *procs) {
    return static_sk_data_make(static_cast<SkPicture *>(picture)->serialize(static_cast<const SkSerialProcs *>(procs)));
}

void SkPicture_serialize_2(void *picture, void *stream, const void *procs) {
    static_cast<SkPicture *>(picture)->serialize(static_cast<SkWStream *>(stream), static_cast<const SkSerialProcs *>(procs));
}

size_t SkPicture_approximateOpCount(void *picture) { //, bool nested
    return static_cast<SkPicture *>(picture)->approximateBytesUsed();
}

size_t SkPicture_approximateBytesUsed(void *picture) { //, SkPicture *picture_2
    return static_cast<SkPicture *>(picture)->approximateBytesUsed();
}

sk_shader_t SkPicture_makeShader(void *picture, int tmx, int tmy, int mode, const void *localMatrix, const void *tileRect) {
    return static_sk_shader_make(static_cast<SkPicture *>(picture)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), static_cast<SkFilterMode>(mode), static_cast<const SkMatrix *>(localMatrix), static_cast<const SkRect *>(tileRect)));
}

sk_shader_t SkPicture_makeShader_2(void *picture, int tmx, int tmy, int mode) {
    return static_sk_shader_make(static_cast<SkPicture *>(picture)->makeShader(static_cast<SkTileMode>(tmx), static_cast<SkTileMode>(tmy), static_cast<SkFilterMode>(mode)));
}

bool SkPicture_unique(void *picture) {
    return static_cast<SkPicture *>(picture)->unique();
}

void SkPicture_ref(void *picture) {
    static_cast<SkPicture *>(picture)->ref();
}

void SkPicture_unref(void *picture) {
    static_cast<SkPicture *>(picture)->unref();
}

// static

sk_picture_t SkPicture_MakeFromStream(void *stream, const void *procs) {
    return static_sk_picture_make(SkPicture::MakeFromStream(static_cast<SkStream *>(stream), static_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakeFromData(const void *data, const void *procs) {
    return static_sk_picture_make(SkPicture::MakeFromData(static_cast<const SkData *>(data), static_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakeFromData_2(const void *data, size_t size, const void *procs) {
    return static_sk_picture_make(SkPicture::MakeFromData(data, size, static_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakePlaceholder(sk_rect_t cull) {
    return static_sk_picture_make(SkPicture::MakePlaceholder(static_sk_rect_get_entity(cull)));
}

}
