//
// Created by dolphilia on 25/01/29.
//

#include "sk_i_point.h"

#include "include/core/SkRect.h"

#include "../handles/static_sk_i_point.h"

#include "../handles/static_sk_i_point-internal.h"

extern "C" {

void SkIPoint_delete(void * i_point) {
    delete reinterpret_cast<SkIPoint *>(i_point);
}

int32_t SkIPoint_x(void * i_point) {
    if (i_point == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkIPoint *>(i_point)->x();
}

int32_t SkIPoint_y(void * i_point) {
    if (i_point == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkIPoint *>(i_point)->y();
}

bool SkIPoint_isZero(void * i_point) {
    if (i_point == nullptr) {
        return true;
    }
    return reinterpret_cast<SkIPoint *>(i_point)->isZero();
}

void SkIPoint_set(void *  i_point, int32_t x, int32_t y) {
    if (i_point == nullptr) {
        return;
    }
    reinterpret_cast<SkIPoint *>(i_point)->set(x, y);
}

sk_i_point_t SkIPoint_negate(void * i_point) {
    if (i_point == nullptr) {
        return static_sk_i_point_make({});
    }
    return static_sk_i_point_make(-(* reinterpret_cast<SkIPoint *>(i_point)));
}

void SkIPoint_addAssign(void * i_point, const void *ivector) {
    if (i_point == nullptr || ivector == nullptr) {
        return;
    }
    (* reinterpret_cast<SkIPoint *>(i_point)) += (* reinterpret_cast<const SkIVector *>(ivector));
}

void SkIPoint_subtractAssign(void * i_point, const void *ivector) {
    if (i_point == nullptr || ivector == nullptr) {
        return;
    }
    (* reinterpret_cast<SkIPoint *>(i_point)) -= (* reinterpret_cast<const SkIVector *>(ivector));
}

bool SkIPoint_equals(void * i_point, int32_t x, int32_t y) {
    if (i_point == nullptr) {
        return false;
    }
    return reinterpret_cast<SkIPoint *>(i_point)->equals(x, y);
}

// static

sk_i_point_t SkIPoint_Make(int x, int y) {
  return static_sk_i_point_make(SkIPoint::Make(x, y));
}

}
