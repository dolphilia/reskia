#ifndef RAIA_SKIA_SK_SKSG_H
#define RAIA_SKIA_SK_SKSG_H

#include <stdbool.h>
#include <stddef.h>

#include "sk_color.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_r_rect_t reskia_r_rect_t;
typedef struct reskia_sksg_geometry_node_t reskia_sksg_geometry_node_t;
typedef struct reskia_sksg_image_filter_t reskia_sksg_image_filter_t;
typedef struct reskia_sksg_invalidation_controller_t reskia_sksg_invalidation_controller_t;
typedef struct reskia_sksg_paint_node_t reskia_sksg_paint_node_t;
typedef struct reskia_sksg_render_node_t reskia_sksg_render_node_t;
typedef struct reskia_sksg_scene_t reskia_sksg_scene_t;
typedef struct reskia_sksg_shader_t reskia_sksg_shader_t;
typedef struct reskia_sksg_transform_t reskia_sksg_transform_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_typeface_t reskia_typeface_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_sksg_scene_t *SkSG_Scene_MakeSimpleRect(float x, float y, float width, float height, reskia_color_t color);
reskia_sksg_scene_t *SkSG_Scene_Make(reskia_sksg_render_node_t *root);

reskia_sksg_render_node_t *SkSG_Group_Make(); // owned; release with SkSG_RenderNode_release
bool SkSG_Group_addChild(reskia_sksg_render_node_t *group, reskia_sksg_render_node_t *child);
bool SkSG_Group_removeChild(reskia_sksg_render_node_t *group, reskia_sksg_render_node_t *child);
size_t SkSG_Group_size(reskia_sksg_render_node_t *group); // NULL/non-group returns 0
bool SkSG_Group_empty(reskia_sksg_render_node_t *group); // NULL/non-group returns true
void SkSG_Group_clear(reskia_sksg_render_node_t *group); // NULL/non-group is no-op

