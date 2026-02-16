//
// Created by dolphilia on 2024/01/08.
//

#include "sk_flattenable.h"

#include "include/core/SkFlattenable.h"

#include "../handles/static_sk_flattenable.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_flattenable-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

void SkFlattenable_release(reskia_flattenable_t *flattenable) {
    reinterpret_cast<SkFlattenable *>(flattenable)->unref();
}

sk_flattenable_factory_t SkFlattenable_getFactory(reskia_flattenable_t *flattenable) {
    return static_sk_flattenable_factory_make(reinterpret_cast<SkFlattenable *>(flattenable)->getFactory());
}

const char * SkFlattenable_getTypeName(reskia_flattenable_t *flattenable) {
    return reinterpret_cast<SkFlattenable *>(flattenable)->getTypeName();
}

void SkFlattenable_flatten(reskia_flattenable_t *flattenable, reskia_write_buffer_t *write_buffer) {
    reinterpret_cast<SkFlattenable *>(flattenable)->flatten(* reinterpret_cast<SkWriteBuffer *>(write_buffer));
}

reskia_flattenable_type_t SkFlattenable_getFlattenableType(reskia_flattenable_t *flattenable) {
    return static_cast<reskia_flattenable_type_t>(reinterpret_cast<SkFlattenable *>(flattenable)->getFlattenableType());
}

sk_data_t SkFlattenable_serialize(reskia_flattenable_t *flattenable, const reskia_serial_procs_t *serial_procs) {
    return static_sk_data_make(reinterpret_cast<SkFlattenable *>(flattenable)->serialize(reinterpret_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkFlattenable_serialize_2(reskia_flattenable_t *flattenable, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs) {
    return reinterpret_cast<SkFlattenable *>(flattenable)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(serial_procs));
}

bool SkFlattenable_unique(reskia_flattenable_t *flattenable) {
    return reinterpret_cast<SkFlattenable *>(flattenable)->unique();
}

void SkFlattenable_ref(reskia_flattenable_t *flattenable) {
    reinterpret_cast<SkFlattenable *>(flattenable)->ref();
}

void SkFlattenable_unref(reskia_flattenable_t *flattenable) {
    reinterpret_cast<SkFlattenable *>(flattenable)->unref();
}

// static

sk_flattenable_factory_t SkFlattenable_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkFlattenable::NameToFactory(name));
}

const char * SkFlattenable_FactoryToName(sk_flattenable_factory_t factory) {
    return SkFlattenable::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkFlattenable_Register(const char name[], sk_flattenable_factory_t factory) {
    SkFlattenable::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

sk_flattenable_t SkFlattenable_Deserialize(reskia_flattenable_type_t type, const uint8_t *data, size_t length, const reskia_deserial_procs_t *procs) {
    return static_sk_flattenable_make(SkFlattenable::Deserialize(static_cast<SkFlattenable::Type>(type), data, length, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

}
