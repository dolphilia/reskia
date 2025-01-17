//
// Created by dolphilia on 2024/01/08.
//

#include "sk_corner_path_effect.h"

#include "include/effects/SkCornerPathEffect.h"

#include "../static/static_sk_path_effect.h"

#include "../static/static_sk_path_effect-internal.h"

extern "C" {

void SkCornerPathEffect_delete(void * cornerPathEffect) {
    delete static_cast<SkCornerPathEffect *>(cornerPathEffect);
}

// static

sk_path_effect_t SkCornerPathEffect_Make(float radius) {
    return static_sk_path_effect_make(SkCornerPathEffect::Make(radius));
}

void SkCornerPathEffect_RegisterFlattenables() {
    SkCornerPathEffect::RegisterFlattenables();
}

}
