//
// Created by dolphilia on 2024/01/09.
//

#include "sk_i_size.h"

#include "include/core/SkSize.h"

#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_i_size-internal.h"

extern "C" {

void SkISize_delete(reskia_i_size_t *i_size) {
    delete reinterpret_cast<SkISize *>(i_size);
}

void SkISize_set(reskia_i_size_t *i_size, int32_t w, int32_t h) {
    reinterpret_cast<SkISize *>(i_size)->set(w, h);
}

bool SkISize_isZero(reskia_i_size_t *i_size) {
    return reinterpret_cast<SkISize *>(i_size)->isZero();
}

bool SkISize_isEmpty(reskia_i_size_t *i_size) {
    return reinterpret_cast<SkISize *>(i_size)->isEmpty();
}

void SkISize_setEmpty(reskia_i_size_t *i_size) {
    return reinterpret_cast<SkISize *>(i_size)->setEmpty();
}

int32_t SkISize_width(reskia_i_size_t *i_size) {
    return reinterpret_cast<SkISize *>(i_size)->width();
}

int32_t SkISize_height(reskia_i_size_t *i_size) {
    return reinterpret_cast<SkISize *>(i_size)->height();
}

int64_t SkISize_area(reskia_i_size_t *i_size) {
    return reinterpret_cast<SkISize *>(i_size)->area();
}

bool SkISize_equals(reskia_i_size_t *i_size, int32_t w, int32_t h) {
    return reinterpret_cast<SkISize *>(i_size)->equals(w, h);
}

// static

sk_i_size_t SkISize_Make(int32_t w, int32_t h) {
    return static_sk_i_size_make(SkISize::Make(w, h));
}

sk_i_size_t SkISize_MakeEmpty() {
    return static_sk_i_size_make(SkISize::MakeEmpty());
}

}
