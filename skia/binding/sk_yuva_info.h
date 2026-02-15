//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_YUVA_INFO_H
#define RAIA_SKIA_SK_YUVA_INFO_H

#include <stddef.h>

#include "../static/static_sk_i_size.h"
#include "../static/static_sk_matrix.h"
#include "../static/static_sk_yuva_info.h"

typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_yuva_info_t reskia_yuva_info_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkYUVAInfo & operator=(const SkYUVAInfo &that)
// bool operator==(const SkYUVAInfo &that)
// bool operator!=(const SkYUVAInfo &that)

reskia_yuva_info_t *SkYUVAInfo_new(); // () -> SkYUVAInfo *
reskia_yuva_info_t *SkYUVAInfo_new_2(const reskia_yuva_info_t *info); // (const SkYUVAInfo *info) -> SkYUVAInfo *
reskia_yuva_info_t *SkYUVAInfo_new_3(int dimensions, int config, int subsampling, int space, int origin, int sitingX, int sitingY); // (sk_i_size_t dimensions, SkYUVAInfo::PlaneConfig config, SkYUVAInfo::Subsampling subsampling, SkYUVColorSpace space, SkEncodedOrigin origin, SkYUVAInfo::Siting sitingX, SkYUVAInfo::Siting sitingY) -> SkYUVAInfo *
void SkYUVAInfo_delete(reskia_yuva_info_t *yuvaInfo); // (SkYUVAInfo *yuvaInfo)
int SkYUVAInfo_planeConfig(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::PlaneConfig
int SkYUVAInfo_subsampling(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Subsampling
int SkYUVAInfo_planeSubsamplingFactors(reskia_yuva_info_t *yuva_info, int planeIdx); // (SkYUVAInfo *yuva_info, int planeIdx) -> tuple_int_int_t
sk_i_size_t SkYUVAInfo_dimensions(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> sk_i_size_t
int SkYUVAInfo_width(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> int
int SkYUVAInfo_height(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> int
int SkYUVAInfo_yuvColorSpace(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVColorSpace
int SkYUVAInfo_sitingX(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Siting
int SkYUVAInfo_sitingY(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkYUVAInfo::Siting
int SkYUVAInfo_origin(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> SkEncodedOrigin
sk_matrix_t SkYUVAInfo_originMatrix(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> sk_matrix_t
bool SkYUVAInfo_hasAlpha(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> bool
int SkYUVAInfo_planeDimensions(reskia_yuva_info_t *yuva_info, reskia_i_size_t *planeDimensions); // (SkYUVAInfo *yuva_info, SkISize planeDimensions[SkYUVAInfo::kMaxPlanes]) -> int
size_t SkYUVAInfo_computeTotalBytes(reskia_yuva_info_t *yuva_info, const size_t *rowBytes, size_t *planeSizes); // (SkYUVAInfo *yuva_info, const size_t rowBytes[SkYUVAInfo::kMaxPlanes], size_t planeSizes[SkYUVAInfo::kMaxPlanes]) -> size_t
int SkYUVAInfo_numPlanes(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> int
int SkYUVAInfo_numChannelsInPlane(reskia_yuva_info_t *yuva_info, int i); // (SkYUVAInfo *yuva_info, int i) -> int
// SkYUVAInfo::YUVALocations SkYUVAInfo_toYUVALocations(SkYUVAInfo *yuva_info, const uint32_t *channelFlags); // (SkYUVAInfo *yuva_info, const uint32_t *channelFlags) -> SkYUVAInfo::YUVALocations
sk_yuva_info_t SkYUVAInfo_makeSubsampling(reskia_yuva_info_t *yuva_info, int subsampling); // (SkYUVAInfo *yuva_info, SkYUVAInfo::Subsampling subsampling) -> sk_yuva_info_t
sk_yuva_info_t SkYUVAInfo_makeDimensions(reskia_yuva_info_t *yuva_info, sk_i_size_t size); // (SkYUVAInfo *yuva_info, sk_i_size_t size) -> sk_yuva_info_t
bool SkYUVAInfo_isValid(reskia_yuva_info_t *yuva_info); // (SkYUVAInfo *yuva_info) -> bool

// static

int SkYUVAInfo_SubsamplingFactors(int subsampling); // (SkYUVAInfo::Subsampling subsampling) -> tuple_int_int_t
int SkYUVAInfo_PlaneSubsamplingFactors(int config, int subsampling, int planeIdx); // (SkYUVAInfo::PlaneConfig config, SkYUVAInfo::Subsampling subsampling, int planeIdx) -> tuple_int_int_t
int SkYUVAInfo_PlaneDimensions(sk_i_size_t imageDimensions, int plane, int subsampling, int origin, reskia_i_size_t *planeDimensions); // (sk_i_size_t imageDimensions, SkYUVAInfo::PlaneConfig plane, SkYUVAInfo::Subsampling subsampling, SkEncodedOrigin origin, SkISize planeDimensions[SkYUVAInfo::kMaxPlanes]) -> int
int SkYUVAInfo_NumPlanes(int config); // (SkYUVAInfo::PlaneConfig config) -> int
int SkYUVAInfo_NumChannelsInPlane(int config, int i); // (SkYUVAInfo::PlaneConfig config, int i) -> int
// SkYUVAInfo::YUVALocations SkYUVAInfo_GetYUVALocations(SkYUVAInfo::PlaneConfig config, const uint32_t *planeChannelFlags); // (SkYUVAInfo::PlaneConfig config, const uint32_t *planeChannelFlags) -> SkYUVAInfo::YUVALocations
bool SkYUVAInfo_HasAlpha(int config); // (SkYUVAInfo::PlaneConfig config) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_YUVA_INFO_H
