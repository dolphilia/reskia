#include "capi/sk_m_44.h"
#include "capi/sk_matrix.h"
#include "capi/sk_rect.h"
#include "handles/static_sk_m_44.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_rect.h"
#include "handles/static_sk_v4.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[m44-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkM44_delete(nullptr);
    SkM44_getColMajor(nullptr, nullptr);
    SkM44_getRowMajor(nullptr, nullptr);
    SkM44_setRC(nullptr, 0, 0, 1.0f);
    SkM44_setRow(nullptr, 0, nullptr);
    SkM44_setCol(nullptr, 0, nullptr);
    SkM44_normalizePerspective(nullptr);
    SkM44_dump(nullptr);

    if (!check(SkM44_new(nullptr) == nullptr, "SkM44_new(nullptr)")) {
        return 1;
    }
    if (!check(SkM44_newFromMatrix(nullptr) == nullptr, "SkM44_newFromMatrix(nullptr)")) {
        return 2;
    }
    if (!check(SkM44_newFromConcat(nullptr, nullptr) == nullptr, "SkM44_newFromConcat(nullptr)")) {
        return 3;
    }
    if (!check(!SkM44_equals(nullptr, nullptr) && !SkM44_notEquals(nullptr, nullptr), "SkM44_equals(nullptr)")) {
        return 4;
    }
    if (!check(SkM44_rc(nullptr, 0, 0) == 0.0f && SkM44_rc(nullptr, 4, 0) == 0.0f, "SkM44_rc(nullptr/index)")) {
        return 5;
    }
    const sk_v4_t null_row = SkM44_row(nullptr, 0);
    if (!check(static_sk_v4_get_ptr(null_row) != nullptr, "SkM44_row(nullptr)")) {
        return 6;
    }
    static_sk_v4_delete(null_row);
    const sk_v4_t bad_col = SkM44_col(nullptr, 4);
    if (!check(static_sk_v4_get_ptr(bad_col) != nullptr, "SkM44_col(bad index)")) {
        return 7;
    }
    static_sk_v4_delete(bad_col);
    if (!check(SkM44_setIdentity(nullptr) == 0, "SkM44_setIdentity(nullptr)")) {
        return 8;
    }
    if (!check(SkM44_setConcat(nullptr, nullptr, nullptr) == 0, "SkM44_setConcat(nullptr)")) {
        return 9;
    }
    if (!check(SkM44_preConcat(nullptr, nullptr) == 0 && SkM44_postConcat(nullptr, nullptr) == 0, "SkM44_concat(nullptr)")) {
        return 10;
    }
    if (!check(!SkM44_isFinite(nullptr), "SkM44_isFinite(nullptr)")) {
        return 11;
    }
    if (!check(!SkM44_invert(nullptr, nullptr), "SkM44_invert(nullptr)")) {
        return 12;
    }
    if (!check(SkM44_transpose(nullptr) == 0, "SkM44_transpose(nullptr)")) {
        return 13;
    }
    const sk_v4_t null_map = SkM44_map(nullptr, 1.0f, 2.0f, 3.0f, 1.0f);
    if (!check(static_sk_v4_get_ptr(null_map) != nullptr, "SkM44_map(nullptr)")) {
        return 14;
    }
    static_sk_v4_delete(null_map);
    if (!check(SkM44_asM33(nullptr) == 0, "SkM44_asM33(nullptr)")) {
        return 15;
    }
    if (!check(SkM44_Rows(nullptr, nullptr, nullptr, nullptr) == 0, "SkM44_Rows(nullptr)")) {
        return 16;
    }
    if (!check(SkM44_Cols(nullptr, nullptr, nullptr, nullptr) == 0, "SkM44_Cols(nullptr)")) {
        return 17;
    }
    if (!check(SkM44_RowMajor(nullptr) == 0 && SkM44_ColMajor(nullptr) == 0, "SkM44_major(nullptr)")) {
        return 18;
    }
    if (!check(SkM44_RectToRect(nullptr, nullptr) == 0, "SkM44_RectToRect(nullptr)")) {
        return 19;
    }
    if (!check(SkM44_LookAt(nullptr, nullptr, nullptr) == 0, "SkM44_LookAt(nullptr)")) {
        return 20;
    }

    reskia_m_44_t *m44 = SkM44_newDefault();
    if (!check(m44 != nullptr && SkM44_isFinite(m44), "SkM44_newDefault(valid)")) {
        return 21;
    }
    float row_major[16] = {};
    SkM44_getRowMajor(m44, row_major);
    if (!check(row_major[0] == 1.0f && row_major[5] == 1.0f && row_major[10] == 1.0f && row_major[15] == 1.0f, "SkM44_getRowMajor(valid)")) {
        SkM44_delete(m44);
        return 22;
    }
    if (!check(SkM44_rc(m44, 0, 0) == 1.0f, "SkM44_rc(valid)")) {
        SkM44_delete(m44);
        return 23;
    }
    SkM44_setRC(m44, 0, 3, 5.0f);
    if (!check(SkM44_rc(m44, 0, 3) == 5.0f, "SkM44_setRC(valid)")) {
        SkM44_delete(m44);
        return 24;
    }
    const sk_v4_t row = SkM44_row(m44, 0);
    auto *row_ptr = static_cast<const reskia_v4_t *>(static_sk_v4_get_ptr(row));
    if (!check(row_ptr != nullptr, "SkM44_row(valid)")) {
        static_sk_v4_delete(row);
        SkM44_delete(m44);
        return 25;
    }
    SkM44_setCol(m44, 1, row_ptr);
    static_sk_v4_delete(row);

    const sk_m_44_t translated = SkM44_Translate(1.0f, 2.0f, 3.0f);
    auto *translated_ptr = static_cast<reskia_m_44_t *>(static_sk_m_44_get_ptr(translated));
    if (!check(translated_ptr != nullptr && SkM44_rc(translated_ptr, 0, 3) == 1.0f, "SkM44_Translate(valid)")) {
        static_sk_m_44_delete(translated);
        SkM44_delete(m44);
        return 26;
    }
    const sk_m_44_t as_transpose = SkM44_transpose(translated_ptr);
    if (!check(as_transpose != 0 && static_sk_m_44_get_ptr(as_transpose) != nullptr, "SkM44_transpose(valid)")) {
        static_sk_m_44_delete(as_transpose);
        static_sk_m_44_delete(translated);
        SkM44_delete(m44);
        return 27;
    }
    static_sk_m_44_delete(as_transpose);

    const sk_matrix_t as_m33 = SkM44_asM33(translated_ptr);
    if (!check(as_m33 != 0 && static_sk_matrix_get_ptr(as_m33) != nullptr, "SkM44_asM33(valid)")) {
        static_sk_matrix_delete(as_m33);
        static_sk_m_44_delete(translated);
        SkM44_delete(m44);
        return 28;
    }
    static_sk_matrix_delete(as_m33);

    float values[16] = {};
    values[0] = 1.0f;
    values[5] = 1.0f;
    values[10] = 1.0f;
    values[15] = 1.0f;
    const sk_m_44_t row_major_handle = SkM44_RowMajor(values);
    if (!check(row_major_handle != 0 && static_sk_m_44_get_ptr(row_major_handle) != nullptr, "SkM44_RowMajor(valid)")) {
        static_sk_m_44_delete(row_major_handle);
        static_sk_m_44_delete(translated);
        SkM44_delete(m44);
        return 29;
    }
    static_sk_m_44_delete(row_major_handle);

    const sk_rect_t src_handle = SkRect_MakeXYWH(0.0f, 0.0f, 2.0f, 2.0f);
    const sk_rect_t dst_handle = SkRect_MakeXYWH(0.0f, 0.0f, 4.0f, 4.0f);
    auto *src = static_cast<const reskia_rect_t *>(static_sk_rect_get_ptr(src_handle));
    auto *dst = static_cast<const reskia_rect_t *>(static_sk_rect_get_ptr(dst_handle));
    const sk_m_44_t rect_to_rect = SkM44_RectToRect(src, dst);
    if (!check(rect_to_rect != 0 && static_sk_m_44_get_ptr(rect_to_rect) != nullptr, "SkM44_RectToRect(valid)")) {
        static_sk_m_44_delete(rect_to_rect);
        static_sk_rect_delete(dst_handle);
        static_sk_rect_delete(src_handle);
        static_sk_m_44_delete(translated);
        SkM44_delete(m44);
        return 30;
    }
    static_sk_m_44_delete(rect_to_rect);
    static_sk_rect_delete(dst_handle);
    static_sk_rect_delete(src_handle);

    static_sk_m_44_delete(translated);
    SkM44_delete(m44);
    return 0;
}
