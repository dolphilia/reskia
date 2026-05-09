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

void SkFlattenable_release(reskia_flattenable_t *flattenable); // owned: caller が保持する参照を release する。NULL 入力では no-op
sk_flattenable_factory_t SkFlattenable_getFactory(reskia_flattenable_t *flattenable); // NULL 入力や factory なしでは 0
const char * SkFlattenable_getTypeName(reskia_flattenable_t *flattenable); // NULL 入力では NULL
void SkFlattenable_flatten(reskia_flattenable_t *flattenable, reskia_write_buffer_t *write_buffer); // write_buffer は非 NULL。invalid 入力では no-op
reskia_flattenable_type_t SkFlattenable_getFlattenableType(reskia_flattenable_t *flattenable); // NULL 入力では -1
sk_data_t SkFlattenable_serialize(reskia_flattenable_t *flattenable, const reskia_serial_procs_t *serial_procs); // serial_procs は NULL 許可。NULL 入力や生成不能では 0
size_t SkFlattenable_serializeToMemory(reskia_flattenable_t *flattenable, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs); // memory_size > 0 では memory 非 NULL。invalid 入力では 0
bool SkFlattenable_unique(reskia_flattenable_t *flattenable); // NULL 入力では false
void SkFlattenable_ref(reskia_flattenable_t *flattenable); // retained: 参照カウントを増やす。NULL 入力では no-op
void SkFlattenable_unref(reskia_flattenable_t *flattenable); // owned: 参照カウントを減らす。NULL 入力では no-op

// static

sk_flattenable_factory_t SkFlattenable_NameToFactory(const char name[]); // name は非 NULL。未登録や invalid 入力では 0
const char * SkFlattenable_FactoryToName(sk_flattenable_factory_t factory); // invalid factory では NULL
void SkFlattenable_Register(const char name[], sk_flattenable_factory_t factory); // name/factory は非 NULL。invalid 入力では no-op
sk_flattenable_t SkFlattenable_Deserialize(reskia_flattenable_type_t type, const uint8_t *data, size_t length, const reskia_deserial_procs_t *procs); // valid type、data 非 NULL、length > 0。invalid 入力や生成不能では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_FLATTENABLE_H
