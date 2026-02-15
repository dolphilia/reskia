//
// Created by dolphilia on 2024/01/11.
//

#include "sk_yuva_pixmap_info.h"

#include "include/core/SkYUVAPixmaps.h"

#include "../static/static_std_tuple_int_sk_yuva_pixmap_info_data_type.h"

#include "../static/static_std_tuple_int_sk_yuva_pixmap_info_data_type-internal.h"

extern "C" {

// SkYUVAPixmapInfo & operator=(const SkYUVAPixmapInfo &)
// bool operator==(const SkYUVAPixmapInfo &)
// bool operator!=(const SkYUVAPixmapInfo &that)

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new() {
    return reinterpret_cast<reskia_yuva_pixmap_info_t *>(new SkYUVAPixmapInfo());
}

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new_2(const reskia_yuva_info_t *info, const int *type, const size_t *rowBytes) {
    return reinterpret_cast<reskia_yuva_pixmap_info_t *>(new SkYUVAPixmapInfo(*reinterpret_cast<const SkYUVAInfo *>(info), reinterpret_cast<const SkColorType *>(type), rowBytes));
}

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new_3(const reskia_yuva_info_t *info, reskia_yuva_pixmap_info_data_type_t type, const size_t *rowBytes) {
    return reinterpret_cast<reskia_yuva_pixmap_info_t *>(new SkYUVAPixmapInfo(*reinterpret_cast<const SkYUVAInfo *>(info), static_cast<SkYUVAPixmapInfo::DataType>(type), rowBytes));
}

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new_4(const reskia_yuva_pixmap_info_t *info) {
    return reinterpret_cast<reskia_yuva_pixmap_info_t *>(new SkYUVAPixmapInfo(*reinterpret_cast<const SkYUVAPixmapInfo *>(info)));
}

void SkYUVAPixmapInfo_delete(reskia_yuva_pixmap_info_t *yuvaPixmapInfo) {
    delete reinterpret_cast<SkYUVAPixmapInfo *>(yuvaPixmapInfo);
}

const reskia_yuva_info_t *SkYUVAPixmapInfo_yuvaInfo(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    return reinterpret_cast<const reskia_yuva_info_t *>(&reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->yuvaInfo());
}

reskia_yuva_pixmap_info_yuv_color_space_t SkYUVAPixmapInfo_yuvColorSpace(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    return static_cast<reskia_yuva_pixmap_info_yuv_color_space_t>(reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->yuvColorSpace());
}

int SkYUVAPixmapInfo_numPlanes(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    return reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->numPlanes();
}

reskia_yuva_pixmap_info_data_type_t SkYUVAPixmapInfo_dataType(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    return static_cast<reskia_yuva_pixmap_info_data_type_t>(reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->dataType());
}

size_t SkYUVAPixmapInfo_rowBytes(reskia_yuva_pixmap_info_t *yuva_pixmap_info, int i) {
    return reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->rowBytes(i);
}

const reskia_image_info_t *SkYUVAPixmapInfo_planeInfo(reskia_yuva_pixmap_info_t *yuva_pixmap_info, int i) {
    return reinterpret_cast<const reskia_image_info_t *>(&reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->planeInfo(i));
}

size_t SkYUVAPixmapInfo_computeTotalBytes(reskia_yuva_pixmap_info_t *yuva_pixmap_info, size_t *planeSizes) {
    return reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->computeTotalBytes(planeSizes);
}

bool SkYUVAPixmapInfo_initPixmapsFromSingleAllocation(reskia_yuva_pixmap_info_t *yuva_pixmap_info, void *memory, reskia_pixmap_t *pixmaps) {
    return reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->initPixmapsFromSingleAllocation(memory, reinterpret_cast<SkPixmap *>(pixmaps));
}

bool SkYUVAPixmapInfo_isValid(reskia_yuva_pixmap_info_t *yuva_pixmap_info) {
    return reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->isValid();
}

bool SkYUVAPixmapInfo_isSupported(reskia_yuva_pixmap_info_t *yuva_pixmap_info, const reskia_yuva_pixmap_info_supported_data_types_t *type) {
    return reinterpret_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->isSupported(*reinterpret_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(type));
}

// static

reskia_yuva_pixmap_info_color_type_t SkYUVAPixmapInfo_DefaultColorTypeForDataType(reskia_yuva_pixmap_info_data_type_t dataType, int numChannels) {
    return static_cast<reskia_yuva_pixmap_info_color_type_t>(
            SkYUVAPixmapInfo::DefaultColorTypeForDataType(static_cast<SkYUVAPixmapInfo::DataType>(dataType), numChannels));
}

tuple_int_sk_yuva_pixmap_info_data_type_t SkYUVAPixmapInfo_NumChannelsAndDataType(reskia_yuva_pixmap_info_color_type_t type) {
    return static_tuple_int_sk_yuva_pixmap_info_data_type_make(SkYUVAPixmapInfo::NumChannelsAndDataType(static_cast<SkColorType>(type)));
}

}
