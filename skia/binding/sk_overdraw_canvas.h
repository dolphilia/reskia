//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_OVERDRAW_CANVAS_H
#define RAIA_SKIA_SK_OVERDRAW_CANVAS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef uint32_t reskia_color_t;
typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_draw_shadow_rec_t reskia_draw_shadow_rec_t;
typedef struct reskia_drawable_t reskia_drawable_t;
typedef struct reskia_glyph_run_list_t reskia_glyph_run_list_t;
typedef struct reskia_image_set_entry_t reskia_image_set_entry_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_lattice_t reskia_lattice_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_overdraw_canvas_t reskia_overdraw_canvas_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_picture_t reskia_picture_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_r_rect_t reskia_r_rect_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_region_t reskia_region_t;
typedef struct reskia_rsxform_t reskia_rsxform_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;
typedef struct reskia_text_blob_t reskia_text_blob_t;
typedef struct reskia_vertices_t reskia_vertices_t;

void SkOverdrawCanvas_delete(reskia_overdraw_canvas_t *overdraw_canvas); // (SkOverdrawCanvas *overdraw_canvas)
void SkOverdrawCanvas_onDrawTextBlob(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_text_blob_t *blob, float scalar1, float scalar2, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkTextBlob *blob, SkScalar scalar1, SkScalar scalar2, const SkPaint *paint)
void SkOverdrawCanvas_onDrawGlyphRunList(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_glyph_run_list_t *glyphRunList, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const sktext::GlyphRunList *glyphRunList, const SkPaint *paint)
void SkOverdrawCanvas_onDrawPatch(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_point_t * point1, const reskia_color_t * color, const reskia_point_t * point2, int mode, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkPoint point1[12], const SkColor color[4], const SkPoint point2[4], SkBlendMode mode, const SkPaint *paint)
void SkOverdrawCanvas_onDrawPaint(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkPaint *paint)
void SkOverdrawCanvas_onDrawBehind(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkPaint *paint)
void SkOverdrawCanvas_onDrawRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkRect *rect, const SkPaint *paint)
void SkOverdrawCanvas_onDrawRegion(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_region_t *region, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkRegion *region, const SkPaint *paint)
void SkOverdrawCanvas_onDrawOval(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkRect *rect, const SkPaint *paint)
void SkOverdrawCanvas_onDrawArc(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, float scalar1, float scalar2, bool v, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkRect *rect, SkScalar scalar1, SkScalar scalar2, bool v, const SkPaint *paint)
void SkOverdrawCanvas_onDrawDRRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_r_rect_t *rect1, const reskia_r_rect_t *rect2, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkRRect *rect1, const SkRRect *rect2, const SkPaint *paint)
void SkOverdrawCanvas_onDrawRRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_r_rect_t *rect, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkRRect *rect, const SkPaint *paint)
void SkOverdrawCanvas_onDrawPoints(reskia_overdraw_canvas_t *overdraw_canvas, int mode, size_t size, const reskia_point_t * point, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, SkOverdrawCanvas::PointMode mode, size_t size, const SkPoint point[], const SkPaint *paint)
void SkOverdrawCanvas_onDrawVerticesObject(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_vertices_t *vertices, int mode, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkVertices *vertices, SkBlendMode mode, const SkPaint *paint)
void SkOverdrawCanvas_onDrawPath(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_path_t *path, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkPath *path, const SkPaint *paint)
void SkOverdrawCanvas_onDrawImage2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, float scalar1, float scalar2, const reskia_sampling_options_t *options, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkImage *image, SkScalar scalar1, SkScalar scalar2, const SkSamplingOptions *options, const SkPaint *paint)
void SkOverdrawCanvas_onDrawImageRect2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, const reskia_rect_t *rect1, const reskia_rect_t *rect2, const reskia_sampling_options_t *options, const reskia_paint_t *paint, int constraint); // (SkOverdrawCanvas *overdraw_canvas, const SkImage *image, const SkRect *rect1, const SkRect *rect2, const SkSamplingOptions *options, const SkPaint *paint, SkOverdrawCanvas::SrcRectConstraint constraint)
void SkOverdrawCanvas_onDrawImageLattice2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, const reskia_lattice_t *lattice, const reskia_rect_t *rect, int mode, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkImage *image, const SkOverdrawCanvas::Lattice *lattice, const SkRect *rect, SkFilterMode mode, const SkPaint *paint)
void SkOverdrawCanvas_onDrawAtlas2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t * image, const reskia_rsxform_t * form, const reskia_rect_t * rect1, const reskia_color_t * color, int v, int mode, const reskia_sampling_options_t *options, const reskia_rect_t *rect2, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkImage *image, const SkRSXform form[], const SkRect rect1[], const SkColor color[], int v, SkBlendMode mode, const SkSamplingOptions *options, const SkRect *rect2, const SkPaint *paint)
void SkOverdrawCanvas_onDrawDrawable(reskia_overdraw_canvas_t *overdraw_canvas, reskia_drawable_t *drawable, const reskia_matrix_t *matrix); // (SkOverdrawCanvas *overdraw_canvas, SkDrawable *drawable, const SkMatrix *matrix)
void SkOverdrawCanvas_onDrawPicture(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_picture_t *picture, const reskia_matrix_t *matrix, const reskia_paint_t *paint); // (SkOverdrawCanvas *overdraw_canvas, const SkPicture *picture, const SkMatrix *matrix, const SkPaint *paint)
void SkOverdrawCanvas_onDrawAnnotation(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const char key[], reskia_data_t *value); // (SkOverdrawCanvas *overdraw_canvas, const SkRect *rect, const char key[], SkData *value)
void SkOverdrawCanvas_onDrawShadowRec(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_path_t *path, const reskia_draw_shadow_rec_t *rec); // (SkOverdrawCanvas *overdraw_canvas, const SkPath *path, const SkDrawShadowRec *rec)
void SkOverdrawCanvas_onDrawEdgeAAQuad(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_point_t * point, int flags, const reskia_color_4f_t *color, int mode); // (SkOverdrawCanvas *overdraw_canvas, const SkRect *rect, const SkPoint point[4], SkCanvas::QuadAAFlags flags, const SkColor4f *color, SkBlendMode mode)
void SkOverdrawCanvas_onDrawEdgeAAImageSet2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_set_entry_t * entry, int count, const reskia_point_t * point, const reskia_matrix_t * matrix, const reskia_sampling_options_t *options, const reskia_paint_t *paint, int constraint); // (SkOverdrawCanvas *overdraw_canvas, const SkOverdrawCanvas::ImageSetEntry entry[], int count, const SkPoint point[], const SkMatrix matrix[], const SkSamplingOptions *options, const SkPaint *paint, SkOverdrawCanvas::SrcRectConstraint constraint)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_OVERDRAW_CANVAS_H
