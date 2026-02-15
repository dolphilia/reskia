//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path_1d_path_effect.h"

#include "include/effects/Sk1DPathEffect.h"

#include "../static/static_sk_path_effect.h"

#include "../static/static_sk_path_effect-internal.h"

extern "C" {

void SkPath1DPathEffect_delete(reskia_path_1d_path_effect_t *path1DPathEffect) {
    delete reinterpret_cast<SkPath1DPathEffect *>(path1DPathEffect);
}

// static

sk_path_effect_t SkPath1DPathEffect_Make(const reskia_path_t *path, float advance, float phase, reskia_path_1d_path_effect_style_t style) {
    return static_sk_path_effect_make(SkPath1DPathEffect::Make(
        *reinterpret_cast<const SkPath *>(path),
        advance,
        phase,
        static_cast<SkPath1DPathEffect::Style>(style)));
}

void SkPath1DPathEffect_RegisterFlattenables() {
    SkPath1DPathEffect::RegisterFlattenables();
}

}
