//
// Created by dolphilia on 2024/01/09.
//

#include "sk_i_size.h"

#include "include/core/SkSize.h"

#include "../static/static_sk_i_size.h"

#include "../static/static_sk_i_size-internal.h"

extern "C" {

void SkISize_delete(void *i_size) {
    delete static_cast<SkISize *>(i_size);
}

void SkISize_set(void *i_size, int32_t w, int32_t h) {
    static_cast<SkISize *>(i_size)->set(w, h);
}

bool SkISize_isZero(void *i_size) {
    return static_cast<SkISize *>(i_size)->isZero();
}

bool SkISize_isEmpty(void *i_size) {
    return static_cast<SkISize *>(i_size)->isEmpty();
}

void SkISize_setEmpty(void *i_size) {
    return static_cast<SkISize *>(i_size)->setEmpty();
}

int32_t SkISize_width(void *i_size) {
    return static_cast<SkISize *>(i_size)->width();
}

int32_t SkISize_height(void *i_size) {
    return static_cast<SkISize *>(i_size)->height();
}

int64_t SkISize_area(void *i_size) {
    return static_cast<SkISize *>(i_size)->area();
}

bool SkISize_equals(void *i_size, int32_t w, int32_t h) {
    return static_cast<SkISize *>(i_size)->equals(w, h);
}

// static

sk_i_size_t SkISize_Make(int32_t w, int32_t h) {
    return static_sk_i_size_make(SkISize::Make(w, h));
}

sk_i_size_t SkISize_MakeEmpty() {
    return static_sk_i_size_make(SkISize::MakeEmpty());
}

}
