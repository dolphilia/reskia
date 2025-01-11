//
// Created by dolphilia on 2024/04/04.
//

#ifndef RAIA_SKIA_STATIC_SK_V4_H
#define RAIA_SKIA_STATIC_SK_V4_H

#include "../static/static_sk_m_44.h"
#include <set>
#include <map>


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_v4_t;
void static_sk_v4_delete(int key);
void * static_sk_v4_get_ptr(int key); // -> SkV4 *
#ifdef __cplusplus
}
#endif

int static_sk_v4_make(SkV4 value);
SkV4 static_sk_v4_get(int key);
void static_sk_v4_set(int key, SkV4 value);

#endif //RAIA_SKIA_STATIC_SK_V4_H
