//
// Created by dolphilia on 2024/01/11.
//

#include "sk_un_pre_multiply.h"

#include "include/core/SkUnPreMultiply.h"

extern "C" {

void SkUnPreMultiply_delete(reskia_un_pre_multiply_t *unPreMultiply) {
    (void)unPreMultiply;
}

// static

const reskia_un_pre_multiply_scale_t *SkUnPreMultiply_GetScaleTable() {
    return SkUnPreMultiply::GetScaleTable();
}

reskia_un_pre_multiply_scale_t SkUnPreMultiply_GetScale(uint32_t alpha) {
    return SkUnPreMultiply::GetScale(alpha);
}

uint32_t SkUnPreMultiply_ApplyScale(reskia_un_pre_multiply_scale_t scale, uint32_t component) {
    return SkUnPreMultiply::ApplyScale(scale, component);
}

reskia_color_t SkUnPreMultiply_PMColorToColor(reskia_pmcolor_t c) {
    return SkUnPreMultiply::PMColorToColor(c);
}

}
