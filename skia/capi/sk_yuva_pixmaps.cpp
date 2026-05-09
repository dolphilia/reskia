//
// Created by dolphilia on 2024/01/11.
//

#include "sk_yuva_pixmaps.h"

#include "include/core/SkData.h"
#include "include/core/SkYUVAPixmaps.h"

#include "../handles/static_sk_yuva_pixmap_info.h"
#include "../handles/static_sk_yuva_pixmaps.h"
#include "../handles/static_sk_data.h"

#include "../handles/static_sk_yuva_pixmaps-internal.h"
#include "../handles/static_sk_yuva_pixmap_info-internal.h"
#include "../handles/static_sk_data-internal.h"

#include <utility>

namespace {

SkYUVAPixmaps *as_yuva_pixmaps(reskia_yuva_pixmaps_t *pixmaps) {
    return reinterpret_cast<SkYUVAPixmaps *>(pixmaps);
}

const SkYUVAPixmaps *as_yuva_pixmaps(const reskia_yuva_pixmaps_t *pixmaps) {
    return reinterpret_cast<const SkYUVAPixmaps *>(pixmaps);
}

const SkYUVAPixmapInfo *as_yuva_pixmap_info(const reskia_yuva_pixmap_info_t *info) {
    return reinterpret_cast<const SkYUVAPixmapInfo *>(info);
}

const SkYUVAInfo *as_yuva_info(const reskia_yuva_info_t *info) {
    return reinterpret_cast<const SkYUVAInfo *>(info);
}

const SkPixmap *as_pixmaps(const reskia_pixmap_t *pixmaps) {
    return reinterpret_cast<const SkPixmap *>(pixmaps);
}

bool is_valid_data_type(reskia_yuva_pixmaps_data_type_t type) {
    return type >= 0 && type <= static_cast<reskia_yuva_pixmaps_data_type_t>(SkYUVAPixmapInfo::DataType::kLast);
}

sk_yuva_pixmaps_t make_yuva_pixmaps_handle_if_valid(SkYUVAPixmaps pixmaps) {
    if (!pixmaps.isValid()) {
        return 0;
    }
    return static_sk_yuva_pixmaps_make(std::move(pixmaps));
}

}

extern "C" {

// SkYUVAPixmaps & operator=(SkYUVAPixmaps &&that)
// SkYUVAPixmaps & operator=(const SkYUVAPixmaps &that)

reskia_yuva_pixmaps_t *SkYUVAPixmaps_new() {
    return reinterpret_cast<reskia_yuva_pixmaps_t *>(new SkYUVAPixmaps());
}

reskia_yuva_pixmaps_t *SkYUVAPixmaps_newCopy(const reskia_yuva_pixmaps_t *pixmaps) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(pixmaps);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_yuva_pixmaps_t *>(new SkYUVAPixmaps(*native));
}

void SkYUVAPixmaps_delete(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    delete as_yuva_pixmaps(yuva_pixmaps);
}

bool SkYUVAPixmaps_isValid(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(yuva_pixmaps);
    return native != nullptr && native->isValid();
}

const reskia_yuva_info_t *SkYUVAPixmaps_yuvaInfo(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    SkYUVAPixmaps *native = as_yuva_pixmaps(yuva_pixmaps);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_yuva_info_t *>(&native->yuvaInfo());
}

reskia_yuva_pixmaps_data_type_t SkYUVAPixmaps_dataType(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(yuva_pixmaps);
    if (native == nullptr || !native->isValid()) {
        return -1;
    }
    return static_cast<reskia_yuva_pixmaps_data_type_t>(native->dataType());
}

sk_yuva_pixmap_info_t SkYUVAPixmaps_pixmapsInfo(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(yuva_pixmaps);
    if (native == nullptr || !native->isValid()) {
        return 0;
    }
    return static_sk_yuva_pixmap_info_make(native->pixmapsInfo());
}

int SkYUVAPixmaps_numPlanes(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(yuva_pixmaps);
    return native != nullptr ? native->numPlanes() : 0;
}

const reskia_pixmap_t *SkYUVAPixmaps_planes(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(yuva_pixmaps);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_pixmap_t *>(native->planes().data());
}

const reskia_pixmap_t *SkYUVAPixmaps_plane(reskia_yuva_pixmaps_t *yuva_pixmaps, int i) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(yuva_pixmaps);
    if (native == nullptr || i < 0 || i >= native->numPlanes()) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_pixmap_t *>(&native->plane(i));
}

//SkYUVAInfo::YUVALocations SkYUVAPixmaps_toYUVALocations(SkYUVAPixmaps *yuva_pixmaps) {
//    return yuva_pixmaps->toYUVALocations();
//}

bool SkYUVAPixmaps_ownsStorage(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(yuva_pixmaps);
    return native != nullptr && native->ownsStorage();
}

// static

reskia_yuva_pixmaps_color_type_t SkYUVAPixmaps_RecommendedRGBAColorType(reskia_yuva_pixmaps_data_type_t type) {
    if (!is_valid_data_type(type)) {
        return -1;
    }
    return static_cast<reskia_yuva_pixmaps_color_type_t>(
            SkYUVAPixmaps::RecommendedRGBAColorType(static_cast<SkYUVAPixmaps::DataType>(type)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_Allocate(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo) {
    const SkYUVAPixmapInfo *info = as_yuva_pixmap_info(yuvaPixmapInfo);
    if (info == nullptr) {
        return 0;
    }
    return make_yuva_pixmaps_handle_if_valid(SkYUVAPixmaps::Allocate(*info));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromData(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo, sk_data_t data) {
    const SkYUVAPixmapInfo *info = as_yuva_pixmap_info(yuvaPixmapInfo);
    if (info == nullptr || static_sk_data_get_ptr(data) == nullptr) {
        return 0;
    }
    return make_yuva_pixmaps_handle_if_valid(SkYUVAPixmaps::FromData(*info, static_sk_data_get_entity(data)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_MakeCopy(const reskia_yuva_pixmaps_t *src) {
    const SkYUVAPixmaps *native = as_yuva_pixmaps(src);
    if (native == nullptr || !native->isValid()) {
        return 0;
    }
    return make_yuva_pixmaps_handle_if_valid(SkYUVAPixmaps::MakeCopy(*native));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalMemory(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo, void *memory) {
    const SkYUVAPixmapInfo *info = as_yuva_pixmap_info(yuvaPixmapInfo);
    if (info == nullptr || memory == nullptr) {
        return 0;
    }
    return make_yuva_pixmaps_handle_if_valid(SkYUVAPixmaps::FromExternalMemory(*info, memory));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalPixmaps(const reskia_yuva_info_t *yuvaInfo, const reskia_pixmap_t *pixmaps) {
    const SkYUVAInfo *info = as_yuva_info(yuvaInfo);
    const SkPixmap *native_pixmaps = as_pixmaps(pixmaps);
    if (info == nullptr || native_pixmaps == nullptr) {
        return 0;
    }
    return make_yuva_pixmaps_handle_if_valid(SkYUVAPixmaps::FromExternalPixmaps(*info, native_pixmaps));
}

}
