//
// Created by dolphilia on 2024/01/06.
//

#include "sk_canvas.h"

#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkDrawable.h"
#include "include/core/SkFont.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkPixmap.h"
#include "include/core/SkPoint.h"
#include "include/core/SkRRect.h"
#include "include/core/SkRegion.h"
#include "include/core/SkRect.h"
#include "include/core/SkString.h"
#include "include/core/SkSurfaceProps.h"
#include "include/core/SkTextBlob.h"
#include "include/core/SkVertices.h"
#include "include/core/SkMesh.h"

#include <utility>

#include "../handles/static_sk_canvas.h"
#include "../handles/static_sk_surface.h"
#include "../handles/static_sk_vertices.h"
#include "../handles/static_sk_text_blob.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_surface_props.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_m_44.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_image_info.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_blender-internal.h"
#include "../handles/static_sk_canvas-internal.h"
#include "../handles/static_sk_surface-internal.h"
#include "../handles/static_sk_vertices-internal.h"
#include "../handles/static_sk_text_blob-internal.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_picture-internal.h"
#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_surface_props-internal.h"
#include "../handles/static_sk_i_rect-internal.h"
#include "../handles/static_sk_m_44-internal.h"
#include "../handles/static_sk_matrix-internal.h"
#include "../handles/static_sk_image_info-internal.h"
#include "../handles/static_sk_point-internal.h"
#include "../handles/static_sk_i_size-internal.h"

namespace {

sk_canvas_t make_canvas_handle(std::unique_ptr<SkCanvas> canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_canvas_make(std::move(canvas));
}

bool has_image_handle(sk_image_t image) {
    return image != 0 && static_sk_image_get_ptr(image) != nullptr;
}

bool has_text_blob_handle(sk_text_blob_t text_blob) {
    return text_blob != 0 && static_sk_text_blob_get_ptr(text_blob) != nullptr;
}

bool has_vertices_handle(sk_vertices_t vertices) {
    return vertices != 0 && static_sk_vertices_get_ptr(vertices) != nullptr;
}

bool has_rect_handle(sk_rect_t rect) {
    return rect != 0 && static_sk_rect_get_ptr(rect) != nullptr;
}

bool has_point_handle(sk_point_t point) {
    return point != 0 && static_sk_point_get_ptr(point) != nullptr;
}

bool has_optional_data_handle(sk_data_t data) {
    return data == 0 || static_sk_data_get_ptr(data) != nullptr;
}

bool valid_blend_mode(reskia_blend_mode_t mode) {
    return mode >= 0 && mode <= static_cast<reskia_blend_mode_t>(SkBlendMode::kLastMode);
}

bool has_valid_pixels(const reskia_image_info_t *info, const void *pixels, size_t rowBytes) {
    if (info == nullptr || pixels == nullptr) {
        return false;
    }
    return reinterpret_cast<const SkImageInfo *>(info)->validRowBytes(rowBytes);
}

}  // namespace

