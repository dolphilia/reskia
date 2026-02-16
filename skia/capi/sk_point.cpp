//
// Created by dolphilia on 2024/01/29.
//

#include "sk_point.h"

#include "include/core/SkPoint.h"

#include "../handles/static_sk_point.h"

#include "../handles/static_sk_point-internal.h"

extern "C" {

void SkPoint_delete(reskia_point_t *point) {
    delete reinterpret_cast<SkPoint *>(point);
}

float SkPoint_x(sk_point_t point) {
    return static_sk_point_get_entity(point).x();
}

float SkPoint_y(sk_point_t point) {
    return static_sk_point_get_entity(point).y();
}

float SkPoint_dot(sk_point_t point, const reskia_vector_t *vec) {
    return static_sk_point_get_entity(point).dot(* reinterpret_cast<const SkVector *>(vec));
}

float SkPoint_length(sk_point_t point) {
    return static_sk_point_get_entity(point).length();
}

float SkPoint_cross(sk_point_t point, const reskia_vector_t *vec) {
    return static_sk_point_get_entity(point).cross(* reinterpret_cast<const SkVector *>(vec));
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

void SkPoint_scaleTo(sk_point_t point, float scale, reskia_point_t *dst) {
    static_sk_point_get_entity(point).scale(scale, reinterpret_cast<SkPoint *>(dst));
}

bool SkPoint_isFinite(sk_point_t point) {
    return static_sk_point_get_entity(point).isFinite();
}

float SkPoint_distanceToOrigin(sk_point_t point) {
    return static_sk_point_get_entity(point).distanceToOrigin();
}

void SkPoint_iset(sk_point_t point, const reskia_i_point_t *p) {
    static_sk_point_get_entity(point).iset(* reinterpret_cast<const SkIPoint *>(p));
}

void SkPoint_isetXY(sk_point_t point, int32_t x, int32_t y) {
    static_sk_point_get_entity(point).iset(x, y);
}

void SkPoint_negate(sk_point_t point) {
    static_sk_point_get_entity(point).negate();
}

void SkPoint_setAbs(sk_point_t point, const reskia_point_t *pt) {
    static_sk_point_get_entity(point).setAbs(* reinterpret_cast<const SkPoint *>(pt));
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

float SkPoint_Normalize(reskia_vector_t *vec) {
    return SkPoint::Normalize(reinterpret_cast<SkVector *>(vec));
}

float SkPoint_Length(float x, float y) {
    return SkPoint::Length(x, y);
}

float SkPoint_CrossProduct(const reskia_vector_t *a, const reskia_vector_t *b) {
    return SkPoint::CrossProduct(* reinterpret_cast<const SkVector *>(a), * reinterpret_cast<const SkVector *>(b));
}

float SkPoint_DotProduct(const reskia_vector_t *a, const reskia_vector_t *b) {
    return SkPoint::DotProduct(* reinterpret_cast<const SkVector *>(a), * reinterpret_cast<const SkVector *>(b));
}

float SkPoint_Distance(const reskia_point_t *a, const reskia_point_t *b) {
    return SkPoint::Distance(* reinterpret_cast<const SkPoint *>(a), * reinterpret_cast<const SkPoint *>(b));
}

void SkPoint_Offset(reskia_point_t *points, int count, float dx, float dy) {
    SkPoint::Offset(reinterpret_cast<SkPoint *>(points), count, dx, dy);
}

void SkPoint_OffsetByVector(reskia_point_t *points, int count, const reskia_vector_t *offset) {
    SkPoint::Offset(reinterpret_cast<SkPoint *>(points), count, * reinterpret_cast<const SkVector *>(offset));
}

}
