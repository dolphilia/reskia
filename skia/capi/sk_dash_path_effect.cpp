//
// Created by dolphilia on 2024/01/08.
//

#include "sk_dash_path_effect.h"

#include "include/effects/SkDashPathEffect.h"

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

void SkDashPathEffect_delete(void * dashPathEffect) {
    if (dashPathEffect == nullptr) {
        return;
    }
    reinterpret_cast<SkPathEffect *>(dashPathEffect)->unref();
}

// static

sk_path_effect_t SkDashPathEffect_Make(const float * intervals, int count, float phase) {
    if (intervals == nullptr || count <= 0) {
        return 0;
    }
    return make_path_effect_handle(
            SkDashPathEffect::Make({intervals, static_cast<size_t>(count)}, phase));
}

}
