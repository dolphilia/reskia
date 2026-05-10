//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_IMAGE_GENERATOR_H
#define RAIA_SKIA_SK_IMAGE_GENERATOR_H

#include <stddef.h>
#include <stdint.h>
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_image_info.h"

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

void SkImageGenerator_delete(reskia_image_generator_t *image_generator); // NULL image_generator is no-op.
reskia_u32_t SkImageGenerator_uniqueID(reskia_image_generator_t *image_generator); // NULL image_generator returns 0.
sk_data_t SkImageGenerator_refEncodedData(reskia_image_generator_t *image_generator); // NULL image_generator or missing encoded data returns 0.
sk_image_info_t SkImageGenerator_getInfo(reskia_image_generator_t *image_generator); // NULL image_generator returns 0.
bool SkImageGenerator_isValid(reskia_image_generator_t *image_generator, reskia_recording_context_t *context); // context may be NULL; NULL image_generator returns false.
bool SkImageGenerator_isProtected(reskia_image_generator_t *image_generator); // NULL image_generator returns false.
bool SkImageGenerator_getPixels(reskia_image_generator_t *image_generator, const reskia_image_info_t *info, void *pixels, size_t rowBytes); // image_generator/info/pixels are required.
bool SkImageGenerator_getPixelsWithPixmap(reskia_image_generator_t *image_generator, const reskia_pixmap_t *pm); // image_generator/pm are required.
bool SkImageGenerator_queryYUVAInfo(reskia_image_generator_t *image_generator, const reskia_supported_data_types_t *supportedDataTypes, reskia_yuva_pixmap_info_t *yuvaPixmapInfo); // image_generator/supportedDataTypes/yuvaPixmapInfo are required.
bool SkImageGenerator_getYUVAPlanes(reskia_image_generator_t *image_generator, const reskia_yuva_pixmaps_t *yuvaPixmaps); // image_generator/yuvaPixmaps are required.
bool SkImageGenerator_isTextureGenerator(reskia_image_generator_t *image_generator); // NULL image_generator returns false.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_GENERATOR_H
