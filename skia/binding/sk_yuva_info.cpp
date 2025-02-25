//
// Created by dolphilia on 2024/01/11.
//

#include "sk_yuva_info.h"

#include "include/core/SkYUVAInfo.h"

#include "../static/static_std_tuple_int_int.h"
#include "../static/static_sk_matrix.h"
#include "../static/static_sk_yuva_info.h"
#include "../static/static_sk_i_size.h"

#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_matrix-internal.h"
#include "../static/static_sk_yuva_info-internal.h"
#include "../static/static_std_tuple_int_int-internal.h"

extern "C" {

// SkYUVAInfo & operator=(const SkYUVAInfo &that)
// bool operator==(const SkYUVAInfo &that)
// bool operator!=(const SkYUVAInfo &that)

void *SkYUVAInfo_new() {
    return new SkYUVAInfo();
}

void *SkYUVAInfo_new_2(const void *info) {
    return new SkYUVAInfo(* static_cast<const SkYUVAInfo *>(info));
}

void *SkYUVAInfo_new_3(sk_i_size_t dimensions, int config, int subsampling, int space, int origin, int sitingX, int sitingY) {
    return new SkYUVAInfo(static_sk_i_size_get_entity(dimensions), static_cast<SkYUVAInfo::PlaneConfig>(config), static_cast<SkYUVAInfo::Subsampling>(subsampling), static_cast<SkYUVColorSpace>(space), static_cast<SkEncodedOrigin>(origin), static_cast<SkYUVAInfo::Siting>(sitingX), static_cast<SkYUVAInfo::Siting>(sitingY));
}

void SkYUVAInfo_delete(void *yuvaInfo) {
    delete static_cast<SkYUVAInfo *>(yuvaInfo);
}

int SkYUVAInfo_planeConfig(void * yuva_info) {
    return static_cast<int>(static_cast<SkYUVAInfo *>(yuva_info)->planeConfig());
}

int SkYUVAInfo_subsampling(void * yuva_info) {
    return static_cast<int>(static_cast<SkYUVAInfo *>(yuva_info)->subsampling());
}

tuple_int_int_t SkYUVAInfo_planeSubsamplingFactors(void * yuva_info, int planeIdx) {
    return static_tuple_int_int_make(static_cast<SkYUVAInfo *>(yuva_info)->planeSubsamplingFactors(planeIdx));
}

sk_i_size_t SkYUVAInfo_dimensions(void * yuva_info) {
    return static_sk_i_size_make(static_cast<SkYUVAInfo *>(yuva_info)->dimensions());
}

int SkYUVAInfo_width(void * yuva_info) {
    return static_cast<SkYUVAInfo *>(yuva_info)->width();
}

int SkYUVAInfo_height(void * yuva_info) {
    return static_cast<SkYUVAInfo *>(yuva_info)->height();
}

int SkYUVAInfo_yuvColorSpace(void * yuva_info) {
    return static_cast<SkYUVAInfo *>(yuva_info)->yuvColorSpace();
}

int SkYUVAInfo_sitingX(void * yuva_info) {
    return static_cast<int>(static_cast<SkYUVAInfo *>(yuva_info)->sitingX());
}

int SkYUVAInfo_sitingY(void * yuva_info) {
    return static_cast<int>(static_cast<SkYUVAInfo *>(yuva_info)->sitingY());
}

int SkYUVAInfo_origin(void * yuva_info) {
    return static_cast<SkYUVAInfo *>(yuva_info)->origin();
}

sk_matrix_t SkYUVAInfo_originMatrix(void * yuva_info) {
    return static_sk_matrix_make(static_cast<SkYUVAInfo *>(yuva_info)->originMatrix());
}

bool SkYUVAInfo_hasAlpha(void * yuva_info) {
    return static_cast<SkYUVAInfo *>(yuva_info)->hasAlpha();
}

int SkYUVAInfo_planeDimensions(void * yuva_info, void * planeDimensions) {
    return static_cast<SkYUVAInfo *>(yuva_info)->planeDimensions(static_cast<SkISize *>(planeDimensions));
}

size_t SkYUVAInfo_computeTotalBytes(void * yuva_info, const void * rowBytes, void * planeSizes) {
    return static_cast<SkYUVAInfo *>(yuva_info)->computeTotalBytes(static_cast<const size_t *>(rowBytes), static_cast<size_t *>(planeSizes));
}

int SkYUVAInfo_numPlanes(void * yuva_info) {
    return static_cast<SkYUVAInfo *>(yuva_info)->numPlanes();
}

int SkYUVAInfo_numChannelsInPlane(void * yuva_info, int i) {
    return static_cast<SkYUVAInfo *>(yuva_info)->numChannelsInPlane(i);
}

//SkYUVAInfo::YUVALocations SkYUVAInfo_toYUVALocations(SkYUVAInfo * yuva_info, const uint32_t *channelFlags) {
//    return yuva_info->toYUVALocations(channelFlags);
//}

sk_yuva_info_t SkYUVAInfo_makeSubsampling(void * yuva_info, int subsampling) {
    return static_sk_yuva_info_make(static_cast<SkYUVAInfo *>(yuva_info)->makeSubsampling(static_cast<SkYUVAInfo::Subsampling>(subsampling)));
}

sk_yuva_info_t SkYUVAInfo_makeDimensions(void * yuva_info, sk_i_size_t size) {
    return static_sk_yuva_info_make(static_cast<SkYUVAInfo *>(yuva_info)->makeDimensions(static_sk_i_size_get_entity(size)));
}

bool SkYUVAInfo_isValid(void * yuva_info) {
    return static_cast<SkYUVAInfo *>(yuva_info)->isValid();
}

// static

tuple_int_int_t SkYUVAInfo_SubsamplingFactors(int subsampling) {
    return static_tuple_int_int_make(SkYUVAInfo::SubsamplingFactors(static_cast<SkYUVAInfo::Subsampling>(subsampling)));
}

tuple_int_int_t SkYUVAInfo_PlaneSubsamplingFactors(int config, int subsampling, int planeIdx) {
    return static_tuple_int_int_make(SkYUVAInfo::PlaneSubsamplingFactors(static_cast<SkYUVAInfo::PlaneConfig>(config), static_cast<SkYUVAInfo::Subsampling>(subsampling), planeIdx));
}

int SkYUVAInfo_PlaneDimensions(sk_i_size_t imageDimensions, int plane, int subsampling, int origin, void * planeDimensions) {
    return SkYUVAInfo::PlaneDimensions(static_sk_i_size_get_entity(imageDimensions), static_cast<SkYUVAInfo::PlaneConfig>(plane), static_cast<SkYUVAInfo::Subsampling>(subsampling), static_cast<SkEncodedOrigin>(origin), static_cast<SkISize *>(planeDimensions));
}

int SkYUVAInfo_NumPlanes(int config) {
    return SkYUVAInfo::NumPlanes(static_cast<SkYUVAInfo::PlaneConfig>(config));
}

int SkYUVAInfo_NumChannelsInPlane(int config, int i) {
    return SkYUVAInfo::NumChannelsInPlane(static_cast<SkYUVAInfo::PlaneConfig>(config), i);
}

// SkYUVAInfo::YUVALocations SkYUVAInfo_GetYUVALocations(SkYUVAInfo::PlaneConfig config, const uint32_t *planeChannelFlags) {
//     return SkYUVAInfo::GetYUVALocations(config, planeChannelFlags);
// }

bool SkYUVAInfo_HasAlpha(int config) {
    return SkYUVAInfo::HasAlpha(static_cast<SkYUVAInfo::PlaneConfig>(config));
}

}
