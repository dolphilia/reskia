//
// Created by dolphilia on 2024/01/11.
//

#include "sk_shader.h"

#include <utility>

#include "include/core/SkShader.h"

#include "../static/static_sk_shader.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_flattenable.h"
#include "../static/static_sk_flattenable_factory.h"

#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_flattenable-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_filter-internal.h"

extern "C" {

void SkShader_delete(reskia_shader_t *shader) {
    reinterpret_cast<SkShader *>(shader)->unref();
}

bool SkShader_isOpaque(reskia_shader_t *shader) {
    return reinterpret_cast<SkShader *>(shader)->isOpaque();
}

reskia_image_t *SkShader_isAImage(reskia_shader_t *shader, reskia_matrix_t *localMatrix, int *xy) {
    return reinterpret_cast<reskia_image_t *>(reinterpret_cast<SkShader *>(shader)->isAImage(reinterpret_cast<SkMatrix *>(localMatrix), reinterpret_cast<SkTileMode *>(xy)));
}

bool SkShader_isAImage_2(reskia_shader_t *shader) {
    return reinterpret_cast<SkShader *>(shader)->isAImage();
}

int SkShader_makeWithLocalMatrix(reskia_shader_t *shader, const reskia_matrix_t *matrix) {
    return static_sk_shader_make(reinterpret_cast<SkShader *>(shader)->makeWithLocalMatrix(*reinterpret_cast<const SkMatrix *>(matrix)));
}

int SkShader_makeWithColorFilter(reskia_shader_t *shader, sk_color_filter_t color_filter) {
    return static_sk_shader_make(reinterpret_cast<SkShader *>(shader)->makeWithColorFilter(static_sk_color_filter_get_entity(color_filter)));
}

int SkShader_makeWithWorkingColorSpace(reskia_shader_t *shader, sk_color_space_t color_space) {
    return static_sk_shader_make(reinterpret_cast<SkShader *>(shader)->makeWithWorkingColorSpace(static_sk_color_space_get_entity(color_space)));
}

int SkShader_getFactory(reskia_shader_t *shader) {
    return static_sk_flattenable_factory_make(reinterpret_cast<SkShader *>(shader)->getFactory());
}

const char *SkShader_getTypeName(reskia_shader_t *shader) {
    return reinterpret_cast<SkShader *>(shader)->getTypeName();
}

void SkShader_flatten(reskia_shader_t *shader, reskia_write_buffer_t *buffer) {
    reinterpret_cast<SkShader *>(shader)->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
}

int SkShader_getFlattenableType(reskia_shader_t *shader) {
    return reinterpret_cast<SkShader *>(shader)->getFlattenableType();
}

sk_data_t SkShader_serialize(reskia_shader_t *shader, const reskia_serial_procs_t *procs) {
    return static_sk_data_make(reinterpret_cast<SkShader *>(shader)->serialize(reinterpret_cast<const SkSerialProcs *>(procs)));
}

size_t SkShader_serialize_2(reskia_shader_t *shader, void *memory, size_t memory_size, const reskia_serial_procs_t *procs) {
    return reinterpret_cast<SkShader *>(shader)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(procs));
}

bool SkShader_unique(reskia_shader_t *shader) {
    return reinterpret_cast<SkShader *>(shader)->unique();
}

void SkShader_ref(reskia_shader_t *shader) {
    reinterpret_cast<SkShader *>(shader)->ref();
}

void SkShader_unref(reskia_shader_t *shader) {
    reinterpret_cast<SkShader *>(shader)->unref();
}

// static

sk_flattenable_factory_t SkShader_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkShader::NameToFactory(name));
}

const char * SkShader_FactoryToName(sk_flattenable_factory_t factory) {
    return SkShader::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkShader_Register(const char name[], sk_flattenable_factory_t factory) {
    SkShader::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

sk_flattenable_t SkShader_Deserialize(int type, const void *data, size_t length, const reskia_deserial_procs_t *procs) {
    return static_sk_flattenable_make(SkShader::Deserialize(static_cast<SkShader::Type>(type), data, length, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

}
