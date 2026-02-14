//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_filter.h"

#include "include/core/SkColorFilter.h"

#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_flattenable_factory.h"
#include "../static/static_sk_color_4f.h"

#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_filter-internal.h"
#include "../static/static_sk_color_4f-internal.h"

extern "C" {

void SkColorFilter_delete(void *color_filter) {
    static_cast<SkColorFilter *>(color_filter)->unref();
}

bool SkColorFilter_asAColorMode(void *color_filter, void *color, void *mode) {
    return static_cast<SkColorFilter *>(color_filter)->asAColorMode(static_cast<SkColor *>(color), static_cast<SkBlendMode *>(mode));
}

bool SkColorFilter_asAColorMatrix(void *color_filter, float matrix[20]) {
    return static_cast<SkColorFilter *>(color_filter)->asAColorMatrix(matrix);
}

bool SkColorFilter_isAlphaUnchanged(void *color_filter) {
    return static_cast<SkColorFilter *>(color_filter)->isAlphaUnchanged();
}

unsigned int  SkColorFilter_filterColor(void *color_filter, unsigned int  color) {
    return static_cast<SkColorFilter *>(color_filter)->filterColor(color);
}

sk_color_4f_t SkColorFilter_filterColor4f(void *color_filter, const void *srcColor, void *srcCS, void *dstCS) {
    return static_sk_color_4f_make(static_cast<SkColorFilter *>(color_filter)->filterColor4f(* static_cast<const SkColor4f *>(srcColor), static_cast<SkColorSpace *>(srcCS), static_cast<SkColorSpace *>(dstCS)));
}

sk_color_filter_t SkColorFilter_makeComposed(void *color_filter, sk_color_filter_t inner) {
    return static_sk_color_filter_make(static_cast<SkColorFilter *>(color_filter)->makeComposed(static_sk_color_filter_get_entity(inner)));
}

sk_color_filter_t SkColorFilter_makeWithWorkingColorSpace(void *color_filter, sk_color_space_t colorSpace) {
    return static_sk_color_filter_make(static_cast<SkColorFilter *>(color_filter)->makeWithWorkingColorSpace(static_sk_color_space_get_entity(colorSpace)));
}

sk_flattenable_factory_t SkColorFilter_getFactory(void *color_filter) {
    return static_sk_flattenable_factory_make(static_cast<SkColorFilter *>(color_filter)->getFactory());
}

const char *SkColorFilter_getTypeName(void *color_filter) {
    return static_cast<SkColorFilter *>(color_filter)->getTypeName();
}

void SkColorFilter_flatten(void *color_filter, void *write_buffer) {
    static_cast<SkColorFilter *>(color_filter)->flatten(*static_cast<SkWriteBuffer *>(write_buffer));
}

int SkColorFilter_getFlattenableType(void *color_filter) {
    return static_cast<SkColorFilter *>(color_filter)->getFlattenableType();
}

sk_data_t SkColorFilter_serialize(void *color_filter, const void *serial_procs) {
    return static_sk_data_make(static_cast<SkColorFilter *>(color_filter)->serialize(static_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkColorFilter_serialize_2(void *color_filter, void *memory, size_t memory_size, const void *serial_procs) {
    return static_cast<SkColorFilter *>(color_filter)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(serial_procs));
}

bool SkColorFilter_unique(void *color_filter) {
    return static_cast<SkColorFilter *>(color_filter)->unique();
}

void SkColorFilter_ref(void *color_filter) {
    return static_cast<SkColorFilter *>(color_filter)->ref();
}

void SkColorFilter_unref(void *color_filter) {
    static_cast<SkColorFilter *>(color_filter)->unref();
}

// static

sk_color_filter_t SkColorFilter_Deserialize(const void *data, size_t size, const void *procs) {
    return static_sk_color_filter_make(SkColorFilter::Deserialize(data, size, static_cast<const SkDeserialProcs *>(procs)));
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
