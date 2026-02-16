//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_SK_ALPHA_TYPE_H
#define RAIA_SKIA_SK_ALPHA_TYPE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t reskia_alpha_type_t;

bool SkAlphaType_SkAlphaTypeIsOpaque(reskia_alpha_type_t at); // (SkAlphaType at) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ALPHA_TYPE_H
