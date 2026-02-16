//
// Created by dolphilia on 2024/01/11.
//

#include "sk_size.h"

#include "include/core/SkSize.h"

#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_size_t.h"

#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_size_t-internal.h"

extern "C" {

void SkSize_delete(reskia_size_t *size) {
    delete reinterpret_cast<SkSize *>(size);
}

void SkSize_set(reskia_size_t *size, float w, float h) {
    reinterpret_cast<SkSize *>(size)->set(w, h);
}

bool SkSize_isZero(reskia_size_t *size) {
    return reinterpret_cast<SkSize *>(size)->isZero();
}

bool SkSize_isEmpty(reskia_size_t *size) {
    return reinterpret_cast<SkSize *>(size)->isEmpty();
}

void SkSize_setEmpty(reskia_size_t *size) {
    reinterpret_cast<SkSize *>(size)->setEmpty();
}

float SkSize_width(reskia_size_t *size) {
    return reinterpret_cast<SkSize *>(size)->width();
}

float SkSize_height(reskia_size_t *size) {
    return reinterpret_cast<SkSize *>(size)->height();
}

bool SkSize_equals(reskia_size_t *size, float w, float h) {
    return reinterpret_cast<SkSize *>(size)->equals(w, h);
}

sk_i_size_t SkSize_toRound(reskia_size_t *size) {
    return static_sk_i_size_make(reinterpret_cast<SkSize *>(size)->toRound());
}

sk_i_size_t SkSize_toCeil(reskia_size_t *size) {
    return static_sk_i_size_make(reinterpret_cast<SkSize *>(size)->toCeil());
}

sk_i_size_t SkSize_toFloor(reskia_size_t *size) {
    return static_sk_i_size_make(reinterpret_cast<SkSize *>(size)->toFloor());
}

// static

sk_size_t SkSize_Make(float w, float h) {
    return static_sk_size_make(SkSize::Make(w, h));
}

sk_size_t SkSize_MakeFromISize(const reskia_i_size_t *src) {
    return static_sk_size_make(SkSize::Make(*reinterpret_cast<const SkISize *>(src)));
}

sk_size_t SkSize_MakeEmpty() {
    return static_sk_size_make(SkSize::MakeEmpty());
}

}
