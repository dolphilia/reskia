//
// Created by dolphilia on 2024/01/05.
//

#include "sk_blenders.h"

#include "include/effects/SkBlenders.h"

#include <utility>

#include "../handles/static_sk_blender.h"

#include "../handles/static_sk_blender-internal.h"

namespace {

sk_blender_t make_blender_handle(sk_sp<SkBlender> blender) {
    if (!blender) {
        return 0;
    }
    return static_sk_blender_make(std::move(blender));
}

} // namespace

extern "C" {

sk_blender_t SkBlenders_Arithmetic(float k1, float k2, float k3, float k4, bool enforcePremul) {
    return make_blender_handle(SkBlenders::Arithmetic(k1, k2, k3, k4, enforcePremul));
}

}
