//
// Created by dolphilia on 2024/01/11.
//

#include "sk_shader.h"

#include <utility>

#include "include/core/SkShader.h"

#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_flattenable.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_flattenable-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_color_filter-internal.h"

namespace {

SkShader *as_shader(reskia_shader_t *shader) {
    return reinterpret_cast<SkShader *>(shader);
}

sk_shader_t make_shader_handle(sk_sp<SkShader> shader) {
    if (!shader) {
        return 0;
    }
    return static_sk_shader_make(std::move(shader));
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

} // namespace

extern "C" {

void SkShader_release(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    if (native != nullptr) {
        native->unref();
    }
}

bool SkShader_isOpaque(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    return native != nullptr ? native->isOpaque() : false;
}

reskia_image_t *SkShader_isAImage(reskia_shader_t *shader, reskia_matrix_t *localMatrix, int *xy) {
    SkShader *native = as_shader(shader);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_image_t *>(native->isAImage(reinterpret_cast<SkMatrix *>(localMatrix), reinterpret_cast<SkTileMode *>(xy)));
}

bool SkShader_isAImageWithoutLocalMatrixAndTileModes(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    return native != nullptr ? native->isAImage() : false;
}

int SkShader_makeWithLocalMatrix(reskia_shader_t *shader, const reskia_matrix_t *matrix) {
    SkShader *native = as_shader(shader);
    if (native == nullptr || matrix == nullptr) {
        return 0;
    }
    return make_shader_handle(native->makeWithLocalMatrix(*reinterpret_cast<const SkMatrix *>(matrix)));
}

int SkShader_makeWithColorFilter(reskia_shader_t *shader, sk_color_filter_t color_filter) {
    SkShader *native = as_shader(shader);
    return native != nullptr ? make_shader_handle(native->makeWithColorFilter(static_sk_color_filter_get_entity(color_filter))) : 0;
}

int SkShader_makeWithWorkingColorSpace(reskia_shader_t *shader, sk_color_space_t color_space) {
    SkShader *native = as_shader(shader);
    return native != nullptr ? make_shader_handle(native->makeWithWorkingColorSpace(static_sk_color_space_get_entity(color_space))) : 0;
}

int SkShader_getFactory(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    SkFlattenable::Factory factory = native != nullptr ? native->getFactory() : nullptr;
    return factory != nullptr ? static_sk_flattenable_factory_make(factory) : 0;
}

const char *SkShader_getTypeName(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    return native != nullptr ? native->getTypeName() : nullptr;
}

void SkShader_flatten(reskia_shader_t *shader, reskia_write_buffer_t *buffer) {
    SkShader *native = as_shader(shader);
    if (native != nullptr && buffer != nullptr) {
        native->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
    }
}

reskia_shader_type_t SkShader_getFlattenableType(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    return native != nullptr ? static_cast<reskia_shader_type_t>(native->getFlattenableType()) : 0;
}

sk_data_t SkShader_serialize(reskia_shader_t *shader, const reskia_serial_procs_t *procs) {
    SkShader *native = as_shader(shader);
    return native != nullptr ? make_data_handle(native->serialize(reinterpret_cast<const SkSerialProcs *>(procs))) : 0;
}

size_t SkShader_serializeToMemory(reskia_shader_t *shader, void *memory, size_t memory_size, const reskia_serial_procs_t *procs) {
    SkShader *native = as_shader(shader);
    if (native == nullptr || (memory == nullptr && memory_size != 0)) {
        return 0;
    }
    return native->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(procs));
}

bool SkShader_unique(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    return native != nullptr ? native->unique() : false;
}

void SkShader_ref(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    if (native != nullptr) {
        native->ref();
    }
}

void SkShader_unref(reskia_shader_t *shader) {
    SkShader *native = as_shader(shader);
    if (native != nullptr) {
        native->unref();
    }
}

// static

sk_flattenable_factory_t SkShader_NameToFactory(const char name[]) {
    if (name == nullptr) {
        return 0;
    }
    SkFlattenable::Factory factory = SkShader::NameToFactory(name);
    return factory != nullptr ? static_sk_flattenable_factory_make(factory) : 0;
}

const char * SkShader_FactoryToName(sk_flattenable_factory_t factory) {
    SkFlattenable::Factory native = static_sk_flattenable_factory_get_entity(factory);
    return native != nullptr ? SkShader::FactoryToName(native) : nullptr;
}

void SkShader_Register(const char name[], sk_flattenable_factory_t factory) {
    SkFlattenable::Factory native = static_sk_flattenable_factory_get_entity(factory);
    if (name != nullptr && native != nullptr) {
        SkShader::Register(name, native);
    }
}

sk_flattenable_t SkShader_Deserialize(reskia_shader_type_t type, const void *data, size_t length, const reskia_deserial_procs_t *procs) {
    if (data == nullptr || length == 0) {
        return 0;
    }
    return make_flattenable_handle(SkShader::Deserialize(static_cast<SkShader::Type>(type), data, length, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

}
