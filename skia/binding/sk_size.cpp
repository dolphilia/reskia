//
// Created by dolphilia on 2024/01/11.
//

#include "sk_size.h"

#include "include/core/SkSize.h"

#include "../static/static_sk_i_size.h"
#include "../static/static_sk_size_t.h"

#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_size_t-internal.h"

extern "C" {

void SkSize_delete(void *size) {
    delete static_cast<SkSize *>(size);
}

void SkSize_set(void *size, float w, float h) {
    static_cast<SkSize *>(size)->set(w, h);
}

bool SkSize_isZero(void *size) {
    return static_cast<SkSize *>(size)->isZero();
}

bool SkSize_isEmpty(void *size) {
    return static_cast<SkSize *>(size)->isEmpty();
}

void SkSize_setEmpty(void *size) {
    static_cast<SkSize *>(size)->setEmpty();
}

float SkSize_width(void *size) {
    return static_cast<SkSize *>(size)->width();
}

float SkSize_height(void *size) {
    return static_cast<SkSize *>(size)->height();
}

bool SkSize_equals(void *size, float w, float h) {
    return static_cast<SkSize *>(size)->equals(w, h);
}

sk_i_size_t SkSize_toRound(void *size) {
    return static_sk_i_size_make(static_cast<SkSize *>(size)->toRound());
}

sk_i_size_t SkSize_toCeil(void *size) {
    return static_sk_i_size_make(static_cast<SkSize *>(size)->toCeil());
}

sk_i_size_t SkSize_toFloor(void *size) {
    return static_sk_i_size_make(static_cast<SkSize *>(size)->toFloor());
}

// static

sk_size_t SkSize_Make(float w, float h) {
    return static_sk_size_make(SkSize::Make(w, h));
}

sk_size_t SkSize_Make_2(const void *src) {
    return static_sk_size_make(SkSize::Make(* static_cast<const SkISize *>(src)));
}

sk_size_t SkSize_MakeEmpty() {
    return static_sk_size_make(SkSize::MakeEmpty());
}

}
