//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_YUVA_INFO_H
#define RAIA_SKIA_SK_YUVA_INFO_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_yuva_info.h"
#include "../handles/static_std_tuple_int_int.h"

typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_yuva_info_t reskia_yuva_info_t;
typedef int32_t reskia_yuva_info_plane_config_t; // SkYUVAInfo::PlaneConfig
typedef int32_t reskia_yuva_info_subsampling_t; // SkYUVAInfo::Subsampling
typedef int32_t reskia_yuva_info_yuv_color_space_t; // SkYUVColorSpace
typedef int32_t reskia_yuva_info_siting_t; // SkYUVAInfo::Siting
typedef int32_t reskia_yuva_info_encoded_origin_t; // SkEncodedOrigin

typedef struct reskia_yuva_location_t {
    int32_t plane;
    int32_t channel;
} reskia_yuva_location_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkYUVAInfo & operator=(const SkYUVAInfo &that)
reskia_yuva_info_t *SkYUVAInfo_new(); // () -> SkYUVAInfo *
reskia_yuva_info_t *SkYUVAInfo_newCopy(const reskia_yuva_info_t *info); // (const SkYUVAInfo *info) -> SkYUVAInfo *
reskia_yuva_info_t *SkYUVAInfo_newWithDimensionsConfigSubsamplingSpaceOriginAndSiting(sk_i_size_t dimensions, int config, int subsampling, int space, int origin, int sitingX, int sitingY); // (sk_i_size_t dimensions, SkYUVAInfo::PlaneConfig config, SkYUVAInfo::Subsampling subsampling, SkYUVColorSpace space, SkEncodedOrigin origin, SkYUVAInfo::Siting sitingX, SkYUVAInfo::Siting sitingY) -> SkYUVAInfo *
void SkYUVAInfo_delete(reskia_yuva_info_t *yuvaInfo); // (SkYUVAInfo *yuvaInfo)
bool SkYUVAInfo_equals(reskia_yuva_info_t *yuva_info, const reskia_yuva_info_t *other); // (SkYUVAInfo *yuva_info, const SkYUVAInfo *other) -> bool
bool SkYUVAInfo_notEquals(reskia_yuva_info_t *yuva_info, const reskia_yuva_info_t *other); // (SkYUVAInfo *yuva_info, const SkYUVAInfo *other) -> bool
reskia_yuva_info_plane_config_t SkYUVAInfo_planeConfig(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::PlaneConfig
reskia_yuva_info_subsampling_t SkYUVAInfo_subsampling(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Subsampling
tuple_int_int_t SkYUVAInfo_planeSubsamplingFactors(reskia_yuva_info_t *yuva_info, int planeIdx); // (SkYUVAInfo *yuva_info, int planeIdx) -> tuple_int_int_t
sk_i_size_t SkYUVAInfo_dimensions(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> sk_i_size_t
int SkYUVAInfo_width(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> int
int SkYUVAInfo_height(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> int
reskia_yuva_info_yuv_color_space_t SkYUVAInfo_yuvColorSpace(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVColorSpace
reskia_yuva_info_siting_t SkYUVAInfo_sitingX(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Siting
reskia_yuva_info_siting_t SkYUVAInfo_sitingY(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Siting
reskia_yuva_info_encoded_origin_t SkYUVAInfo_origin(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkEncodedOrigin
sk_matrix_t SkYUVAInfo_originMatrix(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> sk_matrix_t
sk_matrix_t SkYUVAInfo_inverseOriginMatrix(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> sk_matrix_t
bool SkYUVAInfo_hasAlpha(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> bool
int SkYUVAInfo_planeDimensions(reskia_yuva_info_t *yuva_info, reskia_i_size_t *planeDimensions); // (SkYUVAInfo *yuva_info, SkISize planeDimensions[SkYUVAInfo::kMaxPlanes]) -> int
size_t SkYUVAInfo_computeTotalBytes(reskia_yuva_info_t *yuva_info, const size_t *rowBytes, size_t *planeSizes); // (SkYUVAInfo *yuva_info, const size_t rowBytes[SkYUVAInfo::kMaxPlanes], size_t planeSizes[SkYUVAInfo::kMaxPlanes]) -> size_t
int SkYUVAInfo_numPlanes(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> int
int SkYUVAInfo_numChannelsInPlane(reskia_yuva_info_t *yuva_info, int i); // (SkYUVAInfo *yuva_info, int i) -> int
bool SkYUVAInfo_toYUVALocations(reskia_yuva_info_t *yuva_info, const uint32_t *channelFlags, reskia_yuva_location_t *locations); // locations[4]. invalid input clears locations and returns false
sk_yuva_info_t SkYUVAInfo_makeSubsampling(reskia_yuva_info_t *yuva_info, reskia_yuva_info_subsampling_t subsampling); // (SkYUVAInfo *yuva_info, SkYUVAInfo::Subsampling subsampling) -> sk_yuva_info_t
sk_yuva_info_t SkYUVAInfo_makeDimensions(reskia_yuva_info_t *yuva_info, sk_i_size_t size); // (SkYUVAInfo *yuva_info, sk_i_size_t size) -> sk_yuva_info_t
bool SkYUVAInfo_isValid(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> bool

// static

tuple_int_int_t SkYUVAInfo_SubsamplingFactors(reskia_yuva_info_subsampling_t subsampling); // (SkYUVAInfo::Subsampling subsampling) -> tuple_int_int_t
tuple_int_int_t SkYUVAInfo_PlaneSubsamplingFactors(reskia_yuva_info_plane_config_t config, reskia_yuva_info_subsampling_t subsampling, int planeIdx); // (SkYUVAInfo::PlaneConfig config, SkYUVAInfo::Subsampling subsampling, int planeIdx) -> tuple_int_int_t
int SkYUVAInfo_PlaneDimensions(sk_i_size_t imageDimensions, reskia_yuva_info_plane_config_t plane, reskia_yuva_info_subsampling_t subsampling, reskia_yuva_info_encoded_origin_t origin, reskia_i_size_t *planeDimensions); // (sk_i_size_t imageDimensions, SkYUVAInfo::PlaneConfig plane, SkYUVAInfo::Subsampling subsampling, SkEncodedOrigin origin, SkISize planeDimensions[SkYUVAInfo::kMaxPlanes]) -> int
int SkYUVAInfo_NumPlanes(reskia_yuva_info_plane_config_t config); // (SkYUVAInfo::PlaneConfig config) -> int
int SkYUVAInfo_NumChannelsInPlane(reskia_yuva_info_plane_config_t config, int i); // (SkYUVAInfo::PlaneConfig config, int i) -> int
bool SkYUVAInfo_GetYUVALocations(reskia_yuva_info_plane_config_t config, const uint32_t *planeChannelFlags, reskia_yuva_location_t *locations); // (SkYUVAInfo::PlaneConfig config, const uint32_t *planeChannelFlags, reskia_yuva_location_t locations[4]) -> bool
bool SkYUVAInfo_HasAlpha(reskia_yuva_info_plane_config_t config); // (SkYUVAInfo::PlaneConfig config) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_YUVA_INFO_H
