//
// Created by dolphilia on 2024/03/30.
//

#ifndef RAIA_SKIA_STATIC_SK_COLOR_4F_H
#define RAIA_SKIA_STATIC_SK_COLOR_4F_H

#include <set>
#include <map>
#include "include/core/SkColor.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_color_4f_t;
void static_sk_color_4f_delete(int key);
void * static_sk_color_4f_get_ptr(int key); // -> SkColor4f *
#ifdef __cplusplus
}
#endif

int static_sk_color_4f_make(SkColor4f value);
SkColor4f static_sk_color_4f_get(int key);
void static_sk_color_4f_set(int key, SkColor4f value);

#endif //RAIA_SKIA_STATIC_SK_COLOR_4F_H
