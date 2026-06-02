//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_SK_BLENDER_H
#define RAIA_SKIA_SK_BLENDER_H

#include <stddef.h>
#include <stdint.h>
#include "sk_blend_mode.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable.h"
#include "../handles/static_sk_flattenable_factory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_blender_t reskia_blender_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef int32_t reskia_blender_type_t;

void SkBlender_release(reskia_blender_t *blender); // Owned reference: releases the caller-held reference. No-op for NULL blender. (SkBlender *blender)
sk_flattenable_factory_t SkBlender_getFactory(reskia_blender_t *blender); // Returns 0 for NULL blender or when no factory exists. (SkBlender *blender) -> sk_flattenable_factory_t
const char *SkBlender_getTypeName(reskia_blender_t *blender); // Returns NULL for NULL blender. (SkBlender *blender) -> const char *
/**
 * blender and write_buffer must be non-NULL. NULL input is a no-op.
 * (SkBlender *blender, SkWriteBuffer *write_buffer)
 */
void SkBlender_flatten(reskia_blender_t *blender, reskia_write_buffer_t *write_buffer);
reskia_blender_type_t SkBlender_getFlattenableType(reskia_blender_t *blender); // Returns 0 for NULL blender. (SkBlender *blender) -> SkBlender::Type
/**
 * serial_procs may be NULL. Returns 0 for NULL blender or creation failure.
 * (SkBlender *blender, const SkSerialProcs *serial_procs) -> sk_data_t
 */
sk_data_t SkBlender_serialize(reskia_blender_t *blender, const reskia_serial_procs_t *serial_procs);
/**
 * serial_procs may be NULL. Returns 0 for NULL blender or when memory is NULL with nonzero size.
 * (SkBlender *blender, void *memory, size_t memory_size, const SkSerialProcs *serial_procs) -> size_t
 */
size_t SkBlender_serializeToMemory(reskia_blender_t *blender, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs);
bool SkBlender_unique(reskia_blender_t *blender); // Returns false for NULL blender. (SkBlender *blender) -> bool
void SkBlender_ref(reskia_blender_t *blender); // Retains the object by incrementing the reference count. No-op for NULL blender. (SkBlender *blender)
void SkBlender_unref(reskia_blender_t *blender); // Releases the object by decrementing the reference count. No-op for NULL blender. (SkBlender *blender)

// static

sk_blender_t SkBlender_Mode(reskia_blend_mode_t mode); // Returns 0 on creation failure. (SkBlendMode mode) -> sk_blender_t
sk_flattenable_factory_t SkBlender_NameToFactory(const char * name); // Returns 0 for NULL or unregistered name. (const char *name) -> sk_flattenable_factory_t
const char *SkBlender_FactoryToName(sk_flattenable_factory_t factory); // Returns NULL for invalid factory. (sk_flattenable_factory_t factory) -> const char *
/**
 * name and factory must be non-NULL. Invalid input is a no-op.
 * (const char *name, sk_flattenable_factory_t factory)
 */
void SkBlender_Register(const char * name, sk_flattenable_factory_t factory);
/**
 * procs may be NULL. Returns 0 for NULL data, zero length, or restore failure.
 * (SkBlender::Type type, const void *data, size_t length, const SkDeserialProcs *procs) -> sk_flattenable_t
 */
sk_flattenable_t SkBlender_Deserialize(reskia_blender_type_t type, const void *data, size_t length, const reskia_deserial_procs_t *procs);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BLENDER_H
