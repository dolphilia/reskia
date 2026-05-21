#include <cstdio>

#include "capi/sk_canvas.h"
#include "capi/sk_graphics.h"
#include "capi/sk_matrix.h"
#include "capi/sk_paint.h"
#include "capi/sk_path.h"
#include "capi/sk_rect.h"
#include "capi/sk_r_rect.h"
#include "capi/sk_sksg.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[sksg-capi-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_sksg_capi_minimal() {
    SkSG_RenderNode_ref(nullptr);
    SkSG_RenderNode_unref(nullptr);
    SkSG_RenderNode_release(nullptr);
    SkSG_RenderNode_setVisible(nullptr, true);
    SkSG_Node_invalidate(nullptr, true);
    SkSG_Group_clear(nullptr);
    SkSG_GeometryNode_ref(nullptr);
    SkSG_GeometryNode_unref(nullptr);
    SkSG_GeometryNode_release(nullptr);
    SkSG_PaintNode_ref(nullptr);
    SkSG_PaintNode_unref(nullptr);
    SkSG_PaintNode_release(nullptr);
    SkSG_InvalidationController_delete(nullptr);
    SkSG_InvalidationController_inval(nullptr, 0.0f, 0.0f, 1.0f, 1.0f);
    SkSG_InvalidationController_reset(nullptr);
    SkSG_GeometryNode_clip(nullptr, nullptr, false);
    SkSG_GeometryNode_draw(nullptr, nullptr, nullptr);
    if (!check(SkSG_RenderNode_MakeSimpleRect(0.0f, 0.0f, 0.0f, 8.0f, 0xFF000000u) == nullptr &&
               SkSG_Group_addChild(nullptr, nullptr) == false &&
               SkSG_Group_removeChild(nullptr, nullptr) == false &&
               SkSG_Group_size(nullptr) == 0 &&
               SkSG_Group_empty(nullptr) &&
               SkSG_RenderNode_render(nullptr, nullptr) == false &&
               SkSG_RenderNode_nodeAt(nullptr, 0.0f, 0.0f) == false &&
               SkSG_RenderNode_isVisible(nullptr) == false &&
               SkSG_Rect_MakeXYWH(0.0f, 0.0f, -1.0f, 1.0f) == nullptr &&
               SkSG_Draw_Make(nullptr, nullptr) == nullptr &&
               SkSG_OpacityEffect_Make(nullptr, 1.0f) == nullptr &&
               SkSG_OpacityEffect_getOpacity(nullptr) == 0.0f &&
               SkSG_ClipEffect_Make(nullptr, nullptr, false, false) == nullptr &&
               SkSG_TransformEffect_Make(nullptr, nullptr) == nullptr &&
               SkSG_TransformEffect_MakeWithMatrix(nullptr, nullptr) == nullptr &&
               SkSG_TransformEffect_getTransform(nullptr) == nullptr &&
               SkSG_ShaderEffect_Make(nullptr) == nullptr &&
               SkSG_MaskShaderEffect_Make(nullptr) == nullptr &&
               SkSG_BlenderEffect_Make(nullptr) == nullptr &&
               SkSG_LayerEffect_Make(nullptr, 0) == nullptr &&
               SkSG_MaskEffect_Make(nullptr, nullptr, 0) == nullptr &&
               SkSG_ExternalColorFilter_Make(nullptr) == nullptr &&
               SkSG_ModeColorFilter_Make(nullptr, nullptr, 0) == nullptr &&
               SkSG_GradientColorFilter_Make(nullptr, nullptr, nullptr) == nullptr &&
               SkSG_GradientColorFilter_MakeMany(nullptr, nullptr, 0) == nullptr &&
               SkSG_Image_Make(nullptr) == nullptr &&
               SkSG_ImageFilterEffect_Make(nullptr, nullptr) == nullptr &&
               SkSG_TrimEffect_Make(nullptr) == nullptr &&
               SkSG_DashEffect_Make(nullptr) == nullptr &&
               SkSG_RoundEffect_Make(nullptr) == nullptr &&
               SkSG_OffsetEffect_Make(nullptr) == nullptr &&
               SkSG_GeometryTransform_Make(nullptr, nullptr) == nullptr &&
               SkSG_GeometryTransform_getTransform(nullptr) == nullptr &&
               SkSG_Merge_Make(nullptr, nullptr, -1) == nullptr &&
               SkSG_Text_Make(nullptr, nullptr) == nullptr &&
               SkSG_ShaderPaint_Make(nullptr) == nullptr &&
               SkSG_GeometryNode_contains(nullptr, 0.0f, 0.0f) == false &&
               SkSG_Color_getColor(nullptr) == 0 &&
               SkSG_PaintNode_makePaint(nullptr) == nullptr &&
               SkSG_RRect_MakeFromRRect(nullptr) == nullptr &&
               SkSG_GeometryNode_asPath(nullptr) == nullptr &&
               SkSG_InvalidationController_bounds(nullptr) == nullptr &&
               SkSG_InvalidationController_begin(nullptr) == 0 &&
               SkSG_InvalidationController_end(nullptr) == 0 &&
               SkSG_Shader_getShader(nullptr) == false &&
               SkSG_ImageFilter_getFilter(nullptr) == false &&
               SkSG_Transform_MakeFromMatrix(nullptr) == nullptr &&
               SkSG_Transform_MakeConcat(nullptr, nullptr) == nullptr &&
               SkSG_Transform_MakeInverse(nullptr) == nullptr &&
               SkSG_ShaderEffect_setShader(nullptr, nullptr) == false &&
               SkSG_Node_revalidate(nullptr) == false &&
               !SkSG_Scene_nodeAt(nullptr, 0.0f, 0.0f) &&
               SkSG_Scene_Make(nullptr) == nullptr,
               "SkSG null/invalid helpers")) {
        return false;
    }
    SkSG_Shader_release(nullptr);
    SkSG_Shader_ref(nullptr);
    SkSG_Shader_unref(nullptr);
    SkSG_ImageFilter_release(nullptr);
    SkSG_ImageFilter_ref(nullptr);
    SkSG_ImageFilter_unref(nullptr);
    SkSG_Transform_release(nullptr);
    SkSG_Transform_ref(nullptr);
    SkSG_Transform_unref(nullptr);

    reskia_sksg_scene_t* scene = SkSG_Scene_MakeSimpleRect(8.0f, 8.0f, 48.0f, 48.0f, 0xFFFF0000u);
    if (!check(scene != nullptr, "SkSG_Scene_MakeSimpleRect")) {
        return false;
    }

    reskia_canvas_t* canvas = SkCanvas_newWithSizeProps(64, 64, nullptr);
    if (!check(canvas != nullptr, "SkCanvas_newWithSizeProps")) {
        SkSG_Scene_release(scene);
        return false;
    }

    if (!check(SkSG_Scene_revalidate(scene), "SkSG_Scene_revalidate")) {
        SkCanvas_delete(canvas);
        SkSG_Scene_release(scene);
        return false;
    }
    if (!check(SkSG_Scene_render(scene, canvas), "SkSG_Scene_render")) {
        SkCanvas_delete(canvas);
        SkSG_Scene_release(scene);
        return false;
    }
    if (!check(SkSG_Scene_nodeAt(scene, 16.0f, 16.0f),
               "SkSG_Scene_nodeAt")) {
        SkCanvas_delete(canvas);
        SkSG_Scene_release(scene);
        return false;
    }
    if (!check(SkSG_RenderNode_render(nullptr, canvas) == false, "SkSG_RenderNode_render null node")) {
        SkCanvas_delete(canvas);
        SkSG_Scene_release(scene);
        return false;
    }

    SkCanvas_delete(canvas);
    SkSG_Scene_release(scene);

    reskia_sksg_render_node_t* root = SkSG_RenderNode_MakeSimpleRect(4.0f, 4.0f, 24.0f, 24.0f, 0xFF00FF00u);
    if (!check(root != nullptr, "SkSG_RenderNode_MakeSimpleRect")) {
        return false;
    }
    SkSG_RenderNode_ref(root);
    SkSG_RenderNode_unref(root);
    if (!check(SkSG_RenderNode_isVisible(root), "SkSG_RenderNode_isVisible default")) {
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_RenderNode_setVisible(root, false);
    if (!check(!SkSG_RenderNode_isVisible(root), "SkSG_RenderNode_setVisible false")) {
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_RenderNode_setVisible(root, true);
    SkSG_Node_invalidate(root, true);
    if (!check(SkSG_Node_revalidate(root), "SkSG_Node_revalidate")) {
        SkSG_RenderNode_release(root);
        return false;
    }

    reskia_sksg_render_node_t* group = SkSG_Group_Make();
    if (!check(group != nullptr && SkSG_Group_empty(group) && SkSG_Group_size(group) == 0,
               "SkSG_Group_Make")) {
        SkSG_RenderNode_release(root);
        return false;
    }
    if (!check(SkSG_Group_addChild(group, root) &&
               SkSG_Group_size(group) == 1 &&
               !SkSG_Group_empty(group),
               "SkSG_Group_addChild")) {
        SkSG_RenderNode_release(group);
        SkSG_RenderNode_release(root);
        return false;
    }
    if (!check(SkSG_Group_removeChild(group, root) &&
               SkSG_Group_empty(group),
               "SkSG_Group_removeChild")) {
        SkSG_RenderNode_release(group);
        SkSG_RenderNode_release(root);
        return false;
    }
    if (!check(SkSG_Group_addChild(group, root), "SkSG_Group_addChild again")) {
        SkSG_RenderNode_release(group);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_Group_clear(group);
    if (!check(SkSG_Group_empty(group), "SkSG_Group_clear")) {
        SkSG_RenderNode_release(group);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_RenderNode_release(group);

    reskia_sksg_invalidation_controller_t* inval = SkSG_InvalidationController_new();
    if (!check(inval != nullptr, "SkSG_InvalidationController_new")) {
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_InvalidationController_inval(inval, 1.0f, 2.0f, 5.0f, 8.0f);
    if (!check(SkSG_InvalidationController_begin(inval) == 0 &&
               SkSG_InvalidationController_end(inval) == 1,
               "SkSG_InvalidationController iteration")) {
        SkSG_InvalidationController_delete(inval);
        SkSG_RenderNode_release(root);
        return false;
    }
    reskia_rect_t* inval_bounds = SkSG_InvalidationController_bounds(inval);
    if (!check(inval_bounds != nullptr &&
               SkRect_left(inval_bounds) == 1.0f &&
               SkRect_top(inval_bounds) == 2.0f &&
               SkRect_right(inval_bounds) == 5.0f &&
               SkRect_bottom(inval_bounds) == 8.0f,
               "SkSG_InvalidationController_bounds")) {
        SkRect_delete(inval_bounds);
        SkSG_InvalidationController_delete(inval);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkRect_delete(inval_bounds);
    SkSG_InvalidationController_reset(inval);
    SkSG_InvalidationController_delete(inval);

    reskia_sksg_geometry_node_t* rect = SkSG_Rect_MakeXYWH(2.0f, 2.0f, 12.0f, 12.0f);
    reskia_sksg_paint_node_t* color = SkSG_Color_Make(0xFF0000FFu);
    if (!check(rect != nullptr && color != nullptr, "SkSG_Rect/Color_Make")) {
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    if (!check(SkSG_GeometryNode_contains(rect, 4.0f, 4.0f) &&
               !SkSG_GeometryNode_contains(rect, 32.0f, 32.0f),
               "SkSG_GeometryNode_contains")) {
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    if (!check(SkSG_Color_getColor(color) == 0xFF0000FFu, "SkSG_Color_getColor")) {
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_Color_setColor(color, 0xFFFFFF00u);
    reskia_paint_t* materialized_paint = SkSG_PaintNode_makePaint(color);
    if (!check(materialized_paint != nullptr &&
               SkPaint_getColor(materialized_paint) == 0xFFFFFF00u,
               "SkSG_PaintNode_makePaint")) {
        SkPaint_delete(materialized_paint);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    reskia_canvas_t* geometry_canvas = SkCanvas_newWithSizeProps(32, 32, nullptr);
    if (!check(geometry_canvas != nullptr, "SkCanvas_newWithSizeProps geometry")) {
        SkPaint_delete(materialized_paint);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_GeometryNode_clip(rect, geometry_canvas, true);
    SkSG_GeometryNode_draw(rect, geometry_canvas, materialized_paint);
    SkCanvas_delete(geometry_canvas);
    SkPaint_delete(materialized_paint);

    reskia_path_t* rect_path = SkSG_GeometryNode_asPath(rect);
    if (!check(rect_path != nullptr && !SkPath_isEmpty(rect_path),
               "SkSG_GeometryNode_asPath")) {
        SkPath_delete(rect_path);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkPath_delete(rect_path);

    reskia_sksg_geometry_node_t* default_rrect = SkSG_RRect_Make();
    reskia_r_rect_t* source_rrect = SkRRect_new();
    reskia_sksg_geometry_node_t* copied_rrect = SkSG_RRect_MakeFromRRect(source_rrect);
    if (!check(default_rrect != nullptr && copied_rrect != nullptr,
               "SkSG_RRect_Make")) {
        SkSG_GeometryNode_release(copied_rrect);
        SkRRect_delete(source_rrect);
        SkSG_GeometryNode_release(default_rrect);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_GeometryNode_release(copied_rrect);
    SkRRect_delete(source_rrect);
    SkSG_GeometryNode_release(default_rrect);

    reskia_sksg_render_node_t* draw = SkSG_Draw_Make(rect, color);
    if (!check(draw != nullptr, "SkSG_Draw_Make")) {
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }

    reskia_sksg_render_node_t* opacity = SkSG_OpacityEffect_Make(draw, 0.5f);
    if (!check(opacity != nullptr &&
               SkSG_OpacityEffect_getOpacity(opacity) == 0.5f,
               "SkSG_OpacityEffect_Make")) {
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_OpacityEffect_setOpacity(opacity, 0.75f);
    if (!check(SkSG_OpacityEffect_getOpacity(opacity) == 0.75f,
               "SkSG_OpacityEffect_setOpacity")) {
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }

    reskia_sksg_geometry_node_t* path = SkSG_Path_Make();
    reskia_sksg_geometry_node_t* plane = SkSG_Plane_Make();
    if (!check(path != nullptr && plane != nullptr, "SkSG_Path/Plane_Make")) {
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_Path_setFillType(path, 1);
    reskia_sksg_geometry_node_t* trim = SkSG_TrimEffect_Make(path);
    reskia_sksg_geometry_node_t* dash = SkSG_DashEffect_Make(path);
    reskia_sksg_geometry_node_t* round = SkSG_RoundEffect_Make(path);
    reskia_sksg_geometry_node_t* offset = SkSG_OffsetEffect_Make(path);
    if (!check(trim != nullptr && dash != nullptr && round != nullptr && offset != nullptr,
               "SkSG geometry effects")) {
        SkSG_GeometryNode_release(offset);
        SkSG_GeometryNode_release(round);
        SkSG_GeometryNode_release(dash);
        SkSG_GeometryNode_release(trim);
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_GeometryNode_release(offset);
    SkSG_GeometryNode_release(round);
    SkSG_GeometryNode_release(dash);
    SkSG_GeometryNode_release(trim);

    sk_matrix_t identity_handle = SkMatrix_I();
    const reskia_matrix_t* identity_matrix =
            reinterpret_cast<const reskia_matrix_t*>(static_sk_matrix_get_ptr(identity_handle));
    reskia_sksg_transform_t* transform = SkSG_Transform_MakeFromMatrix(identity_matrix);
    reskia_sksg_transform_t* transform_b = SkSG_Transform_MakeFromMatrix(identity_matrix);
    reskia_sksg_transform_t* concat_transform = SkSG_Transform_MakeConcat(transform, transform_b);
    reskia_sksg_transform_t* inverse_transform = SkSG_Transform_MakeInverse(transform);
    reskia_sksg_geometry_node_t* geometry_transform = SkSG_GeometryTransform_Make(rect, transform);
    reskia_sksg_transform_t* geometry_transform_value = SkSG_GeometryTransform_getTransform(geometry_transform);
    reskia_sksg_render_node_t* transform_effect = SkSG_TransformEffect_Make(opacity, identity_matrix);
    reskia_sksg_transform_t* render_transform_value = SkSG_TransformEffect_getTransform(transform_effect);
    if (!check(transform != nullptr &&
               concat_transform != nullptr &&
               transform_b != nullptr &&
               inverse_transform != nullptr &&
               geometry_transform != nullptr &&
               geometry_transform_value != nullptr &&
               transform_effect != nullptr &&
               render_transform_value != nullptr,
               "SkSG transform wrappers")) {
        SkSG_Transform_release(render_transform_value);
        SkSG_RenderNode_release(transform_effect);
        SkSG_Transform_release(geometry_transform_value);
        SkSG_GeometryNode_release(geometry_transform);
        SkSG_Transform_release(inverse_transform);
        SkSG_Transform_release(concat_transform);
        SkSG_Transform_release(transform_b);
        SkSG_Transform_release(transform);
        static_sk_matrix_delete(identity_handle);
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_Transform_release(render_transform_value);
    SkSG_RenderNode_release(transform_effect);
    SkSG_Transform_release(geometry_transform_value);
    SkSG_GeometryNode_release(geometry_transform);
    SkSG_Transform_ref(transform);
    SkSG_Transform_unref(transform);
    SkSG_Transform_release(inverse_transform);
    SkSG_Transform_release(concat_transform);
    SkSG_Transform_release(transform_b);
    SkSG_Transform_release(transform);
    static_sk_matrix_delete(identity_handle);

    reskia_sksg_shader_t* linear = SkSG_LinearGradient_Make();
    reskia_sksg_shader_t* radial = SkSG_RadialGradient_Make();
    reskia_sksg_paint_node_t* shader_paint = SkSG_ShaderPaint_Make(linear);
    if (!check(linear != nullptr && radial != nullptr && shader_paint != nullptr,
               "SkSG shader wrappers")) {
        SkSG_PaintNode_release(shader_paint);
        SkSG_Shader_release(radial);
        SkSG_Shader_release(linear);
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_Shader_ref(linear);
    SkSG_Shader_unref(linear);
    (void)SkSG_Shader_getShader(linear);
    SkSG_PaintNode_release(shader_paint);
    SkSG_Shader_release(radial);
    SkSG_Shader_release(linear);

    reskia_sksg_image_filter_t* external_filter = SkSG_ExternalImageFilter_Make();
    reskia_sksg_image_filter_t* drop_shadow_filter = SkSG_DropShadowImageFilter_Make();
    reskia_sksg_image_filter_t* blur_filter = SkSG_BlurImageFilter_Make();
    reskia_sksg_render_node_t* image_filter_effect = SkSG_ImageFilterEffect_Make(opacity, blur_filter);
    if (!check(external_filter != nullptr &&
               drop_shadow_filter != nullptr &&
               blur_filter != nullptr &&
               image_filter_effect != nullptr,
               "SkSG image filter wrappers")) {
        SkSG_RenderNode_release(image_filter_effect);
        SkSG_ImageFilter_release(blur_filter);
        SkSG_ImageFilter_release(drop_shadow_filter);
        SkSG_ImageFilter_release(external_filter);
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_ImageFilter_ref(blur_filter);
    SkSG_ImageFilter_unref(blur_filter);
    (void)SkSG_ImageFilter_getFilter(drop_shadow_filter);
    (void)SkSG_ImageFilter_getFilter(blur_filter);
    SkSG_RenderNode_release(image_filter_effect);
    SkSG_ImageFilter_release(blur_filter);
    SkSG_ImageFilter_release(drop_shadow_filter);
    SkSG_ImageFilter_release(external_filter);

    reskia_sksg_geometry_node_t* merge_nodes[] = {rect, plane};
    int merge_modes[] = {0, 1};
    reskia_sksg_geometry_node_t* merge = SkSG_Merge_Make(merge_nodes, merge_modes, 2);
    reskia_sksg_geometry_node_t* text = SkSG_Text_Make(nullptr, "reskia");
    reskia_sksg_render_node_t* external_color_filter = SkSG_ExternalColorFilter_Make(opacity);
    reskia_sksg_render_node_t* mode_color_filter = SkSG_ModeColorFilter_Make(opacity, color, 0);
    reskia_sksg_paint_node_t* color1 = SkSG_Color_Make(0xFFFF0000u);
    reskia_sksg_paint_node_t* colors[] = {color, color1};
    reskia_sksg_render_node_t* gradient_color_filter = SkSG_GradientColorFilter_Make(opacity, color, color1);
    reskia_sksg_render_node_t* gradient_color_filter_many = SkSG_GradientColorFilter_MakeMany(opacity, colors, 2);
    if (!check(merge != nullptr &&
               text != nullptr &&
               external_color_filter != nullptr &&
               mode_color_filter != nullptr &&
               color1 != nullptr &&
               gradient_color_filter != nullptr &&
               gradient_color_filter_many != nullptr,
               "SkSG merge/text/color filter wrappers")) {
        SkSG_RenderNode_release(gradient_color_filter_many);
        SkSG_RenderNode_release(gradient_color_filter);
        SkSG_PaintNode_release(color1);
        SkSG_RenderNode_release(mode_color_filter);
        SkSG_RenderNode_release(external_color_filter);
        SkSG_GeometryNode_release(text);
        SkSG_GeometryNode_release(merge);
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_RenderNode_release(gradient_color_filter_many);
    SkSG_RenderNode_release(gradient_color_filter);
    SkSG_PaintNode_release(color1);
    SkSG_RenderNode_release(mode_color_filter);
    SkSG_RenderNode_release(external_color_filter);
    SkSG_GeometryNode_release(text);
    SkSG_GeometryNode_release(merge);

    if (!check(SkSG_GeometryNode_contains(plane, 1000.0f, 1000.0f),
               "SkSG_Plane_contains")) {
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }

    reskia_sksg_render_node_t* clipped = SkSG_ClipEffect_Make(opacity, rect, true, false);
    if (!check(clipped != nullptr, "SkSG_ClipEffect_Make")) {
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    reskia_sksg_render_node_t* shader_effect = SkSG_ShaderEffect_Make(opacity);
    reskia_sksg_render_node_t* mask_shader_effect = SkSG_MaskShaderEffect_Make(opacity);
    reskia_sksg_render_node_t* blender_effect = SkSG_BlenderEffect_Make(opacity);
    reskia_sksg_render_node_t* layer_effect = SkSG_LayerEffect_Make(opacity, 3);
    reskia_sksg_render_node_t* mask_effect = SkSG_MaskEffect_Make(opacity, root, 0);
    if (!check(shader_effect != nullptr &&
               mask_shader_effect != nullptr &&
               blender_effect != nullptr &&
               layer_effect != nullptr &&
               mask_effect != nullptr,
               "SkSG render effects")) {
        SkSG_RenderNode_release(mask_effect);
        SkSG_RenderNode_release(layer_effect);
        SkSG_RenderNode_release(blender_effect);
        SkSG_RenderNode_release(mask_shader_effect);
        SkSG_RenderNode_release(shader_effect);
        SkSG_RenderNode_release(clipped);
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    reskia_sksg_shader_t* effect_shader = SkSG_LinearGradient_Make();
    if (!check(effect_shader != nullptr &&
               SkSG_ShaderEffect_setShader(shader_effect, effect_shader),
               "SkSG_ShaderEffect_setShader")) {
        SkSG_Shader_release(effect_shader);
        SkSG_RenderNode_release(mask_effect);
        SkSG_RenderNode_release(layer_effect);
        SkSG_RenderNode_release(blender_effect);
        SkSG_RenderNode_release(mask_shader_effect);
        SkSG_RenderNode_release(shader_effect);
        SkSG_RenderNode_release(clipped);
        SkSG_GeometryNode_release(plane);
        SkSG_GeometryNode_release(path);
        SkSG_RenderNode_release(opacity);
        SkSG_RenderNode_release(draw);
        SkSG_GeometryNode_release(rect);
        SkSG_PaintNode_release(color);
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_Shader_release(effect_shader);
    SkSG_RenderNode_release(mask_effect);
    SkSG_RenderNode_release(layer_effect);
    SkSG_RenderNode_release(blender_effect);
    SkSG_RenderNode_release(mask_shader_effect);
    SkSG_RenderNode_release(shader_effect);
    SkSG_RenderNode_release(clipped);
    SkSG_GeometryNode_release(plane);
    SkSG_GeometryNode_release(path);
    SkSG_RenderNode_release(opacity);
    SkSG_RenderNode_release(draw);
    SkSG_GeometryNode_release(rect);
    SkSG_PaintNode_release(color);

    reskia_sksg_scene_t* generic_scene = SkSG_Scene_Make(root);
    if (!check(generic_scene != nullptr, "SkSG_Scene_Make")) {
        SkSG_RenderNode_release(root);
        return false;
    }
    SkSG_Scene_release(generic_scene);
    SkSG_RenderNode_release(root);
    return true;
}

}  // namespace

int main() {
    SkGraphics_Init();

    if (!smoke_sksg_capi_minimal()) {
        return 1;
    }

    std::fprintf(stdout, "[sksg-capi-smoke] PASS\n");
    return 0;
}
