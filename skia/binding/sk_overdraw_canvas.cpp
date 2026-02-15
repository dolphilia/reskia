//
// Created by dolphilia on 2024/01/09.
//

#include "sk_overdraw_canvas.h"

#include "include/core/SkOverdrawCanvas.h"

extern "C" {

void SkOverdrawCanvas_delete(reskia_overdraw_canvas_t *overdraw_canvas) {
    delete reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas);
}

void SkOverdrawCanvas_onDrawTextBlob(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_text_blob_t *blob, SkScalar scalar1, SkScalar scalar2, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawTextBlob(reinterpret_cast<const SkTextBlob *>(blob), scalar1, scalar2, * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawGlyphRunList(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_glyph_run_list_t *glyphRunList, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawGlyphRunList(* reinterpret_cast<const sktext::GlyphRunList *>(glyphRunList), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPatch(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_point_t * point1, const reskia_color_t * color, const reskia_point_t * point2, int mode, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPatch(reinterpret_cast<const SkPoint *>(point1), reinterpret_cast<const SkColor *>(color), reinterpret_cast<const SkPoint *>(point2), static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPaint(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPaint(* reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawBehind(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawBehind(* reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawRect(* reinterpret_cast<const SkRect *>(rect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRegion(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_region_t *region, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawRegion(* reinterpret_cast<const SkRegion *>(region), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawOval(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawOval(* reinterpret_cast<const SkRect *>(rect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawArc(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, float scalar1, float scalar2, bool v, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawArc(* reinterpret_cast<const SkRect *>(rect), scalar1, scalar2, v, * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawDRRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_r_rect_t *rect1, const reskia_r_rect_t *rect2, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawDRRect(* reinterpret_cast<const SkRRect *>(rect1), * reinterpret_cast<const SkRRect *>(rect2), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_r_rect_t *rect, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawRRect(* reinterpret_cast<const SkRRect *>(rect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPoints(reskia_overdraw_canvas_t *overdraw_canvas, int mode, size_t size, const reskia_point_t * point, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPoints(static_cast<SkOverdrawCanvas::PointMode>(mode), size, reinterpret_cast<const SkPoint *>(point), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawVerticesObject(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_vertices_t *vertices, int mode, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawVerticesObject(reinterpret_cast<const SkVertices *>(vertices), static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPath(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_path_t *path, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPath(* reinterpret_cast<const SkPath *>(path), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawImage2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, float scalar1, float scalar2, const reskia_sampling_options_t *options, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawImage2(reinterpret_cast<const SkImage *>(image), scalar1, scalar2, * reinterpret_cast<const SkSamplingOptions *>(options), reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawImageRect2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, const reskia_rect_t *rect1, const reskia_rect_t *rect2, const reskia_sampling_options_t *options, const reskia_paint_t *paint, int constraint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawImageRect2(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkRect *>(rect1), * reinterpret_cast<const SkRect *>(rect2), * reinterpret_cast<const SkSamplingOptions *>(options), reinterpret_cast<const SkPaint *>(paint), static_cast<SkOverdrawCanvas::SrcRectConstraint>(constraint));
}

void SkOverdrawCanvas_onDrawImageLattice2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, const reskia_lattice_t *lattice, const reskia_rect_t *rect, int mode, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawImageLattice2(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkOverdrawCanvas::Lattice *>(lattice), * reinterpret_cast<const SkRect *>(rect), static_cast<SkFilterMode>(mode), reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawAtlas2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t * image, const reskia_rsxform_t * form, const reskia_rect_t * rect1, const reskia_color_t * color, int v, int mode, const reskia_sampling_options_t *options, const reskia_rect_t *rect2, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawAtlas2(reinterpret_cast<const SkImage *>(image), reinterpret_cast<const SkRSXform *>(form), reinterpret_cast<const SkRect *>(rect1), reinterpret_cast<const SkColor *>(color), v, static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkSamplingOptions *>(options), reinterpret_cast<const SkRect *>(rect2), reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawDrawable(reskia_overdraw_canvas_t *overdraw_canvas, reskia_drawable_t *drawable, const reskia_matrix_t *matrix) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawDrawable(reinterpret_cast<SkDrawable *>(drawable), reinterpret_cast<const SkMatrix *>(matrix));
}

void SkOverdrawCanvas_onDrawPicture(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_picture_t *picture, const reskia_matrix_t *matrix, const reskia_paint_t *paint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPicture(reinterpret_cast<const SkPicture *>(picture), reinterpret_cast<const SkMatrix *>(matrix), reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawAnnotation(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const char key[], reskia_data_t *value) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawAnnotation(* reinterpret_cast<const SkRect *>(rect), key, reinterpret_cast<SkData *>(value));
}

void SkOverdrawCanvas_onDrawShadowRec(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_path_t *path, const reskia_draw_shadow_rec_t *rec) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawShadowRec(* reinterpret_cast<const SkPath *>(path), * reinterpret_cast<const SkDrawShadowRec *>(rec));
}

void SkOverdrawCanvas_onDrawEdgeAAQuad(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_point_t * point, int flags, const reskia_color_4f_t *color, int mode) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawEdgeAAQuad(* reinterpret_cast<const SkRect *>(rect), reinterpret_cast<const SkPoint *>(point), static_cast<SkCanvas::QuadAAFlags>(flags), * reinterpret_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkOverdrawCanvas_onDrawEdgeAAImageSet2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_set_entry_t * entry, int count, const reskia_point_t * point, const reskia_matrix_t * matrix, const reskia_sampling_options_t *options, const reskia_paint_t *paint, int constraint) {
    reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawEdgeAAImageSet2(reinterpret_cast<const SkOverdrawCanvas::ImageSetEntry *>(entry), count, reinterpret_cast<const SkPoint *>(point), reinterpret_cast<const SkMatrix *>(matrix), * reinterpret_cast<const SkSamplingOptions *>(options), reinterpret_cast<const SkPaint *>(paint), static_cast<SkOverdrawCanvas::SrcRectConstraint>(constraint));
}

}
