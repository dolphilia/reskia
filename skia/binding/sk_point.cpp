//
// Created by dolphilia on 2024/01/29.
//

#include "sk_point.h"

#include "include/core/SkPoint.h"

#include "../static/static_sk_point.h"

#include "../static/static_sk_point-internal.h"

extern "C" {

void SkPoint_delete(void *point) {
    delete static_cast<SkPoint *>(point);
}

float SkPoint_x(sk_point_t point) {
    return static_sk_point_get_entity(point).x();
}

float SkPoint_y(sk_point_t point) {
    return static_sk_point_get_entity(point).y();
}

float SkPoint_dot(sk_point_t point, const void *vec) {
    return static_sk_point_get_entity(point).dot(* static_cast<const SkVector *>(vec));
}

float SkPoint_length(sk_point_t point) {
    return static_sk_point_get_entity(point).length();
}

float SkPoint_cross(sk_point_t point, const void *vec) {
    return static_sk_point_get_entity(point).cross(* static_cast<const SkVector *>(vec));
}

void SkPoint_set(sk_point_t point, float x, float y) {
    static_sk_point_get_entity(point).set(x, y);
}

bool SkPoint_equals(sk_point_t point, float x, float y) {
    return static_sk_point_get_entity(point).equals(x, y);
}

bool SkPoint_isZero(sk_point_t point) {
    return static_sk_point_get_entity(point).isZero();
}

void SkPoint_scale(sk_point_t point, float value) {
    static_sk_point_get_entity(point).scale(value);
}

void SkPoint_scale_2(sk_point_t point, float scale, void *dst) {
    static_sk_point_get_entity(point).scale(scale, static_cast<SkPoint *>(dst));
}

bool SkPoint_isFinite(sk_point_t point) {
    return static_sk_point_get_entity(point).isFinite();
}

float SkPoint_distanceToOrigin(sk_point_t point) {
    return static_sk_point_get_entity(point).distanceToOrigin();
}

void SkPoint_iset(sk_point_t point, const void *p) {
    static_sk_point_get_entity(point).iset(* static_cast<const SkIPoint *>(p));
}

void SkPoint_iset_2(sk_point_t point, int32_t x, int32_t y) {
    static_sk_point_get_entity(point).iset(x, y);
}

void SkPoint_negate(sk_point_t point) {
    static_sk_point_get_entity(point).negate();
}

void SkPoint_setAbs(sk_point_t point, const void *pt) {
    static_sk_point_get_entity(point).setAbs(* static_cast<const SkPoint *>(pt));
}

bool SkPoint_setLength(sk_point_t point, float length) {
    return static_sk_point_get_entity(point).setLength(length);
}

bool SkPoint_setNormalize(sk_point_t point, float x, float y) {
    return static_sk_point_get_entity(point).setNormalize(x, y);
}

// static

sk_point_t SkPoint_Make(float x, float y) {
    return static_sk_point_make(SkPoint::Make(x, y));
}

float SkPoint_Normalize(void *vec) {
    return SkPoint::Normalize(static_cast<SkVector *>(vec));
}

float SkPoint_Length(float x, float y) {
    return SkPoint::Length(x, y);
}

float SkPoint_CrossProduct(const void *a, const void *b) {
    return SkPoint::CrossProduct(* static_cast<const SkVector *>(a), * static_cast<const SkVector *>(b));
}

float SkPoint_DotProduct(const void *a, const void *b) {
    return SkPoint::DotProduct(* static_cast<const SkVector *>(a), * static_cast<const SkVector *>(b));
}

float SkPoint_Distance(const void *a, const void *b) {
    return SkPoint::Distance(* static_cast<const SkPoint *>(a), * static_cast<const SkPoint *>(b));
}

void SkPoint_Offset(void *points, int count, float dx, float dy) {
    SkPoint::Offset(static_cast<SkPoint *>(points), count, dx, dy);
}

void SkPoint_Offset_2(void *points, int count, const void *offset) {
    SkPoint::Offset(static_cast<SkPoint *>(points), count, * static_cast<const SkVector *>(offset));
}

}
