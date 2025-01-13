//
// Created by dolphilia on 2024/01/06.
//

#include "sk_canvas.h"

#include "include/core/SkCanvas.h"

#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_blender-internal.h"
#include "../static/static_sk_canvas-internal.h"
#include "../static/static_sk_surface-internal.h"
#include "../static/static_sk_vertices-internal.h"
#include "../static/static_sk_text_blob-internal.h"
#include "../static/static_sk_rect-internal.h"
#include "../static/static_sk_picture-internal.h"
#include "../static/static_sk_image-internal.h"
#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_surface_props-internal.h"
#include "../static/static_sk_i_rect-internal.h"
#include "../static/static_sk_m_44-internal.h"
#include "../static/static_sk_matrix-internal.h"
#include "../static/static_sk_image_info-internal.h"
#include "../static/static_sk_point-internal.h"
#include "../static/static_sk_i_size-internal.h"

extern "C" {

void * SkCanvas_new() {
    return new SkCanvas();
}

void * SkCanvas_new_2(int width, int height, const void * props) {
    return new SkCanvas(width, height, static_cast<const SkSurfaceProps *>(props));
}

void * SkCanvas_new_3(void * bitmap) {
    return new SkCanvas(* static_cast<SkBitmap *>(bitmap));
}

void * SkCanvas_new_4(const void * bitmap, const void * props) {
    return new SkCanvas(* static_cast<const SkBitmap *>(bitmap), * static_cast<const SkSurfaceProps *>(props));
}

void SkCanvas_delete(void * canvas) {
    delete static_cast<SkCanvas *>(canvas);
}

void * SkCanvas_accessTopLayerPixels(void * canvas, void * info, void * rowBytes, void * origin) {
    return static_cast<SkCanvas *>(canvas)->accessTopLayerPixels(static_cast<SkImageInfo *>(info), static_cast<size_t *>(rowBytes), static_cast<SkIPoint *>(origin));
}

void * SkCanvas_accessTopRasterHandle(void * canvas) {
    return static_cast<SkCanvas *>(canvas)->accessTopRasterHandle();
}

void SkCanvas_androidFramework_setDeviceClipRestriction(void * canvas, const void * rect) {
    static_cast<SkCanvas *>(canvas)->androidFramework_setDeviceClipRestriction(* static_cast<const SkIRect *>(rect));
}

void SkCanvas_clear(void * canvas, const void * color) {
    static_cast<SkCanvas *>(canvas)->clear(* static_cast<const SkColor4f *>(color));
}

void SkCanvas_clear_2(void * canvas, unsigned int color) {
    static_cast<SkCanvas *>(canvas)->clear(color);
}

void SkCanvas_clipIRect(void * canvas, const void * irect, int op) {
    static_cast<SkCanvas *>(canvas)->clipIRect(* static_cast<const SkIRect *>(irect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipPath(void * canvas, const void *path, bool doAntiAlias) {
    static_cast<SkCanvas *>(canvas)->clipPath(* static_cast<const SkPath *>(path), doAntiAlias);
}

void SkCanvas_clipPath_2(void * canvas, const void *path, int op) {
    static_cast<SkCanvas *>(canvas)->clipPath(* static_cast<const SkPath *>(path), static_cast<SkClipOp>(op));
}

void SkCanvas_clipPath_3(void * canvas, const void *path, int op, bool doAntiAlias) {
    static_cast<SkCanvas *>(canvas)->clipPath(* static_cast<const SkPath *>(path), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipRect(void * canvas, const void * rect, bool doAntiAlias) {
    static_cast<SkCanvas *>(canvas)->clipRect(* static_cast<const SkRect *>(rect), doAntiAlias);
}

void SkCanvas_clipRect_2(void * canvas, const void * rect, int op) {
    static_cast<SkCanvas *>(canvas)->clipRect(* static_cast<const SkRect *>(rect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRect_3(void * canvas, const void * rect, int op, bool doAntiAlias) {
    static_cast<SkCanvas *>(canvas)->clipRect(* static_cast<const SkRect *>(rect), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipRegion(void *canvas, const void * deviceRgn, int op) {
    static_cast<SkCanvas *>(canvas)->clipRegion(* static_cast<const SkRegion *>(deviceRgn), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRRect(void *canvas, const void * rrect, bool doAntiAlias) {
    static_cast<SkCanvas *>(canvas)->clipRRect(* static_cast<const SkRRect *>(rrect), doAntiAlias);
}

void SkCanvas_clipRRect_2(void *canvas, const void *rrect, int op) {
    static_cast<SkCanvas *>(canvas)->clipRRect(* static_cast<const SkRRect *>(rrect), static_cast<SkClipOp>(op));
}

void SkCanvas_clipRRect_3(void *canvas, const void *rrect, int op, bool doAntiAlias) {
    static_cast<SkCanvas *>(canvas)->clipRRect(* static_cast<const SkRRect *>(rrect), static_cast<SkClipOp>(op), doAntiAlias);
}

void SkCanvas_clipShader(void *canvas, sk_shader_t shader, int op) {
    static_cast<SkCanvas *>(canvas)->clipShader(static_sk_shader_move(shader), static_cast<SkClipOp>(op));
}

void SkCanvas_concat(void *canvas, const void * m44) {
    static_cast<SkCanvas *>(canvas)->concat(* static_cast<const SkM44 *>(m44));
}

void SkCanvas_concat_2(void *canvas, const void * matrix) {
    static_cast<SkCanvas *>(canvas)->concat(* static_cast<const SkMatrix *>(matrix));
}

// virtual void SkCanvas_didConcat44(SkCanvas *canvas, const SkM44 *) {} // protected
// virtual void SkCanvas_didRestore(SkCanvas *canvas) {} // protected
// virtual void SkCanvas_didScale(SkCanvas *canvas, SkScalar SkScalar) {} // protected
// virtual void SkCanvas_didTranslate(SkCanvas *canvas, SkScalar SkScalar) {} // protected

void SkCanvas_discard(void *canvas) {
    static_cast<SkCanvas *>(canvas)->discard();
}

void SkCanvas_drawAnnotation(void *canvas, const void * rect, const char * key, sk_data_t data) {
    static_cast<SkCanvas *>(canvas)->drawAnnotation(* static_cast<const SkRect *>(rect), key, static_sk_data_move(data));
}

void SkCanvas_drawAnnotation_2(void *canvas, const void * rect, const char * key, void * value) {
    static_cast<SkCanvas *>(canvas)->drawAnnotation(* static_cast<const SkRect *>(rect), key, static_cast<SkData *>(value));
}

void SkCanvas_drawArc(void *canvas, const void * oval, float startAngle, float sweepAngle, bool useCenter, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawArc(* static_cast<const SkRect *>(oval), startAngle, sweepAngle, useCenter, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawAtlas(void *canvas, const void * atlas, const void * xform, const void * tex, const void * colors, int count, int mode, const void * sampling, const void * cullRect, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawAtlas(static_cast<const SkImage *>(atlas), static_cast<const SkRSXform *>(xform), static_cast<const SkRect *>(tex), static_cast<const SkColor *>(colors), count, static_cast<SkBlendMode>(mode), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkRect *>(cullRect), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawCircle(void *canvas, sk_point_t center, float radius, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawCircle(static_sk_point_get(center), radius, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawCircle_2(void *canvas, float cx, float cy, float radius, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawCircle(cx, cy, radius, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawColor(void *canvas, const void * color, int mode) {
    static_cast<SkCanvas *>(canvas)->drawColor(* static_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkCanvas_drawColor_2(void *canvas, unsigned int color, int mode) {
    static_cast<SkCanvas *>(canvas)->drawColor(color, static_cast<SkBlendMode>(mode));
}

void SkCanvas_drawDrawable(void *canvas, void *drawable, const void *matrix) {
    static_cast<SkCanvas *>(canvas)->drawDrawable(static_cast<SkDrawable *>(drawable), static_cast<const SkMatrix *>(matrix));
}

void SkCanvas_drawDrawable_2(void *canvas, void *drawable, float x, float y) {
    static_cast<SkCanvas *>(canvas)->drawDrawable(static_cast<SkDrawable *>(drawable), x, y);
}

void SkCanvas_drawDRRect(void *canvas, const void *outer, const void *inner, const void *paint) {
    static_cast<SkCanvas *>(canvas)->drawDRRect(* static_cast<const SkRRect *>(outer), * static_cast<const SkRRect *>(inner), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphs(void *canvas, int count, const void * glyphs, const void * positions, const void * clusters, int textByteCount, const char * utf8text, sk_point_t origin, const void * font, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawGlyphs(count, static_cast<const SkGlyphID *>(glyphs), static_cast<const SkPoint *>(positions), static_cast<const uint32_t *>(clusters), textByteCount, utf8text, static_sk_point_get(origin), * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphs_2(void *canvas, int count, const void * glyphs, const void * positions, sk_point_t origin, const void * font, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawGlyphs(count, static_cast<const SkGlyphID *>(glyphs), static_cast<const SkPoint *>(positions), static_sk_point_get(origin), * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawGlyphs_3(void *canvas, int count, const void * glyphs, const void * xforms, sk_point_t origin, const void * font, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawGlyphs(count, static_cast<const SkGlyphID *>(glyphs), static_cast<const SkRSXform *>(xforms), static_sk_point_get(origin), * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImage(void *canvas, sk_image_t image, float left, float top) {
    static_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_move(image), left, top);
}

void SkCanvas_drawImage_2(void *canvas, sk_image_t image, float x, float y, const void * sampling, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawImage(static_sk_image_move(image), x, y, * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImage_3(void *canvas, const void * image, float x, float y, const void * sampling, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawImage(static_cast<const SkImage *>(image), x, y, * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImage_4(void *canvas, const void * image, float left, float top) {
    static_cast<SkCanvas *>(canvas)->drawImage(static_cast<const SkImage *>(image), left, top);
}

void SkCanvas_drawImageLattice(void *canvas, const void * image, const void * lattice, const void * dst) {
    static_cast<SkCanvas *>(canvas)->drawImageLattice(static_cast<const SkImage *>(image), * static_cast<const SkCanvas::Lattice *>(lattice), * static_cast<const SkRect *>(dst));
}

void SkCanvas_drawImageLattice_2(void *canvas, const void * image, const void * lattice, const void * dst, int filter, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawImageLattice(static_cast<const SkImage *>(image), * static_cast<const SkCanvas::Lattice *>(lattice), * static_cast<const SkRect *>(dst), static_cast<SkFilterMode>(filter), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageNine(void *canvas, const void * image, const void * center, const void * dst, int filter, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawImageNine(static_cast<const SkImage *>(image), * static_cast<const SkIRect *>(center), * static_cast<const SkRect *>(dst), static_cast<SkFilterMode>(filter), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRect(void *canvas, sk_image_t image, const void * dst, const void * sampling, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawImageRect(static_sk_image_move(image), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRect_2(void *canvas, sk_image_t image, const void * src, const void * dst, const void * sampling, const void * paint, int constraint) {
    static_cast<SkCanvas *>(canvas)->drawImageRect(static_sk_image_move(image), * static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_drawImageRect_3(void *canvas, const void * image, const void * dst, const void * sampling, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawImageRect(static_cast<const SkImage *>(image), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawImageRect_4(void *canvas, const void * image, const void * src, const void * dst, const void * sampling, const void * paint, int constraint) {
    static_cast<SkCanvas *>(canvas)->drawImageRect(static_cast<const SkImage *>(image), * static_cast<const SkRect *>(src), * static_cast<const SkRect *>(dst), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_drawIRect(void *canvas, const void * rect, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawIRect(* static_cast<const SkIRect *>(rect), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawLine(void *canvas, sk_point_t p0, sk_point_t p1, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawLine(static_sk_point_get(p0), static_sk_point_get(p1), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawLine_2(void *canvas, float x0, float y0, float x1, float y1, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawLine(x0, y0, x1, y1, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawMesh(void *canvas, const void * mesh, sk_blender_t blender, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawMesh(* static_cast<const SkMesh *>(mesh), static_sk_blender_move(blender), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawOval(void *canvas, const void * oval, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawOval(* static_cast<const SkRect *>(oval), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPaint(void *canvas, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawPaint(* static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPatch(void *canvas, const void * cubics, const unsigned int colors[4], const void * texCoords, int mode, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawPatch(static_cast<const SkPoint *>(cubics), colors, static_cast<const SkPoint *>(texCoords), static_cast<SkBlendMode>(mode), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPath(void *canvas, const void * path, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawPath(* static_cast<const SkPath *>(path), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPicture(void *canvas, sk_picture_t picture) {
    static_cast<SkCanvas *>(canvas)->drawPicture(static_sk_picture_move(picture));
}

void SkCanvas_drawPicture_2(void *canvas, sk_picture_t picture, const void * matrix, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawPicture(static_sk_picture_move(picture), static_cast<const SkMatrix *>(matrix), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPicture_3(void *canvas, const void * picture) {
    static_cast<SkCanvas *>(canvas)->drawPicture(static_cast<const SkPicture *>(picture));
}

void SkCanvas_drawPicture_4(void *canvas, const void * picture, const void * matrix, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawPicture(static_cast<const SkPicture *>(picture), static_cast<const SkMatrix *>(matrix), static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPoint(void *canvas, sk_point_t p, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawPoint(static_sk_point_get(p), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPoint_2(void *canvas, float x, float y, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawPoint(x, y, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawPoints(void *canvas, int mode, size_t count, const void * pts, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawPoints(static_cast<SkCanvas::PointMode>(mode), count, static_cast<const SkPoint *>(pts), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRect(void *canvas, sk_rect_t rect, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawRect(static_sk_rect_get(rect), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRegion(void *canvas, const void * region, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawRegion(* static_cast<const SkRegion *>(region), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRoundRect(void *canvas, const void * rect, float rx, float ry, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawRoundRect(* static_cast<const SkRect *>(rect), rx, ry, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawRRect(void *canvas, const void * rrect, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawRRect(* static_cast<const SkRRect *>(rrect), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawSimpleText(void *canvas, const void * text, size_t byteLength, int encoding, float x, float y, const void * font, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawSimpleText(text, byteLength, static_cast<SkTextEncoding>(encoding), x, y, * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawString(void *canvas, const char str[], float x, float y, const void * font, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawString(str, x, y, * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawString_2(void *canvas, const void * str, float x, float y, const void * font, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawString(* static_cast<const SkString *>(str), x, y, * static_cast<const SkFont *>(font), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawTextBlob(void *canvas, sk_text_blob_t text_blob, float x, float y, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawTextBlob(static_sk_text_blob_move(text_blob), x, y, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawTextBlob_2(void *canvas, const void * blob, float x, float y, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawTextBlob(static_cast<const SkTextBlob *>(blob), x, y, * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawVertices(void *canvas, sk_vertices_t vertices, int mode, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawVertices(static_sk_vertices_move(vertices), static_cast<SkBlendMode>(mode), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_drawVertices_2(void *canvas, const void * vertices, int mode, const void * paint) {
    static_cast<SkCanvas *>(canvas)->drawVertices(static_cast<const SkVertices *>(vertices), static_cast<SkBlendMode>(mode), * static_cast<const SkPaint *>(paint));
}

void SkCanvas_experimental_DrawEdgeAAImageSet(void *canvas, const void * imageSet, int cnt, const void * dstClips, const void * preViewMatrices, const void * sampling, const void * paint, int constraint) {
    static_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAImageSet(static_cast<const SkCanvas::ImageSetEntry *>(imageSet), cnt, static_cast<const SkPoint *>(dstClips), static_cast<const SkMatrix *>(preViewMatrices), * static_cast<const SkSamplingOptions *>(sampling), static_cast<const SkPaint *>(paint), static_cast<SkCanvas::SrcRectConstraint>(constraint));
}

void SkCanvas_experimental_DrawEdgeAAQuad(void *canvas, const void * rect, const void * clip, int aaFlags, const void * color, int mode) {
    static_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAQuad(* static_cast<const SkRect *>(rect), static_cast<const SkPoint *>(clip), static_cast<SkCanvas::QuadAAFlags>(aaFlags), * static_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkCanvas_experimental_DrawEdgeAAQuad_2(void *canvas, const void * rect, const void * clip, int aaFlags, unsigned int color, int mode) {
    static_cast<SkCanvas *>(canvas)->experimental_DrawEdgeAAQuad(* static_cast<const SkRect *>(rect), static_cast<const SkPoint *>(clip), static_cast<SkCanvas::QuadAAFlags>(aaFlags), color, static_cast<SkBlendMode>(mode));
}

sk_i_size_t SkCanvas_getBaseLayerSize(void *canvas) { // virtual
    return static_sk_i_size_make(static_cast<SkCanvas *>(canvas)->getBaseLayerSize());
}

sk_surface_props_t SkCanvas_getBaseProps(void *canvas) {
    return static_sk_surface_props_make(static_cast<SkCanvas *>(canvas)->getBaseProps());
}

sk_i_rect_t SkCanvas_getDeviceClipBounds(void *canvas) {
    return static_sk_i_rect_make(static_cast<SkCanvas *>(canvas)->getDeviceClipBounds());
}

bool SkCanvas_getDeviceClipBounds_2(void *canvas, void * bounds) {
    return static_cast<SkCanvas *>(canvas)->getDeviceClipBounds(static_cast<SkIRect *>(bounds));
}

sk_rect_t SkCanvas_getLocalClipBounds(void *canvas) {
    return static_sk_rect_make(static_cast<SkCanvas *>(canvas)->getLocalClipBounds());
}

bool SkCanvas_getLocalClipBounds_2(void *canvas, void * bounds) {
    return static_cast<SkCanvas *>(canvas)->getLocalClipBounds(static_cast<SkRect *>(bounds));
}

sk_m_44_t SkCanvas_getLocalToDevice(void *canvas) {
    return static_sk_m_44_make(static_cast<SkCanvas *>(canvas)->getLocalToDevice());
}

sk_matrix_t SkCanvas_getLocalToDeviceAs3x3(void *canvas) {
    return static_sk_matrix_make(static_cast<SkCanvas *>(canvas)->getLocalToDeviceAs3x3());
}

bool SkCanvas_getProps(void *canvas, void * props) {
    return static_cast<SkCanvas *>(canvas)->getProps(static_cast<SkSurfaceProps *>(props));
}

int SkCanvas_getSaveCount(void *canvas) {
    return static_cast<SkCanvas *>(canvas)->getSaveCount();
}

void * SkCanvas_getSurface(void *canvas) {
    return static_cast<SkCanvas *>(canvas)->getSurface();
}

sk_surface_props_t SkCanvas_getTopProps(void *canvas) {
    return static_sk_surface_props_make(static_cast<SkCanvas *>(canvas)->getTopProps());
}

sk_matrix_t SkCanvas_getTotalMatrix(void *canvas) {
    return static_sk_matrix_make(static_cast<SkCanvas *>(canvas)->getTotalMatrix());
}

sk_image_info_t SkCanvas_imageInfo(void *canvas) {
    return static_sk_image_info_make(static_cast<SkCanvas *>(canvas)->imageInfo());
}

bool SkCanvas_isClipEmpty(void *canvas) {
    return static_cast<SkCanvas *>(canvas)->isClipEmpty();
}

bool SkCanvas_isClipRect(void *canvas) {
    return static_cast<SkCanvas *>(canvas)->isClipRect();
}

sk_surface_t SkCanvas_makeSurface(void *canvas, const void * info, const void * props) {
    return static_sk_surface_make(static_cast<SkCanvas *>(canvas)->makeSurface(* static_cast<const SkImageInfo *>(info), static_cast<const SkSurfaceProps *>(props)));
}

bool SkCanvas_peekPixels(void *canvas, void * pixmap) {
    return static_cast<SkCanvas *>(canvas)->peekPixels(static_cast<SkPixmap *>(pixmap));
}

void SkCanvas_private_draw_shadow_rec(void *canvas, const void * path, const void * rec) {
    static_cast<SkCanvas *>(canvas)->private_draw_shadow_rec(* static_cast<const SkPath *>(path), * static_cast<const SkDrawShadowRec *>(rec));
}

bool SkCanvas_quickReject(void *canvas, const void * path) {
    return static_cast<SkCanvas *>(canvas)->quickReject(* static_cast<const SkPath *>(path));
}

bool SkCanvas_quickReject_2(void *canvas, const void * rect) {
    return static_cast<SkCanvas *>(canvas)->quickReject(* static_cast<const SkRect *>(rect));
}

bool SkCanvas_readPixels(void *canvas, const void * bitmap, int srcX, int srcY) {
    return static_cast<SkCanvas *>(canvas)->readPixels(* static_cast<const SkBitmap *>(bitmap), srcX, srcY);
}

bool SkCanvas_readPixels_2(void *canvas, const void * dstInfo, void * dstPixels, size_t dstRowBytes, int srcX, int srcY) {
    return static_cast<SkCanvas *>(canvas)->readPixels(* static_cast<const SkImageInfo *>(dstInfo), dstPixels, dstRowBytes, srcX, srcY);
}

bool SkCanvas_readPixels_3(void *canvas, const void * pixmap, int srcX, int srcY) {
    return static_cast<SkCanvas *>(canvas)->readPixels(* static_cast<const SkPixmap *>(pixmap), srcX, srcY);
}

void * SkCanvas_recorder(void *canvas) {
    return static_cast<SkCanvas *>(canvas)->recorder();
}

void * SkCanvas_recordingContext(void *canvas) {
    return static_cast<SkCanvas *>(canvas)->recordingContext();
}

void SkCanvas_resetMatrix(void *canvas) {
    static_cast<SkCanvas *>(canvas)->resetMatrix();
}

void SkCanvas_restore(void *canvas) {
    static_cast<SkCanvas *>(canvas)->restore();
}

void SkCanvas_restoreToCount(void *canvas, int saveCount) {
    static_cast<SkCanvas *>(canvas)->restoreToCount(saveCount);
}

void SkCanvas_rotate(void *canvas, float degrees) {
    static_cast<SkCanvas *>(canvas)->rotate(degrees);
}

void SkCanvas_rotate_2(void *canvas, float degrees, float px, float py) {
    static_cast<SkCanvas *>(canvas)->rotate(degrees, px, py);
}

int SkCanvas_save(void *canvas) {
    return static_cast<SkCanvas *>(canvas)->save();
}

int SkCanvas_saveLayer(void *canvas, const void * layerRec) {
    return static_cast<SkCanvas *>(canvas)->saveLayer(* static_cast<const SkCanvas::SaveLayerRec *>(layerRec));
}

int SkCanvas_saveLayer_2(void *canvas, const void * bounds, const void * paint) {
    return static_cast<SkCanvas *>(canvas)->saveLayer(* static_cast<const SkRect *>(bounds), static_cast<const SkPaint *>(paint));
}

int SkCanvas_saveLayer_3(void *canvas, const void * bounds, const void * paint) {
    return static_cast<SkCanvas *>(canvas)->saveLayer(static_cast<const SkRect *>(bounds), static_cast<const SkPaint *>(paint));
}

int SkCanvas_saveLayerAlpha(void *canvas, const void * bounds, unsigned int alpha) {
    return static_cast<SkCanvas *>(canvas)->saveLayerAlpha(static_cast<const SkRect *>(bounds), alpha);
}

int SkCanvas_saveLayerAlphaf(void *canvas, const void * bounds, float alpha) {
    return static_cast<SkCanvas *>(canvas)->saveLayerAlphaf(static_cast<const SkRect *>(bounds), alpha);
}

void SkCanvas_scale(void *canvas, float sx, float sy) {
    static_cast<SkCanvas *>(canvas)->scale(sx, sy);
}

void SkCanvas_setMatrix(void *canvas, const void * matrix) {
    static_cast<SkCanvas *>(canvas)->setMatrix(* static_cast<const SkM44 *>(matrix));
}

void SkCanvas_setMatrix_2(void *canvas, const void * matrix) {
    static_cast<SkCanvas *>(canvas)->setMatrix(* static_cast<const SkMatrix *>(matrix));
}

void SkCanvas_skew(void *canvas, float sx, float sy) {
    static_cast<SkCanvas *>(canvas)->skew(sx, sy);
}

void SkCanvas_temporary_internal_getRgnClip(void *canvas, void * region) {
    static_cast<SkCanvas *>(canvas)->temporary_internal_getRgnClip(static_cast<SkRegion *>(region));
}

void SkCanvas_translate(void *canvas, float dx, float dy) {
    static_cast<SkCanvas *>(canvas)->translate(dx, dy);
}

bool SkCanvas_writePixels(void *canvas, const void * bitmap, int x, int y) {
    return static_cast<SkCanvas *>(canvas)->writePixels(* static_cast<const SkBitmap *>(bitmap), x, y);
}

bool
SkCanvas_writePixels_2(void *canvas, const void * info, const void * pixels, size_t rowBytes, int x, int y) {
    return static_cast<SkCanvas *>(canvas)->writePixels(* static_cast<const SkImageInfo *>(info), pixels, rowBytes, x, y);
}

// static

sk_canvas_t SkCanvas_MakeRasterDirect(const void * info, void *pixels, size_t rowBytes, const void * props) {
    return static_sk_canvas_make(SkCanvas::MakeRasterDirect(* static_cast<const SkImageInfo *>(info), pixels, rowBytes, static_cast<const SkSurfaceProps *>(props)));
}

sk_canvas_t SkCanvas_MakeRasterDirectN32(int width, int height, void * pixels, size_t rowBytes) {
    return static_sk_canvas_make(SkCanvas::MakeRasterDirectN32(width, height, static_cast<SkPMColor *>(pixels), rowBytes));
}

}