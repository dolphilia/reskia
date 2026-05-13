//
// Created by dolphilia on 2024/01/06.
//

#ifndef RAIA_SKIA_SK_CANVAS_H
#define RAIA_SKIA_SK_CANVAS_H

#include <stddef.h>
#include <stdint.h>
#include "sk_blend_mode.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_canvas.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_i_rect.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image_info.h"
#include "../handles/static_sk_m_44.h"
#include "../handles/static_sk_matrix.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_surface.h"
#include "../handles/static_sk_surface_props.h"
#include "../handles/static_sk_text_blob.h"
#include "../handles/static_sk_vertices.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_bitmap_t reskia_bitmap_t;
typedef struct reskia_canvas_save_layer_rec_t reskia_canvas_save_layer_rec_t;
typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_draw_shadow_rec_t reskia_draw_shadow_rec_t;
typedef struct reskia_drawable_t reskia_drawable_t;
typedef struct reskia_font_t reskia_font_t;
typedef struct reskia_graphite_recorder_t reskia_graphite_recorder_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_i_point_t reskia_i_point_t;
typedef struct reskia_image_set_entry_t reskia_image_set_entry_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_lattice_t reskia_lattice_t;
typedef struct reskia_m_44_t reskia_m_44_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_mesh_t reskia_mesh_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_picture_t reskia_picture_t;
typedef struct reskia_pixmap_t reskia_pixmap_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_r_rect_t reskia_r_rect_t;
typedef struct reskia_recording_context_t reskia_recording_context_t;
typedef struct reskia_region_t reskia_region_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_rsxform_t reskia_rsxform_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;
typedef struct reskia_string_t reskia_string_t;
typedef struct reskia_surface_props_t reskia_surface_props_t;
typedef struct reskia_surface_t reskia_surface_t;
typedef struct reskia_text_blob_t reskia_text_blob_t;
typedef struct reskia_vertices_t reskia_vertices_t;
typedef int32_t reskia_canvas_clip_op_t;
typedef int32_t reskia_canvas_filter_mode_t;
typedef int32_t reskia_canvas_point_mode_t;
typedef int32_t reskia_canvas_quad_aa_flags_t;
typedef int32_t reskia_canvas_src_rect_constraint_t;
typedef int32_t reskia_canvas_text_encoding_t;

reskia_canvas_t *SkCanvas_new(void); // () -> SkCanvas *
reskia_canvas_t *SkCanvas_newWithSizeProps(int width, int height, const reskia_surface_props_t *props); // (int width, int height, const SkSurfaceProps *props) -> SkCanvas *
/**
 * bitmap is required.
 * Returns a caller-owned canvas pointer.
 * Returns NULL on invalid input.
 * Skia: (SkBitmap *bitmap) -> SkCanvas *.
 */
reskia_canvas_t *SkCanvas_newFromBitmap(reskia_bitmap_t *bitmap);
/**
 * bitmap/props: non-null.
 * Returns a caller-owned canvas pointer.
 * Returns NULL on invalid input.
 * Skia: (const SkBitmap *bitmap, const SkSurfaceProps *props) -> SkCanvas *.
 */
reskia_canvas_t *SkCanvas_newFromBitmapWithProps(const reskia_bitmap_t *bitmap, const reskia_surface_props_t *props);
void SkCanvas_delete(reskia_canvas_t *canvas); // (SkCanvas *canvas)
/**
 * Borrowed raw pixels.
 * NULL canvas or unavailable top-layer storage returns NULL.
 * Pointer is owned by canvas/layer and valid only while that storage remains unchanged.
 * info/rowBytes/origin are optional out params.
 * Skia: (SkCanvas *canvas, SkImageInfo *info, size_t *rowBytes, SkIPoint *origin) -> void *.
 */
void * SkCanvas_accessTopLayerPixels(reskia_canvas_t *canvas, reskia_image_info_t *info, size_t *rowBytes, reskia_i_point_t *origin);
/**
 * Borrowed implementation-defined raster handle.
 * Caller must not free it.
 * Skia: (SkCanvas *canvas) -> SkRasterHandleAllocator::Handle.
 */
void * SkCanvas_accessTopRasterHandle(reskia_canvas_t *canvas);
/**
 * rect: non-null.
 * Skia: (SkCanvas *canvas, const SkIRect *rect).
 */
void SkCanvas_androidFramework_setDeviceClipRestriction(reskia_canvas_t *canvas, const reskia_i_rect_t *rect);
/**
 * color: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkColor4f *color).
 */
void SkCanvas_clear(reskia_canvas_t *canvas, const reskia_color_4f_t *color);
void SkCanvas_clearColor(reskia_canvas_t *canvas, uint32_t color); // NULL canvas is no-op.
/**
 * irect: non-null.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkIRect *irect, SkClipOp op).
 */
