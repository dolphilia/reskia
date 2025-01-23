//
// Created by dolphilia on 2024/01/09.
//

#include "sk_mask_filter.h"

#include "include/core/SkMaskFilter.h"
#include "include/core/SkRect.h"
#include "include/core/SkData.h"

#include "../static/static_sk_mask_filter.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_flattenable_factory.h"

#include "../static/static_sk_mask_filter-internal.h"
#include "../static/static_sk_rect-internal.h"
#include "../static/static_sk_flattenable_factory-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkMaskFilter_delete(void *maskFilter) {
    delete static_cast<SkMaskFilter *>(maskFilter);
}

sk_rect_t SkMaskFilter_approximateFilteredBounds(void *mask_filter, const void *src) {
    return static_sk_rect_make(static_cast<SkMaskFilter *>(mask_filter)->approximateFilteredBounds(* static_cast<const SkRect *>(src)));
}

sk_flattenable_factory_t SkMaskFilter_getFactory(void *mask_filter) {
    return static_sk_flattenable_factory_make(static_cast<SkMaskFilter *>(mask_filter)->getFactory());
}

const char * SkMaskFilter_getTypeName(void *mask_filter) {
    return static_cast<SkMaskFilter *>(mask_filter)->getTypeName();
}

void SkMaskFilter_flatten(void *mask_filter, void *buffer) {
    return static_cast<SkMaskFilter *>(mask_filter)->flatten(* static_cast<SkWriteBuffer *>(buffer));
}

int SkMaskFilter_getFlattenableType(void *mask_filter) {
    return static_cast<SkMaskFilter *>(mask_filter)->getFlattenableType();
}

sk_data_t SkMaskFilter_serialize(void *mask_filter, const void *procs) {
    return static_sk_data_make(static_cast<SkMaskFilter *>(mask_filter)->serialize(static_cast<const SkSerialProcs *>(procs)));
}

size_t SkMaskFilter_serialize_2(void *mask_filter, void *memory, size_t memory_size, const void *procs) {
    return static_cast<SkMaskFilter *>(mask_filter)->serialize(memory, memory_size, static_cast<const SkSerialProcs *>(procs));
}

bool SkMaskFilter_unique(void *mask_filter) {
    return static_cast<SkMaskFilter *>(mask_filter)->unique();
}

void SkMaskFilter_ref(void *mask_filter) {
    return static_cast<SkMaskFilter *>(mask_filter)->ref();
}

void SkMaskFilter_unref(void *mask_filter) {
    return static_cast<SkMaskFilter *>(mask_filter)->unref();
}


// static

sk_mask_filter_t SkMaskFilter_MakeBlur(int style, float sigma, bool respectCTM) {
    return static_sk_mask_filter_make(SkMaskFilter::MakeBlur(static_cast<SkBlurStyle>(style), sigma, respectCTM));
}

sk_mask_filter_t SkMaskFilter_Deserialize(const void *data, size_t size, const void *procs) {
    return static_sk_mask_filter_make(SkMaskFilter::Deserialize(data, size, static_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkMaskFilter_NameToFactory(const char name[]) {
    return static_sk_flattenable_factory_make(SkMaskFilter::NameToFactory(name));
}

const char * SkMaskFilter_FactoryToName(sk_flattenable_factory_t factory) {
    return SkMaskFilter::FactoryToName(static_sk_flattenable_factory_get(factory));
}

void SkMaskFilter_Register(const char name[], sk_flattenable_factory_t factory) {
    SkMaskFilter::Register(name, static_sk_flattenable_factory_get(factory));
}

}
