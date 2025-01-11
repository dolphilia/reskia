//
// Created by dolphilia on 2024/04/08.
//

#ifndef RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_BUILDER_BUILDER_UNIFORM_H
#define RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_BUILDER_BUILDER_UNIFORM_H

#include <set>
#include <map>
#include "include/effects/SkRuntimeEffect.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_runtime_effect_builder_builder_uniform_t;
void static_sk_runtime_effect_builder_builder_uniform_delete(int key);
SkRuntimeEffectBuilder::BuilderUniform * static_sk_runtime_effect_builder_builder_uniform_get_ptr(int key);
#ifdef __cplusplus
}
#endif

int static_sk_runtime_effect_builder_builder_uniform_make(SkRuntimeEffectBuilder::BuilderUniform value);
SkRuntimeEffectBuilder::BuilderUniform static_sk_runtime_effect_builder_builder_uniform_get(int key);
void static_sk_runtime_effect_builder_builder_uniform_set(int key, SkRuntimeEffectBuilder::BuilderUniform value);

#endif //RAIA_SKIA_STATIC_SK_RUNTIME_EFFECT_BUILDER_BUILDER_UNIFORM_H
