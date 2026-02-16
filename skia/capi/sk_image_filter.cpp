//
// Created by dolphilia on 2024/01/08.
//

#include "sk_image_filter.h"

#include "include/core/SkImageFilter.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_image_filter.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_image_filter-internal.h"
#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

void SkImageFilter_release(reskia_image_filter_t *image_filter) {
    reinterpret_cast<SkImageFilter *>(image_filter)->unref();
}

sk_i_rect_t SkImageFilter_filterBounds(reskia_image_filter_t *image_filter, const reskia_i_rect_t *src, const reskia_matrix_t *ctm, reskia_image_filter_map_direction_t direction, const reskia_i_rect_t *inputRect) {
    return static_sk_i_rect_make(reinterpret_cast<SkImageFilter *>(image_filter)->filterBounds(
        *reinterpret_cast<const SkIRect *>(src),
        *reinterpret_cast<const SkMatrix *>(ctm),
        static_cast<SkImageFilter::MapDirection>(direction),
        reinterpret_cast<const SkIRect *>(inputRect)));
}

bool SkImageFilter_isColorFilterNode(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr) {
    return reinterpret_cast<SkImageFilter *>(image_filter)->isColorFilterNode(reinterpret_cast<SkColorFilter **>(filterPtr));
}

bool SkImageFilter_asColorFilter(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr) {
    return reinterpret_cast<SkImageFilter *>(image_filter)->asColorFilter(reinterpret_cast<SkColorFilter **>(filterPtr));
}

bool SkImageFilter_asAColorFilter(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr) {
    return reinterpret_cast<SkImageFilter *>(image_filter)->asAColorFilter(reinterpret_cast<SkColorFilter **>(filterPtr));
}

int SkImageFilter_countInputs(reskia_image_filter_t *image_filter) {
    return reinterpret_cast<SkImageFilter *>(image_filter)->countInputs();
}

const reskia_image_filter_t *SkImageFilter_getInput(reskia_image_filter_t *image_filter, int i) {
    return reinterpret_cast<const reskia_image_filter_t *>(reinterpret_cast<SkImageFilter *>(image_filter)->getInput(i));
}

sk_rect_t SkImageFilter_computeFastBounds(reskia_image_filter_t *image_filter, const reskia_rect_t *bounds) {
    return static_sk_rect_make(reinterpret_cast<SkImageFilter *>(image_filter)->computeFastBounds(
        *reinterpret_cast<const SkRect *>(bounds)));
}

bool SkImageFilter_canComputeFastBounds(reskia_image_filter_t *image_filter) {
    return reinterpret_cast<SkImageFilter *>(image_filter)->canComputeFastBounds();
}

sk_image_filter_t SkImageFilter_makeWithLocalMatrix(reskia_image_filter_t *image_filter, const reskia_matrix_t *matrix) {
    return static_sk_image_filter_make(reinterpret_cast<SkImageFilter *>(image_filter)->makeWithLocalMatrix(
        *reinterpret_cast<const SkMatrix *>(matrix)));
}

sk_flattenable_factory_t SkImageFilter_getFactory(reskia_image_filter_t *image_filter) {
    return static_sk_flattenable_factory_make(reinterpret_cast<SkImageFilter *>(image_filter)->getFactory());
}

const char *SkImageFilter_getTypeName(reskia_image_filter_t *image_filter) {
    return reinterpret_cast<SkImageFilter *>(image_filter)->getTypeName();
}

void SkImageFilter_flatten(reskia_image_filter_t *image_filter, reskia_write_buffer_t *buffer) {
    reinterpret_cast<SkImageFilter *>(image_filter)->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
}

reskia_image_filter_type_t SkImageFilter_getFlattenableType(reskia_image_filter_t *image_filter) {
    return static_cast<reskia_image_filter_type_t>(reinterpret_cast<SkImageFilter *>(image_filter)->getFlattenableType());
}

sk_data_t SkImageFilter_serialize(reskia_image_filter_t *image_filter, const reskia_serial_procs_t *procs) {
    return static_sk_data_make(reinterpret_cast<SkImageFilter *>(image_filter)->serialize(
        reinterpret_cast<const SkSerialProcs *>(procs)));
}

size_t SkImageFilter_serializeToMemory(reskia_image_filter_t *image_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs) {
    return reinterpret_cast<SkImageFilter *>(image_filter)->serialize(
        memory, memory_size, reinterpret_cast<const SkSerialProcs *>(procs));
}

bool SkImageFilter_unique(reskia_image_filter_t *image_filter) {
    return reinterpret_cast<SkImageFilter *>(image_filter)->unique();
}

void SkImageFilter_ref(reskia_image_filter_t *image_filter) {
    reinterpret_cast<SkImageFilter *>(image_filter)->ref();
}

void SkImageFilter_unref(reskia_image_filter_t *image_filter) {
    reinterpret_cast<SkImageFilter *>(image_filter)->unref();
}

// static

sk_image_filter_t SkImageFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs) {
    return static_sk_image_filter_make(SkImageFilter::Deserialize(
        data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
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