void SkCanvas_clipIRect(reskia_canvas_t *canvas, const reskia_i_rect_t *irect, reskia_canvas_clip_op_t op);
/**
 * path: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkPath *path, bool doAntiAlias).
 */
void SkCanvas_clipPath(reskia_canvas_t *canvas, const reskia_path_t *path, bool doAntiAlias);
/**
 * path: non-null.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkPath *path, SkClipOp op).
 */
void SkCanvas_clipPathWithOp(reskia_canvas_t *canvas, const reskia_path_t *path, reskia_canvas_clip_op_t op);
/**
 * path: non-null.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkPath *path, SkClipOp op, bool doAntiAlias).
 */
void SkCanvas_clipPathWithOpAA(reskia_canvas_t *canvas, const reskia_path_t *path, reskia_canvas_clip_op_t op, bool doAntiAlias);
/**
 * rect: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *rect, bool doAntiAlias).
 */
void SkCanvas_clipRect(reskia_canvas_t *canvas, const reskia_rect_t *rect, bool doAntiAlias);
/**
 * rect: non-null.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *rect, SkClipOp op).
 */
void SkCanvas_clipRectWithOp(reskia_canvas_t *canvas, const reskia_rect_t *rect, reskia_canvas_clip_op_t op);
/**
 * rect: non-null.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *rect, SkClipOp op, bool doAntiAlias).
 */
void SkCanvas_clipRectWithOpAA(reskia_canvas_t *canvas, const reskia_rect_t *rect, reskia_canvas_clip_op_t op, bool doAntiAlias);
/**
 * deviceRgn: non-null.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRegion *deviceRgn, SkClipOp op).
 */
void SkCanvas_clipRegion(reskia_canvas_t *canvas, const reskia_region_t *deviceRgn, reskia_canvas_clip_op_t op);
/**
 * rrect: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRRect *rrect, bool doAntiAlias).
 */
void SkCanvas_clipRRect(reskia_canvas_t *canvas, const reskia_r_rect_t *rrect, bool doAntiAlias);
/**
 * rrect: non-null.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRRect *rrect, SkClipOp op).
 */
void SkCanvas_clipRRectWithOp(reskia_canvas_t *canvas, const reskia_r_rect_t *rrect, reskia_canvas_clip_op_t op);
/**
 * rrect: non-null.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRRect *rrect, SkClipOp op, bool doAntiAlias).
 */
void SkCanvas_clipRRectWithOpAA(reskia_canvas_t *canvas, const reskia_r_rect_t *rrect, reskia_canvas_clip_op_t op, bool doAntiAlias);
/**
 * shader must be a valid handle.
 * op must be a valid SkClipOp.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_shader_t shader, SkClipOp op).
 */
void SkCanvas_clipShader(reskia_canvas_t *canvas, sk_shader_t shader, reskia_canvas_clip_op_t op);
/**
 * m44: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkM44 *m44).
 */
void SkCanvas_concat(reskia_canvas_t *canvas, const reskia_m_44_t *m44);
/**
 * matrix: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkMatrix *matrix).
 */
void SkCanvas_concatMatrix(reskia_canvas_t *canvas, const reskia_matrix_t *matrix);
void SkCanvas_discard(reskia_canvas_t *canvas); // (SkCanvas *canvas)
/**
 * rect/key: non-null.
 * data handle 0 is allowed.
 * Non-zero data must be valid.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *rect, const char key[], sk_data_t data).
 */
void SkCanvas_drawAnnotation(reskia_canvas_t *canvas, const reskia_rect_t *rect, const char * key, sk_data_t data);
/**
 * rect/key: non-null.
 * value may be NULL.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *rect, const char key[], SkData *value).
 */
void SkCanvas_drawAnnotationWithDataPtr(reskia_canvas_t *canvas, const reskia_rect_t *rect, const char * key, reskia_data_t *value);
/**
 * oval/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *oval, SkScalar startAngle, SkScalar sweepAngle, bool useCenter, const SkPaint *paint).
 */
void SkCanvas_drawArc(reskia_canvas_t *canvas, const reskia_rect_t *oval, float startAngle, float sweepAngle, bool useCenter, const reskia_paint_t *paint);
/**
 * count <= 0 is no-op.
 * atlas/xform/tex/sampling are non-null when count > 0.
 * mode must be a valid SkBlendMode when count > 0.
 * colors/cullRect/paint may be NULL.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    const SkImage *atlas,
 *    const SkRSXform xform[],
 *    const SkRect tex[],
 *    const SkColor colors[],
 *    int count,
 *    SkBlendMode mode,
 *    const SkSamplingOptions *sampling,
 *    const SkRect *cullRect,
 *    const SkPaint *paint).
 */
void SkCanvas_drawAtlas(reskia_canvas_t *canvas, const reskia_image_t *atlas, const reskia_rsxform_t *xform, const reskia_rect_t *tex, const uint32_t *colors, int count, reskia_blend_mode_t mode, const reskia_sampling_options_t *sampling, const reskia_rect_t *cullRect, const reskia_paint_t *paint);
/**
 * center must be a valid handle.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_point_t center, SkScalar radius, const SkPaint *paint).
 */
