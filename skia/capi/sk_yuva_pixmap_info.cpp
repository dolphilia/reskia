//
// Created by dolphilia on 2024/01/11.
//

#include "sk_yuva_pixmap_info.h"

#include "include/core/SkYUVAPixmaps.h"
#include "include/core/SkColorType.h"

#include "../handles/static_std_tuple_int_sk_yuva_pixmap_info_data_type.h"

#include "../handles/static_std_tuple_int_sk_yuva_pixmap_info_data_type-internal.h"

namespace {

SkYUVAPixmapInfo *as_yuva_pixmap_info(reskia_yuva_pixmap_info_t *info) {
    return reinterpret_cast<SkYUVAPixmapInfo *>(info);
}

const SkYUVAPixmapInfo *as_yuva_pixmap_info(const reskia_yuva_pixmap_info_t *info) {
    return reinterpret_cast<const SkYUVAPixmapInfo *>(info);
}

const SkYUVAInfo *as_yuva_info(const reskia_yuva_info_t *info) {
    return reinterpret_cast<const SkYUVAInfo *>(info);
}

const SkYUVAPixmapInfo::SupportedDataTypes *as_supported_data_types(const reskia_yuva_pixmap_info_supported_data_types_t *type) {
    return reinterpret_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(type);
}

bool is_valid_data_type(reskia_yuva_pixmap_info_data_type_t type) {
    return type >= 0 && type <= static_cast<reskia_yuva_pixmap_info_data_type_t>(SkYUVAPixmapInfo::DataType::kLast);
}

bool is_valid_color_type(int type) {
    return type >= 0 && type <= kLastEnum_SkColorType;
}

bool color_types_are_valid_for_info(const SkYUVAInfo &info, const int *types) {
    const int num_planes = info.numPlanes();
    if (num_planes < 0 || num_planes > SkYUVAPixmapInfo::kMaxPlanes) {
        return false;
    }
    for (int i = 0; i < num_planes; ++i) {
        if (!is_valid_color_type(types[i])) {
            return false;
        }
    }
    return true;
}

bool has_plane_index(const SkYUVAPixmapInfo *info, int i) {
    return info != nullptr && i >= 0 && i < info->numPlanes();
}

}

extern "C" {

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new() {
    return reinterpret_cast<reskia_yuva_pixmap_info_t *>(new SkYUVAPixmapInfo());
}

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_newWithInfoColorTypesAndRowBytes(const reskia_yuva_info_t *info, const int *type, const size_t *rowBytes) {
    const SkYUVAInfo *yuva_info = as_yuva_info(info);
    if (yuva_info == nullptr || type == nullptr || !color_types_are_valid_for_info(*yuva_info, type)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_yuva_pixmap_info_t *>(new SkYUVAPixmapInfo(*yuva_info, reinterpret_cast<const SkColorType *>(type), rowBytes));
}

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_newWithInfoDataTypeAndRowBytes(const reskia_yuva_info_t *info, reskia_yuva_pixmap_info_data_type_t type, const size_t *rowBytes) {
    const SkYUVAInfo *yuva_info = as_yuva_info(info);
    if (yuva_info == nullptr || !is_valid_data_type(type)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_yuva_pixmap_info_t *>(new SkYUVAPixmapInfo(*yuva_info, static_cast<SkYUVAPixmapInfo::DataType>(type), rowBytes));
}

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_newCopy(const reskia_yuva_pixmap_info_t *info) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(info);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_yuva_pixmap_info_t *>(new SkYUVAPixmapInfo(*native));
}

void SkYUVAPixmapInfo_delete(reskia_yuva_pixmap_info_t *yuvaPixmapInfo) {
    delete as_yuva_pixmap_info(yuvaPixmapInfo);
}

bool SkYUVAPixmapInfo_equals(reskia_yuva_pixmap_info_t *yuva_pixmap_info, const reskia_yuva_pixmap_info_t *other) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    const SkYUVAPixmapInfo *other_native = as_yuva_pixmap_info(other);
    return native != nullptr && other_native != nullptr && *native == *other_native;
}

bool SkYUVAPixmapInfo_notEquals(reskia_yuva_pixmap_info_t *yuva_pixmap_info, const reskia_yuva_pixmap_info_t *other) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    const SkYUVAPixmapInfo *other_native = as_yuva_pixmap_info(other);
    return native != nullptr && other_native != nullptr && *native != *other_native;
}

