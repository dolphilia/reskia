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

void SkDrawable_release(reskia_drawable_t *drawable); // owned: caller が保持する参照を release する (SkDrawable *drawable)
void SkDrawable_draw(reskia_drawable_t *drawable, reskia_canvas_t *canvas, const reskia_matrix_t *matrix); // (SkDrawable *drawable, SkCanvas *canvas, const SkMatrix *matrix)
void SkDrawable_draw_2(reskia_drawable_t *drawable, reskia_canvas_t *canvas, float x, float y); // (SkDrawable *drawable, SkCanvas *canvas, SkScalar x, SkScalar y)
sk_drawable_gpu_draw_handler_t SkDrawable_snapGpuDrawHandler(reskia_drawable_t *drawable, int backendApi, const reskia_matrix_t *matrix, const reskia_i_rect_t *clipBounds, const reskia_image_info_t *bufferInfo); // (SkDrawable *drawable, GrBackendApi backendApi, const SkMatrix *matrix, const SkIRect *clipBounds, const SkImageInfo *bufferInfo) -> sk_drawable_gpu_draw_handler_t
sk_picture_t SkDrawable_makePictureSnapshot(reskia_drawable_t *drawable); // (SkDrawable *drawable) -> sk_picture_t
uint32_t SkDrawable_getGenerationID(reskia_drawable_t *drawable); // (SkDrawable *drawable) -> uint32_t
sk_rect_t SkDrawable_getBounds(reskia_drawable_t *drawable); // (SkDrawable *drawable) -> sk_rect_t
size_t SkDrawable_approximateBytesUsed(reskia_drawable_t *drawable); // (SkDrawable *drawable) -> size_t
void SkDrawable_notifyDrawingChanged(reskia_drawable_t *drawable); // (SkDrawable *drawable)
reskia_drawable_flattenable_type_t SkDrawable_getFlattenableType(reskia_drawable_t *drawable); // (SkDrawable *drawable) -> SkFlattenable::Type
sk_flattenable_factory_t SkDrawable_getFactory(reskia_drawable_t *drawable); // (SkDrawable *drawable) -> sk_flattenable_factory_t
const char * SkDrawable_getTypeName(reskia_drawable_t *drawable); // (SkDrawable *drawable) -> const char *
void SkDrawable_flatten(reskia_drawable_t *drawable, reskia_write_buffer_t *write_buffer); // (SkDrawable *drawable, SkWriteBuffer *write_buffer)
sk_data_t SkDrawable_serialize(reskia_drawable_t *drawable, const reskia_serial_procs_t *serial_procs); // (SkDrawable *drawable, const SkSerialProcs *serial_procs) -> sk_data_t
size_t SkDrawable_serialize_2(reskia_drawable_t *drawable, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs); // (SkDrawable *drawable, void *memory, size_t memory_size, const SkSerialProcs *serial_procs) -> size_t
bool SkDrawable_unique(reskia_drawable_t *drawable); // (SkDrawable *drawable) -> bool
void SkDrawable_ref(reskia_drawable_t *drawable); // retained: 参照カウントを増やす (SkDrawable *drawable)
void SkDrawable_unref(reskia_drawable_t *drawable); // owned: 参照カウントを減らす (SkDrawable *drawable)

// static

reskia_drawable_flattenable_type_t SkDrawable_GetFlattenableType(); // () -> SkFlattenable::Type
sk_drawable_t SkDrawable_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs); // (const void *data, size_t size, const SkDeserialProcs *procs) -> sk_drawable_t
sk_flattenable_factory_t SkDrawable_NameToFactory(const char name[]); // (const char name[]) -> sk_flattenable_factory_t
const char * SkDrawable_FactoryToName(sk_flattenable_factory_t factory); // (sk_flattenable_factory_t factory) -> const char *
void SkDrawable_Register(const char name[], sk_flattenable_factory_t factory); // (const char name[], sk_flattenable_factory_t factory)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DRAWABLE_H