void SkCanvas_drawCircle(reskia_canvas_t *canvas, sk_point_t center, float radius, const reskia_paint_t *paint);
/**
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, SkScalar cx, SkScalar cy, SkScalar radius, const SkPaint *paint).
 */
void SkCanvas_drawCircleAt(reskia_canvas_t *canvas, float cx, float cy, float radius, const reskia_paint_t *paint);
/**
 * color: non-null.
 * mode must be a valid SkBlendMode.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkColor4f *color, SkBlendMode mode).
 */
void SkCanvas_drawColor(reskia_canvas_t *canvas, const reskia_color_4f_t *color, reskia_blend_mode_t mode);
/**
 * mode must be a valid SkBlendMode.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, SkColor color, SkBlendMode mode).
 */
void SkCanvas_drawColorU32(reskia_canvas_t *canvas, uint32_t color, reskia_blend_mode_t mode);
/**
 * drawable: borrowed non-null.
 * matrix may be NULL.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, SkDrawable *drawable, const SkMatrix *matrix).
 */
void SkCanvas_drawDrawable(reskia_canvas_t *canvas, reskia_drawable_t *drawable, const reskia_matrix_t *matrix);
/**
 * drawable: borrowed non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, SkDrawable *drawable, SkScalar x, SkScalar y).
 */
void SkCanvas_drawDrawableAt(reskia_canvas_t *canvas, reskia_drawable_t *drawable, float x, float y);
/**
 * outer/inner/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRRect *outer, const SkRRect *inner, const SkPaint *paint).
 */
void SkCanvas_drawDRRect(reskia_canvas_t *canvas, const reskia_r_rect_t *outer, const reskia_r_rect_t *inner, const reskia_paint_t *paint);
/**
 * count <= 0 is no-op.
 * glyphs/positions/clusters/font/paint are non-null when count > 0.
 * origin must be a valid handle when count > 0.
 * utf8text is non-null when textByteCount > 0.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    int count,
 *    const SkGlyphID glyphs[],
 *    const SkPoint positions[],
 *    const uint32_t clusters[],
 *    int textByteCount,
 *    const char utf8text[],
 *    sk_point_t origin,
 *    const SkFont *font,
 *    const SkPaint *paint).
 */
void SkCanvas_drawGlyphs(reskia_canvas_t *canvas, int count, const uint16_t *glyphs, const reskia_point_t *positions, const uint32_t *clusters, int textByteCount, const char *utf8text, sk_point_t origin, const reskia_font_t *font, const reskia_paint_t *paint);
/**
 * count <= 0 is no-op.
 * glyphs/positions/font/paint are non-null when count > 0.
 * origin must be a valid handle when count > 0.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    int count,
 *    const SkGlyphID glyphs[],
 *    const SkPoint positions[],
 *    sk_point_t origin,
 *    const SkFont *font,
 *    const SkPaint *paint).
 */
void SkCanvas_drawGlyphsAtPositions(reskia_canvas_t *canvas, int count, const uint16_t *glyphs, const reskia_point_t *positions, sk_point_t origin, const reskia_font_t *font, const reskia_paint_t *paint);
/**
 * count <= 0 is no-op.
 * glyphs/xforms/font/paint are non-null when count > 0.
 * origin must be a valid handle when count > 0.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    int count,
 *    const SkGlyphID glyphs[],
 *    const SkRSXform xforms[],
 *    sk_point_t origin,
 *    const SkFont *font,
 *    const SkPaint *paint).
 */
void SkCanvas_drawGlyphsWithXforms(reskia_canvas_t *canvas, int count, const uint16_t *glyphs, const reskia_rsxform_t *xforms, sk_point_t origin, const reskia_font_t *font, const reskia_paint_t *paint);
/**
 * canvas and valid image handle are required.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_image_t image, SkScalar left, SkScalar top).
 */
void SkCanvas_drawImage(reskia_canvas_t *canvas, sk_image_t image, float left, float top);
/**
 * canvas/valid image handle/sampling: non-null.
 * paint may be NULL.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_image_t image, SkScalar x, SkScalar y, const SkSamplingOptions *sampling, const SkPaint *paint).
 */
void SkCanvas_drawImageHandleWithSampling(reskia_canvas_t *canvas, sk_image_t image, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint);
/**
 * image is a borrowed non-null pointer.
 * sampling: non-null.
 * paint may be NULL.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkImage *image, SkScalar x, SkScalar y, const SkSamplingOptions *sampling, const SkPaint *paint).
 */
void SkCanvas_drawImagePtrWithSampling(reskia_canvas_t *canvas, const reskia_image_t *image, float x, float y, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint);
/**
 * image is a borrowed non-null pointer.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkImage *image, SkScalar left, SkScalar top).
 */
