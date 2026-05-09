//
// Created by dolphilia on 2024/01/10.
//

#include "sk_picture.h"

#include "include/core/SkPicture.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_picture.h"

#include "../handles/static_sk_picture-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_data-internal.h"

#include <utility>

namespace {

SkPicture *as_picture(reskia_picture_t *picture) {
    return reinterpret_cast<SkPicture *>(picture);
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

sk_picture_t make_picture_handle(sk_sp<SkPicture> picture) {
    if (!picture) {
        return 0;
    }
    return static_sk_picture_make(std::move(picture));
}

sk_rect_t make_rect_handle(const SkRect &rect) {
    return static_sk_rect_make(rect);
}

sk_shader_t make_shader_handle(sk_sp<SkShader> shader) {
    if (!shader) {
        return 0;
    }
    return static_sk_shader_make(std::move(shader));
}

bool is_valid_tile_mode(reskia_picture_tile_mode_t mode) {
    return mode >= 0 && mode <= 3;
}

bool is_valid_filter_mode(reskia_picture_filter_mode_t mode) {
    return mode >= 0 && mode <= 1;
}

}  // namespace

extern "C" {

void SkPicture_release(reskia_picture_t *picture) {
    if (picture == nullptr) {
        return;
    }
    as_picture(picture)->unref();
}

void SkPicture_playback(reskia_picture_t *picture, reskia_canvas_t *canvas, reskia_picture_abort_callback_t *callback) {
    if (picture == nullptr || canvas == nullptr) {
        return;
    }
    as_picture(picture)->playback(
        reinterpret_cast<SkCanvas *>(canvas),
        reinterpret_cast<SkPicture::AbortCallback *>(callback));
}

sk_rect_t SkPicture_cullRect(reskia_picture_t *picture) {
    if (picture == nullptr) {
        return 0;
    }
    return make_rect_handle(as_picture(picture)->cullRect());
}

uint32_t SkPicture_uniqueID(reskia_picture_t *picture) {
    if (picture == nullptr) {
        return 0;
    }
    return as_picture(picture)->uniqueID();
}

sk_data_t SkPicture_serialize(reskia_picture_t *picture, const reskia_serial_procs_t *procs) {
    if (picture == nullptr) {
        return 0;
    }
    return make_data_handle(as_picture(picture)->serialize(reinterpret_cast<const SkSerialProcs *>(procs)));
}

void SkPicture_serializeToStream(reskia_picture_t *picture, reskia_w_stream_t *stream, const reskia_serial_procs_t *procs) {
    if (picture == nullptr || stream == nullptr) {
        return;
    }
    as_picture(picture)->serialize(
        reinterpret_cast<SkWStream *>(stream),
        reinterpret_cast<const SkSerialProcs *>(procs));
}

size_t SkPicture_approximateOpCount(reskia_picture_t *picture) { //, bool nested
    if (picture == nullptr) {
        return 0;
    }
    return as_picture(picture)->approximateOpCount();
}

size_t SkPicture_approximateBytesUsed(reskia_picture_t *picture) { //, SkPicture *picture_2
    if (picture == nullptr) {
        return 0;
    }
    return as_picture(picture)->approximateBytesUsed();
}

sk_shader_t SkPicture_makeShader(reskia_picture_t *picture, reskia_picture_tile_mode_t tmx, reskia_picture_tile_mode_t tmy, reskia_picture_filter_mode_t mode, const reskia_matrix_t *localMatrix, const reskia_rect_t *tileRect) {
    if (picture == nullptr || !is_valid_tile_mode(tmx) || !is_valid_tile_mode(tmy) || !is_valid_filter_mode(mode)) {
        return 0;
    }
    return make_shader_handle(as_picture(picture)->makeShader(
        static_cast<SkTileMode>(tmx),
        static_cast<SkTileMode>(tmy),
        static_cast<SkFilterMode>(mode),
        reinterpret_cast<const SkMatrix *>(localMatrix),
        reinterpret_cast<const SkRect *>(tileRect)));
}

sk_shader_t SkPicture_makeShaderWithoutLocalMatrixAndTileRect(reskia_picture_t *picture, reskia_picture_tile_mode_t tmx, reskia_picture_tile_mode_t tmy, reskia_picture_filter_mode_t mode) {
    if (picture == nullptr || !is_valid_tile_mode(tmx) || !is_valid_tile_mode(tmy) || !is_valid_filter_mode(mode)) {
        return 0;
    }
    return make_shader_handle(as_picture(picture)->makeShader(
        static_cast<SkTileMode>(tmx),
        static_cast<SkTileMode>(tmy),
        static_cast<SkFilterMode>(mode)));
}

bool SkPicture_unique(reskia_picture_t *picture) {
    return picture != nullptr && as_picture(picture)->unique();
}

void SkPicture_ref(reskia_picture_t *picture) {
    if (picture == nullptr) {
        return;
    }
    as_picture(picture)->ref();
}

void SkPicture_unref(reskia_picture_t *picture) {
    if (picture == nullptr) {
        return;
    }
    as_picture(picture)->unref();
}

// static

sk_picture_t SkPicture_MakeFromStream(reskia_stream_t *stream, const reskia_deserial_procs_t *procs) {
    if (stream == nullptr) {
        return 0;
    }
    return make_picture_handle(SkPicture::MakeFromStream(
        reinterpret_cast<SkStream *>(stream),
        reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakeFromData(const reskia_data_t *data, const reskia_deserial_procs_t *procs) {
    if (data == nullptr) {
        return 0;
    }
    return make_picture_handle(SkPicture::MakeFromData(
        reinterpret_cast<const SkData *>(data),
        reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakeFromMemory(const void *data, size_t size, const reskia_deserial_procs_t *procs) {
    if (data == nullptr || size == 0) {
        return 0;
    }
    return make_picture_handle(SkPicture::MakeFromData(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_picture_t SkPicture_MakePlaceholder(sk_rect_t cull) {
    return make_picture_handle(SkPicture::MakePlaceholder(static_sk_rect_get_entity(cull)));
}

}
