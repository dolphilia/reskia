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

void SkBlender_release(reskia_blender_t *blender); // owned: caller が保持する参照を release する。NULL blender は no-op (SkBlender *blender)
sk_flattenable_factory_t SkBlender_getFactory(reskia_blender_t *blender); // NULL blender または factory 不在なら 0 (SkBlender *blender) -> sk_flattenable_factory_t
const char *SkBlender_getTypeName(reskia_blender_t *blender); // NULL blender なら NULL (SkBlender *blender) -> const char *
void SkBlender_flatten(reskia_blender_t *blender, reskia_write_buffer_t *write_buffer); // blender/write_buffer は非 NULL。NULL 入力は no-op (SkBlender *blender, SkWriteBuffer *write_buffer)
reskia_blender_type_t SkBlender_getFlattenableType(reskia_blender_t *blender); // NULL blender なら 0 (SkBlender *blender) -> SkBlender::Type
sk_data_t SkBlender_serialize(reskia_blender_t *blender, const reskia_serial_procs_t *serial_procs); // serial_procs は NULL 許可。NULL blender または生成不能なら 0 (SkBlender *blender, const SkSerialProcs *serial_procs) -> sk_data_t
size_t SkBlender_serializeToMemory(reskia_blender_t *blender, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs); // serial_procs は NULL 許可。NULL blender または memory NULL かつ size 非 0 なら 0 (SkBlender *blender, void *memory, size_t memory_size, const SkSerialProcs *serial_procs) -> size_t
bool SkBlender_unique(reskia_blender_t *blender); // NULL blender なら false (SkBlender *blender) -> bool
void SkBlender_ref(reskia_blender_t *blender); // retained: 参照カウントを増やす。NULL blender は no-op (SkBlender *blender)
void SkBlender_unref(reskia_blender_t *blender); // owned: 参照カウントを減らす。NULL blender は no-op (SkBlender *blender)

// static

sk_blender_t SkBlender_Mode(reskia_blend_mode_t mode); // 生成不能なら 0 (SkBlendMode mode) -> sk_blender_t
sk_flattenable_factory_t SkBlender_NameToFactory(const char * name); // NULL name または未登録 name なら 0 (const char *name) -> sk_flattenable_factory_t
const char *SkBlender_FactoryToName(sk_flattenable_factory_t factory); // invalid factory なら NULL (sk_flattenable_factory_t factory) -> const char *
void SkBlender_Register(const char * name, sk_flattenable_factory_t factory); // name/factory は非 NULL。invalid 入力は no-op (const char *name, sk_flattenable_factory_t factory)
sk_flattenable_t SkBlender_Deserialize(reskia_blender_type_t type, const void *data, size_t length, const reskia_deserial_procs_t *procs); // procs は NULL 許可。NULL data または length 0 または復元不能なら 0 (SkBlender::Type type, const void *data, size_t length, const SkDeserialProcs *procs) -> sk_flattenable_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_BLENDER_H
