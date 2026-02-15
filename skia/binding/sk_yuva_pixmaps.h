//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_YUVA_PIXMAPS_H
#define RAIA_SKIA_SK_YUVA_PIXMAPS_H

#include <stdint.h>

#include "../static/static_sk_data.h"
#include "../static/static_sk_yuva_pixmap_info.h"
#include "../static/static_sk_yuva_pixmaps.h"

typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_yuva_info_t reskia_yuva_info_t;
typedef struct reskia_yuva_pixmap_info_t reskia_yuva_pixmap_info_t;
typedef struct reskia_yuva_pixmaps_t reskia_yuva_pixmaps_t;
typedef int32_t reskia_yuva_pixmaps_data_type_t; // SkYUVAPixmaps::DataType
typedef int32_t reskia_yuva_pixmaps_color_type_t; // SkColorType

#ifdef __cplusplus
extern "C" {
#endif

// SkYUVAPixmaps & operator=(SkYUVAPixmaps &&that)
// SkYUVAPixmaps & operator=(const SkYUVAPixmaps &that)

reskia_yuva_pixmaps_t *SkYUVAPixmaps_new(); // () -> SkYUVAPixmaps *
reskia_yuva_pixmaps_t *SkYUVAPixmaps_new_2(const reskia_yuva_pixmaps_t *pixmaps); // (const SkYUVAPixmaps *pixmaps) -> SkYUVAPixmaps *
void SkYUVAPixmaps_delete(reskia_yuva_pixmaps_t *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps)
bool SkYUVAPixmaps_isValid(reskia_yuva_pixmaps_t *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps) -> bool
const reskia_yuva_info_t *SkYUVAPixmaps_yuvaInfo(reskia_yuva_pixmaps_t *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps) -> const SkYUVAInfo *
reskia_yuva_pixmaps_data_type_t SkYUVAPixmaps_dataType(reskia_yuva_pixmaps_t *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps) -> SkYUVAPixmaps::DataType
sk_yuva_pixmap_info_t SkYUVAPixmaps_pixmapsInfo(reskia_yuva_pixmaps_t *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps) -> sk_yuva_pixmap_info_t
int SkYUVAPixmaps_numPlanes(reskia_yuva_pixmaps_t *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps) -> int
const reskia_pixmap_t *SkYUVAPixmaps_planes(reskia_yuva_pixmaps_t *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps) -> const SkPixmap *
const reskia_pixmap_t *SkYUVAPixmaps_plane(reskia_yuva_pixmaps_t *yuva_pixmaps, int i); // (SkYUVAPixmaps *yuva_pixmaps, int i) -> const SkPixmap *
// SkYUVAInfo::YUVALocations SkYUVAPixmaps_toYUVALocations(SkYUVAPixmaps *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps) -> SkYUVAInfo::YUVALocations
bool SkYUVAPixmaps_ownsStorage(reskia_yuva_pixmaps_t *yuva_pixmaps); // (SkYUVAPixmaps *yuva_pixmaps) -> bool

// static

reskia_yuva_pixmaps_color_type_t SkYUVAPixmaps_RecommendedRGBAColorType(reskia_yuva_pixmaps_data_type_t type); // (SkYUVAPixmaps::DataType type) -> SkColorType
sk_yuva_pixmaps_t SkYUVAPixmaps_Allocate(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo); // (const SkYUVAPixmapInfo *yuvaPixmapInfo) -> sk_yuva_pixmaps_t
sk_yuva_pixmaps_t SkYUVAPixmaps_FromData(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo, sk_data_t data); // (const SkYUVAPixmapInfo *yuvaPixmapInfo, sk_data_t data) -> sk_yuva_pixmaps_t
sk_yuva_pixmaps_t SkYUVAPixmaps_MakeCopy(const reskia_yuva_pixmaps_t *src); // (const SkYUVAPixmaps *src) -> sk_yuva_pixmaps_t
sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalMemory(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo, void *memory); // (const SkYUVAPixmapInfo *yuvaPixmapInfo, void *memory) -> sk_yuva_pixmaps_t
sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalPixmaps(const reskia_yuva_info_t *yuvaInfo, const reskia_pixmap_t *pixmaps); // (const SkYUVAInfo *yuvaInfo, const SkPixmap pixmaps[4]) -> sk_yuva_pixmaps_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_YUVA_PIXMAPS_H
