//
// Created by dolphilia on 2024/01/08.
//

#include "sk_drawable.h"

#include "include/core/SkDrawable.h"

#include "../handles/static_sk_drawable_gpu_draw_handler.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_drawable.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_picture-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_drawable_gpu_draw_handler-internal.h"
#include "../handles/static_sk_drawable-internal.h"
#include "../handles/static_sk_data-internal.h"

#include <memory>
#include <utility>

namespace {

SkDrawable *as_drawable(reskia_drawable_t *drawable) {
    return reinterpret_cast<SkDrawable *>(drawable);
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

sk_drawable_t make_drawable_handle(sk_sp<SkDrawable> drawable) {
    if (!drawable) {
        return 0;
    }
    return static_sk_drawable_make(std::move(drawable));
}

sk_drawable_gpu_draw_handler_t make_gpu_draw_handler_handle(std::unique_ptr<SkDrawable::GpuDrawHandler> handler) {
    if (!handler) {
        return 0;
    }
    return static_sk_drawable_gpu_draw_handler_make(std::move(handler));
}

sk_flattenable_factory_t make_flattenable_factory_handle(SkFlattenable::Factory factory) {
    if (factory == nullptr) {
        return 0;
    }
    return static_sk_flattenable_factory_make(factory);
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

}  // namespace

extern "C" {

void SkDrawable_release(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return;
    }
    as_drawable(drawable)->unref();
}

void SkDrawable_draw(reskia_drawable_t *drawable, reskia_canvas_t *canvas, const reskia_matrix_t *matrix) {
    if (drawable == nullptr || canvas == nullptr) {
        return;
    }
    as_drawable(drawable)->draw(reinterpret_cast<SkCanvas *>(canvas), reinterpret_cast<const SkMatrix *>(matrix));
}

void SkDrawable_drawAt(reskia_drawable_t *drawable, reskia_canvas_t *canvas, float x, float y) {
    if (drawable == nullptr || canvas == nullptr) {
        return;
    }
    as_drawable(drawable)->draw(reinterpret_cast<SkCanvas *>(canvas), x, y);
}

sk_drawable_gpu_draw_handler_t SkDrawable_snapGpuDrawHandler(reskia_drawable_t *drawable, int backendApi, const reskia_matrix_t *matrix, const reskia_i_rect_t *clipBounds, const reskia_image_info_t *bufferInfo) {
    if (drawable == nullptr || matrix == nullptr || clipBounds == nullptr || bufferInfo == nullptr) {
        return 0;
    }
    return make_gpu_draw_handler_handle(as_drawable(drawable)->snapGpuDrawHandler(static_cast<GrBackendApi>(backendApi), * reinterpret_cast<const SkMatrix *>(matrix), * reinterpret_cast<const SkIRect *>(clipBounds), * reinterpret_cast<const SkImageInfo *>(bufferInfo)));
}

sk_picture_t SkDrawable_makePictureSnapshot(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return 0;
    }
    return make_picture_handle(as_drawable(drawable)->makePictureSnapshot());
}

uint32_t SkDrawable_getGenerationID(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return 0;
    }
    return as_drawable(drawable)->getGenerationID();
}

sk_rect_t SkDrawable_getBounds(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return 0;
    }
    return make_rect_handle(as_drawable(drawable)->getBounds());
}

size_t SkDrawable_approximateBytesUsed(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return 0;
    }
    return as_drawable(drawable)->approximateBytesUsed();
}

void SkDrawable_notifyDrawingChanged(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return;
    }
    as_drawable(drawable)->notifyDrawingChanged();
}

reskia_drawable_flattenable_type_t SkDrawable_getFlattenableType(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return -1;
    }
    return static_cast<reskia_drawable_flattenable_type_t>(as_drawable(drawable)->getFlattenableType());
}

sk_flattenable_factory_t SkDrawable_getFactory(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(as_drawable(drawable)->getFactory());
}

const char * SkDrawable_getTypeName(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return nullptr;
    }
    return as_drawable(drawable)->getTypeName();
}

void SkDrawable_flatten(reskia_drawable_t *drawable, reskia_write_buffer_t *write_buffer) {
    if (drawable == nullptr || write_buffer == nullptr) {
        return;
    }
    as_drawable(drawable)->flatten(* reinterpret_cast<SkWriteBuffer *>(write_buffer));
}

sk_data_t SkDrawable_serialize(reskia_drawable_t *drawable, const reskia_serial_procs_t *serial_procs) {
    if (drawable == nullptr) {
        return 0;
    }
    return make_data_handle(as_drawable(drawable)->serialize(reinterpret_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkDrawable_serializeToMemory(reskia_drawable_t *drawable, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs) {
    if (drawable == nullptr || (memory_size > 0 && memory == nullptr)) {
        return 0;
    }
    return as_drawable(drawable)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(serial_procs));
}

bool SkDrawable_unique(reskia_drawable_t *drawable) {
    return drawable != nullptr && as_drawable(drawable)->unique();
}

void SkDrawable_ref(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return;
    }
    as_drawable(drawable)->ref();
}

void SkDrawable_unref(reskia_drawable_t *drawable) {
    if (drawable == nullptr) {
        return;
    }
    as_drawable(drawable)->unref();
}

// static

reskia_drawable_flattenable_type_t SkDrawable_GetFlattenableType() {
    return static_cast<reskia_drawable_flattenable_type_t>(SkDrawable::GetFlattenableType());
}

sk_drawable_t SkDrawable_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs) {
    if (data == nullptr || size == 0) {
        return 0;
    }
    return make_drawable_handle(SkDrawable::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkDrawable_NameToFactory(const char name[]) {
    if (name == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(SkDrawable::NameToFactory(name));
}

const char * SkDrawable_FactoryToName(sk_flattenable_factory_t factory) {
    if (factory == 0) {
        return nullptr;
    }
    return SkDrawable::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkDrawable_Register(const char name[], sk_flattenable_factory_t factory) {
    if (name == nullptr || factory == 0) {
        return;
    }
    SkDrawable::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

}
