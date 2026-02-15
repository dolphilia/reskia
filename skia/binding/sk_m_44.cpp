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

reskia_m_44_t *SkM44_new(const reskia_m_44_t *src) {
    return reinterpret_cast<reskia_m_44_t *>(new SkM44(*reinterpret_cast<const SkM44 *>(src)));
}

reskia_m_44_t *SkM44_new_2(const reskia_matrix_t *src) {
    return reinterpret_cast<reskia_m_44_t *>(new SkM44(*reinterpret_cast<const SkMatrix *>(src)));
}

reskia_m_44_t *SkM44_new_3() {
    return reinterpret_cast<reskia_m_44_t *>(new SkM44());
}

reskia_m_44_t *SkM44_new_4(const reskia_m_44_t *a, const reskia_m_44_t *b) {
    return reinterpret_cast<reskia_m_44_t *>(new SkM44(*reinterpret_cast<const SkM44 *>(a), *reinterpret_cast<const SkM44 *>(b)));
}

reskia_m_44_t *SkM44_new_5(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15) {
    return reinterpret_cast<reskia_m_44_t *>(new SkM44(m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15));
}

void SkM44_delete(reskia_m_44_t *m44) {
    delete reinterpret_cast<SkM44 *>(m44);
}

void SkM44_getColMajor(reskia_m_44_t *m44, float *v) {
    reinterpret_cast<SkM44 *>(m44)->getColMajor(v);
}

void SkM44_getRowMajor(reskia_m_44_t *m44, float *v) {
    reinterpret_cast<SkM44 *>(m44)->getRowMajor(v);
}

float SkM44_rc(reskia_m_44_t *m44, int r, int c) {
    return reinterpret_cast<SkM44 *>(m44)->rc(r, c);
}

void SkM44_setRC(reskia_m_44_t *m44, int r, int c, float value) {
    reinterpret_cast<SkM44 *>(m44)->setRC(r, c, value);
}

sk_v4_t SkM44_row(reskia_m_44_t *m44, int i) {
    return static_sk_v4_make(reinterpret_cast<SkM44 *>(m44)->row(i));
}

sk_v4_t SkM44_col(reskia_m_44_t *m44, int i) {
    return static_sk_v4_make(reinterpret_cast<SkM44 *>(m44)->col(i));
}

void SkM44_setRow(reskia_m_44_t *m44, int i, const reskia_v4_t *v) {
    reinterpret_cast<SkM44 *>(m44)->setRow(i, *reinterpret_cast<const SkV4 *>(v));
}

void SkM44_setCol(reskia_m_44_t *m44, int i, const reskia_v4_t *v) {
    reinterpret_cast<SkM44 *>(m44)->setCol(i, *reinterpret_cast<const SkV4 *>(v));
}

sk_m_44_t SkM44_setIdentity(reskia_m_44_t *m44) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setIdentity());
}

sk_m_44_t SkM44_setTranslate(reskia_m_44_t *m44, float x, float y, float z) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setTranslate(x, y, z));
}

sk_m_44_t SkM44_setScale(reskia_m_44_t *m44, float x, float y, float z) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setScale(x, y, z));
}

sk_m_44_t SkM44_setRotateUnitSinCos(reskia_m_44_t *m44, sk_v3_t axis, float sinAngle, float cosAngle) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setRotateUnitSinCos(static_sk_v3_get_entity(axis), sinAngle, cosAngle));
}

sk_m_44_t SkM44_setRotateUnit(reskia_m_44_t *m44, sk_v3_t axis, float radians) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setRotateUnit(static_sk_v3_get_entity(axis), radians));
}

sk_m_44_t SkM44_setRotate(reskia_m_44_t *m44, sk_v3_t axis, float radians) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setRotate(static_sk_v3_get_entity(axis), radians));
}

sk_m_44_t SkM44_setConcat(reskia_m_44_t *m44, const reskia_m_44_t *a, const reskia_m_44_t *b) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setConcat(*reinterpret_cast<const SkM44 *>(a), *reinterpret_cast<const SkM44 *>(b)));
}

sk_m_44_t SkM44_preConcat(reskia_m_44_t *m44, const reskia_m_44_t *m) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preConcat(*reinterpret_cast<const SkM44 *>(m)));
}

