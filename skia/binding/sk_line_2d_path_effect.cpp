//
// Created by dolphilia on 2024/01/09.
//

#include "sk_line_2d_path_effect.h"

#include "include/effects/Sk2DPathEffect.h"

#include "../static/static_sk_path_effect.h"

#include "../static/static_sk_path_effect-internal.h"

extern "C" {

void SkLine2DPathEffect_delete(void * line2DPathEffect) {
    delete static_cast<SkLine2DPathEffect *>(line2DPathEffect);
}

// static

sk_path_effect_t SkLine2DPathEffect_Make(float width, const void *matrix) {
    return static_sk_path_effect_make(SkLine2DPathEffect::Make(width, * static_cast<const SkMatrix *>(matrix)));
}

void SkLine2DPathEffect_RegisterFlattenables() {
    SkLine2DPathEffect::RegisterFlattenables();
}

}
