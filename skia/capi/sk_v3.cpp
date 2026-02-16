//
// Created by dolphilia on 2024/01/11.
//

#include "sk_v3.h"

#include "include/core/SkM44.h"
#include "../handles/static_sk_v3.h"

#include "../handles/static_sk_v3-internal.h"

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

void SkV3_delete(reskia_v3_t *v3) {
    delete reinterpret_cast<SkV3 *>(v3);
}

float SkV3_lengthSquared(reskia_v3_t *v3) {
    return reinterpret_cast<SkV3 *>(v3)->lengthSquared();
}

float SkV3_length(reskia_v3_t *v3) {
    return reinterpret_cast<SkV3 *>(v3)->length();
}

float SkV3_dot(reskia_v3_t *v3, const reskia_v3_t *v) {
    return reinterpret_cast<SkV3 *>(v3)->dot(* reinterpret_cast<const SkV3 *>(v));
}

sk_v3_t SkV3_cross(reskia_v3_t *v3, const reskia_v3_t *v) {
    return static_sk_v3_make(reinterpret_cast<SkV3 *>(v3)->cross(* reinterpret_cast<const SkV3 *>(v)));
}

sk_v3_t SkV3_normalize(reskia_v3_t *v3) {
    return static_sk_v3_make(reinterpret_cast<SkV3 *>(v3)->normalize());
}

const float *SkV3_ptr(reskia_v3_t *v3) {
    return reinterpret_cast<SkV3 *>(v3)->ptr();
}

float *SkV3_ptr_2(reskia_v3_t *v3) {
    return reinterpret_cast<SkV3 *>(v3)->ptr();
}

// static

float SkV3_Dot(const reskia_v3_t *a, const reskia_v3_t *b) {
    return SkV3::Dot(* reinterpret_cast<const SkV3 *>(a), * reinterpret_cast<const SkV3 *>(b));
}

sk_v3_t SkV3_Cross(const reskia_v3_t *a, const reskia_v3_t *b) {
    return static_sk_v3_make(SkV3::Cross(* reinterpret_cast<const SkV3 *>(a), * reinterpret_cast<const SkV3 *>(b)));
}

sk_v3_t SkV3_Normalize(const reskia_v3_t *v) {
    return static_sk_v3_make(SkV3::Normalize(* reinterpret_cast<const SkV3 *>(v)));
}

}
