//
// Created by dolphilia on 2024/01/11.
//

#include "sk_trim_path_effect.h"

#include "include/effects/SkTrimPathEffect.h"

#include "../static/static_sk_path_effect.h"

#include "../static/static_sk_path_effect-internal.h"

extern "C" {

void SkTrimPathEffect_delete(void * trimPathEffect) {
    reinterpret_cast<SkPathEffect *>(trimPathEffect)->unref();
}

// static

sk_path_effect_t SkTrimPathEffect_Make(float startT, float stopT, reskia_trim_path_effect_mode_t mode) {
    return static_sk_path_effect_make(SkTrimPathEffect::Make(startT, stopT, static_cast<SkTrimPathEffect::Mode>(mode)));
}

}
