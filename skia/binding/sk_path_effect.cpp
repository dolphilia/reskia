//
// Created by dolphilia on 2024/01/10.
//

#include "sk_path_effect.h"

#include "include/core/SkPathEffect.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_path_effect.h"
#include "../static/static_sk_flattenable_factory.h"

#include "../static/static_sk_path_effect-internal.h"
#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkPathEffect_delete(void * pathEffect) {
    delete static_cast<SkPathEffect *>(pathEffect);
}

int SkPathEffect_asADash(void *path_effect, void *info) {
    return static_cast<SkPathEffect *>(path_effect)->asADash(static_cast<SkPathEffect::DashInfo *>(info));
}

bool SkPathEffect_filterPath(void *path_effect, void *dst, const void *src, void *rec, const void *cullR) {
    return static_cast<SkPathEffect *>(path_effect)->filterPath(static_cast<SkPath *>(dst), * static_cast<const SkPath *>(src), static_cast<SkStrokeRec *>(rec), static_cast<const SkRect *>(cullR));
}

bool SkPathEffect_filterPath_2(void *path_effect, void *dst, const void *src, void *rec, const void *cullR, const void *ctm) {
    return static_cast<SkPathEffect *>(path_effect)->filterPath(static_cast<SkPath *>(dst), * static_cast<const SkPath *>(src), static_cast<SkStrokeRec *>(rec), static_cast<const SkRect *>(cullR), * static_cast<const SkMatrix *>(ctm));
}

bool SkPathEffect_needsCTM(void *path_effect) {
    return static_cast<SkPathEffect *>(path_effect)->needsCTM();
}

sk_flattenable_factory_t SkPathEffect_getFactory(void *path_effect) {
    return static_sk_flattenable_factory_make(static_cast<SkPathEffect *>(path_effect)->getFactory());
}

const char * SkPathEffect_getTypeName(void *path_effect) {
    return static_cast<SkPathEffect *>(path_effect)->getTypeName();
}

void SkPathEffect_flatten(void *path_effect, void *buffer) {
    static_cast<SkPathEffect *>(path_effect)->flatten(* static_cast<SkWriteBuffer *>(buffer));
}

int SkPathEffect_getFlattenableType(void *path_effect) {
    return static_cast<SkPathEffect *>(path_effect)->getFlattenableType();
}

sk_data_t SkPathEffect_serialize(void *path_effect, const void *procs) {
    return static_sk_data_make(static_cast<SkPathEffect *>(path_effect)->serialize(static_cast<const SkSerialProcs *>(procs)));
}

size_t SkPathEffect_serialize_2(void *path_effect, void *memory, size_t memory_size, const void *procs) {
    return static_cast<SkPathEffect *>(path_effect)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(procs));
}

bool SkPathEffect_unique(void *path_effect) {
    return static_cast<SkPathEffect *>(path_effect)->unique();
}

void SkPathEffect_ref(void *path_effect) {
    static_cast<SkPathEffect *>(path_effect)->ref();
}

void SkPathEffect_unref(void *path_effect) {
    static_cast<SkPathEffect *>(path_effect)->unref();
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

sk_path_effect_t SkPathEffect_Deserialize(const void *data, size_t size, const void *procs) {
    return static_sk_path_effect_make(SkPathEffect::Deserialize(data, size, static_cast<const SkDeserialProcs *>(procs)));
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
