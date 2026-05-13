#include "capi/sk_canvas.h"
#include "capi/sk_bitmap.h"
#include "capi/sk_data.h"
#include "capi/sk_font.h"
#include "capi/sk_i_rect.h"
#include "capi/sk_i_point.h"
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
#include "capi/sk_rsx_form.h"
#include "capi/sk_sampling_options.h"
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
#include "handles/static_sk_i_point.h"
#include "handles/static_sk_i_size.h"
#include "handles/static_sk_m_44.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_picture.h"
#include "handles/static_sk_point.h"
#include "handles/static_sk_r_rect.h"
#include "handles/static_sk_rect.h"
#include "handles/static_sk_surface.h"
#include "handles/static_sk_shader.h"
#include "handles/static_sk_rsx_form.h"
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
    if (!check(SkCanvas_getDeviceClipBounds(nullptr) == 0, "SkCanvas_getDeviceClipBounds(nullptr)")) {
        return 1;
    }
    if (!check(!SkCanvas_getDeviceClipBoundsInto(nullptr, nullptr), "SkCanvas_getDeviceClipBoundsInto(nullptr)")) {
        return 1;
    }
    if (!check(SkCanvas_getLocalClipBounds(nullptr) == 0, "SkCanvas_getLocalClipBounds(nullptr)")) {
        return 1;
    }
    if (!check(!SkCanvas_getLocalClipBoundsInto(nullptr, nullptr), "SkCanvas_getLocalClipBoundsInto(nullptr)")) {
        return 1;
    }
    if (!check(!SkCanvas_readPixels(nullptr, nullptr, 0, 0), "SkCanvas_readPixels(nullptr)")) {
        return 2;
    }
    if (!check(!SkCanvas_readPixelsWithPixmap(nullptr, nullptr, 0, 0), "SkCanvas_readPixelsWithPixmap(nullptr)")) {
        return 2;
    }
    if (!check(!SkCanvas_writePixels(nullptr, nullptr, 0, 0), "SkCanvas_writePixels(nullptr)")) {
        return 2;
    }
    if (!check(!SkCanvas_writePixelsWithImageInfo(nullptr, nullptr, nullptr, 0, 0, 0), "SkCanvas_writePixelsWithImageInfo(nullptr)")) {
        return 2;
    }
    if (!check(!SkCanvas_quickReject(nullptr, nullptr), "SkCanvas_quickReject(nullptr)")) {
        return 3;
    }
    if (!check(!SkCanvas_quickRejectRect(nullptr, nullptr), "SkCanvas_quickRejectRect(nullptr)")) {
        return 4;
    }
    if (!check(SkCanvas_getLocalToDevice(nullptr) == 0, "SkCanvas_getLocalToDevice(nullptr)")) {
        return 4;
    }
    if (!check(SkCanvas_getLocalToDeviceAs3x3(nullptr) == 0, "SkCanvas_getLocalToDeviceAs3x3(nullptr)")) {
        return 4;
    }
    if (!check(SkCanvas_getTotalMatrix(nullptr) == 0, "SkCanvas_getTotalMatrix(nullptr)")) {
        return 4;
    }
    if (!check(SkCanvas_getBaseLayerSize(nullptr) == 0, "SkCanvas_getBaseLayerSize(nullptr)")) {
        return 4;
    }
    if (!check(SkCanvas_getBaseProps(nullptr) == 0, "SkCanvas_getBaseProps(nullptr)")) {
        return 4;
    }
    if (!check(!SkCanvas_getProps(nullptr, nullptr), "SkCanvas_getProps(nullptr)")) {
        return 4;
    }
    if (!check(SkCanvas_getSurface(nullptr) == nullptr, "SkCanvas_getSurface(nullptr)")) {
        return 4;
    }
    if (!check(SkCanvas_getTopProps(nullptr) == 0, "SkCanvas_getTopProps(nullptr)")) {
        return 4;
    }
    if (!check(SkCanvas_imageInfo(nullptr) == 0, "SkCanvas_imageInfo(nullptr)")) {
        return 4;
    }
    if (!check(!SkCanvas_isClipEmpty(nullptr), "SkCanvas_isClipEmpty(nullptr)")) {
        return 4;
    }
    if (!check(!SkCanvas_isClipRect(nullptr), "SkCanvas_isClipRect(nullptr)")) {
        return 4;
    }

    SkCanvas_resetMatrix(nullptr);
    SkCanvas_restore(nullptr);
    SkCanvas_restoreToCount(nullptr, 1);
    SkCanvas_rotate(nullptr, 1.0f);
    SkCanvas_rotateAround(nullptr, 1.0f, 0.0f, 0.0f);
    if (!check(SkCanvas_save(nullptr) == 0, "SkCanvas_save(nullptr)")) {
        return 5;
    }
    SkCanvas_scale(nullptr, 1.0f, 1.0f);
    SkCanvas_setMatrix(nullptr, nullptr);
    SkCanvas_setMatrix3x3(nullptr, nullptr);
    SkCanvas_skew(nullptr, 1.0f, 1.0f);
    SkCanvas_translate(nullptr, 1.0f, 1.0f);
    SkCanvas_drawPath(nullptr, nullptr, nullptr);
    SkCanvas_drawRegion(nullptr, nullptr, nullptr);
    SkCanvas_drawPaint(nullptr, nullptr);
    SkCanvas_private_draw_shadow_rec(nullptr, nullptr, nullptr);
    SkCanvas_drawAnnotation(nullptr, nullptr, nullptr, 0);
    SkCanvas_drawAnnotationWithDataPtr(nullptr, nullptr, nullptr, nullptr);
    SkCanvas_drawArc(nullptr, nullptr, 0.0f, 0.0f, false, nullptr);
    SkCanvas_drawOval(nullptr, nullptr, nullptr);
    SkCanvas_drawRect(nullptr, 0, nullptr);
    SkCanvas_drawRoundRect(nullptr, nullptr, 0.0f, 0.0f, nullptr);
    SkCanvas_drawRRect(nullptr, nullptr, nullptr);
    SkCanvas_drawDRRect(nullptr, nullptr, nullptr, nullptr);
    SkCanvas_drawMesh(nullptr, nullptr, 0, nullptr);
    SkCanvas_drawPoints(nullptr, 0, 1, nullptr, nullptr);
    SkCanvas_drawLine(nullptr, 0, 0, nullptr);
    SkCanvas_drawLineXY(nullptr, 0.0f, 0.0f, 1.0f, 1.0f, nullptr);
    SkCanvas_drawPoint(nullptr, 0, nullptr);
    SkCanvas_drawPointXY(nullptr, 0.0f, 0.0f, nullptr);
    SkCanvas_drawCircle(nullptr, 0, 1.0f, nullptr);
    SkCanvas_drawCircleAt(nullptr, 0.0f, 0.0f, 1.0f, nullptr);
    SkCanvas_drawSimpleText(nullptr, nullptr, 1, 0, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawString(nullptr, nullptr, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawStringObject(nullptr, nullptr, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawGlyphs(nullptr, 1, nullptr, nullptr, nullptr, 0, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsAtPositions(nullptr, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawGlyphsWithXforms(nullptr, 1, nullptr, nullptr, 0, nullptr, nullptr);
    SkCanvas_drawAtlas(nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0, nullptr, nullptr, nullptr);
    SkCanvas_drawAtlas(nullptr, nullptr, nullptr, nullptr, nullptr, 1, 0, nullptr, nullptr, nullptr);
    SkCanvas_experimental_DrawEdgeAAImageSet(nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAImageSet(nullptr, nullptr, 1, nullptr, nullptr, nullptr, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAQuad(nullptr, nullptr, nullptr, 0, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAQuadU32Color(nullptr, nullptr, nullptr, 0, 0, 0);
    SkCanvas_drawDrawable(nullptr, nullptr, nullptr);
    SkCanvas_drawDrawableAt(nullptr, nullptr, 0.0f, 0.0f);
    SkCanvas_drawPicture(nullptr, 0);
    SkCanvas_drawPictureHandleWithMatrixPaint(nullptr, 0, nullptr, nullptr);
    SkCanvas_drawPicturePtr(nullptr, nullptr);
    SkCanvas_drawPicturePtrWithMatrixPaint(nullptr, nullptr, nullptr, nullptr);
    SkCanvas_drawTextBlob(nullptr, 0, 0.0f, 0.0f, nullptr);
    SkCanvas_drawTextBlobPtr(nullptr, nullptr, 0.0f, 0.0f, nullptr);
    SkCanvas_drawVertices(nullptr, 0, 0, nullptr);
    SkCanvas_drawVerticesPtr(nullptr, nullptr, 0, nullptr);
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
    if (!check(SkCanvas_newFromBitmap(nullptr) == nullptr, "SkCanvas_newFromBitmap(nullptr)")) {
        return 5;
    }
    if (!check(SkCanvas_newFromBitmapWithProps(nullptr, nullptr) == nullptr, "SkCanvas_newFromBitmapWithProps(nullptr)")) {
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
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, nullptr, 1, nullptr, nullptr, nullptr, nullptr, 999999);
    SkCanvas_drawDrawable(canvas, nullptr, nullptr);
    SkCanvas_drawDrawableAt(canvas, nullptr, 0.0f, 0.0f);
    SkCanvas_drawMesh(canvas, nullptr, 0, nullptr);
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
    if (!check(SkCanvas_saveLayerAlpha(canvas, nullptr, 256) == 0, "SkCanvas_saveLayerAlpha invalid alpha")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(SkCanvas_saveLayerAlpha(canvas, nullptr, 255) > 0, "SkCanvas_saveLayerAlpha optional bounds")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_restore(canvas);
    if (!check(SkCanvas_saveLayerAlphaf(canvas, nullptr, -0.1f) == 0, "SkCanvas_saveLayerAlphaf negative alpha")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    if (!check(SkCanvas_saveLayerAlphaf(canvas, nullptr, 1.1f) == 0, "SkCanvas_saveLayerAlphaf high alpha")) {
        SkCanvas_delete(canvas);
        return 7;
    }
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
    const sk_m_44_t local_to_device = SkCanvas_getLocalToDevice(canvas);
    if (!check(local_to_device != 0 && static_sk_m_44_get_ptr(local_to_device) != nullptr, "SkCanvas_getLocalToDevice valid canvas")) {
        if (local_to_device != 0) {
            static_sk_m_44_delete(local_to_device);
        }
        SkCanvas_delete(canvas);
        return 7;
    }
    static_sk_m_44_delete(local_to_device);
    const sk_matrix_t local_to_device_3x3 = SkCanvas_getLocalToDeviceAs3x3(canvas);
    if (!check(local_to_device_3x3 != 0 && static_sk_matrix_get_ptr(local_to_device_3x3) != nullptr, "SkCanvas_getLocalToDeviceAs3x3 valid canvas")) {
        if (local_to_device_3x3 != 0) {
            static_sk_matrix_delete(local_to_device_3x3);
        }
        SkCanvas_delete(canvas);
        return 7;
    }
    static_sk_matrix_delete(local_to_device_3x3);
    const sk_matrix_t total_matrix = SkCanvas_getTotalMatrix(canvas);
    if (!check(total_matrix != 0 && static_sk_matrix_get_ptr(total_matrix) != nullptr, "SkCanvas_getTotalMatrix valid canvas")) {
        if (total_matrix != 0) {
            static_sk_matrix_delete(total_matrix);
        }
        SkCanvas_delete(canvas);
        return 7;
    }
    static_sk_matrix_delete(total_matrix);
    const int saved = SkCanvas_save(canvas);
    if (!check(saved > 0, "SkCanvas_save valid canvas")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_scale(canvas, 1.0f, 1.0f);
    SkCanvas_rotate(canvas, 0.0f);
    SkCanvas_rotateAround(canvas, 0.0f, 0.0f, 0.0f);
    SkCanvas_skew(canvas, 0.0f, 0.0f);
    SkCanvas_resetMatrix(canvas);
    SkCanvas_restoreToCount(canvas, saved);

    reskia_paint_t *paint = SkPaint_new();
    if (!check(paint != nullptr, "SkPaint_new for canvas text blob")) {
        SkCanvas_delete(canvas);
        return 7;
    }
    SkCanvas_drawMesh(canvas, reinterpret_cast<const reskia_mesh_t *>(1), 999999, paint);
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
    SkCanvas_clipIRect(canvas, reinterpret_cast<const reskia_i_rect_t *>(1), 999999);
    SkCanvas_clipRect(canvas, nullptr, false);
    SkCanvas_clipRectWithOp(canvas, nullptr, 0);
    SkCanvas_clipRectWithOp(canvas, reinterpret_cast<const reskia_rect_t *>(1), 999999);
    SkCanvas_clipRectWithOpAA(canvas, nullptr, 0, false);
    SkCanvas_clipRectWithOpAA(canvas, reinterpret_cast<const reskia_rect_t *>(1), 999999, false);
    SkCanvas_clipRRect(canvas, nullptr, false);
    SkCanvas_clipRRectWithOp(canvas, nullptr, 0);
    SkCanvas_clipRRectWithOp(canvas, reinterpret_cast<const reskia_r_rect_t *>(1), 999999);
    SkCanvas_clipRRectWithOpAA(canvas, nullptr, 0, false);
    SkCanvas_clipRRectWithOpAA(canvas, reinterpret_cast<const reskia_r_rect_t *>(1), 999999, false);
    SkCanvas_clipPath(canvas, nullptr, false);
    SkCanvas_clipPathWithOp(canvas, nullptr, 0);
    SkCanvas_clipPathWithOp(canvas, reinterpret_cast<const reskia_path_t *>(1), 999999);
    SkCanvas_clipPathWithOpAA(canvas, nullptr, 0, false);
    SkCanvas_clipPathWithOpAA(canvas, reinterpret_cast<const reskia_path_t *>(1), 999999, false);
    SkCanvas_clipShader(canvas, 0, 0);
    SkCanvas_clipShader(canvas, 999999, 0);
    SkCanvas_clipShader(canvas, 999999, 999999);
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
    SkCanvas_clipRegion(canvas, nullptr, 0);
    SkCanvas_clipRegion(canvas, reinterpret_cast<const reskia_region_t *>(1), 999999);
    SkCanvas_clipRegion(canvas, region, 0);
    SkRegion_delete(region);
    SkPoint patch_cubics[12] = {};
    SkPoint patch_tex_coords[4] = {};
    const auto *patch_cubics_input = reinterpret_cast<const reskia_point_t *>(patch_cubics);
    const auto *patch_tex_coords_input = reinterpret_cast<const reskia_point_t *>(patch_tex_coords);
    SkCanvas_drawPatch(canvas, nullptr, nullptr, patch_tex_coords_input, 0, paint);
    SkCanvas_drawPatch(canvas, patch_cubics_input, nullptr, nullptr, 0, paint);
    SkCanvas_drawPatch(canvas, patch_cubics_input, nullptr, patch_tex_coords_input, 0, nullptr);
    SkCanvas_drawPatch(canvas, patch_cubics_input, nullptr, patch_tex_coords_input, -1, paint);
    SkCanvas_drawPatch(canvas, patch_cubics_input, nullptr, patch_tex_coords_input, 999999, paint);
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
    const SkPoint draw_points[] = {SkPoint::Make(0.0f, 0.0f), SkPoint::Make(1.0f, 1.0f)};
    SkCanvas_drawPoints(canvas, 999999, 0, nullptr, paint);
    SkCanvas_drawPoints(canvas, 999999, 1, reinterpret_cast<const reskia_point_t *>(draw_points), paint);
    SkCanvas_drawPoints(canvas, 0, 1, nullptr, paint);
    SkCanvas_drawPoints(canvas, 0, 1, reinterpret_cast<const reskia_point_t *>(draw_points), nullptr);
    SkCanvas_drawPoints(canvas, 0, 0, nullptr, paint);
    SkCanvas_drawPoints(canvas, 0, 2, reinterpret_cast<const reskia_point_t *>(draw_points), paint);
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
    SkCanvas_experimental_DrawEdgeAAQuad(canvas, nullptr, nullptr, 0, canvas_color_input, 0);
    SkCanvas_experimental_DrawEdgeAAQuad(canvas, round_rect, nullptr, 0, nullptr, 0);
    SkCanvas_experimental_DrawEdgeAAQuad(canvas, round_rect, nullptr, 999999, canvas_color_input, 0);
    SkCanvas_experimental_DrawEdgeAAQuad(canvas, round_rect, nullptr, 0, canvas_color_input, -1);
    SkCanvas_experimental_DrawEdgeAAQuad(canvas, round_rect, nullptr, 0, canvas_color_input, 999999);
    SkCanvas_experimental_DrawEdgeAAQuad(canvas, round_rect, nullptr, 0, canvas_color_input, 0);
    SkCanvas_experimental_DrawEdgeAAQuadU32Color(canvas, nullptr, nullptr, 0, 0xFF000000u, 0);
    SkCanvas_experimental_DrawEdgeAAQuadU32Color(canvas, round_rect, nullptr, 999999, 0xFF000000u, 0);
    SkCanvas_experimental_DrawEdgeAAQuadU32Color(canvas, round_rect, nullptr, 0, 0xFF000000u, -1);
    SkCanvas_experimental_DrawEdgeAAQuadU32Color(canvas, round_rect, nullptr, 0, 0xFF000000u, 999999);
    SkCanvas_experimental_DrawEdgeAAQuadU32Color(canvas, round_rect, nullptr, 0, 0xFF000000u, 0);
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
    const sk_point_t glyph_origin_handle = SkPoint_Make(0.0f, 0.0f);
    auto *glyph_origin = static_cast<reskia_point_t *>(static_sk_point_get_ptr(glyph_origin_handle));
    if (!check(glyph_origin != nullptr, "SkPoint_Make for canvas glyph origin")) {
        if (glyph_origin_handle != 0) {
            static_sk_point_delete(glyph_origin_handle);
        }
        SkFont_delete(font);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    const sk_rsx_form_t glyph_xform_handle = SkRSXform_Make(1.0f, 0.0f, 0.0f, 0.0f);
    auto *glyph_xform = static_cast<reskia_rsxform_t *>(static_sk_rsx_form_get_ptr(glyph_xform_handle));
    if (!check(glyph_xform != nullptr, "SkRSXform_Make for canvas glyph xforms")) {
        if (glyph_xform_handle != 0) {
            static_sk_rsx_form_delete(glyph_xform_handle);
        }
        static_sk_point_delete(glyph_origin_handle);
        SkFont_delete(font);
        SkPaint_delete(paint);
        SkCanvas_delete(canvas);
        return 7;
    }
    const uint16_t glyphs[] = {0};
    const SkPoint glyph_positions[] = {SkPoint::Make(0.0f, 0.0f)};
    const uint32_t glyph_clusters[] = {0};
    const char glyph_text[] = "A";
    SkCanvas_drawGlyphs(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), glyph_clusters, 1, nullptr, glyph_origin_handle, font, paint);
    SkCanvas_drawGlyphs(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), glyph_clusters, 1, glyph_text, 999999, font, paint);
    SkCanvas_drawGlyphs(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), glyph_clusters, 1, glyph_text, glyph_origin_handle, nullptr, paint);
    SkCanvas_drawGlyphs(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), glyph_clusters, 1, glyph_text, glyph_origin_handle, font, nullptr);
    SkCanvas_drawGlyphs(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), glyph_clusters, 1, glyph_text, glyph_origin_handle, font, paint);
    SkCanvas_drawGlyphsAtPositions(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), 999999, font, paint);
    SkCanvas_drawGlyphsAtPositions(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), glyph_origin_handle, nullptr, paint);
    SkCanvas_drawGlyphsAtPositions(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), glyph_origin_handle, font, nullptr);
    SkCanvas_drawGlyphsAtPositions(canvas, 1, glyphs, reinterpret_cast<const reskia_point_t *>(glyph_positions), glyph_origin_handle, font, paint);
    SkCanvas_drawGlyphsWithXforms(canvas, 1, glyphs, glyph_xform, 999999, font, paint);
    SkCanvas_drawGlyphsWithXforms(canvas, 1, glyphs, glyph_xform, glyph_origin_handle, nullptr, paint);
    SkCanvas_drawGlyphsWithXforms(canvas, 1, glyphs, glyph_xform, glyph_origin_handle, font, nullptr);
    SkCanvas_drawGlyphsWithXforms(canvas, 1, glyphs, glyph_xform, glyph_origin_handle, font, paint);
    static_sk_rsx_form_delete(glyph_xform_handle);
    static_sk_point_delete(glyph_origin_handle);
    const char simple_text[] = "A";
    SkCanvas_drawSimpleText(canvas, simple_text, 1, 999999, 0.0f, 0.0f, font, paint);
    SkCanvas_drawSimpleText(canvas, simple_text, 1, 0, 0.0f, 0.0f, nullptr, paint);
    SkCanvas_drawSimpleText(canvas, simple_text, 1, 0, 0.0f, 0.0f, font, nullptr);
    SkCanvas_drawSimpleText(canvas, simple_text, 1, 0, 0.0f, 0.0f, font, paint);
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
    SkCanvas_drawVertices(canvas, vertices_handle, -1, paint);
    SkCanvas_drawVertices(canvas, vertices_handle, 999999, paint);
    SkCanvas_drawVerticesPtr(canvas, vertices, 0, nullptr);
    SkCanvas_drawVerticesPtr(canvas, vertices, -1, paint);
    SkCanvas_drawVerticesPtr(canvas, vertices, 999999, paint);
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
    if (!check(!SkCanvas_writePixels(canvas, nullptr, 0, 0), "SkCanvas_writePixels(canvas, nullptr)")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    reskia_bitmap_t *empty_write_bitmap = SkBitmap_new();
    if (!check(empty_write_bitmap != nullptr, "SkBitmap_new for canvas writePixels")) {
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(!SkCanvas_writePixels(canvas, empty_write_bitmap, 0, 0), "SkCanvas_writePixels empty bitmap")) {
        SkBitmap_delete(empty_write_bitmap);
        SkCanvas_delete(canvas);
        return 8;
    }
    SkBitmap_delete(empty_write_bitmap);
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
    if (!check(SkCanvas_MakeRasterDirect(image_info, pixels, 1, nullptr) == 0, "SkCanvas_MakeRasterDirect invalid rowBytes")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(SkCanvas_MakeRasterDirectN32(2, 2, pixels, 1) == 0, "SkCanvas_MakeRasterDirectN32 invalid rowBytes")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    size_t top_layer_row_bytes = 0;
    SkCanvas_accessTopLayerPixels(canvas, image_info, &top_layer_row_bytes, nullptr);
    reskia_bitmap_t *layer_bitmap = SkBitmap_new();
    if (!check(layer_bitmap != nullptr, "SkBitmap_new for canvas borrowed pixels")) {
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    SkBitmap_allocN32Pixels(layer_bitmap, 2, 2, false);
    reskia_canvas_t *layer_canvas = SkCanvas_newFromBitmap(layer_bitmap);
    if (!check(layer_canvas != nullptr, "SkCanvas_newFromBitmap for borrowed pixels")) {
        SkBitmap_delete(layer_bitmap);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    const sk_i_point_t origin_handle = SkIPoint_Make(0, 0);
    auto *origin = static_cast<reskia_i_point_t *>(static_sk_i_point_get_ptr(origin_handle));
    if (!check(origin != nullptr, "SkIPoint_Make for canvas borrowed pixels")) {
        static_sk_i_point_delete(origin_handle);
        SkCanvas_delete(layer_canvas);
        SkBitmap_delete(layer_bitmap);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    size_t borrowed_row_bytes = 0;
    void *borrowed_pixels = SkCanvas_accessTopLayerPixels(layer_canvas, image_info, &borrowed_row_bytes, origin);
    if (!check(borrowed_pixels != nullptr && borrowed_row_bytes >= SkImageInfo_minRowBytes(image_info), "SkCanvas_accessTopLayerPixels borrowed storage and optional outs")) {
        static_sk_i_point_delete(origin_handle);
        SkCanvas_delete(layer_canvas);
        SkBitmap_delete(layer_bitmap);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(SkCanvas_accessTopLayerPixels(layer_canvas, nullptr, nullptr, nullptr) != nullptr, "SkCanvas_accessTopLayerPixels optional outs null")) {
        static_sk_i_point_delete(origin_handle);
        SkCanvas_delete(layer_canvas);
        SkBitmap_delete(layer_bitmap);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    reskia_pixmap_t *borrowed_pixmap = SkPixmap_new();
    if (!check(borrowed_pixmap != nullptr, "SkPixmap_new for canvas peekPixels")) {
        static_sk_i_point_delete(origin_handle);
        SkCanvas_delete(layer_canvas);
        SkBitmap_delete(layer_bitmap);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    if (!check(SkCanvas_peekPixels(layer_canvas, borrowed_pixmap), "SkCanvas_peekPixels borrowed storage")) {
        SkPixmap_delete(borrowed_pixmap);
        static_sk_i_point_delete(origin_handle);
        SkCanvas_delete(layer_canvas);
        SkBitmap_delete(layer_bitmap);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    SkPixmap_delete(borrowed_pixmap);
    static_sk_i_point_delete(origin_handle);
    SkCanvas_delete(layer_canvas);
    SkBitmap_delete(layer_bitmap);
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
    SkCanvas_drawImageLatticeWithFilter(canvas, image, c_lattice, dst, 999999, nullptr);
    SkCanvas_drawImageNine(canvas, image, nullptr, dst, 0, nullptr);
    SkCanvas_drawImageNine(canvas, image, center, nullptr, 0, nullptr);
    SkCanvas_drawImageNine(canvas, image, center, dst, 999999, nullptr);
    reskia_sampling_options_t *image_sampling = SkSamplingOptions_new();
    if (!check(image_sampling != nullptr, "SkSamplingOptions_new for canvas drawImage")) {
        static_sk_i_rect_delete(center_handle);
        static_sk_rect_delete(dst_handle);
        static_sk_image_delete(image_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    SkCanvas_drawImage(canvas, image_handle, 0.0f, 0.0f);
    SkCanvas_drawImageHandleWithSampling(canvas, image_handle, 0.0f, 0.0f, image_sampling, nullptr);
    SkCanvas_drawImageRect(canvas, image_handle, dst, image_sampling, nullptr);
    SkCanvas_drawImageRectHandleWithSrcDst(canvas, image_handle, dst, dst, image_sampling, nullptr, 0);
    SkCanvas_drawImageRectHandleWithSrcDst(canvas, image_handle, dst, dst, image_sampling, nullptr, 999999);
    SkCanvas_drawImagePtr(canvas, image, 0.0f, 0.0f);
    SkCanvas_drawImagePtrWithSampling(canvas, image, 0.0f, 0.0f, image_sampling, nullptr);
    SkCanvas_drawImagePtrWithSampling(canvas, image, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawImageRectPtr(canvas, image, dst, image_sampling, nullptr);
    SkCanvas_drawImageRectPtr(canvas, image, dst, nullptr, nullptr);
    SkCanvas_drawImageRectPtrWithSrcDst(canvas, image, dst, dst, image_sampling, nullptr, 0);
    SkCanvas_drawImageRectPtrWithSrcDst(canvas, image, dst, dst, image_sampling, nullptr, 999999);
    SkCanvas_drawImageHandleWithSampling(canvas, image_handle, 0.0f, 0.0f, nullptr, nullptr);
    SkCanvas_drawImageRect(canvas, image_handle, dst, nullptr, nullptr);
    const sk_rsx_form_t atlas_xform_handle = SkRSXform_Make(1.0f, 0.0f, 0.0f, 0.0f);
    auto *atlas_xform = static_cast<reskia_rsxform_t *>(static_sk_rsx_form_get_ptr(atlas_xform_handle));
    if (!check(atlas_xform != nullptr, "SkRSXform_Make for canvas drawAtlas")) {
        if (atlas_xform_handle != 0) {
            static_sk_rsx_form_delete(atlas_xform_handle);
        }
        SkSamplingOptions_delete(image_sampling);
        static_sk_i_rect_delete(center_handle);
        static_sk_rect_delete(dst_handle);
        static_sk_image_delete(image_handle);
        static_sk_surface_delete(surface_handle);
        static_sk_image_info_delete(image_info_handle);
        SkCanvas_delete(canvas);
        return 8;
    }
    SkCanvas_drawAtlas(canvas, nullptr, atlas_xform, dst, nullptr, 1, 0, image_sampling, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, image, nullptr, dst, nullptr, 1, 0, image_sampling, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, image, atlas_xform, nullptr, nullptr, 1, 0, image_sampling, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, image, atlas_xform, dst, nullptr, 1, 0, nullptr, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, image, atlas_xform, dst, nullptr, 1, -1, image_sampling, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, image, atlas_xform, dst, nullptr, 1, 999999, image_sampling, nullptr, nullptr);
    SkCanvas_drawAtlas(canvas, image, atlas_xform, dst, nullptr, 1, 0, image_sampling, nullptr, nullptr);
    const auto *fake_image_set = reinterpret_cast<const reskia_image_set_entry_t *>(1);
    SkCanvas_experimental_DrawEdgeAAImageSet(canvas, fake_image_set, 1, nullptr, nullptr, nullptr, nullptr, 0);
    static_sk_rsx_form_delete(atlas_xform_handle);
    SkSamplingOptions_delete(image_sampling);

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
    const sk_i_size_t base_layer_size = SkCanvas_getBaseLayerSize(canvas);
    if (!check(base_layer_size != 0 && static_sk_i_size_get_ptr(base_layer_size) != nullptr, "SkCanvas_getBaseLayerSize returned handle")) {
        if (base_layer_size != 0) {
            static_sk_i_size_delete(base_layer_size);
        }
        SkCanvas_delete(canvas);
        return 10;
    }
    static_sk_i_size_delete(base_layer_size);
    const sk_i_rect_t device_clip_bounds = SkCanvas_getDeviceClipBounds(canvas);
    if (!check(device_clip_bounds != 0 && static_sk_i_rect_get_ptr(device_clip_bounds) != nullptr, "SkCanvas_getDeviceClipBounds returned handle")) {
        if (device_clip_bounds != 0) {
            static_sk_i_rect_delete(device_clip_bounds);
        }
        SkCanvas_delete(canvas);
        return 10;
    }
    if (!check(!SkCanvas_getDeviceClipBoundsInto(canvas, nullptr), "SkCanvas_getDeviceClipBoundsInto null out")) {
        static_sk_i_rect_delete(device_clip_bounds);
        SkCanvas_delete(canvas);
        return 10;
    }
    SkCanvas_getDeviceClipBoundsInto(canvas, static_cast<reskia_i_rect_t *>(static_sk_i_rect_get_ptr(device_clip_bounds)));
    static_sk_i_rect_delete(device_clip_bounds);
    const sk_rect_t local_clip_bounds = SkCanvas_getLocalClipBounds(canvas);
    if (!check(local_clip_bounds != 0 && static_sk_rect_get_ptr(local_clip_bounds) != nullptr, "SkCanvas_getLocalClipBounds returned handle")) {
        if (local_clip_bounds != 0) {
            static_sk_rect_delete(local_clip_bounds);
        }
        SkCanvas_delete(canvas);
        return 10;
    }
    if (!check(!SkCanvas_getLocalClipBoundsInto(canvas, nullptr), "SkCanvas_getLocalClipBoundsInto null out")) {
        static_sk_rect_delete(local_clip_bounds);
        SkCanvas_delete(canvas);
        return 10;
    }
    SkCanvas_getLocalClipBoundsInto(canvas, static_cast<reskia_rect_t *>(static_sk_rect_get_ptr(local_clip_bounds)));
    static_sk_rect_delete(local_clip_bounds);

    SkCanvas_delete(canvas);
    return 0;
}
