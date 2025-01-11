//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_STREAM_MEMORY_H
#define RAIA_SKIA_STATIC_SK_STREAM_MEMORY_H

#include <set>
#include <map>
#include "include/core/SkStream.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_stream_memory_t;
void static_sk_stream_memory_delete(int key);
SkStreamMemory *static_sk_stream_memory_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_stream_memory_make(std::unique_ptr<SkStreamMemory> value);
void static_sk_stream_memory_set(int key, std::unique_ptr<SkStreamMemory> value);
std::unique_ptr<SkStreamMemory> static_sk_stream_memory_move(int key);

#endif //RAIA_SKIA_STATIC_SK_STREAM_MEMORY_H
