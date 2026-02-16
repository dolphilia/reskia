//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_MATRIX_FILTER_H
#define RAIA_SKIA_SK_COLOR_MATRIX_FILTER_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_color_4f.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable_factory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_color_matrix_filter_t reskia_color_matrix_filter_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef uint32_t reskia_color_t;
typedef int32_t reskia_color_matrix_filter_type_t;

void SkColorMatrixFilter_release(reskia_color_matrix_filter_t *color_matrix_filter); // owned: caller が保持する参照を release する (SkColorMatrixFilter *color_matrix_filter)
bool SkColorMatrixFilter_asAColorMode(reskia_color_matrix_filter_t *color_matrix_filter, reskia_color_t *color, int *mode); // (SkColorMatrixFilter *color_matrix_filter, SkColor *color, SkBlendMode *mode) -> bool
bool SkColorMatrixFilter_asAColorMatrix(reskia_color_matrix_filter_t *color_matrix_filter, float matrix[20]); // (SkColorMatrixFilter *color_matrix_filter, float matrix[20]) -> bool
bool SkColorMatrixFilter_isAlphaUnchanged(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> bool
reskia_color_t SkColorMatrixFilter_filterColor(reskia_color_matrix_filter_t *color_matrix_filter, reskia_color_t color); // (SkColorMatrixFilter *color_matrix_filter, SkColor color) -> SkColor
sk_color_4f_t SkColorMatrixFilter_filterColor4f(reskia_color_matrix_filter_t *color_matrix_filter, const reskia_color_4f_t *srcColor, reskia_color_space_t *srcCS, reskia_color_space_t *dstCS); // (SkColorMatrixFilter *color_matrix_filter, const SkColor4f *srcColor, SkColorSpace *srcCS, SkColorSpace *dstCS) -> sk_color_4f_t
sk_color_filter_t SkColorMatrixFilter_makeComposed(reskia_color_matrix_filter_t *color_matrix_filter, sk_color_filter_t colorFilter); // (SkColorMatrixFilter *color_matrix_filter, sk_color_filter_t colorFilter) -> sk_color_filter_t
sk_color_filter_t SkColorMatrixFilter_makeWithWorkingColorSpace(reskia_color_matrix_filter_t *color_matrix_filter, sk_color_space_t colorSpace); // (SkColorMatrixFilter *color_matrix_filter, sk_color_space_t colorSpace) -> sk_color_filter_t
sk_flattenable_factory_t SkColorMatrixFilter_getFactory(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> sk_flattenable_factory_t
const char *SkColorMatrixFilter_getTypeName(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> const char *
void SkColorMatrixFilter_flatten(reskia_color_matrix_filter_t *color_matrix_filter, reskia_write_buffer_t *write_buffer); // (SkColorMatrixFilter *color_matrix_filter, SkWriteBuffer * write_buffer)
reskia_color_matrix_filter_type_t SkColorMatrixFilter_getFlattenableType(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> SkColorMatrixFilter::Type
sk_data_t SkColorMatrixFilter_serialize(reskia_color_matrix_filter_t *color_matrix_filter, const reskia_serial_procs_t *serial_procs); // (SkColorMatrixFilter *color_matrix_filter, const SkSerialProcs *serial_procs) -> sk_data_t
size_t SkColorMatrixFilter_serializeToMemory(reskia_color_matrix_filter_t *color_matrix_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs); // (SkColorMatrixFilter *color_matrix_filter, void *memory, size_t memory_size, const SkSerialProcs *serial_procs) -> size_t
bool SkColorMatrixFilter_unique(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> bool
void SkColorMatrixFilter_ref(reskia_color_matrix_filter_t *color_matrix_filter); // retained: 参照カウントを増やす (SkColorMatrixFilter *color_matrix_filter)
void SkColorMatrixFilter_unref(reskia_color_matrix_filter_t *color_matrix_filter); // owned: 参照カウントを減らす (SkColorMatrixFilter *color_matrix_filter)

// static

sk_color_filter_t SkColorMatrixFilter_MakeLightingFilter(reskia_color_t mul, reskia_color_t add); // (SkColor mul, SkColor add) -> sk_color_filter_t
sk_color_filter_t SkColorMatrixFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs); // (const void *data, size_t size, const SkDeserialProcs *procs) -> sk_color_filter_t
sk_flattenable_factory_t SkColorMatrixFilter_NameToFactory(const char name[]); // (const char name[]) -> sk_flattenable_factory_t
const char * SkColorMatrixFilter_FactoryToName(sk_flattenable_factory_t factory); // (sk_flattenable_factory_t factory) -> const char *
void SkColorMatrixFilter_Register(const char name[], sk_flattenable_factory_t factory); // (const char name[], sk_flattenable_factory_t factory)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_MATRIX_FILTER_H
