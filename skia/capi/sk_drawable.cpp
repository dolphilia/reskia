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

extern "C" {

void SkDrawable_delete(reskia_drawable_t *drawable) {
    reinterpret_cast<SkDrawable *>(drawable)->unref();
}

void SkDrawable_draw(reskia_drawable_t *drawable, reskia_canvas_t *canvas, const reskia_matrix_t *matrix) {
    reinterpret_cast<SkDrawable *>(drawable)->draw(reinterpret_cast<SkCanvas *>(canvas), reinterpret_cast<const SkMatrix *>(matrix));
}

void SkDrawable_draw_2(reskia_drawable_t *drawable, reskia_canvas_t *canvas, float x, float y) {
    reinterpret_cast<SkDrawable *>(drawable)->draw(reinterpret_cast<SkCanvas *>(canvas), x, y);
}

sk_drawable_gpu_draw_handler_t SkDrawable_snapGpuDrawHandler(reskia_drawable_t *drawable, int backendApi, const reskia_matrix_t *matrix, const reskia_i_rect_t *clipBounds, const reskia_image_info_t *bufferInfo) {
    return static_sk_drawable_gpu_draw_handler_make(reinterpret_cast<SkDrawable *>(drawable)->snapGpuDrawHandler(static_cast<GrBackendApi>(backendApi), * reinterpret_cast<const SkMatrix *>(matrix), * reinterpret_cast<const SkIRect *>(clipBounds), * reinterpret_cast<const SkImageInfo *>(bufferInfo)));
}

sk_picture_t SkDrawable_makePictureSnapshot(reskia_drawable_t *drawable) {
    return static_sk_picture_make(reinterpret_cast<SkDrawable *>(drawable)->makePictureSnapshot());
}

uint32_t SkDrawable_getGenerationID(reskia_drawable_t *drawable) {
    return reinterpret_cast<SkDrawable *>(drawable)->getGenerationID();
}

sk_rect_t SkDrawable_getBounds(reskia_drawable_t *drawable) {
    return static_sk_rect_make(reinterpret_cast<SkDrawable *>(drawable)->getBounds());
}

size_t SkDrawable_approximateBytesUsed(reskia_drawable_t *drawable) {
    return reinterpret_cast<SkDrawable *>(drawable)->approximateBytesUsed();
}

void SkDrawable_notifyDrawingChanged(reskia_drawable_t *drawable) {
    reinterpret_cast<SkDrawable *>(drawable)->notifyDrawingChanged();
}

reskia_drawable_flattenable_type_t SkDrawable_getFlattenableType(reskia_drawable_t *drawable) {
    return static_cast<reskia_drawable_flattenable_type_t>(reinterpret_cast<SkDrawable *>(drawable)->getFlattenableType());
}

sk_flattenable_factory_t SkDrawable_getFactory(reskia_drawable_t *drawable) {
    return static_sk_flattenable_factory_make(reinterpret_cast<SkDrawable *>(drawable)->getFactory());
}

const char * SkDrawable_getTypeName(reskia_drawable_t *drawable) {
    return reinterpret_cast<SkDrawable *>(drawable)->getTypeName();
}

void SkDrawable_flatten(reskia_drawable_t *drawable, reskia_write_buffer_t *write_buffer) {
    reinterpret_cast<SkDrawable *>(drawable)->flatten(* reinterpret_cast<SkWriteBuffer *>(write_buffer));
}

sk_data_t SkDrawable_serialize(reskia_drawable_t *drawable, const reskia_serial_procs_t *serial_procs) {
    return static_sk_data_make(reinterpret_cast<SkDrawable *>(drawable)->serialize(reinterpret_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkDrawable_serialize_2(reskia_drawable_t *drawable, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs) {
    return reinterpret_cast<SkDrawable *>(drawable)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(serial_procs));
}

bool SkDrawable_unique(reskia_drawable_t *drawable) {
    return reinterpret_cast<SkDrawable *>(drawable)->unique();
}

void SkDrawable_ref(reskia_drawable_t *drawable) {
    reinterpret_cast<SkDrawable *>(drawable)->ref();
}

void SkDrawable_unref(reskia_drawable_t *drawable) {
    reinterpret_cast<SkDrawable *>(drawable)->unref();
}

// static

reskia_drawable_flattenable_type_t SkDrawable_GetFlattenableType() {
    return static_cast<reskia_drawable_flattenable_type_t>(SkDrawable::GetFlattenableType());
}

sk_drawable_t SkDrawable_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs) {
    return static_sk_drawable_make(SkDrawable::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkDrawable_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkDrawable::NameToFactory(name));
}

const char * SkDrawable_FactoryToName(sk_flattenable_factory_t factory) {
    return SkDrawable::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkDrawable_Register(const char name[], sk_flattenable_factory_t factory) {
    SkDrawable::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

}
