//
// Created by dolphilia on 2024/01/11.
//

#include "sk_yuva_info.h"

#include "include/core/SkYUVAInfo.h"

#include "../handles/static_std_tuple_int_int.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_yuva_info.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_matrix-internal.h"
#include "../handles/static_sk_yuva_info-internal.h"
#include "../handles/static_std_tuple_int_int-internal.h"

extern "C" {

// SkYUVAInfo & operator=(const SkYUVAInfo &that)
// bool operator==(const SkYUVAInfo &that)
// bool operator!=(const SkYUVAInfo &that)

reskia_yuva_info_t *SkYUVAInfo_new() {
    return reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo());
}

reskia_yuva_info_t *SkYUVAInfo_newCopy(const reskia_yuva_info_t *info) {
    return reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo(*reinterpret_cast<const SkYUVAInfo *>(info)));
}

reskia_yuva_info_t *SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(sk_i_size_t dimensions, int config, int subsampling, int space, int origin, int sitingX, int sitingY) {
    return reinterpret_cast<reskia_yuva_info_t *>(new SkYUVAInfo(static_sk_i_size_get_entity(dimensions), static_cast<SkYUVAInfo::PlaneConfig>(config), static_cast<SkYUVAInfo::Subsampling>(subsampling), static_cast<SkYUVColorSpace>(space), static_cast<SkEncodedOrigin>(origin), static_cast<SkYUVAInfo::Siting>(sitingX), static_cast<SkYUVAInfo::Siting>(sitingY)));
}

void SkYUVAInfo_delete(reskia_yuva_info_t *yuvaInfo) {
    delete reinterpret_cast<SkYUVAInfo *>(yuvaInfo);
}

reskia_yuva_info_plane_config_t SkYUVAInfo_planeConfig(reskia_yuva_info_t *yuva_info) {
    return static_cast<reskia_yuva_info_plane_config_t>(reinterpret_cast<SkYUVAInfo *>(yuva_info)->planeConfig());
}

reskia_yuva_info_subsampling_t SkYUVAInfo_subsampling(reskia_yuva_info_t *yuva_info) {
    return static_cast<reskia_yuva_info_subsampling_t>(reinterpret_cast<SkYUVAInfo *>(yuva_info)->subsampling());
}

tuple_int_int_t SkYUVAInfo_planeSubsamplingFactors(reskia_yuva_info_t *yuva_info, int planeIdx) {
    return static_tuple_int_int_make(reinterpret_cast<SkYUVAInfo *>(yuva_info)->planeSubsamplingFactors(planeIdx));
}

sk_i_size_t SkYUVAInfo_dimensions(reskia_yuva_info_t *yuva_info) {
    return static_sk_i_size_make(reinterpret_cast<SkYUVAInfo *>(yuva_info)->dimensions());
}

int SkYUVAInfo_width(reskia_yuva_info_t *yuva_info) {
    return reinterpret_cast<SkYUVAInfo *>(yuva_info)->width();
}

int SkYUVAInfo_height(reskia_yuva_info_t *yuva_info) {
    return reinterpret_cast<SkYUVAInfo *>(yuva_info)->height();
}

reskia_yuva_info_yuv_color_space_t SkYUVAInfo_yuvColorSpace(reskia_yuva_info_t *yuva_info) {
    return static_cast<reskia_yuva_info_yuv_color_space_t>(reinterpret_cast<SkYUVAInfo *>(yuva_info)->yuvColorSpace());
}

reskia_yuva_info_siting_t SkYUVAInfo_sitingX(reskia_yuva_info_t *yuva_info) {
    return static_cast<reskia_yuva_info_siting_t>(reinterpret_cast<SkYUVAInfo *>(yuva_info)->sitingX());
}

reskia_yuva_info_siting_t SkYUVAInfo_sitingY(reskia_yuva_info_t *yuva_info) {
    return static_cast<reskia_yuva_info_siting_t>(reinterpret_cast<SkYUVAInfo *>(yuva_info)->sitingY());
}

reskia_yuva_info_encoded_origin_t SkYUVAInfo_origin(reskia_yuva_info_t *yuva_info) {
    return static_cast<reskia_yuva_info_encoded_origin_t>(reinterpret_cast<SkYUVAInfo *>(yuva_info)->origin());
}

sk_matrix_t SkYUVAInfo_originMatrix(reskia_yuva_info_t *yuva_info) {
    return static_sk_matrix_make(reinterpret_cast<SkYUVAInfo *>(yuva_info)->originMatrix());
}

