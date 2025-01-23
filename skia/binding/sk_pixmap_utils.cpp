//
// Created by dolphilia on 2024/02/02.
//

#include "sk_pixmap_utils.h"

#include "include/codec/SkPixmapUtils.h"

#include "../static/static_sk_image_info.h"

#include "../static/static_sk_image_info-internal.h"

extern "C" {

bool SkPixmapUtils_Orient(const void * dst, const void * src, int origin) {
    return SkPixmapUtils::Orient(* static_cast<const SkPixmap *>(dst), * static_cast<const SkPixmap *>(src), static_cast<SkEncodedOrigin>(origin));
}

sk_image_info_t SkPixmapUtils_SwapWidthHeight(const void * info) {
    return static_sk_image_info_make(SkPixmapUtils::SwapWidthHeight(* static_cast<const SkImageInfo *>(info)));
}

}
