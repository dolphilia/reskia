#include "sk_sksg.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkImage.h"
#include "include/core/SkMatrix.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkPoint.h"
#include "include/core/SkRect.h"
#include "include/core/SkRefCnt.h"
#include "include/core/SkRRect.h"
#include "include/core/SkTypeface.h"
#include "modules/sksg/include/SkSGColorFilter.h"
#include "modules/sksg/include/SkSGDraw.h"
#include "modules/sksg/include/SkSGClipEffect.h"
#include "modules/sksg/include/SkSGGradient.h"
#include "modules/sksg/include/SkSGGroup.h"
#include "modules/sksg/include/SkSGGeometryEffect.h"
#include "modules/sksg/include/SkSGImage.h"
#include "modules/sksg/include/SkSGInvalidationController.h"
#include "modules/sksg/include/SkSGMaskEffect.h"
#include "modules/sksg/include/SkSGMerge.h"
#include "modules/sksg/include/SkSGOpacityEffect.h"
#include "modules/sksg/include/SkSGPaint.h"
#include "modules/sksg/include/SkSGPath.h"
#include "modules/sksg/include/SkSGPlane.h"
#include "modules/sksg/include/SkSGRect.h"
#include "modules/sksg/include/SkSGRenderEffect.h"
#include "modules/sksg/include/SkSGScene.h"
#include "modules/sksg/include/SkSGText.h"
#include "modules/sksg/include/SkSGTransform.h"

#include <iterator>
#include <memory>
#include <utility>
#include <vector>

namespace {

class ReskiaSkSGScene final : public SkRefCnt {
public:
    explicit ReskiaSkSGScene(std::unique_ptr<sksg::Scene> scene_in)
            : scene(std::move(scene_in)) {}

    std::unique_ptr<sksg::Scene> scene;
};

class ReskiaSkSGRenderNode final : public SkRefCnt {
public:
    explicit ReskiaSkSGRenderNode(sk_sp<sksg::RenderNode> node_in)
            : node(std::move(node_in)) {}

    explicit ReskiaSkSGRenderNode(sk_sp<sksg::Group> group_in)
            : node(group_in)
            , group(std::move(group_in)) {}

    explicit ReskiaSkSGRenderNode(sk_sp<sksg::OpacityEffect> opacity_effect_in)
            : node(opacity_effect_in)
            , opacity_effect(std::move(opacity_effect_in)) {}

    explicit ReskiaSkSGRenderNode(sk_sp<sksg::TransformEffect> transform_effect_in)
            : node(transform_effect_in)
            , transform_effect(std::move(transform_effect_in)) {}

    explicit ReskiaSkSGRenderNode(sk_sp<sksg::ShaderEffect> shader_effect_in)
            : node(shader_effect_in)
            , shader_effect(std::move(shader_effect_in)) {}

    sk_sp<sksg::RenderNode> node;
    sk_sp<sksg::Group> group;
    sk_sp<sksg::OpacityEffect> opacity_effect;
    sk_sp<sksg::TransformEffect> transform_effect;
    sk_sp<sksg::ShaderEffect> shader_effect;
};

class ReskiaSkSGGeometryNode final : public SkRefCnt {
public:
    explicit ReskiaSkSGGeometryNode(sk_sp<sksg::GeometryNode> node_in)
            : node(std::move(node_in)) {}

    explicit ReskiaSkSGGeometryNode(sk_sp<sksg::Rect> rect_in)
            : node(rect_in)
            , rect(std::move(rect_in)) {}

    explicit ReskiaSkSGGeometryNode(sk_sp<sksg::Path> path_in)
            : node(path_in)
            , path(std::move(path_in)) {}

    explicit ReskiaSkSGGeometryNode(sk_sp<sksg::RRect> rrect_in)
            : node(rrect_in)
            , rrect(std::move(rrect_in)) {}

    explicit ReskiaSkSGGeometryNode(sk_sp<sksg::GeometryTransform> geometry_transform_in)
            : node(geometry_transform_in)
            , geometry_transform(std::move(geometry_transform_in)) {}

    sk_sp<sksg::GeometryNode> node;
    sk_sp<sksg::Rect> rect;
    sk_sp<sksg::Path> path;
    sk_sp<sksg::RRect> rrect;
    sk_sp<sksg::GeometryTransform> geometry_transform;
};

class ReskiaSkSGPaintNode final : public SkRefCnt {
public:
    explicit ReskiaSkSGPaintNode(sk_sp<sksg::PaintNode> node_in)
            : node(std::move(node_in)) {}

    explicit ReskiaSkSGPaintNode(sk_sp<sksg::Color> color_in)
            : node(color_in)
            , color(std::move(color_in)) {}

    sk_sp<sksg::PaintNode> node;
    sk_sp<sksg::Color> color;
};

class ReskiaSkSGShader final : public SkRefCnt {
public:
    explicit ReskiaSkSGShader(sk_sp<sksg::Shader> shader_in)
            : shader(std::move(shader_in)) {}

    sk_sp<sksg::Shader> shader;
};

class ReskiaSkSGImageFilter final : public SkRefCnt {
public:
    explicit ReskiaSkSGImageFilter(sk_sp<sksg::ImageFilter> filter_in)
            : filter(std::move(filter_in)) {}

