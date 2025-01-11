//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_TRACED_SHADER_H
#define RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_TRACED_SHADER_H

#include <set>
#include <map>
#include "include/effects/SkRuntimeEffect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_runtime_effect_traced_shader_t;
void static_sk_runtime_effect_traced_shader_delete(int key);
void * static_sk_runtime_effect_traced_shader_get_ptr(int key); // -> SkRuntimeEffect::TracedShader *
#ifdef __cplusplus
}
#endif

// const
int static_sk_runtime_effect_traced_shader_make(SkRuntimeEffect::TracedShader value);
SkRuntimeEffect::TracedShader static_sk_runtime_effect_traced_shader_get(int key);
void static_sk_runtime_effect_traced_shader_set(int key, SkRuntimeEffect::TracedShader value);

#endif //RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_TRACED_SHADER_H
