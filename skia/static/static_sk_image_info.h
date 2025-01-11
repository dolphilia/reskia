//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_IMAGE_INFO_H
#define RAIA_SKIA_STATIC_SK_IMAGE_INFO_H

#include <set>
#include <map>
#include <utility>
#include "include/core/SkImageInfo.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_image_info_t;
void static_sk_image_info_delete(int key);
void * static_sk_image_info_get_ptr(int key); // -> SkImageInfo *
#ifdef __cplusplus
}
#endif

int static_sk_image_info_make(SkImageInfo value);
SkImageInfo static_sk_image_info_get(int key);
void static_sk_image_info_set(int key, SkImageInfo value);

#endif //RAIA_SKIA_STATIC_SK_IMAGE_INFO_H
