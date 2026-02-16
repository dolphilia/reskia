//
// Created by dolphilia on 2024/01/11.
//

#include "sk_yuva_pixmaps.h"

#include "include/core/SkYUVAPixmaps.h"

#include "../handles/static_sk_yuva_pixmap_info.h"
#include "../handles/static_sk_yuva_pixmaps.h"
#include "../handles/static_sk_data.h"

#include "../handles/static_sk_yuva_pixmaps-internal.h"
#include "../handles/static_sk_yuva_pixmap_info-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

// SkYUVAPixmaps & operator=(SkYUVAPixmaps &&that)
// SkYUVAPixmaps & operator=(const SkYUVAPixmaps &that)

reskia_yuva_pixmaps_t *SkYUVAPixmaps_new() {
    return reinterpret_cast<reskia_yuva_pixmaps_t *>(new SkYUVAPixmaps());
}

reskia_yuva_pixmaps_t *SkYUVAPixmaps_newCopy(const reskia_yuva_pixmaps_t *pixmaps) {
    return reinterpret_cast<reskia_yuva_pixmaps_t *>(new SkYUVAPixmaps(*reinterpret_cast<const SkYUVAPixmaps *>(pixmaps)));
}

void SkYUVAPixmaps_delete(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    delete reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps);
}

bool SkYUVAPixmaps_isValid(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    return reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps)->isValid();
}

const reskia_yuva_info_t *SkYUVAPixmaps_yuvaInfo(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    return reinterpret_cast<const reskia_yuva_info_t *>(&reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps)->yuvaInfo());
}

reskia_yuva_pixmaps_data_type_t SkYUVAPixmaps_dataType(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    return static_cast<reskia_yuva_pixmaps_data_type_t>(reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps)->dataType());
}

sk_yuva_pixmap_info_t SkYUVAPixmaps_pixmapsInfo(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    return static_sk_yuva_pixmap_info_make(reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps)->pixmapsInfo());
}

int SkYUVAPixmaps_numPlanes(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    return reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps)->numPlanes();
}

const reskia_pixmap_t *SkYUVAPixmaps_planes(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    return reinterpret_cast<const reskia_pixmap_t *>(reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps)->planes().data());
}

const reskia_pixmap_t *SkYUVAPixmaps_plane(reskia_yuva_pixmaps_t *yuva_pixmaps, int i) {
    return reinterpret_cast<const reskia_pixmap_t *>(&reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps)->plane(i));
}

//SkYUVAInfo::YUVALocations SkYUVAPixmaps_toYUVALocations(SkYUVAPixmaps *yuva_pixmaps) {
//    return yuva_pixmaps->toYUVALocations();
//}

bool SkYUVAPixmaps_ownsStorage(reskia_yuva_pixmaps_t *yuva_pixmaps) {
    return reinterpret_cast<SkYUVAPixmaps *>(yuva_pixmaps)->ownsStorage();
}

// static

reskia_yuva_pixmaps_color_type_t SkYUVAPixmaps_RecommendedRGBAColorType(reskia_yuva_pixmaps_data_type_t type) {
    return static_cast<reskia_yuva_pixmaps_color_type_t>(
            SkYUVAPixmaps::RecommendedRGBAColorType(static_cast<SkYUVAPixmaps::DataType>(type)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_Allocate(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::Allocate(*reinterpret_cast<const SkYUVAPixmapInfo *>(yuvaPixmapInfo)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromData(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo, sk_data_t data) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::FromData(*reinterpret_cast<const SkYUVAPixmapInfo *>(yuvaPixmapInfo), static_sk_data_get_entity(data)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_MakeCopy(const reskia_yuva_pixmaps_t *src) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::MakeCopy(*reinterpret_cast<const SkYUVAPixmaps *>(src)));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalMemory(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo, void *memory) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::FromExternalMemory(*reinterpret_cast<const SkYUVAPixmapInfo *>(yuvaPixmapInfo), memory));
}

sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalPixmaps(const reskia_yuva_info_t *yuvaInfo, const reskia_pixmap_t *pixmaps) {
    return static_sk_yuva_pixmaps_make(SkYUVAPixmaps::FromExternalPixmaps(*reinterpret_cast<const SkYUVAInfo *>(yuvaInfo), reinterpret_cast<const SkPixmap *>(pixmaps)));
}

}
