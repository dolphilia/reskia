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

/**
 * owned: releases the caller-held reference. No-op for NULL input.
 * (SkColorMatrixFilter *color_matrix_filter)
 */
void SkColorMatrixFilter_release(reskia_color_matrix_filter_t *color_matrix_filter);
/**
 * out: color and mode may be NULL. Returns false when color_matrix_filter is NULL.
 */
bool SkColorMatrixFilter_asAColorMode(reskia_color_matrix_filter_t *color_matrix_filter, reskia_color_t *color, int *mode);
bool SkColorMatrixFilter_asAColorMatrix(reskia_color_matrix_filter_t *color_matrix_filter, float matrix[20]); // out: matrix must contain at least 20 elements and be non-NULL. Returns false for NULL input.
bool SkColorMatrixFilter_isAlphaUnchanged(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> bool
/**
 * srcColor must be non-NULL. srcCS and dstCS may be NULL. Returns 0 for NULL input.
 */
sk_color_4f_t SkColorMatrixFilter_filterColor4f(reskia_color_matrix_filter_t *color_matrix_filter, const reskia_color_4f_t *srcColor, reskia_color_space_t *srcCS, reskia_color_space_t *dstCS);
sk_color_filter_t SkColorMatrixFilter_makeComposed(reskia_color_matrix_filter_t *color_matrix_filter, sk_color_filter_t colorFilter); // colorFilter 0/invalid means null filter. Returns 0 on failure.
sk_color_filter_t SkColorMatrixFilter_makeWithWorkingColorSpace(reskia_color_matrix_filter_t *color_matrix_filter, sk_color_space_t colorSpace); // colorSpace 0/invalid means null color space. Returns 0 on failure.
sk_flattenable_factory_t SkColorMatrixFilter_getFactory(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> sk_flattenable_factory_t
const char *SkColorMatrixFilter_getTypeName(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> const char *
/**
 * write_buffer must be non-NULL. No-op for NULL input.
 */
void SkColorMatrixFilter_flatten(reskia_color_matrix_filter_t *color_matrix_filter, reskia_write_buffer_t *write_buffer);
reskia_color_matrix_filter_type_t SkColorMatrixFilter_getFlattenableType(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> SkColorMatrixFilter::Type
/**
 * retained data handle. serial_procs may be NULL. Returns 0 when color_matrix_filter is NULL.
 */
sk_data_t SkColorMatrixFilter_serialize(reskia_color_matrix_filter_t *color_matrix_filter, const reskia_serial_procs_t *serial_procs);
/**
 * raw output buffer: memory must contain at least memory_size bytes.
 * Use serialize() to query the required size. Returns 0 for NULL input.
 */
size_t SkColorMatrixFilter_serializeToMemory(reskia_color_matrix_filter_t *color_matrix_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs);
bool SkColorMatrixFilter_unique(reskia_color_matrix_filter_t *color_matrix_filter); // (SkColorMatrixFilter *color_matrix_filter) -> bool
void SkColorMatrixFilter_ref(reskia_color_matrix_filter_t *color_matrix_filter); // retained: increments the reference count. (SkColorMatrixFilter *color_matrix_filter)
void SkColorMatrixFilter_unref(reskia_color_matrix_filter_t *color_matrix_filter); // owned: decrements the reference count. (SkColorMatrixFilter *color_matrix_filter)

// static

sk_color_filter_t SkColorMatrixFilter_MakeLightingFilter(reskia_color_t mul, reskia_color_t add); // Returns 0 on failure. (SkColor mul, SkColor add) -> sk_color_filter_t
/**
 * raw input buffer: data must contain at least size bytes and be non-NULL.
 * procs may be NULL. Returns 0 on failure.
 */
sk_color_filter_t SkColorMatrixFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs);
sk_flattenable_factory_t SkColorMatrixFilter_NameToFactory(const char name[]); // name must be non-NULL. Returns 0 when not found.
const char * SkColorMatrixFilter_FactoryToName(sk_flattenable_factory_t factory); // Returns NULL when factory is 0/invalid.
void SkColorMatrixFilter_Register(const char name[], sk_flattenable_factory_t factory); // name and factory must be non-NULL/non-zero. No-op for invalid input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_MATRIX_FILTER_H
