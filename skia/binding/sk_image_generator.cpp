//
// Created by dolphilia on 2024/01/09.
//

#include "sk_image_generator.h"

#include "include/core/SkImageGenerator.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_image_info.h"

#include "../static/static_sk_image_info-internal.h"
#include "../static/static_sk_data-internal.h"

extern "C" {

void SkImageGenerator_delete(void *image_generator) {
    delete static_cast<SkImageGenerator *>(image_generator);
}

uint32_t SkImageGenerator_uniqueID(void *image_generator) {
    return static_cast<SkImageGenerator *>(image_generator)->uniqueID();
}

sk_data_t SkImageGenerator_refEncodedData(void *image_generator) {
    return static_sk_data_make(static_cast<SkImageGenerator *>(image_generator)->refEncodedData());
}

sk_image_info_t SkImageGenerator_getInfo(void *image_generator) {
    return static_sk_image_info_make(static_cast<SkImageGenerator *>(image_generator)->getInfo());
}

bool SkImageGenerator_isValid(void *image_generator, void *context) {
    return static_cast<SkImageGenerator *>(image_generator)->isValid(static_cast<GrRecordingContext *>(context));
}

bool SkImageGenerator_isProtected(void *image_generator) {
    return static_cast<SkImageGenerator *>(image_generator)->isProtected();
}

bool SkImageGenerator_getPixels(void *image_generator, const void *info, void *pixels, size_t rowBytes) {
    return static_cast<SkImageGenerator *>(image_generator)->getPixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes);
}

bool SkImageGenerator_getPixels_2(void *image_generator, const void *pm) {
    return static_cast<SkImageGenerator *>(image_generator)->getPixels(* static_cast<const SkPixmap *>(pm));
}

bool SkImageGenerator_queryYUVAInfo(void *image_generator, const void *supportedDataTypes, void *yuvaPixmapInfo) {
    return static_cast<SkImageGenerator *>(image_generator)->queryYUVAInfo(* static_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(supportedDataTypes), static_cast<SkYUVAPixmapInfo *>(yuvaPixmapInfo));
}

bool SkImageGenerator_getYUVAPlanes(void *image_generator, const void *yuvaPixmaps) {
    return static_cast<SkImageGenerator *>(image_generator)->getYUVAPlanes(* static_cast<const SkYUVAPixmaps *>(yuvaPixmaps));
}

bool SkImageGenerator_isTextureGenerator(void *image_generator) {
    return static_cast<SkImageGenerator *>(image_generator)->isTextureGenerator();
}

}
