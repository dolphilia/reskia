//
// Created by dolphilia on 25/01/29.
//

#include "sk_i_point.h"

#include "include/core/SkRect.h"

#include "../static/static_sk_i_point.h"

#include "../static/static_sk_i_point-internal.h"

extern "C" {

void SkIPoint_delete(void * i_point) {
    delete static_cast<SkIPoint *>(i_point);
}

int32_t SkIPoint_x(void * i_point) {
    return static_cast<SkIPoint *>(i_point)->x();
}

int32_t SkIPoint_y(void * i_point) {
    return static_cast<SkIPoint *>(i_point)->y();
}

bool SkIPoint_isZero(void * i_point) {
    return static_cast<SkIPoint *>(i_point)->isZero();
}

void SkIPoint_set(void *  i_point, int32_t x, int32_t y) {
    static_cast<SkIPoint *>(i_point)->set(x, y);
}

bool SkIPoint_equals(void * i_point, int32_t x, int32_t y) {
    return static_cast<SkIPoint *>(i_point)->equals(x, y);
}

// static

sk_i_point_t SkIPoint_Make(int x, int y) {
  return static_sk_i_point_make(SkIPoint::Make(x, y));
}

}
