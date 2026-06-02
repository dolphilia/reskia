//
// Created by dolphilia on 2024/01/09.
//

#include "sk_m_44.h"

#include "include/core/SkM44.h"

#include "../handles/static_sk_m_44.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_v4.h"
#include "../handles/static_sk_v3.h"

#include "../handles/static_sk_matrix-internal.h"
#include "../handles/static_sk_m_44-internal.h"
#include "../handles/static_sk_v3-internal.h"
#include "../handles/static_sk_v4-internal.h"

namespace {

bool is_valid_m44_index(int i) {
    return 0 <= i && i < 4;
}

bool is_valid_m44_rc(int r, int c) {
    return is_valid_m44_index(r) && is_valid_m44_index(c);
}

}  // namespace

extern "C" {

reskia_m_44_t *SkM44_new(const reskia_m_44_t *src) {
    if (src == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_m_44_t *>(new SkM44(*reinterpret_cast<const SkM44 *>(src)));
}

reskia_m_44_t *SkM44_newFromMatrix(const reskia_matrix_t *src) {
    if (src == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_m_44_t *>(new SkM44(*reinterpret_cast<const SkMatrix *>(src)));
}

reskia_m_44_t *SkM44_newDefault() {
    return reinterpret_cast<reskia_m_44_t *>(new SkM44());
}

reskia_m_44_t *SkM44_newFromConcat(const reskia_m_44_t *a, const reskia_m_44_t *b) {
    if (a == nullptr || b == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_m_44_t *>(new SkM44(*reinterpret_cast<const SkM44 *>(a), *reinterpret_cast<const SkM44 *>(b)));
}

reskia_m_44_t *SkM44_newFromScalars(float m0, float m4, float m8, float m12, float m1, float m5, float m9, float m13, float m2, float m6, float m10, float m14, float m3, float m7, float m11, float m15) {
    return reinterpret_cast<reskia_m_44_t *>(new SkM44(m0, m4, m8, m12, m1, m5, m9, m13, m2, m6, m10, m14, m3, m7, m11, m15));
}

void SkM44_delete(reskia_m_44_t *m44) {
    if (m44 == nullptr) {
        return;
    }
    delete reinterpret_cast<SkM44 *>(m44);
}

bool SkM44_equals(reskia_m_44_t *m44, const reskia_m_44_t *other) {
    if (m44 == nullptr || other == nullptr) {
        return false;
    }
    return *reinterpret_cast<SkM44 *>(m44) == *reinterpret_cast<const SkM44 *>(other);
}

bool SkM44_notEquals(reskia_m_44_t *m44, const reskia_m_44_t *other) {
    if (m44 == nullptr || other == nullptr) {
        return false;
    }
    return *reinterpret_cast<SkM44 *>(m44) != *reinterpret_cast<const SkM44 *>(other);
}

void SkM44_getColMajor(reskia_m_44_t *m44, float *v) {
    if (m44 == nullptr || v == nullptr) {
        return;
    }
    reinterpret_cast<SkM44 *>(m44)->getColMajor(v);
}

void SkM44_getRowMajor(reskia_m_44_t *m44, float *v) {
    if (m44 == nullptr || v == nullptr) {
        return;
    }
    reinterpret_cast<SkM44 *>(m44)->getRowMajor(v);
}

float SkM44_rc(reskia_m_44_t *m44, int r, int c) {
    if (m44 == nullptr || !is_valid_m44_rc(r, c)) {
        return 0.0f;
    }
    return reinterpret_cast<SkM44 *>(m44)->rc(r, c);
}

void SkM44_setRC(reskia_m_44_t *m44, int r, int c, float value) {
    if (m44 == nullptr || !is_valid_m44_rc(r, c)) {
        return;
    }
    reinterpret_cast<SkM44 *>(m44)->setRC(r, c, value);
}

sk_v4_t SkM44_row(reskia_m_44_t *m44, int i) {
    if (m44 == nullptr || !is_valid_m44_index(i)) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(reinterpret_cast<SkM44 *>(m44)->row(i));
}

sk_v4_t SkM44_col(reskia_m_44_t *m44, int i) {
    if (m44 == nullptr || !is_valid_m44_index(i)) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(reinterpret_cast<SkM44 *>(m44)->col(i));
}

void SkM44_setRow(reskia_m_44_t *m44, int i, const reskia_v4_t *v) {
    if (m44 == nullptr || !is_valid_m44_index(i) || v == nullptr) {
        return;
    }
    reinterpret_cast<SkM44 *>(m44)->setRow(i, *reinterpret_cast<const SkV4 *>(v));
}

void SkM44_setCol(reskia_m_44_t *m44, int i, const reskia_v4_t *v) {
    if (m44 == nullptr || !is_valid_m44_index(i) || v == nullptr) {
        return;
    }
    reinterpret_cast<SkM44 *>(m44)->setCol(i, *reinterpret_cast<const SkV4 *>(v));
}

sk_m_44_t SkM44_setIdentity(reskia_m_44_t *m44) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setIdentity());
}

sk_m_44_t SkM44_setTranslate(reskia_m_44_t *m44, float x, float y, float z) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setTranslate(x, y, z));
}

