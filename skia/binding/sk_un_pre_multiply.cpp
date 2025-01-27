//
// Created by dolphilia on 2024/01/11.
//

#include "sk_un_pre_multiply.h"

#include "include/core/SkUnPreMultiply.h"

extern "C" {

void SkUnPreMultiply_delete(void * unPreMultiply) {
    delete static_cast<SkUnPreMultiply *>(unPreMultiply);
}

// static

const void * SkUnPreMultiply_GetScaleTable() {
    return SkUnPreMultiply::GetScaleTable();
}

unsigned int SkUnPreMultiply_GetScale(unsigned int alpha) {
    return SkUnPreMultiply::GetScale(alpha);
}

unsigned int SkUnPreMultiply_ApplyScale(unsigned int scale, unsigned int component) {
    return SkUnPreMultiply::ApplyScale(scale, component);
}

unsigned int SkUnPreMultiply_PMColorToColor(unsigned int c) {
    return SkUnPreMultiply::PMColorToColor(c);
}

}