//
// Created by dolphilia on 2024/01/30.
//

#include "sk_typeface_mac.h"

#include "../handles/static_sk_typeface.h"

#include "../handles/static_sk_typeface-internal.h"

#ifdef __APPLE__
#ifdef TARGET_OS_MAC

#include "include/ports/SkTypeface_mac.h"
#include <CoreText/CoreText.h>

#include <utility>

namespace {

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

}  // namespace

extern "C" {

sk_typeface_t Mac_SkMakeTypefaceFromCTFont(const reskia_ct_font_t *fontRef) {
    if (fontRef == nullptr) {
        return 0;
    }
    return make_typeface_handle(SkMakeTypefaceFromCTFont(reinterpret_cast<CTFontRef>(fontRef)));
}

const reskia_ct_font_t *Mac_SkTypeface_GetCTFontRef(const reskia_typeface_t *face) {
    if (face == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_ct_font_t *>(SkTypeface_GetCTFontRef(reinterpret_cast<const SkTypeface *>(face)));
}

}

#endif
#endif
