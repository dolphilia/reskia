//
// Created by dolphilia on 2024/04/01.
//

#ifndef RAIA_SKIA_STATIC_STD_CHRONO_MILLISECONDS_H
#define RAIA_SKIA_STATIC_STD_CHRONO_MILLISECONDS_H

#include <set>
#include <map>
#ifdef _WIN32
#include <chrono>
#endif

typedef int chrono_milliseconds_t;

#ifdef __cplusplus
extern "C" {
#endif
void static_chrono_milliseconds_delete(int key);
#ifdef __cplusplus
}
#endif

int static_chrono_milliseconds_make(std::chrono::milliseconds value);
std::chrono::milliseconds static_chrono_milliseconds_get(int key);
void static_chrono_milliseconds_set(int key, std::chrono::milliseconds value);

#endif //RAIA_SKIA_STATIC_STD_CHRONO_MILLISECONDS_H
