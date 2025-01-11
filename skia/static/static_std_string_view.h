//
// Created by dolphilia on 2024/01/12.
//

#ifndef RAIA_SKIA_STATIC_STD_STRING_VIEW_H
#define RAIA_SKIA_STATIC_STD_STRING_VIEW_H

#include <set>
#include <map>

typedef int string_view_t;

#ifdef __cplusplus
extern "C" {
#endif
void static_string_view_delete(int key);
#ifdef __cplusplus
}
#endif

int static_string_view_make(std::string_view value);
std::string_view static_string_view_get(int key);
void static_string_view_set(int key, std::string_view value);

#endif //RAIA_SKIA_STATIC_STD_STRING_VIEW_H
