//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_COLOR_FILTER_H
#define RAIA_SKIA_STATIC_SK_COLOR_FILTER_H

#include <set>
#include <string>
#include <map>
#include "include/core/SkColorFilter.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_color_filter_t;
void static_sk_color_filter_delete(int key);
SkColorFilter *static_sk_color_filter_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_color_filter_make(sk_sp<SkColorFilter> value);
void static_sk_color_filter_set(int key, sk_sp<SkColorFilter> value);
sk_sp<SkColorFilter> static_sk_color_filter_move(int key);

#endif //RAIA_SKIA_STATIC_SK_COLOR_FILTER_H
