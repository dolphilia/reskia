//
// Created by dolphilia on 2024/01/05.
//

#include "sk_blender.h"

#include "include/core/SkBlender.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_blender.h"
#include "../static/static_sk_flattenable.h"
#include "../static/static_sk_flattenable_factory.h"

#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_flattenable-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_blender-internal.h"

extern "C" {

void SkBlender_delete(reskia_blender_t *blender) {
    reinterpret_cast<SkBlender *>(blender)->unref();
}

sk_flattenable_factory_t SkBlender_getFactory(reskia_blender_t *blender) {
    return static_sk_flattenable_factory_make(reinterpret_cast<SkBlender *>(blender)->getFactory());
}

const char *SkBlender_getTypeName(reskia_blender_t *blender) {
    return reinterpret_cast<SkBlender *>(blender)->getTypeName();
}

void SkBlender_flatten(reskia_blender_t *blender, reskia_write_buffer_t *write_buffer) {
    reinterpret_cast<SkBlender *>(blender)->flatten(*reinterpret_cast<SkWriteBuffer *>(write_buffer));
}

int SkBlender_getFlattenableType(reskia_blender_t *blender) {
    return reinterpret_cast<SkBlender *>(blender)->getFlattenableType();
}

sk_data_t SkBlender_serialize(reskia_blender_t *blender, const reskia_serial_procs_t *serial_procs) {
    return static_sk_data_make(reinterpret_cast<SkBlender *>(blender)->serialize(reinterpret_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkBlender_serialize_2(reskia_blender_t *blender, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs) {
    return reinterpret_cast<SkBlender *>(blender)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(serial_procs));
}

bool SkBlender_unique(reskia_blender_t *blender) {
    return reinterpret_cast<SkBlender *>(blender)->unique();
}

void SkBlender_ref(reskia_blender_t *blender) {
    reinterpret_cast<SkBlender *>(blender)->ref();
}

void SkBlender_unref(reskia_blender_t *blender) {
    reinterpret_cast<SkBlender *>(blender)->unref();
}

// static

sk_blender_t SkBlender_Mode(int mode) {
    return static_sk_blender_make(SkBlender::Mode(static_cast<SkBlendMode>(mode)));
}

sk_flattenable_factory_t SkBlender_NameToFactory(const char * name) {
    return static_sk_flattenable_factory_make(SkBlender::NameToFactory(name));
}

const char *SkBlender_FactoryToName(sk_flattenable_factory_t factory) {
    return SkBlender::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkBlender_Register(const char * name, sk_flattenable_factory_t factory) {
    SkBlender::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

sk_flattenable_t SkBlender_Deserialize(int type, const void *data, size_t length, const reskia_deserial_procs_t *procs) {
    return static_sk_flattenable_make(SkBlender::Deserialize(static_cast<SkBlender::Type>(type), data, length, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

}