void SkCanvas_drawImagePtr(reskia_canvas_t *canvas, const reskia_image_t *image, float left, float top);
/**
 * image/lattice/dst: non-null borrowed pointers.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkImage *image, const SkCanvas::Lattice *lattice, const SkRect *dst).
 */
void SkCanvas_drawImageLattice(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_lattice_t *lattice, const reskia_rect_t *dst);
/**
 * image/lattice/dst: non-null borrowed pointers.
 * paint may be NULL.
 * filter must be a valid SkFilterMode.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    const SkImage *image,
 *    const SkCanvas::Lattice *lattice,
 *    const SkRect *dst,
 *    SkFilterMode filter,
 *    const SkPaint *paint).
 */
void SkCanvas_drawImageLatticeWithFilter(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_lattice_t *lattice, const reskia_rect_t *dst, reskia_canvas_filter_mode_t filter, const reskia_paint_t *paint);
/**
 * image/center/dst: non-null borrowed pointers.
 * paint may be NULL.
 * filter must be a valid SkFilterMode.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkImage *image, const SkIRect *center, const SkRect *dst, SkFilterMode filter, const SkPaint *paint).
 */
void SkCanvas_drawImageNine(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_i_rect_t *center, const reskia_rect_t *dst, reskia_canvas_filter_mode_t filter, const reskia_paint_t *paint);
/**
 * canvas/valid image handle/dst/sampling: non-null.
 * paint may be NULL.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_image_t image, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint).
 */
void SkCanvas_drawImageRect(reskia_canvas_t *canvas, sk_image_t image, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint);
/**
 * canvas/valid image handle/src/dst/sampling: non-null.
 * paint may be NULL.
 * constraint must be a valid SkCanvas::SrcRectConstraint.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    sk_image_t image,
 *    const SkRect *src,
 *    const SkRect *dst,
 *    const SkSamplingOptions *sampling,
 *    const SkPaint *paint,
 *    SkCanvas::SrcRectConstraint constraint).
 */
void SkCanvas_drawImageRectHandleWithSrcDst(reskia_canvas_t *canvas, sk_image_t image, const reskia_rect_t *src, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_canvas_src_rect_constraint_t constraint);
/**
 * image/dst/sampling are non-null borrowed pointers.
 * paint may be NULL.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkImage *image, const SkRect *dst, const SkSamplingOptions *sampling, const SkPaint *paint).
 */
void SkCanvas_drawImageRectPtr(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint);
/**
 * image/src/dst/sampling are non-null borrowed pointers.
 * paint may be NULL.
 * constraint must be a valid SkCanvas::SrcRectConstraint.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    const SkImage *image,
 *    const SkRect *src,
 *    const SkRect *dst,
 *    const SkSamplingOptions *sampling,
 *    const SkPaint *paint,
 *    SkCanvas::SrcRectConstraint constraint).
 */
void SkCanvas_drawImageRectPtrWithSrcDst(reskia_canvas_t *canvas, const reskia_image_t *image, const reskia_rect_t *src, const reskia_rect_t *dst, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_canvas_src_rect_constraint_t constraint);
/**
 * rect/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkIRect *rect, const SkPaint *paint).
 */
void SkCanvas_drawIRect(reskia_canvas_t *canvas, const reskia_i_rect_t *rect, const reskia_paint_t *paint);
/**
 * p0/p1 must be valid handles.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_point_t p0, sk_point_t p1, const SkPaint *paint).
 */
void SkCanvas_drawLine(reskia_canvas_t *canvas, sk_point_t p0, sk_point_t p1, const reskia_paint_t *paint);
/**
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, SkScalar x0, SkScalar y0, SkScalar x1, SkScalar y1, const SkPaint *paint).
 */
void SkCanvas_drawLineXY(reskia_canvas_t *canvas, float x0, float y0, float x1, float y1, const reskia_paint_t *paint);
/**
 * mesh/paint: non-null.
 * blender must be a valid handle.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkMesh *mesh, sk_blender_t blender, const SkPaint *paint).
 */
void SkCanvas_drawMesh(reskia_canvas_t *canvas, const reskia_mesh_t *mesh, sk_blender_t blender, const reskia_paint_t *paint);
/**
 * oval/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *oval, const SkPaint *paint).
 */
void SkCanvas_drawOval(reskia_canvas_t *canvas, const reskia_rect_t *oval, const reskia_paint_t *paint);
/**
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkPaint *paint).
 */
void SkCanvas_drawPaint(reskia_canvas_t *canvas, const reskia_paint_t *paint);
/**
 * cubics/texCoords/paint: non-null.
 * mode must be a valid SkBlendMode.
 * colors may be NULL.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    const SkPoint cubics[12],
 *    const SkColor colors[4],
 *    const SkPoint texCoords[4],
 *    SkBlendMode mode,
 *    const SkPaint *paint).
 */