sk_m_44_t SkM44_setScale(reskia_m_44_t *m44, float x, float y, float z) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setScale(x, y, z));
}

sk_m_44_t SkM44_setRotateUnitSinCos(reskia_m_44_t *m44, sk_v3_t axis, float sinAngle, float cosAngle) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setRotateUnitSinCos(static_sk_v3_get_entity(axis), sinAngle, cosAngle));
}

sk_m_44_t SkM44_setRotateUnit(reskia_m_44_t *m44, sk_v3_t axis, float radians) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setRotateUnit(static_sk_v3_get_entity(axis), radians));
}

sk_m_44_t SkM44_setRotate(reskia_m_44_t *m44, sk_v3_t axis, float radians) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setRotate(static_sk_v3_get_entity(axis), radians));
}

sk_m_44_t SkM44_setConcat(reskia_m_44_t *m44, const reskia_m_44_t *a, const reskia_m_44_t *b) {
    if (m44 == nullptr || a == nullptr || b == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->setConcat(*reinterpret_cast<const SkM44 *>(a), *reinterpret_cast<const SkM44 *>(b)));
}

sk_m_44_t SkM44_preConcat(reskia_m_44_t *m44, const reskia_m_44_t *m) {
    if (m44 == nullptr || m == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preConcat(*reinterpret_cast<const SkM44 *>(m)));
}

sk_m_44_t SkM44_preConcatMatrix(reskia_m_44_t *m44, const reskia_matrix_t *matrix) {
    if (m44 == nullptr || matrix == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preConcat(*reinterpret_cast<const SkMatrix *>(matrix)));
}

sk_m_44_t SkM44_postConcat(reskia_m_44_t *m44, const reskia_m_44_t *m) {
    if (m44 == nullptr || m == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->postConcat(*reinterpret_cast<const SkM44 *>(m)));
}

void SkM44_normalizePerspective(reskia_m_44_t *m44) {
    if (m44 == nullptr) {
        return;
    }
    reinterpret_cast<SkM44 *>(m44)->normalizePerspective();
}

bool SkM44_isFinite(reskia_m_44_t *m44) {
    if (m44 == nullptr) {
        return false;
    }
    return reinterpret_cast<SkM44 *>(m44)->isFinite();
}

bool SkM44_invert(reskia_m_44_t *m44, reskia_m_44_t *inverse) {
    if (m44 == nullptr) {
        return false;
    }
    return reinterpret_cast<SkM44 *>(m44)->invert(reinterpret_cast<SkM44 *>(inverse));
}

