#include <cstdio>
#include <cstring>

#include "capi/sk_canvas.h"
#include "capi/sk_font.h"
#include "capi/sk_matrix.h"
#include "capi/sk_paint.h"
#include "capi/sk_path.h"
#include "capi/sk_point_3.h"
#include "capi/sk_rect.h"
#include "capi/sk_shadow_utils.h"
#include "capi/sk_text_utils.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_point_3.h"
#include "handles/static_sk_rect.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[text-shadow-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_text_utils() {
    reskia_canvas_t *canvas = SkCanvas_newWithSizeProps(64, 64, nullptr);
    reskia_font_t *font = SkFont_new();
    reskia_paint_t *paint = SkPaint_new();
    reskia_path_t *path = SkPath_new();
    if (!check(canvas != nullptr && font != nullptr && paint != nullptr && path != nullptr,
               "text utils setup")) {
        SkPath_delete(path);
        SkPaint_delete(paint);
        SkFont_delete(font);
        SkCanvas_delete(canvas);
        return false;
    }

    SkTextUtils_Draw(nullptr, "abc", 3, 0, 0.0f, 12.0f, font, paint, 0);
    SkTextUtils_Draw(canvas, nullptr, 3, 0, 0.0f, 12.0f, font, paint, 0);
    SkTextUtils_DrawString(canvas, "abc", 0.0f, 12.0f, font, paint, 0);
    SkTextUtils_Draw(canvas, "abc", 3, 0, 0.0f, 24.0f, font, paint, 1);
    SkTextUtils_GetPath("A", 1, 0, 0.0f, 0.0f, font, path);
    if (!check(SkPath_isFinite(path), "SkTextUtils_GetPath path finite")) {
        SkPath_delete(path);
        SkPaint_delete(paint);
        SkFont_delete(font);
        SkCanvas_delete(canvas);
        return false;
    }

    SkPath_delete(path);
    SkPaint_delete(paint);
    SkFont_delete(font);
    SkCanvas_delete(canvas);
    return true;
}

bool smoke_shadow_utils() {
    uint32_t ambient = 0;
    uint32_t spot = 0;
    SkShadowUtils_ComputeTonalColors(0x55000000, 0xaa000000, &ambient, &spot);
    if (!check(ambient != 0 || spot != 0, "SkShadowUtils_ComputeTonalColors")) {
        return false;
    }

    reskia_canvas_t *canvas = SkCanvas_newWithSizeProps(64, 64, nullptr);
    reskia_path_t *path = SkPath_new();
    sk_point_3_t z_handle = SkPoint3_Make(0.0f, 0.0f, 8.0f);
    sk_point_3_t light_handle = SkPoint3_Make(16.0f, -32.0f, 64.0f);
    sk_matrix_t matrix_handle = SkMatrix_I();
    sk_rect_t bounds_handle = SkRect_MakeEmpty();
    auto *z_plane = reinterpret_cast<reskia_point_3_t *>(static_sk_point_3_get_ptr(z_handle));
    auto *light = reinterpret_cast<reskia_point_3_t *>(static_sk_point_3_get_ptr(light_handle));
    auto *matrix = reinterpret_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(matrix_handle));
    auto *bounds = reinterpret_cast<reskia_rect_t *>(static_sk_rect_get_ptr(bounds_handle));
    if (!check(canvas != nullptr &&
               path != nullptr &&
               z_plane != nullptr &&
               light != nullptr &&
               matrix != nullptr &&
               bounds != nullptr,
               "shadow utils setup")) {
        static_sk_rect_delete(bounds_handle);
        static_sk_matrix_delete(matrix_handle);
        static_sk_point_3_delete(light_handle);
        static_sk_point_3_delete(z_handle);
        SkPath_delete(path);
        SkCanvas_delete(canvas);
        return false;
    }

    SkPath_addRectLTRBWithDirection(path, 8.0f, 8.0f, 32.0f, 32.0f, 0);
    if (!check(SkShadowUtils_GetLocalBounds(matrix, path, z_plane, light, 4.0f, 0, bounds),
               "SkShadowUtils_GetLocalBounds")) {
        static_sk_rect_delete(bounds_handle);
        static_sk_matrix_delete(matrix_handle);
        static_sk_point_3_delete(light_handle);
        static_sk_point_3_delete(z_handle);
        SkPath_delete(path);
        SkCanvas_delete(canvas);
        return false;
    }
    SkShadowUtils_DrawShadow(canvas, path, z_plane, light, 4.0f, ambient, spot, 0);
    if (!check(!SkShadowUtils_GetLocalBounds(nullptr, path, z_plane, light, 4.0f, 0, bounds),
               "SkShadowUtils_GetLocalBounds invalid input")) {
        static_sk_rect_delete(bounds_handle);
        static_sk_matrix_delete(matrix_handle);
        static_sk_point_3_delete(light_handle);
        static_sk_point_3_delete(z_handle);
        SkPath_delete(path);
        SkCanvas_delete(canvas);
        return false;
    }

    static_sk_rect_delete(bounds_handle);
    static_sk_matrix_delete(matrix_handle);
    static_sk_point_3_delete(light_handle);
    static_sk_point_3_delete(z_handle);
    SkPath_delete(path);
    SkCanvas_delete(canvas);
    return true;
}

}  // namespace

int main() {
    if (!smoke_text_utils()) {
        return 1;
    }
    if (!smoke_shadow_utils()) {
        return 1;
    }
    std::fprintf(stdout, "[text-shadow-utils-smoke] PASS\n");
    return 0;
}
