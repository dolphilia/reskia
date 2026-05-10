//
// Created by dolphilia on 2024/01/05.
//

#include "sk_blender.h"

#include "include/core/SkBlender.h"

#include <utility>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_flattenable.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_flattenable-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_blender-internal.h"

namespace {

SkBlender *as_blender(reskia_blender_t *blender) {
    return reinterpret_cast<SkBlender *>(blender);
}

sk_blender_t make_blender_handle(sk_sp<SkBlender> blender) {
    if (!blender) {
        return 0;
    }
    return static_sk_blender_make(std::move(blender));
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

sk_flattenable_factory_t make_factory_handle(SkFlattenable::Factory factory) {
    if (factory == nullptr) {
        return 0;
    }
    return static_sk_flattenable_factory_make(factory);
}

} // namespace

extern "C" {

void SkBlender_release(reskia_blender_t *blender) {
    SkBlender *native = as_blender(blender);
    if (native != nullptr) {
        native->unref();
    }
}

sk_flattenable_factory_t SkBlender_getFactory(reskia_blender_t *blender) {
    SkBlender *native = as_blender(blender);
    return native != nullptr ? make_factory_handle(native->getFactory()) : 0;
}

const char *SkBlender_getTypeName(reskia_blender_t *blender) {
    SkBlender *native = as_blender(blender);
    return native != nullptr ? native->getTypeName() : nullptr;
}

void SkBlender_flatten(reskia_blender_t *blender, reskia_write_buffer_t *write_buffer) {
    SkBlender *native = as_blender(blender);
    if (native != nullptr && write_buffer != nullptr) {
        native->flatten(*reinterpret_cast<SkWriteBuffer *>(write_buffer));
    }
}

reskia_blender_type_t SkBlender_getFlattenableType(reskia_blender_t *blender) {
    SkBlender *native = as_blender(blender);
    return native != nullptr ? static_cast<reskia_blender_type_t>(native->getFlattenableType()) : 0;
}

sk_data_t SkBlender_serialize(reskia_blender_t *blender, const reskia_serial_procs_t *serial_procs) {
    SkBlender *native = as_blender(blender);
    return native != nullptr ? make_data_handle(native->serialize(reinterpret_cast<const SkSerialProcs *>(serial_procs))) : 0;
}

size_t SkBlender_serializeToMemory(reskia_blender_t *blender, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs) {
    SkBlender *native = as_blender(blender);
    if (native == nullptr || (memory == nullptr && memory_size != 0)) {
        return 0;
    }
    return native->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(serial_procs));
}

bool SkBlender_unique(reskia_blender_t *blender) {
    SkBlender *native = as_blender(blender);
    return native != nullptr ? native->unique() : false;
}

void SkBlender_ref(reskia_blender_t *blender) {
    SkBlender *native = as_blender(blender);
    if (native != nullptr) {
        native->ref();
    }
}

void SkBlender_unref(reskia_blender_t *blender) {
    SkBlender *native = as_blender(blender);
    if (native != nullptr) {
        native->unref();
    }
}

// static

sk_blender_t SkBlender_Mode(reskia_blend_mode_t mode) {
    return make_blender_handle(SkBlender::Mode(static_cast<SkBlendMode>(mode)));
}

sk_flattenable_factory_t SkBlender_NameToFactory(const char * name) {
    if (name == nullptr) {
        return 0;
    }
    return make_factory_handle(SkBlender::NameToFactory(name));
}

const char *SkBlender_FactoryToName(sk_flattenable_factory_t factory) {
    SkFlattenable::Factory native = static_sk_flattenable_factory_get_entity(factory);
    return native != nullptr ? SkBlender::FactoryToName(native) : nullptr;
}

void SkBlender_Register(const char * name, sk_flattenable_factory_t factory) {
    SkFlattenable::Factory native = static_sk_flattenable_factory_get_entity(factory);
    if (name != nullptr && native != nullptr) {
        SkBlender::Register(name, native);
    }
}

sk_flattenable_t SkBlender_Deserialize(reskia_blender_type_t type, const void *data, size_t length, const reskia_deserial_procs_t *procs) {
    if (data == nullptr || length == 0) {
        return 0;
    }
    return make_flattenable_handle(SkBlender::Deserialize(static_cast<SkBlender::Type>(type), data, length, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

}
