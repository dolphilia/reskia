//
// Created by dolphilia on 2024/01/09.
//

#include "sk_m_44.h"

#include "include/core/SkM44.h"

#include "../static/static_sk_m_44.h"
#include "../static/static_sk_matrix.h"
#include "../static/static_sk_v4.h"
#include "../static/static_sk_v3.h"

#include "../static/static_sk_matrix-internal.h"
#include "../static/static_sk_m_44-internal.h"
#include "../static/static_sk_v3-internal.h"
#include "../static/static_sk_v4-internal.h"

extern "C" {

//SkM44 & operator=(const SkM44 &src)
//bool operator==(const SkM44 &other)
//bool operator!=(const SkM44 &other)
//SkV4 operator*(const SkV4 &v)
//SkV3 operator*(SkV3 v)

void *SkM44_new(const void *src) {
    return new SkM44(* static_cast<const SkM44 *>(src));
}

void *SkM44_new_2(const void *src) {
    return new SkM44(* static_cast<const SkMatrix *>(src));
}

void *SkM44_new_3() {
    return new SkM44();
}

void *SkM44_new_4(const void *a, const void *b) {
    return new SkM44(* static_cast<const SkM44 *>(a), * static_cast<const SkM44 *>(b));
}

void *SkM44_new_5(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15) {
    return new SkM44(m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15);
}

void SkM44_delete(void *m44) {
    delete static_cast<SkM44 *>(m44);
}

void SkM44_getColMajor(void *m44, void * v) {
    static_cast<SkM44 *>(m44)->getColMajor(static_cast<SkScalar *>(v));
}

void SkM44_getRowMajor(void *m44, void * v) {
    static_cast<SkM44 *>(m44)->getRowMajor(static_cast<SkScalar *>(v));
}

float SkM44_rc(void *m44, int r, int c) {
    return static_cast<SkM44 *>(m44)->rc(r, c);
}

void SkM44_setRC(void *m44, int r, int c, float value) {
    static_cast<SkM44 *>(m44)->setRC(r, c, value);
}

sk_v4_t SkM44_row(void *m44, int i) {
    return static_sk_v4_make(static_cast<SkM44 *>(m44)->row(i));
}

sk_v4_t SkM44_col(void *m44, int i) {
    return static_sk_v4_make(static_cast<SkM44 *>(m44)->col(i));
}

void SkM44_setRow(void *m44, int i, const void *v) {
    static_cast<SkM44 *>(m44)->setRow(i, * static_cast<const SkV4 *>(v));
}

void SkM44_setCol(void *m44, int i, const void *v) {
    static_cast<SkM44 *>(m44)->setCol(i, * static_cast<const SkV4 *>(v));
}

sk_m_44_t SkM44_setIdentity(void *m44) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->setIdentity());
}

sk_m_44_t SkM44_setTranslate(void *m44, float x, float y, float z) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->setTranslate(x, y, z));
}

sk_m_44_t SkM44_setScale(void *m44, float x, float y, float z) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->setScale(x, y, z));
}

sk_m_44_t SkM44_setRotateUnitSinCos(void *m44, sk_v3_t axis, float sinAngle, float cosAngle) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->setRotateUnitSinCos(static_sk_v3_get_entity(axis), sinAngle, cosAngle));
}

sk_m_44_t SkM44_setRotateUnit(void *m44, sk_v3_t axis, float radians) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->setRotateUnit(static_sk_v3_get_entity(axis), radians));
}

sk_m_44_t SkM44_setRotate(void *m44, sk_v3_t axis, float radians) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->setRotate(static_sk_v3_get_entity(axis), radians));
}

sk_m_44_t SkM44_setConcat(void *m44, const void *a, const void *b) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->setConcat(* static_cast<const SkM44 *>(a), * static_cast<const SkM44 *>(b)));
}

sk_m_44_t SkM44_preConcat(void *m44, const void *m) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->preConcat(* static_cast<const SkM44 *>(m)));
}

