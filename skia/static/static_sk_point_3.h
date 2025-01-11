//
// Created by dolphilia on 2024/04/05.
//

#ifndef RAIA_SKIA_STATIC_SK_POINT_3_H
#define RAIA_SKIA_STATIC_SK_POINT_3_H

#include <set>
#include <map>
#include "include/core/SkPoint3.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_point_3_t;
void static_sk_point_3_delete(int key);
void * static_sk_point_3_get_ptr(int key); // -> SkPoint3 *
#ifdef __cplusplus
}
#endif

int static_sk_point_3_make(SkPoint3 value);
SkPoint3 static_sk_point_3_get(int key);
void static_sk_point_3_set(int key, SkPoint3 value);

#endif //RAIA_SKIA_STATIC_SK_POINT_3_H
