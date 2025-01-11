//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_YUVA_PIXMAPS_H
#define RAIA_SKIA_STATIC_SK_YUVA_PIXMAPS_H

#include <set>
#include <map>
#include "include/core/SkYUVAPixmaps.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_yuva_pixmaps_t;
void static_sk_yuva_pixmaps_delete(int key);
SkYUVAPixmaps * static_sk_yuva_pixmaps_get_ptr(int key);
#ifdef __cplusplus
}
#endif

int static_sk_yuva_pixmaps_make(SkYUVAPixmaps value);
SkYUVAPixmaps static_sk_yuva_pixmaps_get(int key);
void static_sk_yuva_pixmaps_set(int key, SkYUVAPixmaps value);

#endif //RAIA_SKIA_STATIC_SK_YUVA_PIXMAPS_H
