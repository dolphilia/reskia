//
// Created by dolphilia on 2024/02/02.
//

#include "sk_pixmap_utils.h"

#include "include/codec/SkPixmapUtils.h"
#include "include/codec/SkEncodedOrigin.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPixmap.h"

#include "../handles/static_sk_image_info.h"

#include "../handles/static_sk_image_info-internal.h"

namespace {

bool is_valid_encoded_origin(reskia_pixmap_utils_encoded_origin_t origin) {
    return origin > 0 && origin <= kLast_SkEncodedOrigin;
}

}

extern "C" {

bool SkPixmapUtils_Orient(const void * dst, const void * src, reskia_pixmap_utils_encoded_origin_t origin) {
    if (dst == nullptr || src == nullptr || !is_valid_encoded_origin(origin)) {
        return false;
    }
    return SkPixmapUtils::Orient(*static_cast<const SkPixmap *>(dst), *static_cast<const SkPixmap *>(src), static_cast<SkEncodedOrigin>(origin));
}

sk_image_info_t SkPixmapUtils_SwapWidthHeight(const void * info) {
    if (info == nullptr) {
        return 0;
    }
    return static_sk_image_info_make(SkPixmapUtils::SwapWidthHeight(*static_cast<const SkImageInfo *>(info)));
}

}
