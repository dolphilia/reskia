#include "capi/sk_canvas.h"
#include "capi/sk_bitmap.h"
#include "capi/sk_data.h"
#include "capi/sk_font.h"
#include "capi/sk_i_rect.h"
#include "capi/sk_image_info.h"
#include "capi/sk_m_44.h"
#include "capi/sk_matrix.h"
#include "capi/sk_paint.h"
#include "capi/sk_path.h"
#include "capi/sk_picture_recorder.h"
#include "capi/sk_pixmap.h"
#include "capi/sk_point.h"
#include "capi/sk_region.h"
#include "capi/sk_rect.h"
#include "capi/sk_r_rect.h"
#include "capi/sk_string.h"
#include "capi/sk_surface.h"
#include "capi/sk_surfaces.h"
#include "capi/sk_text_blob.h"
#include "capi/sk_vertices.h"
#include "handles/static_sk_i_rect.h"
#include "handles/static_sk_drawable.h"
#include "handles/static_sk_data.h"
#include "handles/static_sk_image.h"
#include "handles/static_sk_image_info.h"
#include "handles/static_sk_m_44.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_picture.h"
#include "handles/static_sk_point.h"
#include "handles/static_sk_r_rect.h"
#include "handles/static_sk_rect.h"
#include "handles/static_sk_surface.h"
#include "handles/static_sk_shader.h"
#include "handles/static_sk_text_blob.h"
#include "handles/static_sk_vertices.h"
#include "include/core/SkPoint.h"

#include <cstdio>

