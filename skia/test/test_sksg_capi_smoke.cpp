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
