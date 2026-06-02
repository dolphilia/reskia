//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_YUVA_PIXMAPS_H
#define RAIA_SKIA_SK_YUVA_PIXMAPS_H

#include <stdint.h>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_yuva_pixmap_info.h"
#include "../handles/static_sk_yuva_pixmaps.h"
#include "sk_yuva_info.h"

typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_yuva_info_t reskia_yuva_info_t;
typedef struct reskia_yuva_pixmap_info_t reskia_yuva_pixmap_info_t;
typedef struct reskia_yuva_pixmaps_t reskia_yuva_pixmaps_t;
typedef int32_t reskia_yuva_pixmaps_data_type_t; // SkYUVAPixmaps::DataType
typedef int32_t reskia_yuva_pixmaps_color_type_t; // SkColorType

#ifdef __cplusplus
extern "C" {
#endif


reskia_yuva_pixmaps_t *SkYUVAPixmaps_new(); // () -> SkYUVAPixmaps *
reskia_yuva_pixmaps_t *SkYUVAPixmaps_newCopy(const reskia_yuva_pixmaps_t *pixmaps); // returns null on null pixmaps
void SkYUVAPixmaps_delete(reskia_yuva_pixmaps_t *yuva_pixmaps); // null pixmaps is a no-op
bool SkYUVAPixmaps_isValid(reskia_yuva_pixmaps_t *yuva_pixmaps); // returns false on null pixmaps
/**
 * borrowed.
 * returns null on null pixmaps.
 */
const reskia_yuva_info_t *SkYUVAPixmaps_yuvaInfo(reskia_yuva_pixmaps_t *yuva_pixmaps);
reskia_yuva_pixmaps_data_type_t SkYUVAPixmaps_dataType(reskia_yuva_pixmaps_t *yuva_pixmaps); // returns -1 on null or invalid pixmaps
sk_yuva_pixmap_info_t SkYUVAPixmaps_pixmapsInfo(reskia_yuva_pixmaps_t *yuva_pixmaps); // returns handle 0 on null or invalid pixmaps
int SkYUVAPixmaps_numPlanes(reskia_yuva_pixmaps_t *yuva_pixmaps); // returns 0 on null pixmaps
/**
 * borrowed array.
 * returns null on null pixmaps.
 */
const reskia_pixmap_t *SkYUVAPixmaps_planes(reskia_yuva_pixmaps_t *yuva_pixmaps);
/**
 * borrowed.
 * returns null on null pixmaps or out-of-range plane index.
 */
const reskia_pixmap_t *SkYUVAPixmaps_plane(reskia_yuva_pixmaps_t *yuva_pixmaps, int i);
bool SkYUVAPixmaps_toYUVALocations(reskia_yuva_pixmaps_t *yuva_pixmaps, reskia_yuva_location_t *locations); // locations[4]. invalid input clears locations and returns false
bool SkYUVAPixmaps_ownsStorage(reskia_yuva_pixmaps_t *yuva_pixmaps); // returns false on null pixmaps

// static

reskia_yuva_pixmaps_color_type_t SkYUVAPixmaps_RecommendedRGBAColorType(reskia_yuva_pixmaps_data_type_t type); // returns -1 on invalid data type
sk_yuva_pixmaps_t SkYUVAPixmaps_Allocate(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo); // returns handle 0 on null input or invalid result
/**
 * data handle must be valid.
 * returns 0 on invalid input or result.
 */
sk_yuva_pixmaps_t SkYUVAPixmaps_FromData(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo, sk_data_t data);
/**
 * src must be valid.
 * returns 0 on invalid input or result.
 */
sk_yuva_pixmaps_t SkYUVAPixmaps_MakeCopy(const reskia_yuva_pixmaps_t *src);
/**
 * memory must be non-null.
 * returns 0 on invalid input or result.
 */
sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalMemory(const reskia_yuva_pixmap_info_t *yuvaPixmapInfo, void *memory);
/**
 * yuvaInfo/pixmaps: non-null.
 * returns 0 on invalid input or result.
 */
sk_yuva_pixmaps_t SkYUVAPixmaps_FromExternalPixmaps(const reskia_yuva_info_t *yuvaInfo, const reskia_pixmap_t *pixmaps);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_YUVA_PIXMAPS_H
