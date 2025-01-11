//
// Created by dolphilia on 2024/04/02.
//

#ifndef RAIA_SKIA_STATIC_SK_FLATTENABLE_FACTORY_H
#define RAIA_SKIA_STATIC_SK_FLATTENABLE_FACTORY_H

#include <set>
#include <map>
#include "include/core/SkFlattenable.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_flattenable_factory_t;
void static_sk_flattenable_factory_delete(int key);
#ifdef __cplusplus
}
#endif

int static_sk_flattenable_factory_make(SkFlattenable::Factory value);
SkFlattenable::Factory static_sk_flattenable_factory_get(int key);

#endif //RAIA_SKIA_STATIC_SK_FLATTENABLE_FACTORY_H
