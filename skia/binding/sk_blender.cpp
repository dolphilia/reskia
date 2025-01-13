//
// Created by dolphilia on 2024/01/05.
//

#include "sk_blender.h"

#include "include/core/SkBlender.h"

#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_flattenable-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_blender-internal.h"

extern "C" {

void SkBlender_delete(void *blender) {
    delete static_cast<SkBlender *>(blender);
}

sk_flattenable_factory_t SkBlender_getFactory(void *blender) {
    return static_sk_flattenable_factory_make(static_cast<SkBlender *>(blender)->getFactory());
}

const char *SkBlender_getTypeName(void *blender) {
    return static_cast<SkBlender *>(blender)->getTypeName();
}

void SkBlender_flatten(void *blender, void *write_buffer) {
    static_cast<SkBlender *>(blender)->flatten(* static_cast<SkWriteBuffer *>(write_buffer));
}

int SkBlender_getFlattenableType(void *blender) {
    return static_cast<SkBlender *>(blender)->getFlattenableType();
}

sk_data_t SkBlender_serialize(void *blender, const void *serial_procs) {
    return static_sk_data_make(static_cast<SkBlender *>(blender)->serialize(static_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkBlender_serialize_2(void *blender, void *memory, size_t memory_size, const void *serial_procs) {
    return static_cast<SkBlender *>(blender)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(serial_procs));
}

bool SkBlender_unique(void *blender) {
    return static_cast<SkBlender *>(blender)->unique();
}

void SkBlender_ref(void *blender) {
    static_cast<SkBlender *>(blender)->ref();
}

void SkBlender_unref(void *blender) {
    static_cast<SkBlender *>(blender)->unref();
}

// static

sk_blender_t SkBlender_Mode(int mode) {
    return static_sk_blender_make(SkBlender::Mode(static_cast<SkBlendMode>(mode)));
}

sk_flattenable_factory_t SkBlender_NameToFactory(const char * name) {
    return static_sk_flattenable_factory_make(SkBlender::NameToFactory(name));
}

const char *SkBlender_FactoryToName(sk_flattenable_factory_t factory) {
    return SkBlender::FactoryToName(static_sk_flattenable_factory_get(factory));
}

void SkBlender_Register(const char * name, sk_flattenable_factory_t factory) {
    SkBlender::Register(name, static_sk_flattenable_factory_get(factory));
}

sk_flattenable_t SkBlender_Deserialize(int type, const void *data, size_t length, const void *procs) {
    return static_sk_flattenable_make(SkBlender::Deserialize(static_cast<SkBlender::Type>(type), data, length, static_cast<const SkDeserialProcs *>(procs)));
}

}
