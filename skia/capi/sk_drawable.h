//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_DRAWABLE_H
#define RAIA_SKIA_SK_DRAWABLE_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_drawable.h"
#include "../handles/static_sk_drawable_gpu_draw_handler.h"
#include "../handles/static_sk_flattenable_factory.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_rect.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_drawable_t reskia_drawable_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef int32_t reskia_drawable_flattenable_type_t;

void SkDrawable_release(reskia_drawable_t *drawable); // Owned reference: releases the caller-held reference. No-op for NULL input.
/**
 * canvas must be non-NULL, and matrix may be NULL.
 * No-op for invalid input.
 */
void SkDrawable_draw(reskia_drawable_t *drawable, reskia_canvas_t *canvas, const reskia_matrix_t *matrix);
void SkDrawable_drawAt(reskia_drawable_t *drawable, reskia_canvas_t *canvas, float x, float y); // canvas must be non-NULL. No-op for invalid input.
/**
 * matrix, clipBounds, and bufferInfo must be non-NULL.
 * Returns 0 for invalid input or creation failure.
 */
sk_drawable_gpu_draw_handler_t SkDrawable_snapGpuDrawHandler(reskia_drawable_t *drawable, int backendApi, const reskia_matrix_t *matrix, const reskia_i_rect_t *clipBounds, const reskia_image_info_t *bufferInfo);
sk_picture_t SkDrawable_makePictureSnapshot(reskia_drawable_t *drawable); // Returns 0 for NULL input or creation failure.
uint32_t SkDrawable_getGenerationID(reskia_drawable_t *drawable); // Returns 0 for NULL input.
sk_rect_t SkDrawable_getBounds(reskia_drawable_t *drawable); // Returns 0 for NULL input.
size_t SkDrawable_approximateBytesUsed(reskia_drawable_t *drawable); // Returns 0 for NULL input.
void SkDrawable_notifyDrawingChanged(reskia_drawable_t *drawable); // No-op for NULL input.
reskia_drawable_flattenable_type_t SkDrawable_getFlattenableType(reskia_drawable_t *drawable); // Returns -1 for NULL input.
sk_flattenable_factory_t SkDrawable_getFactory(reskia_drawable_t *drawable); // Returns 0 for NULL input or when no factory exists.
const char * SkDrawable_getTypeName(reskia_drawable_t *drawable); // Returns NULL for NULL input.
void SkDrawable_flatten(reskia_drawable_t *drawable, reskia_write_buffer_t *write_buffer); // write_buffer must be non-NULL. No-op for invalid input.
sk_data_t SkDrawable_serialize(reskia_drawable_t *drawable, const reskia_serial_procs_t *serial_procs); // serial_procs may be NULL. Returns 0 for NULL input or creation failure.
/**
 * memory must be non-NULL when memory_size is greater than 0.
 * Returns 0 for invalid input.
 */
size_t SkDrawable_serializeToMemory(reskia_drawable_t *drawable, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs);
bool SkDrawable_unique(reskia_drawable_t *drawable); // Returns false for NULL input.
void SkDrawable_ref(reskia_drawable_t *drawable); // Retains the object by incrementing the reference count. No-op for NULL input.
void SkDrawable_unref(reskia_drawable_t *drawable); // Releases the object by decrementing the reference count. No-op for NULL input.

// static

reskia_drawable_flattenable_type_t SkDrawable_GetFlattenableType(); // () -> SkFlattenable::Type
sk_drawable_t SkDrawable_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs); // data must be non-NULL, and size must be greater than 0. Returns 0 for invalid input or creation failure.
sk_flattenable_factory_t SkDrawable_NameToFactory(const char name[]); // name must be non-NULL. Returns 0 for unregistered names or invalid input.
const char * SkDrawable_FactoryToName(sk_flattenable_factory_t factory); // Returns NULL for invalid factory.
void SkDrawable_Register(const char name[], sk_flattenable_factory_t factory); // name and factory must be non-NULL. No-op for invalid input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DRAWABLE_H