extern "C" sk_shader_t SkShaders_Color(uint32_t color);

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
    SkCanvas_drawSimpleText(nullptr, nullptr, 1, 0, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawGlyphs(nullptr, 1, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsAtPositions(nullptr, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsWithXforms(nullptr, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawAtlas(nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr);
    SkCanvas_drawAtlas(nullptr, nullptr, nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr);
    SkCanvas_experimental_DrawEdgeAAImageSet(nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAImageSet(nullptr, nullptr, 1, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_drawDrawable(nullptr, nullptr, nullptr);
    SkCanvas_drawDrawableAt(nullptr, nullptr, 0.0f, 0.0f);
    SkCanvas_drawPicture(nullptr, 0);
    SkCanvas_drawPictureHandleWithMatrixPaint(nullptr, 0, nullptr, nullptr);
    SkCanvas_drawPicturePtr(nullptr, nullptr);
    SkCanvas_drawPicturePtrWithMatrixPaint(nullptr, nullptr, nullptr, nullptr);
    if (!check(SkCanvas_saveLayer(nullptr, nullptr) == 0, "SkCanvas_saveLayer(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_saveLayerWithBoundsPaintRef(nullptr, nullptr, nullptr) == 0, "SkCanvas_saveLayerWithBoundsPaintRef(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_saveLayerWithBoundsPaintPtr(nullptr, nullptr, nullptr) == 0, "SkCanvas_saveLayerWithBoundsPaintPtr(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_saveLayerAlpha(nullptr, nullptr, 255) == 0, "SkCanvas_saveLayerAlpha(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_saveLayerAlphaf(nullptr, nullptr, 1.0f) == 0, "SkCanvas_saveLayerAlphaf(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_MakeRasterDirect(nullptr, nullptr, 0, nullptr) == 0, "SkCanvas_MakeRasterDirect(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_MakeRasterDirectN32(-1, 1, nullptr, 0) == 0, "SkCanvas_MakeRasterDirectN32(negative width)")) {
        return 5;
    }
    if (!check(SkCanvas_MakeRasterDirectN32(1, -1, nullptr, 0) == 0, "SkCanvas_MakeRasterDirectN32(negative height)")) {
        return 5;
    }
    if (!check(SkCanvas_MakeRasterDirectN32(1, 1, nullptr, 0) == 0, "SkCanvas_MakeRasterDirectN32(null pixels)")) {
        return 5;
    }
    if (!check(SkCanvas_makeSurface(nullptr, nullptr, nullptr) == 0, "SkCanvas_makeSurface(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_accessTopLayerPixels(nullptr, nullptr, nullptr, nullptr) == nullptr, "SkCanvas_accessTopLayerPixels(nullptr)")) {
        return 5;
    }
    if (!check(!SkCanvas_peekPixels(nullptr, nullptr), "SkCanvas_peekPixels(nullptr)")) {
        return 5;
    }

    reskia_canvas_t *canvas = SkCanvas_new();
    if (!check(canvas != nullptr, "SkCanvas_new")) {
        return 6;
    }

    SkCanvas_translate(canvas, 1.0f, 1.0f);
    SkCanvas_drawPath(canvas, nullptr, nullptr);
    SkCanvas_drawPoints(canvas, 0, 1, nullptr, nullptr);
    SkCanvas_drawSimpleText(canvas, nullptr, 0, 0, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawSimpleText(canvas, nullptr, 1, 0, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 0, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, reinterpret_cast<const uint16_t *>(1), reinterpret_cast<const reskia_point_t *>(1), nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, reinterpret_cast<const uint16_t *>(1), reinterpret_cast<const reskia_point_t *>(1), reinterpret_cast<const uint32_t *>(1), -1, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, reinterpret_cast<const uint16_t *>(1), reinterpret_cast<const reskia_point_t *>(1), reinterpret_cast<const uint32_t *>(1), 1, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsAtPositions(canvas, 0, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsAtPositions(canvas, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsWithXforms(canvas, 0, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsWithXforms(canvas, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, nullptr, nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, nullptr, nullptr, nullptr, nullptr, -1, 0, nullptr, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, nullptr, nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr);
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, nullptr, 0, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, nullptr, -1, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, nullptr, 1, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_drawDrawable(canvas, nullptr, nullptr);
    SkCanvas_drawDrawableAt(canvas, nullptr, 0.0f, 0.0f);
    SkCanvas_drawPicture(canvas, 0);
    SkCanvas_drawPicture(canvas, 999999);
    SkCanvas_drawImage(canvas, 0, 0.0f, 0.0f);
    SkCanvas_drawImage(canvas, 999999, 0.0f, 0.0f);
    SkCanvas_drawImageHandleWithSampling(canvas, 999999, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawImageLattice(canvas, nullptr, nullptr, nullptr);
    SkCanvas_drawImageLatticeWithFilter(canvas, nullptr, nullptr, nullptr, 0, nullptr);
    SkCanvas_drawImageNine(canvas, nullptr, nullptr, nullptr, 0, nullptr);
    SkCanvas_drawImageRect(canvas, 999999, nullptr, nullptr, nullptr);
    SkCanvas_drawImageRectHandleWithSrcDst(canvas, 999999, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_drawPictureHandleWithMatrixPaint(canvas, 0, nullptr, nullptr);
    SkCanvas_drawPictureHandleWithMatrixPaint(canvas, 999999, nullptr, nullptr);
    SkCanvas_drawPicturePtr(canvas, nullptr);
    SkCanvas_drawPicturePtrWithMatrixPaint(canvas, nullptr, nullptr, nullptr);
    SkCanvas_drawTextBlob(canvas, 0, 0.0f, 0.0f, nullptr);
    SkCanvas_drawTextBlobPtr(canvas, nullptr, 0.0f, 0.0f, nullptr);
    if (!check(SkCanvas_saveLayer(canvas, nullptr) == 0, "SkCanvas_saveLayer(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(SkCanvas_saveLayerWithBoundsPaintRef(canvas, nullptr, nullptr) == 0, "SkCanvas_saveLayerWithBoundsPaintRef(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(SkCanvas_saveLayerWithBoundsPaintPtr(canvas, nullptr, nullptr) > 0, "SkCanvas_saveLayerWithBoundsPaintPtr optional bounds/paint")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_restore(canvas);
    if (!check(SkCanvas_saveLayerAlpha(canvas, nullptr, 255) > 0, "SkCanvas_saveLayerAlpha optional bounds")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_restore(canvas);
    if (!check(SkCanvas_saveLayerAlphaf(canvas, nullptr, 1.0f) > 0, "SkCanvas_saveLayerAlphaf optional bounds")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_restore(canvas);
    if (!check(SkCanvas_makeSurface(canvas, nullptr, nullptr) == 0, "SkCanvas_makeSurface(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_concat(canvas, nullptr);
    SkCanvas_concatMatrix(canvas, nullptr);
    SkCanvas_setMatrix(canvas, nullptr);
    SkCanvas_setMatrix3x3(canvas, nullptr);
    const sk_m_44_t m44_handle = SkM44_Translate(1.0f, 2.0f, 0.0f);
    auto *m44 = static_cast<reskia_m_44_t *>(static_sk_m_44_get_ptr(m44_handle));
    if (!check(m44 != nullptr, "SkM44_Translate for canvas matrix")) {
        if (m44_handle != 0) {
            static_sk_m_44_delete(m44_handle);
        }
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_concat(canvas, m44);
    SkCanvas_setMatrix(canvas, m44);
    static_sk_m_44_delete(m44_handle);
    const sk_matrix_t canvas_matrix_handle = SkMatrix_I();
    auto *canvas_matrix = static_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(canvas_matrix_handle));
    if (!check(canvas_matrix != nullptr, "SkMatrix_I for canvas matrix")) {
        if (canvas_matrix_handle != 0) {
            static_sk_matrix_delete(canvas_matrix_handle);
        }
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_concatMatrix(canvas, canvas_matrix);
    SkCanvas_setMatrix3x3(canvas, canvas_matrix);
    static_sk_matrix_delete(canvas_matrix_handle);

    reskia_paint_t *paint = SkPaint_new();
    if (!check(paint != nullptr, "SkPaint_new for canvas text blob")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawPaint(canvas, nullptr);
    SkCanvas_drawPaint(canvas, paint);
    const float canvas_color[4] = {1.0f, 0.0f, 0.0f, 1.0f};
    const auto *canvas_color_input = reinterpret_cast<const reskia_color_4f_t *>(canvas_color);
    SkCanvas_drawColor(canvas, nullptr, 0);
    SkCanvas_drawColor(canvas, canvas_color_input, -1);
    SkCanvas_drawColor(canvas, canvas_color_input, 999999);
    SkCanvas_drawColor(canvas, canvas_color_input, 0);
    SkCanvas_drawColorU32(canvas, 0xFF000000u, -1);
    SkCanvas_drawColorU32(canvas, 0xFF000000u, 999999);
    SkCanvas_drawColorU32(canvas, 0xFF000000u, 0);
    SkCanvas_clipIRect(canvas, nullptr, 0);
    SkCanvas_clipRect(canvas, nullptr, false);
    SkCanvas_clipRectWithOp(canvas, nullptr, 0);
    SkCanvas_clipRectWithOpAA(canvas, nullptr, 0, false);
    SkCanvas_clipRRect(canvas, nullptr, false);
    SkCanvas_clipRRectWithOp(canvas, nullptr, 0);
    SkCanvas_clipRRectWithOpAA(canvas, nullptr, 0, false);
    SkCanvas_clipPath(canvas, nullptr, false);
    SkCanvas_clipPathWithOp(canvas, nullptr, 0);
    SkCanvas_clipPathWithOpAA(canvas, nullptr, 0, false);
    SkCanvas_clipShader(canvas, 0, 0);
    SkCanvas_clipShader(canvas, 999999, 0);
    const sk_i_rect_t clip_irect_handle = SkIRect_MakeXYWH(0, 0, 1, 1);
    auto *clip_irect = static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(clip_irect_handle));
    if (!check(clip_irect != nullptr, "SkIRect_MakeXYWH for canvas clipIRect")) {
        if (clip_irect_handle != 0) {
            static_sk_i_rect_delete(clip_irect_handle);
        }
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_clipIRect(canvas, clip_irect, 0);
    static_sk_i_rect_delete(clip_irect_handle);
    const sk_rect_t clip_rect_handle = SkRect_MakeWH(1.0f, 1.0f);
    auto *clip_rect = static_cast<reskia_rect_t *>(static_sk_rect_get_ptr(clip_rect_handle));
    if (!check(clip_rect != nullptr, "SkRect_MakeWH for canvas clipRect")) {
        if (clip_rect_handle != 0) {
            static_sk_rect_delete(clip_rect_handle);
        }
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_clipRect(canvas, clip_rect, false);
    SkCanvas_clipRectWithOp(canvas, clip_rect, 0);
    SkCanvas_clipRectWithOpAA(canvas, clip_rect, 0, false);
    static_sk_rect_delete(clip_rect_handle);
    const sk_r_rect_t clip_rrect_handle = SkRRect_MakeEmpty();
    auto *clip_rrect = static_cast<reskia_r_rect_t *>(static_sk_r_rect_get_ptr(clip_rrect_handle));
    if (!check(clip_rrect != nullptr, "SkRRect_MakeEmpty for canvas clipRRect")) {
        if (clip_rrect_handle != 0) {
            static_sk_r_rect_delete(clip_rrect_handle);
        }
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_clipRRect(canvas, clip_rrect, false);
    SkCanvas_clipRRectWithOp(canvas, clip_rrect, 0);
    SkCanvas_clipRRectWithOpAA(canvas, clip_rrect, 0, false);
    static_sk_r_rect_delete(clip_rrect_handle);
    const sk_shader_t clip_shader_handle = SkShaders_Color(0xFF00FF00u);
    if (!check(clip_shader_handle != 0 && static_sk_shader_get_ptr(clip_shader_handle) != nullptr, "SkShaders_Color for canvas clipShader")) {
        if (clip_shader_handle != 0) {
            static_sk_shader_delete(clip_shader_handle);
        }
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_clipShader(canvas, clip_shader_handle, 0);
    static_sk_shader_delete(clip_shader_handle);
    reskia_path_t *path = SkPath_new();
    if (!check(path != nullptr, "SkPath_new for canvas drawPath")) {
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawPath(canvas, nullptr, paint);
    SkCanvas_drawPath(canvas, path, nullptr);
    SkCanvas_drawPath(canvas, path, paint);
    SkCanvas_clipPath(canvas, path, false);
    SkCanvas_clipPathWithOp(canvas, path, 0);
    SkCanvas_clipPathWithOpAA(canvas, path, 0, false);
    SkPath_delete(path);
    reskia_region_t *region = SkRegion_new();
    if (!check(region != nullptr, "SkRegion_new for canvas drawRegion")) {
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawRegion(canvas, nullptr, paint);
    SkCanvas_drawRegion(canvas, region, nullptr);
    SkCanvas_drawRegion(canvas, region, paint);
    SkRegion_delete(region);
    SkPoint patch_cubics[12] = {};
    SkPoint patch_tex_coords[4] = {};
    const auto *patch_cubics_input = reinterpret_cast<const reskia_point_t *>(patch_cubics);
    const auto *patch_tex_coords_input = reinterpret_cast<const reskia_point_t *>(patch_tex_coords);
    SkCanvas_drawPatch(canvas, nullptr, nullptr, patch_tex_coords_input, 0, paint);
    SkCanvas_drawPatch(canvas, patch_cubics_input, nullptr, nullptr, 0, paint);
    SkCanvas_drawPatch(canvas, patch_cubics_input, nullptr, patch_tex_coords_input, 0, nullptr);
    SkCanvas_drawPatch(canvas, patch_cubics_input, nullptr, patch_tex_coords_input, 0, paint);
    const sk_point_t point0_handle = SkPoint_Make(0.0f, 0.0f);
    const sk_point_t point1_handle = SkPoint_Make(1.0f, 1.0f);
    if (!check(static_sk_point_get_ptr(point0_handle) != nullptr && static_sk_point_get_ptr(point1_handle) != nullptr, "SkPoint_Make for canvas point/line")) {
        if (point0_handle != 0) {
            static_sk_point_delete(point0_handle);
        }
        if (point1_handle != 0) {
            static_sk_point_delete(point1_handle);
        }
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawLine(canvas, 0, point1_handle, paint);
    SkCanvas_drawLine(canvas, 999999, point1_handle, paint);
    SkCanvas_drawLine(canvas, point0_handle, 999999, paint);
    SkCanvas_drawLine(canvas, point0_handle, point1_handle, nullptr);
    SkCanvas_drawLine(canvas, point0_handle, point1_handle, paint);
    SkCanvas_drawLineXY(canvas, 0.0f, 0.0f, 1.0f, 1.0f, nullptr);
    SkCanvas_drawLineXY(canvas, 0.0f, 0.0f, 1.0f, 1.0f, paint);
    SkCanvas_drawPoint(canvas, 0, paint);
    SkCanvas_drawPoint(canvas, 999999, paint);
    SkCanvas_drawPoint(canvas, point0_handle, nullptr);
    SkCanvas_drawPoint(canvas, point0_handle, paint);
    SkCanvas_drawPointXY(canvas, 0.0f, 0.0f, nullptr);
    SkCanvas_drawPointXY(canvas, 0.0f, 0.0f, paint);
    SkCanvas_drawCircle(canvas, 0, 1.0f, paint);
    SkCanvas_drawCircle(canvas, 999999, 1.0f, paint);
    SkCanvas_drawCircle(canvas, point0_handle, 1.0f, nullptr);
    SkCanvas_drawCircle(canvas, point0_handle, 1.0f, paint);
    SkCanvas_drawCircleAt(canvas, 0.0f, 0.0f, 1.0f, nullptr);
    SkCanvas_drawCircleAt(canvas, 0.0f, 0.0f, 1.0f, paint);
    static_sk_point_delete(point1_handle);
    static_sk_point_delete(point0_handle);
    const sk_rect_t round_rect_handle = SkRect_MakeXYWH(0.0f, 0.0f, 2.0f, 2.0f);
    auto *round_rect = static_cast<reskia_rect_t *>(static_sk_rect_get_ptr(round_rect_handle));
    if (!check(round_rect != nullptr, "SkRect_MakeXYWH for canvas rounded rect")) {
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    const sk_data_t annotation_data_handle = SkData_MakeWithCString("annotation");
    auto *annotation_data = static_cast<reskia_data_t *>(static_sk_data_get_ptr(annotation_data_handle));
    if (!check(annotation_data != nullptr, "SkData_MakeWithCString for canvas annotation")) {
        if (annotation_data_handle != 0) {
            static_sk_data_delete(annotation_data_handle);
        }
        static_sk_rect_delete(round_rect_handle);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawAnnotation(canvas, nullptr, "k", annotation_data_handle);
    SkCanvas_drawAnnotation(canvas, round_rect, nullptr, annotation_data_handle);
    SkCanvas_drawAnnotation(canvas, round_rect, "k", 0);
    SkCanvas_drawAnnotation(canvas, round_rect, "k", 999999);
    SkCanvas_drawAnnotation(canvas, round_rect, "k", annotation_data_handle);
    SkCanvas_drawAnnotationWithDataPtr(canvas, nullptr, "k", annotation_data);
    SkCanvas_drawAnnotationWithDataPtr(canvas, round_rect, nullptr, annotation_data);
    SkCanvas_drawAnnotationWithDataPtr(canvas, round_rect, "k", nullptr);
    SkCanvas_drawAnnotationWithDataPtr(canvas, round_rect, "k", annotation_data);
    static_sk_data_delete(annotation_data_handle);
    SkCanvas_drawArc(canvas, nullptr, 0.0f, 90.0f, false, paint);
    SkCanvas_drawArc(canvas, round_rect, 0.0f, 90.0f, false, nullptr);
    SkCanvas_drawArc(canvas, round_rect, 0.0f, 90.0f, false, paint);
    const sk_i_rect_t irect_handle = SkIRect_MakeXYWH(0, 0, 2, 2);
    auto *irect = static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(irect_handle));
    if (!check(irect != nullptr, "SkIRect_MakeXYWH for canvas irect")) {
        static_sk_rect_delete(round_rect_handle);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawIRect(canvas, nullptr, paint);
    SkCanvas_drawIRect(canvas, irect, nullptr);
    SkCanvas_drawIRect(canvas, irect, paint);
    SkCanvas_drawOval(canvas, nullptr, paint);
    SkCanvas_drawOval(canvas, round_rect, nullptr);
    SkCanvas_drawOval(canvas, round_rect, paint);
    SkCanvas_drawRect(canvas, 0, paint);
    SkCanvas_drawRect(canvas, 999999, paint);
    SkCanvas_drawRect(canvas, round_rect_handle, nullptr);
    SkCanvas_drawRect(canvas, round_rect_handle, paint);
    const sk_r_rect_t rrect_handle = SkRRect_MakeRect(round_rect);
    auto *rrect = static_cast<reskia_r_rect_t *>(static_sk_r_rect_get_ptr(rrect_handle));
    if (!check(rrect != nullptr, "SkRRect_MakeRect for canvas rrect")) {
        static_sk_i_rect_delete(irect_handle);
        static_sk_rect_delete(round_rect_handle);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawRoundRect(canvas, nullptr, 1.0f, 1.0f, paint);
    SkCanvas_drawRoundRect(canvas, round_rect, 1.0f, 1.0f, nullptr);
    SkCanvas_drawRoundRect(canvas, round_rect, 1.0f, 1.0f, paint);
    SkCanvas_drawRRect(canvas, nullptr, paint);
    SkCanvas_drawRRect(canvas, rrect, nullptr);
    SkCanvas_drawRRect(canvas, rrect, paint);
    SkCanvas_drawDRRect(canvas, nullptr, rrect, paint);
    SkCanvas_drawDRRect(canvas, rrect, nullptr, paint);
    SkCanvas_drawDRRect(canvas, rrect, rrect, nullptr);
    SkCanvas_drawDRRect(canvas, rrect, rrect, paint);
    static_sk_r_rect_delete(rrect_handle);
    static_sk_i_rect_delete(irect_handle);
    static_sk_rect_delete(round_rect_handle);
    SkCanvas_drawTextBlob(canvas, 0, 0.0f, 0.0f, paint);
    SkCanvas_drawTextBlob(canvas, 999999, 0.0f, 0.0f, paint);
    SkCanvas_drawTextBlobPtr(canvas, nullptr, 0.0f, 0.0f, paint);
    reskia_font_t *font = SkFont_new();
    if (!check(font != nullptr, "SkFont_new for canvas text blob")) {
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    const sk_text_blob_t text_blob_handle = SkTextBlob_MakeFromString("A", font, 0);
    auto *text_blob = static_cast<reskia_text_blob_t *>(static_sk_text_blob_get_ptr(text_blob_handle));
    if (!check(text_blob != nullptr, "SkTextBlob_MakeFromString for canvas")) {
        SkFont_delete(font);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawTextBlob(canvas, text_blob_handle, 0.0f, 0.0f, nullptr);
    SkCanvas_drawTextBlobPtr(canvas, text_blob, 0.0f, 0.0f, nullptr);
    SkCanvas_drawTextBlob(canvas, text_blob_handle, 0.0f, 0.0f, paint);
    SkCanvas_drawTextBlobPtr(canvas, text_blob, 0.0f, 0.0f, paint);
    static_sk_text_blob_delete(text_blob_handle);
    SkCanvas_drawString(canvas, nullptr, 0.0f, 0.0f, font, paint);
    SkCanvas_drawString(canvas, "A", 0.0f, 0.0f, nullptr, paint);
    SkCanvas_drawString(canvas, "A", 0.0f, 0.0f, font, nullptr);
    SkCanvas_drawString(canvas, "A", 0.0f, 0.0f, font, paint);
    reskia_string_t *string = SkString_newFromText("A");
    if (!check(string != nullptr, "SkString_newFromText for canvas string")) {
        SkFont_delete(font);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawStringObject(canvas, nullptr, 0.0f, 0.0f, font, paint);
    SkCanvas_drawStringObject(canvas, string, 0.0f, 0.0f, nullptr, paint);
    SkCanvas_drawStringObject(canvas, string, 0.0f, 0.0f, font, nullptr);
    SkCanvas_drawStringObject(canvas, string, 0.0f, 0.0f, font, paint);
    SkString_delete(string);
    SkFont_delete(font);

    reskia_picture_recorder_t *picture_recorder = SkPictureRecorder_new();
    if (!check(picture_recorder != nullptr, "SkPictureRecorder_new for canvas picture")) {
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(SkPictureRecorder_beginRecordingWithSizeAndFactory(picture_recorder, 2.0f, 2.0f, nullptr) != nullptr, "SkPictureRecorder_beginRecordingWithSizeAndFactory for canvas picture")) {
        SkPictureRecorder_delete(picture_recorder);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    const sk_picture_t picture_handle = SkPictureRecorder_finishRecordingAsPicture(picture_recorder);
    auto *picture = static_cast<reskia_picture_t *>(static_sk_picture_get_ptr(picture_handle));
    if (!check(picture != nullptr, "SkPictureRecorder_finishRecordingAsPicture for canvas")) {
        SkPictureRecorder_delete(picture_recorder);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawPicture(canvas, picture_handle);
    SkCanvas_drawPictureHandleWithMatrixPaint(canvas, picture_handle, nullptr, nullptr);
    SkCanvas_drawPictureHandleWithMatrixPaint(canvas, picture_handle, nullptr, paint);
    const sk_matrix_t picture_matrix_handle = SkMatrix_I();
    auto *picture_matrix = static_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(picture_matrix_handle));
    if (!check(picture_matrix != nullptr, "SkMatrix_I for canvas drawPicture")) {
        if (picture_matrix_handle != 0) {
            static_sk_matrix_delete(picture_matrix_handle);
        }
        static_sk_picture_delete(picture_handle);
        SkPictureRecorder_delete(picture_recorder);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawPictureHandleWithMatrixPaint(canvas, picture_handle, picture_matrix, nullptr);
    SkCanvas_drawPictureHandleWithMatrixPaint(canvas, picture_handle, picture_matrix, paint);
    SkCanvas_drawPicturePtr(canvas, picture);
    SkCanvas_drawPicturePtrWithMatrixPaint(canvas, picture, nullptr, nullptr);
    SkCanvas_drawPicturePtrWithMatrixPaint(canvas, picture, nullptr, paint);
    SkCanvas_drawPicturePtrWithMatrixPaint(canvas, picture, picture_matrix, nullptr);
    SkCanvas_drawPicturePtrWithMatrixPaint(canvas, picture, picture_matrix, paint);
    static_sk_matrix_delete(picture_matrix_handle);
    static_sk_picture_delete(picture_handle);
    SkPictureRecorder_delete(picture_recorder);

    SkCanvas_drawVertices(canvas, 0, 0, paint);
    SkCanvas_drawVertices(canvas, 999999, 0, paint);
    SkCanvas_drawVerticesPtr(canvas, nullptr, 0, paint);
    SkPoint vertex_positions[3] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {0.0f, 1.0f}};
    const auto *vertex_position_input = reinterpret_cast<const reskia_point_t *>(vertex_positions);
    const sk_vertices_t vertices_handle = SkVertices_MakeCopyWithoutIndices(0, 3, vertex_position_input, nullptr, nullptr);
    auto *vertices = static_cast<reskia_vertices_t *>(static_sk_vertices_get_ptr(vertices_handle));
    if (!check(vertices != nullptr, "SkVertices_MakeCopyWithoutIndices for canvas")) {
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawVertices(canvas, vertices_handle, 0, nullptr);
    SkCanvas_drawVerticesPtr(canvas, vertices, 0, nullptr);
    SkCanvas_drawVertices(canvas, vertices_handle, 0, paint);
    SkCanvas_drawVerticesPtr(canvas, vertices, 0, paint);
    static_sk_vertices_delete(vertices_handle);

    reskia_picture_recorder_t *drawable_recorder = SkPictureRecorder_new();
    if (!check(drawable_recorder != nullptr, "SkPictureRecorder_new for canvas drawable")) {
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(SkPictureRecorder_beginRecordingWithSizeAndFactory(drawable_recorder, 2.0f, 2.0f, nullptr) != nullptr, "SkPictureRecorder_beginRecordingWithSizeAndFactory for canvas drawable")) {
        SkPictureRecorder_delete(drawable_recorder);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    const sk_drawable_t drawable_handle = SkPictureRecorder_finishRecordingAsDrawable(drawable_recorder);
    auto *drawable = static_cast<reskia_drawable_t *>(static_sk_drawable_get_ptr(drawable_handle));
    if (!check(drawable != nullptr, "SkPictureRecorder_finishRecordingAsDrawable for canvas")) {
        SkPictureRecorder_delete(drawable_recorder);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawDrawable(canvas, drawable, nullptr);
    const sk_matrix_t drawable_matrix_handle = SkMatrix_I();
    auto *drawable_matrix = static_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(drawable_matrix_handle));
    if (!check(drawable_matrix != nullptr, "SkMatrix_I for canvas drawDrawable")) {
        if (drawable_matrix_handle != 0) {
            static_sk_matrix_delete(drawable_matrix_handle);
        }
        static_sk_drawable_delete(drawable_handle);
        SkPictureRecorder_delete(drawable_recorder);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawDrawable(canvas, drawable, drawable_matrix);
    static_sk_matrix_delete(drawable_matrix_handle);
    SkCanvas_drawDrawableAt(canvas, drawable, 0.0f, 0.0f);
    static_sk_drawable_delete(drawable_handle);
    SkPictureRecorder_delete(drawable_recorder);

    SkPaint_delete(paint);

    if (!check(!SkCanvas_readPixels(canvas, nullptr, 0, 0), "SkCanvas_readPixels(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    reskia_bitmap_t *empty_bitmap = SkBitmap_new();
    if (!check(empty_bitmap != nullptr, "SkBitmap_new for canvas readPixels")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_readPixels(canvas, empty_bitmap, 0, 0), "SkCanvas_readPixels empty bitmap")) {
        SkBitmap_delete(empty_bitmap);
        SkCanvas_delete(canvas);
        return 8;
    }
    SkBitmap_delete(empty_bitmap);
    SkCanvas_accessTopLayerPixels(canvas, nullptr, nullptr, nullptr);
    if (!check(!SkCanvas_peekPixels(canvas, nullptr), "SkCanvas_peekPixels(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_readPixelsWithImageInfo(canvas, nullptr, nullptr, 0, 0, 0), "SkCanvas_readPixelsWithImageInfo(null info)")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_writePixelsWithImageInfo(canvas, nullptr, nullptr, 0, 0, 0), "SkCanvas_writePixelsWithImageInfo(null info)")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    const sk_image_info_t image_info_handle = SkImageInfo_MakeN32Premul(2, 2);
    auto *image_info = static_cast<reskia_image_info_t *>(static_sk_image_info_get_ptr(image_info_handle));
    if (!check(image_info != nullptr, "SkImageInfo_MakeN32Premul for canvas pixels")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    uint32_t pixels[4] = {};
    size_t top_layer_row_bytes = 0;
    SkCanvas_accessTopLayerPixels(canvas, image_info, &top_layer_row_bytes, nullptr);
    if (!check(!SkCanvas_readPixelsWithImageInfo(canvas, image_info, nullptr, SkImageInfo_minRowBytes(image_info), 0, 0), "SkCanvas_readPixelsWithImageInfo(null pixels)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_readPixelsWithImageInfo(canvas, image_info, pixels, 1, 0, 0), "SkCanvas_readPixelsWithImageInfo(invalid rowBytes)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_readPixelsWithPixmap(canvas, nullptr, 0, 0), "SkCanvas_readPixelsWithPixmap(null pixmap)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    reskia_pixmap_t *empty_pixmap = SkPixmap_new();
    if (!check(empty_pixmap != nullptr, "SkPixmap_new for canvas readPixels")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_readPixelsWithPixmap(canvas, empty_pixmap, 0, 0), "SkCanvas_readPixelsWithPixmap empty pixmap")) {
        SkPixmap_delete(empty_pixmap);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    SkPixmap_delete(empty_pixmap);
    if (!check(!SkCanvas_writePixelsWithImageInfo(canvas, image_info, nullptr, SkImageInfo_minRowBytes(image_info), 0, 0), "SkCanvas_writePixelsWithImageInfo(null pixels)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_writePixelsWithImageInfo(canvas, image_info, pixels, 1, 0, 0), "SkCanvas_writePixelsWithImageInfo(invalid rowBytes)")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }

    const sk_surface_t surface_handle = SkSurfaces_RasterWithoutRowBytes(image_info, nullptr);
    auto *surface = static_cast<reskia_surface_t *>(static_sk_surface_get_ptr(surface_handle));
    if (!check(surface != nullptr, "SkSurfaces_RasterWithoutRowBytes for canvas image lattice")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    const sk_image_t image_handle = SkSurface_makeImageSnapshot(surface);
    auto *image = static_cast<reskia_image_t *>(static_sk_image_get_ptr(image_handle));
    if (!check(image != nullptr, "SkSurface_makeImageSnapshot for canvas image lattice")) {
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    const sk_rect_t dst_handle = SkRect_MakeXYWH(0.0f, 0.0f, 2.0f, 2.0f);
    auto *dst = static_cast<reskia_rect_t *>(static_sk_rect_get_ptr(dst_handle));
    const sk_i_rect_t center_handle = SkIRect_MakeXYWH(0, 0, 1, 1);
    auto *center = static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(center_handle));
    if (!check(dst != nullptr && center != nullptr, "canvas image lattice/nine rects")) {
        static_sk_i_rect_delete(center_handle);
        static_sk_rect_delete(dst_handle);
        static_sk_image_delete(image_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    SkCanvas_drawImageLattice(canvas, image, nullptr, dst);
    const auto *c_lattice = reinterpret_cast<const reskia_lattice_t *>(&pixels);
    SkCanvas_drawImageLattice(canvas, image, c_lattice, nullptr);
    SkCanvas_drawImageLatticeWithFilter(canvas, image, nullptr, dst, 0, nullptr);
    SkCanvas_drawImageLatticeWithFilter(canvas, image, c_lattice, nullptr, 0, nullptr);
    SkCanvas_drawImageNine(canvas, image, nullptr, dst, 0, nullptr);
    SkCanvas_drawImageNine(canvas, image, center, nullptr, 0, nullptr);

    static_sk_i_rect_delete(center_handle);
    static_sk_rect_delete(dst_handle);
    static_sk_image_delete(image_handle);
    static_sk_surface_delete(surface_handle);
    static_sk_image_info_delete(image_info_handle);
    if (!check(!SkCanvas_quickReject(canvas, nullptr), "SkCanvas_quickReject(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 9;
    }
    if (!check(!SkCanvas_quickRejectRect(canvas, nullptr), "SkCanvas_quickRejectRect(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 10;
    }

    SkCanvas_delete(canvas);
    return 0;
}
