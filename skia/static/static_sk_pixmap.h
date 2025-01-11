//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_PIXMAP_H
#define RAIA_SKIA_STATIC_SK_PIXMAP_H

#include <set>
#include <map>
#include "include/core/SkPixmap.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_pixmap_t;
void static_sk_pixmap_delete(int key);
void * static_sk_pixmap_get_ptr(int key); // -> SkPixmap *
#ifdef __cplusplus
}
#endif

int static_sk_pixmap_make(SkPixmap value);
SkPixmap static_sk_pixmap_get(int key) ;
void static_sk_pixmap_set(int key, SkPixmap value);

#endif //RAIA_SKIA_STATIC_SK_PIXMAP_H
