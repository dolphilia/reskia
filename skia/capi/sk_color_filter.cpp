//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_filter.h"

#include "include/core/SkColorFilter.h"

#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable_factory.h"
#include "../handles/static_sk_color_4f.h"

#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_color_filter-internal.h"
#include "../handles/static_sk_color_4f-internal.h"

extern "C" {

void SkColorFilter_release(reskia_color_filter_t *color_filter) {
    reinterpret_cast<SkColorFilter *>(color_filter)->unref();
}

bool SkColorFilter_asAColorMode(reskia_color_filter_t *color_filter, reskia_color_t *color, int *mode) {
    return reinterpret_cast<SkColorFilter *>(color_filter)->asAColorMode(
        reinterpret_cast<SkColor *>(color),
        reinterpret_cast<SkBlendMode *>(mode));
}

bool SkColorFilter_asAColorMatrix(reskia_color_filter_t *color_filter, float matrix[20]) {
    return reinterpret_cast<SkColorFilter *>(color_filter)->asAColorMatrix(matrix);
}

bool SkColorFilter_isAlphaUnchanged(reskia_color_filter_t *color_filter) {
    return reinterpret_cast<SkColorFilter *>(color_filter)->isAlphaUnchanged();
}

reskia_color_t SkColorFilter_filterColor(reskia_color_filter_t *color_filter, reskia_color_t color) {
    return static_cast<reskia_color_t>(reinterpret_cast<SkColorFilter *>(color_filter)->filterColor(static_cast<SkColor>(color)));
}

sk_color_4f_t SkColorFilter_filterColor4f(reskia_color_filter_t *color_filter, const reskia_color_4f_t *srcColor, reskia_color_space_t *srcCS, reskia_color_space_t *dstCS) {
    return static_sk_color_4f_make(reinterpret_cast<SkColorFilter *>(color_filter)->filterColor4f(
        *reinterpret_cast<const SkColor4f *>(srcColor),
        reinterpret_cast<SkColorSpace *>(srcCS),
        reinterpret_cast<SkColorSpace *>(dstCS)));
}

sk_color_filter_t SkColorFilter_makeComposed(reskia_color_filter_t *color_filter, sk_color_filter_t inner) {
    return static_sk_color_filter_make(reinterpret_cast<SkColorFilter *>(color_filter)->makeComposed(static_sk_color_filter_get_entity(inner)));
}

sk_color_filter_t SkColorFilter_makeWithWorkingColorSpace(reskia_color_filter_t *color_filter, sk_color_space_t colorSpace) {
    return static_sk_color_filter_make(reinterpret_cast<SkColorFilter *>(color_filter)->makeWithWorkingColorSpace(static_sk_color_space_get_entity(colorSpace)));
}

sk_flattenable_factory_t SkColorFilter_getFactory(reskia_color_filter_t *color_filter) {
    return static_sk_flattenable_factory_make(reinterpret_cast<SkColorFilter *>(color_filter)->getFactory());
}

const char *SkColorFilter_getTypeName(reskia_color_filter_t *color_filter) {
    return reinterpret_cast<SkColorFilter *>(color_filter)->getTypeName();
}

void SkColorFilter_flatten(reskia_color_filter_t *color_filter, reskia_write_buffer_t *write_buffer) {
    reinterpret_cast<SkColorFilter *>(color_filter)->flatten(*reinterpret_cast<SkWriteBuffer *>(write_buffer));
}

reskia_color_filter_type_t SkColorFilter_getFlattenableType(reskia_color_filter_t *color_filter) {
    return static_cast<reskia_color_filter_type_t>(reinterpret_cast<SkColorFilter *>(color_filter)->getFlattenableType());
}

sk_data_t SkColorFilter_serialize(reskia_color_filter_t *color_filter, const reskia_serial_procs_t *serial_procs) {
    return static_sk_data_make(reinterpret_cast<SkColorFilter *>(color_filter)->serialize(reinterpret_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkColorFilter_serializeToMemory(reskia_color_filter_t *color_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs) {
    return reinterpret_cast<SkColorFilter *>(color_filter)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(serial_procs));
}

bool SkColorFilter_unique(reskia_color_filter_t *color_filter) {
    return reinterpret_cast<SkColorFilter *>(color_filter)->unique();
}

void SkColorFilter_ref(reskia_color_filter_t *color_filter) {
    return reinterpret_cast<SkColorFilter *>(color_filter)->ref();
}

void SkColorFilter_unref(reskia_color_filter_t *color_filter) {
    reinterpret_cast<SkColorFilter *>(color_filter)->unref();
}

// static

sk_color_filter_t SkColorFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs) {
    return static_sk_color_filter_make(SkColorFilter::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkColorFilter_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkColorFilter::NameToFactory(name));
}

const char *SkColorFilter_FactoryToName(sk_flattenable_factory_t factory) {
    return SkColorFilter::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkColorFilter_Register(const char name[], sk_flattenable_factory_t factory) {
    SkColorFilter::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

}
