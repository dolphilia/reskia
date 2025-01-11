//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_PATH_EFFECT_H
#define RAIA_SKIA_STATIC_SK_PATH_EFFECT_H

#include <set>
#include <map>
#include "include/core/SkPathEffect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_path_effect_t;
void static_sk_path_effect_delete(int key);
void *static_sk_path_effect_get(int key); // -> SkPathEffect *
#ifdef __cplusplus
}
#endif

int static_sk_path_effect_make(sk_sp<SkPathEffect> value);
void static_sk_path_effect_set(int key, sk_sp<SkPathEffect> value);
sk_sp<SkPathEffect> static_sk_path_effect_move(int key);

#endif //RAIA_SKIA_STATIC_SK_PATH_EFFECT_H
