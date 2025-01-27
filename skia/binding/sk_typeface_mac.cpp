//
// Created by dolphilia on 2024/01/30.
//

#include "sk_typeface_mac.h"

#include "../static/static_sk_typeface.h"

#include "../static/static_sk_typeface-internal.h"

#ifdef __APPLE__
#ifdef TARGET_OS_MAC

#include "include/ports/SkTypeface_mac.h"
#include <CoreText/CoreText.h>

extern "C" {

sk_typeface_t Mac_SkMakeTypefaceFromCTFont(void * fontRef) {
    return static_sk_typeface_make(SkMakeTypefaceFromCTFont(static_cast<CTFontRef>(fontRef)));
}

const void * Mac_SkTypeface_GetCTFontRef(const void *face) {
    return SkTypeface_GetCTFontRef(static_cast<const SkTypeface *>(face));
}

}

#endif
#endif