const reskia_yuva_info_t *SkYUVAPixmapInfo_yuvaInfo(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_yuva_info_t *>(&native->yuvaInfo());
}

reskia_yuva_pixmap_info_yuv_color_space_t SkYUVAPixmapInfo_yuvColorSpace(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    if (native == nullptr) {
        return -1;
    }
    return static_cast<reskia_yuva_pixmap_info_yuv_color_space_t>(native->yuvColorSpace());
}

int SkYUVAPixmapInfo_numPlanes(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    return native != nullptr ? native->numPlanes() : 0;
}

reskia_yuva_pixmap_info_data_type_t SkYUVAPixmapInfo_dataType(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    if (native == nullptr) {
        return -1;
    }
    return static_cast<reskia_yuva_pixmap_info_data_type_t>(native->dataType());
}

size_t SkYUVAPixmapInfo_rowBytes(reskia_yuva_pixmap_info_t *yuva_pixmap_info, int i) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    return has_plane_index(native, i) ? native->rowBytes(i) : 0;
}

const reskia_image_info_t *SkYUVAPixmapInfo_planeInfo(reskia_yuva_pixmap_info_t *yuva_pixmap_info, int i) {
    SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    if (!has_plane_index(native, i)) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_image_info_t *>(&native->planeInfo(i));
}

size_t SkYUVAPixmapInfo_computeTotalBytes(reskia_yuva_pixmap_info_t *yuva_pixmap_info, size_t *planeSizes) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    if (native == nullptr) {
        if (planeSizes != nullptr) {
            for (int i = 0; i < SkYUVAPixmapInfo::kMaxPlanes; ++i) {
                planeSizes[i] = 0;
            }
        }
        return 0;
    }
    return native->computeTotalBytes(planeSizes);
}

bool SkYUVAPixmapInfo_initPixmapsFromSingleAllocation(reskia_yuva_pixmap_info_t *yuva_pixmap_info, void *memory, reskia_pixmap_t *pixmaps) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    if (native == nullptr || memory == nullptr || pixmaps == nullptr) {
        return false;
    }
    return native->initPixmapsFromSingleAllocation(memory, reinterpret_cast<SkPixmap *>(pixmaps));
}

bool SkYUVAPixmapInfo_isValid(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    return native != nullptr && native->isValid();
}

bool SkYUVAPixmapInfo_isSupported(reskia_yuva_pixmap_info_t *yuva_pixmap_info, const reskia_yuva_pixmap_info_supported_data_types_t *type) {
    const SkYUVAPixmapInfo *native = as_yuva_pixmap_info(yuva_pixmap_info);
    const SkYUVAPixmapInfo::SupportedDataTypes *supported = as_supported_data_types(type);
    return native != nullptr && supported != nullptr && native->isSupported(*supported);
}

// static

reskia_yuva_pixmap_info_color_type_t SkYUVAPixmapInfo_DefaultColorTypeForDataType(reskia_yuva_pixmap_info_data_type_t dataType, int numChannels) {
    if (!is_valid_data_type(dataType)) {
        return -1;
    }
    return static_cast<reskia_yuva_pixmap_info_color_type_t>(
            SkYUVAPixmapInfo::DefaultColorTypeForDataType(static_cast<SkYUVAPixmapInfo::DataType>(dataType), numChannels));
}

tuple_int_sk_yuva_pixmap_info_data_type_t SkYUVAPixmapInfo_NumChannelsAndDataType(reskia_yuva_pixmap_info_color_type_t type) {
    if (!is_valid_color_type(type)) {
        return 0;
    }
    return static_tuple_int_sk_yuva_pixmap_info_data_type_make(SkYUVAPixmapInfo::NumChannelsAndDataType(static_cast<SkColorType>(type)));
}

}
