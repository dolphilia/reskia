//
// Created by dolphilia on 2024/01/11.
//

#include "sk_yuva_info.h"

#include "include/codec/SkEncodedOrigin.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkYUVAInfo.h"
#include "src/core/SkYUVAInfoLocation.h"

#include "../handles/static_std_tuple_int_int.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_yuva_info.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_matrix-internal.h"
#include "../handles/static_sk_yuva_info-internal.h"
#include "../handles/static_std_tuple_int_int-internal.h"

namespace {

SkYUVAInfo *as_yuva_info(reskia_yuva_info_t *info) {
    return reinterpret_cast<SkYUVAInfo *>(info);
}

const SkYUVAInfo *as_yuva_info(const reskia_yuva_info_t *info) {
    return reinterpret_cast<const SkYUVAInfo *>(info);
}

bool is_valid_plane_config(int config) {
    return config >= 0 && config <= static_cast<int>(SkYUVAInfo::PlaneConfig::kLast);
}

bool is_valid_subsampling(int subsampling) {
    return subsampling >= 0 && subsampling <= static_cast<int>(SkYUVAInfo::Subsampling::kLast);
}

bool is_valid_yuv_color_space(int space) {
    return space >= 0 && space <= kLastEnum_SkYUVColorSpace;
}

bool is_valid_origin(int origin) {
    return origin >= kTopLeft_SkEncodedOrigin && origin <= kLast_SkEncodedOrigin;
}

bool is_valid_siting(int siting) {
    return siting == static_cast<int>(SkYUVAInfo::Siting::kCentered);
}

SkISize *get_size_ptr(sk_i_size_t size) {
    return static_cast<SkISize *>(static_sk_i_size_get_ptr(size));
}

bool has_valid_plane_index(SkYUVAInfo::PlaneConfig config, int planeIdx) {
    return is_valid_plane_config(static_cast<int>(config)) &&
           planeIdx >= 0 &&
           planeIdx < SkYUVAInfo::NumPlanes(config);
}

void clear_plane_dimensions(reskia_i_size_t *planeDimensions) {
    if (planeDimensions == nullptr) {
        return;
    }
    SkISize *dimensions = reinterpret_cast<SkISize *>(planeDimensions);
    for (int i = 0; i < SkYUVAInfo::kMaxPlanes; ++i) {
        dimensions[i] = SkISize{0, 0};
    }
}

void clear_plane_sizes(size_t *planeSizes) {
    if (planeSizes == nullptr) {
        return;
    }
    for (int i = 0; i < SkYUVAInfo::kMaxPlanes; ++i) {
        planeSizes[i] = 0;
    }
}

void clear_yuva_locations(reskia_yuva_location_t *locations) {
    if (locations == nullptr) {
        return;
    }
    for (int i = 0; i < SkYUVAInfo::kYUVAChannelCount; ++i) {
        locations[i].plane = -1;
        locations[i].channel = -1;
    }
}

}

extern "C" {

// SkYUVAInfo & operator=(const SkYUVAInfo &that)
reskia_yuva_info_t *SkYUVAInfo_new() {
    return reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo());
}

reskia_yuva_info_t *SkYUVAInfo_newCopy(const reskia_yuva_info_t *info) {
    const SkYUVAInfo *native = as_yuva_info(info);
    if (native == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo(*native));
}

reskia_yuva_info_t *SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(sk_i_size_t dimensions, int config, int subsampling, int space, int origin, int sitingX, int sitingY) {
    const SkISize *native_dimensions = get_size_ptr(dimensions);
    if (native_dimensions == nullptr ||
        !is_valid_plane_config(config) ||
        !is_valid_subsampling(subsampling) ||
        !is_valid_yuv_color_space(space) ||
        !is_valid_origin(origin) ||
        !is_valid_siting(sitingX) ||
        !is_valid_siting(sitingY)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo(*native_dimensions, static_cast<SkYUVAInfo::PlaneConfig>(config), static_cast<SkYUVAInfo::Subsampling>(subsampling), static_cast<SkYUVColorSpace>(space), static_cast<SkEncodedOrigin>(origin), static_cast<SkYUVAInfo::Siting>(sitingX), static_cast<SkYUVAInfo::Siting>(sitingY)));
}

void SkYUVAInfo_delete(reskia_yuva_info_t *yuvaInfo) {
    delete as_yuva_info(yuvaInfo);
}

