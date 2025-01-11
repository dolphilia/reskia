//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_YUVA_INFO_H
#define RAIA_SKIA_STATIC_SK_YUVA_INFO_H

#include <set>
#include <map>
#include "include/core/SkYUVAInfo.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_yuva_info_t;
void static_sk_yuva_info_delete(int key);
void * static_sk_yuva_info_get_ptr(int key); // -> SkYUVAInfo *
#ifdef __cplusplus
}
#endif

int static_sk_yuva_info_make(SkYUVAInfo value);
SkYUVAInfo static_sk_yuva_info_get(int key);
void static_sk_yuva_info_set(int key, SkYUVAInfo value);

#endif //RAIA_SKIA_STATIC_SK_YUVA_INFO_H
