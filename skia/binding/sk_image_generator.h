//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_IMAGE_GENERATOR_H
#define RAIA_SKIA_SK_IMAGE_GENERATOR_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_data.h"
#include "../static/static_sk_image_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_image_generator_t reskia_image_generator_t;
typedef struct reskia_recording_context_t reskia_recording_context_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_supported_data_types_t reskia_supported_data_types_t;
typedef struct reskia_yuva_pixmap_info_t reskia_yuva_pixmap_info_t;
typedef struct reskia_yuva_pixmaps_t reskia_yuva_pixmaps_t;
typedef uint32_t reskia_u32_t;

void SkImageGenerator_delete(reskia_image_generator_t *image_generator); // (SkImageGenerator *image_generator)
reskia_u32_t SkImageGenerator_uniqueID(reskia_image_generator_t *image_generator); // (SkImageGenerator *image_generator) -> uint32_t
sk_data_t SkImageGenerator_refEncodedData(reskia_image_generator_t *image_generator); // (SkImageGenerator *image_generator) -> sk_data_t
sk_image_info_t SkImageGenerator_getInfo(reskia_image_generator_t *image_generator); // (SkImageGenerator *image_generator) -> sk_image_info_t
bool SkImageGenerator_isValid(reskia_image_generator_t *image_generator, reskia_recording_context_t *context); // (SkImageGenerator *image_generator, GrRecordingContext *context) -> bool
bool SkImageGenerator_isProtected(reskia_image_generator_t *image_generator); // (SkImageGenerator *image_generator) -> bool
bool SkImageGenerator_getPixels(reskia_image_generator_t *image_generator, const reskia_image_info_t *info, void *pixels, size_t rowBytes); // (SkImageGenerator *image_generator, const SkImageInfo *info, void *pixels, size_t rowBytes) -> bool
bool SkImageGenerator_getPixels_2(reskia_image_generator_t *image_generator, const reskia_pixmap_t *pm); // (SkImageGenerator *image_generator, const SkPixmap *pm) -> bool
bool SkImageGenerator_queryYUVAInfo(reskia_image_generator_t *image_generator, const reskia_supported_data_types_t *supportedDataTypes, reskia_yuva_pixmap_info_t *yuvaPixmapInfo); // (SkImageGenerator *image_generator, const SkYUVAPixmapInfo::SupportedDataTypes *supportedDataTypes, SkYUVAPixmapInfo *yuvaPixmapInfo) -> bool
bool SkImageGenerator_getYUVAPlanes(reskia_image_generator_t *image_generator, const reskia_yuva_pixmaps_t *yuvaPixmaps); // (SkImageGenerator *image_generator, const SkYUVAPixmaps *yuvaPixmaps) -> bool
bool SkImageGenerator_isTextureGenerator(reskia_image_generator_t *image_generator); // (SkImageGenerator *image_generator) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_GENERATOR_H
