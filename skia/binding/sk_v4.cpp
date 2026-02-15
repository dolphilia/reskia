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

void SkV4_delete(reskia_v4_t *v4) {
    delete reinterpret_cast<SkV4 *>(v4);
}

float SkV4_lengthSquared(reskia_v4_t *v4) {
    return reinterpret_cast<SkV4 *>(v4)->lengthSquared();
}

float SkV4_length(reskia_v4_t *v4) {
    return reinterpret_cast<SkV4 *>(v4)->length();
}

float SkV4_dot(reskia_v4_t *v4, const reskia_v4_t *v) {
    return reinterpret_cast<SkV4 *>(v4)->dot(* reinterpret_cast<const SkV4 *>(v));
}

sk_v4_t SkV4_normalize(reskia_v4_t *v4) {
    return static_sk_v4_make(reinterpret_cast<SkV4 *>(v4)->normalize());
}

const float *SkV4_ptr(reskia_v4_t *v4) {
    return reinterpret_cast<SkV4 *>(v4)->ptr();
}

float *SkV4_ptr_2(reskia_v4_t *v4) {
    return reinterpret_cast<SkV4 *>(v4)->ptr();
}

// static

float SkV4_Dot(const reskia_v4_t *a, const reskia_v4_t *b) {
    return SkV4::Dot(* reinterpret_cast<const SkV4 *>(a), * reinterpret_cast<const SkV4 *>(b));
}

sk_v4_t SkV4_Normalize(const reskia_v4_t *v) {
    return static_sk_v4_make(SkV4::Normalize(* reinterpret_cast<const SkV4 *>(v)));
}

}