bool SkYUVAInfo_hasAlpha(reskia_yuva_info_t *yuva_info) {
    return reinterpret_cast<SkYUVAInfo *>(yuva_info)->hasAlpha();
}

int SkYUVAInfo_planeDimensions(reskia_yuva_info_t *yuva_info, reskia_i_size_t *planeDimensions) {
    return reinterpret_cast<SkYUVAInfo *>(yuva_info)->planeDimensions(reinterpret_cast<SkISize *>(planeDimensions));
}

size_t SkYUVAInfo_computeTotalBytes(reskia_yuva_info_t *yuva_info, const size_t *rowBytes, size_t *planeSizes) {
    return reinterpret_cast<SkYUVAInfo *>(yuva_info)->computeTotalBytes(rowBytes, planeSizes);
}

int SkYUVAInfo_numPlanes(reskia_yuva_info_t *yuva_info) {
    return reinterpret_cast<SkYUVAInfo *>(yuva_info)->numPlanes();
}

int SkYUVAInfo_numChannelsInPlane(reskia_yuva_info_t *yuva_info, int i) {
    return reinterpret_cast<SkYUVAInfo *>(yuva_info)->numChannelsInPlane(i);
}

//SkYUVAInfo::YUVALocations SkYUVAInfo_toYUVALocations(SkYUVAInfo * yuva_info, const uint32_t *channelFlags) {
//    return yuva_info->toYUVALocations(channelFlags);
//}

sk_yuva_info_t SkYUVAInfo_makeSubsampling(reskia_yuva_info_t *yuva_info, reskia_yuva_info_subsampling_t subsampling) {
    return static_sk_yuva_info_make(reinterpret_cast<SkYUVAInfo *>(yuva_info)->makeSubsampling(static_cast<SkYUVAInfo::Subsampling>(subsampling)));
}

sk_yuva_info_t SkYUVAInfo_makeDimensions(reskia_yuva_info_t *yuva_info, sk_i_size_t size) {
    return static_sk_yuva_info_make(reinterpret_cast<SkYUVAInfo *>(yuva_info)->makeDimensions(static_sk_i_size_get_entity(size)));
}

bool SkYUVAInfo_isValid(reskia_yuva_info_t *yuva_info) {
    return reinterpret_cast<SkYUVAInfo *>(yuva_info)->isValid();
}

// static

tuple_int_int_t SkYUVAInfo_SubsamplingFactors(reskia_yuva_info_subsampling_t subsampling) {
    return static_tuple_int_int_make(SkYUVAInfo::SubsamplingFactors(static_cast<SkYUVAInfo::Subsampling>(subsampling)));
}

tuple_int_int_t SkYUVAInfo_PlaneSubsamplingFactors(reskia_yuva_info_plane_config_t config, reskia_yuva_info_subsampling_t subsampling, int planeIdx) {
    return static_tuple_int_int_make(SkYUVAInfo::PlaneSubsamplingFactors(static_cast<SkYUVAInfo::PlaneConfig>(config), static_cast<SkYUVAInfo::Subsampling>(subsampling), planeIdx));
}

int SkYUVAInfo_PlaneDimensions(sk_i_size_t imageDimensions, reskia_yuva_info_plane_config_t plane, reskia_yuva_info_subsampling_t subsampling, reskia_yuva_info_encoded_origin_t origin, reskia_i_size_t *planeDimensions) {
    return SkYUVAInfo::PlaneDimensions(static_sk_i_size_get_entity(imageDimensions), static_cast<SkYUVAInfo::PlaneConfig>(plane), static_cast<SkYUVAInfo::Subsampling>(subsampling), static_cast<SkEncodedOrigin>(origin), reinterpret_cast<SkISize *>(planeDimensions));
}

int SkYUVAInfo_NumPlanes(reskia_yuva_info_plane_config_t config) {
    return SkYUVAInfo::NumPlanes(static_cast<SkYUVAInfo::PlaneConfig>(config));
}

int SkYUVAInfo_NumChannelsInPlane(reskia_yuva_info_plane_config_t config, int i) {
    return SkYUVAInfo::NumChannelsInPlane(static_cast<SkYUVAInfo::PlaneConfig>(config), i);
}

// SkYUVAInfo::YUVALocations SkYUVAInfo_GetYUVALocations(SkYUVAInfo::PlaneConfig config, const uint32_t *planeChannelFlags) {
//     return SkYUVAInfo::GetYUVALocations(config, planeChannelFlags);
// }

bool SkYUVAInfo_HasAlpha(reskia_yuva_info_plane_config_t config) {
    return SkYUVAInfo::HasAlpha(static_cast<SkYUVAInfo::PlaneConfig>(config));
}

}
