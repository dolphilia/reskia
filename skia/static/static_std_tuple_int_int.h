//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_STATIC_STD_TUPLE_INT_INT_H
#define RAIA_SKIA_STATIC_STD_TUPLE_INT_INT_H

#include <set>
#include <string>
#include <map>
#include <tuple>

typedef int tuple_int_int_t;

#ifdef __cplusplus
extern "C" {
#endif
void static_tuple_int_int_delete(int key);
#ifdef __cplusplus
}
#endif

int static_tuple_int_int_make(std::tuple<int, int> value);
std::tuple<int, int> static_tuple_int_int_get(int key);
void static_tuple_int_int_set(int key, std::tuple<int, int> value);

#endif //RAIA_SKIA_STATIC_STD_TUPLE_INT_INT_H
