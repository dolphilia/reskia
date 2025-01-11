//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_STREAM_H
#define RAIA_SKIA_STATIC_SK_STREAM_H

#include <set>
#include <map>
#include "include/core/SkStream.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_stream_t;
void static_sk_stream_delete(int key);
void *static_sk_stream_get(int key); // -> SkStream *
#ifdef __cplusplus
}
#endif

int static_sk_stream_make(std::unique_ptr<SkStream> value);
void static_sk_stream_set(int key, std::unique_ptr<SkStream> value);
std::unique_ptr<SkStream> static_sk_stream_move(int key);

#endif //RAIA_SKIA_STATIC_SK_STREAM_H
