#include "capi/sk_matrix.h"
#include "capi/sk_rect.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_point.h"
#include "handles/static_sk_rect.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[matrix-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkMatrix_delete(nullptr);
    SkMatrix_normalizePerspective(nullptr);
    SkMatrix_mapPoints(nullptr, nullptr, nullptr, 1);
    SkMatrix_mapPointsInPlace(nullptr, nullptr, 1);
    SkMatrix_mapHomogeneousPoints(nullptr, nullptr, nullptr, 1);
    SkMatrix_mapHomogeneousPointsFromPoints(nullptr, nullptr, nullptr, 1);
    SkMatrix_mapVectors(nullptr, nullptr, nullptr, 1);
    SkMatrix_mapVectorsInPlace(nullptr, nullptr, 1);
    SkMatrix_mapVector(nullptr, 1.0f, 2.0f, nullptr);
    SkMatrix_mapRectToQuad(nullptr, nullptr, nullptr);
    SkMatrix_mapRectScaleTranslate(nullptr, nullptr, nullptr);
    SkMatrix_dump(nullptr);
    SkMatrix_dirtyMatrixTypeCache(nullptr);
    SkMatrix_setScaleTranslate(nullptr, 1.0f, 1.0f, 0.0f, 0.0f);
    SkMatrix_SetAffineIdentity(nullptr);

    if (!check(SkMatrix_new(nullptr) == nullptr, "SkMatrix_new(nullptr)")) {
        return 1;
    }
    if (!check(SkMatrix_getType(nullptr) == -1, "SkMatrix_getType(nullptr)")) {
        return 2;
    }
    if (!check(!SkMatrix_isIdentity(nullptr), "SkMatrix_isIdentity(nullptr)")) {
        return 3;
    }
    if (!check(!SkMatrix_isScaleTranslate(nullptr), "SkMatrix_isScaleTranslate(nullptr)")) {
        return 4;
    }
    if (!check(!SkMatrix_hasPerspective(nullptr), "SkMatrix_hasPerspective(nullptr)")) {
        return 5;
    }
    if (!check(SkMatrix_get(nullptr, 0) == 0.0f && SkMatrix_get(nullptr, 9) == 0.0f, "SkMatrix_get(nullptr/index)")) {
        return 6;
    }
    if (!check(SkMatrix_rc(nullptr, 0, 0) == 0.0f && SkMatrix_rc(nullptr, 3, 0) == 0.0f, "SkMatrix_rc(nullptr/index)")) {
        return 7;
    }
    if (!check(SkMatrix_set(nullptr, 0, 1.0f) == 0 && SkMatrix_set(nullptr, 9, 1.0f) == 0, "SkMatrix_set(nullptr/index)")) {
        return 8;
    }
    if (!check(SkMatrix_set9(nullptr, nullptr) == 0, "SkMatrix_set9(nullptr)")) {
        return 9;
    }
    if (!check(SkMatrix_setTranslateWithVector(nullptr, nullptr) == 0, "SkMatrix_setTranslateWithVector(nullptr)")) {
        return 10;
    }
    if (!check(SkMatrix_setConcat(nullptr, nullptr, nullptr) == 0, "SkMatrix_setConcat(nullptr)")) {
        return 11;
    }
    if (!check(!SkMatrix_setRectToRect(nullptr, nullptr, nullptr, 0), "SkMatrix_setRectToRect(nullptr)")) {
        return 12;
    }
    if (!check(!SkMatrix_setPolyToPoly(nullptr, nullptr, nullptr, 0), "SkMatrix_setPolyToPoly(nullptr)")) {
        return 13;
    }
    if (!check(!SkMatrix_invert(nullptr, nullptr), "SkMatrix_invert(nullptr)")) {
        return 14;
    }
    if (!check(!SkMatrix_asAffine(nullptr, nullptr), "SkMatrix_asAffine(nullptr)")) {
        return 15;
    }
    if (!check(SkMatrix_setAffine(nullptr, nullptr) == 0, "SkMatrix_setAffine(nullptr)")) {
        return 16;
    }
    if (!check(!SkMatrix_mapRect(nullptr, nullptr, nullptr, 0), "SkMatrix_mapRect(nullptr)")) {
        return 17;
    }
    if (!check(!SkMatrix_mapRectInPlace(nullptr, nullptr, 0), "SkMatrix_mapRectInPlace(nullptr)")) {
        return 18;
    }
    const sk_rect_t empty_rect = SkMatrix_mapRectFromSource(nullptr, nullptr, 0);
    if (!check(static_sk_rect_get_ptr(empty_rect) != nullptr, "SkMatrix_mapRectFromSource(nullptr)")) {
        return 19;
    }
    static_sk_rect_delete(empty_rect);
    if (!check(SkMatrix_mapRadius(nullptr, 2.0f) == 0.0f, "SkMatrix_mapRadius(nullptr)")) {
        return 20;
    }
    if (!check(SkMatrix_getMinScale(nullptr) == -1.0f && SkMatrix_getMaxScale(nullptr) == -1.0f, "SkMatrix_getMinMax(nullptr)")) {
        return 21;
    }
    if (!check(!SkMatrix_getMinMaxScales(nullptr, nullptr), "SkMatrix_getMinMaxScales(nullptr)")) {
        return 22;
    }
    if (!check(!SkMatrix_decomposeScale(nullptr, nullptr, nullptr), "SkMatrix_decomposeScale(nullptr)")) {
        return 23;
    }
    if (!check(!SkMatrix_isFinite(nullptr), "SkMatrix_isFinite(nullptr)")) {
        return 24;
    }
    if (!check(SkMatrix_RectToRect(nullptr, nullptr, 0) == 0 && SkMatrix_MakeRectToRect(nullptr, nullptr, 0) == 0, "SkMatrix static rect null")) {
        return 25;
    }
    if (!check(SkMatrix_Concat(nullptr, nullptr) == 0, "SkMatrix_Concat(nullptr)")) {
        return 26;
    }

    const sk_matrix_t identity_handle = SkMatrix_I();
    auto *identity = static_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(identity_handle));
    if (!check(identity != nullptr && SkMatrix_isIdentity(identity), "SkMatrix_I(valid)")) {
        return 27;
    }

    float values[9] = {};
    SkMatrix_get9(identity, values);
    if (!check(values[0] == 1.0f && values[4] == 1.0f && values[8] == 1.0f, "SkMatrix_get9(valid)")) {
        static_sk_matrix_delete(identity_handle);
        return 28;
    }
    values[2] = 3.0f;
    const sk_matrix_t set9_handle = SkMatrix_set9(identity, values);
    auto *set9 = static_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(set9_handle));
    if (!check(set9 != nullptr && SkMatrix_getTranslateX(set9) == 3.0f, "SkMatrix_set9(valid)")) {
        static_sk_matrix_delete(set9_handle);
        static_sk_matrix_delete(identity_handle);
        return 29;
    }

    const sk_point_t mapped_point = SkMatrix_mapXYToPoint(set9, 2.0f, 4.0f);
    if (!check(static_sk_point_get_ptr(mapped_point) != nullptr, "SkMatrix_mapXYToPoint(valid)")) {
        static_sk_point_delete(mapped_point);
        static_sk_matrix_delete(set9_handle);
        static_sk_matrix_delete(identity_handle);
        return 30;
    }
    static_sk_point_delete(mapped_point);

    const sk_rect_t src_handle = SkRect_MakeXYWH(0.0f, 0.0f, 2.0f, 2.0f);
    const sk_rect_t dst_handle = SkRect_MakeXYWH(0.0f, 0.0f, 4.0f, 4.0f);
    auto *src = static_cast<const reskia_rect_t *>(static_sk_rect_get_ptr(src_handle));
    auto *dst = static_cast<reskia_rect_t *>(static_sk_rect_get_ptr(dst_handle));
    if (!check(src != nullptr && dst != nullptr && SkMatrix_mapRect(set9, dst, src, 0), "SkMatrix_mapRect(valid)")) {
        static_sk_rect_delete(dst_handle);
        static_sk_rect_delete(src_handle);
        static_sk_matrix_delete(set9_handle);
        static_sk_matrix_delete(identity_handle);
        return 31;
    }

    float affine[6] = {};
    if (!check(SkMatrix_asAffine(set9, affine), "SkMatrix_asAffine(valid)")) {
        static_sk_rect_delete(dst_handle);
        static_sk_rect_delete(src_handle);
        static_sk_matrix_delete(set9_handle);
        static_sk_matrix_delete(identity_handle);
        return 32;
    }

    static_sk_rect_delete(dst_handle);
    static_sk_rect_delete(src_handle);
    static_sk_matrix_delete(set9_handle);
    static_sk_matrix_delete(identity_handle);
    return 0;
}
