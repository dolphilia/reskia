//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_SK_BLENDER_H
#define RAIA_SKIA_SK_BLENDER_H

#include "../static/static_sk_data.h"
#include "../static/static_sk_blender.h"
#include "../static/static_sk_flattenable.h"
#include "../static/static_sk_flattenable_factory.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

void SkBlender_delete(void *blender); // (SkBlender *blender)
sk_flattenable_factory_t SkBlender_getFactory(void *blender); // (SkBlender *blender) -> sk_flattenable_factory_t
const char *SkBlender_getTypeName(void *blender); // (SkBlender *blender) -> const char *
void SkBlender_flatten(void *blender, void *write_buffer); // (SkBlender *blender, SkWriteBuffer *write_buffer)
int SkBlender_getFlattenableType(void *blender); // (SkBlender *blender) -> SkBlender::Type
sk_data_t SkBlender_serialize(void *blender, const void *serial_procs); // (SkBlender *blender, const SkSerialProcs *serial_procs) -> sk_data_t
size_t SkBlender_serialize_2(void *blender, void *memory, size_t memory_size, const void *serial_procs); // (SkBlender *blender, void *memory, size_t memory_size, const SkSerialProcs *serial_procs) -> size_t
bool SkBlender_unique(void *blender); // (SkBlender *blender) -> bool
void SkBlender_ref(void *blender); // (SkBlender *blender)
void SkBlender_unref(void *blender); // (SkBlender *blender)

// static

sk_blender_t SkBlender_Mode(int mode); // (SkBlendMode mode) -> sk_blender_t
sk_flattenable_factory_t SkBlender_NameToFactory(const char * name); // (const char *name) -> sk_flattenable_factory_t
const char *SkBlender_FactoryToName(sk_flattenable_factory_t factory); // (sk_flattenable_factory_t factory) -> const char *
void SkBlender_Register(const char * name, sk_flattenable_factory_t factory); // (const char *name, sk_flattenable_factory_t factory)
sk_flattenable_t SkBlender_Deserialize(int type, const void *data, size_t length, const void *procs); // (SkBlender::Type type, const void *data, size_t length, const SkDeserialProcs *procs) -> sk_flattenable_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BLENDER_H
