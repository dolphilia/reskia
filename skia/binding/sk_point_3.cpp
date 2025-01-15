//
// Created by dolphilia on 2024/01/10.
//

#include "sk_point_3.h"

#include "include/core/SkPoint3.h"

#include "../static/static_sk_point_3.h"

#include "../static/static_sk_point_3-internal.h"

extern "C" {

// SkPoint3 operator-()
// void operator+=(const SkPoint3 &v)
// void operator-=(const SkPoint3 &v)

void SkPoint3_delete(void *point3) {
    delete static_cast<SkPoint3 *>(point3);
}

float SkPoint3_x(void *point3) {
    return static_cast<SkPoint3 *>(point3)->x();
}

float SkPoint3_y(void *point3) {
    return static_cast<SkPoint3 *>(point3)->y();
}

float SkPoint3_z(void *point3) {
    return static_cast<SkPoint3 *>(point3)->z();
}

void SkPoint3_set(void *point3, float x, float y, float z) {
    static_cast<SkPoint3 *>(point3)->set(x, y, z);
}

float SkPoint3_length(void *point3) {
    return static_cast<SkPoint3 *>(point3)->length();
}

bool SkPoint3_normalize(void *point3) {
    return static_cast<SkPoint3 *>(point3)->normalize();
}

sk_point_3_t SkPoint3_makeScale(void *point3, float scale) {
    return static_sk_point_3_make(static_cast<SkPoint3 *>(point3)->makeScale(scale));
}

void SkPoint3_scale(void *point3, float value) {
    static_cast<SkPoint3 *>(point3)->scale(value);
}

bool SkPoint3_isFinite(void *point3) {
    return static_cast<SkPoint3 *>(point3)->isFinite();
}

float SkPoint3_dot(void *point3, const void *vec) {
    return static_cast<SkPoint3 *>(point3)->dot(* static_cast<const SkPoint3 *>(vec));
}

sk_point_3_t SkPoint3_cross(void *point3, const void *vec) {
    return static_sk_point_3_make(static_cast<SkPoint3 *>(point3)->cross(* static_cast<const SkPoint3 *>(vec)));
}

// static

sk_point_3_t SkPoint3_Make(float x, float y, float z) {
    return static_sk_point_3_make(SkPoint3::Make(x, y, z));
}

float SkPoint3_Length(float x, float y, float z) {
    return SkPoint3::Length(x, y, z);
}

float SkPoint3_DotProduct(const void *a, const void *b) {
    return SkPoint3::DotProduct(* static_cast<const SkPoint3 *>(a), * static_cast<const SkPoint3 *>(b));
}

sk_point_3_t SkPoint3_CrossProduct(const void *a, const void *b) {
    return static_sk_point_3_make(SkPoint3::CrossProduct(* static_cast<const SkPoint3 *>(a), * static_cast<const SkPoint3 *>(b)));
}

}
