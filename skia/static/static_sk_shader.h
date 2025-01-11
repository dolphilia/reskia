//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_SHADER_H
#define RAIA_SKIA_STATIC_SK_SHADER_H

#include <set>
#include <map>
#include "include/core/SkShader.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_shader_t;
void static_sk_shader_delete(int key);
void * static_sk_shader_get(int key); // -> SkShader *
#ifdef __cplusplus
}
#endif

int static_sk_shader_make(sk_sp<SkShader> value);
void static_sk_shader_set(int key, sk_sp<SkShader> value);
sk_sp<SkShader> static_sk_shader_move(int key);

#endif //RAIA_SKIA_STATIC_SK_SHADER_H
