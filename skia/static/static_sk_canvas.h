//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_STATIC_SK_CANVAS_H
#define RAIA_SKIA_STATIC_SK_CANVAS_H

#include "include/core/SkCanvas.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int sk_canvas_t;

void static_sk_canvas_delete(int key);
SkCanvas *static_sk_canvas_get(int key);

#ifdef __cplusplus
}
#endif

int static_sk_canvas_make(std::unique_ptr<SkCanvas> value);
void static_sk_canvas_set(int key, std::unique_ptr<SkCanvas> value);
std::unique_ptr<SkCanvas> static_sk_canvas_move(int key);

#endif //RAIA_SKIA_STATIC_SK_CANVAS_H
