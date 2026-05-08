#include "capi/sk_paint.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[paint-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkPaint_newWithColor4fAndColorSpace(nullptr, nullptr) == nullptr, "SkPaint_newWithColor4fAndColorSpace(nullptr)")) {
        return 1;
    }
    if (!check(SkPaint_newCopy(nullptr) == nullptr, "SkPaint_newCopy(nullptr)")) {
        return 2;
    }
    if (!check(!SkPaint_isAntiAlias(nullptr), "SkPaint_isAntiAlias(nullptr)")) {
        return 3;
    }
    if (!check(!SkPaint_isDither(nullptr), "SkPaint_isDither(nullptr)")) {
        return 4;
    }
    if (!check(SkPaint_getStyle(nullptr) == 0, "SkPaint_getStyle(nullptr)")) {
        return 5;
    }
    if (!check(SkPaint_getColor(nullptr) == 0, "SkPaint_getColor(nullptr)")) {
        return 6;
    }
    if (!check(SkPaint_getColor4f(nullptr) == 0, "SkPaint_getColor4f(nullptr)")) {
        return 7;
    }
    if (!check(SkPaint_getAlpha(nullptr) == 0, "SkPaint_getAlpha(nullptr)")) {
        return 8;
    }
    if (!check(SkPaint_getStrokeWidth(nullptr) == 0.0f, "SkPaint_getStrokeWidth(nullptr)")) {
        return 9;
    }
    if (!check(SkPaint_getShader(nullptr) == nullptr, "SkPaint_getShader(nullptr)")) {
        return 10;
    }
    if (!check(SkPaint_refShader(nullptr) == 0, "SkPaint_refShader(nullptr)")) {
        return 11;
    }
    if (!check(SkPaint_asBlendMode(nullptr) == 0, "SkPaint_asBlendMode(nullptr)")) {
        return 12;
    }
    if (!check(SkPaint_getBlendMode_or(nullptr, 1) == 1, "SkPaint_getBlendMode_or(nullptr)")) {
        return 13;
    }
    if (!check(SkPaint_nothingToDraw(nullptr), "SkPaint_nothingToDraw(nullptr)")) {
        return 14;
    }
    if (!check(!SkPaint_canComputeFastBounds(nullptr), "SkPaint_canComputeFastBounds(nullptr)")) {
        return 15;
    }
    if (!check(SkPaint_computeFastBounds(nullptr, nullptr, nullptr) == nullptr, "SkPaint_computeFastBounds(nullptr)")) {
        return 16;
    }

    SkPaint_reset(nullptr);
    SkPaint_setAntiAlias(nullptr, true);
    SkPaint_setDither(nullptr, true);
    SkPaint_setStyle(nullptr, 0);
    SkPaint_setStroke(nullptr, true);
    SkPaint_setColor(nullptr, 0);
    SkPaint_setColor4f(nullptr, nullptr, nullptr);
    SkPaint_setAlpha(nullptr, 255);
    SkPaint_setStrokeWidth(nullptr, 1.0f);
    SkPaint_setShader(nullptr, 0);
    SkPaint_setColorFilter(nullptr, 0);
    SkPaint_setBlendMode(nullptr, 0);
    SkPaint_setBlender(nullptr, 0);
    SkPaint_setPathEffect(nullptr, 0);
    SkPaint_setMaskFilter(nullptr, 0);
    SkPaint_setImageFilter(nullptr, 0);

    reskia_paint_t *paint = SkPaint_new();
    if (!check(paint != nullptr, "SkPaint_new")) {
        return 17;
    }

    SkPaint_setColor4f(paint, nullptr, nullptr);
    if (!check(SkPaint_computeFastBounds(paint, nullptr, nullptr) == nullptr, "SkPaint_computeFastBounds(paint, nullptr)")) {
        SkPaint_delete(paint);
        return 18;
    }
    if (!check(SkPaint_computeFastStrokeBounds(paint, nullptr, nullptr) == nullptr, "SkPaint_computeFastStrokeBounds(paint, nullptr)")) {
        SkPaint_delete(paint);
        return 19;
    }
    if (!check(SkPaint_doComputeFastBounds(paint, nullptr, nullptr, 0) == nullptr, "SkPaint_doComputeFastBounds(paint, nullptr)")) {
        SkPaint_delete(paint);
        return 20;
    }

    SkPaint_delete(paint);
    return 0;
}
