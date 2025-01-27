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

void *SkYUVAPixmapInfo_new() {
    return new SkYUVAPixmapInfo();
}

void *SkYUVAPixmapInfo_new_2(const void *info, const void * type, const void * rowBytes) {
    return new SkYUVAPixmapInfo(* static_cast<const SkYUVAInfo *>(info), static_cast<const SkColorType *>(type), static_cast<const size_t *>(rowBytes));
}

void *SkYUVAPixmapInfo_new_3(const void *info, int type, const void * rowBytes) {
    return new SkYUVAPixmapInfo(* static_cast<const SkYUVAInfo *>(info), static_cast<SkYUVAPixmapInfo::DataType>(type), static_cast<const size_t *>(rowBytes));
}

void *SkYUVAPixmapInfo_new_4(const void *info) {
    return new SkYUVAPixmapInfo(* static_cast<const SkYUVAPixmapInfo *>(info));
}

void SkYUVAPixmapInfo_delete(void *yuvaPixmapInfo) {
    delete static_cast<SkYUVAPixmapInfo *>(yuvaPixmapInfo);
}

const void * SkYUVAPixmapInfo_yuvaInfo(void *yuva_pixmap_info) {
    return &static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->yuvaInfo();
}

int SkYUVAPixmapInfo_yuvColorSpace(void *yuva_pixmap_info) {
    return static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->yuvColorSpace();
}

int SkYUVAPixmapInfo_numPlanes(void *yuva_pixmap_info) {
    return static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->numPlanes();
}

int SkYUVAPixmapInfo_dataType(void *yuva_pixmap_info) {
    return static_cast<int>(static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->dataType());
}

size_t SkYUVAPixmapInfo_rowBytes(void *yuva_pixmap_info, int i) {
    return static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->rowBytes(i);
}

const void * SkYUVAPixmapInfo_planeInfo(void *yuva_pixmap_info, int i) {
    return &static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->planeInfo(i);
}

size_t SkYUVAPixmapInfo_computeTotalBytes(void *yuva_pixmap_info, void * planeSizes) {
    return static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->computeTotalBytes(static_cast<size_t *>(planeSizes));
}

bool SkYUVAPixmapInfo_initPixmapsFromSingleAllocation(void *yuva_pixmap_info, void *memory, void * pixmaps) {
    return static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->initPixmapsFromSingleAllocation(memory, static_cast<SkPixmap *>(pixmaps));
}

bool SkYUVAPixmapInfo_isValid(void *yuva_pixmap_info) {
    return static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->isValid();
}

bool SkYUVAPixmapInfo_isSupported(void *yuva_pixmap_info, const void *type) {
    return static_cast<SkYUVAPixmapInfo *>(yuva_pixmap_info)->isSupported(* static_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(type));
}

// static

int SkYUVAPixmapInfo_DefaultColorTypeForDataType(int dataType, int numChannels) {
    return SkYUVAPixmapInfo::DefaultColorTypeForDataType(static_cast<SkYUVAPixmapInfo::DataType>(dataType), numChannels);
}

tuple_int_sk_yuva_pixmap_info_data_type_t SkYUVAPixmapInfo_NumChannelsAndDataType(int type) {
    return static_tuple_int_sk_yuva_pixmap_info_data_type_make(SkYUVAPixmapInfo::NumChannelsAndDataType(static_cast<SkColorType>(type)));
}

}
