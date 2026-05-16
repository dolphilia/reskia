#include "sk_sksg.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkRect.h"
#include "include/core/SkRefCnt.h"
#include "modules/sksg/include/SkSGDraw.h"
#include "modules/sksg/include/SkSGGroup.h"
#include "modules/sksg/include/SkSGPaint.h"
#include "modules/sksg/include/SkSGRect.h"
#include "modules/sksg/include/SkSGScene.h"

#include <memory>
#include <utility>

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

    sk_sp<sksg::RenderNode> node;
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
    if (node == nullptr) {
        return nullptr;
    }
    auto holder = sk_make_sp<ReskiaSkSGRenderNode>(std::move(node));
    return reinterpret_cast<reskia_sksg_render_node_t *>(holder.release());
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

} // extern "C"
