#include "capi/sk_region.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[region-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkRegion_newCopy(nullptr) == nullptr, "SkRegion_newCopy(nullptr)")) {
        return 1;
    }
    if (!check(SkRegion_newFromIRect(nullptr) == nullptr, "SkRegion_newFromIRect(nullptr)")) {
        return 2;
    }
    if (!check(!SkRegion_equals(nullptr, nullptr), "SkRegion_equals(nullptr)")) {
        return 3;
    }
    if (!check(!SkRegion_notEquals(nullptr, nullptr), "SkRegion_notEquals(nullptr)")) {
        return 4;
    }
    if (!check(!SkRegion_set(nullptr, nullptr), "SkRegion_set(nullptr)")) {
        return 5;
    }
    if (!check(SkRegion_isEmpty(nullptr), "SkRegion_isEmpty(nullptr)")) {
        return 6;
    }
    if (!check(!SkRegion_isRect(nullptr), "SkRegion_isRect(nullptr)")) {
        return 7;
    }
    if (!check(!SkRegion_isComplex(nullptr), "SkRegion_isComplex(nullptr)")) {
        return 8;
    }
    if (!check(SkRegion_getBounds(nullptr) == nullptr, "SkRegion_getBounds(nullptr)")) {
        return 9;
    }
    if (!check(SkRegion_computeRegionComplexity(nullptr) == 0, "SkRegion_computeRegionComplexity(nullptr)")) {
        return 10;
    }
    if (!check(!SkRegion_getBoundaryPath(nullptr, nullptr), "SkRegion_getBoundaryPath(nullptr)")) {
        return 11;
    }
    if (!check(!SkRegion_setEmpty(nullptr), "SkRegion_setEmpty(nullptr)")) {
        return 12;
    }
    if (!check(!SkRegion_setRect(nullptr, nullptr), "SkRegion_setRect(nullptr)")) {
        return 13;
    }
    if (!check(!SkRegion_setRects(nullptr, nullptr, 0), "SkRegion_setRects(nullptr)")) {
        return 14;
    }
    if (!check(!SkRegion_setRegion(nullptr, nullptr), "SkRegion_setRegion(nullptr)")) {
        return 15;
    }
    if (!check(!SkRegion_setPath(nullptr, nullptr, nullptr), "SkRegion_setPath(nullptr)")) {
        return 16;
    }
    if (!check(!SkRegion_intersects(nullptr, nullptr), "SkRegion_intersects(nullptr)")) {
        return 17;
    }
    if (!check(!SkRegion_intersectsRegion(nullptr, nullptr), "SkRegion_intersectsRegion(nullptr)")) {
        return 18;
    }
    if (!check(!SkRegion_contains(nullptr, 0, 0), "SkRegion_contains(nullptr)")) {
        return 19;
    }
    if (!check(!SkRegion_containsIRect(nullptr, nullptr), "SkRegion_containsIRect(nullptr)")) {
        return 20;
    }
    if (!check(!SkRegion_containsRegion(nullptr, nullptr), "SkRegion_containsRegion(nullptr)")) {
        return 21;
    }
    if (!check(!SkRegion_quickContains(nullptr, nullptr), "SkRegion_quickContains(nullptr)")) {
        return 22;
    }
    if (!check(!SkRegion_quickReject(nullptr, nullptr), "SkRegion_quickReject(nullptr)")) {
        return 23;
    }
    if (!check(!SkRegion_quickRejectRegion(nullptr, nullptr), "SkRegion_quickRejectRegion(nullptr)")) {
        return 24;
    }
    if (!check(!SkRegion_op(nullptr, nullptr, 0), "SkRegion_op(nullptr)")) {
        return 25;
    }
    if (!check(!SkRegion_opWithRegion(nullptr, nullptr, 0), "SkRegion_opWithRegion(nullptr)")) {
        return 26;
    }
    if (!check(!SkRegion_opWithIRectAndRegion(nullptr, nullptr, nullptr, 0), "SkRegion_opWithIRectAndRegion(nullptr)")) {
        return 27;
    }
    if (!check(!SkRegion_opWithRegionAndIRect(nullptr, nullptr, nullptr, 0), "SkRegion_opWithRegionAndIRect(nullptr)")) {
        return 28;
    }
    if (!check(!SkRegion_op_5(nullptr, nullptr, nullptr, 0), "SkRegion_op_5(nullptr)")) {
        return 29;
    }
    if (!check(SkRegion_writeToMemory(nullptr, nullptr) == 0, "SkRegion_writeToMemory(nullptr)")) {
        return 30;
    }
    if (!check(SkRegion_readFromMemory(nullptr, nullptr, 0) == 0, "SkRegion_readFromMemory(nullptr)")) {
        return 31;
    }

    SkRegion_delete(nullptr);
    SkRegion_swap(nullptr, nullptr);
    SkRegion_translate(nullptr, 1, 2);
    SkRegion_translateToRegion(nullptr, 1, 2, nullptr);

    reskia_region_t *region = SkRegion_new();
    if (!check(region != nullptr, "SkRegion_new")) {
        return 32;
    }
    if (!check(!SkRegion_setRects(region, nullptr, -1), "SkRegion_setRects negative count")) {
        SkRegion_delete(region);
        return 33;
    }
    if (!check(!SkRegion_setRects(region, nullptr, 1), "SkRegion_setRects missing array")) {
        SkRegion_delete(region);
        return 34;
    }
    if (!check(!SkRegion_op(region, nullptr, 99), "SkRegion_op invalid op")) {
        SkRegion_delete(region);
        return 35;
    }
    if (!check(!SkRegion_readFromMemory(region, nullptr, 0), "SkRegion_readFromMemory missing buffer")) {
        SkRegion_delete(region);
        return 36;
    }
    SkRegion_translateToRegion(region, 1, 2, nullptr);
    SkRegion_delete(region);

    return 0;
}
