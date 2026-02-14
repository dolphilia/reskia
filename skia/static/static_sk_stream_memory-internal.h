#ifndef STATIC_SK_STREAM_MEMORY_INTERNAL_H
#define STATIC_SK_STREAM_MEMORY_INTERNAL_H
#include <set>
#include <map>
#include "include/core/SkStream.h"
int static_sk_stream_memory_make(std::unique_ptr<SkStreamMemory> value);
void static_sk_stream_memory_set(int key, std::unique_ptr<SkStreamMemory> value);
SkStreamMemory* static_sk_stream_memory_borrow_entity(int key);
std::unique_ptr<SkStreamMemory> static_sk_stream_memory_take_entity(int key);
std::unique_ptr<SkStreamMemory> static_sk_stream_memory_get_entity(int key);
#endif // STATIC_SK_STREAM_MEMORY_INTERNAL_H
