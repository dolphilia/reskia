//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_COLOR_FILTER_H
#define RAIA_SKIA_SK_COLOR_FILTER_H

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
typedef struct reskia_color_filter_t reskia_color_filter_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef uint32_t reskia_color_t;
typedef int32_t reskia_color_filter_type_t;

void SkColorFilter_release(reskia_color_filter_t *color_filter); // owned: releases the caller-held reference. No-op for NULL input. (SkColorFilter *color_filter)
/**
 * out: color and mode may be NULL. Returns false when color_filter is NULL.
 * (SkColorFilter *color_filter, SkColor *color, SkBlendMode *mode) -> bool
 */
bool SkColorFilter_asAColorMode(reskia_color_filter_t *color_filter, reskia_color_t *color, int *mode);
/**
 * out: matrix must contain at least 20 elements and be non-NULL. Returns false for NULL input.
 * (SkColorFilter *color_filter, float matrix[20]) -> bool
 */
bool SkColorFilter_asAColorMatrix(reskia_color_filter_t *color_filter, float matrix[20]);
bool SkColorFilter_isAlphaUnchanged(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> bool
/**
 * srcColor must be non-NULL. srcCS and dstCS may be NULL. Returns 0 for NULL input.
 * (SkColorFilter *color_filter, const SkColor4f *srcColor, SkColorSpace *srcCS, SkColorSpace *dstCS) -> sk_color_4f_t
 */
sk_color_4f_t SkColorFilter_filterColor4f(reskia_color_filter_t *color_filter, const reskia_color_4f_t *srcColor, reskia_color_space_t *srcCS, reskia_color_space_t *dstCS);
sk_color_filter_t SkColorFilter_makeComposed(reskia_color_filter_t *color_filter, sk_color_filter_t inner); // inner 0/invalid means null filter. Returns 0 on failure. (SkColorFilter *color_filter, sk_color_filter_t inner) -> sk_color_filter_t
sk_color_filter_t SkColorFilter_makeWithWorkingColorSpace(reskia_color_filter_t *color_filter, sk_color_space_t colorSpace); // colorSpace 0/invalid means null color space. Returns 0 on failure. (SkColorFilter *color_filter, sk_color_space_t colorSpace) -> sk_color_filter_t
sk_flattenable_factory_t SkColorFilter_getFactory(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> sk_flattenable_factory_t
const char *SkColorFilter_getTypeName(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> const char *
/**
 * write_buffer must be non-NULL. No-op for NULL input.
 * (SkColorFilter *color_filter, SkWriteBuffer *write_buffer)
 */
void SkColorFilter_flatten(reskia_color_filter_t *color_filter, reskia_write_buffer_t *write_buffer);
reskia_color_filter_type_t SkColorFilter_getFlattenableType(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> SkColorFilter::Type
/**
 * retained data handle. serial_procs may be NULL. Returns 0 when color_filter is NULL.
 * (SkColorFilter *color_filter, const SkSerialProcs *serial_procs) -> sk_data_t
 */
sk_data_t SkColorFilter_serialize(reskia_color_filter_t *color_filter, const reskia_serial_procs_t *serial_procs);
/**
 * raw output buffer: memory must contain at least memory_size bytes.
 * Use serialize() to query the required size. Returns 0 when color_filter is NULL.
 */
size_t SkColorFilter_serializeToMemory(reskia_color_filter_t *color_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs);
bool SkColorFilter_unique(reskia_color_filter_t *color_filter); // (SkColorFilter *color_filter) -> bool
void SkColorFilter_ref(reskia_color_filter_t *color_filter); // retained: increments the reference count. (SkColorFilter *color_filter)
void SkColorFilter_unref(reskia_color_filter_t *color_filter); // owned: decrements the reference count. (SkColorFilter *color_filter)

// static

/**
 * raw input buffer: data must contain at least size bytes and be non-NULL.
 * procs may be NULL. Returns 0 on failure.
 */
sk_color_filter_t SkColorFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs);
sk_flattenable_factory_t SkColorFilter_NameToFactory(const char name[]); // name must be non-NULL. Returns 0 when not found.
const char *SkColorFilter_FactoryToName(sk_flattenable_factory_t factory); // Returns NULL when factory is 0/invalid.
void SkColorFilter_Register(const char name[], sk_flattenable_factory_t factory); // name and factory must be non-NULL/non-zero. No-op for invalid input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_COLOR_FILTER_H
