//
// Created by dolphilia on 2024/01/10.
//

#include "sk_path_effect.h"

#include "include/core/SkPathEffect.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_path_effect.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_path_effect-internal.h"
#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

void SkPathEffect_delete(reskia_path_effect_t *pathEffect) {
    reinterpret_cast<SkPathEffect *>(pathEffect)->unref();
}

int SkPathEffect_asADash(reskia_path_effect_t *path_effect, reskia_path_effect_dash_info_t *info) {
    return reinterpret_cast<SkPathEffect *>(path_effect)->asADash(reinterpret_cast<SkPathEffect::DashInfo *>(info));
}

bool SkPathEffect_filterPath(reskia_path_effect_t *path_effect, reskia_path_t *dst, const reskia_path_t *src, reskia_stroke_rec_t *rec, const reskia_rect_t *cullR) {
    return reinterpret_cast<SkPathEffect *>(path_effect)->filterPath(
        reinterpret_cast<SkPath *>(dst),
        *reinterpret_cast<const SkPath *>(src),
        reinterpret_cast<SkStrokeRec *>(rec),
        reinterpret_cast<const SkRect *>(cullR));
}

bool SkPathEffect_filterPath_2(reskia_path_effect_t *path_effect, reskia_path_t *dst, const reskia_path_t *src, reskia_stroke_rec_t *rec, const reskia_rect_t *cullR, const reskia_matrix_t *ctm) {
    return reinterpret_cast<SkPathEffect *>(path_effect)->filterPath(
        reinterpret_cast<SkPath *>(dst),
        *reinterpret_cast<const SkPath *>(src),
        reinterpret_cast<SkStrokeRec *>(rec),
        reinterpret_cast<const SkRect *>(cullR),
        *reinterpret_cast<const SkMatrix *>(ctm));
}

bool SkPathEffect_needsCTM(reskia_path_effect_t *path_effect) {
    return reinterpret_cast<SkPathEffect *>(path_effect)->needsCTM();
}

sk_flattenable_factory_t SkPathEffect_getFactory(reskia_path_effect_t *path_effect) {
    return static_sk_flattenable_factory_make(reinterpret_cast<SkPathEffect *>(path_effect)->getFactory());
}

const char * SkPathEffect_getTypeName(reskia_path_effect_t *path_effect) {
    return reinterpret_cast<SkPathEffect *>(path_effect)->getTypeName();
}

void SkPathEffect_flatten(reskia_path_effect_t *path_effect, reskia_write_buffer_t *buffer) {
    reinterpret_cast<SkPathEffect *>(path_effect)->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
}

int SkPathEffect_getFlattenableType(reskia_path_effect_t *path_effect) {
    return reinterpret_cast<SkPathEffect *>(path_effect)->getFlattenableType();
}

sk_data_t SkPathEffect_serialize(reskia_path_effect_t *path_effect, const reskia_serial_procs_t *procs) {
    return static_sk_data_make(reinterpret_cast<SkPathEffect *>(path_effect)->serialize(reinterpret_cast<const SkSerialProcs *>(procs)));
}

size_t SkPathEffect_serialize_2(reskia_path_effect_t *path_effect, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *procs) {
    return reinterpret_cast<SkPathEffect *>(path_effect)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(procs));
}

bool SkPathEffect_unique(reskia_path_effect_t *path_effect) {
    return reinterpret_cast<SkPathEffect *>(path_effect)->unique();
}

void SkPathEffect_ref(reskia_path_effect_t *path_effect) {
    reinterpret_cast<SkPathEffect *>(path_effect)->ref();
}

void SkPathEffect_unref(reskia_path_effect_t *path_effect) {
    reinterpret_cast<SkPathEffect *>(path_effect)->unref();
}

// static

sk_path_effect_t SkPathEffect_MakeSum(sk_path_effect_t first, sk_path_effect_t second) {
    return static_sk_path_effect_make(SkPathEffect::MakeSum(static_sk_path_effect_get_entity(first), static_sk_path_effect_get_entity(second)));
}

sk_path_effect_t SkPathEffect_MakeCompose(sk_path_effect_t outer, sk_path_effect_t inner) {
    return static_sk_path_effect_make(SkPathEffect::MakeCompose(static_sk_path_effect_get_entity(outer), static_sk_path_effect_get_entity(inner)));
}

int SkPathEffect_GetFlattenableType() {
    return SkPathEffect::GetFlattenableType();
}

sk_path_effect_t SkPathEffect_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs) {
    return static_sk_path_effect_make(SkPathEffect::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkPathEffect_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkPathEffect::NameToFactory(name));
}

const char * SkPathEffect_FactoryToName(sk_flattenable_factory_t factory) {
    return SkPathEffect::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkPathEffect_Register(const char name[], sk_flattenable_factory_t factory) {
    SkPathEffect::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

}
