//
// Created by dolphilia on 2024/01/08.
//

#include "sk_image_filter.h"

#include "include/core/SkImageFilter.h"

#include <utility>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_image_filter.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_image_filter-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_data-internal.h"

namespace {

SkImageFilter *as_image_filter(reskia_image_filter_t *image_filter) {
    return reinterpret_cast<SkImageFilter *>(image_filter);
}

sk_image_filter_t make_image_filter_handle(sk_sp<SkImageFilter> image_filter) {
    if (!image_filter) {
        return 0;
    }
    return static_sk_image_filter_make(std::move(image_filter));
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

} // namespace

extern "C" {

void SkImageFilter_release(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    if (native != nullptr) {
        native->unref();
    }
}

sk_i_rect_t SkImageFilter_filterBounds(reskia_image_filter_t *image_filter, const reskia_i_rect_t *src, const reskia_matrix_t *ctm, reskia_image_filter_map_direction_t direction, const reskia_i_rect_t *inputRect) {
    SkImageFilter *native = as_image_filter(image_filter);
    if (native == nullptr || src == nullptr || ctm == nullptr) {
        return 0;
    }
    return static_sk_i_rect_make(native->filterBounds(
        *reinterpret_cast<const SkIRect *>(src),
        *reinterpret_cast<const SkMatrix *>(ctm),
        static_cast<SkImageFilter::MapDirection>(direction),
        reinterpret_cast<const SkIRect *>(inputRect)));
}

bool SkImageFilter_isColorFilterNode(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? native->isColorFilterNode(reinterpret_cast<SkColorFilter **>(filterPtr)) : false;
}

bool SkImageFilter_asColorFilter(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? native->asColorFilter(reinterpret_cast<SkColorFilter **>(filterPtr)) : false;
}

bool SkImageFilter_asAColorFilter(reskia_image_filter_t *image_filter, reskia_color_filter_t **filterPtr) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? native->asAColorFilter(reinterpret_cast<SkColorFilter **>(filterPtr)) : false;
}

int SkImageFilter_countInputs(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? native->countInputs() : 0;
}

const reskia_image_filter_t *SkImageFilter_getInput(reskia_image_filter_t *image_filter, int i) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? reinterpret_cast<const reskia_image_filter_t *>(native->getInput(i)) : nullptr;
}

sk_rect_t SkImageFilter_computeFastBounds(reskia_image_filter_t *image_filter, const reskia_rect_t *bounds) {
    SkImageFilter *native = as_image_filter(image_filter);
    if (native == nullptr || bounds == nullptr) {
        return 0;
    }
    return static_sk_rect_make(native->computeFastBounds(*reinterpret_cast<const SkRect *>(bounds)));
}

bool SkImageFilter_canComputeFastBounds(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? native->canComputeFastBounds() : false;
}

sk_image_filter_t SkImageFilter_makeWithLocalMatrix(reskia_image_filter_t *image_filter, const reskia_matrix_t *matrix) {
    SkImageFilter *native = as_image_filter(image_filter);
    if (native == nullptr || matrix == nullptr) {
        return 0;
    }
    return make_image_filter_handle(native->makeWithLocalMatrix(*reinterpret_cast<const SkMatrix *>(matrix)));
}

sk_flattenable_factory_t SkImageFilter_getFactory(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    SkFlattenable::Factory factory = native != nullptr ? native->getFactory() : nullptr;
    return factory != nullptr ? static_sk_flattenable_factory_make(factory) : 0;
}

const char *SkImageFilter_getTypeName(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? native->getTypeName() : nullptr;
}

void SkImageFilter_flatten(reskia_image_filter_t *image_filter, reskia_write_buffer_t *buffer) {
    SkImageFilter *native = as_image_filter(image_filter);
    if (native != nullptr && buffer != nullptr) {
        native->flatten(*reinterpret_cast<SkWriteBuffer *>(buffer));
    }
}

reskia_image_filter_type_t SkImageFilter_getFlattenableType(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? static_cast<reskia_image_filter_type_t>(native->getFlattenableType()) : 0;
}

sk_data_t SkImageFilter_serialize(reskia_image_filter_t *image_filter, const reskia_serial_procs_t *procs) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? make_data_handle(native->serialize(reinterpret_cast<const SkSerialProcs *>(procs))) : 0;
}

size_t SkImageFilter_serializeToMemory(reskia_image_filter_t *image_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *procs) {
    SkImageFilter *native = as_image_filter(image_filter);
    if (native == nullptr || (memory == nullptr && memory_size != 0)) {
        return 0;
    }
    return native->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(procs));
}

bool SkImageFilter_unique(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    return native != nullptr ? native->unique() : false;
}

void SkImageFilter_ref(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    if (native != nullptr) {
        native->ref();
    }
}

void SkImageFilter_unref(reskia_image_filter_t *image_filter) {
    SkImageFilter *native = as_image_filter(image_filter);
    if (native != nullptr) {
        native->unref();
    }
}

// static

sk_image_filter_t SkImageFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs) {
    if (data == nullptr || size == 0) {
        return 0;
    }
    return make_image_filter_handle(SkImageFilter::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkImageFilter_NameToFactory(const char name[]) {
    if (name == nullptr) {
        return 0;
    }
    SkFlattenable::Factory factory = SkImageFilter::NameToFactory(name);
    return factory != nullptr ? static_sk_flattenable_factory_make(factory) : 0;
}

const char * SkImageFilter_FactoryToName(sk_flattenable_factory_t factory) {
    SkFlattenable::Factory native = static_sk_flattenable_factory_get_entity(factory);
    return native != nullptr ? SkImageFilter::FactoryToName(native) : nullptr;
}

void SkImageFilter_Register(const char name[], sk_flattenable_factory_t factory) {
    SkFlattenable::Factory native = static_sk_flattenable_factory_get_entity(factory);
    if (name != nullptr && native != nullptr) {
        SkImageFilter::Register(name, native);
    }
}

}
