//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FLATTENABLE_H
#define RAIA_SKIA_SK_FLATTENABLE_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable.h"
#include "../handles/static_sk_flattenable_factory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_flattenable_t reskia_flattenable_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef int32_t reskia_flattenable_type_t;

void SkFlattenable_release(reskia_flattenable_t *flattenable); // owned: releases the caller-held reference. No-op for NULL input.
sk_flattenable_factory_t SkFlattenable_getFactory(reskia_flattenable_t *flattenable); // Returns 0 for NULL input or when no factory is available.
const char * SkFlattenable_getTypeName(reskia_flattenable_t *flattenable); // Returns NULL for NULL input.
void SkFlattenable_flatten(reskia_flattenable_t *flattenable, reskia_write_buffer_t *write_buffer); // write_buffer must be non-NULL. No-op for invalid input.
reskia_flattenable_type_t SkFlattenable_getFlattenableType(reskia_flattenable_t *flattenable); // Returns -1 for NULL input.
sk_data_t SkFlattenable_serialize(reskia_flattenable_t *flattenable, const reskia_serial_procs_t *serial_procs); // serial_procs may be NULL. Returns 0 for NULL input or failure.
/**
 * memory must be non-NULL when memory_size > 0. Returns 0 for invalid input.
 */
size_t SkFlattenable_serializeToMemory(reskia_flattenable_t *flattenable, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs);
bool SkFlattenable_unique(reskia_flattenable_t *flattenable); // Returns false for NULL input.
void SkFlattenable_ref(reskia_flattenable_t *flattenable); // retained: increments the reference count. No-op for NULL input.
void SkFlattenable_unref(reskia_flattenable_t *flattenable); // owned: decrements the reference count. No-op for NULL input.

// static

sk_flattenable_factory_t SkFlattenable_NameToFactory(const char name[]); // name must be non-NULL. Returns 0 for unregistered or invalid input.
const char * SkFlattenable_FactoryToName(sk_flattenable_factory_t factory); // Returns NULL for invalid factory.
void SkFlattenable_Register(const char name[], sk_flattenable_factory_t factory); // name and factory must be non-NULL. No-op for invalid input.
/**
 * type must be valid, data must be non-NULL, and length must be greater than 0.
 * Returns 0 for invalid input or failure.
 */
sk_flattenable_t SkFlattenable_Deserialize(reskia_flattenable_type_t type, const uint8_t *data, size_t length, const reskia_deserial_procs_t *procs);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FLATTENABLE_H
