#include <cstdio>

#include "capi/sk_canvas.h"
#include "capi/sk_graphics.h"
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
    if (!check(SkSG_RenderNode_MakeSimpleRect(0.0f, 0.0f, 0.0f, 8.0f, 0xFF000000u) == nullptr &&
               SkSG_Scene_Make(nullptr) == nullptr,
               "SkSG null/invalid helpers")) {
        return false;
    }

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

    SkCanvas_delete(canvas);
    SkSG_Scene_release(scene);

    reskia_sksg_render_node_t* root = SkSG_RenderNode_MakeSimpleRect(4.0f, 4.0f, 24.0f, 24.0f, 0xFF00FF00u);
    if (!check(root != nullptr, "SkSG_RenderNode_MakeSimpleRect")) {
        return false;
    }
    SkSG_RenderNode_ref(root);
    SkSG_RenderNode_unref(root);
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