extern "C" {

reskia_canvas_t *SkCanvas_new(void) {
    return reinterpret_cast<reskia_canvas_t *>(new SkCanvas());
}

reskia_canvas_t *SkCanvas_newWithSizeProps(int width, int height, const reskia_surface_props_t * props) {
    return reinterpret_cast<reskia_canvas_t *>(new SkCanvas(width, height, reinterpret_cast<const SkSurfaceProps *>(props)));
}

reskia_canvas_t *SkCanvas_newFromBitmap(reskia_bitmap_t * bitmap) {
    if (bitmap == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(new SkCanvas(* reinterpret_cast<SkBitmap *>(bitmap)));
}

reskia_canvas_t *SkCanvas_newFromBitmapWithProps(const reskia_bitmap_t * bitmap, const reskia_surface_props_t * props) {
    if (bitmap == nullptr || props == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(new SkCanvas(* reinterpret_cast<const SkBitmap *>(bitmap), * reinterpret_cast<const SkSurfaceProps *>(props)));
}

void SkCanvas_delete(reskia_canvas_t *canvas) {
    delete reinterpret_cast<SkCanvas *>(canvas);
}

void * SkCanvas_accessTopLayerPixels(reskia_canvas_t *canvas, reskia_image_info_t * info, size_t * rowBytes, reskia_i_point_t * origin) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->accessTopLayerPixels(reinterpret_cast<SkImageInfo *>(info), rowBytes, reinterpret_cast<SkIPoint *>(origin));
}

void * SkCanvas_accessTopRasterHandle(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->accessTopRasterHandle();
}

void SkCanvas_androidFramework_setDeviceClipRestriction(reskia_canvas_t *canvas, const reskia_i_rect_t * rect) {
    if (canvas == nullptr || rect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->androidFramework_setDeviceClipRestriction(* reinterpret_cast<const SkIRect *>(rect));
}

void SkCanvas_clear(reskia_canvas_t *canvas, const reskia_color_4f_t * color) {
    if (canvas == nullptr || color == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clear(* reinterpret_cast<const SkColor4f *>(color));
}

void SkCanvas_clearColor(reskia_canvas_t *canvas, uint32_t color) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clear(color);
}

void SkCanvas_clipIRect(reskia_canvas_t *canvas, const reskia_i_rect_t * irect, reskia_canvas_clip_op_t op) {
    if (canvas == nullptr || irect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipIRect(* reinterpret_cast<const SkIRect *>(irect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipPath(reskia_canvas_t *canvas, const reskia_path_t *path, bool doAntiAlias) {
    if (canvas == nullptr || path == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipPath(* reinterpret_cast<const SkPath *>(path), doAntiAlias);
}

void SkCanvas_clipPathWithOp(reskia_canvas_t *canvas, const reskia_path_t *path, reskia_canvas_clip_op_t op) {
    if (canvas == nullptr || path == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipPath(* reinterpret_cast<const SkPath *>(path), static_cast<SkClipOp>(op));
}

void SkCanvas_clipPathWithOpAA(reskia_canvas_t *canvas, const reskia_path_t *path, reskia_canvas_clip_op_t op, bool doAntiAlias) {
    if (canvas == nullptr || path == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipPath(* reinterpret_cast<const SkPath *>(path), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipRect(reskia_canvas_t *canvas, const reskia_rect_t * rect, bool doAntiAlias) {
    if (canvas == nullptr || rect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipRect(* reinterpret_cast<const SkRect *>(rect), doAntiAlias);
}

void SkCanvas_clipRectWithOp(reskia_canvas_t *canvas, const reskia_rect_t * rect, reskia_canvas_clip_op_t op) {
    if (canvas == nullptr || rect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipRect(* reinterpret_cast<const SkRect *>(rect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRectWithOpAA(reskia_canvas_t *canvas, const reskia_rect_t * rect, reskia_canvas_clip_op_t op, bool doAntiAlias) {
    if (canvas == nullptr || rect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipRect(* reinterpret_cast<const SkRect *>(rect), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipRegion(reskia_canvas_t *canvas, const reskia_region_t * deviceRgn, reskia_canvas_clip_op_t op) {
    if (canvas == nullptr || deviceRgn == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipRegion(* reinterpret_cast<const SkRegion *>(deviceRgn), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRRect(reskia_canvas_t *canvas, const reskia_r_rect_t * rrect, bool doAntiAlias) {
    if (canvas == nullptr || rrect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipRRect(* reinterpret_cast<const SkRRect *>(rrect), doAntiAlias);
}

void SkCanvas_clipRRectWithOp(reskia_canvas_t *canvas, const reskia_r_rect_t *rrect, reskia_canvas_clip_op_t op) {
    if (canvas == nullptr || rrect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipRRect(* reinterpret_cast<const SkRRect *>(rrect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRRectWithOpAA(reskia_canvas_t *canvas, const reskia_r_rect_t *rrect, reskia_canvas_clip_op_t op, bool doAntiAlias) {
    if (canvas == nullptr || rrect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipRRect(* reinterpret_cast<const SkRRect *>(rrect), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipShader(reskia_canvas_t *canvas, sk_shader_t shader, reskia_canvas_clip_op_t op) {
    if (canvas == nullptr || shader == 0) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->clipShader(static_sk_shader_get_entity(shader), static_cast<SkClipOp>(op));
}

void SkCanvas_concat(reskia_canvas_t *canvas, const reskia_m_44_t * m44) {
    if (canvas == nullptr || m44 == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->concat(* reinterpret_cast<const SkM44 *>(m44));
}

void SkCanvas_concatMatrix(reskia_canvas_t *canvas, const reskia_matrix_t * matrix) {
    if (canvas == nullptr || matrix == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->concat(* reinterpret_cast<const SkMatrix *>(matrix));
}

// virtual void SkCanvas_didConcat44(SkCanvas *canvas, const SkM44 *) {} // protected
// virtual void SkCanvas_didRestore(SkCanvas *canvas) {} // protected
// virtual void SkCanvas_didScale(SkCanvas *canvas, SkScalar SkScalar) {} // protected
// virtual void SkCanvas_didTranslate(SkCanvas *canvas, SkScalar SkScalar) {} // protected

void SkCanvas_discard(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->discard();
}

void SkCanvas_drawAnnotation(reskia_canvas_t *canvas, const reskia_rect_t * rect, const char * key, sk_data_t data) {
    if (canvas == nullptr || rect == nullptr || key == nullptr || !has_optional_data_handle(data)) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawAnnotation(* reinterpret_cast<const SkRect *>(rect), key, static_sk_data_get_entity(data));
}

void SkCanvas_drawAnnotationWithDataPtr(reskia_canvas_t *canvas, const reskia_rect_t * rect, const char * key, reskia_data_t * value) {
    if (canvas == nullptr || rect == nullptr || key == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawAnnotation(* reinterpret_cast<const SkRect *>(rect), key, reinterpret_cast<SkData *>(value));
}

void SkCanvas_drawArc(reskia_canvas_t *canvas, const reskia_rect_t * oval, float startAngle, float sweepAngle, bool useCenter, const reskia_paint_t * paint) {
    if (canvas == nullptr || oval == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawArc(* reinterpret_cast<const SkRect *>(oval), startAngle, sweepAngle, useCenter, * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawAtlas(reskia_canvas_t *canvas, const reskia_image_t * atlas, const reskia_rsxform_t * xform, const reskia_rect_t * tex, const uint32_t * colors, int count, reskia_blend_mode_t mode, const reskia_sampling_options_t * sampling, const reskia_rect_t * cullRect, const reskia_paint_t * paint) {
    if (canvas == nullptr || count <= 0) {
        return;
    }
    if (atlas == nullptr || xform == nullptr || tex == nullptr || sampling == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawAtlas(reinterpret_cast<const SkImage *>(atlas), reinterpret_cast<const SkRSXform *>(xform), reinterpret_cast<const SkRect *>(tex), reinterpret_cast<const SkColor *>(colors), count, static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkRect *>(cullRect), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawCircle(reskia_canvas_t *canvas, sk_point_t center, float radius, const reskia_paint_t * paint) {
    if (canvas == nullptr || !has_point_handle(center) || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawCircle(static_sk_point_get_entity(center), radius, * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawCircleAt(reskia_canvas_t *canvas, float cx, float cy, float radius, const reskia_paint_t * paint) {
    if (canvas == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawCircle(cx, cy, radius, * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawColor(reskia_canvas_t *canvas, const reskia_color_4f_t * color, reskia_blend_mode_t mode) {
    if (canvas == nullptr || color == nullptr || !valid_blend_mode(mode)) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawColor(* reinterpret_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkCanvas_drawColorU32(reskia_canvas_t *canvas, uint32_t color, reskia_blend_mode_t mode) {
    if (canvas == nullptr || !valid_blend_mode(mode)) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawColor(color, static_cast<SkBlendMode>(mode));
}

void SkCanvas_drawDrawable(reskia_canvas_t *canvas, reskia_drawable_t *drawable, const reskia_matrix_t *matrix) {
    if (canvas == nullptr || drawable == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawDrawable(reinterpret_cast<SkDrawable *>(drawable), reinterpret_cast<const SkMatrix *>(matrix));
}

void SkCanvas_drawDrawableAt(reskia_canvas_t *canvas, reskia_drawable_t *drawable, float x, float y) {
    if (canvas == nullptr || drawable == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawDrawable(reinterpret_cast<SkDrawable *>(drawable), x, y);
}

void SkCanvas_drawDRRect(reskia_canvas_t *canvas, const reskia_r_rect_t *outer, const reskia_r_rect_t *inner, const reskia_paint_t *paint) {
    if (canvas == nullptr || outer == nullptr || inner == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawDRRect(* reinterpret_cast<const SkRRect *>(outer), * reinterpret_cast<const SkRRect *>(inner), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphs(reskia_canvas_t *canvas, int count, const uint16_t * glyphs, const reskia_point_t * positions, const uint32_t * clusters, int textByteCount, const char * utf8text, sk_point_t origin, const reskia_font_t * font, const reskia_paint_t * paint) {
    if (canvas == nullptr || count <= 0) {
        return;
    }
    if (glyphs == nullptr || positions == nullptr || clusters == nullptr || textByteCount < 0 || (textByteCount > 0 && utf8text == nullptr) || origin == 0 || font == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawGlyphs(count, reinterpret_cast<const SkGlyphID *>(glyphs), reinterpret_cast<const SkPoint *>(positions), clusters, textByteCount, utf8text, static_sk_point_get_entity(origin), * reinterpret_cast<const SkFont *>(font), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphsAtPositions(reskia_canvas_t *canvas, int count, const uint16_t * glyphs, const reskia_point_t * positions, sk_point_t origin, const reskia_font_t * font, const reskia_paint_t * paint) {
    if (canvas == nullptr || count <= 0) {
        return;
    }
    if (glyphs == nullptr || positions == nullptr || origin == 0 || font == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawGlyphs(count, reinterpret_cast<const SkGlyphID *>(glyphs), reinterpret_cast<const SkPoint *>(positions), static_sk_point_get_entity(origin), * reinterpret_cast<const SkFont *>(font), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphsWithXforms(reskia_canvas_t *canvas, int count, const uint16_t * glyphs, const reskia_rsxform_t * xforms, sk_point_t origin, const reskia_font_t * font, const reskia_paint_t * paint) {
    if (canvas == nullptr || count <= 0) {
        return;
    }
    if (glyphs == nullptr || xforms == nullptr || origin == 0 || font == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawGlyphs(count, reinterpret_cast<const SkGlyphID *>(glyphs), reinterpret_cast<const SkRSXform *>(xforms), static_sk_point_get_entity(origin), * reinterpret_cast<const SkFont *>(font), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImage(reskia_canvas_t *canvas, sk_image_t image, float left, float top) {
    if (canvas == nullptr || !has_image_handle(image)) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_get_entity(image), left, top);
}

void SkCanvas_drawImageHandleWithSampling(reskia_canvas_t *canvas, sk_image_t image, float x, float y, const reskia_sampling_options_t * sampling, const reskia_paint_t * paint) {
    if (canvas == nullptr || !has_image_handle(image) || sampling == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_get_entity(image), x, y, * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImagePtrWithSampling(reskia_canvas_t *canvas, const reskia_image_t * image, float x, float y, const reskia_sampling_options_t * sampling, const reskia_paint_t * paint) {
    if (canvas == nullptr || image == nullptr || sampling == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(reinterpret_cast<const SkImage *>(image), x, y, * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImagePtr(reskia_canvas_t *canvas, const reskia_image_t * image, float left, float top) {
    if (canvas == nullptr || image == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(reinterpret_cast<const SkImage *>(image), left, top);
}

void SkCanvas_drawImageLattice(reskia_canvas_t *canvas, const reskia_image_t * image, const reskia_lattice_t * lattice, const reskia_rect_t * dst) {
    if (canvas == nullptr || image == nullptr || lattice == nullptr || dst == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImageLattice(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkCanvas::Lattice *>(lattice), * reinterpret_cast<const SkRect *>(dst));
}

void SkCanvas_drawImageLatticeWithFilter(reskia_canvas_t *canvas, const reskia_image_t * image, const reskia_lattice_t * lattice, const reskia_rect_t * dst, reskia_canvas_filter_mode_t filter, const reskia_paint_t * paint) {
    if (canvas == nullptr || image == nullptr || lattice == nullptr || dst == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImageLattice(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkCanvas::Lattice *>(lattice), * reinterpret_cast<const SkRect *>(dst), static_cast<SkFilterMode>(filter), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageNine(reskia_canvas_t *canvas, const reskia_image_t * image, const reskia_i_rect_t * center, const reskia_rect_t * dst, reskia_canvas_filter_mode_t filter, const reskia_paint_t * paint) {
    if (canvas == nullptr || image == nullptr || center == nullptr || dst == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImageNine(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkIRect *>(center), * reinterpret_cast<const SkRect *>(dst), static_cast<SkFilterMode>(filter), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRect(reskia_canvas_t *canvas, sk_image_t image, const reskia_rect_t * dst, const reskia_sampling_options_t * sampling, const reskia_paint_t * paint) {
    if (canvas == nullptr || !has_image_handle(image) || dst == nullptr || sampling == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImageRect(static_sk_image_get_entity(image), * reinterpret_cast<const SkRect *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRectHandleWithSrcDst(reskia_canvas_t *canvas, sk_image_t image, const reskia_rect_t * src, const reskia_rect_t * dst, const reskia_sampling_options_t * sampling, const reskia_paint_t * paint, reskia_canvas_src_rect_constraint_t constraint) {
    if (canvas == nullptr || !has_image_handle(image) || src == nullptr || dst == nullptr || sampling == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImageRect(static_sk_image_get_entity(image), * reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_drawImageRectPtr(reskia_canvas_t *canvas, const reskia_image_t * image, const reskia_rect_t * dst, const reskia_sampling_options_t * sampling, const reskia_paint_t * paint) {
    if (canvas == nullptr || image == nullptr || dst == nullptr || sampling == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImageRect(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkRect *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRectPtrWithSrcDst(reskia_canvas_t *canvas, const reskia_image_t * image, const reskia_rect_t * src, const reskia_rect_t * dst, const reskia_sampling_options_t * sampling, const reskia_paint_t * paint, reskia_canvas_src_rect_constraint_t constraint) {
    if (canvas == nullptr || image == nullptr || src == nullptr || dst == nullptr || sampling == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawImageRect(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkRect *>(src), * reinterpret_cast<const SkRect *>(dst), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_drawIRect(reskia_canvas_t *canvas, const reskia_i_rect_t * rect, const reskia_paint_t * paint) {
    if (canvas == nullptr || rect == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawIRect(* reinterpret_cast<const SkIRect *>(rect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawLine(reskia_canvas_t *canvas, sk_point_t p0, sk_point_t p1, const reskia_paint_t * paint) {
    if (canvas == nullptr || !has_point_handle(p0) || !has_point_handle(p1) || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawLine(static_sk_point_get_entity(p0), static_sk_point_get_entity(p1), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawLineXY(reskia_canvas_t *canvas, float x0, float y0, float x1, float y1, const reskia_paint_t * paint) {
    if (canvas == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawLine(x0, y0, x1, y1, * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawMesh(reskia_canvas_t *canvas, const reskia_mesh_t * mesh, sk_blender_t blender, const reskia_paint_t * paint) {
    if (canvas == nullptr || mesh == nullptr || blender == 0 || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawMesh(* reinterpret_cast<const SkMesh *>(mesh), static_sk_blender_get_entity(blender), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawOval(reskia_canvas_t *canvas, const reskia_rect_t * oval, const reskia_paint_t * paint) {
    if (canvas == nullptr || oval == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawOval(* reinterpret_cast<const SkRect *>(oval), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPaint(reskia_canvas_t *canvas, const reskia_paint_t * paint) {
    if (canvas == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPaint(* reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPatch(reskia_canvas_t *canvas, const reskia_point_t * cubics, const uint32_t colors[4], const reskia_point_t * texCoords, reskia_blend_mode_t mode, const reskia_paint_t * paint) {
    if (canvas == nullptr || cubics == nullptr || texCoords == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPatch(reinterpret_cast<const SkPoint *>(cubics), colors, reinterpret_cast<const SkPoint *>(texCoords), static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPath(reskia_canvas_t *canvas, const reskia_path_t * path, const reskia_paint_t * paint) {
    if (canvas == nullptr || path == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPath(* reinterpret_cast<const SkPath *>(path), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPicture(reskia_canvas_t *canvas, sk_picture_t picture) {
    if (canvas == nullptr || picture == 0) {
        return;
    }
    sk_sp<SkPicture> native_picture = static_sk_picture_get_entity(picture);
    if (!native_picture) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPicture(native_picture);
}

void SkCanvas_drawPictureHandleWithMatrixPaint(reskia_canvas_t *canvas, sk_picture_t picture, const reskia_matrix_t * matrix, const reskia_paint_t * paint) {
    if (canvas == nullptr || picture == 0) {
        return;
    }
    sk_sp<SkPicture> native_picture = static_sk_picture_get_entity(picture);
    if (!native_picture) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPicture(native_picture, reinterpret_cast<const SkMatrix *>(matrix), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPicturePtr(reskia_canvas_t *canvas, const reskia_picture_t * picture) {
    if (canvas == nullptr || picture == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPicture(reinterpret_cast<const SkPicture *>(picture));
}

void SkCanvas_drawPicturePtrWithMatrixPaint(reskia_canvas_t *canvas, const reskia_picture_t * picture, const reskia_matrix_t * matrix, const reskia_paint_t * paint) {
    if (canvas == nullptr || picture == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPicture(reinterpret_cast<const SkPicture *>(picture), reinterpret_cast<const SkMatrix *>(matrix), reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPoint(reskia_canvas_t *canvas, sk_point_t p, const reskia_paint_t * paint) {
    if (canvas == nullptr || !has_point_handle(p) || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPoint(static_sk_point_get_entity(p), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPointXY(reskia_canvas_t *canvas, float x, float y, const reskia_paint_t * paint) {
    if (canvas == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPoint(x, y, * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPoints(reskia_canvas_t *canvas, reskia_canvas_point_mode_t mode, size_t count, const reskia_point_t * pts, const reskia_paint_t * paint) {
    if (canvas == nullptr || paint == nullptr || (count > 0 && pts == nullptr)) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawPoints(static_cast<SkCanvas::PointMode>(mode), count, reinterpret_cast<const SkPoint *>(pts), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRect(reskia_canvas_t *canvas, sk_rect_t rect, const reskia_paint_t * paint) {
    if (canvas == nullptr || !has_rect_handle(rect) || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawRect(static_sk_rect_get_entity(rect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRegion(reskia_canvas_t *canvas, const reskia_region_t * region, const reskia_paint_t * paint) {
    if (canvas == nullptr || region == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawRegion(* reinterpret_cast<const SkRegion *>(region), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRoundRect(reskia_canvas_t *canvas, const reskia_rect_t * rect, float rx, float ry, const reskia_paint_t * paint) {
    if (canvas == nullptr || rect == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawRoundRect(* reinterpret_cast<const SkRect *>(rect), rx, ry, * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRRect(reskia_canvas_t *canvas, const reskia_r_rect_t * rrect, const reskia_paint_t * paint) {
    if (canvas == nullptr || rrect == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawRRect(* reinterpret_cast<const SkRRect *>(rrect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawSimpleText(reskia_canvas_t *canvas, const void * text, size_t byteLength, reskia_canvas_text_encoding_t encoding, float x, float y, const reskia_font_t * font, const reskia_paint_t * paint) {
    if (canvas == nullptr || byteLength == 0) {
        return;
    }
    if (text == nullptr || font == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawSimpleText(text, byteLength, static_cast<SkTextEncoding>(encoding), x, y, * reinterpret_cast<const SkFont *>(font), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawString(reskia_canvas_t *canvas, const char str[], float x, float y, const reskia_font_t * font, const reskia_paint_t * paint) {
    if (canvas == nullptr || str == nullptr || font == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawString(str, x, y, * reinterpret_cast<const SkFont *>(font), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawStringObject(reskia_canvas_t *canvas, const reskia_string_t * str, float x, float y, const reskia_font_t * font, const reskia_paint_t * paint) {
    if (canvas == nullptr || str == nullptr || font == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawString(* reinterpret_cast<const SkString *>(str), x, y, * reinterpret_cast<const SkFont *>(font), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawTextBlob(reskia_canvas_t *canvas, sk_text_blob_t text_blob, float x, float y, const reskia_paint_t * paint) {
    if (canvas == nullptr || !has_text_blob_handle(text_blob) || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawTextBlob(static_sk_text_blob_get_entity(text_blob), x, y, * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawTextBlobPtr(reskia_canvas_t *canvas, const reskia_text_blob_t * blob, float x, float y, const reskia_paint_t * paint) {
    if (canvas == nullptr || blob == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawTextBlob(reinterpret_cast<const SkTextBlob *>(blob), x, y, * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawVertices(reskia_canvas_t *canvas, sk_vertices_t vertices, reskia_blend_mode_t mode, const reskia_paint_t * paint) {
    if (canvas == nullptr || !has_vertices_handle(vertices) || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawVertices(static_sk_vertices_get_entity(vertices), static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_drawVerticesPtr(reskia_canvas_t *canvas, const reskia_vertices_t * vertices, reskia_blend_mode_t mode, const reskia_paint_t * paint) {
    if (canvas == nullptr || vertices == nullptr || paint == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->drawVertices(reinterpret_cast<const SkVertices *>(vertices), static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkPaint *>(paint));
}

void SkCanvas_experimental_DrawEdgeAAImageSet(reskia_canvas_t *canvas, const reskia_image_set_entry_t * imageSet, int cnt, const reskia_point_t * dstClips, const reskia_matrix_t * preViewMatrices, const reskia_sampling_options_t * sampling, const reskia_paint_t * paint, reskia_canvas_src_rect_constraint_t constraint) {
    if (canvas == nullptr || cnt <= 0) {
        return;
    }
    if (imageSet == nullptr || sampling == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAImageSet(reinterpret_cast<const SkCanvas::ImageSetEntry *>(imageSet), cnt, reinterpret_cast<const SkPoint *>(dstClips), reinterpret_cast<const SkMatrix *>(preViewMatrices), * reinterpret_cast<const SkSamplingOptions *>(sampling), reinterpret_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_experimental_DrawEdgeAAQuad(reskia_canvas_t *canvas, const reskia_rect_t * rect, const reskia_point_t * clip, reskia_canvas_quad_aa_flags_t aaFlags, const reskia_color_4f_t * color, reskia_blend_mode_t mode) {
    if (canvas == nullptr || rect == nullptr || color == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAQuad(* reinterpret_cast<const SkRect *>(rect), reinterpret_cast<const SkPoint *>(clip), static_cast<SkCanvas::QuadAAFlags>(aaFlags), * reinterpret_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkCanvas_experimental_DrawEdgeAAQuadU32Color(reskia_canvas_t *canvas, const reskia_rect_t * rect, const reskia_point_t * clip, reskia_canvas_quad_aa_flags_t aaFlags, uint32_t color, reskia_blend_mode_t mode) {
    if (canvas == nullptr || rect == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAQuad(* reinterpret_cast<const SkRect *>(rect), reinterpret_cast<const SkPoint *>(clip), static_cast<SkCanvas::QuadAAFlags>(aaFlags), color, static_cast<SkBlendMode>(mode));
}

sk_i_size_t SkCanvas_getBaseLayerSize(reskia_canvas_t *canvas) { // virtual
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_i_size_make(reinterpret_cast<SkCanvas *>(canvas)->getBaseLayerSize());
}

sk_surface_props_t SkCanvas_getBaseProps(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_surface_props_make(reinterpret_cast<SkCanvas *>(canvas)->getBaseProps());
}

sk_i_rect_t SkCanvas_getDeviceClipBounds(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_i_rect_make(reinterpret_cast<SkCanvas *>(canvas)->getDeviceClipBounds());
}

bool SkCanvas_getDeviceClipBoundsInto(reskia_canvas_t *canvas, reskia_i_rect_t * bounds) {
    if (canvas == nullptr || bounds == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->getDeviceClipBounds(reinterpret_cast<SkIRect *>(bounds));
}

sk_rect_t SkCanvas_getLocalClipBounds(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_rect_make(reinterpret_cast<SkCanvas *>(canvas)->getLocalClipBounds());
}

bool SkCanvas_getLocalClipBoundsInto(reskia_canvas_t *canvas, reskia_rect_t * bounds) {
    if (canvas == nullptr || bounds == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->getLocalClipBounds(reinterpret_cast<SkRect *>(bounds));
}

sk_m_44_t SkCanvas_getLocalToDevice(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_m_44_make(reinterpret_cast<SkCanvas *>(canvas)->getLocalToDevice());
}

sk_matrix_t SkCanvas_getLocalToDeviceAs3x3(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkCanvas *>(canvas)->getLocalToDeviceAs3x3());
}

bool SkCanvas_getProps(reskia_canvas_t *canvas, reskia_surface_props_t * props) {
    if (canvas == nullptr || props == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->getProps(reinterpret_cast<SkSurfaceProps *>(props));
}

int SkCanvas_getSaveCount(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->getSaveCount();
}

reskia_surface_t *SkCanvas_getSurface(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_surface_t *>(reinterpret_cast<SkCanvas *>(canvas)->getSurface());
}

sk_surface_props_t SkCanvas_getTopProps(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_surface_props_make(reinterpret_cast<SkCanvas *>(canvas)->getTopProps());
}

sk_matrix_t SkCanvas_getTotalMatrix(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_matrix_make(reinterpret_cast<SkCanvas *>(canvas)->getTotalMatrix());
}

sk_image_info_t SkCanvas_imageInfo(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_image_info_make(reinterpret_cast<SkCanvas *>(canvas)->imageInfo());
}

bool SkCanvas_isClipEmpty(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return true;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->isClipEmpty();
}

bool SkCanvas_isClipRect(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->isClipRect();
}

sk_surface_t SkCanvas_makeSurface(reskia_canvas_t *canvas, const reskia_image_info_t * info, const reskia_surface_props_t * props) {
    if (canvas == nullptr || info == nullptr) {
        return 0;
    }
    sk_sp<SkSurface> surface = reinterpret_cast<SkCanvas *>(canvas)->makeSurface(* reinterpret_cast<const SkImageInfo *>(info), reinterpret_cast<const SkSurfaceProps *>(props));
    return surface ? static_sk_surface_make(std::move(surface)) : 0;
}

bool SkCanvas_peekPixels(reskia_canvas_t *canvas, reskia_pixmap_t * pixmap) {
    if (canvas == nullptr || pixmap == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->peekPixels(reinterpret_cast<SkPixmap *>(pixmap));
}

void SkCanvas_private_draw_shadow_rec(reskia_canvas_t *canvas, const reskia_path_t * path, const reskia_draw_shadow_rec_t * rec) {
    if (canvas == nullptr || path == nullptr || rec == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->private_draw_shadow_rec(* reinterpret_cast<const SkPath *>(path), * reinterpret_cast<const SkDrawShadowRec *>(rec));
}

bool SkCanvas_quickReject(reskia_canvas_t *canvas, const reskia_path_t * path) {
    if (canvas == nullptr || path == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->quickReject(* reinterpret_cast<const SkPath *>(path));
}

bool SkCanvas_quickRejectRect(reskia_canvas_t *canvas, const reskia_rect_t * rect) {
    if (canvas == nullptr || rect == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->quickReject(* reinterpret_cast<const SkRect *>(rect));
}

bool SkCanvas_readPixels(reskia_canvas_t *canvas, const reskia_bitmap_t * bitmap, int srcX, int srcY) {
    if (canvas == nullptr || bitmap == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->readPixels(* reinterpret_cast<const SkBitmap *>(bitmap), srcX, srcY);
}

bool SkCanvas_readPixelsWithImageInfo(reskia_canvas_t *canvas, const reskia_image_info_t * dstInfo, void * dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    if (canvas == nullptr || !has_valid_pixels(dstInfo, dstPixels, dstRowBytes)) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->readPixels(* reinterpret_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkCanvas_readPixelsWithPixmap(reskia_canvas_t *canvas, const reskia_pixmap_t * pixmap, int srcX, int srcY) {
    if (canvas == nullptr || pixmap == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->readPixels(* reinterpret_cast<const SkPixmap *>(pixmap), srcX, srcY);
}

reskia_graphite_recorder_t *SkCanvas_recorder(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_graphite_recorder_t *>(reinterpret_cast<SkCanvas *>(canvas)->recorder());
}

reskia_recording_context_t *SkCanvas_recordingContext(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_recording_context_t *>(reinterpret_cast<SkCanvas *>(canvas)->recordingContext());
}

void SkCanvas_resetMatrix(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->resetMatrix();
}

void SkCanvas_restore(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->restore();
}

void SkCanvas_restoreToCount(reskia_canvas_t *canvas, int saveCount) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->restoreToCount(saveCount);
}

void SkCanvas_rotate(reskia_canvas_t *canvas, float degrees) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->rotate(degrees);
}

void SkCanvas_rotateAround(reskia_canvas_t *canvas, float degrees, float px, float py) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->rotate(degrees, px, py);
}

int SkCanvas_save(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->save();
}

int SkCanvas_saveLayer(reskia_canvas_t *canvas, const reskia_canvas_save_layer_rec_t * layerRec) {
    if (canvas == nullptr || layerRec == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayer(* reinterpret_cast<const SkCanvas::SaveLayerRec *>(layerRec));
}

int SkCanvas_saveLayerWithBoundsPaintRef(reskia_canvas_t *canvas, const reskia_rect_t * bounds, const reskia_paint_t * paint) {
    if (canvas == nullptr || bounds == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayer(* reinterpret_cast<const SkRect *>(bounds), reinterpret_cast<const SkPaint *>(paint));
}

int SkCanvas_saveLayerWithBoundsPaintPtr(reskia_canvas_t *canvas, const reskia_rect_t * bounds, const reskia_paint_t * paint) {
    if (canvas == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayer(reinterpret_cast<const SkRect *>(bounds), reinterpret_cast<const SkPaint *>(paint));
}

int SkCanvas_saveLayerAlpha(reskia_canvas_t *canvas, const reskia_rect_t * bounds, uint32_t alpha) {
    if (canvas == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayerAlpha(reinterpret_cast<const SkRect *>(bounds), alpha);
}

int SkCanvas_saveLayerAlphaf(reskia_canvas_t *canvas, const reskia_rect_t * bounds, float alpha) {
    if (canvas == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayerAlphaf(reinterpret_cast<const SkRect *>(bounds), alpha);
}

void SkCanvas_scale(reskia_canvas_t *canvas, float sx, float sy) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->scale(sx, sy);
}

void SkCanvas_setMatrix(reskia_canvas_t *canvas, const reskia_m_44_t * matrix) {
    if (canvas == nullptr || matrix == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->setMatrix(* reinterpret_cast<const SkM44 *>(matrix));
}

void SkCanvas_setMatrix3x3(reskia_canvas_t *canvas, const reskia_matrix_t * matrix) {
    if (canvas == nullptr || matrix == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->setMatrix(* reinterpret_cast<const SkMatrix *>(matrix));
}

void SkCanvas_skew(reskia_canvas_t *canvas, float sx, float sy) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->skew(sx, sy);
}

void SkCanvas_temporary_internal_getRgnClip(reskia_canvas_t *canvas, reskia_region_t * region) {
    if (canvas == nullptr || region == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->temporary_internal_getRgnClip(reinterpret_cast<SkRegion *>(region));
}

void SkCanvas_translate(reskia_canvas_t *canvas, float dx, float dy) {
    if (canvas == nullptr) {
        return;
    }
    reinterpret_cast<SkCanvas *>(canvas)->translate(dx, dy);
}

bool SkCanvas_writePixels(reskia_canvas_t *canvas, const reskia_bitmap_t * bitmap, int x, int y) {
    if (canvas == nullptr || bitmap == nullptr) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->writePixels(* reinterpret_cast<const SkBitmap *>(bitmap), x, y);
}

bool
SkCanvas_writePixelsWithImageInfo(reskia_canvas_t *canvas, const reskia_image_info_t * info, const void * pixels, size_t rowBytes, int x, int y) {
    if (canvas == nullptr || !has_valid_pixels(info, pixels, rowBytes)) {
        return false;
    }
    return reinterpret_cast<SkCanvas *>(canvas)->writePixels(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes, x, y);
}

// static

sk_canvas_t SkCanvas_MakeRasterDirect(const reskia_image_info_t * info, void *pixels, size_t rowBytes, const reskia_surface_props_t * props) {
    if (info == nullptr || pixels == nullptr) {
        return 0;
    }
    return make_canvas_handle(SkCanvas::MakeRasterDirect(* reinterpret_cast<const SkImageInfo *>(info), pixels, rowBytes, reinterpret_cast<const SkSurfaceProps *>(props)));
}

sk_canvas_t SkCanvas_MakeRasterDirectN32(int width, int height, void * pixels, size_t rowBytes) {
    if (width < 0 || height < 0 || pixels == nullptr) {
        return 0;
    }
    return make_canvas_handle(SkCanvas::MakeRasterDirectN32(width, height, static_cast<SkPMColor *>(pixels), rowBytes));
}

}