reskia_sksg_geometry_node_t *SkSG_Rect_Make(); // owned; release with SkSG_GeometryNode_release
reskia_sksg_geometry_node_t *SkSG_Rect_MakeXYWH(float x, float y, float width, float height); // owned; invalid size returns NULL
reskia_sksg_geometry_node_t *SkSG_RRect_Make(); // owned; release with SkSG_GeometryNode_release
reskia_sksg_geometry_node_t *SkSG_RRect_MakeFromRRect(const reskia_r_rect_t *rrect); // owned; NULL input returns NULL
reskia_sksg_geometry_node_t *SkSG_Path_Make(); // owned; release with SkSG_GeometryNode_release
void SkSG_Path_setFillType(reskia_sksg_geometry_node_t *path, int fill_type); // NULL/non-path is no-op
reskia_sksg_geometry_node_t *SkSG_Plane_Make(); // owned; release with SkSG_GeometryNode_release
reskia_sksg_geometry_node_t *SkSG_TrimEffect_Make(reskia_sksg_geometry_node_t *child); // owned; invalid input returns NULL
reskia_sksg_geometry_node_t *SkSG_DashEffect_Make(reskia_sksg_geometry_node_t *child); // owned; invalid input returns NULL
reskia_sksg_geometry_node_t *SkSG_RoundEffect_Make(reskia_sksg_geometry_node_t *child); // owned; invalid input returns NULL
reskia_sksg_geometry_node_t *SkSG_OffsetEffect_Make(reskia_sksg_geometry_node_t *child); // owned; invalid input returns NULL
reskia_sksg_geometry_node_t *SkSG_GeometryTransform_Make(reskia_sksg_geometry_node_t *child, reskia_sksg_transform_t *transform); // owned; invalid input returns NULL
reskia_sksg_transform_t *SkSG_GeometryTransform_getTransform(reskia_sksg_geometry_node_t *geometry_transform); // owned; invalid input returns NULL
reskia_sksg_geometry_node_t *SkSG_Merge_Make(const reskia_sksg_geometry_node_t *const *geometry_nodes, const int *modes, int count); // owned; invalid input returns NULL
reskia_sksg_geometry_node_t *SkSG_Text_Make(reskia_typeface_t *typeface, const char *text); // owned; invalid text returns NULL
reskia_sksg_paint_node_t *SkSG_Color_Make(reskia_color_t color); // owned; release with SkSG_PaintNode_release
reskia_color_t SkSG_Color_getColor(reskia_sksg_paint_node_t *color); // NULL/non-color returns 0
void SkSG_Color_setColor(reskia_sksg_paint_node_t *color, reskia_color_t value); // NULL/non-color is no-op
reskia_sksg_paint_node_t *SkSG_ShaderPaint_Make(reskia_sksg_shader_t *shader); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_Draw_Make(reskia_sksg_geometry_node_t *geometry, reskia_sksg_paint_node_t *paint); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_OpacityEffect_Make(reskia_sksg_render_node_t *child, float opacity); // owned; invalid input returns NULL
float SkSG_OpacityEffect_getOpacity(reskia_sksg_render_node_t *effect); // NULL/non-opacity returns 0
void SkSG_OpacityEffect_setOpacity(reskia_sksg_render_node_t *effect, float opacity); // NULL/non-opacity is no-op
reskia_sksg_render_node_t *SkSG_ClipEffect_Make(reskia_sksg_render_node_t *child, reskia_sksg_geometry_node_t *clip, bool aa, bool force_clip); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_TransformEffect_Make(reskia_sksg_render_node_t *child, const reskia_matrix_t *matrix); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_TransformEffect_MakeWithMatrix(reskia_sksg_render_node_t *child, const reskia_matrix_t *matrix); // alias; owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_ShaderEffect_Make(reskia_sksg_render_node_t *child); // owned; invalid input returns NULL
bool SkSG_ShaderEffect_setShader(reskia_sksg_render_node_t *effect, reskia_sksg_shader_t *shader); // invalid input returns false
reskia_sksg_render_node_t *SkSG_MaskShaderEffect_Make(reskia_sksg_render_node_t *child); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_BlenderEffect_Make(reskia_sksg_render_node_t *child); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_LayerEffect_Make(reskia_sksg_render_node_t *child, int blend_mode); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_MaskEffect_Make(reskia_sksg_render_node_t *child, reskia_sksg_render_node_t *mask, int mode); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_ExternalColorFilter_Make(reskia_sksg_render_node_t *child); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_ModeColorFilter_Make(reskia_sksg_render_node_t *child, reskia_sksg_paint_node_t *color, int blend_mode); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_GradientColorFilter_Make(reskia_sksg_render_node_t *child, reskia_sksg_paint_node_t *color0, reskia_sksg_paint_node_t *color1); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_GradientColorFilter_MakeMany(reskia_sksg_render_node_t *child, reskia_sksg_paint_node_t *const *colors, int count); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_Image_Make(reskia_image_t *image); // owned; invalid input returns NULL
reskia_sksg_render_node_t *SkSG_ImageFilterEffect_Make(reskia_sksg_render_node_t *child, reskia_sksg_image_filter_t *filter); // owned; invalid input returns NULL

reskia_sksg_invalidation_controller_t *SkSG_InvalidationController_new(); // owned; delete with SkSG_InvalidationController_delete
void SkSG_InvalidationController_delete(reskia_sksg_invalidation_controller_t *controller); // NULL input is no-op
void SkSG_InvalidationController_inval(reskia_sksg_invalidation_controller_t *controller, float left, float top, float right, float bottom); // NULL input is no-op
reskia_rect_t *SkSG_InvalidationController_bounds(reskia_sksg_invalidation_controller_t *controller); // owned; NULL input returns NULL
size_t SkSG_InvalidationController_begin(reskia_sksg_invalidation_controller_t *controller); // NULL input returns 0
size_t SkSG_InvalidationController_end(reskia_sksg_invalidation_controller_t *controller); // NULL input returns 0
void SkSG_InvalidationController_reset(reskia_sksg_invalidation_controller_t *controller); // NULL input is no-op

reskia_sksg_shader_t *SkSG_LinearGradient_Make(); // owned; release with SkSG_Shader_release
reskia_sksg_shader_t *SkSG_RadialGradient_Make(); // owned; release with SkSG_Shader_release
void SkSG_Shader_release(reskia_sksg_shader_t *shader);
void SkSG_Shader_ref(reskia_sksg_shader_t *shader);
void SkSG_Shader_unref(reskia_sksg_shader_t *shader);
bool SkSG_Shader_getShader(reskia_sksg_shader_t *shader); // NULL input returns false