void SkCanvas_drawPatch(reskia_canvas_t *canvas, const reskia_point_t *cubics, const uint32_t colors[4], const reskia_point_t *texCoords, reskia_blend_mode_t mode, const reskia_paint_t *paint);
/**
 * path/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkPath *path, const SkPaint *paint).
 */
void SkCanvas_drawPath(reskia_canvas_t *canvas, const reskia_path_t *path, const reskia_paint_t *paint);
/**
 * Invalid picture handle is no-op.
 * Skia: (SkCanvas *canvas, sk_picture_t picture).
 */
void SkCanvas_drawPicture(reskia_canvas_t *canvas, sk_picture_t picture);
/**
 * Invalid picture handle is no-op. matrix/paint may be NULL.
 * Skia: (SkCanvas *canvas, sk_picture_t picture, const SkMatrix *matrix, const SkPaint *paint).
 */
void SkCanvas_drawPictureHandleWithMatrixPaint(reskia_canvas_t *canvas, sk_picture_t picture, const reskia_matrix_t *matrix, const reskia_paint_t *paint);
/**
 * picture is a borrowed non-null pointer.
 * Caller must not free it through this API.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkPicture *picture).
 */
void SkCanvas_drawPicturePtr(reskia_canvas_t *canvas, const reskia_picture_t *picture);
/**
 * picture is a borrowed non-null pointer.
 * Caller must not free it through this API.
 * matrix/paint may be NULL.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkPicture *picture, const SkMatrix *matrix, const SkPaint *paint).
 */
void SkCanvas_drawPicturePtrWithMatrixPaint(reskia_canvas_t *canvas, const reskia_picture_t *picture, const reskia_matrix_t *matrix, const reskia_paint_t *paint);
/**
 * p must be a valid handle.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_point_t p, const SkPaint *paint).
 */
void SkCanvas_drawPoint(reskia_canvas_t *canvas, sk_point_t p, const reskia_paint_t *paint);
/**
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, SkScalar x, SkScalar y, const SkPaint *paint).
 */
void SkCanvas_drawPointXY(reskia_canvas_t *canvas, float x, float y, const reskia_paint_t *paint);
/**
 * mode must be a valid SkCanvas::PointMode.
 * count == 0 is no-op.
 * pts is non-null when count > 0.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, SkCanvas::PointMode mode, size_t count, const SkPoint pts[], const SkPaint *paint).
 */
void SkCanvas_drawPoints(reskia_canvas_t *canvas, reskia_canvas_point_mode_t mode, size_t count, const reskia_point_t *pts, const reskia_paint_t *paint);
/**
 * rect must be a valid handle.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_rect_t rect, const SkPaint *paint).
 */
void SkCanvas_drawRect(reskia_canvas_t *canvas, sk_rect_t rect, const reskia_paint_t *paint);
/**
 * region/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRegion *region, const SkPaint *paint).
 */
void SkCanvas_drawRegion(reskia_canvas_t *canvas, const reskia_region_t *region, const reskia_paint_t *paint);
/**
 * rect/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *rect, SkScalar rx, SkScalar ry, const SkPaint *paint).
 */
void SkCanvas_drawRoundRect(reskia_canvas_t *canvas, const reskia_rect_t *rect, float rx, float ry, const reskia_paint_t *paint);
/**
 * rrect/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRRect *rrect, const SkPaint *paint).
 */
void SkCanvas_drawRRect(reskia_canvas_t *canvas, const reskia_r_rect_t *rrect, const reskia_paint_t *paint);
/**
 * byteLength == 0 is no-op.
 * Borrowed raw text bytes must be non-null and readable for byteLength during call.
 * encoding must be a valid SkTextEncoding.
 * font/paint: non-null when byteLength > 0.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    const void *text,
 *    size_t byteLength,
 *    SkTextEncoding encoding,
 *    SkScalar x,
 *    SkScalar y,
 *    const SkFont *font,
 *    const SkPaint *paint).
 */
void SkCanvas_drawSimpleText(reskia_canvas_t *canvas, const void *text, size_t byteLength, reskia_canvas_text_encoding_t encoding, float x, float y, const reskia_font_t *font, const reskia_paint_t *paint);
/**
 * str/font/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const char str[], SkScalar x, SkScalar y, const SkFont *font, const SkPaint *paint).
 */
void SkCanvas_drawString(reskia_canvas_t *canvas, const char * str, float x, float y, const reskia_font_t *font, const reskia_paint_t *paint);
/**
 * str/font/paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkString *str, SkScalar x, SkScalar y, const SkFont *font, const SkPaint *paint).
 */
void SkCanvas_drawStringObject(reskia_canvas_t *canvas, const reskia_string_t *str, float x, float y, const reskia_font_t *font, const reskia_paint_t *paint);
/**
 * text_blob must be a valid handle.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_text_blob_t text_blob, SkScalar x, SkScalar y, const SkPaint *paint).
 */
