//
// Created by dolphilia on 2024/01/13.
//

#include "sk_malloc_pixel_ref.h"

#include "include/core/SkPixelRef.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkData.h"
#include "include/core/SkMallocPixelRef.h"

#include "../handles/static_sk_pixel_ref.h"
#include "../handles/static_sk_data.h"

#include "../handles/static_sk_pixel_ref-internal.h"
#include "../handles/static_sk_data-internal.h"

#include <utility>

namespace {

const SkImageInfo *as_image_info(const reskia_image_info_t *imageInfo) {
    return reinterpret_cast<const SkImageInfo *>(imageInfo);
}

sk_pixel_ref_t make_pixel_ref_handle(sk_sp<SkPixelRef> pixelRef) {
    if (!pixelRef) {
        return 0;
    }
    return static_sk_pixel_ref_make(std::move(pixelRef));
}

} // namespace

extern "C" {

sk_pixel_ref_t SkMallocPixelRef_MakeAllocate(const reskia_image_info_t *imageInfo, size_t rowBytes) {
    const SkImageInfo *info = as_image_info(imageInfo);
    if (info == nullptr) {
        return 0;
    }
    return make_pixel_ref_handle(SkMallocPixelRef::MakeAllocate(*info, rowBytes));
}

sk_pixel_ref_t SkMallocPixelRef_MakeWithData(const reskia_image_info_t *imageInfo, size_t rowBytes, sk_data_t data) {
    const SkImageInfo *info = as_image_info(imageInfo);
    sk_sp<SkData> pixelData = static_sk_data_get_entity(data);
    if (info == nullptr || !pixelData) {
        return 0;
    }
    return make_pixel_ref_handle(SkMallocPixelRef::MakeWithData(*info, rowBytes, std::move(pixelData)));
}

}
