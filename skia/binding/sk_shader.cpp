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

void SkShader_delete(void *shader) {
    delete static_cast<SkShader *>(shader);
}

bool SkShader_isOpaque(void *shader) {
    return static_cast<SkShader *>(shader)->isOpaque();
}

void * SkShader_isAImage(void *shader, void *localMatrix, void * xy) {
    return static_cast<SkShader *>(shader)->isAImage(static_cast<SkMatrix *>(localMatrix), static_cast<SkTileMode *>(xy));
}

bool SkShader_isAImage_2(void *shader) {
    return static_cast<SkShader *>(shader)->isAImage();
}

int SkShader_makeWithLocalMatrix(void *shader, const void *matrix) {
    return static_sk_shader_make(static_cast<SkShader *>(shader)->makeWithLocalMatrix(* static_cast<const SkMatrix *>(matrix)));
}

int SkShader_makeWithColorFilter(void *shader, sk_color_filter_t color_filter) {
    return static_sk_shader_make(static_cast<SkShader *>(shader)->makeWithColorFilter(static_sk_color_filter_move(color_filter)));
}

int SkShader_makeWithWorkingColorSpace(void *shader, sk_color_space_t color_space) {
    return static_sk_shader_make(static_cast<SkShader *>(shader)->makeWithWorkingColorSpace(static_sk_color_space_move(color_space)));
}

int SkShader_getFactory(void *shader) {
    return static_sk_flattenable_factory_make(static_cast<SkShader *>(shader)->getFactory());
}

const char * SkShader_getTypeName(void *shader) {
    return static_cast<SkShader *>(shader)->getTypeName();
}

void SkShader_flatten(void *shader, void *buffer) {
    static_cast<SkShader *>(shader)->flatten(* static_cast<SkWriteBuffer *>(buffer));
}

int SkShader_getFlattenableType(void *shader) {
    return static_cast<SkShader *>(shader)->getFlattenableType();
}

sk_data_t SkShader_serialize(void *shader, const void *procs) {
    return static_sk_data_make(static_cast<SkShader *>(shader)->serialize(static_cast<const SkSerialProcs *>(procs)));
}

size_t SkShader_serialize_2(void *shader, void *memory, size_t memory_size, const void *procs) {
    return static_cast<SkShader *>(shader)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(procs));
}

bool SkShader_unique(void *shader) {
    return static_cast<SkShader *>(shader)->unique();
}

void SkShader_ref(void *shader) {
    static_cast<SkShader *>(shader)->ref();
}

void SkShader_unref(void *shader) {
    static_cast<SkShader *>(shader)->unref();
}

// static

sk_flattenable_factory_t SkShader_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkShader::NameToFactory(name));
}

const char * SkShader_FactoryToName(sk_flattenable_factory_t factory) {
    return SkShader::FactoryToName(static_sk_flattenable_factory_get(factory));
}

void SkShader_Register(const char name[], sk_flattenable_factory_t factory) {
    SkShader::Register(name, static_sk_flattenable_factory_get(factory));
}

sk_flattenable_t SkShader_Deserialize(int type, const void *data, size_t length, const void *procs) {
    return static_sk_flattenable_make(SkShader::Deserialize(static_cast<SkShader::Type>(type), data, length, static_cast<const SkDeserialProcs *>(procs)));
}

}
