//
// Created by dolphilia on 2024/01/06.
//

#include "sk_canvas.h"

#include "include/core/SkCanvas.h"

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

extern "C" {

reskia_canvas_t *SkCanvas_new(void) {
    return reinterpret_cast<reskia_canvas_t *>(new SkCanvas());
}

reskia_canvas_t *SkCanvas_new_2(int width, int height, const void * props) {
    return reinterpret_cast<reskia_canvas_t *>(new SkCanvas(width, height, static_cast<const SkSurfaceProps *>(props)));
}

reskia_canvas_t *SkCanvas_new_3(void * bitmap) {
    return reinterpret_cast<reskia_canvas_t *>(new SkCanvas(* static_cast<SkBitmap *>(bitmap)));
}

reskia_canvas_t *SkCanvas_new_4(const void * bitmap, const void * props) {
    return reinterpret_cast<reskia_canvas_t *>(new SkCanvas(* static_cast<const SkBitmap *>(bitmap), * static_cast<const SkSurfaceProps *>(props)));
}

void SkCanvas_delete(reskia_canvas_t *canvas) {
    delete reinterpret_cast<SkCanvas *>(canvas);
}

void * SkCanvas_accessTopLayerPixels(reskia_canvas_t *canvas, void * info, void * rowBytes, void * origin) {
    return reinterpret_cast<SkCanvas *>(canvas)->accessTopLayerPixels(static_cast<SkImageInfo *>(info), static_cast<size_t *>(rowBytes), static_cast<SkIPoint *>(origin));
}

void * SkCanvas_accessTopRasterHandle(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas)->accessTopRasterHandle();
}

void SkCanvas_androidFramework_setDeviceClipRestriction(reskia_canvas_t *canvas, const void * rect) {
    reinterpret_cast<SkCanvas *>(canvas)->androidFramework_setDeviceClipRestriction(* static_cast<const SkIRect *>(rect));
}

void SkCanvas_clear(reskia_canvas_t *canvas, const void * color) {
    reinterpret_cast<SkCanvas *>(canvas)->clear(* static_cast<const SkColor4f *>(color));
}

void SkCanvas_clear_2(reskia_canvas_t *canvas, uint32_t color) {
    reinterpret_cast<SkCanvas *>(canvas)->clear(color);
}

