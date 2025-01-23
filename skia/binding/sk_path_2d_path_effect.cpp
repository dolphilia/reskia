//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path_2d_path_effect.h"

#include "include/effects/Sk2DPathEffect.h"

#include "../static/static_sk_path_effect.h"

#include "../static/static_sk_path_effect-internal.h"

extern "C" {

void SkPath2DPathEffect_delete(void * path2DPathEffect) {
    delete static_cast<SkPath2DPathEffect *>(path2DPathEffect);
}

// static

sk_path_effect_t SkPath2DPathEffect_Make(const void *matrix, const void *path) {
    return static_sk_path_effect_make(SkPath2DPathEffect::Make(* static_cast<const SkMatrix *>(matrix), * static_cast<const SkPath *>(path)));
}

void SkPath2DPathEffect_RegisterFlattenables() {
    SkPath2DPathEffect::RegisterFlattenables();
}

}
