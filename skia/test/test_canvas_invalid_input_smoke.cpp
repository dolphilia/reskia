#include "capi/sk_canvas.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[canvas-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(SkCanvas_getSaveCount(nullptr) == 0, "SkCanvas_getSaveCount(nullptr)")) {
        return 1;
    }
    if (!check(!SkCanvas_readPixels(nullptr, nullptr, 0, 0), "SkCanvas_readPixels(nullptr)")) {
        return 2;
    }
    if (!check(!SkCanvas_quickReject(nullptr, nullptr), "SkCanvas_quickReject(nullptr)")) {
        return 3;
    }
    if (!check(!SkCanvas_quickRejectRect(nullptr, nullptr), "SkCanvas_quickRejectRect(nullptr)")) {
        return 4;
    }

    SkCanvas_translate(nullptr, 1.0f, 1.0f);
    SkCanvas_drawPath(nullptr, nullptr, nullptr);
    SkCanvas_drawPoints(nullptr, 0, 1, nullptr, nullptr);
    SkCanvas_drawAtlas(nullptr, nullptr, nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr);
    SkCanvas_experimental_DrawEdgeAAImageSet(nullptr, nullptr, 1, nullptr, nullptr, nullptr, nullptr, 0);

    reskia_canvas_t *canvas = SkCanvas_new();
    if (!check(canvas != nullptr, "SkCanvas_new")) {
        return 5;
    }

    SkCanvas_translate(canvas, 1.0f, 1.0f);
    SkCanvas_drawPath(canvas, nullptr, nullptr);
    SkCanvas_drawPoints(canvas, 0, 1, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, nullptr, nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr);
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, nullptr, 1, nullptr, nullptr, nullptr, nullptr, 0);

    if (!check(!SkCanvas_readPixels(canvas, nullptr, 0, 0), "SkCanvas_readPixels(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 6;
    }
    if (!check(!SkCanvas_quickReject(canvas, nullptr), "SkCanvas_quickReject(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(!SkCanvas_quickRejectRect(canvas, nullptr), "SkCanvas_quickRejectRect(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 8;
    }

    SkCanvas_delete(canvas);
    return 0;
}
