//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_SAMPLING_OPTIONS_H
#define RAIA_SKIA_STATIC_SK_SAMPLING_OPTIONS_H

#include <set>
#include <string>
#include <map>
#include "include/core/SkSamplingOptions.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_sampling_options_t;
void static_sk_sampling_options_delete(int key);
SkSamplingOptions * static_sk_sampling_options_get_ptr(int key);
#ifdef __cplusplus
}
#endif

int static_sk_sampling_options_make(SkSamplingOptions value);
SkSamplingOptions static_sk_sampling_options_get(int key);
void static_sk_sampling_options_set(int key, SkSamplingOptions value);

#endif //RAIA_SKIA_STATIC_SK_SAMPLING_OPTIONS_H
