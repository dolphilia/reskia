//
// Created by dolphilia on 2024/01/30.
//

#ifndef RAIA_SKIA_SK_TYPEFACE_MAC_H
#define RAIA_SKIA_SK_TYPEFACE_MAC_H

#ifdef __APPLE__
#ifdef TARGET_OS_MAC

#include "../handles/static_sk_typeface.h"

typedef struct reskia_ct_font_t reskia_ct_font_t;
typedef struct reskia_typeface_t reskia_typeface_t;

#ifdef __cplusplus
extern "C" {
#endif

sk_typeface_t Mac_SkMakeTypefaceFromCTFont(const reskia_ct_font_t *fontRef); // (CTFontRef fontRef) -> sk_typeface_t
const reskia_ct_font_t *Mac_SkTypeface_GetCTFontRef(const reskia_typeface_t *face); // (const SkTypeface *face) -> CTFontRef

#ifdef __cplusplus
}
#endif

#endif
#endif

#endif //RAIA_SKIA_SK_TYPEFACE_MAC_H
