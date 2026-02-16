//
// Created by dolphilia on 2024/01/09.
//

#include "sk_image_generator.h"

#include "include/core/SkImageGenerator.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_image_info.h"

#include "../handles/static_sk_image_info-internal.h"
#include "../handles/static_sk_data-internal.h"

extern "C" {

void SkImageGenerator_delete(reskia_image_generator_t *image_generator) {
    delete reinterpret_cast<SkImageGenerator *>(image_generator);
}

reskia_u32_t SkImageGenerator_uniqueID(reskia_image_generator_t *image_generator) {
    return reinterpret_cast<SkImageGenerator *>(image_generator)->uniqueID();
}

sk_data_t SkImageGenerator_refEncodedData(reskia_image_generator_t *image_generator) {
    return static_sk_data_make(reinterpret_cast<SkImageGenerator *>(image_generator)->refEncodedData());
}

sk_image_info_t SkImageGenerator_getInfo(reskia_image_generator_t *image_generator) {
    return static_sk_image_info_make(reinterpret_cast<SkImageGenerator *>(image_generator)->getInfo());
}

bool SkImageGenerator_isValid(reskia_image_generator_t *image_generator, reskia_recording_context_t *context) {
    return reinterpret_cast<SkImageGenerator *>(image_generator)->isValid(reinterpret_cast<GrRecordingContext *>(context));
}

bool SkImageGenerator_isProtected(reskia_image_generator_t *image_generator) {
    return reinterpret_cast<SkImageGenerator *>(image_generator)->isProtected();
}

bool SkImageGenerator_getPixels(reskia_image_generator_t *image_generator, const reskia_image_info_t *info, void *pixels, size_t rowBytes) {
    return reinterpret_cast<SkImageGenerator *>(image_generator)->getPixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes);
}

bool SkImageGenerator_getPixelsWithPixmap(reskia_image_generator_t *image_generator, const reskia_pixmap_t *pm) {
    return reinterpret_cast<SkImageGenerator *>(image_generator)->getPixels(* reinterpret_cast<const SkPixmap *>(pm));
}

bool SkImageGenerator_queryYUVAInfo(reskia_image_generator_t *image_generator, const reskia_supported_data_types_t *supportedDataTypes, reskia_yuva_pixmap_info_t *yuvaPixmapInfo) {
    return reinterpret_cast<SkImageGenerator *>(image_generator)->queryYUVAInfo(* reinterpret_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(supportedDataTypes), reinterpret_cast<SkYUVAPixmapInfo *>(yuvaPixmapInfo));
}

bool SkImageGenerator_getYUVAPlanes(reskia_image_generator_t *image_generator, const reskia_yuva_pixmaps_t *yuvaPixmaps) {
    return reinterpret_cast<SkImageGenerator *>(image_generator)->getYUVAPlanes(* reinterpret_cast<const SkYUVAPixmaps *>(yuvaPixmaps));
}

bool SkImageGenerator_isTextureGenerator(reskia_image_generator_t *image_generator) {
    return reinterpret_cast<SkImageGenerator *>(image_generator)->isTextureGenerator();
}

}
