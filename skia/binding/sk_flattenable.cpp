//
// Created by dolphilia on 2024/01/08.
//

#include "sk_flattenable.h"

#include "include/core/SkFlattenable.h"

#include "../static/static_sk_flattenable.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_flattenable_factory.h"

#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_flattenable-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkFlattenable_delete(void *flattenable) {
    delete static_cast<SkFlattenable *>(flattenable);
}

sk_flattenable_factory_t SkFlattenable_getFactory(void *flattenable) {
    return static_sk_flattenable_factory_make(static_cast<SkFlattenable *>(flattenable)->getFactory());
}

const char * SkFlattenable_getTypeName(void *flattenable) {
    return static_cast<SkFlattenable *>(flattenable)->getTypeName();
}

void SkFlattenable_flatten(void *flattenable, void * write_buffer) {
    static_cast<SkFlattenable *>(flattenable)->flatten(* static_cast<SkWriteBuffer *>(write_buffer));
}

int SkFlattenable_getFlattenableType(void *flattenable) {
    return static_cast<SkFlattenable *>(flattenable)->getFlattenableType();
}

sk_data_t SkFlattenable_serialize(void *flattenable, const void * serial_procs) {
    return static_sk_data_make(static_cast<SkFlattenable *>(flattenable)->serialize(static_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkFlattenable_serialize_2(void *flattenable, void *memory, size_t memory_size, const void * serial_procs) {
    return static_cast<SkFlattenable *>(flattenable)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(serial_procs));
}

bool SkFlattenable_unique(void *flattenable) {
    return static_cast<SkFlattenable *>(flattenable)->unique();
}

void SkFlattenable_ref(void *flattenable) {
    static_cast<SkFlattenable *>(flattenable)->ref();
}

void SkFlattenable_unref(void *flattenable) {
    static_cast<SkFlattenable *>(flattenable)->unref();
}

// static

sk_flattenable_factory_t SkFlattenable_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkFlattenable::NameToFactory(name));
}

const char * SkFlattenable_FactoryToName(sk_flattenable_factory_t factory) {
    return SkFlattenable::FactoryToName(static_sk_flattenable_factory_get(factory));
}

void SkFlattenable_Register(const char name[], sk_flattenable_factory_t factory) {
    SkFlattenable::Register(name, static_sk_flattenable_factory_get(factory));
}

sk_flattenable_t SkFlattenable_Deserialize(int type, const void *data, size_t length, const void *procs) {
    return static_sk_flattenable_make(SkFlattenable::Deserialize(static_cast<SkFlattenable::Type>(type), data, length, static_cast<const SkDeserialProcs *>(procs)));
}

}
