//
// Created by dolphilia on 2024/01/08.
//

#include "sk_drawable.h"

#include "include/core/SkDrawable.h"

#include "../static/static_sk_drawable_gpu_draw_handler.h"
#include "../static/static_sk_picture.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_drawable.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_flattenable_factory.h"

#include "../static/static_sk_picture-internal.h"
#include "../static/static_sk_rect-internal.h"
#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_drawable_gpu_draw_handler-internal.h"
#include "../static/static_sk_drawable-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkDrawable_delete(void *drawable) {
    delete static_cast<SkDrawable *>(drawable);
}

void SkDrawable_draw(void *drawable, void * canvas, const void * matrix) {
    static_cast<SkDrawable *>(drawable)->draw(static_cast<SkCanvas *>(canvas), static_cast<const SkMatrix *>(matrix));
}

void SkDrawable_draw_2(void *drawable, void *canvas, float x, float y) {
    static_cast<SkDrawable *>(drawable)->draw(static_cast<SkCanvas *>(canvas), x, y);
}

sk_drawable_gpu_draw_handler_t SkDrawable_snapGpuDrawHandler(void *drawable, int backendApi, const void *matrix, const void *clipBounds, const void *bufferInfo) {
    return static_sk_drawable_gpu_draw_handler_make(static_cast<SkDrawable *>(drawable)->snapGpuDrawHandler(static_cast<GrBackendApi>(backendApi), * static_cast<const SkMatrix *>(matrix), * static_cast<const SkIRect *>(clipBounds), * static_cast<const SkImageInfo *>(bufferInfo)));
}

sk_picture_t SkDrawable_makePictureSnapshot(void *drawable) {
    return static_sk_picture_make(static_cast<SkDrawable *>(drawable)->makePictureSnapshot());
}

uint32_t SkDrawable_getGenerationID(void *drawable) {
    return static_cast<SkDrawable *>(drawable)->getGenerationID();
}

sk_rect_t SkDrawable_getBounds(void *drawable) {
    return static_sk_rect_make(static_cast<SkDrawable *>(drawable)->getBounds());
}

size_t SkDrawable_approximateBytesUsed(void *drawable) {
    return static_cast<SkDrawable *>(drawable)->approximateBytesUsed();
}

void SkDrawable_notifyDrawingChanged(void *drawable) {
    static_cast<SkDrawable *>(drawable)->notifyDrawingChanged();
}

int SkDrawable_getFlattenableType(void *drawable) {
    return static_cast<SkDrawable *>(drawable)->getFlattenableType();
}

sk_flattenable_factory_t SkDrawable_getFactory(void *drawable) {
    return static_sk_flattenable_factory_make(static_cast<SkDrawable *>(drawable)->getFactory());
}

const char * SkDrawable_getTypeName(void *drawable) {
    return static_cast<SkDrawable *>(drawable)->getTypeName();
}

void SkDrawable_flatten(void *drawable, void *write_buffer) {
    static_cast<SkDrawable *>(drawable)->flatten(* static_cast<SkWriteBuffer *>(write_buffer));
}

sk_data_t SkDrawable_serialize(void *drawable, const void *serial_procs) {
    return static_sk_data_make(static_cast<SkDrawable *>(drawable)->serialize(static_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkDrawable_serialize_2(void *drawable, void *memory, size_t memory_size, const void *serial_procs) {
    return static_cast<SkDrawable *>(drawable)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(serial_procs));
}

bool SkDrawable_unique(void *drawable) {
    return static_cast<SkDrawable *>(drawable)->unique();
}

void SkDrawable_ref(void *drawable) {
    static_cast<SkDrawable *>(drawable)->ref();
}

void SkDrawable_unref(void *drawable) {
    static_cast<SkDrawable *>(drawable)->unref();
}

// static

int SkDrawable_GetFlattenableType() {
    return SkDrawable::GetFlattenableType();
}

sk_drawable_t SkDrawable_Deserialize(const void *data, size_t size, const void *procs) {
    return static_sk_drawable_make(SkDrawable::Deserialize(data, size, static_cast<const SkDeserialProcs *>(procs)));
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
