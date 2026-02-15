//
// Created by codex on 2026/02/16.
//

#ifndef RAIA_SKIA_RESKIA_STATUS_H
#define RAIA_SKIA_RESKIA_STATUS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t reskia_status_t;

enum {
    RESKIA_STATUS_OK = 0,
    RESKIA_STATUS_INVALID_ARGUMENT = 1,
    RESKIA_STATUS_NOT_FOUND = 2,
    RESKIA_STATUS_INTERNAL_ERROR = 3,
};

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_RESKIA_STATUS_H
