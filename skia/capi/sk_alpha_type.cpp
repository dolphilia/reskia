//
// Created by dolphilia on 2024/01/05.
//

#include "sk_alpha_type.h"
#include "include/core/SkAlphaType.h"

#ifdef __cplusplus
extern "C" {
#endif

// static

bool SkAlphaType_SkAlphaTypeIsOpaque(reskia_alpha_type_t at) {
    return SkAlphaTypeIsOpaque(static_cast<SkAlphaType>(at));
}

#ifdef __cplusplus
}
#endif
