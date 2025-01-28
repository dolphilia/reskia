//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_matrix_filter.h"

#include "include/effects/SkColorMatrixFilter.h"

#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_color_4f.h"
#include "../static/static_sk_flattenable_factory.h"

#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_color_space-internal.h"
#include "../static/static_sk_color_filter-internal.h"
#include "../static/static_sk_color_4f-internal.h"

extern "C" {

void SkColorMatrixFilter_delete(void *color_matrix_filter) {
    delete static_cast<SkColorMatrixFilter *>(color_matrix_filter);
}

bool SkColorMatrixFilter_asAColorMode(void *color_matrix_filter, void *color, void *mode) {
    return static_cast<SkColorMatrixFilter *>(color_matrix_filter)->asAColorMode(static_cast<SkColor *>(color), static_cast<SkBlendMode *>(mode));
}

bool SkColorMatrixFilter_asAColorMatrix(void *color_matrix_filter, void * matrix) {
    return static_cast<SkColorMatrixFilter *>(color_matrix_filter)->asAColorMatrix(static_cast<float *>(matrix));
}

bool SkColorMatrixFilter_isAlphaUnchanged(void *color_matrix_filter) {
    return static_cast<SkColorMatrixFilter *>(color_matrix_filter)->isAlphaUnchanged();
}

unsigned int SkColorMatrixFilter_filterColor(void *color_matrix_filter, unsigned int color) {
    return static_cast<SkColorMatrixFilter *>(color_matrix_filter)->filterColor(color);
}

sk_color_4f_t SkColorMatrixFilter_filterColor4f(void *color_matrix_filter, const void *srcColor, void *srcCS, void *dstCS) {
    return static_sk_color_4f_make(static_cast<SkColorMatrixFilter *>(color_matrix_filter)->filterColor4f(* static_cast<const SkColor4f *>(srcColor), static_cast<SkColorSpace *>(srcCS), static_cast<SkColorSpace *>(dstCS)));
}

sk_color_filter_t SkColorMatrixFilter_makeComposed(void *color_matrix_filter, sk_color_filter_t colorFilter) {
    return static_sk_color_filter_make(static_cast<SkColorMatrixFilter *>(color_matrix_filter)->makeComposed(static_sk_color_filter_move(colorFilter)));
}

sk_color_filter_t SkColorMatrixFilter_makeWithWorkingColorSpace(void *color_matrix_filter, sk_color_space_t colorSpace) {
    return static_sk_color_filter_make(static_cast<SkColorMatrixFilter *>(color_matrix_filter)->makeWithWorkingColorSpace(static_sk_color_space_move(colorSpace)));
}

sk_flattenable_factory_t SkColorMatrixFilter_getFactory(void *color_matrix_filter) {
    return static_sk_flattenable_factory_make(static_cast<SkColorMatrixFilter *>(color_matrix_filter)->getFactory());
}

const char * SkColorMatrixFilter_getTypeName(void *color_matrix_filter) {
    return static_cast<SkColorMatrixFilter *>(color_matrix_filter)->getTypeName();
}

void SkColorMatrixFilter_flatten(void *color_matrix_filter, void * write_buffer) {
    static_cast<SkColorMatrixFilter *>(color_matrix_filter)->flatten(* static_cast<SkWriteBuffer *>(write_buffer));
}

int SkColorMatrixFilter_getFlattenableType(void *color_matrix_filter) {
    return static_cast<SkColorMatrixFilter *>(color_matrix_filter)->getFlattenableType();
}

sk_data_t SkColorMatrixFilter_serialize(void *color_matrix_filter, const void *serial_procs) {
    return static_sk_data_make(static_cast<SkColorMatrixFilter *>(color_matrix_filter)->serialize(static_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkColorMatrixFilter_serialize_2(void *color_matrix_filter, void *memory, size_t memory_size, const void *serial_procs) {
    return static_cast<SkColorMatrixFilter *>(color_matrix_filter)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(serial_procs));
}

bool SkColorMatrixFilter_unique(void *color_matrix_filter) {
    return static_cast<SkColorMatrixFilter *>(color_matrix_filter)->unique();
}

void SkColorMatrixFilter_ref(void *color_matrix_filter) {
    static_cast<SkColorMatrixFilter *>(color_matrix_filter)->ref();
}

void SkColorMatrixFilter_unref(void *color_matrix_filter) {
    static_cast<SkColorMatrixFilter *>(color_matrix_filter)->unref();
}

// static

sk_color_filter_t SkColorMatrixFilter_MakeLightingFilter(unsigned int mul, unsigned int add) {
    return static_sk_color_filter_make(SkColorMatrixFilter::MakeLightingFilter(mul, add));
}

sk_color_filter_t SkColorMatrixFilter_Deserialize(const void *data, size_t size, const void *procs) {
    return static_sk_color_filter_make(SkColorMatrixFilter::Deserialize(data, size, static_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkColorMatrixFilter_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkColorMatrixFilter::NameToFactory(name));
}

const char * SkColorMatrixFilter_FactoryToName(sk_flattenable_factory_t factory) {
    return SkColorMatrixFilter::FactoryToName(static_sk_flattenable_factory_get(factory));
}

void SkColorMatrixFilter_Register(const char name[], sk_flattenable_factory_t factory) {
    SkColorMatrixFilter::Register(name, static_sk_flattenable_factory_get(factory));
}

}
