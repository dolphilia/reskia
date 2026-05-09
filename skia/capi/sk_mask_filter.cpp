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

#include <utility>

namespace {

sk_mask_filter_t make_mask_filter_handle(sk_sp<SkMaskFilter> mask_filter) {
    if (!mask_filter) {
        return 0;
    }
    return static_sk_mask_filter_make(std::move(mask_filter));
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

sk_flattenable_factory_t make_flattenable_factory_handle(SkFlattenable::Factory factory) {
    if (factory == nullptr) {
        return 0;
    }
    return static_sk_flattenable_factory_make(factory);
}

}  // namespace

extern "C" {

void SkMaskFilter_release(reskia_mask_filter_t *maskFilter) {
    if (maskFilter == nullptr) {
        return;
    }
    reinterpret_cast<SkMaskFilter *>(maskFilter)->unref();
}

sk_rect_t SkMaskFilter_approximateFilteredBounds(reskia_mask_filter_t *mask_filter, const reskia_rect_t *src) {
    if (mask_filter == nullptr || src == nullptr) {
        return static_sk_rect_make(SkRect::MakeEmpty());
    }
    return static_sk_rect_make(reinterpret_cast<SkMaskFilter *>(mask_filter)->approximateFilteredBounds(*reinterpret_cast<const SkRect *>(src)));
}

sk_flattenable_factory_t SkMaskFilter_getFactory(reskia_mask_filter_t *mask_filter) {
    if (mask_filter == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(reinterpret_cast<SkMaskFilter *>(mask_filter)->getFactory());
}

const char *SkMaskFilter_getTypeName(reskia_mask_filter_t *mask_filter) {
    if (mask_filter == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->getTypeName();
}

void SkMaskFilter_flatten(reskia_mask_filter_t *mask_filter, reskia_write_buffer_t *buffer) {
    if (mask_filter == nullptr || buffer == nullptr) {
        return;
    }
    reinterpret_cast<SkMaskFilter *>(mask_filter)->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
}

reskia_mask_filter_type_t SkMaskFilter_getFlattenableType(reskia_mask_filter_t *mask_filter) {
    if (mask_filter == nullptr) {
        return -1;
    }
    return static_cast<reskia_mask_filter_type_t>(reinterpret_cast<SkMaskFilter *>(mask_filter)->getFlattenableType());
}

sk_data_t SkMaskFilter_serialize(reskia_mask_filter_t *mask_filter, const reskia_serial_procs_t *procs) {
    if (mask_filter == nullptr) {
        return 0;
    }
    return make_data_handle(reinterpret_cast<SkMaskFilter *>(mask_filter)->serialize(reinterpret_cast<const SkSerialProcs *>(procs)));
}

size_t SkMaskFilter_serializeToMemory(reskia_mask_filter_t *mask_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs) {
    if (mask_filter == nullptr || (memory == nullptr && memory_size > 0)) {
        return 0;
    }
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(procs));
}

bool SkMaskFilter_unique(reskia_mask_filter_t *mask_filter) {
    if (mask_filter == nullptr) {
        return false;
    }
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->unique();
}

void SkMaskFilter_ref(reskia_mask_filter_t *mask_filter) {
    if (mask_filter == nullptr) {
        return;
    }
    reinterpret_cast<SkMaskFilter *>(mask_filter)->ref();
}

void SkMaskFilter_unref(reskia_mask_filter_t *mask_filter) {
    if (mask_filter == nullptr) {
        return;
    }
    return reinterpret_cast<SkMaskFilter *>(mask_filter)->unref();
}


// static

sk_mask_filter_t SkMaskFilter_MakeBlur(reskia_mask_filter_blur_style_t style, float sigma, bool respectCTM) {
    return make_mask_filter_handle(SkMaskFilter::MakeBlur(static_cast<SkBlurStyle>(style), sigma, respectCTM));
}

sk_mask_filter_t SkMaskFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs) {
    if (data == nullptr || size == 0) {
        return 0;
    }
    return make_mask_filter_handle(SkMaskFilter::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkMaskFilter_NameToFactory(const char name[]) {
    if (name == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(SkMaskFilter::NameToFactory(name));
}

const char * SkMaskFilter_FactoryToName(sk_flattenable_factory_t factory) {
    if (factory == 0) {
        return nullptr;
    }
    return SkMaskFilter::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkMaskFilter_Register(const char name[], sk_flattenable_factory_t factory) {
    if (name == nullptr || factory == 0) {
        return;
    }
    SkMaskFilter::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

}
