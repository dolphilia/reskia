//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_TYPEFACE_H
#define RAIA_SKIA_STATIC_SK_TYPEFACE_H

#include <set>
#include <string>
#include <map>
#include "include/core/SkTypeface.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_typeface_t;
void static_sk_typeface_delete(int key);
SkTypeface *static_sk_typeface_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_typeface_make(sk_sp<SkTypeface> value);
void static_sk_typeface_set(int key, sk_sp<SkTypeface> value);
sk_sp<SkTypeface> static_sk_typeface_move(int key);

#endif //RAIA_SKIA_STATIC_SK_TYPEFACE_H