sk_m_44_t SkM44_preConcat_2(reskia_m_44_t *m44, const reskia_matrix_t *matrix) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preConcat(*reinterpret_cast<const SkMatrix *>(matrix)));
}

sk_m_44_t SkM44_postConcat(reskia_m_44_t *m44, const reskia_m_44_t *m) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->postConcat(*reinterpret_cast<const SkM44 *>(m)));
}

void SkM44_normalizePerspective(reskia_m_44_t *m44) {
    reinterpret_cast<SkM44 *>(m44)->normalizePerspective();
}

bool SkM44_isFinite(reskia_m_44_t *m44) {
    return reinterpret_cast<SkM44 *>(m44)->isFinite();
}

bool SkM44_invert(reskia_m_44_t *m44, reskia_m_44_t *inverse) {
    return reinterpret_cast<SkM44 *>(m44)->invert(reinterpret_cast<SkM44 *>(inverse));
}

sk_m_44_t SkM44_transpose(reskia_m_44_t *m44) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->transpose());
}

void SkM44_dump(reskia_m_44_t *m44) {
    reinterpret_cast<SkM44 *>(m44)->dump();
}

sk_v4_t SkM44_map(reskia_m_44_t *m44, float x, float y, float z, float w) {
    return static_sk_v4_make(reinterpret_cast<SkM44 *>(m44)->map(x, y, z, w));
}

sk_matrix_t SkM44_asM33(reskia_m_44_t *m44) {
    return static_sk_matrix_make(reinterpret_cast<SkM44 *>(m44)->asM33());
}

sk_m_44_t SkM44_preTranslate(reskia_m_44_t *m44, float x, float y, float z) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preTranslate(x, y, z));
}

sk_m_44_t SkM44_postTranslate(reskia_m_44_t *m44, float x, float y, float z) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->postTranslate(x, y, z));
}

sk_m_44_t SkM44_preScale(reskia_m_44_t *m44, float x, float y) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preScale(x, y));
}

sk_m_44_t SkM44_preScale_2(reskia_m_44_t *m44, float x, float y, float z) {
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preScale(x, y, z));
}

// static

sk_m_44_t SkM44_Rows(const reskia_v4_t *r0, const reskia_v4_t *r1, const reskia_v4_t *r2, const reskia_v4_t *r3) {
    return static_sk_m_44_make(SkM44::Rows(*reinterpret_cast<const SkV4 *>(r0), *reinterpret_cast<const SkV4 *>(r1), *reinterpret_cast<const SkV4 *>(r2), *reinterpret_cast<const SkV4 *>(r3)));
}

sk_m_44_t SkM44_Cols(const reskia_v4_t *c0, const reskia_v4_t *c1, const reskia_v4_t *c2, const reskia_v4_t *c3) {
    return static_sk_m_44_make(SkM44::Cols(*reinterpret_cast<const SkV4 *>(c0), *reinterpret_cast<const SkV4 *>(c1), *reinterpret_cast<const SkV4 *>(c2), *reinterpret_cast<const SkV4 *>(c3)));
}

sk_m_44_t SkM44_RowMajor(const float *r) {
    return static_sk_m_44_make(SkM44::RowMajor(r));
}

sk_m_44_t SkM44_ColMajor(const float *c) {
    return static_sk_m_44_make(SkM44::ColMajor(c));
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

sk_m_44_t SkM44_RectToRect(const reskia_rect_t *src, const reskia_rect_t *dst) {
    return static_sk_m_44_make(SkM44::RectToRect(*reinterpret_cast<const SkRect *>(src), *reinterpret_cast<const SkRect *>(dst)));
}

sk_m_44_t SkM44_LookAt(const reskia_v3_t *eye, const reskia_v3_t *center, const reskia_v3_t *up) {
    return static_sk_m_44_make(SkM44::LookAt(*reinterpret_cast<const SkV3 *>(eye), *reinterpret_cast<const SkV3 *>(center), *reinterpret_cast<const SkV3 *>(up)));
}

sk_m_44_t SkM44_Perspective(float near, float far, float angle) {
    return static_sk_m_44_make(SkM44::Perspective(near, far, angle));
}

}