void SkCanvas_drawTextBlob(reskia_canvas_t *canvas, sk_text_blob_t text_blob, float x, float y, const reskia_paint_t *paint);
/**
 * blob is a borrowed non-null pointer.
 * Caller must not free it through this API.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkTextBlob *blob, SkScalar x, SkScalar y, const SkPaint *paint).
 */
void SkCanvas_drawTextBlobPtr(reskia_canvas_t *canvas, const reskia_text_blob_t *blob, float x, float y, const reskia_paint_t *paint);
/**
 * vertices must be a valid handle.
 * mode must be a valid SkBlendMode.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, sk_vertices_t vertices, SkBlendMode mode, const SkPaint *paint).
 */
void SkCanvas_drawVertices(reskia_canvas_t *canvas, sk_vertices_t vertices, reskia_blend_mode_t mode, const reskia_paint_t *paint);
/**
 * vertices: borrowed non-null.
 * mode must be a valid SkBlendMode.
 * paint: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkVertices *vertices, SkBlendMode mode, const SkPaint *paint).
 */
void SkCanvas_drawVerticesPtr(reskia_canvas_t *canvas, const reskia_vertices_t *vertices, reskia_blend_mode_t mode, const reskia_paint_t *paint);
/**
 * cnt <= 0 is no-op.
 * imageSet/sampling are non-null when cnt > 0.
 * dstClips/preViewMatrices/paint may be NULL.
 * constraint must be a valid SkCanvas::SrcRectConstraint.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    const SkCanvas::ImageSetEntry imageSet[],
 *    int cnt,
 *    const SkPoint dstClips[],
 *    const SkMatrix preViewMatrices[],
 *    const SkSamplingOptions *sampling,
 *    const SkPaint *paint,
 *    SkCanvas::SrcRectConstraint constraint).
 */
void SkCanvas_experimental_DrawEdgeAAImageSet(reskia_canvas_t *canvas, const reskia_image_set_entry_t *imageSet, int cnt, const reskia_point_t *dstClips, const reskia_matrix_t *preViewMatrices, const reskia_sampling_options_t *sampling, const reskia_paint_t *paint, reskia_canvas_src_rect_constraint_t constraint);
/**
 * rect/color: non-null.
 * aaFlags must be between kNone_QuadAAFlags and kAll_QuadAAFlags.
 * mode must be a valid SkBlendMode.
 * clip may be NULL.
 * Invalid input is no-op.
 * Skia:
 *   (SkCanvas *canvas,
 *    const SkRect *rect,
 *    const SkPoint clip[4],
 *    SkCanvas::QuadAAFlags aaFlags,
 *    const SkColor4f *color,
 *    SkBlendMode mode).
 */
void SkCanvas_experimental_DrawEdgeAAQuad(reskia_canvas_t *canvas, const reskia_rect_t *rect, const reskia_point_t *clip, reskia_canvas_quad_aa_flags_t aaFlags, const reskia_color_4f_t *color, reskia_blend_mode_t mode);
/**
 * rect: non-null.
 * aaFlags must be between kNone_QuadAAFlags and kAll_QuadAAFlags.
 * mode must be a valid SkBlendMode.
 * clip may be NULL.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkRect *rect, const SkPoint clip[4], SkCanvas::QuadAAFlags aaFlags, SkColor color, SkBlendMode mode).
 */
void SkCanvas_experimental_DrawEdgeAAQuadU32Color(reskia_canvas_t *canvas, const reskia_rect_t *rect, const reskia_point_t *clip, reskia_canvas_quad_aa_flags_t aaFlags, uint32_t color, reskia_blend_mode_t mode);
/**
 * Returns a caller-owned i-size handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_i_size_t.
 */
sk_i_size_t SkCanvas_getBaseLayerSize(reskia_canvas_t *canvas);
/**
 * Returns a caller-owned surface props handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_surface_props_t.
 */
sk_surface_props_t SkCanvas_getBaseProps(reskia_canvas_t *canvas);
/**
 * Returns a caller-owned irect handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_i_rect_t.
 */
sk_i_rect_t SkCanvas_getDeviceClipBounds(reskia_canvas_t *canvas);
/**
 * bounds: non-null out param.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, SkIRect *bounds) -> bool.
 */
bool SkCanvas_getDeviceClipBoundsInto(reskia_canvas_t *canvas, reskia_i_rect_t *bounds);
/**
 * Returns a caller-owned rect handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_rect_t.
 */
sk_rect_t SkCanvas_getLocalClipBounds(reskia_canvas_t *canvas);
/**
 * bounds: non-null out param.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, SkRect *bounds) -> bool.
 */
bool SkCanvas_getLocalClipBoundsInto(reskia_canvas_t *canvas, reskia_rect_t *bounds);
/**
 * Returns a caller-owned matrix handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_m_44_t.
 */
sk_m_44_t SkCanvas_getLocalToDevice(reskia_canvas_t *canvas);
/**
 * Returns a caller-owned matrix handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_matrix_t.
 */
