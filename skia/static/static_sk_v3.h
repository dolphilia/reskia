//
// Created by dolphilia on 2024/04/04.
//

#ifndef RAIA_SKIA_STATIC_SK_V3_H
#define RAIA_SKIA_STATIC_SK_V3_H

#include "../static/static_sk_m_44.h"
#include <set>
#include <map>


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_v3_t;
void static_sk_v3_delete(int key);
void * static_sk_v3_get_ptr(int key); // -> SkV3 *
#ifdef __cplusplus
}
#endif

int static_sk_v3_make(SkV3 value);
SkV3 static_sk_v3_get(int key);
void static_sk_v3_set(int key, SkV3 value);

#endif //RAIA_SKIA_STATIC_SK_V3_H
