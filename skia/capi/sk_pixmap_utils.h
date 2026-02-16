//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_PIXMAP_UTILS_H
#define RAIA_SKIA_SK_PIXMAP_UTILS_H

#include <stdint.h>

#include "../handles/static_sk_image_info.h"

typedef int32_t reskia_pixmap_utils_encoded_origin_t;

#ifdef __cplusplus
extern "C" {
#endif

bool SkPixmapUtils_Orient(const void* dst, const void* src, reskia_pixmap_utils_encoded_origin_t origin); // (const SkPixmap* dst, const SkPixmap* src, SkEncodedOrigin origin) -> bool
sk_image_info_t SkPixmapUtils_SwapWidthHeight(const void* info); // (const SkImageInfo* info) -> sk_image_info_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PIXMAP_UTILS_H