reskia_sksg_image_filter_t *SkSG_ExternalImageFilter_Make(); // owned; release with SkSG_ImageFilter_release
reskia_sksg_image_filter_t *SkSG_DropShadowImageFilter_Make(); // owned; release with SkSG_ImageFilter_release
reskia_sksg_image_filter_t *SkSG_BlurImageFilter_Make(); // owned; release with SkSG_ImageFilter_release
void SkSG_ImageFilter_release(reskia_sksg_image_filter_t *filter);
void SkSG_ImageFilter_ref(reskia_sksg_image_filter_t *filter);
void SkSG_ImageFilter_unref(reskia_sksg_image_filter_t *filter);
bool SkSG_ImageFilter_getFilter(reskia_sksg_image_filter_t *filter); // NULL input returns false

reskia_sksg_transform_t *SkSG_Transform_MakeFromMatrix(const reskia_matrix_t *matrix); // owned; invalid input returns NULL
reskia_sksg_transform_t *SkSG_Transform_MakeConcat(reskia_sksg_transform_t *a, reskia_sksg_transform_t *b); // owned; invalid input returns NULL
reskia_sksg_transform_t *SkSG_Transform_MakeInverse(reskia_sksg_transform_t *transform); // owned; invalid input returns NULL
void SkSG_Transform_release(reskia_sksg_transform_t *transform);
void SkSG_Transform_ref(reskia_sksg_transform_t *transform);
void SkSG_Transform_unref(reskia_sksg_transform_t *transform);

void SkSG_GeometryNode_release(reskia_sksg_geometry_node_t *node);
void SkSG_GeometryNode_ref(reskia_sksg_geometry_node_t *node);
void SkSG_GeometryNode_unref(reskia_sksg_geometry_node_t *node);
bool SkSG_GeometryNode_contains(reskia_sksg_geometry_node_t *node, float x, float y); // NULL input returns false
void SkSG_GeometryNode_clip(reskia_sksg_geometry_node_t *node, reskia_canvas_t *canvas, bool anti_alias); // NULL input is no-op
void SkSG_GeometryNode_draw(reskia_sksg_geometry_node_t *node, reskia_canvas_t *canvas, const reskia_paint_t *paint); // NULL input is no-op
reskia_path_t *SkSG_GeometryNode_asPath(reskia_sksg_geometry_node_t *node); // owned; NULL input returns NULL

void SkSG_PaintNode_release(reskia_sksg_paint_node_t *node);
void SkSG_PaintNode_ref(reskia_sksg_paint_node_t *node);
void SkSG_PaintNode_unref(reskia_sksg_paint_node_t *node);
reskia_paint_t *SkSG_PaintNode_makePaint(reskia_sksg_paint_node_t *node); // owned; NULL input returns NULL

reskia_sksg_render_node_t *SkSG_RenderNode_MakeSimpleRect(float x, float y, float width, float height, reskia_color_t color);
void SkSG_RenderNode_release(reskia_sksg_render_node_t *node);
void SkSG_RenderNode_ref(reskia_sksg_render_node_t *node);
void SkSG_RenderNode_unref(reskia_sksg_render_node_t *node);
bool SkSG_RenderNode_render(reskia_sksg_render_node_t *node, reskia_canvas_t *canvas);
bool SkSG_RenderNode_nodeAt(reskia_sksg_render_node_t *node, float x, float y);
bool SkSG_RenderNode_isVisible(reskia_sksg_render_node_t *node); // NULL input returns false
void SkSG_RenderNode_setVisible(reskia_sksg_render_node_t *node, bool visible); // NULL input is no-op
reskia_sksg_transform_t *SkSG_TransformEffect_getTransform(reskia_sksg_render_node_t *effect); // owned; invalid input returns NULL

void SkSG_Node_invalidate(reskia_sksg_render_node_t *node, bool damage); // NULL input is no-op
bool SkSG_Node_revalidate(reskia_sksg_render_node_t *node); // NULL input returns false

void SkSG_Scene_release(reskia_sksg_scene_t *scene);
void SkSG_Scene_ref(reskia_sksg_scene_t *scene);
void SkSG_Scene_unref(reskia_sksg_scene_t *scene);

bool SkSG_Scene_revalidate(reskia_sksg_scene_t *scene);
bool SkSG_Scene_render(reskia_sksg_scene_t *scene, reskia_canvas_t *canvas);
bool SkSG_Scene_nodeAt(reskia_sksg_scene_t *scene, float x, float y); // NULL input returns false

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SKSG_H
