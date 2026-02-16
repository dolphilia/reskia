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

extern "C" {

sk_typeface_t Mac_SkMakeTypefaceFromCTFont(const reskia_ct_font_t *fontRef) {
    return static_sk_typeface_make(SkMakeTypefaceFromCTFont(reinterpret_cast<CTFontRef>(fontRef)));
}

const reskia_ct_font_t *Mac_SkTypeface_GetCTFontRef(const reskia_typeface_t *face) {
    return reinterpret_cast<const reskia_ct_font_t *>(SkTypeface_GetCTFontRef(reinterpret_cast<const SkTypeface *>(face)));
}

}

#endif
#endif
