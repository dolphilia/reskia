//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_YUVA_PIXMAP_INFO_H
#define RAIA_SKIA_SK_YUVA_PIXMAP_INFO_H

#include <stddef.h>

typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_yuva_info_t reskia_yuva_info_t;
typedef struct reskia_yuva_pixmap_info_supported_data_types_t reskia_yuva_pixmap_info_supported_data_types_t;
typedef struct reskia_yuva_pixmap_info_t reskia_yuva_pixmap_info_t;

#ifdef __cplusplus
extern "C" {
#endif

// SkYUVAPixmapInfo & operator=(const SkYUVAPixmapInfo &)
// bool operator==(const SkYUVAPixmapInfo &)
// bool operator!=(const SkYUVAPixmapInfo &that)

reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new(); // () -> SkYUVAPixmapInfo *
reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new_2(const reskia_yuva_info_t *info, const int *type, const size_t *rowBytes); // (const SkYUVAInfo *info, const SkColorType type[4], const size_t rowBytes[4]) -> SkYUVAPixmapInfo *
reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new_3(const reskia_yuva_info_t *info, int type, const size_t *rowBytes); // (const SkYUVAInfo *info, SkYUVAPixmapInfo::DataType type, const size_t rowBytes[4]) -> SkYUVAPixmapInfo *
reskia_yuva_pixmap_info_t *SkYUVAPixmapInfo_new_4(const reskia_yuva_pixmap_info_t *info); // (const SkYUVAPixmapInfo *info) -> SkYUVAPixmapInfo *
void SkYUVAPixmapInfo_delete(reskia_yuva_pixmap_info_t *yuvaPixmapInfo); // (SkYUVAPixmapInfo *yuvaPixmapInfo)
const reskia_yuva_info_t *SkYUVAPixmapInfo_yuvaInfo(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // (SkYUVAPixmapInfo *yuva_pixmap_info) -> const SkYUVAInfo *
int SkYUVAPixmapInfo_yuvColorSpace(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // (SkYUVAPixmapInfo *yuva_pixmap_info) -> SkYUVColorSpace
int SkYUVAPixmapInfo_numPlanes(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // (SkYUVAPixmapInfo *yuva_pixmap_info) -> int
int SkYUVAPixmapInfo_dataType(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // (SkYUVAPixmapInfo *yuva_pixmap_info) -> SkYUVAPixmapInfo::DataType
size_t SkYUVAPixmapInfo_rowBytes(reskia_yuva_pixmap_info_t *yuva_pixmap_info, int i); // (SkYUVAPixmapInfo *yuva_pixmap_info, int i) -> size_t
const reskia_image_info_t *SkYUVAPixmapInfo_planeInfo(reskia_yuva_pixmap_info_t *yuva_pixmap_info, int i); // (SkYUVAPixmapInfo *yuva_pixmap_info, int i) -> const SkImageInfo *
size_t SkYUVAPixmapInfo_computeTotalBytes(reskia_yuva_pixmap_info_t *yuva_pixmap_info, size_t *planeSizes); // (SkYUVAPixmapInfo *yuva_pixmap_info, size_t planeSizes[SkYUVAPixmapInfo::kMaxPlanes]) -> size_t
bool SkYUVAPixmapInfo_initPixmapsFromSingleAllocation(reskia_yuva_pixmap_info_t *yuva_pixmap_info, void *memory, reskia_pixmap_t *pixmaps); // (SkYUVAPixmapInfo *yuva_pixmap_info, void *memory, SkPixmap pixmaps[SkYUVAPixmapInfo::kMaxPlanes]) -> bool
bool SkYUVAPixmapInfo_isValid(reskia_yuva_pixmap_info_t *yuva_pixmap_info); // (SkYUVAPixmapInfo *yuva_pixmap_info) -> bool
bool SkYUVAPixmapInfo_isSupported(reskia_yuva_pixmap_info_t *yuva_pixmap_info, const reskia_yuva_pixmap_info_supported_data_types_t *type); // (SkYUVAPixmapInfo *yuva_pixmap_info, const SkYUVAPixmapInfo::SupportedDataTypes *type) -> bool

// static

int SkYUVAPixmapInfo_DefaultColorTypeForDataType(int dataType, int numChannels); // (SkYUVAPixmapInfo::DataType dataType, int numChannels) -> SkColorType
int SkYUVAPixmapInfo_NumChannelsAndDataType(int type); // (SkColorType type) -> tuple_int_sk_yuva_pixmap_info_data_type_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_YUVA_PIXMAP_INFO_H
