#include "capi/sk_path.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[path-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkPath_newCopy(nullptr) == nullptr, "SkPath_newCopy(nullptr)")) {
        return 1;
    }
    if (!check(!SkPath_isInterpolatable(nullptr, nullptr), "SkPath_isInterpolatable(nullptr)")) {
        return 2;
    }
    if (!check(SkPath_interpolate(nullptr, nullptr, 0.5f, nullptr) == RESKIA_STATUS_INVALID_ARGUMENT, "SkPath_interpolate(nullptr)")) {
        return 3;
    }
    if (!check(SkPath_getFillType(nullptr) == 0, "SkPath_getFillType(nullptr)")) {
        return 4;
    }
    if (!check(SkPath_isEmpty(nullptr), "SkPath_isEmpty(nullptr)")) {
        return 5;
    }
    if (!check(!SkPath_isFinite(nullptr), "SkPath_isFinite(nullptr)")) {
        return 6;
    }
    if (!check(SkPath_countPoints(nullptr) == 0, "SkPath_countPoints(nullptr)")) {
        return 7;
    }
    if (!check(SkPath_getPoint(nullptr, 0) == 0, "SkPath_getPoint(nullptr)")) {
        return 8;
    }
    if (!check(SkPath_getBounds(nullptr) == nullptr, "SkPath_getBounds(nullptr)")) {
        return 9;
    }
    if (!check(SkPath_moveTo(nullptr, 1.0f, 2.0f) == nullptr, "SkPath_moveTo(nullptr)")) {
        return 10;
    }
    if (!check(SkPath_writeToMemory(nullptr, nullptr) == 0, "SkPath_writeToMemory(nullptr)")) {
        return 11;
    }
    if (!check(SkPath_readFromMemory(nullptr, nullptr, 0) == 0, "SkPath_readFromMemory(nullptr)")) {
        return 12;
    }
    if (!check(SkPath_Rect(nullptr, 0, 0) == 0, "SkPath_Rect(nullptr)")) {
        return 13;
    }
    if (!check(SkPath_Make(nullptr, 1, nullptr, 0, nullptr, 0, 0, false) == 0, "SkPath_Make(missing points)")) {
        return 14;
    }
    if (!check(SkPath_Polygon(nullptr, 1, false, 0, false) == 0, "SkPath_Polygon(missing points)")) {
        return 15;
    }
    if (!check(SkPath_IsLineDegenerate(nullptr, nullptr, true), "SkPath_IsLineDegenerate(nullptr)")) {
        return 16;
    }

    reskia_path_t *path = SkPath_new();
    if (!check(path != nullptr, "SkPath_new")) {
        return 17;
    }

    if (!check(SkPath_moveToPoint(path, nullptr) == nullptr, "SkPath_moveToPoint(path, nullptr)")) {
        SkPath_delete(path);
        return 18;
    }
    if (!check(SkPath_addRect(path, nullptr, 0, 0) == nullptr, "SkPath_addRect(path, nullptr)")) {
        SkPath_delete(path);
        return 19;
    }
    if (!check(SkPath_addPoly(path, nullptr, 1, false) == nullptr, "SkPath_addPoly(path, nullptr, 1)")) {
        SkPath_delete(path);
        return 20;
    }
    SkPath_transform(path, nullptr, nullptr, 0);
    SkPath_transform(nullptr, nullptr, nullptr, 0);

    const size_t serialized_size = SkPath_writeToMemory(path, nullptr);
    if (!check(serialized_size > 0, "SkPath_writeToMemory(path, nullptr)")) {
        SkPath_delete(path);
        return 21;
    }

    SkPath_delete(path);
    return 0;
}
