//
// Created by dolphilia on 2024/01/08.
//

#include "sk_image_filter.h"

#include "include/core/SkImageFilter.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_image_filter.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_flattenable_factory.h"

#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_image_filter-internal.h"
#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_rect-internal.h"
#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkImageFilter_delete(void *image_filter) {
    static_cast<SkImageFilter *>(image_filter)->unref();
}

sk_i_rect_t SkImageFilter_filterBounds(void *image_filter, const void *src, const void *ctm, int direction, const void *inputRect) {
    return static_sk_i_rect_make(static_cast<SkImageFilter *>(image_filter)->filterBounds(* static_cast<const SkIRect *>(src), * static_cast<const SkMatrix *>(ctm), static_cast<SkImageFilter::MapDirection>(direction), static_cast<const SkIRect *>(inputRect)));
}

bool SkImageFilter_isColorFilterNode(void *image_filter, void **filterPtr) {
    return static_cast<SkImageFilter *>(image_filter)->isColorFilterNode(reinterpret_cast<SkColorFilter **>(filterPtr));
}

bool SkImageFilter_asColorFilter(void *image_filter, void **filterPtr) {
    return static_cast<SkImageFilter *>(image_filter)->asColorFilter(reinterpret_cast<SkColorFilter **>(filterPtr));
}

bool SkImageFilter_asAColorFilter(void *image_filter, void **filterPtr) {
    return static_cast<SkImageFilter *>(image_filter)->asAColorFilter(reinterpret_cast<SkColorFilter **>(filterPtr));
}

int SkImageFilter_countInputs(void *image_filter) {
    return static_cast<SkImageFilter *>(image_filter)->countInputs();
}

const void * SkImageFilter_getInput(void *image_filter, int i) {
    return static_cast<SkImageFilter *>(image_filter)->getInput(i);
}

sk_rect_t SkImageFilter_computeFastBounds(void *image_filter, const void *bounds) {
    return static_sk_rect_make(static_cast<SkImageFilter *>(image_filter)->computeFastBounds(* static_cast<const SkRect *>(bounds)));
}

bool SkImageFilter_canComputeFastBounds(void *image_filter) {
    return static_cast<SkImageFilter *>(image_filter)->canComputeFastBounds();
}

sk_image_filter_t SkImageFilter_makeWithLocalMatrix(void *image_filter, const void *matrix) {
    return static_sk_image_filter_make(static_cast<SkImageFilter *>(image_filter)->makeWithLocalMatrix(* static_cast<const SkMatrix *>(matrix)));
}

sk_flattenable_factory_t SkImageFilter_getFactory(void *image_filter) {
    return static_sk_flattenable_factory_make(static_cast<SkImageFilter *>(image_filter)->getFactory());
}

const char * SkImageFilter_getTypeName(void *image_filter) {
    return static_cast<SkImageFilter *>(image_filter)->getTypeName();
}

void SkImageFilter_flatten(void *image_filter, void *buffer) {
    static_cast<SkImageFilter *>(image_filter)->flatten(* static_cast<SkWriteBuffer *>(buffer));
}

int SkImageFilter_getFlattenableType(void *image_filter) {
    return static_cast<SkImageFilter *>(image_filter)->getFlattenableType();
}

sk_data_t SkImageFilter_serialize(void *image_filter, const void *procs) {
    return static_sk_data_make(static_cast<SkImageFilter *>(image_filter)->serialize(static_cast<const SkSerialProcs *>(procs)));
}

size_t SkImageFilter_serialize_2(void *image_filter, void *memory, size_t memory_size, const void *procs) {
    return static_cast<SkImageFilter *>(image_filter)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(procs));
}

bool SkImageFilter_unique(void *image_filter) {
    return static_cast<SkImageFilter *>(image_filter)->unique();
}

void SkImageFilter_ref(void *image_filter) {
    static_cast<SkImageFilter *>(image_filter)->ref();
}

void SkImageFilter_unref(void *image_filter) {
    static_cast<SkImageFilter *>(image_filter)->unref();
}

// static

sk_image_filter_t SkImageFilter_Deserialize(const void *data, size_t size, const void *procs) {
    return static_sk_image_filter_make(SkImageFilter::Deserialize(data, size, static_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkImageFilter_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkImageFilter::NameToFactory(name));
}

const char * SkImageFilter_FactoryToName(sk_flattenable_factory_t factory) {
    return SkImageFilter::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkImageFilter_Register(const char name[], sk_flattenable_factory_t factory) {
    return SkImageFilter::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

}
