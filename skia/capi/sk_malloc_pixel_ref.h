//
// Created by dolphilia on 2024/01/13.
//

#ifndef RAIA_SKIA_SK_MALLOC_PIXEL_REF_H
#define RAIA_SKIA_SK_MALLOC_PIXEL_REF_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_pixel_ref.h"

typedef struct reskia_image_info_t reskia_image_info_t;

sk_pixel_ref_t SkMallocPixelRef_MakeAllocate(const reskia_image_info_t *imageInfo, size_t rowBytes); // (const SkImageInfo *imageInfo, size_t rowBytes) -> sk_pixel_ref_t
sk_pixel_ref_t SkMallocPixelRef_MakeWithData(const reskia_image_info_t *imageInfo, size_t rowBytes, sk_data_t data); // (const SkImageInfo &imageInfo, size_t rowBytes, sk_data_t data) -> sk_pixel_ref_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_MALLOC_PIXEL_REF_H
