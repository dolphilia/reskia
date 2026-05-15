#include <cmath>
#include <cstdio>

#include "capi/sk_camera.h"
#include "capi/sk_canvas.h"
#include "capi/sk_m_44.h"
#include "capi/sk_matrix.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_v3-internal.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[camera-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool nearly_equal(float a, float b) {
    return std::fabs(a - b) < 0.001f;
}

bool smoke_patch_3d() {
    reskia_patch_3d_t *patch = SkPatch3D_new();
    reskia_patch_3d_t *dst = SkPatch3D_new();
    reskia_m_44_t *translate = SkM44_newDefault();
    if (!check(patch != nullptr && dst != nullptr && translate != nullptr, "SkPatch3D setup")) {
        SkM44_delete(translate);
        SkPatch3D_delete(dst);
        SkPatch3D_delete(patch);
        return false;
    }

    if (!check(nearly_equal(SkPatch3D_dotWith(patch, 0.0f, 0.0f, 1.0f), -1.0f),
               "SkPatch3D_dotWith default normal")) {
        SkM44_delete(translate);
        SkPatch3D_delete(dst);
        SkPatch3D_delete(patch);
        return false;
    }
    sk_v3_t normal_handle = static_sk_v3_make({0.0f, 0.0f, 1.0f});
    auto *normal = reinterpret_cast<reskia_v3_t *>(static_sk_v3_get_ptr(normal_handle));
    if (!check(nearly_equal(SkPatch3D_dotWithV3(patch, normal), -1.0f), "SkPatch3D_dotWithV3")) {
        static_sk_v3_delete(normal_handle);
        SkM44_delete(translate);
        SkPatch3D_delete(dst);
        SkPatch3D_delete(patch);
        return false;
    }

    SkM44_setTranslate(translate, 1.0f, 2.0f, 3.0f);
    SkPatch3D_transform(patch, translate, dst);
    const sk_v3_t origin_handle = SkPatch3D_getOrigin(dst);
    const SkV3 origin = static_sk_v3_get_entity(origin_handle);
    if (!check(nearly_equal(origin.x, 1.0f) && nearly_equal(origin.y, 2.0f) && nearly_equal(origin.z, 3.0f),
               "SkPatch3D_transform origin")) {
        static_sk_v3_delete(origin_handle);
        static_sk_v3_delete(normal_handle);
        SkM44_delete(translate);
        SkPatch3D_delete(dst);
        SkPatch3D_delete(patch);
        return false;
    }

    SkPatch3D_rotate(patch, 1.0f, 2.0f, 3.0f);
    SkPatch3D_rotateDegrees(patch, 1.0f, 2.0f, 3.0f);
    SkPatch3D_reset(patch);
    static_sk_v3_delete(origin_handle);
    static_sk_v3_delete(normal_handle);
    SkM44_delete(translate);
    SkPatch3D_delete(dst);
    SkPatch3D_delete(patch);
    return true;
}

bool smoke_camera_3d() {
    reskia_patch_3d_t *patch = SkPatch3D_new();
    reskia_camera_3d_t *camera = SkCamera3D_new();
    reskia_matrix_t *matrix = reinterpret_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(SkMatrix_Scale(1.0f, 1.0f)));
    if (!check(patch != nullptr && camera != nullptr && matrix != nullptr, "SkCamera3D setup")) {
        SkCamera3D_delete(camera);
        SkPatch3D_delete(patch);
        return false;
    }

    SkCamera3D_patchToMatrix(camera, patch, matrix);
    if (!check(SkMatrix_getPerspY(matrix) == 0.0f, "SkCamera3D_patchToMatrix")) {
        SkCamera3D_delete(camera);
        SkPatch3D_delete(patch);
        return false;
    }

    sk_v3_t location_handle = SkCamera3D_getLocation(camera);
    auto *location = reinterpret_cast<reskia_v3_t *>(static_sk_v3_get_ptr(location_handle));
    if (!check(location != nullptr, "SkCamera3D_getLocation")) {
        static_sk_v3_delete(location_handle);
        SkCamera3D_delete(camera);
        SkPatch3D_delete(patch);
        return false;
    }
    SkCamera3D_setObserver(camera, location);
    SkCamera3D_update(camera);
    SkCamera3D_reset(camera);

    static_sk_v3_delete(location_handle);
    SkCamera3D_delete(camera);
    SkPatch3D_delete(patch);
    return true;
}

bool smoke_3d_view() {
    reskia_3d_view_t *view = Sk3DView_new();
    reskia_matrix_t *matrix = reinterpret_cast<reskia_matrix_t *>(static_sk_matrix_get_ptr(SkMatrix_Scale(1.0f, 1.0f)));
    reskia_canvas_t *canvas = SkCanvas_newWithSizeProps(16, 16, nullptr);
    if (!check(view != nullptr && matrix != nullptr && canvas != nullptr, "Sk3DView setup")) {
        SkCanvas_delete(canvas);
        Sk3DView_delete(view);
        return false;
    }

    Sk3DView_save(view);
    Sk3DView_translate(view, 1.0f, 2.0f, 3.0f);
    Sk3DView_rotateX(view, 5.0f);
    Sk3DView_rotateY(view, 6.0f);
    Sk3DView_rotateZ(view, 7.0f);
    Sk3DView_getMatrix(view, matrix);
    Sk3DView_applyToCanvas(view, canvas);
    if (!check(Sk3DView_dotWithNormal(view, 0.0f, 0.0f, 1.0f) < 0.0f, "Sk3DView_dotWithNormal")) {
        SkCanvas_delete(canvas);
        Sk3DView_delete(view);
        return false;
    }
    Sk3DView_restore(view);

    SkCanvas_delete(canvas);
    Sk3DView_delete(view);
    return true;
}

}  // namespace

int main() {
    if (!smoke_patch_3d()) {
        return 1;
    }
    if (!smoke_camera_3d()) {
        return 1;
    }
    if (!smoke_3d_view()) {
        return 1;
    }
    std::fprintf(stdout, "[camera-utils-smoke] PASS\n");
    return 0;
}
