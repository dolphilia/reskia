//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_STREAM_REWINDABLE_H
#define RAIA_SKIA_STATIC_SK_STREAM_REWINDABLE_H

#include <set>
#include <map>
#include "include/core/SkStream.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_stream_rewindable_t;
void static_sk_stream_rewindable_delete(int key);
SkStreamRewindable *static_sk_stream_rewindable_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_stream_rewindable_make(std::unique_ptr<SkStreamRewindable> value);
void static_sk_stream_rewindable_set(int key, std::unique_ptr<SkStreamRewindable> value);
std::unique_ptr<SkStreamRewindable> static_sk_stream_rewindable_move(int key);

#endif //RAIA_SKIA_STATIC_SK_STREAM_REWINDABLE_H
