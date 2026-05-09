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

#include <utility>

namespace {

SkFlattenable *as_flattenable(reskia_flattenable_t *flattenable) {
    return reinterpret_cast<SkFlattenable *>(flattenable);
}

SkFlattenable::Factory make_factory_or_null(SkFlattenable::Factory factory) {
    return factory;
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

sk_flattenable_t make_flattenable_handle(sk_sp<SkFlattenable> flattenable) {
    if (!flattenable) {
        return 0;
    }
    return static_sk_flattenable_make(std::move(flattenable));
}

sk_flattenable_factory_t make_flattenable_factory_handle(SkFlattenable::Factory factory) {
    if (factory == nullptr) {
        return 0;
    }
    return static_sk_flattenable_factory_make(make_factory_or_null(factory));
}

bool is_valid_flattenable_type(reskia_flattenable_type_t type) {
    return type >= SkFlattenable::kSkColorFilter_Type && type <= SkFlattenable::kSkShader_Type;
}

}  // namespace

extern "C" {

void SkFlattenable_release(reskia_flattenable_t *flattenable) {
    if (flattenable == nullptr) {
        return;
    }
    as_flattenable(flattenable)->unref();
}

sk_flattenable_factory_t SkFlattenable_getFactory(reskia_flattenable_t *flattenable) {
    if (flattenable == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(as_flattenable(flattenable)->getFactory());
}

const char * SkFlattenable_getTypeName(reskia_flattenable_t *flattenable) {
    if (flattenable == nullptr) {
        return nullptr;
    }
    return as_flattenable(flattenable)->getTypeName();
}

void SkFlattenable_flatten(reskia_flattenable_t *flattenable, reskia_write_buffer_t *write_buffer) {
    if (flattenable == nullptr || write_buffer == nullptr) {
        return;
    }
    as_flattenable(flattenable)->flatten(* reinterpret_cast<SkWriteBuffer *>(write_buffer));
}

reskia_flattenable_type_t SkFlattenable_getFlattenableType(reskia_flattenable_t *flattenable) {
    if (flattenable == nullptr) {
        return -1;
    }
    return static_cast<reskia_flattenable_type_t>(as_flattenable(flattenable)->getFlattenableType());
}

sk_data_t SkFlattenable_serialize(reskia_flattenable_t *flattenable, const reskia_serial_procs_t *serial_procs) {
    if (flattenable == nullptr) {
        return 0;
    }
    return make_data_handle(as_flattenable(flattenable)->serialize(reinterpret_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkFlattenable_serializeToMemory(reskia_flattenable_t *flattenable, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs) {
    if (flattenable == nullptr || (memory_size > 0 && memory == nullptr)) {
        return 0;
    }
    return as_flattenable(flattenable)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(serial_procs));
}

bool SkFlattenable_unique(reskia_flattenable_t *flattenable) {
    return flattenable != nullptr && as_flattenable(flattenable)->unique();
}

void SkFlattenable_ref(reskia_flattenable_t *flattenable) {
    if (flattenable == nullptr) {
        return;
    }
    as_flattenable(flattenable)->ref();
}

void SkFlattenable_unref(reskia_flattenable_t *flattenable) {
    if (flattenable == nullptr) {
        return;
    }
    as_flattenable(flattenable)->unref();
}

// static

sk_flattenable_factory_t SkFlattenable_NameToFactory(const char name[]) {
    if (name == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(SkFlattenable::NameToFactory(name));
}

const char * SkFlattenable_FactoryToName(sk_flattenable_factory_t factory) {
    if (factory == 0) {
        return nullptr;
    }
    return SkFlattenable::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkFlattenable_Register(const char name[], sk_flattenable_factory_t factory) {
    if (name == nullptr || factory == 0) {
        return;
    }
    SkFlattenable::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

sk_flattenable_t SkFlattenable_Deserialize(reskia_flattenable_type_t type, const uint8_t *data, size_t length, const reskia_deserial_procs_t *procs) {
    if (!is_valid_flattenable_type(type) || data == nullptr || length == 0) {
        return 0;
    }
    return make_flattenable_handle(SkFlattenable::Deserialize(static_cast<SkFlattenable::Type>(type), data, length, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

}
