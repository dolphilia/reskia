//
// Created by dolphilia on 2024/01/09.
//

#include "sk_path_2d_path_effect.h"

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

void SkPath2DPathEffect_delete(reskia_path_2d_path_effect_t *path2DPathEffect) {
    delete reinterpret_cast<SkPath2DPathEffect *>(path2DPathEffect);
}

// static

sk_path_effect_t SkPath2DPathEffect_Make(const reskia_matrix_t *matrix, const reskia_path_t *path) {
    if (matrix == nullptr || path == nullptr) {
        return 0;
    }
    return make_path_effect_handle(SkPath2DPathEffect::Make(
        *reinterpret_cast<const SkMatrix *>(matrix),
        *reinterpret_cast<const SkPath *>(path)));
}

void SkPath2DPathEffect_RegisterFlattenables() {
    SkPath2DPathEffect::RegisterFlattenables();
}

}
