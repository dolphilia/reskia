#include "capi/sk_r_rect.h"
#include "capi/sk_rect.h"

#include <cstdio>
#include <limits>
#include "include/core/SkPoint.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[rect-rrect-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkRect_isEmpty(nullptr), "SkRect_isEmpty(nullptr)")) {
        return 1;
    }
    if (!check(!SkRect_isFinite(nullptr), "SkRect_isFinite(nullptr)")) {
        return 2;
    }
    if (!check(SkRect_width(nullptr) == 0.0f, "SkRect_width(nullptr)")) {
        return 3;
    }
    if (!check(SkRect_center(nullptr) == 0, "SkRect_center(nullptr)")) {
        return 4;
    }
    if (!check(SkRect_makeInset(nullptr, 1.0f, 1.0f) == 0, "SkRect_makeInset(nullptr)")) {
        return 5;
    }
    if (!check(!SkRect_intersect(nullptr, nullptr), "SkRect_intersect(nullptr)")) {
        return 6;
    }
    if (!check(SkRect_asScalars(nullptr) == nullptr, "SkRect_asScalars(nullptr)")) {
        return 7;
    }
    if (!check(SkRect_MakeSize(nullptr) == 0, "SkRect_MakeSize(nullptr)")) {
        return 8;
    }
    if (!check(!SkRect_Intersects(nullptr, nullptr), "SkRect_Intersects(nullptr)")) {
        return 9;
    }

    SkRect_toQuad(nullptr, nullptr);
    SkRect_setEmpty(nullptr);
    SkRect_setBounds(nullptr, nullptr, 0);
    SkRect_offset(nullptr, 1.0f, 2.0f);
    SkRect_round(nullptr, nullptr);
    SkRect_dumpDefault(nullptr);

    const sk_rect_t rect_handle = SkRect_MakeLTRB(0.0f, 0.0f, 10.0f, 10.0f);
    auto *rect = static_cast<reskia_rect_t *>(static_sk_rect_get_ptr(rect_handle));
    if (!check(rect != nullptr, "SkRect_MakeLTRB")) {
        return 10;
    }

    if (!check(!SkRect_setBoundsCheck(rect, nullptr, 1), "SkRect_setBoundsCheck(rect, nullptr, 1)")) {
        static_sk_rect_delete(rect_handle);
        return 11;
    }
    SkRect_set(nullptr, nullptr);
    SkRect_setFromPoints(rect, nullptr, nullptr);
    SkRect_offsetByPoint(rect, nullptr);
    SkRect_join(rect, nullptr);

    if (!check(SkRRect_newCopy(nullptr) == nullptr, "SkRRect_newCopy(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 12;
    }
    if (!check(SkRRect_isEmpty(nullptr), "SkRRect_isEmpty(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 13;
    }
    if (!check(!SkRRect_isValid(nullptr), "SkRRect_isValid(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 14;
    }
    if (!check(SkRRect_rect(nullptr) == nullptr, "SkRRect_rect(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 15;
    }
    if (!check(SkRRect_makeOffset(nullptr, 1.0f, 2.0f) == 0, "SkRRect_makeOffset(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 16;
    }
    if (!check(SkRRect_writeToMemory(nullptr, nullptr) == 0, "SkRRect_writeToMemory(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 17;
    }
    if (!check(SkRRect_readFromMemory(nullptr, nullptr, 0) == 0, "SkRRect_readFromMemory(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 18;
    }
    if (!check(!SkRRect_transform(nullptr, nullptr, nullptr), "SkRRect_transform(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 19;
    }
    if (!check(SkRRect_MakeRect(nullptr) == 0, "SkRRect_MakeRect(nullptr)")) {
        static_sk_rect_delete(rect_handle);
        return 20;
    }

    SkRRect_dumpDefault(nullptr);
    SkRRect_setRect(nullptr, nullptr);

    reskia_r_rect_t *rrect = SkRRect_new();
    if (!check(rrect != nullptr, "SkRRect_new")) {
        static_sk_rect_delete(rect_handle);
        return 21;
    }
    SkRRect_setRect(rrect, rect);
    if (!check(SkRRect_writeToMemory(rrect, nullptr) > 0, "SkRRect_writeToMemory(rrect, nullptr)")) {
        SkRRect_delete(rrect);
        static_sk_rect_delete(rect_handle);
        return 22;
    }
    if (!check(SkRRect_MakeRect(rect) != 0, "SkRRect_MakeRect(rect)")) {
        SkRRect_delete(rrect);
        static_sk_rect_delete(rect_handle);
        return 23;
    }

    SkRRect_setRectXY(rrect, rect, 2.0f, 2.0f);
    auto contains = [rrect](float x, float y) {
        const SkPoint point = SkPoint::Make(x, y);
        return SkRRect_containsPoint(rrect, reinterpret_cast<const reskia_point_t *>(&point));
    };
    if (!check(contains(5, 5), "rounded rect center") ||
        !check(contains(0, 5), "straight edge") ||
        !check(!contains(0, 0), "outside curved corner") ||
        !check(!contains(11, 5), "outside bounds") ||
        !check(!contains(std::numeric_limits<float>::quiet_NaN(), 5), "NaN point") ||
        !check(!SkRRect_containsPoint(rrect, nullptr), "NULL point") ||
        !check(!SkRRect_containsPoint(nullptr, nullptr), "NULL rrect")) {
        SkRRect_delete(rrect);
        static_sk_rect_delete(rect_handle);
        return 24;
    }
    SkRRect_setEmpty(rrect);
    if (!check(!contains(0, 0), "empty rounded rect")) {
        SkRRect_delete(rrect);
        static_sk_rect_delete(rect_handle);
        return 25;
    }

    SkRRect_delete(rrect);
    static_sk_rect_delete(rect_handle);
    return 0;
}
