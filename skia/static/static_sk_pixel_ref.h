//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_PIXEL_REF_H
#define RAIA_SKIA_STATIC_SK_PIXEL_REF_H

#include <set>
#include <map>
#include "include/core/SkPixelRef.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_pixel_ref_t;
void static_sk_pixel_ref_delete(int key);
void *static_sk_pixel_ref_get(int key); // -> SkPixelRef *
#ifdef __cplusplus
}
#endif

int static_sk_pixel_ref_make(sk_sp<SkPixelRef> value);
void static_sk_pixel_ref_set(int key, sk_sp<SkPixelRef> value);
sk_sp<SkPixelRef> static_sk_pixel_ref_move(int key);

#endif //RAIA_SKIA_STATIC_SK_PIXEL_REF_H
