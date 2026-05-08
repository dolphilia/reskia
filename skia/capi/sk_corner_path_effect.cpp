//
// Created by dolphilia on 2024/01/08.
//

#include "sk_corner_path_effect.h"

#include "include/effects/SkCornerPathEffect.h"

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

void SkCornerPathEffect_delete(void * cornerPathEffect) {
    if (cornerPathEffect == nullptr) {
        return;
    }
    reinterpret_cast<SkPathEffect *>(cornerPathEffect)->unref();
}

// static

sk_path_effect_t SkCornerPathEffect_Make(float radius) {
    return make_path_effect_handle(SkCornerPathEffect::Make(radius));
}

void SkCornerPathEffect_RegisterFlattenables() {
    SkCornerPathEffect::RegisterFlattenables();
}

}
