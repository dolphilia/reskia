//
// Created by dolphilia on 2024/04/08.
//

#ifndef RAIA_SKIA_STATIC_SK_SIZE_T_H
#define RAIA_SKIA_STATIC_SK_SIZE_T_H

#include <set>
#include <map>
#include "include/core/SkRect.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef int sk_size_t;

void static_sk_size_delete(int key);
void * static_sk_size_get_ptr(int key); // -> SkSize *

#ifdef __cplusplus
}
#endif

int static_sk_size_make(SkSize value);
SkSize static_sk_size_get(int key);
void static_sk_size_set(int key, SkSize value);

#endif //RAIA_SKIA_STATIC_SK_SIZE_T_H
