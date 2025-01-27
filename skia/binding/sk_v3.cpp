//
// Created by dolphilia on 2024/01/11.
//

#include "sk_v3.h"

#include "include/core/SkM44.h"
#include "../static/static_sk_v3.h"

#include "../static/static_sk_v3-internal.h"

bool SkV3_Equal(const SkV3 &v1, const SkV3 &v2) {
    return v1 == v2;
}

bool SkV3_NotEqual(const SkV3 &v1, const SkV3 &v2) {
    return  v1 != v2;
}

SkV3 SkV3_Minus(const SkV3 &v1, const SkV3 &v2) {
    return v1 - v2;
}

SkV3 SkV3_Plus(const SkV3 &v1, const SkV3 &v2) {
    return v1 + v2;
}

SkV3 SkV3_Star(const SkV3 &v1, const SkV3 &v2) {
    return v1 * v2;
}

void SkV3_PlusAssign(SkV3 &v1, const SkV3 &v2) {
    v1 += v2;
}

void SkV3_MinusAssign(SkV3 &v1, const SkV3 &v2) {
    v1 -= v2;
}

void SkV3_StarAssign(SkV3 &v1, const SkV3 &v2) {
    v1 *= v2;
}

extern "C" {

// bool operator==(const SkV3 &v)
// bool operator!=(const SkV3 &v)
// SkV3 operator-()
// SkV3 operator+(const SkV3 &v)
// SkV3 operator-(const SkV3 &v)
// SkV3 operator*(const SkV3 &v)
// void operator+=(SkV3 v)
// void operator-=(SkV3 v)
// void operator*=(SkV3 v)
// void operator*=(SkScalar s)

void SkV3_delete(void *v3) {
    delete static_cast<SkV3 *>(v3);
}

float SkV3_lengthSquared(void *v3) {
    return static_cast<SkV3 *>(v3)->lengthSquared();
}

float SkV3_length(void *v3) {
    return static_cast<SkV3 *>(v3)->length();
}

float SkV3_dot(void *v3, const void *v) {
    return static_cast<SkV3 *>(v3)->dot(* static_cast<const SkV3 *>(v));
}

sk_v3_t SkV3_cross(void *v3, const void *v) {
    return static_sk_v3_make(static_cast<SkV3 *>(v3)->cross(* static_cast<const SkV3 *>(v)));
}

sk_v3_t SkV3_normalize(void *v3) {
    return static_sk_v3_make(static_cast<SkV3 *>(v3)->normalize());
}

const void * SkV3_ptr(void *v3) {
    return static_cast<SkV3 *>(v3)->ptr();
}

float * SkV3_ptr_2(void *v3) {
    return static_cast<SkV3 *>(v3)->ptr();
}

// static

float SkV3_Dot(const void *a, const void *b) {
    return SkV3::Dot(* static_cast<const SkV3 *>(a), * static_cast<const SkV3 *>(b));
}

sk_v3_t SkV3_Cross(const void *a, const void *b) {
    return static_sk_v3_make(SkV3::Cross(* static_cast<const SkV3 *>(a), * static_cast<const SkV3 *>(b)));
}

sk_v3_t SkV3_Normalize(const void *v) {
    return static_sk_v3_make(SkV3::Normalize(* static_cast<const SkV3 *>(v)));
}

}