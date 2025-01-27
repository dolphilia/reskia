//
// Created by dolphilia on 2024/01/11.
//

#include "sk_v4.h"

#include "include/core/SkM44.h"
#include "../static/static_sk_v4.h"

#include "../static/static_sk_v4-internal.h"

extern "C" {

// bool operator==(const SkV4 &v)
// bool operator!=(const SkV4 &v)
// SkV4 operator-()
// SkV4 operator+(const SkV4 &v)
// SkV4 operator-(const SkV4 &v)
// SkV4 operator*(const SkV4 &v)
// float operator[](int i)
// float & operator[](int i)

void SkV4_delete(void *v4) {
    delete static_cast<SkV4 *>(v4);
}

float SkV4_lengthSquared(void *v4) {
    return static_cast<SkV4 *>(v4)->lengthSquared();
}

float SkV4_length(void *v4) {
    return static_cast<SkV4 *>(v4)->length();
}

float SkV4_dot(void *v4, const void *v) {
    return static_cast<SkV4 *>(v4)->dot(* static_cast<const SkV4 *>(v));
}

sk_v4_t SkV4_normalize(void *v4) {
    return static_sk_v4_make(static_cast<SkV4 *>(v4)->normalize());
}

const void * SkV4_ptr(void *v4) {
    return static_cast<SkV4 *>(v4)->ptr();
}

float * SkV4_ptr_2(void *v4) {
    return static_cast<SkV4 *>(v4)->ptr();
}

// static

float SkV4_Dot(const void *a, const void *b) {
    return SkV4::Dot(* static_cast<const SkV4 *>(a), * static_cast<const SkV4 *>(b));
}

sk_v4_t SkV4_Normalize(const void *v) {
    return static_sk_v4_make(SkV4::Normalize(* static_cast<const SkV4 *>(v)));
}

}