sk_matrix_t SkCanvas_getLocalToDeviceAs3x3(reskia_canvas_t *canvas);
/**
 * props: non-null out param.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, SkSurfaceProps *props) -> bool.
 */
bool SkCanvas_getProps(reskia_canvas_t *canvas, reskia_surface_props_t *props);
int SkCanvas_getSaveCount(reskia_canvas_t *canvas); // NULL canvas returns 0.
/**
 * Borrowed pointer; caller must not free.
 * Skia: (SkCanvas *canvas) -> SkSurface *.
 */
reskia_surface_t *SkCanvas_getSurface(reskia_canvas_t *canvas);
/**
 * Returns a caller-owned surface props handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_surface_props_t.
 */
sk_surface_props_t SkCanvas_getTopProps(reskia_canvas_t *canvas);
/**
 * Returns a caller-owned matrix handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_matrix_t.
 */
sk_matrix_t SkCanvas_getTotalMatrix(reskia_canvas_t *canvas);
/**
 * Returns a caller-owned image info handle.
 * Returns 0 when canvas is NULL.
 * Skia: (SkCanvas *canvas) -> sk_image_info_t.
 */
sk_image_info_t SkCanvas_imageInfo(reskia_canvas_t *canvas);
bool SkCanvas_isClipEmpty(reskia_canvas_t *canvas); // NULL canvas returns false.
bool SkCanvas_isClipRect(reskia_canvas_t *canvas); // NULL canvas returns false.
/**
 * info: non-null.
 * props may be NULL.
 * factory failure returns 0.
 * Skia: (SkCanvas *canvas, const SkImageInfo *info, const SkSurfaceProps *props) -> sk_surface_t.
 */
sk_surface_t SkCanvas_makeSurface(reskia_canvas_t *canvas, const reskia_image_info_t *info, const reskia_surface_props_t *props);
/**
 * pixmap: non-null out param.
 * Returned pixmap borrows canvas pixels and is valid only while canvas storage remains unchanged.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, SkPixmap *pixmap) -> bool.
 */
bool SkCanvas_peekPixels(reskia_canvas_t *canvas, reskia_pixmap_t *pixmap);
/**
 * path/rec: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkPath *path, const SkDrawShadowRec *rec).
 */
void SkCanvas_private_draw_shadow_rec(reskia_canvas_t *canvas, const reskia_path_t *path, const reskia_draw_shadow_rec_t *rec);
/**
 * path: non-null.
 * Skia: (SkCanvas *canvas, const SkPath *path) -> bool.
 */
bool SkCanvas_quickReject(reskia_canvas_t *canvas, const reskia_path_t *path); // Invalid input returns false.
/**
 * rect: non-null.
 * Skia: (SkCanvas *canvas, const SkRect *rect) -> bool.
 */
bool SkCanvas_quickRejectRect(reskia_canvas_t *canvas, const reskia_rect_t *rect); // Invalid input returns false.
/**
 * bitmap: non-null output storage.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, const SkBitmap *bitmap, int srcX, int srcY) -> bool.
 */
bool SkCanvas_readPixels(reskia_canvas_t *canvas, const reskia_bitmap_t *bitmap, int srcX, int srcY);
/**
 * dstInfo/dstPixels: non-null.
 * dstRowBytes must satisfy dstInfo.validRowBytes.
 * dstPixels is caller-owned mutable buffer and is not retained.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, const SkImageInfo *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY) -> bool.
 */
bool SkCanvas_readPixelsWithImageInfo(reskia_canvas_t *canvas, const reskia_image_info_t *dstInfo, void *dstPixels, size_t dstRowBytes, int srcX, int srcY);
/**
 * pixmap: non-null output storage.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, const SkPixmap *pixmap, int srcX, int srcY) -> bool.
 */
bool SkCanvas_readPixelsWithPixmap(reskia_canvas_t *canvas, const reskia_pixmap_t *pixmap, int srcX, int srcY);
/**
 * Borrowed pointer; caller must not free.
 * Skia: (SkCanvas *canvas) -> skgpu::graphite::Recorder *.
 */
reskia_graphite_recorder_t *SkCanvas_recorder(reskia_canvas_t *canvas);
/**
 * Borrowed pointer; caller must not free.
 * Skia: (SkCanvas *canvas) -> GrRecordingContext *.
 */
reskia_recording_context_t *SkCanvas_recordingContext(reskia_canvas_t *canvas);
void SkCanvas_resetMatrix(reskia_canvas_t *canvas); // NULL canvas is no-op.
void SkCanvas_restore(reskia_canvas_t *canvas); // NULL canvas is no-op.
void SkCanvas_restoreToCount(reskia_canvas_t *canvas, int saveCount); // NULL canvas is no-op.
void SkCanvas_rotate(reskia_canvas_t *canvas, float degrees); // NULL canvas is no-op.
void SkCanvas_rotateAround(reskia_canvas_t *canvas, float degrees, float px, float py); // NULL canvas is no-op.
int SkCanvas_save(reskia_canvas_t *canvas); // NULL canvas returns 0.
/**
 * canvas/layerRec: non-null.
 * Invalid input returns 0.
 * Skia: (SkCanvas *canvas, const SkCanvas::SaveLayerRec *layerRec) -> int.
 */
