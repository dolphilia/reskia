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
typedef int32_t reskia_overdraw_canvas_blend_mode_t;
typedef int32_t reskia_overdraw_canvas_point_mode_t;
typedef int32_t reskia_overdraw_canvas_src_rect_constraint_t;
typedef int32_t reskia_overdraw_canvas_filter_mode_t;
typedef int32_t reskia_overdraw_canvas_quad_aa_flags_t;
typedef struct reskia_canvas_t reskia_canvas_t;

reskia_overdraw_canvas_t *SkOverdrawCanvas_new(reskia_canvas_t *canvas); // canvas は非 NULL。invalid 入力では NULL
void SkOverdrawCanvas_delete(reskia_overdraw_canvas_t *overdraw_canvas); // NULL 入力では no-op
/**
 * blob/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawTextBlob(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_text_blob_t *blob, float scalar1, float scalar2, const reskia_paint_t *paint);
/**
 * glyphRunList/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawGlyphRunList(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_glyph_run_list_t *glyphRunList, const reskia_paint_t *paint);
/**
 * point1[12]/paint は非 NULL。color[4]/point2[4] は NULL 許可。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawPatch(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_point_t * point1, const reskia_color_t * color, const reskia_point_t * point2, reskia_overdraw_canvas_blend_mode_t mode, const reskia_paint_t *paint);
void SkOverdrawCanvas_onDrawPaint(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_paint_t *paint); // paint は非 NULL。invalid 入力では no-op
void SkOverdrawCanvas_onDrawBehind(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_paint_t *paint); // paint は非 NULL。invalid 入力では no-op
/**
 * rect/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_paint_t *paint);
/**
 * region/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawRegion(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_region_t *region, const reskia_paint_t *paint);
/**
 * rect/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawOval(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_paint_t *paint);
/**
 * rect/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawArc(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, float scalar1, float scalar2, bool v, const reskia_paint_t *paint);
/**
 * rect1/rect2/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawDRRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_r_rect_t *rect1, const reskia_r_rect_t *rect2, const reskia_paint_t *paint);
/**
 * rect/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawRRect(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_r_rect_t *rect, const reskia_paint_t *paint);
/**
 * size > 0 では point 非 NULL。paint 非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawPoints(reskia_overdraw_canvas_t *overdraw_canvas, reskia_overdraw_canvas_point_mode_t mode, size_t size, const reskia_point_t * point, const reskia_paint_t *paint);
/**
 * vertices/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawVerticesObject(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_vertices_t *vertices, reskia_overdraw_canvas_blend_mode_t mode, const reskia_paint_t *paint);
/**
 * path/paint は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawPath(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_path_t *path, const reskia_paint_t *paint);
/**
 * image/options は非 NULL。paint は NULL 許可。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawImage2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, float scalar1, float scalar2, const reskia_sampling_options_t *options, const reskia_paint_t *paint);
/**
 * image/rect1/rect2/options は非 NULL。paint は NULL 許可。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawImageRect2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, const reskia_rect_t *rect1, const reskia_rect_t *rect2, const reskia_sampling_options_t *options, const reskia_paint_t *paint, reskia_overdraw_canvas_src_rect_constraint_t constraint);
/**
 * image/lattice/rect は非 NULL。paint は NULL 許可。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawImageLattice2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t *image, const reskia_lattice_t *lattice, const reskia_rect_t *rect, reskia_overdraw_canvas_filter_mode_t mode, const reskia_paint_t *paint);
/**
 * v > 0 では form/rect1 は v 要素以上、非 NULL。color/rect2/paint は NULL 許可。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawAtlas2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_t * image, const reskia_rsxform_t * form, const reskia_rect_t * rect1, const reskia_color_t * color, int v, reskia_overdraw_canvas_blend_mode_t mode, const reskia_sampling_options_t *options, const reskia_rect_t *rect2, const reskia_paint_t *paint);
/**
 * drawable は非 NULL、matrix は NULL 許可。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawDrawable(reskia_overdraw_canvas_t *overdraw_canvas, reskia_drawable_t *drawable, const reskia_matrix_t *matrix);
/**
 * picture は非 NULL、matrix/paint は NULL 許可。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawPicture(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_picture_t *picture, const reskia_matrix_t *matrix, const reskia_paint_t *paint);
/**
 * rect/key は非 NULL、value は NULL 許可。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawAnnotation(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const char key[], reskia_data_t *value);
/**
 * path/rec は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawShadowRec(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_path_t *path, const reskia_draw_shadow_rec_t *rec);
/**
 * rect/point[4]/color は非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawEdgeAAQuad(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_rect_t *rect, const reskia_point_t * point, reskia_overdraw_canvas_quad_aa_flags_t flags, const reskia_color_4f_t *color, reskia_overdraw_canvas_blend_mode_t mode);
/**
 * count > 0 では entry 非 NULL。point/matrix/paint は NULL 許可。options 非 NULL。invalid 入力では no-op
 */
void SkOverdrawCanvas_onDrawEdgeAAImageSet2(reskia_overdraw_canvas_t *overdraw_canvas, const reskia_image_set_entry_t * entry, int count, const reskia_point_t * point, const reskia_matrix_t * matrix, const reskia_sampling_options_t *options, const reskia_paint_t *paint, reskia_overdraw_canvas_src_rect_constraint_t constraint);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_OVERDRAW_CANVAS_H
