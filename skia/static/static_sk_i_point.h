//
// Created by dolphilia on 2024/03/30.
//

#ifndef RAIA_SKIA_STATIC_SK_I_POINT_H
#define RAIA_SKIA_STATIC_SK_I_POINT_H

#include <set>
#include <string>
#include <map>
#include "include/core/SkRect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_i_point_t;
void static_sk_i_point_delete(int key);
SkIPoint * static_sk_i_point_get_ptr(int key);
#ifdef __cplusplus
}
#endif

int static_sk_i_point_make(SkIPoint value);
SkIPoint static_sk_i_point_get(int key);
void static_sk_i_point_set(int key, SkIPoint value);

#endif //RAIA_SKIA_STATIC_SK_I_POINT_H
