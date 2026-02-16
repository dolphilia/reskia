//
// Created by dolphilia on 2024/01/09.
//

#include "sk_mask_filter.h"

#include "include/core/SkMaskFilter.h"
#include "include/core/SkRect.h"
#include "include/core/SkData.h"

#include "../handles/static_sk_mask_filter.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_mask_filter-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

void SkMaskFilter_delete(reskia_mask_filter_t *maskFilter) {
    reinterpret_cast<SkMaskFilter *>(maskFilter)->unref();
}

sk_rect_t SkMaskFilter_approximateFilteredBounds(reskia_mask_filter_t *mask_filter, const reskia_rect_t *src) {
    return static_sk_rect_make(reinterpret_cast<SkMaskFilter *>(mask_filter)->approximateFilteredBounds(*reinterpret_cast<const SkRect *>(src)));
}

sk_flattenable_factory_t SkMaskFilter_getFactory(reskia_mask_filter_t *mask_filter) {
    return static_sk_flattenable_factory_make(reinterpret_cast<SkMaskFilter *>(mask_filter)->getFactory());
}

const char *SkMaskFilter_getTypeName(reskia_mask_filter_t *mask_filter) {
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->getTypeName();
}

void SkMaskFilter_flatten(reskia_mask_filter_t *mask_filter, reskia_write_buffer_t *buffer) {
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
}

reskia_mask_filter_type_t SkMaskFilter_getFlattenableType(reskia_mask_filter_t *mask_filter) {
    return static_cast<reskia_mask_filter_type_t>(reinterpret_cast<SkMaskFilter *>(mask_filter)->getFlattenableType());
}

sk_data_t SkMaskFilter_serialize(reskia_mask_filter_t *mask_filter, const reskia_serial_procs_t *procs) {
    return static_sk_data_make(reinterpret_cast<SkMaskFilter *>(mask_filter)->serialize(reinterpret_cast<const SkSerialProcs *>(procs)));
}

size_t SkMaskFilter_serialize_2(reskia_mask_filter_t *mask_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs) {
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(procs));
}

bool SkMaskFilter_unique(reskia_mask_filter_t *mask_filter) {
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->unique();
}

void SkMaskFilter_ref(reskia_mask_filter_t *mask_filter) {
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->ref();
}

void SkMaskFilter_unref(reskia_mask_filter_t *mask_filter) {
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->unref();
}


// static

sk_mask_filter_t SkMaskFilter_MakeBlur(reskia_mask_filter_blur_style_t style, float sigma, bool respectCTM) {
    return static_sk_mask_filter_make(SkMaskFilter::MakeBlur(static_cast<SkBlurStyle>(style), sigma, respectCTM));
}

sk_mask_filter_t SkMaskFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs) {
    return static_sk_mask_filter_make(SkMaskFilter::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkMaskFilter_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkMaskFilter::NameToFactory(name));
}

const char * SkMaskFilter_FactoryToName(sk_flattenable_factory_t factory) {
    return SkMaskFilter::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkMaskFilter_Register(const char name[], sk_flattenable_factory_t factory) {
    SkMaskFilter::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

}
