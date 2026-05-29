//
// Created by dolphilia on 2024/01/08.
//

#include "sk_color_matrix_filter.h"

#include "include/effects/SkColorMatrixFilter.h"

#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_color_4f.h"
#include "../handles/static_sk_flattenable_factory.h"

#include "../handles/static_sk_flattenable_factory-internal.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_color_space-internal.h"
#include "../handles/static_sk_color_filter-internal.h"
#include "../handles/static_sk_color_4f-internal.h"

#include <utility>

namespace {

sk_color_filter_t make_color_filter_handle(sk_sp<SkColorFilter> color_filter) {
    if (!color_filter) {
        return 0;
    }
    return static_sk_color_filter_make(std::move(color_filter));
}

sk_flattenable_factory_t make_flattenable_factory_handle(SkFlattenable::Factory factory) {
    if (factory == nullptr) {
        return 0;
    }
    return static_sk_flattenable_factory_make(factory);
}

}  // namespace

extern "C" {

void SkColorMatrixFilter_release(reskia_color_matrix_filter_t *color_matrix_filter) {
    if (color_matrix_filter == nullptr) {
        return;
    }
    reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->unref();
}

bool SkColorMatrixFilter_asAColorMode(reskia_color_matrix_filter_t *color_matrix_filter, reskia_color_t *color, int *mode) {
    if (color_matrix_filter == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->asAColorMode(
        reinterpret_cast<SkColor *>(color),
        reinterpret_cast<SkBlendMode *>(mode));
}

bool SkColorMatrixFilter_asAColorMatrix(reskia_color_matrix_filter_t *color_matrix_filter, float matrix[20]) {
    if (color_matrix_filter == nullptr || matrix == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->asAColorMatrix(matrix);
}

bool SkColorMatrixFilter_isAlphaUnchanged(reskia_color_matrix_filter_t *color_matrix_filter) {
    if (color_matrix_filter == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->isAlphaUnchanged();
}

sk_color_4f_t SkColorMatrixFilter_filterColor4f(reskia_color_matrix_filter_t *color_matrix_filter, const reskia_color_4f_t *srcColor, reskia_color_space_t *srcCS, reskia_color_space_t *dstCS) {
    if (color_matrix_filter == nullptr || srcColor == nullptr) {
        return 0;
    }
    return static_sk_color_4f_make(reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->filterColor4f(
        *reinterpret_cast<const SkColor4f *>(srcColor),
        reinterpret_cast<SkColorSpace *>(srcCS),
        reinterpret_cast<SkColorSpace *>(dstCS)));
}

sk_color_filter_t SkColorMatrixFilter_makeComposed(reskia_color_matrix_filter_t *color_matrix_filter, sk_color_filter_t colorFilter) {
    if (color_matrix_filter == nullptr) {
        return 0;
    }
    return make_color_filter_handle(reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->makeComposed(static_sk_color_filter_get_entity(colorFilter)));
}

sk_color_filter_t SkColorMatrixFilter_makeWithWorkingColorSpace(reskia_color_matrix_filter_t *color_matrix_filter, sk_color_space_t colorSpace) {
    if (color_matrix_filter == nullptr) {
        return 0;
    }
    return make_color_filter_handle(reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->makeWithWorkingColorSpace(static_sk_color_space_get_entity(colorSpace)));
}

sk_flattenable_factory_t SkColorMatrixFilter_getFactory(reskia_color_matrix_filter_t *color_matrix_filter) {
    if (color_matrix_filter == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->getFactory());
}

const char *SkColorMatrixFilter_getTypeName(reskia_color_matrix_filter_t *color_matrix_filter) {
    if (color_matrix_filter == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->getTypeName();
}

void SkColorMatrixFilter_flatten(reskia_color_matrix_filter_t *color_matrix_filter, reskia_write_buffer_t *write_buffer) {
    if (color_matrix_filter == nullptr || write_buffer == nullptr) {
        return;
    }
    reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->flatten(*reinterpret_cast<SkWriteBuffer *>(write_buffer));
}

reskia_color_matrix_filter_type_t SkColorMatrixFilter_getFlattenableType(reskia_color_matrix_filter_t *color_matrix_filter) {
    if (color_matrix_filter == nullptr) {
        return 0;
    }
    return static_cast<reskia_color_matrix_filter_type_t>(reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->getFlattenableType());
}

sk_data_t SkColorMatrixFilter_serialize(reskia_color_matrix_filter_t *color_matrix_filter, const reskia_serial_procs_t *serial_procs) {
    if (color_matrix_filter == nullptr) {
        return 0;
    }
    return static_sk_data_make(reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->serialize(reinterpret_cast<const SkSerialProcs *>(serial_procs)));
}

size_t SkColorMatrixFilter_serializeToMemory(reskia_color_matrix_filter_t *color_matrix_filter, void *memory, size_t memory_size, const reskia_serial_procs_t *serial_procs) {
    if (color_matrix_filter == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->serialize(memory, memory_size, reinterpret_cast<const SkSerialProcs *>(serial_procs));
}

bool SkColorMatrixFilter_unique(reskia_color_matrix_filter_t *color_matrix_filter) {
    if (color_matrix_filter == nullptr) {
        return false;
    }
    return reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->unique();
}

void SkColorMatrixFilter_ref(reskia_color_matrix_filter_t *color_matrix_filter) {
    if (color_matrix_filter == nullptr) {
        return;
    }
    reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->ref();
}

void SkColorMatrixFilter_unref(reskia_color_matrix_filter_t *color_matrix_filter) {
    if (color_matrix_filter == nullptr) {
        return;
    }
    reinterpret_cast<SkColorMatrixFilter *>(color_matrix_filter)->unref();
}

// static

sk_color_filter_t SkColorMatrixFilter_MakeLightingFilter(reskia_color_t mul, reskia_color_t add) {
    return make_color_filter_handle(SkColorMatrixFilter::MakeLightingFilter(static_cast<SkColor>(mul), static_cast<SkColor>(add)));
}

sk_color_filter_t SkColorMatrixFilter_Deserialize(const void *data, size_t size, const reskia_deserial_procs_t *procs) {
    if (data == nullptr) {
        return 0;
    }
    return make_color_filter_handle(SkColorMatrixFilter::Deserialize(data, size, reinterpret_cast<const SkDeserialProcs *>(procs)));
}

sk_flattenable_factory_t SkColorMatrixFilter_NameToFactory(const char name[]) {
    if (name == nullptr) {
        return 0;
    }
    return make_flattenable_factory_handle(SkColorMatrixFilter::NameToFactory(name));
}

const char * SkColorMatrixFilter_FactoryToName(sk_flattenable_factory_t factory) {
    if (factory == 0) {
        return nullptr;
    }
    return SkColorMatrixFilter::FactoryToName(static_sk_flattenable_factory_get_entity(factory));
}

void SkColorMatrixFilter_Register(const char name[], sk_flattenable_factory_t factory) {
    if (name == nullptr || factory == 0) {
        return;
    }
    SkColorMatrixFilter::Register(name, static_sk_flattenable_factory_get_entity(factory));
}

}
