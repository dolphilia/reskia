//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_SK_STREAM_SEEKABLE_H
#define RAIA_SKIA_STATIC_SK_STREAM_SEEKABLE_H

#include <set>
#include <map>
#include "include/core/SkStream.h"


#ifdef __cplusplus
extern "C" {
#endif
typedef int sk_stream_seekable_t;
void static_sk_stream_seekable_delete(int key);
SkStreamSeekable *static_sk_stream_seekable_get(int key);
#ifdef __cplusplus
}
#endif

int static_sk_stream_seekable_make(std::unique_ptr<SkStreamSeekable> value);
void static_sk_stream_seekable_set(int key, std::unique_ptr<SkStreamSeekable> value);
std::unique_ptr<SkStreamSeekable> static_sk_stream_seekable_move(int key);

#endif //RAIA_SKIA_STATIC_SK_STREAM_SEEKABLE_H
