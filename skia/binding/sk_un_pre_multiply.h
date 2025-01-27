//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_UN_PRE_MULTIPLY_H
#define RAIA_SKIA_SK_UN_PRE_MULTIPLY_H

#include "include/core/SkUnPreMultiply.h"

extern "C" {

void SkUnPreMultiply_delete(SkUnPreMultiply *unPreMultiply); // (SkUnPreMultiply *unPreMultiply)

// static

const SkUnPreMultiply::Scale * SkUnPreMultiply_GetScaleTable(); // () -> const SkUnPreMultiply::Scale *
SkUnPreMultiply::Scale SkUnPreMultiply_GetScale(U8CPU alpha); // (U8CPU alpha) -> SkUnPreMultiply::Scale
U8CPU SkUnPreMultiply_ApplyScale(SkUnPreMultiply::Scale scale, U8CPU component); // (SkUnPreMultiply::Scale scale, U8CPU component) -> U8CPU
SkColor SkUnPreMultiply_PMColorToColor(SkPMColor c); // (SkPMColor c) -> SkColor

}

#endif //RAIA_SKIA_SK_UN_PRE_MULTIPLY_H
