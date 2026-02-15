//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_FLATTENABLE_H
#define RAIA_SKIA_SK_FLATTENABLE_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_data.h"
#include "../static/static_sk_flattenable.h"
#include "../static/static_sk_flattenable_factory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_flattenable_t reskia_flattenable_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef int32_t reskia_flattenable_type_t;

void SkFlattenable_delete(reskia_flattenable_t *flattenable); // owned: caller が保持する参照を release する (SkFlattenable *flattenable)
sk_flattenable_factory_t SkFlattenable_getFactory(reskia_flattenable_t *flattenable); // (SkFlattenable *flattenable) -> sk_flattenable_factory_t
const char * SkFlattenable_getTypeName(reskia_flattenable_t *flattenable); // (SkFlattenable *flattenable) -> const char *
void SkFlattenable_flatten(reskia_flattenable_t *flattenable, reskia_write_buffer_t *write_buffer); // (SkFlattenable *flattenable, SkWriteBuffer *write_buffer)
reskia_flattenable_type_t SkFlattenable_getFlattenableType(reskia_flattenable_t *flattenable); // (SkFlattenable *flattenable) -> SkFlattenable::Type
sk_data_t SkFlattenable_serialize(reskia_flattenable_t *flattenable, const reskia_serial_procs_t *serial_procs); // (SkFlattenable *flattenable, const SkSerialProcs *serial_procs) -> sk_data_t
size_t SkFlattenable_serialize_2(reskia_flattenable_t *flattenable, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs); // (SkFlattenable *flattenable, void *memory, size_t memory_size, const SkSerialProcs *serial_procs) -> size_t
bool SkFlattenable_unique(reskia_flattenable_t *flattenable); // (SkFlattenable *flattenable) -> bool
void SkFlattenable_ref(reskia_flattenable_t *flattenable); // retained: 参照カウントを増やす (SkFlattenable *flattenable)
void SkFlattenable_unref(reskia_flattenable_t *flattenable); // owned: 参照カウントを減らす (SkFlattenable *flattenable)

// static

sk_flattenable_factory_t SkFlattenable_NameToFactory(const char name[]); // (const char name[]) -> sk_flattenable_factory_t
const char * SkFlattenable_FactoryToName(sk_flattenable_factory_t factory); // (sk_flattenable_factory_t factory) -> const char *
void SkFlattenable_Register(const char name[], sk_flattenable_factory_t factory); // (const char name[], sk_flattenable_factory_t factory)
sk_flattenable_t SkFlattenable_Deserialize(reskia_flattenable_type_t type, const uint8_t *data, size_t length, const reskia_deserial_procs_t *procs); // (SkFlattenable::Type type, const void *data, size_t length, const SkDeserialProcs *procs) -> sk_flattenable_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FLATTENABLE_H