bool SkYUVAInfo_equals(reskia_yuva_info_t *yuva_info, const reskia_yuva_info_t *other) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    const SkYUVAInfo *other_native = as_yuva_info(other);
    return native != nullptr && other_native != nullptr && *native == *other_native;
}

bool SkYUVAInfo_notEquals(reskia_yuva_info_t *yuva_info, const reskia_yuva_info_t *other) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    const SkYUVAInfo *other_native = as_yuva_info(other);
    return native != nullptr && other_native != nullptr && *native != *other_native;
}

reskia_yuva_info_plane_config_t SkYUVAInfo_planeConfig(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? static_cast<reskia_yuva_info_plane_config_t>(native->planeConfig()) : -1;
}

reskia_yuva_info_subsampling_t SkYUVAInfo_subsampling(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? static_cast<reskia_yuva_info_subsampling_t>(native->subsampling()) : -1;
}

tuple_int_int_t SkYUVAInfo_planeSubsamplingFactors(reskia_yuva_info_t *yuva_info, int planeIdx) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    if (native == nullptr || !has_valid_plane_index(native->planeConfig(), planeIdx)) {
        return 0;
    }
    return static_tuple_int_int_make(native->planeSubsamplingFactors(planeIdx));
}

sk_i_size_t SkYUVAInfo_dimensions(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? static_sk_i_size_make(native->dimensions()) : 0;
}

int SkYUVAInfo_width(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? native->width() : 0;
}

int SkYUVAInfo_height(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? native->height() : 0;
}

reskia_yuva_info_yuv_color_space_t SkYUVAInfo_yuvColorSpace(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? static_cast<reskia_yuva_info_yuv_color_space_t>(native->yuvColorSpace()) : -1;
}

reskia_yuva_info_siting_t SkYUVAInfo_sitingX(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? static_cast<reskia_yuva_info_siting_t>(native->sitingX()) : -1;
}

reskia_yuva_info_siting_t SkYUVAInfo_sitingY(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? static_cast<reskia_yuva_info_siting_t>(native->sitingY()) : -1;
}

reskia_yuva_info_encoded_origin_t SkYUVAInfo_origin(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? static_cast<reskia_yuva_info_encoded_origin_t>(native->origin()) : -1;
}

sk_matrix_t SkYUVAInfo_originMatrix(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? static_sk_matrix_make(native->originMatrix()) : 0;
}

bool SkYUVAInfo_hasAlpha(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr && native->hasAlpha();
}

int SkYUVAInfo_planeDimensions(reskia_yuva_info_t *yuva_info, reskia_i_size_t *planeDimensions) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    if (native == nullptr || planeDimensions == nullptr) {
        clear_plane_dimensions(planeDimensions);
        return 0;
    }
    return native->planeDimensions(reinterpret_cast<SkISize *>(planeDimensions));
}

size_t SkYUVAInfo_computeTotalBytes(reskia_yuva_info_t *yuva_info, const size_t *rowBytes, size_t *planeSizes) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    if (native == nullptr || rowBytes == nullptr) {
        clear_plane_sizes(planeSizes);
        return 0;
    }
    return native->computeTotalBytes(rowBytes, planeSizes);
}

int SkYUVAInfo_numPlanes(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? native->numPlanes() : 0;
}

int SkYUVAInfo_numChannelsInPlane(reskia_yuva_info_t *yuva_info, int i) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr ? native->numChannelsInPlane(i) : 0;
}

bool SkYUVAInfo_toYUVALocations(reskia_yuva_info_t *yuva_info, const uint32_t *channelFlags, reskia_yuva_location_t *locations) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    if (native == nullptr || channelFlags == nullptr || locations == nullptr) {
        clear_yuva_locations(locations);
        return false;
    }
    auto yuvaLocations = native->toYUVALocations(channelFlags);
    for (int i = 0; i < SkYUVAInfo::kYUVAChannelCount; ++i) {
        locations[i].plane = yuvaLocations[i].fPlane;
        locations[i].channel = static_cast<int32_t>(yuvaLocations[i].fChannel);
    }
    return SkYUVAInfo::YUVALocation::AreValidLocations(yuvaLocations);
}

sk_yuva_info_t SkYUVAInfo_makeSubsampling(reskia_yuva_info_t *yuva_info, reskia_yuva_info_subsampling_t subsampling) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    if (native == nullptr || !is_valid_subsampling(subsampling)) {
        return 0;
    }
    SkYUVAInfo result = native->makeSubsampling(static_cast<SkYUVAInfo::Subsampling>(subsampling));
    return result.isValid() ? static_sk_yuva_info_make(result) : 0;
}

