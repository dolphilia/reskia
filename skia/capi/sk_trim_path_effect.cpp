//
// Created by dolphilia on 2024/01/11.
//

#include "sk_trim_path_effect.h"

#include "include/effects/SkTrimPathEffect.h"

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

void SkTrimPathEffect_delete(void * trimPathEffect) {
    if (trimPathEffect == nullptr) {
        return;
    }
    reinterpret_cast<SkPathEffect *>(trimPathEffect)->unref();
}

// static

sk_path_effect_t SkTrimPathEffect_Make(float startT, float stopT, reskia_trim_path_effect_mode_t mode) {
    return make_path_effect_handle(SkTrimPathEffect::Make(startT, stopT, static_cast<SkTrimPathEffect::Mode>(mode)));
}

}
