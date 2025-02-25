//
// Created by dolphilia on 2024/01/11.
//

#include "sk_yuva_pixmaps.h"

#include "include/core/SkYUVAPixmaps.h"

#include "../static/static_sk_yuva_pixmap_info.h"
#include "../static/static_sk_yuva_pixmaps.h"
#include "../static/static_sk_data.h"

#include "../static/static_sk_yuva_pixmaps-internal.h"
#include "../static/static_sk_yuva_pixmap_info-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

// SkYUVAPixmaps & operator=(SkYUVAPixmaps &&that)
// SkYUVAPixmaps & operator=(const SkYUVAPixmaps &that)

void *SkYUVAPixmaps_new() {
    return new SkYUVAPixmaps();
}

void *SkYUVAPixmaps_new_2(const void *pixmaps) {
    return new SkYUVAPixmaps(* static_cast<const SkYUVAPixmaps *>(pixmaps));
}

void SkYUVAPixmaps_delete(void *yuva_pixmaps) {
    delete static_cast<SkYUVAPixmaps *>(yuva_pixmaps);
}

bool SkYUVAPixmaps_isValid(void *yuva_pixmaps) {
    return static_cast<SkYUVAPixmaps *>(yuva_pixmaps)->isValid();
}

const void * SkYUVAPixmaps_yuvaInfo(void *yuva_pixmaps) {
    return &static_cast<SkYUVAPixmaps *>(yuva_pixmaps)->yuvaInfo();
}

int SkYUVAPixmaps_dataType(void *yuva_pixmaps) {
    return static_cast<int>(static_cast<SkYUVAPixmaps *>(yuva_pixmaps)->dataType());
}

sk_yuva_pixmap_info_t SkYUVAPixmaps_pixmapsInfo(void *yuva_pixmaps) {
    return static_sk_yuva_pixmap_info_make(static_cast<SkYUVAPixmaps *>(yuva_pixmaps)->pixmapsInfo());
}

int SkYUVAPixmaps_numPlanes(void *yuva_pixmaps) {
    return static_cast<SkYUVAPixmaps *>(yuva_pixmaps)->numPlanes();
}

const void * SkYUVAPixmaps_planes(void *yuva_pixmaps) {
    return &static_cast<SkYUVAPixmaps *>(yuva_pixmaps)->planes();
}

const void * SkYUVAPixmaps_plane(void *yuva_pixmaps, int i) {
    return &static_cast<SkYUVAPixmaps *>(yuva_pixmaps)->plane(i);
}

//SkYUVAInfo::YUVALocations SkYUVAPixmaps_toYUVALocations(SkYUVAPixmaps *yuva_pixmaps) {
//    return yuva_pixmaps->toYUVALocations();
//}

bool SkYUVAPixmaps_ownsStorage(void *yuva_pixmaps) {
    return static_cast<SkYUVAPixmaps *>(yuva_pixmaps)->ownsStorage();
}

// static

int SkYUVAPixmaps_RecommendedRGBAColorType(int type) {
    return SkYUVAPixmaps::RecommendedRGBAColorType(static_cast<SkYUVAPixmaps::DataType>(type));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_Allocate(const void *yuvaPixmapInfo) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::Allocate(* static_cast<const SkYUVAPixmapInfo *>(yuvaPixmapInfo)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromData(const void *yuvaPixmapInfo, sk_data_t data) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::FromData(* static_cast<const SkYUVAPixmapInfo *>(yuvaPixmapInfo), static_sk_data_get_entity(data)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_MakeCopy(const void *src) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::MakeCopy(* static_cast<const SkYUVAPixmaps *>(src)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalMemory(const void *yuvaPixmapInfo, void *memory) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::FromExternalMemory(* static_cast<const SkYUVAPixmapInfo *>(yuvaPixmapInfo), memory));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalPixmaps(const void *yuvaInfo, const void * pixmaps) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::FromExternalPixmaps(* static_cast<const SkYUVAInfo *>(yuvaInfo), static_cast<const SkPixmap *>(pixmaps)));
}

}
