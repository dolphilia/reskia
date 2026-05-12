//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_YUVA_PIXMAP_INFO_H
#define RAIA_SKIA_SK_YUVA_PIXMAP_INFO_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_yuva_info_t reskia_yuva_info_t;
typedef struct reskia_yuva_pixmap_info_supported_data_types_t reskia_yuva_pixmap_info_supported_data_types_t;
typedef struct reskia_yuva_pixmap_info_t reskia_yuva_pixmap_info_t;
typedef int32_t reskia_yuva_pixmap_info_data_type_t; // SkYUVAPixmapInfo::DataType
typedef int32_t reskia_yuva_pixmap_info_yuv_color_space_t; // SkYUVColorSpace
typedef int32_t reskia_yuva_pixmap_info_color_type_t; // SkColorType

#ifdef __cplusplus
extern "C" {
#endif

// SkYUVAPixmapInfo & operator=(const SkYUVAPixmapInfo &)
reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new(); // () -> SkYUVAPixmapInfo *
/**
 * info/type: non-null.
 * rowBytes may be null.
 * returns null on invalid input.
 */
reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_newWithInfoColorTypesAndRowBytes(const reskia_yuva_info_t *info, const int *type, const size_t *rowBytes);
/**
 * info: non-null.
 * rowBytes may be null.
 * returns null on invalid input.
 */
reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_newWithInfoDataTypeAndRowBytes(const reskia_yuva_info_t *info, reskia_yuva_pixmap_info_data_type_t type, const size_t *rowBytes);
reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_newCopy(const reskia_yuva_pixmap_info_t *info); // returns null on null info
void SkYUVAPixmapInfo_delete(reskia_yuva_pixmap_info_t *yuvaPixmapInfo); // null info is a no-op
bool SkYUVAPixmapInfo_equals(reskia_yuva_pixmap_info_t *yuva_pixmap_info, const reskia_yuva_pixmap_info_t *other); // false on null input
bool SkYUVAPixmapInfo_notEquals(reskia_yuva_pixmap_info_t *yuva_pixmap_info, const reskia_yuva_pixmap_info_t *other); // false on null input
/**
 * borrowed.
 * returns null on null input.
 */
const reskia_yuva_info_t *SkYUVAPixmapInfo_yuvaInfo(reskia_yuva_pixmap_info_t *yuva_pixmap_info);
reskia_yuva_pixmap_info_yuv_color_space_t SkYUVAPixmapInfo_yuvColorSpace(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // returns -1 on null input
int SkYUVAPixmapInfo_numPlanes(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // returns 0 on null input
reskia_yuva_pixmap_info_data_type_t SkYUVAPixmapInfo_dataType(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // returns -1 on null input
size_t SkYUVAPixmapInfo_rowBytes(reskia_yuva_pixmap_info_t *yuva_pixmap_info, int i); // returns 0 on null input or out-of-range plane index
/**
 * borrowed.
 * returns null on null input or out-of-range plane index.
 */
const reskia_image_info_t *SkYUVAPixmapInfo_planeInfo(reskia_yuva_pixmap_info_t *yuva_pixmap_info, int i);
/**
 * returns 0 on null input and clears planeSizes when provided
 */
size_t SkYUVAPixmapInfo_computeTotalBytes(reskia_yuva_pixmap_info_t *yuva_pixmap_info, size_t *planeSizes);
/**
 * info/memory/pixmaps: non-null.
 * false on invalid input.
 */
bool SkYUVAPixmapInfo_initPixmapsFromSingleAllocation(reskia_yuva_pixmap_info_t *yuva_pixmap_info, void *memory, reskia_pixmap_t *pixmaps);
bool SkYUVAPixmapInfo_isValid(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // returns false on null input
/**
 * info/type: non-null.
 * false on invalid input.
 */
bool SkYUVAPixmapInfo_isSupported(reskia_yuva_pixmap_info_t *yuva_pixmap_info, const reskia_yuva_pixmap_info_supported_data_types_t *type);

// static

reskia_yuva_pixmap_info_color_type_t SkYUVAPixmapInfo_DefaultColorTypeForDataType(reskia_yuva_pixmap_info_data_type_t dataType, int numChannels); // returns -1 on invalid dataType
int SkYUVAPixmapInfo_NumChannelsAndDataType(reskia_yuva_pixmap_info_color_type_t type); // returns handle 0 on invalid color type

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_YUVA_PIXMAP_INFO_H
