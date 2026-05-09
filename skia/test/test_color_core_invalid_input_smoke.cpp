#include "capi/sk_color.h"
#include "capi/sk_color_priv.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[color-core-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkColor_SkColorToHSV(0xff112233, nullptr);
    SkColor_SkRGBToHSV(0x11, 0x22, 0x33, nullptr);
    if (!check(SkColor_SkHSVToColor(nullptr) == 0, "SkColor_SkHSVToColor(nullptr)")) {
        return 1;
    }
    if (!check(SkColor_SkHSVToColorWithAlpha(0xff, nullptr) == 0, "SkColor_SkHSVToColorWithAlpha(nullptr)")) {
        return 2;
    }

    float hsv[3] = {};
    SkColor_SkColorToHSV(0xffff0000, hsv);
    if (!check(hsv[0] == 0.0f && hsv[1] == 1.0f && hsv[2] == 1.0f, "SkColor_SkColorToHSV(red)")) {
        return 3;
    }
    if (!check(SkColor_SkHSVToColor(hsv) == 0xffff0000, "SkColor_SkHSVToColor(red)")) {
        return 4;
    }
    if (!check(SkColor_SkHSVToColorWithAlpha(0x80, hsv) == 0x80ff0000, "SkColor_SkHSVToColorWithAlpha(red)")) {
        return 5;
    }
    SkColor_SkRGBToHSV(0, 255, 0, hsv);
    if (!check(hsv[0] == 120.0f && hsv[1] == 1.0f && hsv[2] == 1.0f, "SkColor_SkRGBToHSV(green)")) {
        return 6;
    }
    if (!check(SkColor_SkColorSetA(0x00112233, 0xff) == 0xff112233, "SkColor_SkColorSetA")) {
        return 7;
    }
    if (!check(SkColor_SkColorSetARGB(0xff, 0x11, 0x22, 0x33) == 0xff112233, "SkColor_SkColorSetARGB")) {
        return 8;
    }
    if (!check(SkColor_SkPreMultiplyColor(0xffff0000) == SkColor_SkPreMultiplyARGB(0xff, 0xff, 0, 0), "SkColor_SkPreMultiplyColor")) {
        return 9;
    }
    if (!check(SkColorPriv_SkAlpha255To256(255) == 256, "SkColorPriv_SkAlpha255To256")) {
        return 10;
    }
    if (!check(SkColorPriv_SkUnitScalarClampToByte(1.0f) == 255, "SkColorPriv_SkUnitScalarClampToByte")) {
        return 11;
    }
    return 0;
}