sk_m_44_t SkM44_preConcat_2(void *m44, const void *matrix) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->preConcat(* static_cast<const SkMatrix *>(matrix)));
}

sk_m_44_t SkM44_postConcat(void *m44, const void *m) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->postConcat(* static_cast<const SkM44 *>(m)));
}

void SkM44_normalizePerspective(void *m44) {
    static_cast<SkM44 *>(m44)->normalizePerspective();
}

bool SkM44_isFinite(void *m44) {
    return static_cast<SkM44 *>(m44)->isFinite();
}

bool SkM44_invert(void *m44, void *inverse) {
    return static_cast<SkM44 *>(m44)->invert(static_cast<SkM44 *>(inverse));
}

sk_m_44_t SkM44_transpose(void *m44) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->transpose());
}

void SkM44_dump(void *m44) {
    static_cast<SkM44 *>(m44)->dump();
}

sk_v4_t SkM44_map(void *m44, float x, float y, float z, float w) {
    return static_sk_v4_make(static_cast<SkM44 *>(m44)->map(x, y, z, w));
}

sk_matrix_t SkM44_asM33(void *m44) {
    return static_sk_matrix_make(static_cast<SkM44 *>(m44)->asM33());
}

sk_m_44_t SkM44_preTranslate(void *m44, float x, float y, float z) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->preTranslate(x, y, z));
}

sk_m_44_t SkM44_postTranslate(void *m44, float x, float y, float z) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->postTranslate(x, y, z));
}

sk_m_44_t SkM44_preScale(void *m44, float x, float y) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->preScale(x, y));
}

sk_m_44_t SkM44_preScale_2(void *m44, float x, float y, float z) {
    return static_sk_m_44_make(static_cast<SkM44 *>(m44)->preScale(x, y, z));
}

// static

sk_m_44_t SkM44_Rows(const void *r0, const void *r1, const void *r2, const void *r3) {
    return static_sk_m_44_make(SkM44::Rows(* static_cast<const SkV4 *>(r0), * static_cast<const SkV4 *>(r1), * static_cast<const SkV4 *>(r2), * static_cast<const SkV4 *>(r3)));
}

sk_m_44_t SkM44_Cols(const void *c0, const void *c1, const void *c2, const void *c3) {
    return static_sk_m_44_make(SkM44::Cols(* (const SkV4 *)c0, * static_cast<const SkV4 *>(c1), * static_cast<const SkV4 *>(c2), * static_cast<const SkV4 *>(c3)));
}

sk_m_44_t SkM44_RowMajor(const void * r) {
    return static_sk_m_44_make(SkM44::RowMajor(static_cast<const SkScalar *>(r)));
}

sk_m_44_t SkM44_ColMajor(const void * c) {
    return static_sk_m_44_make(SkM44::ColMajor(static_cast<const SkScalar *>(c)));
}

sk_m_44_t SkM44_Translate(float x, float y, float z) {
    return static_sk_m_44_make(SkM44::Translate(x, y, z));
}

sk_m_44_t SkM44_Scale(float x, float y, float z) {
    return static_sk_m_44_make(SkM44::Scale(x, y, z));
}

sk_m_44_t SkM44_Rotate(sk_v3_t axis, float radians) {
    return static_sk_m_44_make(SkM44::Rotate(static_sk_v3_get_entity(axis), radians));
}

sk_m_44_t SkM44_RectToRect(const void *src, const void *dst) {
    return static_sk_m_44_make(SkM44::RectToRect(* static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst)));
}

sk_m_44_t SkM44_LookAt(const void *eye, const void *center, const void *up) {
    return static_sk_m_44_make(SkM44::LookAt(* static_cast<const SkV3 *>(eye), * static_cast<const SkV3 *>(center), * static_cast<const SkV3 *>(up)));
}

sk_m_44_t SkM44_Perspective(float near, float far, float angle) {
    return static_sk_m_44_make(SkM44::Perspective(near, far, angle));
}

}
