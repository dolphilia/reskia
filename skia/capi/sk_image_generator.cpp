//
// Created by dolphilia on 2024/01/09.
//

#include "sk_image_generator.h"

#include "include/core/SkImageGenerator.h"

#include <utility>

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_image_info.h"

#include "../handles/static_sk_image_info-internal.h"
#include "../handles/static_sk_data-internal.h"

namespace {

SkImageGenerator *as_image_generator(reskia_image_generator_t *image_generator) {
    return reinterpret_cast<SkImageGenerator *>(image_generator);
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

} // namespace

extern "C" {

void SkImageGenerator_delete(reskia_image_generator_t *image_generator) {
    delete as_image_generator(image_generator);
}

reskia_u32_t SkImageGenerator_uniqueID(reskia_image_generator_t *image_generator) {
    SkImageGenerator *native = as_image_generator(image_generator);
    return native != nullptr ? native->uniqueID() : 0;
}

sk_data_t SkImageGenerator_refEncodedData(reskia_image_generator_t *image_generator) {
    SkImageGenerator *native = as_image_generator(image_generator);
    return native != nullptr ? make_data_handle(native->refEncodedData()) : 0;
}

sk_image_info_t SkImageGenerator_getInfo(reskia_image_generator_t *image_generator) {
    SkImageGenerator *native = as_image_generator(image_generator);
    return native != nullptr ? static_sk_image_info_make(native->getInfo()) : 0;
}

bool SkImageGenerator_isValid(reskia_image_generator_t *image_generator, reskia_recording_context_t *context) {
    SkImageGenerator *native = as_image_generator(image_generator);
    return native != nullptr ? native->isValid(reinterpret_cast<GrRecordingContext *>(context)) : false;
}

bool SkImageGenerator_isProtected(reskia_image_generator_t *image_generator) {
    SkImageGenerator *native = as_image_generator(image_generator);
    return native != nullptr ? native->isProtected() : false;
}

bool SkImageGenerator_getPixels(reskia_image_generator_t *image_generator, const reskia_image_info_t *info, void *pixels, size_t rowBytes) {
    SkImageGenerator *native = as_image_generator(image_generator);
    if (native == nullptr || info == nullptr || pixels == nullptr) {
        return false;
    }
    return native->getPixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes);
}

bool SkImageGenerator_getPixelsWithPixmap(reskia_image_generator_t *image_generator, const reskia_pixmap_t *pm) {
    SkImageGenerator *native = as_image_generator(image_generator);
    if (native == nullptr || pm == nullptr) {
        return false;
    }
    return native->getPixels(* reinterpret_cast<const SkPixmap *>(pm));
}

bool SkImageGenerator_queryYUVAInfo(reskia_image_generator_t *image_generator, const reskia_supported_data_types_t *supportedDataTypes, reskia_yuva_pixmap_info_t *yuvaPixmapInfo) {
    SkImageGenerator *native = as_image_generator(image_generator);
    if (native == nullptr || supportedDataTypes == nullptr || yuvaPixmapInfo == nullptr) {
        return false;
    }
    return native->queryYUVAInfo(* reinterpret_cast<const SkYUVAPixmapInfo::SupportedDataTypes *>(supportedDataTypes), reinterpret_cast<SkYUVAPixmapInfo *>(yuvaPixmapInfo));
}

bool SkImageGenerator_getYUVAPlanes(reskia_image_generator_t *image_generator, const reskia_yuva_pixmaps_t *yuvaPixmaps) {
    SkImageGenerator *native = as_image_generator(image_generator);
    if (native == nullptr || yuvaPixmaps == nullptr) {
        return false;
    }
    return native->getYUVAPlanes(* reinterpret_cast<const SkYUVAPixmaps *>(yuvaPixmaps));
}

bool SkImageGenerator_isTextureGenerator(reskia_image_generator_t *image_generator) {
    SkImageGenerator *native = as_image_generator(image_generator);
    return native != nullptr ? native->isTextureGenerator() : false;
}

}
