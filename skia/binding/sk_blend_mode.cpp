//
// Created by dolphilia on 2024/01/06.
//

#include "sk_blend_mode.h"

#include "include/core/SkBlendMode.h"

extern "C" {

bool SkBlendMode_SkBlendMode_AsCoeff(int mode, void *src, void *dst) {
    return SkBlendMode_AsCoeff(static_cast<SkBlendMode>(mode), static_cast<SkBlendModeCoeff *>(src), static_cast<SkBlendModeCoeff *>(dst));
}

const char *SkBlendMode_SkBlendMode_Name(int blendMode) {
    return SkBlendMode_Name(static_cast<SkBlendMode>(blendMode));
}

}