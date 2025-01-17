//
// Created by dolphilia on 2024/01/08.
//

#include "sk_dash_path_effect.h"

#include "include/effects/SkDashPathEffect.h"

#include "../static/static_sk_path_effect.h"

#include "../static/static_sk_path_effect-internal.h"

extern "C" {

void SkDashPathEffect_delete(void * dashPathEffect) {
    delete static_cast<SkDashPathEffect *>(dashPathEffect);
}

// static

sk_path_effect_t SkDashPathEffect_Make(const float * intervals, int count, float phase) {
    return static_sk_path_effect_make(SkDashPathEffect::Make(intervals, count, phase));
}

}