sk_yuva_info_t SkYUVAInfo_makeDimensions(reskia_yuva_info_t *yuva_info, sk_i_size_t size) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    const SkISize *native_size = get_size_ptr(size);
    if (native == nullptr || native_size == nullptr) {
        return 0;
    }
    SkYUVAInfo result = native->makeDimensions(*native_size);
    return result.isValid() ? static_sk_yuva_info_make(result) : 0;
}

bool SkYUVAInfo_isValid(reskia_yuva_info_t *yuva_info) {
    const SkYUVAInfo *native = as_yuva_info(yuva_info);
    return native != nullptr && native->isValid();
}

// static

tuple_int_int_t SkYUVAInfo_SubsamplingFactors(reskia_yuva_info_subsampling_t subsampling) {
    if (!is_valid_subsampling(subsampling)) {
        return 0;
    }
    return static_tuple_int_int_make(SkYUVAInfo::SubsamplingFactors(static_cast<SkYUVAInfo::Subsampling>(subsampling)));
}

tuple_int_int_t SkYUVAInfo_PlaneSubsamplingFactors(reskia_yuva_info_plane_config_t config, reskia_yuva_info_subsampling_t subsampling, int planeIdx) {
    if (!is_valid_plane_config(config) || !is_valid_subsampling(subsampling)) {
        return 0;
    }
    if (!has_valid_plane_index(static_cast<SkYUVAInfo::PlaneConfig>(config), planeIdx)) {
        return 0;
    }
    return static_tuple_int_int_make(SkYUVAInfo::PlaneSubsamplingFactors(static_cast<SkYUVAInfo::PlaneConfig>(config), static_cast<SkYUVAInfo::Subsampling>(subsampling), planeIdx));
}

int SkYUVAInfo_PlaneDimensions(sk_i_size_t imageDimensions, reskia_yuva_info_plane_config_t plane, reskia_yuva_info_subsampling_t subsampling, reskia_yuva_info_encoded_origin_t origin, reskia_i_size_t *planeDimensions) {
    const SkISize *native_dimensions = get_size_ptr(imageDimensions);
    if (native_dimensions == nullptr ||
        planeDimensions == nullptr ||
        !is_valid_plane_config(plane) ||
        !is_valid_subsampling(subsampling) ||
        !is_valid_origin(origin)) {
        clear_plane_dimensions(planeDimensions);
        return 0;
    }
    return SkYUVAInfo::PlaneDimensions(*native_dimensions, static_cast<SkYUVAInfo::PlaneConfig>(plane), static_cast<SkYUVAInfo::Subsampling>(subsampling), static_cast<SkEncodedOrigin>(origin), reinterpret_cast<SkISize *>(planeDimensions));
}

int SkYUVAInfo_NumPlanes(reskia_yuva_info_plane_config_t config) {
    if (!is_valid_plane_config(config)) {
        return 0;
    }
    return SkYUVAInfo::NumPlanes(static_cast<SkYUVAInfo::PlaneConfig>(config));
}

int SkYUVAInfo_NumChannelsInPlane(reskia_yuva_info_plane_config_t config, int i) {
    if (!is_valid_plane_config(config)) {
        return 0;
    }
    return SkYUVAInfo::NumChannelsInPlane(static_cast<SkYUVAInfo::PlaneConfig>(config), i);
}

bool SkYUVAInfo_GetYUVALocations(reskia_yuva_info_plane_config_t config, const uint32_t *planeChannelFlags, reskia_yuva_location_t *locations) {
    if (!planeChannelFlags || !locations || !is_valid_plane_config(config)) {
        clear_yuva_locations(locations);
        return false;
    }
    auto yuvaLocations = SkYUVAInfo::GetYUVALocations(static_cast<SkYUVAInfo::PlaneConfig>(config), planeChannelFlags);
    for (int i = 0; i < SkYUVAInfo::kYUVAChannelCount; ++i) {
        locations[i].plane = yuvaLocations[i].fPlane;
        locations[i].channel = static_cast<int32_t>(yuvaLocations[i].fChannel);
    }
    return SkYUVAInfo::YUVALocation::AreValidLocations(yuvaLocations);
}

bool SkYUVAInfo_HasAlpha(reskia_yuva_info_plane_config_t config) {
    if (!is_valid_plane_config(config)) {
        return false;
    }
    return SkYUVAInfo::HasAlpha(static_cast<SkYUVAInfo::PlaneConfig>(config));
}

}
