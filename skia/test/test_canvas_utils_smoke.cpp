#include <cstdio>

#include "capi/sk_bitmap.h"
#include "capi/sk_canvas.h"
#include "capi/sk_canvas_state_utils.h"
#include "capi/sk_i_rect.h"
#include "capi/sk_no_draw_canvas.h"
#include "capi/sk_nway_canvas.h"
#include "capi/sk_paint.h"
#include "capi/sk_rect.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_rect.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[canvas-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_no_draw_canvas() {
    reskia_no_draw_canvas_t *no_draw = SkNoDrawCanvas_new(64, 64);
    if (!check(no_draw != nullptr, "SkNoDrawCanvas_new")) {
        return false;
    }
    reskia_canvas_t *as_canvas = SkNoDrawCanvas_asCanvas(no_draw);
    if (!check(as_canvas != nullptr, "SkNoDrawCanvas_asCanvas")) {
        SkNoDrawCanvas_delete(no_draw);
        return false;
    }
    SkNoDrawCanvas_resetCanvas(no_draw, 32, 48);
    SkCanvas_clearColor(as_canvas, 0xffabcdef);

    sk_i_rect_t irect_handle = SkIRect_MakeXYWH(0, 0, 16, 16);
    auto *irect = reinterpret_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(irect_handle));
    if (!check(irect != nullptr, "SkIRect_MakeXYWH")) {
        static_sk_i_rect_delete(irect_handle);
        SkNoDrawCanvas_delete(no_draw);
        return false;
    }
    SkNoDrawCanvas_resetCanvasWithIRect(no_draw, irect);
    reskia_no_draw_canvas_t *no_draw_rect = SkNoDrawCanvas_newWithIRect(irect);
    if (!check(no_draw_rect != nullptr, "SkNoDrawCanvas_newWithIRect")) {
        static_sk_i_rect_delete(irect_handle);
        SkNoDrawCanvas_delete(no_draw);
        return false;
    }
    SkNoDrawCanvas_delete(no_draw_rect);
    static_sk_i_rect_delete(irect_handle);
    SkNoDrawCanvas_delete(no_draw);
    return true;
}

bool smoke_nway_canvas() {
    reskia_nway_canvas_t *nway = SkNWayCanvas_new(64, 64);
    reskia_canvas_t *target_a = SkCanvas_newWithSizeProps(64, 64, nullptr);
    reskia_canvas_t *target_b = SkCanvas_newWithSizeProps(64, 64, nullptr);
    reskia_paint_t *paint = SkPaint_new();
    sk_rect_t rect_handle = SkRect_MakeLTRB(4.0f, 4.0f, 20.0f, 20.0f);
    auto *rect = reinterpret_cast<reskia_rect_t *>(static_sk_rect_get_ptr(rect_handle));
    if (!check(nway != nullptr && target_a != nullptr && target_b != nullptr && paint != nullptr && rect != nullptr,
               "SkNWayCanvas setup")) {
        static_sk_rect_delete(rect_handle);
        SkPaint_delete(paint);
        SkCanvas_delete(target_b);
        SkCanvas_delete(target_a);
        SkNWayCanvas_delete(nway);
        return false;
    }

    reskia_canvas_t *nway_canvas = SkNWayCanvas_asCanvas(nway);
    if (!check(nway_canvas != nullptr, "SkNWayCanvas_asCanvas")) {
        static_sk_rect_delete(rect_handle);
        SkPaint_delete(paint);
        SkCanvas_delete(target_b);
        SkCanvas_delete(target_a);
        SkNWayCanvas_delete(nway);
        return false;
    }
    SkNWayCanvas_addCanvas(nway, target_a);
    SkNWayCanvas_addCanvas(nway, target_b);
    SkCanvas_drawRect(nway_canvas, rect_handle, paint);
    SkNWayCanvas_removeCanvas(nway, target_a);
    SkCanvas_drawRect(nway_canvas, rect_handle, paint);
    SkNWayCanvas_removeAll(nway);
    SkCanvas_drawRect(nway_canvas, rect_handle, paint);

    static_sk_rect_delete(rect_handle);
    SkPaint_delete(paint);
    SkCanvas_delete(target_b);
    SkCanvas_delete(target_a);
    SkNWayCanvas_delete(nway);
    return true;
}

bool smoke_canvas_state_utils() {
    if (!check(SkCanvasStateUtils_CaptureCanvasState(nullptr) == nullptr,
               "SkCanvasStateUtils_CaptureCanvasState null")) {
        return false;
    }
    if (!check(SkCanvasStateUtils_MakeFromCanvasState(nullptr) == nullptr,
               "SkCanvasStateUtils_MakeFromCanvasState null")) {
        return false;
    }
    SkCanvasStateUtils_ReleaseCanvasState(nullptr);

    reskia_bitmap_t *bitmap = SkBitmap_new();
    if (!check(bitmap != nullptr, "SkBitmap_new for canvas state")) {
        return false;
    }
    SkBitmap_allocN32Pixels(bitmap, 8, 8, false);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);
    if (!check(canvas != nullptr, "SkCanvas_newFromBitmap for canvas state")) {
        SkBitmap_delete(bitmap);
        return false;
    }
    SkCanvas_clearColor(canvas, 0xff123456);
    reskia_canvas_state_t *state = SkCanvasStateUtils_CaptureCanvasState(canvas);
    if (!check(state != nullptr, "SkCanvasStateUtils_CaptureCanvasState")) {
        SkCanvas_delete(canvas);
        SkBitmap_delete(bitmap);
        return false;
    }
    reskia_canvas_t *state_canvas = SkCanvasStateUtils_MakeFromCanvasState(state);
    if (!check(state_canvas != nullptr, "SkCanvasStateUtils_MakeFromCanvasState")) {
        SkCanvasStateUtils_ReleaseCanvasState(state);
        SkCanvas_delete(canvas);
        SkBitmap_delete(bitmap);
        return false;
    }
    SkCanvas_clearColor(state_canvas, 0xff654321);
    SkCanvas_delete(state_canvas);
    SkCanvasStateUtils_ReleaseCanvasState(state);
    SkCanvas_delete(canvas);
    SkBitmap_delete(bitmap);
    return true;
}

}  // namespace

int main() {
    if (!smoke_no_draw_canvas()) {
        return 1;
    }
    if (!smoke_nway_canvas()) {
        return 1;
    }
    if (!smoke_canvas_state_utils()) {
        return 1;
    }
    std::fprintf(stdout, "[canvas-utils-smoke] PASS\n");
    return 0;
}
