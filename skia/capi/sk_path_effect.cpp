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

#include <utility>

namespace {

sk_path_effect_t make_path_effect_handle(sk_sp<SkPathEffect> path_effect) {
    if (!path_effect) {
        return 0;
    }
    return static_sk_path_effect_make(std::move(path_effect));
}

sk_flattenable_factory_t make_flattenable_factory_handle(SkFlattenable::Factory factory) {
    if (factory == nullptr) {
        return 0;
    }
    return static_sk_flattenable_factory_make(factory);
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

}  // namespace

extern "C" {

void SkPathEffect_release(reskia_path_effect_t *pathEffect) {
    if (pathEffect == nullptr) {
        return;
    }
    reinterpret_cast<SkPathEffect *>(pathEffect)->unref();
}

bool SkPathEffect_filterPath(reskia_path_effect_t *path_effect, reskia_path_t *dst, const reskia_path_t *src, reskia_stroke_rec_t *rec, const reskia_rect_t *cullR) {
    if (path_effect == nullptr || dst == nullptr || src == nullptr || rec == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPathEffect *>(path_effect)->filterPath(
        reinterpret_cast<SkPath *>(dst),
        *reinterpret_cast<const SkPath *>(src),
        reinterpret_cast<SkStrokeRec *>(rec),
        reinterpret_cast<const SkRect *>(cullR));
}

bool SkPathEffect_filterPathWithCTM(reskia_path_effect_t *path_effect, reskia_path_t *dst, const reskia_path_t *src, reskia_stroke_rec_t *rec, const reskia_rect_t *cullR, const reskia_matrix_t *ctm) {
    if (path_effect == nullptr || dst == nullptr || src == nullptr || rec == nullptr || ctm == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPathEffect *>(path_effect)->filterPath(
        reinterpret_cast<SkPath *>(dst),
        *reinterpret_cast<const SkPath *>(src),
        reinterpret_cast<SkStrokeRec *>(rec),
        reinterpret_cast<const SkRect *>(cullR),
        *reinterpret_cast<const SkMatrix *>(ctm));
}

bool SkPathEffect_needsCTM(reskia_path_effect_t *path_effect) {
    if (path_effect == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPathEffect *>(path_effect)->needsCTM();
}

sk_flattenable_factory_t SkPathEffect_getFactory(reskia_path_effect_t *path_effect) {
    if (path_effect == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(reinterpret_cast<SkPathEffect *>(path_effect)->getFactory());
}

const char * SkPathEffect_getTypeName(reskia_path_effect_t *path_effect) {
    if (path_effect == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkPathEffect *>(path_effect)->getTypeName();
}

void SkPathEffect_flatten(reskia_path_effect_t *path_effect, reskia_write_buffer_t *buffer) {
    if (path_effect == nullptr || buffer == nullptr) {
        return;
    }
    reinterpret_cast<SkPathEffect *>(path_effect)->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
}

int SkPathEffect_getFlattenableType(reskia_path_effect_t *path_effect) {
    if (path_effect == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkPathEffect *>(path_effect)->getFlattenableType();
}

sk_data_t SkPathEffect_serialize(reskia_path_effect_t *path_effect, const reskia_serial_procs_t *procs) {
    if (path_effect == nullptr) {
        return 0;
    }
    return make_data_handle(reinterpret_cast<SkPathEffect *>(path_effect)->serialize(reinterpret_cast<const SkSerialProcs *>(procs)));
}

size_t SkPathEffect_serializeToMemory(reskia_path_effect_t *path_effect, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *procs) {
    if (path_effect == nullptr || (memory == nullptr && memory_size != 0)) {
        return 0;
    }
    return reinterpret_cast<SkPathEffect *>(path_effect)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(procs));
}

bool SkPathEffect_unique(reskia_path_effect_t *path_effect) {
    if (path_effect == nullptr) {
        return false;
    }
    return reinterpret_cast<SkPathEffect *>(path_effect)->unique();
}

void SkPathEffect_ref(reskia_path_effect_t *path_effect) {
    if (path_effect == nullptr) {
        return;
    }
    reinterpret_cast<SkPathEffect *>(path_effect)->ref();
}

void SkPathEffect_unref(reskia_path_effect_t *path_effect) {
    if (path_effect == nullptr) {
        return;
    }
    reinterpret_cast<SkPathEffect *>(path_effect)->unref();
}

// static

sk_path_effect_t SkPathEffect_MakeSum(sk_path_effect_t first, sk_path_effect_t second) {
    return make_path_effect_handle(SkPathEffect::MakeSum(static_sk_path_effect_get_entity(first), static_sk_path_effect_get_entity(second)));
}

sk_path_effect_t SkPathEffect_MakeCompose(sk_path_effect_t outer, sk_path_effect_t inner) {
    return make_path_effect_handle(SkPathEffect::MakeCompose(static_sk_path_effect_get_entity(outer), static_sk_path_effect_get_entity(inner)));
}

int SkPathEffect_GetFlattenableType() {
    return SkPathEffect::GetFlattenableType();
}

sk_path_effect_t SkPathEffect_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs) {
    if (data == nullptr || size == 0) {
        return 0;
    }
    return make_path_effect_handle(SkPathEffect::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkPathEffect_NameToFactory(const char name[]) {
    if (name == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(SkPathEffect::NameToFactory(name));
}

const char * SkPathEffect_FactoryToName(sk_flattenable_factory_t factory) {
    SkFlattenable::Factory native = static_sk_flattenable_factory_get_entity(factory);
    if (native == nullptr) {
        return nullptr;
    }
    return SkPathEffect::FactoryToName(native);
}

void SkPathEffect_Register(const char name[], sk_flattenable_factory_t factory) {
    SkFlattenable::Factory native = static_sk_flattenable_factory_get_entity(factory);
    if (name == nullptr || native == nullptr) {
        return;
    }
    SkPathEffect::Register(name, native);
}

}
