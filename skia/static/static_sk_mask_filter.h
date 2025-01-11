//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_MASK_FILTER_H
#define RAIA_SKIA_STATIC_SK_MASK_FILTER_H

#include <set>
#include <string>
#include <map>
#include "include/core/SkMaskFilter.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_mask_filter_t;
void static_sk_mask_filter_delete(int key);
SkMaskFilter *static_sk_mask_filter_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_mask_filter_make(sk_sp<SkMaskFilter> value);
void static_sk_mask_filter_set(int key, sk_sp<SkMaskFilter> value);
sk_sp<SkMaskFilter> static_sk_mask_filter_move(int key);

#endif //RAIA_SKIA_STATIC_SK_MASK_FILTER_H
