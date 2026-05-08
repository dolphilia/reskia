//
// Created by dolphilia on 2024/01/09.
//

#include "sk_line_2d_path_effect.h"

#include "include/effects/Sk2DPathEffect.h"

#include "../handles/static_sk_path_effect.h"

#include "../handles/static_sk_path_effect-internal.h"

#include <utility>

namespace {

sk_path_effect_t make_path_effect_handle(sk_sp<SkPathEffect> path_effect) {
    if (!path_effect) {
        return 0;
    }
    return static_sk_path_effect_make(std::move(path_effect));
}

}  // namespace

extern "C" {

void SkLine2DPathEffect_delete(reskia_line_2d_path_effect_t *line2DPathEffect) {
    delete reinterpret_cast<SkLine2DPathEffect *>(line2DPathEffect);
}

// static

sk_path_effect_t SkLine2DPathEffect_Make(float width, const reskia_matrix_t *matrix) {
    if (matrix == nullptr) {
        return 0;
    }
    return make_path_effect_handle(SkLine2DPathEffect::Make(width, *reinterpret_cast<const SkMatrix *>(matrix)));
}

void SkLine2DPathEffect_RegisterFlattenables() {
    SkLine2DPathEffect::RegisterFlattenables();
}

}