void SkCanvas_clipIRect(reskia_canvas_t *canvas, const void * irect, reskia_canvas_clip_op_t op) {
    reinterpret_cast<SkCanvas *>(canvas)->clipIRect(* static_cast<const SkIRect *>(irect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipPath(reskia_canvas_t *canvas, const void *path, bool doAntiAlias) {
    reinterpret_cast<SkCanvas *>(canvas)->clipPath(* static_cast<const SkPath *>(path), doAntiAlias);
}

void SkCanvas_clipPath_2(reskia_canvas_t *canvas, const void *path, reskia_canvas_clip_op_t op) {
    reinterpret_cast<SkCanvas *>(canvas)->clipPath(* static_cast<const SkPath *>(path), static_cast<SkClipOp>(op));
}

void SkCanvas_clipPath_3(reskia_canvas_t *canvas, const void *path, reskia_canvas_clip_op_t op, bool doAntiAlias) {
    reinterpret_cast<SkCanvas *>(canvas)->clipPath(* static_cast<const SkPath *>(path), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipRect(reskia_canvas_t *canvas, const void * rect, bool doAntiAlias) {
    reinterpret_cast<SkCanvas *>(canvas)->clipRect(* static_cast<const SkRect *>(rect), doAntiAlias);
}

void SkCanvas_clipRect_2(reskia_canvas_t *canvas, const void * rect, reskia_canvas_clip_op_t op) {
    reinterpret_cast<SkCanvas *>(canvas)->clipRect(* static_cast<const SkRect *>(rect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRect_3(reskia_canvas_t *canvas, const void * rect, reskia_canvas_clip_op_t op, bool doAntiAlias) {
    reinterpret_cast<SkCanvas *>(canvas)->clipRect(* static_cast<const SkRect *>(rect), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipRegion(reskia_canvas_t *canvas, const void * deviceRgn, reskia_canvas_clip_op_t op) {
    reinterpret_cast<SkCanvas *>(canvas)->clipRegion(* static_cast<const SkRegion *>(deviceRgn), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRRect(reskia_canvas_t *canvas, const void * rrect, bool doAntiAlias) {
    reinterpret_cast<SkCanvas *>(canvas)->clipRRect(* static_cast<const SkRRect *>(rrect), doAntiAlias);
}

void SkCanvas_clipRRect_2(reskia_canvas_t *canvas, const void *rrect, reskia_canvas_clip_op_t op) {
    reinterpret_cast<SkCanvas *>(canvas)->clipRRect(* static_cast<const SkRRect *>(rrect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRRect_3(reskia_canvas_t *canvas, const void *rrect, reskia_canvas_clip_op_t op, bool doAntiAlias) {
    reinterpret_cast<SkCanvas *>(canvas)->clipRRect(* static_cast<const SkRRect *>(rrect), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipShader(reskia_canvas_t *canvas, sk_shader_t shader, reskia_canvas_clip_op_t op) {
    reinterpret_cast<SkCanvas *>(canvas)->clipShader(static_sk_shader_get_entity(shader), static_cast<SkClipOp>(op));
}

void SkCanvas_concat(reskia_canvas_t *canvas, const void * m44) {
    reinterpret_cast<SkCanvas *>(canvas)->concat(* static_cast<const SkM44 *>(m44));
}

void SkCanvas_concat_2(reskia_canvas_t *canvas, const void * matrix) {
    reinterpret_cast<SkCanvas *>(canvas)->concat(* static_cast<const SkMatrix *>(matrix));
}

// virtual void SkCanvas_didConcat44(SkCanvas *canvas, const SkM44 *) {} // protected
// virtual void SkCanvas_didRestore(SkCanvas *canvas) {} // protected
// virtual void SkCanvas_didScale(SkCanvas *canvas, SkScalar SkScalar) {} // protected
// virtual void SkCanvas_didTranslate(SkCanvas *canvas, SkScalar SkScalar) {} // protected

void SkCanvas_discard(reskia_canvas_t *canvas) {
    reinterpret_cast<SkCanvas *>(canvas)->discard();
}

void SkCanvas_drawAnnotation(reskia_canvas_t *canvas, const void * rect, const char * key, sk_data_t data) {
    reinterpret_cast<SkCanvas *>(canvas)->drawAnnotation(* static_cast<const SkRect *>(rect), key, static_sk_data_get_entity(data));
}

void SkCanvas_drawAnnotation_2(reskia_canvas_t *canvas, const void * rect, const char * key, void * value) {
    reinterpret_cast<SkCanvas *>(canvas)->drawAnnotation(* static_cast<const SkRect *>(rect), key, static_cast<SkData *>(value));
}

void SkCanvas_drawArc(reskia_canvas_t *canvas, const void * oval, float startAngle, float sweepAngle, bool useCenter, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawArc(* static_cast<const SkRect *>(oval), startAngle, sweepAngle, useCenter, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawAtlas(reskia_canvas_t *canvas, const void * atlas, const void * xform, const void * tex, const void * colors, int count, reskia_blend_mode_t mode, const void * sampling, const void * cullRect, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawAtlas(static_cast<const SkImage *>(atlas), static_cast<const SkRSXform *>(xform), static_cast<const SkRect *>(tex), static_cast<const SkColor *>(colors), count, static_cast<SkBlendMode>(mode), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkRect *>(cullRect), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawCircle(reskia_canvas_t *canvas, sk_point_t center, float radius, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawCircle(static_sk_point_get_entity(center), radius, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawCircle_2(reskia_canvas_t *canvas, float cx, float cy, float radius, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawCircle(cx, cy, radius, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawColor(reskia_canvas_t *canvas, const void * color, reskia_blend_mode_t mode) {
    reinterpret_cast<SkCanvas *>(canvas)->drawColor(* static_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkCanvas_drawColor_2(reskia_canvas_t *canvas, uint32_t color, reskia_blend_mode_t mode) {
    reinterpret_cast<SkCanvas *>(canvas)->drawColor(color, static_cast<SkBlendMode>(mode));
}

void SkCanvas_drawDrawable(reskia_canvas_t *canvas, void *drawable, const void *matrix) {
    reinterpret_cast<SkCanvas *>(canvas)->drawDrawable(static_cast<SkDrawable *>(drawable), static_cast<const SkMatrix *>(matrix));
}

void SkCanvas_drawDrawable_2(reskia_canvas_t *canvas, void *drawable, float x, float y) {
    reinterpret_cast<SkCanvas *>(canvas)->drawDrawable(static_cast<SkDrawable *>(drawable), x, y);
}

void SkCanvas_drawDRRect(reskia_canvas_t *canvas, const void *outer, const void *inner, const void *paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawDRRect(* static_cast<const SkRRect *>(outer), * static_cast<const SkRRect *>(inner), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphs(reskia_canvas_t *canvas, int count, const void * glyphs, const void * positions, const void * clusters, int textByteCount, const char * utf8text, sk_point_t origin, const void * font, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawGlyphs(count, static_cast<const SkGlyphID *>(glyphs), static_cast<const SkPoint *>(positions), static_cast<const uint32_t *>(clusters), textByteCount, utf8text, static_sk_point_get_entity(origin), * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphs_2(reskia_canvas_t *canvas, int count, const void * glyphs, const void * positions, sk_point_t origin, const void * font, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawGlyphs(count, static_cast<const SkGlyphID *>(glyphs), static_cast<const SkPoint *>(positions), static_sk_point_get_entity(origin), * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphs_3(reskia_canvas_t *canvas, int count, const void * glyphs, const void * xforms, sk_point_t origin, const void * font, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawGlyphs(count, static_cast<const SkGlyphID *>(glyphs), static_cast<const SkRSXform *>(xforms), static_sk_point_get_entity(origin), * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImage(reskia_canvas_t *canvas, sk_image_t image, float left, float top) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_get_entity(image), left, top);
}

void SkCanvas_drawImage_2(reskia_canvas_t *canvas, sk_image_t image, float x, float y, const void * sampling, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_get_entity(image), x, y, * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImage_3(reskia_canvas_t *canvas, const void * image, float x, float y, const void * sampling, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_cast<const SkImage *>(image), x, y, * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImage_4(reskia_canvas_t *canvas, const void * image, float left, float top) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImage(static_cast<const SkImage *>(image), left, top);
}

void SkCanvas_drawImageLattice(reskia_canvas_t *canvas, const void * image, const void * lattice, const void * dst) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImageLattice(static_cast<const SkImage *>(image), * static_cast<const SkCanvas::Lattice *>(lattice), * static_cast<const SkRect *>(dst));
}

void SkCanvas_drawImageLattice_2(reskia_canvas_t *canvas, const void * image, const void * lattice, const void * dst, reskia_canvas_filter_mode_t filter, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImageLattice(static_cast<const SkImage *>(image), * static_cast<const SkCanvas::Lattice *>(lattice), * static_cast<const SkRect *>(dst), static_cast<SkFilterMode>(filter), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageNine(reskia_canvas_t *canvas, const void * image, const void * center, const void * dst, reskia_canvas_filter_mode_t filter, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImageNine(static_cast<const SkImage *>(image), * static_cast<const SkIRect *>(center), * static_cast<const SkRect *>(dst), static_cast<SkFilterMode>(filter), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRect(reskia_canvas_t *canvas, sk_image_t image, const void * dst, const void * sampling, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImageRect(static_sk_image_get_entity(image), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRect_2(reskia_canvas_t *canvas, sk_image_t image, const void * src, const void * dst, const void * sampling, const void * paint, reskia_canvas_src_rect_constraint_t constraint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImageRect(static_sk_image_get_entity(image), * static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_drawImageRect_3(reskia_canvas_t *canvas, const void * image, const void * dst, const void * sampling, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImageRect(static_cast<const SkImage *>(image), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRect_4(reskia_canvas_t *canvas, const void * image, const void * src, const void * dst, const void * sampling, const void * paint, reskia_canvas_src_rect_constraint_t constraint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawImageRect(static_cast<const SkImage *>(image), * static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_drawIRect(reskia_canvas_t *canvas, const void * rect, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawIRect(* static_cast<const SkIRect *>(rect), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawLine(reskia_canvas_t *canvas, sk_point_t p0, sk_point_t p1, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawLine(static_sk_point_get_entity(p0), static_sk_point_get_entity(p1), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawLine_2(reskia_canvas_t *canvas, float x0, float y0, float x1, float y1, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawLine(x0, y0, x1, y1, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawMesh(reskia_canvas_t *canvas, const void * mesh, sk_blender_t blender, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawMesh(* static_cast<const SkMesh *>(mesh), static_sk_blender_get_entity(blender), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawOval(reskia_canvas_t *canvas, const void * oval, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawOval(* static_cast<const SkRect *>(oval), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPaint(reskia_canvas_t *canvas, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPaint(* static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPatch(reskia_canvas_t *canvas, const void * cubics, const uint32_t colors[4], const void * texCoords, reskia_blend_mode_t mode, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPatch(static_cast<const SkPoint *>(cubics), colors, static_cast<const SkPoint *>(texCoords), static_cast<SkBlendMode>(mode), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPath(reskia_canvas_t *canvas, const void * path, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPath(* static_cast<const SkPath *>(path), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPicture(reskia_canvas_t *canvas, sk_picture_t picture) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPicture(static_sk_picture_get_entity(picture));
}

void SkCanvas_drawPicture_2(reskia_canvas_t *canvas, sk_picture_t picture, const void * matrix, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPicture(static_sk_picture_get_entity(picture), static_cast<const SkMatrix *>(matrix), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPicture_3(reskia_canvas_t *canvas, const void * picture) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPicture(static_cast<const SkPicture *>(picture));
}

void SkCanvas_drawPicture_4(reskia_canvas_t *canvas, const void * picture, const void * matrix, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPicture(static_cast<const SkPicture *>(picture), static_cast<const SkMatrix *>(matrix), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPoint(reskia_canvas_t *canvas, sk_point_t p, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPoint(static_sk_point_get_entity(p), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPoint_2(reskia_canvas_t *canvas, float x, float y, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPoint(x, y, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPoints(reskia_canvas_t *canvas, reskia_canvas_point_mode_t mode, size_t count, const void * pts, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawPoints(static_cast<SkCanvas::PointMode>(mode), count, static_cast<const SkPoint *>(pts), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRect(reskia_canvas_t *canvas, sk_rect_t rect, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawRect(static_sk_rect_get_entity(rect), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRegion(reskia_canvas_t *canvas, const void * region, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawRegion(* static_cast<const SkRegion *>(region), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRoundRect(reskia_canvas_t *canvas, const void * rect, float rx, float ry, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawRoundRect(* static_cast<const SkRect *>(rect), rx, ry, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRRect(reskia_canvas_t *canvas, const void * rrect, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawRRect(* static_cast<const SkRRect *>(rrect), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawSimpleText(reskia_canvas_t *canvas, const void * text, size_t byteLength, reskia_canvas_text_encoding_t encoding, float x, float y, const void * font, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawSimpleText(text, byteLength, static_cast<SkTextEncoding>(encoding), x, y, * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawString(reskia_canvas_t *canvas, const char str[], float x, float y, const void * font, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawString(str, x, y, * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawString_2(reskia_canvas_t *canvas, const void * str, float x, float y, const void * font, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawString(* static_cast<const SkString *>(str), x, y, * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawTextBlob(reskia_canvas_t *canvas, sk_text_blob_t text_blob, float x, float y, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawTextBlob(static_sk_text_blob_get_entity(text_blob), x, y, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawTextBlob_2(reskia_canvas_t *canvas, const void * blob, float x, float y, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawTextBlob(static_cast<const SkTextBlob *>(blob), x, y, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawVertices(reskia_canvas_t *canvas, sk_vertices_t vertices, reskia_blend_mode_t mode, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawVertices(static_sk_vertices_get_entity(vertices), static_cast<SkBlendMode>(mode), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawVertices_2(reskia_canvas_t *canvas, const void * vertices, reskia_blend_mode_t mode, const void * paint) {
    reinterpret_cast<SkCanvas *>(canvas)->drawVertices(static_cast<const SkVertices *>(vertices), static_cast<SkBlendMode>(mode), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_experimental_DrawEdgeAAImageSet(reskia_canvas_t *canvas, const void * imageSet, int cnt, const void * dstClips, const void * preViewMatrices, const void * sampling, const void * paint, reskia_canvas_src_rect_constraint_t constraint) {
    reinterpret_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAImageSet(static_cast<const SkCanvas::ImageSetEntry *>(imageSet), cnt, static_cast<const SkPoint *>(dstClips), static_cast<const SkMatrix *>(preViewMatrices), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_experimental_DrawEdgeAAQuad(reskia_canvas_t *canvas, const void * rect, const void * clip, reskia_canvas_quad_aa_flags_t aaFlags, const void * color, reskia_blend_mode_t mode) {
    reinterpret_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAQuad(* static_cast<const SkRect *>(rect), static_cast<const SkPoint *>(clip), static_cast<SkCanvas::QuadAAFlags>(aaFlags), * static_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkCanvas_experimental_DrawEdgeAAQuad_2(reskia_canvas_t *canvas, const void * rect, const void * clip, reskia_canvas_quad_aa_flags_t aaFlags, uint32_t color, reskia_blend_mode_t mode) {
    reinterpret_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAQuad(* static_cast<const SkRect *>(rect), static_cast<const SkPoint *>(clip), static_cast<SkCanvas::QuadAAFlags>(aaFlags), color, static_cast<SkBlendMode>(mode));
}

sk_i_size_t SkCanvas_getBaseLayerSize(reskia_canvas_t *canvas) { // virtual
    return static_sk_i_size_make(reinterpret_cast<SkCanvas *>(canvas)->getBaseLayerSize());
}

sk_surface_props_t SkCanvas_getBaseProps(reskia_canvas_t *canvas) {
    return static_sk_surface_props_make(reinterpret_cast<SkCanvas *>(canvas)->getBaseProps());
}

sk_i_rect_t SkCanvas_getDeviceClipBounds(reskia_canvas_t *canvas) {
    return static_sk_i_rect_make(reinterpret_cast<SkCanvas *>(canvas)->getDeviceClipBounds());
}

bool SkCanvas_getDeviceClipBounds_2(reskia_canvas_t *canvas, void * bounds) {
    return reinterpret_cast<SkCanvas *>(canvas)->getDeviceClipBounds(static_cast<SkIRect *>(bounds));
}

sk_rect_t SkCanvas_getLocalClipBounds(reskia_canvas_t *canvas) {
    return static_sk_rect_make(reinterpret_cast<SkCanvas *>(canvas)->getLocalClipBounds());
}

bool SkCanvas_getLocalClipBounds_2(reskia_canvas_t *canvas, void * bounds) {
    return reinterpret_cast<SkCanvas *>(canvas)->getLocalClipBounds(static_cast<SkRect *>(bounds));
}

sk_m_44_t SkCanvas_getLocalToDevice(reskia_canvas_t *canvas) {
    return static_sk_m_44_make(reinterpret_cast<SkCanvas *>(canvas)->getLocalToDevice());
}

sk_matrix_t SkCanvas_getLocalToDeviceAs3x3(reskia_canvas_t *canvas) {
    return static_sk_matrix_make(reinterpret_cast<SkCanvas *>(canvas)->getLocalToDeviceAs3x3());
}

bool SkCanvas_getProps(reskia_canvas_t *canvas, void * props) {
    return reinterpret_cast<SkCanvas *>(canvas)->getProps(static_cast<SkSurfaceProps *>(props));
}

int SkCanvas_getSaveCount(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas)->getSaveCount();
}

void * SkCanvas_getSurface(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas)->getSurface();
}

sk_surface_props_t SkCanvas_getTopProps(reskia_canvas_t *canvas) {
    return static_sk_surface_props_make(reinterpret_cast<SkCanvas *>(canvas)->getTopProps());
}

sk_matrix_t SkCanvas_getTotalMatrix(reskia_canvas_t *canvas) {
    return static_sk_matrix_make(reinterpret_cast<SkCanvas *>(canvas)->getTotalMatrix());
}

sk_image_info_t SkCanvas_imageInfo(reskia_canvas_t *canvas) {
    return static_sk_image_info_make(reinterpret_cast<SkCanvas *>(canvas)->imageInfo());
}

bool SkCanvas_isClipEmpty(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas)->isClipEmpty();
}

bool SkCanvas_isClipRect(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas)->isClipRect();
}

sk_surface_t SkCanvas_makeSurface(reskia_canvas_t *canvas, const void * info, const void * props) {
    return static_sk_surface_make(reinterpret_cast<SkCanvas *>(canvas)->makeSurface(* static_cast<const SkImageInfo *>(info), static_cast<const SkSurfaceProps *>(props)));
}

bool SkCanvas_peekPixels(reskia_canvas_t *canvas, void * pixmap) {
    return reinterpret_cast<SkCanvas *>(canvas)->peekPixels(static_cast<SkPixmap *>(pixmap));
}

void SkCanvas_private_draw_shadow_rec(reskia_canvas_t *canvas, const void * path, const void * rec) {
    reinterpret_cast<SkCanvas *>(canvas)->private_draw_shadow_rec(* static_cast<const SkPath *>(path), * static_cast<const SkDrawShadowRec *>(rec));
}

bool SkCanvas_quickReject(reskia_canvas_t *canvas, const void * path) {
    return reinterpret_cast<SkCanvas *>(canvas)->quickReject(* static_cast<const SkPath *>(path));
}

bool SkCanvas_quickReject_2(reskia_canvas_t *canvas, const void * rect) {
    return reinterpret_cast<SkCanvas *>(canvas)->quickReject(* static_cast<const SkRect *>(rect));
}

bool SkCanvas_readPixels(reskia_canvas_t *canvas, const void * bitmap, int srcX, int srcY) {
    return reinterpret_cast<SkCanvas *>(canvas)->readPixels(* static_cast<const SkBitmap *>(bitmap), srcX, srcY);
}

bool SkCanvas_readPixels_2(reskia_canvas_t *canvas, const void * dstInfo, void * dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    return reinterpret_cast<SkCanvas *>(canvas)->readPixels(* static_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkCanvas_readPixels_3(reskia_canvas_t *canvas, const void * pixmap, int srcX, int srcY) {
    return reinterpret_cast<SkCanvas *>(canvas)->readPixels(* static_cast<const SkPixmap *>(pixmap), srcX, srcY);
}

void * SkCanvas_recorder(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas)->recorder();
}

void * SkCanvas_recordingContext(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas)->recordingContext();
}

void SkCanvas_resetMatrix(reskia_canvas_t *canvas) {
    reinterpret_cast<SkCanvas *>(canvas)->resetMatrix();
}

void SkCanvas_restore(reskia_canvas_t *canvas) {
    reinterpret_cast<SkCanvas *>(canvas)->restore();
}

void SkCanvas_restoreToCount(reskia_canvas_t *canvas, int saveCount) {
    reinterpret_cast<SkCanvas *>(canvas)->restoreToCount(saveCount);
}

void SkCanvas_rotate(reskia_canvas_t *canvas, float degrees) {
    reinterpret_cast<SkCanvas *>(canvas)->rotate(degrees);
}

void SkCanvas_rotate_2(reskia_canvas_t *canvas, float degrees, float px, float py) {
    reinterpret_cast<SkCanvas *>(canvas)->rotate(degrees, px, py);
}

int SkCanvas_save(reskia_canvas_t *canvas) {
    return reinterpret_cast<SkCanvas *>(canvas)->save();
}

int SkCanvas_saveLayer(reskia_canvas_t *canvas, const void * layerRec) {
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayer(* static_cast<const SkCanvas::SaveLayerRec *>(layerRec));
}

int SkCanvas_saveLayer_2(reskia_canvas_t *canvas, const void * bounds, const void * paint) {
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayer(* static_cast<const SkRect *>(bounds), static_cast<const SkPaint *>(paint));
}

int SkCanvas_saveLayer_3(reskia_canvas_t *canvas, const void * bounds, const void * paint) {
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayer(static_cast<const SkRect *>(bounds), static_cast<const SkPaint *>(paint));
}

int SkCanvas_saveLayerAlpha(reskia_canvas_t *canvas, const void * bounds, uint32_t alpha) {
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayerAlpha(static_cast<const SkRect *>(bounds), alpha);
}

int SkCanvas_saveLayerAlphaf(reskia_canvas_t *canvas, const void * bounds, float alpha) {
    return reinterpret_cast<SkCanvas *>(canvas)->saveLayerAlphaf(static_cast<const SkRect *>(bounds), alpha);
}

void SkCanvas_scale(reskia_canvas_t *canvas, float sx, float sy) {
    reinterpret_cast<SkCanvas *>(canvas)->scale(sx, sy);
}

void SkCanvas_setMatrix(reskia_canvas_t *canvas, const void * matrix) {
    reinterpret_cast<SkCanvas *>(canvas)->setMatrix(* static_cast<const SkM44 *>(matrix));
}

void SkCanvas_setMatrix_2(reskia_canvas_t *canvas, const void * matrix) {
    reinterpret_cast<SkCanvas *>(canvas)->setMatrix(* static_cast<const SkMatrix *>(matrix));
}

void SkCanvas_skew(reskia_canvas_t *canvas, float sx, float sy) {
    reinterpret_cast<SkCanvas *>(canvas)->skew(sx, sy);
}

void SkCanvas_temporary_internal_getRgnClip(reskia_canvas_t *canvas, void * region) {
    reinterpret_cast<SkCanvas *>(canvas)->temporary_internal_getRgnClip(static_cast<SkRegion *>(region));
}

void SkCanvas_translate(reskia_canvas_t *canvas, float dx, float dy) {
    reinterpret_cast<SkCanvas *>(canvas)->translate(dx, dy);
}

bool SkCanvas_writePixels(reskia_canvas_t *canvas, const void * bitmap, int x, int y) {
    return reinterpret_cast<SkCanvas *>(canvas)->writePixels(* static_cast<const SkBitmap *>(bitmap), x, y);
}

bool
SkCanvas_writePixels_2(reskia_canvas_t *canvas, const void * info, const void * pixels, size_t rowBytes, int x, int y) {
    return reinterpret_cast<SkCanvas *>(canvas)->writePixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes, x, y);
}

// static

sk_canvas_t SkCanvas_MakeRasterDirect(const void * info, void *pixels, size_t rowBytes, const void * props) {
    return static_sk_canvas_make(SkCanvas::MakeRasterDirect(* static_cast<const SkImageInfo *>(info), pixels, rowBytes, static_cast<const SkSurfaceProps *>(props)));
}

sk_canvas_t SkCanvas_MakeRasterDirectN32(int width, int height, void * pixels, size_t rowBytes) {
    return static_sk_canvas_make(SkCanvas::MakeRasterDirectN32(width, height, static_cast<SkPMColor *>(pixels), rowBytes));
}

}
