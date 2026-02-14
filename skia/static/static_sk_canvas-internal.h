#ifndef STATIC_SK_CANVAS_INTERNAL_H
#define STATIC_SK_CANVAS_INTERNAL_H
#include <set>
#include <map>
#include "include/core/SkCanvas.h"
int static_sk_canvas_make(std::unique_ptr<SkCanvas> value);
void static_sk_canvas_set(int key, std::unique_ptr<SkCanvas> value);
SkCanvas* static_sk_canvas_borrow_entity(int key);
std::unique_ptr<SkCanvas> static_sk_canvas_take_entity(int key);
std::unique_ptr<SkCanvas> static_sk_canvas_get_entity(int key);
#endif // STATIC_SK_CANVAS_INTERNAL_H