    sk_sp<sksg::ImageFilter> filter;
};

class ReskiaSkSGTransform final : public SkRefCnt {
public:
    explicit ReskiaSkSGTransform(sk_sp<sksg::Transform> transform_in)
            : transform(std::move(transform_in)) {}

    sk_sp<sksg::Transform> transform;
};

inline ReskiaSkSGScene *to_scene_holder(reskia_sksg_scene_t *scene) {
    return reinterpret_cast<ReskiaSkSGScene *>(scene);
}

inline const ReskiaSkSGScene *to_scene_holder(const reskia_sksg_scene_t *scene) {
    return reinterpret_cast<const ReskiaSkSGScene *>(scene);
}

inline ReskiaSkSGRenderNode *to_render_node_holder(reskia_sksg_render_node_t *node) {
    return reinterpret_cast<ReskiaSkSGRenderNode *>(node);
}

inline const ReskiaSkSGRenderNode *to_render_node_holder(const reskia_sksg_render_node_t *node) {
    return reinterpret_cast<const ReskiaSkSGRenderNode *>(node);
}

inline ReskiaSkSGGeometryNode *to_geometry_node_holder(reskia_sksg_geometry_node_t *node) {
    return reinterpret_cast<ReskiaSkSGGeometryNode *>(node);
}

inline ReskiaSkSGPaintNode *to_paint_node_holder(reskia_sksg_paint_node_t *node) {
    return reinterpret_cast<ReskiaSkSGPaintNode *>(node);
}

inline ReskiaSkSGShader *to_shader_holder(reskia_sksg_shader_t *shader) {
    return reinterpret_cast<ReskiaSkSGShader *>(shader);
}

inline ReskiaSkSGImageFilter *to_image_filter_holder(reskia_sksg_image_filter_t *filter) {
    return reinterpret_cast<ReskiaSkSGImageFilter *>(filter);
}

inline ReskiaSkSGTransform *to_transform_holder(reskia_sksg_transform_t *transform) {
    return reinterpret_cast<ReskiaSkSGTransform *>(transform);
}

inline sksg::InvalidationController *to_invalidation_controller(reskia_sksg_invalidation_controller_t *controller) {
    return reinterpret_cast<sksg::InvalidationController *>(controller);
}

sk_sp<sksg::RenderNode> make_simple_rect_render_node(float x, float y, float width, float height, reskia_color_t color) {
    if (!(width > 0.0f) || !(height > 0.0f)) {
        return nullptr;
    }
    auto root = sksg::Group::Make();
    auto rect = sksg::Rect::Make(SkRect::MakeXYWH(x, y, width, height));
    auto paint = sksg::Color::Make(static_cast<SkColor>(color));
    auto draw = sksg::Draw::Make(rect, paint);
    if (root == nullptr || rect == nullptr || paint == nullptr || draw == nullptr) {
        return nullptr;
    }
    root->addChild(draw);
    return root;
}

reskia_sksg_render_node_t *wrap_render_node(sk_sp<sksg::RenderNode> node) {
    if (node == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGRenderNode>(std::move(node));
    return reinterpret_cast<reskia_sksg_render_node_t *>(holder.release());
}

reskia_sksg_render_node_t *wrap_group(sk_sp<sksg::Group> group) {
    if (group == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGRenderNode>(std::move(group));
    return reinterpret_cast<reskia_sksg_render_node_t *>(holder.release());
}

reskia_sksg_render_node_t *wrap_opacity_effect(sk_sp<sksg::OpacityEffect> effect) {
    if (effect == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGRenderNode>(std::move(effect));
    return reinterpret_cast<reskia_sksg_render_node_t *>(holder.release());
}

reskia_sksg_render_node_t *wrap_transform_effect(sk_sp<sksg::TransformEffect> effect) {
    if (effect == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGRenderNode>(std::move(effect));
    return reinterpret_cast<reskia_sksg_render_node_t *>(holder.release());
}

reskia_sksg_render_node_t *wrap_shader_effect(sk_sp<sksg::ShaderEffect> effect) {
    if (effect == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGRenderNode>(std::move(effect));
    return reinterpret_cast<reskia_sksg_render_node_t *>(holder.release());
}

reskia_sksg_geometry_node_t *wrap_geometry_node(sk_sp<sksg::GeometryNode> node) {
    if (node == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGGeometryNode>(std::move(node));
    return reinterpret_cast<reskia_sksg_geometry_node_t *>(holder.release());
}

reskia_sksg_geometry_node_t *wrap_rect(sk_sp<sksg::Rect> rect) {
    if (rect == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGGeometryNode>(std::move(rect));
    return reinterpret_cast<reskia_sksg_geometry_node_t *>(holder.release());
}

reskia_sksg_geometry_node_t *wrap_path(sk_sp<sksg::Path> path) {
    if (path == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGGeometryNode>(std::move(path));
    return reinterpret_cast<reskia_sksg_geometry_node_t *>(holder.release());
}

reskia_sksg_geometry_node_t *wrap_rrect(sk_sp<sksg::RRect> rrect) {
    if (rrect == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGGeometryNode>(std::move(rrect));
    return reinterpret_cast<reskia_sksg_geometry_node_t *>(holder.release());
}

reskia_sksg_geometry_node_t *wrap_geometry_transform(sk_sp<sksg::GeometryTransform> geometry_transform) {
    if (geometry_transform == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGGeometryNode>(std::move(geometry_transform));
    return reinterpret_cast<reskia_sksg_geometry_node_t *>(holder.release());
}

reskia_sksg_paint_node_t *wrap_color(sk_sp<sksg::Color> color) {
    if (color == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGPaintNode>(std::move(color));
    return reinterpret_cast<reskia_sksg_paint_node_t *>(holder.release());
}

reskia_sksg_paint_node_t *wrap_paint_node(sk_sp<sksg::PaintNode> node) {
    if (node == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGPaintNode>(std::move(node));
    return reinterpret_cast<reskia_sksg_paint_node_t *>(holder.release());
}

reskia_sksg_shader_t *wrap_shader(sk_sp<sksg::Shader> shader) {
    if (shader == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGShader>(std::move(shader));
    return reinterpret_cast<reskia_sksg_shader_t *>(holder.release());
}

reskia_sksg_image_filter_t *wrap_image_filter(sk_sp<sksg::ImageFilter> filter) {
    if (filter == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGImageFilter>(std::move(filter));
    return reinterpret_cast<reskia_sksg_image_filter_t *>(holder.release());
}

reskia_sksg_transform_t *wrap_transform(sk_sp<sksg::Transform> transform) {
    if (transform == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGTransform>(std::move(transform));
    return reinterpret_cast<reskia_sksg_transform_t *>(holder.release());
}

} // namespace

extern "C" {

reskia_sksg_scene_t *SkSG_Scene_MakeSimpleRect(float x, float y, float width, float height, reskia_color_t color) {
    auto root = make_simple_rect_render_node(x, y, width, height, color);
    auto scene = sksg::Scene::Make(root);
    if (scene == nullptr) {
        return nullptr;
    }

    auto holder = sk_make_sp<ReskiaSkSGScene>(std::move(scene));
    return reinterpret_cast<reskia_sksg_scene_t *>(holder.release());
}

reskia_sksg_scene_t *SkSG_Scene_Make(reskia_sksg_render_node_t *root) {
    if (root == nullptr || to_render_node_holder(root)->node == nullptr) {
        return nullptr;
    }
    auto scene = sksg::Scene::Make(to_render_node_holder(root)->node);
    if (scene == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGScene>(std::move(scene));
    return reinterpret_cast<reskia_sksg_scene_t *>(holder.release());
}

reskia_sksg_render_node_t *SkSG_RenderNode_MakeSimpleRect(float x, float y, float width, float height, reskia_color_t color) {
    auto node = make_simple_rect_render_node(x, y, width, height, color);
    return wrap_render_node(std::move(node));
}

reskia_sksg_render_node_t *SkSG_Group_Make() {
    return wrap_group(sksg::Group::Make());
}

bool SkSG_Group_addChild(reskia_sksg_render_node_t *group, reskia_sksg_render_node_t *child) {
    if (group == nullptr || child == nullptr ||
        to_render_node_holder(group)->group == nullptr ||
        to_render_node_holder(child)->node == nullptr) {
        return false;
    }
    to_render_node_holder(group)->group->addChild(to_render_node_holder(child)->node);
    return true;
}

bool SkSG_Group_removeChild(reskia_sksg_render_node_t *group, reskia_sksg_render_node_t *child) {
    if (group == nullptr || child == nullptr ||
        to_render_node_holder(group)->group == nullptr ||
        to_render_node_holder(child)->node == nullptr) {
        return false;
    }
    to_render_node_holder(group)->group->removeChild(to_render_node_holder(child)->node);
    return true;
}

size_t SkSG_Group_size(reskia_sksg_render_node_t *group) {
    return group != nullptr && to_render_node_holder(group)->group != nullptr
                   ? to_render_node_holder(group)->group->size()
                   : 0;
}

bool SkSG_Group_empty(reskia_sksg_render_node_t *group) {
    return group == nullptr || to_render_node_holder(group)->group == nullptr ||
           to_render_node_holder(group)->group->empty();
}

void SkSG_Group_clear(reskia_sksg_render_node_t *group) {
    if (group != nullptr && to_render_node_holder(group)->group != nullptr) {
        to_render_node_holder(group)->group->clear();
    }
}

reskia_sksg_geometry_node_t *SkSG_Rect_Make() {
    return wrap_rect(sksg::Rect::Make());
}

reskia_sksg_geometry_node_t *SkSG_Rect_MakeXYWH(float x, float y, float width, float height) {
    if (!(width >= 0.0f) || !(height >= 0.0f)) {
        return nullptr;
    }
    return wrap_rect(sksg::Rect::Make(SkRect::MakeXYWH(x, y, width, height)));
}

reskia_sksg_geometry_node_t *SkSG_RRect_Make() {
    return wrap_rrect(sksg::RRect::Make());
}

reskia_sksg_geometry_node_t *SkSG_RRect_MakeFromRRect(const reskia_r_rect_t *rrect) {
    return rrect != nullptr ? wrap_rrect(sksg::RRect::Make(*reinterpret_cast<const SkRRect *>(rrect))) : nullptr;
}

reskia_sksg_geometry_node_t *SkSG_Path_Make() {
    return wrap_path(sksg::Path::Make());
}

void SkSG_Path_setFillType(reskia_sksg_geometry_node_t *path, int fill_type) {
    if (path != nullptr && to_geometry_node_holder(path)->path != nullptr) {
        to_geometry_node_holder(path)->path->setFillType(static_cast<SkPathFillType>(fill_type));
    }
}

reskia_sksg_geometry_node_t *SkSG_Plane_Make() {
    return wrap_geometry_node(sksg::Plane::Make());
}

reskia_sksg_geometry_node_t *SkSG_TrimEffect_Make(reskia_sksg_geometry_node_t *child) {
    return child != nullptr && to_geometry_node_holder(child)->node != nullptr
                   ? wrap_geometry_node(sksg::TrimEffect::Make(to_geometry_node_holder(child)->node))
                   : nullptr;
}

reskia_sksg_geometry_node_t *SkSG_DashEffect_Make(reskia_sksg_geometry_node_t *child) {
    return child != nullptr && to_geometry_node_holder(child)->node != nullptr
                   ? wrap_geometry_node(sksg::DashEffect::Make(to_geometry_node_holder(child)->node))
                   : nullptr;
}

reskia_sksg_geometry_node_t *SkSG_RoundEffect_Make(reskia_sksg_geometry_node_t *child) {
    return child != nullptr && to_geometry_node_holder(child)->node != nullptr
                   ? wrap_geometry_node(sksg::RoundEffect::Make(to_geometry_node_holder(child)->node))
                   : nullptr;
}

reskia_sksg_geometry_node_t *SkSG_OffsetEffect_Make(reskia_sksg_geometry_node_t *child) {
    return child != nullptr && to_geometry_node_holder(child)->node != nullptr
                   ? wrap_geometry_node(sksg::OffsetEffect::Make(to_geometry_node_holder(child)->node))
                   : nullptr;
}

reskia_sksg_geometry_node_t *SkSG_GeometryTransform_Make(reskia_sksg_geometry_node_t *child, reskia_sksg_transform_t *transform) {
    return child != nullptr && transform != nullptr &&
                   to_geometry_node_holder(child)->node != nullptr &&
                   to_transform_holder(transform)->transform != nullptr
                   ? wrap_geometry_transform(sksg::GeometryTransform::Make(
                             to_geometry_node_holder(child)->node,
                             to_transform_holder(transform)->transform))
                   : nullptr;
}

reskia_sksg_transform_t *SkSG_GeometryTransform_getTransform(reskia_sksg_geometry_node_t *geometry_transform) {
    return geometry_transform != nullptr && to_geometry_node_holder(geometry_transform)->geometry_transform != nullptr
                   ? wrap_transform(to_geometry_node_holder(geometry_transform)->geometry_transform->getTransform())
                   : nullptr;
}

reskia_sksg_geometry_node_t *SkSG_Merge_Make(const reskia_sksg_geometry_node_t *const *geometry_nodes, const int *modes, int count) {
    if (count < 0 || (count > 0 && (geometry_nodes == nullptr || modes == nullptr))) {
        return nullptr;
    }
    std::vector<sksg::Merge::Rec> records;
    records.reserve(static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        auto *holder = reinterpret_cast<const ReskiaSkSGGeometryNode *>(geometry_nodes[i]);
        if (holder == nullptr || holder->node == nullptr) {
            return nullptr;
        }
        records.push_back({holder->node, static_cast<sksg::Merge::Mode>(modes[i])});
    }
    return wrap_geometry_node(sksg::Merge::Make(std::move(records)));
}

reskia_sksg_geometry_node_t *SkSG_Text_Make(reskia_typeface_t *typeface, const char *text) {
    return text != nullptr ? wrap_geometry_node(sksg::Text::Make(
            typeface != nullptr ? sk_ref_sp(reinterpret_cast<SkTypeface *>(typeface)) : nullptr,
            SkString(text))) : nullptr;
}

reskia_sksg_paint_node_t *SkSG_Color_Make(reskia_color_t color) {
    return wrap_color(sksg::Color::Make(static_cast<SkColor>(color)));
}

reskia_color_t SkSG_Color_getColor(reskia_sksg_paint_node_t *color) {
    return color != nullptr && to_paint_node_holder(color)->color != nullptr
                   ? static_cast<reskia_color_t>(to_paint_node_holder(color)->color->getColor())
                   : 0;
}

void SkSG_Color_setColor(reskia_sksg_paint_node_t *color, reskia_color_t value) {
    if (color != nullptr && to_paint_node_holder(color)->color != nullptr) {
        to_paint_node_holder(color)->color->setColor(static_cast<SkColor>(value));
    }
}

reskia_sksg_paint_node_t *SkSG_ShaderPaint_Make(reskia_sksg_shader_t *shader) {
    return shader != nullptr && to_shader_holder(shader)->shader != nullptr
                   ? wrap_paint_node(sksg::ShaderPaint::Make(to_shader_holder(shader)->shader))
                   : nullptr;
}

reskia_sksg_render_node_t *SkSG_Draw_Make(reskia_sksg_geometry_node_t *geometry, reskia_sksg_paint_node_t *paint) {
    if (geometry == nullptr || paint == nullptr ||
        to_geometry_node_holder(geometry)->node == nullptr ||
        to_paint_node_holder(paint)->node == nullptr) {
        return nullptr;
    }
    return wrap_render_node(sksg::Draw::Make(to_geometry_node_holder(geometry)->node,
                                             to_paint_node_holder(paint)->node));
}

reskia_sksg_render_node_t *SkSG_OpacityEffect_Make(reskia_sksg_render_node_t *child, float opacity) {
    if (child == nullptr || to_render_node_holder(child)->node == nullptr) {
        return nullptr;
    }
    return wrap_opacity_effect(sksg::OpacityEffect::Make(to_render_node_holder(child)->node, opacity));
}

float SkSG_OpacityEffect_getOpacity(reskia_sksg_render_node_t *effect) {
    return effect != nullptr && to_render_node_holder(effect)->opacity_effect != nullptr
                   ? to_render_node_holder(effect)->opacity_effect->getOpacity()
                   : 0.0f;
}

void SkSG_OpacityEffect_setOpacity(reskia_sksg_render_node_t *effect, float opacity) {
    if (effect != nullptr && to_render_node_holder(effect)->opacity_effect != nullptr) {
        to_render_node_holder(effect)->opacity_effect->setOpacity(opacity);
    }
}

reskia_sksg_render_node_t *SkSG_ClipEffect_Make(reskia_sksg_render_node_t *child, reskia_sksg_geometry_node_t *clip, bool aa, bool force_clip) {
    if (child == nullptr || clip == nullptr ||
        to_render_node_holder(child)->node == nullptr ||
        to_geometry_node_holder(clip)->node == nullptr) {
        return nullptr;
    }
    return wrap_render_node(sksg::ClipEffect::Make(to_render_node_holder(child)->node,
                                                   to_geometry_node_holder(clip)->node,
                                                   aa,
                                                   force_clip));
}

reskia_sksg_render_node_t *SkSG_TransformEffect_Make(reskia_sksg_render_node_t *child, const reskia_matrix_t *matrix) {
    if (child == nullptr || matrix == nullptr || to_render_node_holder(child)->node == nullptr) {
        return nullptr;
    }
    return wrap_transform_effect(sksg::TransformEffect::Make(to_render_node_holder(child)->node,
                                                             *reinterpret_cast<const SkMatrix *>(matrix)));
}

reskia_sksg_render_node_t *SkSG_TransformEffect_MakeWithMatrix(reskia_sksg_render_node_t *child, const reskia_matrix_t *matrix) {
    return SkSG_TransformEffect_Make(child, matrix);
}

reskia_sksg_render_node_t *SkSG_ShaderEffect_Make(reskia_sksg_render_node_t *child) {
    return child != nullptr && to_render_node_holder(child)->node != nullptr
                   ? wrap_shader_effect(sksg::ShaderEffect::Make(to_render_node_holder(child)->node))
                   : nullptr;
}

bool SkSG_ShaderEffect_setShader(reskia_sksg_render_node_t *effect, reskia_sksg_shader_t *shader) {
    if (effect == nullptr || shader == nullptr ||
        to_render_node_holder(effect)->shader_effect == nullptr ||
        to_shader_holder(shader)->shader == nullptr) {
        return false;
    }
    to_render_node_holder(effect)->shader_effect->setShader(to_shader_holder(shader)->shader);
    return true;
}

reskia_sksg_render_node_t *SkSG_MaskShaderEffect_Make(reskia_sksg_render_node_t *child) {
    return child != nullptr && to_render_node_holder(child)->node != nullptr
                   ? wrap_render_node(sksg::MaskShaderEffect::Make(to_render_node_holder(child)->node))
                   : nullptr;
}

reskia_sksg_render_node_t *SkSG_BlenderEffect_Make(reskia_sksg_render_node_t *child) {
    return child != nullptr && to_render_node_holder(child)->node != nullptr
                   ? wrap_render_node(sksg::BlenderEffect::Make(to_render_node_holder(child)->node))
                   : nullptr;
}

reskia_sksg_render_node_t *SkSG_LayerEffect_Make(reskia_sksg_render_node_t *child, int blend_mode) {
    return child != nullptr && to_render_node_holder(child)->node != nullptr
                   ? wrap_render_node(sksg::LayerEffect::Make(to_render_node_holder(child)->node,
                                                              static_cast<SkBlendMode>(blend_mode)))
                   : nullptr;
}

reskia_sksg_render_node_t *SkSG_MaskEffect_Make(reskia_sksg_render_node_t *child, reskia_sksg_render_node_t *mask, int mode) {
    if (child == nullptr || mask == nullptr ||
        to_render_node_holder(child)->node == nullptr ||
        to_render_node_holder(mask)->node == nullptr) {
        return nullptr;
    }
    return wrap_render_node(sksg::MaskEffect::Make(to_render_node_holder(child)->node,
                                                   to_render_node_holder(mask)->node,
                                                   static_cast<sksg::MaskEffect::Mode>(mode)));
}

reskia_sksg_render_node_t *SkSG_ExternalColorFilter_Make(reskia_sksg_render_node_t *child) {
    return child != nullptr && to_render_node_holder(child)->node != nullptr
                   ? wrap_render_node(sksg::ExternalColorFilter::Make(to_render_node_holder(child)->node))
                   : nullptr;
}

reskia_sksg_render_node_t *SkSG_ModeColorFilter_Make(reskia_sksg_render_node_t *child, reskia_sksg_paint_node_t *color, int blend_mode) {
    return child != nullptr && color != nullptr &&
                   to_render_node_holder(child)->node != nullptr &&
                   to_paint_node_holder(color)->color != nullptr
                   ? wrap_render_node(sksg::ModeColorFilter::Make(
                             to_render_node_holder(child)->node,
                             to_paint_node_holder(color)->color,
                             static_cast<SkBlendMode>(blend_mode)))
                   : nullptr;
}

reskia_sksg_render_node_t *SkSG_GradientColorFilter_Make(reskia_sksg_render_node_t *child, reskia_sksg_paint_node_t *color0, reskia_sksg_paint_node_t *color1) {
    return child != nullptr && color0 != nullptr && color1 != nullptr &&
                   to_render_node_holder(child)->node != nullptr &&
                   to_paint_node_holder(color0)->color != nullptr &&
                   to_paint_node_holder(color1)->color != nullptr
                   ? wrap_render_node(sksg::GradientColorFilter::Make(
                             to_render_node_holder(child)->node,
                             to_paint_node_holder(color0)->color,
                             to_paint_node_holder(color1)->color))
                   : nullptr;
}

reskia_sksg_render_node_t *SkSG_GradientColorFilter_MakeMany(reskia_sksg_render_node_t *child, reskia_sksg_paint_node_t *const *colors, int count) {
    if (child == nullptr || to_render_node_holder(child)->node == nullptr ||
        count < 0 || (count > 0 && colors == nullptr)) {
        return nullptr;
    }
    std::vector<sk_sp<sksg::Color>> color_nodes;
    color_nodes.reserve(static_cast<size_t>(count));
    for (int i = 0; i < count; ++i) {
        if (colors[i] == nullptr || to_paint_node_holder(colors[i])->color == nullptr) {
            return nullptr;
        }
        color_nodes.push_back(to_paint_node_holder(colors[i])->color);
    }
    return wrap_render_node(sksg::GradientColorFilter::Make(
            to_render_node_holder(child)->node, std::move(color_nodes)));
}

reskia_sksg_render_node_t *SkSG_Image_Make(reskia_image_t *image) {
    return image != nullptr ? wrap_render_node(sksg::Image::Make(sk_ref_sp(reinterpret_cast<SkImage *>(image)))) : nullptr;
}

reskia_sksg_render_node_t *SkSG_ImageFilterEffect_Make(reskia_sksg_render_node_t *child, reskia_sksg_image_filter_t *filter) {
    return child != nullptr && filter != nullptr &&
                   to_render_node_holder(child)->node != nullptr &&
                   to_image_filter_holder(filter)->filter != nullptr
                   ? wrap_render_node(sksg::ImageFilterEffect::Make(
                             to_render_node_holder(child)->node,
                             to_image_filter_holder(filter)->filter))
                   : nullptr;
}

reskia_sksg_invalidation_controller_t *SkSG_InvalidationController_new() {
    return reinterpret_cast<reskia_sksg_invalidation_controller_t *>(new sksg::InvalidationController());
}

void SkSG_InvalidationController_delete(reskia_sksg_invalidation_controller_t *controller) {
    delete to_invalidation_controller(controller);
}

void SkSG_InvalidationController_inval(reskia_sksg_invalidation_controller_t *controller, float left, float top, float right, float bottom) {
    if (controller != nullptr) {
        to_invalidation_controller(controller)->inval(SkRect::MakeLTRB(left, top, right, bottom));
    }
}

reskia_rect_t *SkSG_InvalidationController_bounds(reskia_sksg_invalidation_controller_t *controller) {
    return controller != nullptr ? reinterpret_cast<reskia_rect_t *>(new SkRect(to_invalidation_controller(controller)->bounds())) : nullptr;
}

size_t SkSG_InvalidationController_begin(reskia_sksg_invalidation_controller_t *controller) {
    (void)controller;
    return 0;
}

size_t SkSG_InvalidationController_end(reskia_sksg_invalidation_controller_t *controller) {
    if (controller == nullptr) {
        return 0;
    }
    return static_cast<size_t>(std::distance(
            to_invalidation_controller(controller)->begin(),
            to_invalidation_controller(controller)->end()));
}

void SkSG_InvalidationController_reset(reskia_sksg_invalidation_controller_t *controller) {
    if (controller != nullptr) {
        to_invalidation_controller(controller)->reset();
    }
}

reskia_sksg_shader_t *SkSG_LinearGradient_Make() {
    return wrap_shader(sksg::LinearGradient::Make());
}

reskia_sksg_shader_t *SkSG_RadialGradient_Make() {
    return wrap_shader(sksg::RadialGradient::Make());
}

void SkSG_Shader_release(reskia_sksg_shader_t *shader) {
    if (shader != nullptr) {
        to_shader_holder(shader)->unref();
    }
}

void SkSG_Shader_ref(reskia_sksg_shader_t *shader) {
    if (shader != nullptr) {
        to_shader_holder(shader)->ref();
    }
}

void SkSG_Shader_unref(reskia_sksg_shader_t *shader) {
    if (shader != nullptr) {
        to_shader_holder(shader)->unref();
    }
}

bool SkSG_Shader_getShader(reskia_sksg_shader_t *shader) {
    if (shader == nullptr || to_shader_holder(shader)->shader == nullptr) {
        return false;
    }
    to_shader_holder(shader)->shader->revalidate(nullptr, SkMatrix::I());
    return to_shader_holder(shader)->shader->getShader() != nullptr;
}

reskia_sksg_image_filter_t *SkSG_ExternalImageFilter_Make() {
    return wrap_image_filter(sksg::ExternalImageFilter::Make());
}

reskia_sksg_image_filter_t *SkSG_DropShadowImageFilter_Make() {
    return wrap_image_filter(sksg::DropShadowImageFilter::Make());
}

reskia_sksg_image_filter_t *SkSG_BlurImageFilter_Make() {
    return wrap_image_filter(sksg::BlurImageFilter::Make());
}

void SkSG_ImageFilter_release(reskia_sksg_image_filter_t *filter) {
    if (filter != nullptr) {
        to_image_filter_holder(filter)->unref();
    }
}

void SkSG_ImageFilter_ref(reskia_sksg_image_filter_t *filter) {
    if (filter != nullptr) {
        to_image_filter_holder(filter)->ref();
    }
}

void SkSG_ImageFilter_unref(reskia_sksg_image_filter_t *filter) {
    if (filter != nullptr) {
        to_image_filter_holder(filter)->unref();
    }
}

bool SkSG_ImageFilter_getFilter(reskia_sksg_image_filter_t *filter) {
    if (filter == nullptr || to_image_filter_holder(filter)->filter == nullptr) {
        return false;
    }
    to_image_filter_holder(filter)->filter->revalidate(nullptr, SkMatrix::I());
    return to_image_filter_holder(filter)->filter->getFilter() != nullptr;
}

reskia_sksg_transform_t *SkSG_Transform_MakeFromMatrix(const reskia_matrix_t *matrix) {
    return matrix != nullptr ? wrap_transform(sksg::Matrix<SkMatrix>::Make(*reinterpret_cast<const SkMatrix *>(matrix))) : nullptr;
}

reskia_sksg_transform_t *SkSG_Transform_MakeConcat(reskia_sksg_transform_t *a, reskia_sksg_transform_t *b) {
    return a != nullptr && b != nullptr && a != b &&
                   to_transform_holder(a)->transform != nullptr &&
                   to_transform_holder(b)->transform != nullptr
                   ? wrap_transform(sksg::Transform::MakeConcat(
                             to_transform_holder(a)->transform,
                             to_transform_holder(b)->transform))
                   : nullptr;
}

reskia_sksg_transform_t *SkSG_Transform_MakeInverse(reskia_sksg_transform_t *transform) {
    return transform != nullptr && to_transform_holder(transform)->transform != nullptr
                   ? wrap_transform(sksg::Transform::MakeInverse(to_transform_holder(transform)->transform))
                   : nullptr;
}

void SkSG_Transform_release(reskia_sksg_transform_t *transform) {
    if (transform != nullptr) {
        to_transform_holder(transform)->unref();
    }
}

void SkSG_Transform_ref(reskia_sksg_transform_t *transform) {
    if (transform != nullptr) {
        to_transform_holder(transform)->ref();
    }
}

void SkSG_Transform_unref(reskia_sksg_transform_t *transform) {
    if (transform != nullptr) {
        to_transform_holder(transform)->unref();
    }
}

void SkSG_GeometryNode_release(reskia_sksg_geometry_node_t *node) {
    if (node != nullptr) {
        to_geometry_node_holder(node)->unref();
    }
}

void SkSG_GeometryNode_ref(reskia_sksg_geometry_node_t *node) {
    if (node != nullptr) {
        to_geometry_node_holder(node)->ref();
    }
}

void SkSG_GeometryNode_unref(reskia_sksg_geometry_node_t *node) {
    if (node != nullptr) {
        to_geometry_node_holder(node)->unref();
    }
}

bool SkSG_GeometryNode_contains(reskia_sksg_geometry_node_t *node, float x, float y) {
    if (node == nullptr || to_geometry_node_holder(node)->node == nullptr) {
        return false;
    }
    to_geometry_node_holder(node)->node->revalidate(nullptr, SkMatrix::I());
    return to_geometry_node_holder(node)->node->contains(SkPoint::Make(x, y));
}

void SkSG_GeometryNode_clip(reskia_sksg_geometry_node_t *node, reskia_canvas_t *canvas, bool anti_alias) {
    if (node != nullptr && canvas != nullptr && to_geometry_node_holder(node)->node != nullptr) {
        to_geometry_node_holder(node)->node->revalidate(nullptr, SkMatrix::I());
        to_geometry_node_holder(node)->node->clip(reinterpret_cast<SkCanvas *>(canvas), anti_alias);
    }
}

void SkSG_GeometryNode_draw(reskia_sksg_geometry_node_t *node, reskia_canvas_t *canvas, const reskia_paint_t *paint) {
    if (node != nullptr && canvas != nullptr && paint != nullptr && to_geometry_node_holder(node)->node != nullptr) {
        to_geometry_node_holder(node)->node->revalidate(nullptr, SkMatrix::I());
        to_geometry_node_holder(node)->node->draw(reinterpret_cast<SkCanvas *>(canvas),
                                                  *reinterpret_cast<const SkPaint *>(paint));
    }
}

reskia_path_t *SkSG_GeometryNode_asPath(reskia_sksg_geometry_node_t *node) {
    if (node == nullptr || to_geometry_node_holder(node)->node == nullptr) {
        return nullptr;
    }
    to_geometry_node_holder(node)->node->revalidate(nullptr, SkMatrix::I());
    return reinterpret_cast<reskia_path_t *>(new SkPath(to_geometry_node_holder(node)->node->asPath()));
}

void SkSG_PaintNode_release(reskia_sksg_paint_node_t *node) {
    if (node != nullptr) {
        to_paint_node_holder(node)->unref();
    }
}

void SkSG_PaintNode_ref(reskia_sksg_paint_node_t *node) {
    if (node != nullptr) {
        to_paint_node_holder(node)->ref();
    }
}

void SkSG_PaintNode_unref(reskia_sksg_paint_node_t *node) {
    if (node != nullptr) {
        to_paint_node_holder(node)->unref();
    }
}

reskia_paint_t *SkSG_PaintNode_makePaint(reskia_sksg_paint_node_t *node) {
    if (node == nullptr || to_paint_node_holder(node)->node == nullptr) {
        return nullptr;
    }
    to_paint_node_holder(node)->node->revalidate(nullptr, SkMatrix::I());
    return reinterpret_cast<reskia_paint_t *>(new SkPaint(to_paint_node_holder(node)->node->makePaint()));
}

void SkSG_RenderNode_release(reskia_sksg_render_node_t *node) {
    if (node == nullptr) {
        return;
    }
    to_render_node_holder(node)->unref();
}

void SkSG_RenderNode_ref(reskia_sksg_render_node_t *node) {
    if (node == nullptr) {
        return;
    }
    to_render_node_holder(node)->ref();
}

void SkSG_RenderNode_unref(reskia_sksg_render_node_t *node) {
    if (node == nullptr) {
        return;
    }
    to_render_node_holder(node)->unref();
}

bool SkSG_RenderNode_render(reskia_sksg_render_node_t *node, reskia_canvas_t *canvas) {
    if (node == nullptr || canvas == nullptr || to_render_node_holder(node)->node == nullptr) {
        return false;
    }
    to_render_node_holder(node)->node->render(reinterpret_cast<SkCanvas *>(canvas));
    return true;
}

bool SkSG_RenderNode_nodeAt(reskia_sksg_render_node_t *node, float x, float y) {
    if (node == nullptr || to_render_node_holder(node)->node == nullptr) {
        return false;
    }
    return to_render_node_holder(node)->node->nodeAt(SkPoint::Make(x, y)) != nullptr;
}

bool SkSG_RenderNode_isVisible(reskia_sksg_render_node_t *node) {
    return node != nullptr && to_render_node_holder(node)->node != nullptr &&
           to_render_node_holder(node)->node->isVisible();
}

void SkSG_RenderNode_setVisible(reskia_sksg_render_node_t *node, bool visible) {
    if (node != nullptr && to_render_node_holder(node)->node != nullptr) {
        to_render_node_holder(node)->node->setVisible(visible);
    }
}

reskia_sksg_transform_t *SkSG_TransformEffect_getTransform(reskia_sksg_render_node_t *effect) {
    return effect != nullptr && to_render_node_holder(effect)->transform_effect != nullptr
                   ? wrap_transform(to_render_node_holder(effect)->transform_effect->getTransform())
                   : nullptr;
}

void SkSG_Node_invalidate(reskia_sksg_render_node_t *node, bool damage) {
    if (node != nullptr && to_render_node_holder(node)->node != nullptr) {
        to_render_node_holder(node)->node->invalidate(damage);
    }
}

bool SkSG_Node_revalidate(reskia_sksg_render_node_t *node) {
    if (node == nullptr || to_render_node_holder(node)->node == nullptr) {
        return false;
    }
    to_render_node_holder(node)->node->revalidate(nullptr, SkMatrix::I());
    return true;
}

void SkSG_Scene_release(reskia_sksg_scene_t *scene) {
    if (scene == nullptr) {
        return;
    }
    to_scene_holder(scene)->unref();
}

void SkSG_Scene_ref(reskia_sksg_scene_t *scene) {
    if (scene == nullptr) {
        return;
    }
    to_scene_holder(scene)->ref();
}

void SkSG_Scene_unref(reskia_sksg_scene_t *scene) {
    if (scene == nullptr) {
        return;
    }
    to_scene_holder(scene)->unref();
}

bool SkSG_Scene_revalidate(reskia_sksg_scene_t *scene) {
    if (scene == nullptr) {
        return false;
    }
    const auto *holder = to_scene_holder(scene);
    if (!holder->scene) {
        return false;
    }
    holder->scene->revalidate();
    return true;
}

bool SkSG_Scene_render(reskia_sksg_scene_t *scene, reskia_canvas_t *canvas) {
    if (scene == nullptr || canvas == nullptr) {
        return false;
    }
    const auto *holder = to_scene_holder(scene);
    if (!holder->scene) {
        return false;
    }
    holder->scene->revalidate();
    holder->scene->render(reinterpret_cast<SkCanvas *>(canvas));
    return true;
}

bool SkSG_Scene_nodeAt(reskia_sksg_scene_t *scene, float x, float y) {
    if (scene == nullptr || !to_scene_holder(scene)->scene) {
        return false;
    }
    to_scene_holder(scene)->scene->revalidate();
    return to_scene_holder(scene)->scene->nodeAt(SkPoint::Make(x, y)) != nullptr;
}

} // extern "C"
