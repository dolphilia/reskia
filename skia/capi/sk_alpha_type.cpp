//
// Created by dolphilia on 2024/01/05.
//

#include "sk_alpha_type.h"
#include "include/core/SkAlphaType.h"

namespace {

bool valid_alpha_type(reskia_alpha_type_t at) {
    return at >= 0 && at <= static_cast<reskia_alpha_type_t>(kLastEnum_SkAlphaType);
}

}  // namespace

#ifdef __cplusplus
extern "C" {
#endif

// static

bool SkAlphaType_SkAlphaTypeIsOpaque(reskia_alpha_type_t at) {
    if (!valid_alpha_type(at)) {
        return false;
    }
    return SkAlphaTypeIsOpaque(static_cast<SkAlphaType>(at));
}

#ifdef __cplusplus
}
#endif
