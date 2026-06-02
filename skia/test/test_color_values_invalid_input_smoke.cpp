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
    if (!check(SkColor4f_equals(nullptr, nullptr), "SkColor4f_equals(nullptr, nullptr)")) {
        return 7;
    }
    if (!check(!SkColor4f_notEquals(nullptr, nullptr), "SkColor4f_notEquals(nullptr, nullptr)")) {
        return 8;
    }
    if (!check(SkColor4f_mulScalar(nullptr, 2.0f) == 0, "SkColor4f_mulScalar(nullptr)")) {
        return 9;
    }
    if (!check(SkColor4f_mulColor(nullptr, nullptr) == 0, "SkColor4f_mulColor(nullptr)")) {
        return 10;
    }
    if (!check(SkColor4f_get(nullptr, 0) == 0.0f, "SkColor4f_get(nullptr)")) {
        return 11;
    }
    SkColor4f_set(nullptr, 0, 1.0f);
    float color_array[4] = {};
    if (!check(!SkColor4f_toArray(nullptr, color_array), "SkColor4f_toArray(nullptr)")) {
        return 12;
    }
    if (!check(!SkColor4f_toArray(nullptr, nullptr), "SkColor4f_toArray(null out)")) {
        return 13;
    }
    if (!check(!SkColor4f_isOpaque(nullptr), "SkColor4f_isOpaque(nullptr)")) {
        return 14;
    }
    if (!check(!SkColor4f_fitsInBytes(nullptr), "SkColor4f_fitsInBytes(nullptr)")) {
        return 15;
    }
    if (!check(SkColor4f_toSkColor(nullptr) == 0, "SkColor4f_toSkColor(nullptr)")) {
        return 16;
    }
    if (!check(SkColor4f_toBytes_RGBA(nullptr) == 0, "SkColor4f_toBytes_RGBA(nullptr)")) {
        return 17;
    }
    if (!check(SkColor4f_makeOpaque(nullptr) == 0, "SkColor4f_makeOpaque(nullptr)")) {
        return 18;
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
        return 19;
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
        return 20;
    }
    SkColorMatrix_setRowMajor(matrix, nullptr);
    SkColorMatrix_getRowMajor(matrix, nullptr);

    const sk_color_matrix_t rgb_to_yuv = SkColorMatrix_RGBtoYUV(0);
    if (!check(static_sk_color_matrix_get_ptr(rgb_to_yuv) != nullptr, "SkColorMatrix_RGBtoYUV")) {
        SkColorMatrix_delete(matrix);
        return 21;
    }

    const sk_color_4f_t color_handle = SkColor4f_FromColor(0xff112233);
    auto *color = static_cast<reskia_color_4f_t *>(static_sk_color_4f_get_ptr(color_handle));
    if (!check(color != nullptr, "SkColor4f_FromColor")) {
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 22;
    }
    if (!check(!SkColor4f_equals(color, nullptr), "SkColor4f_equals(valid, nullptr)")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 23;
    }
    if (!check(SkColor4f_notEquals(color, nullptr), "SkColor4f_notEquals(valid, nullptr)")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 24;
    }
    if (!check(SkColor4f_get(color, -1) == 0.0f && SkColor4f_get(color, 4) == 0.0f, "SkColor4f_get(out of range)")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 25;
    }
    const float previous_r = SkColor4f_fR(color);
    SkColor4f_set(color, 0, 0.25f);
    if (!check(SkColor4f_get(color, 0) == 0.25f, "SkColor4f_set/get")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 26;
    }
    SkColor4f_set(color, -1, 0.5f);
    SkColor4f_set(color, 4, 0.5f);
    if (!check(SkColor4f_get(color, 0) == 0.25f, "SkColor4f_set(out of range)")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 27;
    }
    SkColor4f_set(color, 0, previous_r);
    if (!check(SkColor4f_toArray(color, color_array) && color_array[3] == SkColor4f_fA(color), "SkColor4f_toArray(valid)")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 28;
    }
    if (!check(SkColor4f_fA(color) == 1.0f, "SkColor4f_fA(valid)")) {
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 29;
    }
    const sk_color_4f_t scaled_handle = SkColor4f_mulScalar(color, 0.5f);
    auto *scaled = static_cast<reskia_color_4f_t *>(static_sk_color_4f_get_ptr(scaled_handle));
    if (!check(scaled != nullptr && SkColor4f_fA(scaled) == 0.5f, "SkColor4f_mulScalar(valid)")) {
        static_sk_color_4f_delete(scaled_handle);
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 30;
    }
    const sk_color_4f_t product_handle = SkColor4f_mulColor(color, scaled);
    auto *product = static_cast<reskia_color_4f_t *>(static_sk_color_4f_get_ptr(product_handle));
    if (!check(product != nullptr && SkColor4f_fA(product) == 0.5f, "SkColor4f_mulColor(valid)")) {
        static_sk_color_4f_delete(product_handle);
        static_sk_color_4f_delete(scaled_handle);
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 31;
    }
    const sk_color_4f_t opaque = SkColor4f_makeOpaque(color);
    if (!check(static_sk_color_4f_get_ptr(opaque) != nullptr, "SkColor4f_makeOpaque(valid)")) {
        static_sk_color_4f_delete(product_handle);
        static_sk_color_4f_delete(scaled_handle);
        static_sk_color_4f_delete(color_handle);
        static_sk_color_matrix_delete(rgb_to_yuv);
        SkColorMatrix_delete(matrix);
        return 32;
    }

    static_sk_color_4f_delete(opaque);
    static_sk_color_4f_delete(product_handle);
    static_sk_color_4f_delete(scaled_handle);
    static_sk_color_4f_delete(color_handle);
    static_sk_color_matrix_delete(rgb_to_yuv);
    SkColorMatrix_delete(matrix);
    return 0;
}
