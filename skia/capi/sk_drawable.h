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

void SkDrawable_release(reskia_drawable_t *drawable); // owned: caller が保持する参照を release する。NULL 入力では no-op
void SkDrawable_draw(reskia_drawable_t *drawable, reskia_canvas_t *canvas, const reskia_matrix_t *matrix); // canvas は非 NULL、matrix は NULL 許可。invalid 入力では no-op
void SkDrawable_drawAt(reskia_drawable_t *drawable, reskia_canvas_t *canvas, float x, float y); // canvas は非 NULL。invalid 入力では no-op
sk_drawable_gpu_draw_handler_t SkDrawable_snapGpuDrawHandler(reskia_drawable_t *drawable, int backendApi, const reskia_matrix_t *matrix, const reskia_i_rect_t *clipBounds, const reskia_image_info_t *bufferInfo); // matrix/clipBounds/bufferInfo は非 NULL。invalid 入力や生成不能では 0
sk_picture_t SkDrawable_makePictureSnapshot(reskia_drawable_t *drawable); // NULL 入力や生成不能では 0
uint32_t SkDrawable_getGenerationID(reskia_drawable_t *drawable); // NULL 入力では 0
sk_rect_t SkDrawable_getBounds(reskia_drawable_t *drawable); // NULL 入力では 0
size_t SkDrawable_approximateBytesUsed(reskia_drawable_t *drawable); // NULL 入力では 0
void SkDrawable_notifyDrawingChanged(reskia_drawable_t *drawable); // NULL 入力では no-op
reskia_drawable_flattenable_type_t SkDrawable_getFlattenableType(reskia_drawable_t *drawable); // NULL 入力では -1
sk_flattenable_factory_t SkDrawable_getFactory(reskia_drawable_t *drawable); // NULL 入力や factory なしでは 0
const char * SkDrawable_getTypeName(reskia_drawable_t *drawable); // NULL 入力では NULL
void SkDrawable_flatten(reskia_drawable_t *drawable, reskia_write_buffer_t *write_buffer); // write_buffer は非 NULL。invalid 入力では no-op
sk_data_t SkDrawable_serialize(reskia_drawable_t *drawable, const reskia_serial_procs_t *serial_procs); // serial_procs は NULL 許可。NULL 入力や生成不能では 0
size_t SkDrawable_serializeToMemory(reskia_drawable_t *drawable, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs); // memory_size > 0 では memory 非 NULL。invalid 入力では 0
bool SkDrawable_unique(reskia_drawable_t *drawable); // NULL 入力では false
void SkDrawable_ref(reskia_drawable_t *drawable); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkDrawable_unref(reskia_drawable_t *drawable); // owned: 参照カウントを減らす。NULL 入力では no-op

// static

reskia_drawable_flattenable_type_t SkDrawable_GetFlattenableType(); // () -> SkFlattenable::Type
sk_drawable_t SkDrawable_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs); // data 非 NULL、size > 0。invalid 入力や生成不能では 0
sk_flattenable_factory_t SkDrawable_NameToFactory(const char name[]); // name は非 NULL。未登録や invalid 入力では 0
const char * SkDrawable_FactoryToName(sk_flattenable_factory_t factory); // invalid factory では NULL
void SkDrawable_Register(const char name[], sk_flattenable_factory_t factory); // name/factory は非 NULL。invalid 入力では no-op

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_DRAWABLE_H