int SkCanvas_saveLayer(reskia_canvas_t *canvas, const reskia_canvas_save_layer_rec_t *layerRec);
/**
 * canvas/bounds: non-null.
 * paint may be NULL.
 * Invalid input returns 0.
 * Skia: (SkCanvas *canvas, const SkRect *bounds, const SkPaint *paint) -> int.
 */
int SkCanvas_saveLayerWithBoundsPaintRef(reskia_canvas_t *canvas, const reskia_rect_t *bounds, const reskia_paint_t *paint);
/**
 * bounds/paint may be NULL.
 * NULL canvas returns 0.
 * Skia: (SkCanvas *canvas, const SkRect *bounds, const SkPaint *paint) -> int.
 */
int SkCanvas_saveLayerWithBoundsPaintPtr(reskia_canvas_t *canvas, const reskia_rect_t *bounds, const reskia_paint_t *paint);
/**
 * bounds may be NULL.
 * alpha must be between 0 and 255.
 * NULL canvas returns 0.
 * Skia: (SkCanvas *canvas, const SkRect *bounds, U8CPU alpha) -> int.
 */
int SkCanvas_saveLayerAlpha(reskia_canvas_t *canvas, const reskia_rect_t *bounds, uint32_t alpha);
/**
 * bounds may be NULL.
 * alpha must be finite and between 0.0 and 1.0.
 * NULL canvas returns 0.
 * Skia: (SkCanvas *canvas, const SkRect *bounds, float alpha) -> int.
 */
int SkCanvas_saveLayerAlphaf(reskia_canvas_t *canvas, const reskia_rect_t *bounds, float alpha);
void SkCanvas_scale(reskia_canvas_t *canvas, float sx, float sy); // NULL canvas is no-op.
/**
 * matrix: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkM44 *matrix).
 */
void SkCanvas_setMatrix(reskia_canvas_t *canvas, const reskia_m_44_t *matrix);
/**
 * matrix: non-null.
 * Invalid input is no-op.
 * Skia: (SkCanvas *canvas, const SkMatrix *matrix).
 */
void SkCanvas_setMatrix3x3(reskia_canvas_t *canvas, const reskia_matrix_t *matrix);
void SkCanvas_skew(reskia_canvas_t *canvas, float sx, float sy); // NULL canvas is no-op.
/**
 * region: non-null out param.
 * Skia: (SkCanvas *canvas, SkRegion *region).
 */
void SkCanvas_temporary_internal_getRgnClip(reskia_canvas_t *canvas, reskia_region_t *region);
void SkCanvas_translate(reskia_canvas_t *canvas, float dx, float dy); // NULL canvas is no-op.
/**
 * bitmap: non-null input storage.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, const SkBitmap *bitmap, int x, int y) -> bool.
 */
bool SkCanvas_writePixels(reskia_canvas_t *canvas, const reskia_bitmap_t *bitmap, int x, int y);
/**
 * info/pixels: non-null.
 * rowBytes must satisfy info.validRowBytes.
 * pixels is caller-owned read-only buffer and is not retained.
 * Invalid input returns false.
 * Skia: (SkCanvas *canvas, const SkImageInfo *info, const void *pixels, size_t rowBytes, int x, int y) -> bool.
 */
bool SkCanvas_writePixelsWithImageInfo(reskia_canvas_t *canvas, const reskia_image_info_t *info, const void *pixels, size_t rowBytes, int x, int y);
// static
/**
 * info/pixels: non-null.
 * rowBytes must satisfy info.validRowBytes.
 * pixels are caller-owned mutable backing store and must outlive returned canvas.
 * props may be NULL.
 * Invalid input/factory failure returns 0.
 * Skia: (const SkImageInfo *info, void *pixels, size_t rowBytes, const SkSurfaceProps *props) -> sk_canvas_t.
 */
sk_canvas_t SkCanvas_MakeRasterDirect(const reskia_image_info_t *info, void *pixels, size_t rowBytes, const reskia_surface_props_t *props);
/**
 * width/height must be >= 0.
 * pixels are caller-owned mutable N32 backing store and must outlive returned canvas.
 * rowBytes must be at least width * sizeof(SkPMColor).
 * Invalid input/factory failure returns 0.
 * Skia: (int width, int height, SkPMColor *pixels, size_t rowBytes) -> sk_canvas_t}.
 */
sk_canvas_t SkCanvas_MakeRasterDirectN32(int width, int height, void *pixels, size_t rowBytes);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CANVAS_H
