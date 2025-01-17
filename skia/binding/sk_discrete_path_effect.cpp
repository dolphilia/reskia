//
// Created by dolphilia on 2024/01/08.
//

#include "sk_discrete_path_effect.h"

#include "include/effects/SkDiscretePathEffect.h"

#include "../static/static_sk_path_effect.h"

#include "../static/static_sk_path_effect-internal.h"

extern "C" {

void SkDiscretePathEffect_delete(void * discretePathEffect) {
    delete static_cast<SkDiscretePathEffect *>(discretePathEffect);
}

sk_path_effect_t SkDiscretePathEffect_Make(float segLength, float dev, unsigned int seedAssist) {
    return static_sk_path_effect_make(SkDiscretePathEffect::Make(segLength, dev, seedAssist));
}

void SkDiscretePathEffect_RegisterFlattenables() {
    SkDiscretePathEffect::RegisterFlattenables();
}

}
