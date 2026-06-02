//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_MASK_FILTER_H
#define RAIA_SKIA_SK_MASK_FILTER_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable_factory.h"
#include "../handles/static_sk_mask_filter.h"

typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_mask_filter_t reskia_mask_filter_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef int32_t reskia_mask_filter_type_t;
typedef int32_t reskia_mask_filter_blur_style_t;

void SkMaskFilter_release(reskia_mask_filter_t *maskFilter); // Owned reference: releases the caller-held reference. No-op for NULL input.
sk_flattenable_factory_t SkMaskFilter_getFactory(reskia_mask_filter_t *mask_filter); // Returns 0 for NULL input or when no factory exists.
const char *SkMaskFilter_getTypeName(reskia_mask_filter_t *mask_filter); // Borrowed; do not free. Returns NULL for NULL input.
void SkMaskFilter_flatten(reskia_mask_filter_t *mask_filter, reskia_write_buffer_t *buffer); // buffer must be non-NULL. No-op for NULL input.
reskia_mask_filter_type_t SkMaskFilter_getFlattenableType(reskia_mask_filter_t *mask_filter); // Returns -1 for NULL input.
sk_data_t SkMaskFilter_serialize(reskia_mask_filter_t *mask_filter, const reskia_serial_procs_t *procs); // procs may be NULL. Returns 0 for NULL input or creation failure.
/**
 * memory must be non-NULL when memory_size is greater than 0.
 * Returns 0 for NULL input.
 */
size_t SkMaskFilter_serializeToMemory(reskia_mask_filter_t *mask_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs);
bool SkMaskFilter_unique(reskia_mask_filter_t *mask_filter); // Returns false for NULL input.
void SkMaskFilter_ref(reskia_mask_filter_t *mask_filter); // Retains the object by incrementing the reference count. No-op for NULL input.
void SkMaskFilter_unref(reskia_mask_filter_t *mask_filter); // Releases the object by decrementing the reference count. No-op for NULL input.

// static

sk_mask_filter_t SkMaskFilter_MakeBlur(reskia_mask_filter_blur_style_t style, float sigma, bool respectCTM); // Returns 0 on creation failure.
sk_mask_filter_t SkMaskFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs); // data must be non-NULL when size is greater than 0. Returns 0 for NULL, empty, or failed input.
sk_flattenable_factory_t SkMaskFilter_NameToFactory(const char name[]); // name must be NUL-terminated and non-NULL. Returns 0 for unregistered names or NULL input.
const char *SkMaskFilter_FactoryToName(sk_flattenable_factory_t factory); // Borrowed; do not free. Returns NULL for factory 0.
void SkMaskFilter_Register(const char name[], sk_flattenable_factory_t factory); // name must be non-NULL, and factory must be nonzero. No-op for NULL input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MASK_FILTER_H
