#include "capi/sk_color_4f.h"
#include "capi/sk_color_matrix.h"
#include "handles/static_sk_color_4f.h"
#include "handles/static_sk_color_matrix.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[color-values-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkColor4f_delete(nullptr);
    if (!check(SkColor4f_fR(nullptr) == 0.0f, "SkColor4f_fR(nullptr)")) {
        return 1;
    }
    if (!check(SkColor4f_fG(nullptr) == 0.0f, "SkColor4f_fG(nullptr)")) {
        return 2;
    }
    if (!check(SkColor4f_fB(nullptr) == 0.0f, "SkColor4f_fB(nullptr)")) {
        return 3;
    }
    if (!check(SkColor4f_fA(nullptr) == 0.0f, "SkColor4f_fA(nullptr)")) {
        return 4;
    }
    if (!check(SkColor4f_vec(nullptr) == nullptr, "SkColor4f_vec(nullptr)")) {
        return 5;
    }
    if (!check(SkColor4f_vecMutable(nullptr) == nullptr, "SkColor4f_vecMutable(nullptr)")) {
        return 6;
    }
    if (!check(!SkColor4f_isOpaque(nullptr), "SkColor4f_isOpaque(nullptr)")) {
        return 7;
    }
    if (!check(!SkColor4f_fitsInBytes(nullptr), "SkColor4f_fitsInBytes(nullptr)")) {
        return 8;
    }
    if (!check(SkColor4f_toSkColor(nullptr) == 0, "SkColor4f_toSkColor(nullptr)")) {
        return 9;
    }
    if (!check(SkColor4f_toBytes_RGBA(nullptr) == 0, "SkColor4f_toBytes_RGBA(nullptr)")) {
        return 10;
    }
    if (!check(SkColor4f_makeOpaque(nullptr) == 0, "SkColor4f_makeOpaque(nullptr)")) {
        return 11;
    }

    SkColorMatrix_delete(nullptr);
    SkColorMatrix_setIdentity(nullptr);
    SkColorMatrix_setScale(nullptr, 1.0f, 1.0f, 1.0f, 1.0f);
    SkColorMatrix_postTranslate(nullptr, 0.0f, 0.0f, 0.0f, 0.0f);
    SkColorMatrix_setConcat(nullptr, nullptr, nullptr);
    SkColorMatrix_preConcat(nullptr, nullptr);
    SkColorMatrix_postConcat(nullptr, nullptr);
    SkColorMatrix_setSaturation(nullptr, 1.0f);
    SkColorMatrix_setRowMajor(nullptr, nullptr);
    SkColorMatrix_getRowMajor(nullptr, nullptr);

    reskia_color_matrix_t *matrix = SkColorMatrix_new();
    if (!check(matrix != nullptr, "SkColorMatrix_new")) {
        return 12;
    }
    float identity[20] = {
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    };
    float out[20] = {};
    SkColorMatrix_setRowMajor(matrix, identity);
    SkColorMatrix_getRowMajor(matrix, out);
    if (!check(out[0] == 1.0f && out[6] == 1.0f && out[12] == 1.0f && out[18] == 1.0f, "SkColorMatrix row major roundtrip")) {
        SkColorMatrix_delete(matrix);
        return 13;
    }
    SkColorMatrix_setRowMajor(matrix, nullptr);
    SkColorMatrix_getRowMajor(matrix, nullptr);

    const sk_color_matrix_t rgb_to_yuv = SkColorMatrix_RGBtoYUV(0);
    if (!check(static_sk_color_matrix_get_ptr(rgb_to_yuv) != nullptr, "SkColorMatrix_RGBtoYUV")) {
        SkColorMatrix_delete(matrix);
        return 14;
    }

    const sk_color_4f_t color_handle = SkColor4f_FromColor(0xff112233);
    auto *color = static_cast<reskia_color_4f_t *>(static_sk_color_4f_get_ptr(color_handle));
    if (!check(color != nullptr, "SkColor4f_FromColor")) {
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 15;
    }
    if (!check(SkColor4f_fA(color) == 1.0f, "SkColor4f_fA(valid)")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 16;
    }
    const sk_color_4f_t opaque = SkColor4f_makeOpaque(color);
    if (!check(static_sk_color_4f_get_ptr(opaque) != nullptr, "SkColor4f_makeOpaque(valid)")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 17;
    }

    static_sk_color_4f_delete(opaque);
    static_sk_color_4f_delete(color_handle);
    static_sk_color_matrix_delete(rgb_to_yuv);
    SkColorMatrix_delete(matrix);
    return 0;
}
