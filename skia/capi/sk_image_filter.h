//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_IMAGE_FILTER_H
#define RAIA_SKIA_SK_IMAGE_FILTER_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable_factory.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_image_filter.h"
#include "../handles/static_sk_rect.h"

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

void SkImageFilter_release(reskia_image_filter_t *image_filter); // owned: NULL image_filter is no-op.
sk_i_rect_t SkImageFilter_filterBounds(reskia_image_filter_t *image_filter, const reskia_i_rect_t *src, const reskia_matrix_t *ctm, reskia_image_filter_map_direction_t direction, const reskia_i_rect_t *inputRect); // image_filter/src/ctm are required; inputRect may be NULL.
bool SkImageFilter_isColorFilterNode(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr); // filterPtr may be NULL; NULL image_filter returns false.
bool SkImageFilter_asColorFilter(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr); // filterPtr may be NULL; NULL image_filter returns false.
bool SkImageFilter_asAColorFilter(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr); // filterPtr may be NULL; NULL image_filter returns false.
int SkImageFilter_countInputs(reskia_image_filter_t *image_filter); // NULL image_filter returns 0.
const reskia_image_filter_t *SkImageFilter_getInput(reskia_image_filter_t *image_filter, int i); // borrowed; NULL image_filter returns NULL.
sk_rect_t SkImageFilter_computeFastBounds(reskia_image_filter_t *image_filter, const reskia_rect_t *bounds); // image_filter/bounds are required.
bool SkImageFilter_canComputeFastBounds(reskia_image_filter_t *image_filter); // NULL image_filter returns false.
sk_image_filter_t SkImageFilter_makeWithLocalMatrix(reskia_image_filter_t *image_filter, const reskia_matrix_t *matrix); // image_filter/matrix are required; NULL result returns 0.
sk_flattenable_factory_t SkImageFilter_getFactory(reskia_image_filter_t *image_filter); // NULL image_filter or missing factory returns 0.
const char *SkImageFilter_getTypeName(reskia_image_filter_t *image_filter); // NULL image_filter returns NULL.
void SkImageFilter_flatten(reskia_image_filter_t *image_filter, reskia_write_buffer_t *buffer); // image_filter/buffer are required; NULL input is no-op.
reskia_image_filter_type_t SkImageFilter_getFlattenableType(reskia_image_filter_t *image_filter); // NULL image_filter returns 0.
sk_data_t SkImageFilter_serialize(reskia_image_filter_t *image_filter, const reskia_serial_procs_t *procs); // procs may be NULL; NULL image_filter/result returns 0.
size_t SkImageFilter_serializeToMemory(reskia_image_filter_t *image_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs); // procs may be NULL; NULL image_filter or NULL memory with nonzero size returns 0.
bool SkImageFilter_unique(reskia_image_filter_t *image_filter); // NULL image_filter returns false.
void SkImageFilter_ref(reskia_image_filter_t *image_filter); // retained: NULL image_filter is no-op.
void SkImageFilter_unref(reskia_image_filter_t *image_filter); // owned: NULL image_filter is no-op.

// static

sk_image_filter_t SkImageFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs); // data/procs may be NULL only as upstream allows; NULL data or zero size returns 0.
sk_flattenable_factory_t SkImageFilter_NameToFactory(const char name[]); // NULL name or missing factory returns 0.
const char *SkImageFilter_FactoryToName(sk_flattenable_factory_t factory); // invalid factory returns NULL.
void SkImageFilter_Register(const char name[], sk_flattenable_factory_t factory); // name/factory are required; invalid input is no-op.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_FILTER_H
