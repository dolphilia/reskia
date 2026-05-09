//
// Created by dolphilia on 2024/01/09.
//

#include "sk_overdraw_canvas.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkOverdrawCanvas.h"

namespace {

SkOverdrawCanvas *as_overdraw_canvas(reskia_overdraw_canvas_t *overdraw_canvas) {
    return reinterpret_cast<SkOverdrawCanvas *>(overdraw_canvas);
}

}  // namespace

extern "C" {

reskia_overdraw_canvas_t *SkOverdrawCanvas_new(reskia_canvas_t *canvas) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_overdraw_canvas_t *>(new SkOverdrawCanvas(reinterpret_cast<SkCanvas *>(canvas)));
}

void SkOverdrawCanvas_delete(reskia_overdraw_canvas_t *overdraw_canvas) {
    delete as_overdraw_canvas(overdraw_canvas);
}

void SkOverdrawCanvas_onDrawTextBlob(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_text_blob_t *blob, SkScalar scalar1, SkScalar scalar2, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || blob == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawTextBlob(reinterpret_cast<const SkTextBlob *>(blob), scalar1, scalar2, * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawGlyphRunList(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_glyph_run_list_t *glyphRunList, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || glyphRunList == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawGlyphRunList(* reinterpret_cast<const sktext::GlyphRunList *>(glyphRunList), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPatch(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_point_t * point1, const reskia_color_t * color, const reskia_point_t * point2, reskia_overdraw_canvas_blend_mode_t mode, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || point1 == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawPatch(reinterpret_cast<const SkPoint *>(point1), reinterpret_cast<const SkColor *>(color), reinterpret_cast<const SkPoint *>(point2), static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPaint(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawPaint(* reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawBehind(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawBehind(* reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || rect == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawRect(* reinterpret_cast<const SkRect *>(rect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRegion(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_region_t *region, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || region == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawRegion(* reinterpret_cast<const SkRegion *>(region), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawOval(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || rect == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawOval(* reinterpret_cast<const SkRect *>(rect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawArc(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, float scalar1, float scalar2, bool v, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || rect == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawArc(* reinterpret_cast<const SkRect *>(rect), scalar1, scalar2, v, * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawDRRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_r_rect_t *rect1, const reskia_r_rect_t *rect2, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || rect1 == nullptr || rect2 == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawDRRect(* reinterpret_cast<const SkRRect *>(rect1), * reinterpret_cast<const SkRRect *>(rect2), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawRRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_r_rect_t *rect, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || rect == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawRRect(* reinterpret_cast<const SkRRect *>(rect), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPoints(reskia_overdraw_canvas_t *overdraw_canvas, reskia_overdraw_canvas_point_mode_t mode, size_t size, const reskia_point_t * point, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || (size > 0 && point == nullptr) || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawPoints(static_cast<SkOverdrawCanvas::PointMode>(mode), size, reinterpret_cast<const SkPoint *>(point), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawVerticesObject(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_vertices_t *vertices, reskia_overdraw_canvas_blend_mode_t mode, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || vertices == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawVerticesObject(reinterpret_cast<const SkVertices *>(vertices), static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawPath(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_path_t *path, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || path == nullptr || paint == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawPath(* reinterpret_cast<const SkPath *>(path), * reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawImage2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, float scalar1, float scalar2, const reskia_sampling_options_t *options, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || image == nullptr || options == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawImage2(reinterpret_cast<const SkImage *>(image), scalar1, scalar2, * reinterpret_cast<const SkSamplingOptions *>(options), reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawImageRect2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, const reskia_rect_t *rect1, const reskia_rect_t *rect2, const reskia_sampling_options_t *options, const reskia_paint_t *paint, reskia_overdraw_canvas_src_rect_constraint_t constraint) {
    if (overdraw_canvas == nullptr || image == nullptr || rect1 == nullptr || rect2 == nullptr || options == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawImageRect2(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkRect *>(rect1), * reinterpret_cast<const SkRect *>(rect2), * reinterpret_cast<const SkSamplingOptions *>(options), reinterpret_cast<const SkPaint *>(paint), static_cast<SkOverdrawCanvas::SrcRectConstraint>(constraint));
}

void SkOverdrawCanvas_onDrawImageLattice2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, const reskia_lattice_t *lattice, const reskia_rect_t *rect, reskia_overdraw_canvas_filter_mode_t mode, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || image == nullptr || lattice == nullptr || rect == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawImageLattice2(reinterpret_cast<const SkImage *>(image), * reinterpret_cast<const SkOverdrawCanvas::Lattice *>(lattice), * reinterpret_cast<const SkRect *>(rect), static_cast<SkFilterMode>(mode), reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawAtlas2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t * image, const reskia_rsxform_t * form, const reskia_rect_t * rect1, const reskia_color_t * color, int v, reskia_overdraw_canvas_blend_mode_t mode, const reskia_sampling_options_t *options, const reskia_rect_t *rect2, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || image == nullptr || v < 0 || (v > 0 && (form == nullptr || rect1 == nullptr)) || options == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawAtlas2(reinterpret_cast<const SkImage *>(image), reinterpret_cast<const SkRSXform *>(form), reinterpret_cast<const SkRect *>(rect1), reinterpret_cast<const SkColor *>(color), v, static_cast<SkBlendMode>(mode), * reinterpret_cast<const SkSamplingOptions *>(options), reinterpret_cast<const SkRect *>(rect2), reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawDrawable(reskia_overdraw_canvas_t *overdraw_canvas, reskia_drawable_t *drawable, const reskia_matrix_t *matrix) {
    if (overdraw_canvas == nullptr || drawable == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawDrawable(reinterpret_cast<SkDrawable *>(drawable), reinterpret_cast<const SkMatrix *>(matrix));
}

void SkOverdrawCanvas_onDrawPicture(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_picture_t *picture, const reskia_matrix_t *matrix, const reskia_paint_t *paint) {
    if (overdraw_canvas == nullptr || picture == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawPicture(reinterpret_cast<const SkPicture *>(picture), reinterpret_cast<const SkMatrix *>(matrix), reinterpret_cast<const SkPaint *>(paint));
}

void SkOverdrawCanvas_onDrawAnnotation(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const char key[], reskia_data_t *value) {
    if (overdraw_canvas == nullptr || rect == nullptr || key == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawAnnotation(* reinterpret_cast<const SkRect *>(rect), key, reinterpret_cast<SkData *>(value));
}

void SkOverdrawCanvas_onDrawShadowRec(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_path_t *path, const reskia_draw_shadow_rec_t *rec) {
    if (overdraw_canvas == nullptr || path == nullptr || rec == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawShadowRec(* reinterpret_cast<const SkPath *>(path), * reinterpret_cast<const SkDrawShadowRec *>(rec));
}

void SkOverdrawCanvas_onDrawEdgeAAQuad(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_point_t * point, reskia_overdraw_canvas_quad_aa_flags_t flags, const reskia_color_4f_t *color, reskia_overdraw_canvas_blend_mode_t mode) {
    if (overdraw_canvas == nullptr || rect == nullptr || point == nullptr || color == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawEdgeAAQuad(* reinterpret_cast<const SkRect *>(rect), reinterpret_cast<const SkPoint *>(point), static_cast<SkCanvas::QuadAAFlags>(flags), * reinterpret_cast<const SkColor4f *>(color), static_cast<SkBlendMode>(mode));
}

void SkOverdrawCanvas_onDrawEdgeAAImageSet2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_set_entry_t * entry, int count, const reskia_point_t * point, const reskia_matrix_t * matrix, const reskia_sampling_options_t *options, const reskia_paint_t *paint, reskia_overdraw_canvas_src_rect_constraint_t constraint) {
    if (overdraw_canvas == nullptr || count < 0 || (count > 0 && entry == nullptr) || options == nullptr) {
        return;
    }
    as_overdraw_canvas(overdraw_canvas)->onDrawEdgeAAImageSet2(reinterpret_cast<const SkOverdrawCanvas::ImageSetEntry *>(entry), count, reinterpret_cast<const SkPoint *>(point), reinterpret_cast<const SkMatrix *>(matrix), * reinterpret_cast<const SkSamplingOptions *>(options), reinterpret_cast<const SkPaint *>(paint), static_cast<SkOverdrawCanvas::SrcRectConstraint>(constraint));
}

}
