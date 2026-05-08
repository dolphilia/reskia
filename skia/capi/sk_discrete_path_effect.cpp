//
// Created by dolphilia on 2024/01/08.
//

#include "sk_discrete_path_effect.h"

#include "include/effects/SkDiscretePathEffect.h"

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

void SkDiscretePathEffect_delete(reskia_discrete_path_effect_t *discretePathEffect) {
    delete reinterpret_cast<SkDiscretePathEffect *>(discretePathEffect);
}

sk_path_effect_t SkDiscretePathEffect_Make(float segLength, float dev, uint32_t seedAssist) {
    return make_path_effect_handle(SkDiscretePathEffect::Make(segLength, dev, seedAssist));
}

void SkDiscretePathEffect_RegisterFlattenables() {
    SkDiscretePathEffect::RegisterFlattenables();
}

}
