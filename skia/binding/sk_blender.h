//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_SK_BLENDER_H
#define RAIA_SKIA_SK_BLENDER_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_blender_t reskia_blender_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;

void SkBlender_delete(reskia_blender_t *blender); // owned: caller が保持する参照を release する (SkBlender *blender)
int SkBlender_getFactory(reskia_blender_t *blender); // (SkBlender *blender) -> sk_flattenable_factory_t
const char *SkBlender_getTypeName(reskia_blender_t *blender); // (SkBlender *blender) -> const char *
void SkBlender_flatten(reskia_blender_t *blender, reskia_write_buffer_t *write_buffer); // borrowed: inputs are borrowed only (SkBlender *blender, SkWriteBuffer *write_buffer)
int SkBlender_getFlattenableType(reskia_blender_t *blender); // (SkBlender *blender) -> SkBlender::Type
int SkBlender_serialize(reskia_blender_t *blender, const reskia_serial_procs_t *serial_procs); // (SkBlender *blender, const SkSerialProcs *serial_procs) -> sk_data_t
size_t SkBlender_serialize_2(reskia_blender_t *blender, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs); // (SkBlender *blender, void *memory, size_t memory_size, const SkSerialProcs *serial_procs) -> size_t
bool SkBlender_unique(reskia_blender_t *blender); // (SkBlender *blender) -> bool
void SkBlender_ref(reskia_blender_t *blender); // retained: 参照カウントを増やす (SkBlender *blender)
void SkBlender_unref(reskia_blender_t *blender); // owned: 参照カウントを減らす (SkBlender *blender)

// static

int SkBlender_Mode(int mode); // (SkBlendMode mode) -> sk_blender_t
int SkBlender_NameToFactory(const char * name); // (const char *name) -> sk_flattenable_factory_t
const char *SkBlender_FactoryToName(int factory); // (sk_flattenable_factory_t factory) -> const char *
void SkBlender_Register(const char * name, int factory); // (const char *name, sk_flattenable_factory_t factory)
int SkBlender_Deserialize(int type, const void *data, size_t length, const reskia_deserial_procs_t *procs); // (SkBlender::Type type, const void *data, size_t length, const SkDeserialProcs *procs) -> sk_flattenable_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BLENDER_H
