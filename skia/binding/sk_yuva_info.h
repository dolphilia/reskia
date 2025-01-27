//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_YUVA_INFO_H
#define RAIA_SKIA_SK_YUVA_INFO_H

#include "include/core/SkYUVAInfo.h"
#include "../static/static_std_tuple_int_int.h"
#include "../static/static_sk_matrix.h"
#include "../static/static_sk_yuva_info.h"
#include "../static/static_sk_i_size.h"

extern "C" {

// SkYUVAInfo & operator=(const SkYUVAInfo &that)
// bool operator==(const SkYUVAInfo &that)
// bool operator!=(const SkYUVAInfo &that)

SkYUVAInfo *SkYUVAInfo_new(); // () -> SkYUVAInfo *
SkYUVAInfo *SkYUVAInfo_new_2(const SkYUVAInfo *info); // (const SkYUVAInfo *info) -> SkYUVAInfo *
SkYUVAInfo *SkYUVAInfo_new_3(sk_i_size_t dimensions, SkYUVAInfo::PlaneConfig config, SkYUVAInfo::Subsampling subsampling, SkYUVColorSpace space, SkEncodedOrigin origin, SkYUVAInfo::Siting sitingX, SkYUVAInfo::Siting sitingY); // (sk_i_size_t dimensions, SkYUVAInfo::PlaneConfig config, SkYUVAInfo::Subsampling subsampling, SkYUVColorSpace space, SkEncodedOrigin origin, SkYUVAInfo::Siting sitingX, SkYUVAInfo::Siting sitingY) -> SkYUVAInfo *
void SkYUVAInfo_delete(SkYUVAInfo *yuvaInfo); // (SkYUVAInfo *yuvaInfo)
SkYUVAInfo::PlaneConfig SkYUVAInfo_planeConfig(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::PlaneConfig
SkYUVAInfo::Subsampling SkYUVAInfo_subsampling(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Subsampling
tuple_int_int_t SkYUVAInfo_planeSubsamplingFactors(SkYUVAInfo *yuva_info, int planeIdx); // (SkYUVAInfo *yuva_info, int planeIdx) -> tuple_int_int_t
sk_i_size_t SkYUVAInfo_dimensions(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> sk_i_size_t
int SkYUVAInfo_width(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> int
int SkYUVAInfo_height(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> int
SkYUVColorSpace SkYUVAInfo_yuvColorSpace(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVColorSpace
SkYUVAInfo::Siting SkYUVAInfo_sitingX(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Siting
SkYUVAInfo::Siting SkYUVAInfo_sitingY(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Siting
SkEncodedOrigin SkYUVAInfo_origin(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> SkEncodedOrigin
sk_matrix_t SkYUVAInfo_originMatrix(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> sk_matrix_t
bool SkYUVAInfo_hasAlpha(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> bool
int SkYUVAInfo_planeDimensions(SkYUVAInfo *yuva_info, SkISize planeDimensions[SkYUVAInfo::kMaxPlanes]); // (SkYUVAInfo *yuva_info, SkISize planeDimensions[SkYUVAInfo::kMaxPlanes]) -> int
size_t SkYUVAInfo_computeTotalBytes(SkYUVAInfo *yuva_info, const size_t rowBytes[SkYUVAInfo::kMaxPlanes], size_t planeSizes[SkYUVAInfo::kMaxPlanes]); // (SkYUVAInfo *yuva_info, const size_t rowBytes[SkYUVAInfo::kMaxPlanes], size_t planeSizes[SkYUVAInfo::kMaxPlanes]) -> size_t
int SkYUVAInfo_numPlanes(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> int
int SkYUVAInfo_numChannelsInPlane(SkYUVAInfo *yuva_info, int i); // (SkYUVAInfo *yuva_info, int i) -> int
// SkYUVAInfo::YUVALocations SkYUVAInfo_toYUVALocations(SkYUVAInfo *yuva_info, const uint32_t *channelFlags); // (SkYUVAInfo *yuva_info, const uint32_t *channelFlags) -> SkYUVAInfo::YUVALocations
sk_yuva_info_t SkYUVAInfo_makeSubsampling(SkYUVAInfo *yuva_info, SkYUVAInfo::Subsampling subsampling); // (SkYUVAInfo *yuva_info, SkYUVAInfo::Subsampling subsampling) -> sk_yuva_info_t
sk_yuva_info_t SkYUVAInfo_makeDimensions(SkYUVAInfo *yuva_info, sk_i_size_t size); // (SkYUVAInfo *yuva_info, sk_i_size_t size) -> sk_yuva_info_t
bool SkYUVAInfo_isValid(SkYUVAInfo *yuva_info); // (SkYUVAInfo *yuva_info) -> bool

// static

tuple_int_int_t SkYUVAInfo_SubsamplingFactors(SkYUVAInfo::Subsampling subsampling); // (SkYUVAInfo::Subsampling subsampling) -> tuple_int_int_t
tuple_int_int_t SkYUVAInfo_PlaneSubsamplingFactors(SkYUVAInfo::PlaneConfig config, SkYUVAInfo::Subsampling subsampling, int planeIdx); // (SkYUVAInfo::PlaneConfig config, SkYUVAInfo::Subsampling subsampling, int planeIdx) -> tuple_int_int_t
int SkYUVAInfo_PlaneDimensions(sk_i_size_t imageDimensions, SkYUVAInfo::PlaneConfig plane, SkYUVAInfo::Subsampling subsampling, SkEncodedOrigin origin, SkISize planeDimensions[SkYUVAInfo::kMaxPlanes]); // (sk_i_size_t imageDimensions, SkYUVAInfo::PlaneConfig plane, SkYUVAInfo::Subsampling subsampling, SkEncodedOrigin origin, SkISize planeDimensions[SkYUVAInfo::kMaxPlanes]) -> int
int SkYUVAInfo_NumPlanes(SkYUVAInfo::PlaneConfig config); // (SkYUVAInfo::PlaneConfig config) -> int
int SkYUVAInfo_NumChannelsInPlane(SkYUVAInfo::PlaneConfig config, int i); // (SkYUVAInfo::PlaneConfig config, int i) -> int
// SkYUVAInfo::YUVALocations SkYUVAInfo_GetYUVALocations(SkYUVAInfo::PlaneConfig config, const uint32_t *planeChannelFlags); // (SkYUVAInfo::PlaneConfig config, const uint32_t *planeChannelFlags) -> SkYUVAInfo::YUVALocations
bool SkYUVAInfo_HasAlpha(SkYUVAInfo::PlaneConfig config); // (SkYUVAInfo::PlaneConfig config) -> bool

}

#endif //RAIA_SKIA_SK_YUVA_INFO_H
