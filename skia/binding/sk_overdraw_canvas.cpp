//
// Created by dolphilia on 2024/01/09.
//

#include "sk_overdraw_canvas.h"

#include "include/core/SkOverdrawCanvas.h"

extern "C" {

void SkOverdrawCanvas_delete(void *overdraw_canvas) {
    delete static_cast<SkOverdrawCanvas *>(overdraw_canvas);
}

void SkOverdrawCanvas_onDrawTextBlob(void *overdraw_canvas, const void *blob, SkScalar scalar1, SkScalar scalar2, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawTextBlob(static_cast<const SkTextBlob *>(blob), scalar1, scalar2, * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawGlyphRunList(void *overdraw_canvas, const void *glyphRunList, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawGlyphRunList(* static_cast<const sktext::GlyphRunList *>(glyphRunList), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPatch(void *overdraw_canvas, const void * point1, const void * color, const void * point2, int mode, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPatch(static_cast<const SkPoint *>(point1), static_cast<const SkColor *>(color), static_cast<const SkPoint *>(point2), static_cast<SkBlendMode>(mode), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPaint(void *overdraw_canvas, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPaint(* static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawBehind(void *overdraw_canvas, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawBehind(* static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRect(void *overdraw_canvas, const void *rect, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawRect(* static_cast<const SkRect *>(rect), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRegion(void *overdraw_canvas, const void *region, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawRegion(* static_cast<const SkRegion *>(region), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawOval(void *overdraw_canvas, const void *rect, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawOval(* static_cast<const SkRect *>(rect), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawArc(void *overdraw_canvas, const void *rect, float scalar1, float scalar2, bool v, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawArc(* static_cast<const SkRect *>(rect), scalar1, scalar2, v, * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawDRRect(void *overdraw_canvas, const void *rect1, const void *rect2, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawDRRect(* static_cast<const SkRRect *>(rect1), * static_cast<const SkRRect *>(rect2), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRRect(void *overdraw_canvas, const void *rect, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawRRect(* static_cast<const SkRRect *>(rect), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPoints(void *overdraw_canvas, int mode, size_t size, const void * point, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPoints(static_cast<SkOverdrawCanvas::PointMode>(mode), size, static_cast<const SkPoint *>(point), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawVerticesObject(void *overdraw_canvas, const void *vertices, int mode, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawVerticesObject(static_cast<const SkVertices *>(vertices), static_cast<SkBlendMode>(mode), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPath(void *overdraw_canvas, const void *path, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPath(* static_cast<const SkPath *>(path), * static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawImage2(void *overdraw_canvas, const void *image, float scalar1, float scalar2, const void *options, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawImage2(static_cast<const SkImage *>(image), scalar1, scalar2, * static_cast<const SkSamplingOptions *>(options), static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawImageRect2(void *overdraw_canvas, const void *image, const void *rect1, const void *rect2, const void *options, const void *paint, int constraint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawImageRect2(static_cast<const SkImage *>(image), * static_cast<const SkRect *>(rect1), * static_cast<const SkRect *>(rect2), * static_cast<const SkSamplingOptions *>(options), static_cast<const SkPaint *>(paint), static_cast<SkOverdrawCanvas::SrcRectConstraint>(constraint));
}

void SkOverdrawCanvas_onDrawImageLattice2(void *overdraw_canvas, const void *image, const void *lattice, const void *rect, int mode, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawImageLattice2(static_cast<const SkImage *>(image), * static_cast<const SkOverdrawCanvas::Lattice *>(lattice), * static_cast<const SkRect *>(rect), static_cast<SkFilterMode>(mode), static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawAtlas2(void *overdraw_canvas, const void * image, const void * form, const void * rect1, const void * color, int v, int mode, const void *options, const void *rect2, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawAtlas2(static_cast<const SkImage *>(image), static_cast<const SkRSXform *>(form), static_cast<const SkRect *>(rect1), static_cast<const SkColor *>(color), v, static_cast<SkBlendMode>(mode), * static_cast<const SkSamplingOptions *>(options), static_cast<const SkRect *>(rect2), static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawDrawable(void *overdraw_canvas, void *drawable, const void *matrix) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawDrawable(static_cast<SkDrawable *>(drawable), static_cast<const SkMatrix *>(matrix));
}

void SkOverdrawCanvas_onDrawPicture(void *overdraw_canvas, const void *picture, const void *matrix, const void *paint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawPicture(static_cast<const SkPicture *>(picture), static_cast<const SkMatrix *>(matrix), static_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawAnnotation(void *overdraw_canvas, const void *rect, const char key[], void *value) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawAnnotation(* static_cast<const SkRect *>(rect), key, static_cast<SkData *>(value));
}

void SkOverdrawCanvas_onDrawShadowRec(void *overdraw_canvas, const void *path, const void *rec) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawShadowRec(* static_cast<const SkPath *>(path), * static_cast<const SkDrawShadowRec *>(rec));
}

void SkOverdrawCanvas_onDrawEdgeAAQuad(void *overdraw_canvas, const void *rect, const void * point, int flags, const void *color, int mode) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawEdgeAAQuad(* static_cast<const SkRect *>(rect), static_cast<const SkPoint *>(point), static_cast<SkCanvas::QuadAAFlags>(flags), * static_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkOverdrawCanvas_onDrawEdgeAAImageSet2(void *overdraw_canvas, const void * entry, int count, const void * point, const void * matrix, const void *options, const void *paint, int constraint) {
    static_cast<SkOverdrawCanvas *>(overdraw_canvas)->onDrawEdgeAAImageSet2(static_cast<const SkOverdrawCanvas::ImageSetEntry *>(entry), count, static_cast<const SkPoint *>(point), static_cast<const SkMatrix *>(matrix), * static_cast<const SkSamplingOptions *>(options), static_cast<const SkPaint *>(paint), static_cast<SkOverdrawCanvas::SrcRectConstraint>(constraint));
}

}