sk_m_44_t SkM44_transpose(reskia_m_44_t *m44) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->transpose());
}

void SkM44_dump(reskia_m_44_t *m44) {
    if (m44 == nullptr) {
        return;
    }
    reinterpret_cast<SkM44 *>(m44)->dump();
}

sk_v4_t SkM44_map(reskia_m_44_t *m44, float x, float y, float z, float w) {
    if (m44 == nullptr) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(reinterpret_cast<SkM44 *>(m44)->map(x, y, z, w));
}

sk_v4_t SkM44_multiplyV4(reskia_m_44_t *m44, const reskia_v4_t *v) {
    if (m44 == nullptr || v == nullptr) {
        return static_sk_v4_make({});
    }
    return static_sk_v4_make(*reinterpret_cast<SkM44 *>(m44) * *reinterpret_cast<const SkV4 *>(v));
}

sk_v3_t SkM44_multiplyV3(reskia_m_44_t *m44, const reskia_v3_t *v) {
    if (m44 == nullptr || v == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(*reinterpret_cast<SkM44 *>(m44) * *reinterpret_cast<const SkV3 *>(v));
}

sk_matrix_t SkM44_asM33(reskia_m_44_t *m44) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkM44 *>(m44)->asM33());
}

sk_m_44_t SkM44_preTranslate(reskia_m_44_t *m44, float x, float y, float z) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preTranslate(x, y, z));
}

sk_m_44_t SkM44_postTranslate(reskia_m_44_t *m44, float x, float y, float z) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->postTranslate(x, y, z));
}

sk_m_44_t SkM44_preScale(reskia_m_44_t *m44, float x, float y) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preScale(x, y));
}

sk_m_44_t SkM44_preScale3D(reskia_m_44_t *m44, float x, float y, float z) {
    if (m44 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkM44 *>(m44)->preScale(x, y, z));
}

// static

sk_m_44_t SkM44_Rows(const reskia_v4_t *r0, const reskia_v4_t *r1, const reskia_v4_t *r2, const reskia_v4_t *r3) {
    if (r0 == nullptr || r1 == nullptr || r2 == nullptr || r3 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(SkM44::Rows(*reinterpret_cast<const SkV4 *>(r0), *reinterpret_cast<const SkV4 *>(r1), *reinterpret_cast<const SkV4 *>(r2), *reinterpret_cast<const SkV4 *>(r3)));
}

sk_m_44_t SkM44_Cols(const reskia_v4_t *c0, const reskia_v4_t *c1, const reskia_v4_t *c2, const reskia_v4_t *c3) {
    if (c0 == nullptr || c1 == nullptr || c2 == nullptr || c3 == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(SkM44::Cols(*reinterpret_cast<const SkV4 *>(c0), *reinterpret_cast<const SkV4 *>(c1), *reinterpret_cast<const SkV4 *>(c2), *reinterpret_cast<const SkV4 *>(c3)));
}

sk_m_44_t SkM44_RowMajor(const float *r) {
    if (r == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(SkM44::RowMajor(r));
}

sk_m_44_t SkM44_ColMajor(const float *c) {
    if (c == nullptr) {
        return 0;
    }
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
    if (src == nullptr || dst == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(SkM44::RectToRect(*reinterpret_cast<const SkRect *>(src), *reinterpret_cast<const SkRect *>(dst)));
}

sk_m_44_t SkM44_LookAt(const reskia_v3_t *eye, const reskia_v3_t *center, const reskia_v3_t *up) {
    if (eye == nullptr || center == nullptr || up == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(SkM44::LookAt(*reinterpret_cast<const SkV3 *>(eye), *reinterpret_cast<const SkV3 *>(center), *reinterpret_cast<const SkV3 *>(up)));
}

sk_m_44_t SkM44_Perspective(float near, float far, float angle) {
    return static_sk_m_44_make(SkM44::Perspective(near, far, angle));
}

}
