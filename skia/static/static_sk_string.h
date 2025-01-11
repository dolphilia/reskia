//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_STATIC_SK_STRING_H
#define RAIA_SKIA_STATIC_SK_STRING_H

#include <set>
#include <map>
#include "include/core/SkString.h"
#include "include/private/base/SkSpan_impl.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_string_t;
void static_sk_string_delete(int key);
SkString * static_sk_string_get_ptr(int key);
// sk_span
void static_sk_span_sk_string_delete(int key);
SkString * static_sk_span_sk_string_get_ptr(int key, int index);
#ifdef __cplusplus
}
#endif

int static_sk_string_make(SkString value);
SkString static_sk_string_get(int key);
void static_sk_string_set(int key, SkString value);

// sk_span

int static_sk_span_sk_string_make(SkSpan<SkString> value);
SkSpan<SkString> static_sk_span_sk_string_get(int key);
void static_sk_span_sk_string_set(int key, SkSpan<SkString> value);

#endif //RAIA_SKIA_STATIC_SK_STRING_H
