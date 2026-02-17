#include <cstdio>

#import <Metal/Metal.h>

#include "capi/reskia_ffi.h"
#include "capi/sk_canvas.h"
#include "capi/sk_gpu_context.h"
#include "capi/sk_graphics.h"
#include "capi/sk_image_info.h"
#include "capi/sk_paint.h"
#include "capi/sk_rect.h"
#include "capi/sk_surface.h"
#include "capi/sk_surface_gpu.h"

#include "handles/static_sk_image_info.h"
#include "handles/static_sk_rect.h"
#include "handles/static_sk_surface.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[gpu-surface-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_surface_create_draw_flush() {
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    if (device == nil) {
        std::fprintf(stdout, "[gpu-surface-capi-smoke] SKIP: Metal device is unavailable in this environment\n");
        return true;
    }

    id<MTLCommandQueue> queue = [device newCommandQueue];
    if (queue == nil) {
        std::fprintf(stdout, "[gpu-surface-capi-smoke] SKIP: Metal command queue could not be created\n");
        return true;
    }

    reskia_direct_context_t* direct_context =
            Reskia_GaneshContext_MakeMetal((void*)device, (void*)queue);
    if (!check(direct_context != nullptr, "Reskia_GaneshContext_MakeMetal")) {
        return false;
    }

    const sk_image_info_t info_handle = SkImageInfo_MakeN32Premul(64, 64);
    auto* info_ptr =
            reinterpret_cast<const reskia_image_info_t*>(static_sk_image_info_get_ptr(info_handle));
    if (!check(info_ptr != nullptr, "SkImageInfo_MakeN32Premul")) {
        Reskia_DirectContext_Release(direct_context);
        static_sk_image_info_delete(info_handle);
        return false;
    }

    sk_surface_t surface_handle = 0;
    const reskia_gpu_surface_status_t status = Reskia_GaneshSurface_MakeRenderTarget(
            direct_context,
            info_ptr,
            true,
            0,
            0,
            nullptr,
            &surface_handle);
    if (!check(status == RESKIA_GPU_SURFACE_STATUS_OK, "Reskia_GaneshSurface_MakeRenderTarget")) {
        Reskia_DirectContext_Release(direct_context);
        static_sk_image_info_delete(info_handle);
        return false;
    }
    if (!check(surface_handle != 0, "surface_handle")) {
        Reskia_DirectContext_Release(direct_context);
        static_sk_image_info_delete(info_handle);
        return false;
    }

    reskia_surface_t* surface = reskia_surface_borrow_from_handle(surface_handle);
    if (!check(surface != nullptr, "reskia_surface_borrow_from_handle")) {
        static_sk_surface_delete(surface_handle);
        Reskia_DirectContext_Release(direct_context);
        static_sk_image_info_delete(info_handle);
        return false;
    }

    reskia_canvas_t* canvas = SkSurface_getCanvas(surface);
    if (!check(canvas != nullptr, "SkSurface_getCanvas")) {
        static_sk_surface_delete(surface_handle);
        Reskia_DirectContext_Release(direct_context);
        static_sk_image_info_delete(info_handle);
        return false;
    }

    SkCanvas_clearColor(canvas, 0xFF101820u);

    reskia_paint_t* paint = SkPaint_new();
    if (!check(paint != nullptr, "SkPaint_new")) {
        static_sk_surface_delete(surface_handle);
        Reskia_DirectContext_Release(direct_context);
        static_sk_image_info_delete(info_handle);
        return false;
    }
    SkPaint_setColor(paint, 0xFFFF5A36u);

    const sk_rect_t rect = SkRect_MakeXYWH(8.0f, 8.0f, 48.0f, 48.0f);
    SkCanvas_drawRect(canvas, rect, paint);

    Reskia_DirectContext_FlushAndSubmit(direct_context, true);

    static_sk_rect_delete(rect);
    SkPaint_delete(paint);
    static_sk_surface_delete(surface_handle);
    Reskia_DirectContext_Release(direct_context);
    static_sk_image_info_delete(info_handle);
    return true;
}

}  // namespace

int main() {
    SkGraphics_Init();

    if (!smoke_surface_create_draw_flush()) {
        return 1;
    }

    std::fprintf(stdout, "[gpu-surface-capi-smoke] PASS\n");
    return 0;
}
