//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_IMAGE_FILTER_H
#define RAIA_SKIA_SK_IMAGE_FILTER_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_data.h"
#include "../static/static_sk_flattenable_factory.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_image_filter.h"
#include "../static/static_sk_rect.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_filter_t reskia_color_filter_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_filter_t reskia_image_filter_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef int32_t reskia_image_filter_map_direction_t;
typedef int32_t reskia_image_filter_type_t;

void SkImageFilter_delete(reskia_image_filter_t *image_filter); // owned: caller が保持する参照を release する (SkImageFilter *image_filter)
sk_i_rect_t SkImageFilter_filterBounds(reskia_image_filter_t *image_filter, const reskia_i_rect_t *src, const reskia_matrix_t *ctm, reskia_image_filter_map_direction_t direction, const reskia_i_rect_t *inputRect); // (SkImageFilter *image_filter, const SkIRect *src, const SkMatrix *ctm, SkImageFilter::MapDirection direction, const SkIRect *inputRect) -> sk_i_rect_t
bool SkImageFilter_isColorFilterNode(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr); // (SkImageFilter *image_filter, SkColorFilter **filterPtr) -> bool
bool SkImageFilter_asColorFilter(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr); // (SkImageFilter *image_filter, SkColorFilter **filterPtr) -> bool
bool SkImageFilter_asAColorFilter(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr); // (SkImageFilter *image_filter, SkColorFilter **filterPtr) -> bool
int SkImageFilter_countInputs(reskia_image_filter_t *image_filter); // (SkImageFilter *image_filter) -> int
const reskia_image_filter_t *SkImageFilter_getInput(reskia_image_filter_t *image_filter, int i); // borrowed: 解放不要の借用ポインタ (SkImageFilter *image_filter, int i) -> const SkImageFilter *
sk_rect_t SkImageFilter_computeFastBounds(reskia_image_filter_t *image_filter, const reskia_rect_t *bounds); // (SkImageFilter *image_filter, const SkRect *bounds) -> sk_rect_t
bool SkImageFilter_canComputeFastBounds(reskia_image_filter_t *image_filter); // (SkImageFilter *image_filter) -> bool
sk_image_filter_t SkImageFilter_makeWithLocalMatrix(reskia_image_filter_t *image_filter, const reskia_matrix_t *matrix); // (SkImageFilter *image_filter, const SkMatrix *matrix) -> sk_image_filter_t
sk_flattenable_factory_t SkImageFilter_getFactory(reskia_image_filter_t *image_filter); // (SkImageFilter *image_filter) -> sk_flattenable_factory_t
const char *SkImageFilter_getTypeName(reskia_image_filter_t *image_filter); // (SkImageFilter *image_filter) -> const char *
void SkImageFilter_flatten(reskia_image_filter_t *image_filter, reskia_write_buffer_t *buffer); // (SkImageFilter *image_filter, SkWriteBuffer *buffer)
reskia_image_filter_type_t SkImageFilter_getFlattenableType(reskia_image_filter_t *image_filter); // (SkImageFilter *image_filter) -> SkImageFilter::Type
sk_data_t SkImageFilter_serialize(reskia_image_filter_t *image_filter, const reskia_serial_procs_t *procs); // (SkImageFilter *image_filter, const SkSerialProcs *procs) -> sk_data_t
size_t SkImageFilter_serialize_2(reskia_image_filter_t *image_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs); // (SkImageFilter *image_filter, void *memory, size_t memory_size, const SkSerialProcs *procs) -> size_t
bool SkImageFilter_unique(reskia_image_filter_t *image_filter); // (SkImageFilter *image_filter) -> bool
void SkImageFilter_ref(reskia_image_filter_t *image_filter); // retained: 参照カウントを増やす (SkImageFilter *image_filter)
void SkImageFilter_unref(reskia_image_filter_t *image_filter); // owned: 参照カウントを減らす (SkImageFilter *image_filter)

// static

sk_image_filter_t SkImageFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs); // (const void *data, size_t size, const SkDeserialProcs *procs) -> sk_image_filter_t
sk_flattenable_factory_t SkImageFilter_NameToFactory(const char name[]); // (const char name[]) -> sk_flattenable_factory_t
const char *SkImageFilter_FactoryToName(sk_flattenable_factory_t factory); // (sk_flattenable_factory_t factory) -> const char *
void SkImageFilter_Register(const char name[], sk_flattenable_factory_t factory); // (const char name[], sk_flattenable_factory_t factory)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_FILTER_H
