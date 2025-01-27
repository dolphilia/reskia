//
// Created by dolphilia on 2024/01/11.
//

#include "sk_v2.h"

#include "include/core/SkM44.h"

#include "../static/static_sk_v2.h"

#include "../static/static_sk_v2-internal.h"

extern "C" {

// bool operator==(const SkV2 v)
// bool operator!=(const SkV2 v)
// SkV2 operator-()
// SkV2 operator+(SkV2 v)
// SkV2 operator-(SkV2 v)
// SkV2 operator*(SkV2 v)
// void operator+=(SkV2 v)
// void operator-=(SkV2 v)
// void operator*=(SkV2 v)
// void operator*=(SkScalar s)
// void operator/=(SkScalar s)

void SkV2_delete(void *v2) {
    delete static_cast<SkV2 *>(v2);
}

float SkV2_lengthSquared(void *v2) {
    return static_cast<SkV2 *>(v2)->lengthSquared();
}

float SkV2_length(void *v2) {
    return static_cast<SkV2 *>(v2)->length();
}

float SkV2_dot(void *v2, sk_v2_t v) {
    return static_cast<SkV2 *>(v2)->dot(static_sk_v2_get(v));
}

float SkV2_cross(void *v2, sk_v2_t v) {
    return static_cast<SkV2 *>(v2)->cross(static_sk_v2_get(v));
}

sk_v2_t SkV2_normalize(void *v2) {
    return static_sk_v2_make(static_cast<SkV2 *>(v2)->normalize());
}

const void * SkV2_ptr(void *v2) {
    return static_cast<SkV2 *>(v2)->ptr();
}

float * SkV2_ptr_2(void *v2) {
    return static_cast<SkV2 *>(v2)->ptr();
}

// static

float SkV2_Dot(sk_v2_t a, sk_v2_t b) {
    return SkV2::Dot(static_sk_v2_get(a), static_sk_v2_get(b));
}

float SkV2_Cross(sk_v2_t a, sk_v2_t b) {
    return SkV2::Cross(static_sk_v2_get(a), static_sk_v2_get(b));
}

sk_v2_t SkV2_Normalize(sk_v2_t v) {
    return static_sk_v2_make(SkV2::Normalize(static_sk_v2_get(v)));
}

}
