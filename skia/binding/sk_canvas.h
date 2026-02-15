//
// Created by dolphilia on 2024/01/06.
//

#ifndef RAIA_SKIA_SK_CANVAS_H
#define RAIA_SKIA_SK_CANVAS_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_blender.h"
#include "../static/static_sk_canvas.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_i_size.h"
#include "../static/static_sk_image.h"
#include "../static/static_sk_image_info.h"
#include "../static/static_sk_m_44.h"
#include "../static/static_sk_matrix.h"
#include "../static/static_sk_picture.h"
#include "../static/static_sk_point.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_shader.h"
#include "../static/static_sk_surface.h"
#include "../static/static_sk_surface_props.h"
#include "../static/static_sk_text_blob.h"
#include "../static/static_sk_vertices.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_canvas_t reskia_canvas_t;

reskia_canvas_t *SkCanvas_new(void); // () -> SkCanvas *
reskia_canvas_t *SkCanvas_new_2(int width, int height, const void *props); // (int width, int height, const SkSurfaceProps *props) -> SkCanvas *
reskia_canvas_t *SkCanvas_new_3(void *bitmap); // (SkBitmap *bitmap) -> SkCanvas *
reskia_canvas_t *SkCanvas_new_4(const void *bitmap, const void *props); // (const SkBitmap *bitmap, const SkSurfaceProps *props) -> SkCanvas *
void SkCanvas_delete(reskia_canvas_t *canvas); // (SkCanvas *canvas)
void * SkCanvas_accessTopLayerPixels(reskia_canvas_t *canvas, void *info, void *rowBytes, void *origin); // (SkCanvas *canvas, SkImageInfo *info, size_t *rowBytes, SkIPoint *origin) -> void *
void * SkCanvas_accessTopRasterHandle(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> SkRasterHandleAllocator::Handle
void SkCanvas_androidFramework_setDeviceClipRestriction(reskia_canvas_t *canvas, const void *rect); // (SkCanvas *canvas, const SkIRect *rect)
void SkCanvas_clear(reskia_canvas_t *canvas, const void *color); // (SkCanvas *canvas, const SkColor4f *color)
void SkCanvas_clear_2(reskia_canvas_t *canvas, uint32_t color); // (SkCanvas *canvas, SkColor color)
void SkCanvas_clipIRect(reskia_canvas_t *canvas, const void *irect, int op); // (SkCanvas *canvas, const SkIRect *irect, SkClipOp op)
void SkCanvas_clipPath(reskia_canvas_t *canvas, const void *path, bool doAntiAlias); // (SkCanvas *canvas, const SkPath *path, bool doAntiAlias)
void SkCanvas_clipPath_2(reskia_canvas_t *canvas, const void *path, int op); // (SkCanvas *canvas, const SkPath *path, SkClipOp op)
void SkCanvas_clipPath_3(reskia_canvas_t *canvas, const void *path, int op, bool doAntiAlias); // (SkCanvas *canvas, const SkPath *path, SkClipOp op, bool doAntiAlias)
void SkCanvas_clipRect(reskia_canvas_t *canvas, const void *rect, bool doAntiAlias); // (SkCanvas *canvas, const SkRect *rect, bool doAntiAlias)
void SkCanvas_clipRect_2(reskia_canvas_t *canvas, const void *rect, int op); // (SkCanvas *canvas, const SkRect *rect, SkClipOp op)
void SkCanvas_clipRect_3(reskia_canvas_t *canvas, const void *rect, int op, bool doAntiAlias); // (SkCanvas *canvas, const SkRect *rect, SkClipOp op, bool doAntiAlias)
void SkCanvas_clipRegion(reskia_canvas_t *canvas, const void *deviceRgn, int op); // (SkCanvas *canvas, const SkRegion *deviceRgn, SkClipOp op)
void SkCanvas_clipRRect(reskia_canvas_t *canvas, const void *rrect, bool doAntiAlias); // (SkCanvas *canvas, const SkRRect *rrect, bool doAntiAlias)
void SkCanvas_clipRRect_2(reskia_canvas_t *canvas, const void *rrect, int op); // (SkCanvas *canvas, const SkRRect *rrect, SkClipOp op)
void SkCanvas_clipRRect_3(reskia_canvas_t *canvas, const void *rrect, int op, bool doAntiAlias); // (SkCanvas *canvas, const SkRRect *rrect, SkClipOp op, bool doAntiAlias)
void SkCanvas_clipShader(reskia_canvas_t *canvas, sk_shader_t shader, int op); // (SkCanvas *canvas, sk_shader_t shader, SkClipOp op)
void SkCanvas_concat(reskia_canvas_t *canvas, const void * m44); // (SkCanvas *canvas, const SkM44 *m44)
void SkCanvas_concat_2(reskia_canvas_t *canvas, const void * matrix); // (SkCanvas *canvas, const SkMatrix *matrix)
void SkCanvas_discard(reskia_canvas_t *canvas); // (SkCanvas *canvas)
void SkCanvas_drawAnnotation(reskia_canvas_t *canvas, const void *rect, const char * key, sk_data_t data); // (SkCanvas *canvas, const SkRect *rect, const char key[], sk_data_t data)
void SkCanvas_drawAnnotation_2(reskia_canvas_t *canvas, const void *rect, const char * key, void *value); // (SkCanvas *canvas, const SkRect *rect, const char key[], SkData *value)
void SkCanvas_drawArc(reskia_canvas_t *canvas, const void *oval, float startAngle, float sweepAngle, bool useCenter, const void *paint); // (SkCanvas *canvas, const SkRect *oval, SkScalar startAngle, SkScalar sweepAngle, bool useCenter, const SkPaint *paint)
void SkCanvas_drawAtlas(reskia_canvas_t *canvas, const void *atlas, const void * xform, const void * tex, const void * colors, int count, int mode, const void *sampling, const void *cullRect, const void *paint); // (SkCanvas *canvas, const SkImage *atlas, const SkRSXform xform[], const SkRect tex[], const SkColor colors[], int count, SkBlendMode mode, const SkSamplingOptions *sampling, const SkRect *cullRect, const SkPaint *paint)
void SkCanvas_drawCircle(reskia_canvas_t *canvas, sk_point_t center, float radius, const void *paint); // (SkCanvas *canvas, sk_point_t center, SkScalar radius, const SkPaint *paint)
void SkCanvas_drawCircle_2(reskia_canvas_t *canvas, float cx, float cy, float radius, const void *paint); // (SkCanvas *canvas, SkScalar cx, SkScalar cy, SkScalar radius, const SkPaint *paint)
void SkCanvas_drawColor(reskia_canvas_t *canvas, const void * color, int mode); // (SkCanvas *canvas, const SkColor4f *color, SkBlendMode mode)
void SkCanvas_drawColor_2(reskia_canvas_t *canvas, uint32_t color, int mode); // (SkCanvas *canvas, SkColor color, SkBlendMode mode)
void SkCanvas_drawDrawable(reskia_canvas_t *canvas, void *drawable, const void *matrix); // (SkCanvas *canvas, SkDrawable *drawable, const SkMatrix *matrix)
void SkCanvas_drawDrawable_2(reskia_canvas_t *canvas, void *drawable, float x, float y); // (SkCanvas *canvas, SkDrawable *drawable, SkScalar x, SkScalar y)
void SkCanvas_drawDRRect(reskia_canvas_t *canvas, const void *outer, const void *inner, const void *paint); // (SkCanvas *canvas, const SkRRect *outer, const SkRRect *inner, const SkPaint *paint)
void SkCanvas_drawGlyphs(reskia_canvas_t *canvas, int count, const void * glyphs, const void * positions, const void * clusters, int textByteCount, const char * utf8text, sk_point_t origin, const void *font, const void *paint); // (SkCanvas *canvas, int count, const SkGlyphID glyphs[], const SkPoint positions[], const uint32_t clusters[], int textByteCount, const char utf8text[], sk_point_t origin, const SkFont *font, const SkPaint *paint)
void SkCanvas_drawGlyphs_2(reskia_canvas_t *canvas, int count, const void * glyphs, const void * positions, sk_point_t origin, const void *font, const void *paint); // (SkCanvas *canvas, int count, const SkGlyphID glyphs[], const SkPoint positions[], sk_point_t origin, const SkFont *font, const SkPaint *paint)
void SkCanvas_drawGlyphs_3(reskia_canvas_t *canvas, int count, const void * glyphs, const void * xforms, sk_point_t origin, const void *font, const void *paint); // (SkCanvas *canvas, int count, const SkGlyphID glyphs[], const SkRSXform xforms[], sk_point_t origin, const SkFont *font, const SkPaint *paint)
void SkCanvas_drawImage(reskia_canvas_t *canvas, sk_image_t image, float left, float top); // (SkCanvas *canvas, sk_image_t image, SkScalar left, SkScalar top)
void SkCanvas_drawImage_2(reskia_canvas_t *canvas, sk_image_t image, float x, float y, const void *sampling, const void *paint); // (SkCanvas *canvas, sk_image_t image, SkScalar x, SkScalar y, const SkSamplingOptions *sampling, const SkPaint *paint)
void SkCanvas_drawImage_3(reskia_canvas_t *canvas, const void *image, float x, float y, const void *sampling, const void *paint); // (SkCanvas *canvas, const SkImage *image, SkScalar x, SkScalar y, const SkSamplingOptions *sampling, const SkPaint *paint)
void SkCanvas_drawImage_4(reskia_canvas_t *canvas, const void *image, float left, float top); // (SkCanvas *canvas, const SkImage *image, SkScalar left, SkScalar top)
void SkCanvas_drawImageLattice(reskia_canvas_t *canvas, const void *image, const void *lattice, const void *dst); // (SkCanvas *canvas, const SkImage *image, const SkCanvas::Lattice *lattice, const SkRect *dst)
void SkCanvas_drawImageLattice_2(reskia_canvas_t *canvas, const void *image, const void *lattice, const void *dst, int filter, const void *paint); // (SkCanvas *canvas, const SkImage *image, const SkCanvas::Lattice *lattice, const SkRect *dst, SkFilterMode filter, const SkPaint *paint)
void SkCanvas_drawImageNine(reskia_canvas_t *canvas, const void *image, const void *center, const void *dst, int filter, const void *paint); // (SkCanvas *canvas, const SkImage *image, const SkIRect *center, const SkRect *dst, SkFilterMode filter, const SkPaint *paint)
void SkCanvas_drawImageRect(reskia_canvas_t *canvas, sk_image_t image, const void *dst, const void *sampling, const void *paint); // (SkCanvas *canvas, sk_image_t image, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint)
void SkCanvas_drawImageRect_2(reskia_canvas_t *canvas, sk_image_t image, const void *src, const void *dst, const void *sampling, const void *paint, int constraint); // (SkCanvas *canvas, sk_image_t image, const SkRect *src, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkCanvas_drawImageRect_3(reskia_canvas_t *canvas, const void *image, const void *dst, const void *sampling, const void *paint); // (SkCanvas *canvas, const SkImage *image, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint)
void SkCanvas_drawImageRect_4(reskia_canvas_t *canvas, const void *image, const void *src, const void *dst, const void *sampling, const void *paint, int constraint); // (SkCanvas *canvas, const SkImage *image, const SkRect *src, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkCanvas_drawIRect(reskia_canvas_t *canvas, const void *rect, const void *paint); // (SkCanvas *canvas, const SkIRect *rect, const SkPaint *paint)
void SkCanvas_drawLine(reskia_canvas_t *canvas, sk_point_t p0, sk_point_t p1, const void *paint); // (SkCanvas *canvas, sk_point_t p0, sk_point_t p1, const SkPaint *paint)
void SkCanvas_drawLine_2(reskia_canvas_t *canvas, float x0, float y0, float x1, float y1, const void *paint); // (SkCanvas *canvas, SkScalar x0, SkScalar y0, SkScalar x1, SkScalar y1, const SkPaint *paint)
void SkCanvas_drawMesh(reskia_canvas_t *canvas, const void *mesh, sk_blender_t blender, const void *paint); // (SkCanvas *canvas, const SkMesh *mesh, sk_blender_t blender, const SkPaint *paint)
void SkCanvas_drawOval(reskia_canvas_t *canvas, const void *oval, const void *paint); // (SkCanvas *canvas, const SkRect *oval, const SkPaint *paint)
void SkCanvas_drawPaint(reskia_canvas_t *canvas, const void *paint); // (SkCanvas *canvas, const SkPaint *paint)
void SkCanvas_drawPatch(reskia_canvas_t *canvas, const void * cubics, const uint32_t colors[4], const void * texCoords, int mode, const void *paint); // (SkCanvas *canvas, const SkPoint cubics[12], const SkColor colors[4], const SkPoint texCoords[4], SkBlendMode mode, const SkPaint *paint)
void SkCanvas_drawPath(reskia_canvas_t *canvas, const void *path, const void *paint); // (SkCanvas *canvas, const SkPath *path, const SkPaint *paint)
void SkCanvas_drawPicture(reskia_canvas_t *canvas, sk_picture_t picture); // (SkCanvas *canvas, sk_picture_t picture)
void SkCanvas_drawPicture_2(reskia_canvas_t *canvas, sk_picture_t picture, const void *matrix, const void *paint); // (SkCanvas *canvas, sk_picture_t picture, const SkMatrix *matrix, const SkPaint *paint)
void SkCanvas_drawPicture_3(reskia_canvas_t *canvas, const void *picture); // (SkCanvas *canvas, const SkPicture *picture)
void SkCanvas_drawPicture_4(reskia_canvas_t *canvas, const void *picture, const void *matrix, const void *paint); // (SkCanvas *canvas, const SkPicture *picture, const SkMatrix *matrix, const SkPaint *paint)
void SkCanvas_drawPoint(reskia_canvas_t *canvas, sk_point_t p, const void *paint); // (SkCanvas *canvas, sk_point_t p, const SkPaint *paint)
void SkCanvas_drawPoint_2(reskia_canvas_t *canvas, float x, float y, const void *paint); // (SkCanvas *canvas, SkScalar x, SkScalar y, const SkPaint *paint)
void SkCanvas_drawPoints(reskia_canvas_t *canvas, int mode, size_t count, const void * pts, const void *paint); // (SkCanvas *canvas, SkCanvas::PointMode mode, size_t count, const SkPoint pts[], const SkPaint *paint)
void SkCanvas_drawRect(reskia_canvas_t *canvas, sk_rect_t rect, const void *paint); // (SkCanvas *canvas, sk_rect_t rect, const SkPaint *paint)
void SkCanvas_drawRegion(reskia_canvas_t *canvas, const void *region, const void *paint); // (SkCanvas *canvas, const SkRegion *region, const SkPaint *paint)
void SkCanvas_drawRoundRect(reskia_canvas_t *canvas, const void *rect, float rx, float ry, const void *paint); // (SkCanvas *canvas, const SkRect *rect, SkScalar rx, SkScalar ry, const SkPaint *paint)
void SkCanvas_drawRRect(reskia_canvas_t *canvas, const void *rrect, const void *paint); // (SkCanvas *canvas, const SkRRect *rrect, const SkPaint *paint)
void SkCanvas_drawSimpleText(reskia_canvas_t *canvas, const void *text, size_t byteLength, int encoding, float x, float y, const void *font, const void *paint); // (SkCanvas *canvas, const void *text, size_t byteLength, SkTextEncoding encoding, SkScalar x, SkScalar y, const SkFont *font, const SkPaint *paint)
void SkCanvas_drawString(reskia_canvas_t *canvas, const char * str, float x, float y, const void *font, const void *paint); // (SkCanvas *canvas, const char str[], SkScalar x, SkScalar y, const SkFont *font, const SkPaint *paint)
void SkCanvas_drawString_2(reskia_canvas_t *canvas, const void *str, float x, float y, const void *font, const void *paint); // (SkCanvas *canvas, const SkString *str, SkScalar x, SkScalar y, const SkFont *font, const SkPaint *paint)
void SkCanvas_drawTextBlob(reskia_canvas_t *canvas, sk_text_blob_t text_blob, float x, float y, const void *paint); // (SkCanvas *canvas, sk_text_blob_t text_blob, SkScalar x, SkScalar y, const SkPaint *paint)
void SkCanvas_drawTextBlob_2(reskia_canvas_t *canvas, const void *blob, float x, float y, const void *paint); // (SkCanvas *canvas, const SkTextBlob *blob, SkScalar x, SkScalar y, const SkPaint *paint)
void SkCanvas_drawVertices(reskia_canvas_t *canvas, sk_vertices_t vertices, int mode, const void *paint); // (SkCanvas *canvas, sk_vertices_t vertices, SkBlendMode mode, const SkPaint *paint)
void SkCanvas_drawVertices_2(reskia_canvas_t *canvas, const void *vertices, int mode, const void *paint); // (SkCanvas *canvas, const SkVertices *vertices, SkBlendMode mode, const SkPaint *paint)
void SkCanvas_experimental_DrawEdgeAAImageSet(reskia_canvas_t *canvas, const void * imageSet, int cnt, const void * dstClips, const void * preViewMatrices, const void *sampling, const void *paint, int constraint); // (SkCanvas *canvas, const SkCanvas::ImageSetEntry imageSet[], int cnt, const SkPoint dstClips[], const SkMatrix preViewMatrices[], const SkSamplingOptions *sampling, const SkPaint *paint, SkCanvas::SrcRectConstraint constraint)
void SkCanvas_experimental_DrawEdgeAAQuad(reskia_canvas_t *canvas, const void *rect, const void * clip, int aaFlags, const void * color, int mode); // (SkCanvas *canvas, const SkRect *rect, const SkPoint clip[4], SkCanvas::QuadAAFlags aaFlags, const SkColor4f *color, SkBlendMode mode)
void SkCanvas_experimental_DrawEdgeAAQuad_2(reskia_canvas_t *canvas, const void *rect, const void * clip, int aaFlags, uint32_t color, int mode); // (SkCanvas *canvas, const SkRect *rect, const SkPoint clip[4], SkCanvas::QuadAAFlags aaFlags, SkColor color, SkBlendMode mode)
sk_i_size_t SkCanvas_getBaseLayerSize(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_i_size_t
sk_surface_props_t SkCanvas_getBaseProps(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_surface_props_t
sk_i_rect_t SkCanvas_getDeviceClipBounds(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_i_rect_t
bool SkCanvas_getDeviceClipBounds_2(reskia_canvas_t *canvas, void *bounds); // (SkCanvas *canvas, SkIRect *bounds) -> bool
sk_rect_t SkCanvas_getLocalClipBounds(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_rect_t
bool SkCanvas_getLocalClipBounds_2(reskia_canvas_t *canvas, void *bounds); // (SkCanvas *canvas, SkRect *bounds) -> bool
sk_m_44_t SkCanvas_getLocalToDevice(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_m_44_t
sk_matrix_t SkCanvas_getLocalToDeviceAs3x3(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_matrix_t
bool SkCanvas_getProps(reskia_canvas_t *canvas, void *props); // (SkCanvas *canvas, SkSurfaceProps *props) -> bool
int SkCanvas_getSaveCount(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> int
void * SkCanvas_getSurface(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> SkSurface *
sk_surface_props_t SkCanvas_getTopProps(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_surface_props_t
sk_matrix_t SkCanvas_getTotalMatrix(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_matrix_t
sk_image_info_t SkCanvas_imageInfo(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> sk_image_info_t
bool SkCanvas_isClipEmpty(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> bool
bool SkCanvas_isClipRect(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> bool
sk_surface_t SkCanvas_makeSurface(reskia_canvas_t *canvas, const void *info, const void *props); // (SkCanvas *canvas, const SkImageInfo *info, const SkSurfaceProps *props) -> sk_surface_t
bool SkCanvas_peekPixels(reskia_canvas_t *canvas, void *pixmap); // (SkCanvas *canvas, SkPixmap *pixmap) -> bool
void SkCanvas_private_draw_shadow_rec(reskia_canvas_t *canvas, const void *path, const void *rec); // (SkCanvas *canvas, const SkPath *path, const SkDrawShadowRec *rec)
bool SkCanvas_quickReject(reskia_canvas_t *canvas, const void *path); // (SkCanvas *canvas, const SkPath *path) -> bool
bool SkCanvas_quickReject_2(reskia_canvas_t *canvas, const void *rect); // (SkCanvas *canvas, const SkRect *rect) -> bool
bool SkCanvas_readPixels(reskia_canvas_t *canvas, const void *bitmap, int srcX, int srcY); // (SkCanvas *canvas, const SkBitmap *bitmap, int srcX, int srcY) -> bool
bool SkCanvas_readPixels_2(reskia_canvas_t *canvas, const void *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY); // (SkCanvas *canvas, const SkImageInfo *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) -> bool
bool SkCanvas_readPixels_3(reskia_canvas_t *canvas, const void *pixmap, int srcX, int srcY); // (SkCanvas *canvas, const SkPixmap *pixmap, int srcX, int srcY) -> bool
void * SkCanvas_recorder(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> skgpu::graphite::Recorder *
void * SkCanvas_recordingContext(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> GrRecordingContext *
void SkCanvas_resetMatrix(reskia_canvas_t *canvas); // (SkCanvas *canvas)
void SkCanvas_restore(reskia_canvas_t *canvas); // (SkCanvas *canvas)
void SkCanvas_restoreToCount(reskia_canvas_t *canvas, int saveCount); // (SkCanvas *canvas, int saveCount)
void SkCanvas_rotate(reskia_canvas_t *canvas, float degrees); // (SkCanvas *canvas, SkScalar degrees)
void SkCanvas_rotate_2(reskia_canvas_t *canvas, float degrees, float px, float py); // (SkCanvas *canvas, SkScalar degrees, SkScalar px, SkScalar py)
int SkCanvas_save(reskia_canvas_t *canvas); // (SkCanvas *canvas) -> int
int SkCanvas_saveLayer(reskia_canvas_t *canvas, const void *layerRec); // (SkCanvas *canvas, const SkCanvas::SaveLayerRec *layerRec) -> int
int SkCanvas_saveLayer_2(reskia_canvas_t *canvas, const void *bounds, const void *paint); // (SkCanvas *canvas, const SkRect *bounds, const SkPaint *paint) -> int
int SkCanvas_saveLayer_3(reskia_canvas_t *canvas, const void *bounds, const void *paint); // (SkCanvas *canvas, const SkRect *bounds, const SkPaint *paint) -> int
int SkCanvas_saveLayerAlpha(reskia_canvas_t *canvas, const void *bounds, uint32_t alpha); // (SkCanvas *canvas, const SkRect *bounds, U8CPU alpha) -> int
int SkCanvas_saveLayerAlphaf(reskia_canvas_t *canvas, const void *bounds, float alpha); // (SkCanvas *canvas, const SkRect *bounds, float alpha) -> int
void SkCanvas_scale(reskia_canvas_t *canvas, float sx, float sy); // (SkCanvas *canvas, SkScalar sx, SkScalar sy)
void SkCanvas_setMatrix(reskia_canvas_t *canvas, const void *matrix); // (SkCanvas *canvas, const SkM44 *matrix)
void SkCanvas_setMatrix_2(reskia_canvas_t *canvas, const void *matrix); // (SkCanvas *canvas, const SkMatrix *matrix)
void SkCanvas_skew(reskia_canvas_t *canvas, float sx, float sy); // (SkCanvas *canvas, SkScalar sx, SkScalar sy)
void SkCanvas_temporary_internal_getRgnClip(reskia_canvas_t *canvas, void *region); // (SkCanvas *canvas, SkRegion *region)
void SkCanvas_translate(reskia_canvas_t *canvas, float dx, float dy); // (SkCanvas *canvas, SkScalar dx, SkScalar dy)
bool SkCanvas_writePixels(reskia_canvas_t *canvas, const void *bitmap, int x, int y); // (SkCanvas *canvas, const SkBitmap *bitmap, int x, int y) -> bool
bool SkCanvas_writePixels_2(reskia_canvas_t *canvas, const void *info, const void *pixels, size_t rowBytes, int x, int y); // (SkCanvas *canvas, const SkImageInfo *info, const void *pixels, size_t rowBytes, int x, int y) -> bool
// static
sk_canvas_t SkCanvas_MakeRasterDirect(const void *info, void *pixels, size_t rowBytes, const void *props); // (const SkImageInfo *info, void *pixels, size_t rowBytes, const SkSurfaceProps *props) -> sk_canvas_t
sk_canvas_t SkCanvas_MakeRasterDirectN32(int width, int height, void *pixels, size_t rowBytes); // (int width, int height, SkPMColor *pixels, size_t rowBytes) -> sk_canvas_t}

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CANVAS_H
