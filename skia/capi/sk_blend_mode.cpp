//
// Created by dolphilia on 2024/01/06.
//

#include "sk_blend_mode.h"

#include "include/core/SkBlendMode.h"

namespace {

bool valid_blend_mode(reskia_blend_mode_t mode) {
    return mode >= 0 && mode <= static_cast<reskia_blend_mode_t>(SkBlendMode::kLastMode);
}

}  // namespace

extern "C" {

bool SkBlendMode_SkBlendMode_AsCoeff(reskia_blend_mode_t mode, void *src, void *dst) {
    if (!valid_blend_mode(mode) || src == nullptr || dst == nullptr) {
        return false;
    }
    return SkBlendMode_AsCoeff(static_cast<SkBlendMode>(mode), static_cast<SkBlendModeCoeff *>(src), static_cast<SkBlendModeCoeff *>(dst));
}

const char *SkBlendMode_SkBlendMode_Name(reskia_blend_mode_t blendMode) {
    if (!valid_blend_mode(blendMode)) {
        return nullptr;
    }
    return SkBlendMode_Name(static_cast<SkBlendMode>(blendMode));
}

}
