#include "sk_camera.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkM44.h"
#include "include/core/SkMatrix.h"
#include "include/utils/SkCamera.h"

#include "../handles/static_sk_v3-internal.h"

extern "C" {

reskia_patch_3d_t *SkPatch3D_new(void) {
    return reinterpret_cast<reskia_patch_3d_t *>(new SkPatch3D());
}

void SkPatch3D_delete(reskia_patch_3d_t *patch) {
    delete reinterpret_cast<SkPatch3D *>(patch);
}

void SkPatch3D_reset(reskia_patch_3d_t *patch) {
    if (patch == nullptr) {
        return;
    }
    reinterpret_cast<SkPatch3D *>(patch)->reset();
}

void SkPatch3D_transform(const reskia_patch_3d_t *patch, const reskia_m_44_t *matrix, reskia_patch_3d_t *dst) {
    if (patch == nullptr || matrix == nullptr) {
        return;
    }
    reinterpret_cast<const SkPatch3D *>(patch)->transform(
            *reinterpret_cast<const SkM44 *>(matrix),
            reinterpret_cast<SkPatch3D *>(dst));
}

float SkPatch3D_dotWith(const reskia_patch_3d_t *patch, float dx, float dy, float dz) {
    if (patch == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<const SkPatch3D *>(patch)->dotWith(dx, dy, dz);
}

float SkPatch3D_dotWithV3(const reskia_patch_3d_t *patch, const reskia_v3_t *v) {
    if (patch == nullptr || v == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<const SkPatch3D *>(patch)->dotWith(*reinterpret_cast<const SkV3 *>(v));
}

void SkPatch3D_rotate(reskia_patch_3d_t *patch, float x, float y, float z) {
    if (patch == nullptr) {
        return;
    }
    reinterpret_cast<SkPatch3D *>(patch)->rotate(x, y, z);
}

void SkPatch3D_rotateDegrees(reskia_patch_3d_t *patch, float x, float y, float z) {
    if (patch == nullptr) {
        return;
    }
    reinterpret_cast<SkPatch3D *>(patch)->rotateDegrees(x, y, z);
}

sk_v3_t SkPatch3D_getU(const reskia_patch_3d_t *patch) {
    if (patch == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<const SkPatch3D *>(patch)->fU);
}

sk_v3_t SkPatch3D_getV(const reskia_patch_3d_t *patch) {
    if (patch == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<const SkPatch3D *>(patch)->fV);
}

sk_v3_t SkPatch3D_getOrigin(const reskia_patch_3d_t *patch) {
    if (patch == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<const SkPatch3D *>(patch)->fOrigin);
}

void SkPatch3D_setU(reskia_patch_3d_t *patch, const reskia_v3_t *u) {
    if (patch == nullptr || u == nullptr) {
        return;
    }
    reinterpret_cast<SkPatch3D *>(patch)->fU = *reinterpret_cast<const SkV3 *>(u);
}

void SkPatch3D_setV(reskia_patch_3d_t *patch, const reskia_v3_t *v) {
    if (patch == nullptr || v == nullptr) {
        return;
    }
    reinterpret_cast<SkPatch3D *>(patch)->fV = *reinterpret_cast<const SkV3 *>(v);
}

void SkPatch3D_setOrigin(reskia_patch_3d_t *patch, const reskia_v3_t *origin) {
    if (patch == nullptr || origin == nullptr) {
        return;
    }
    reinterpret_cast<SkPatch3D *>(patch)->fOrigin = *reinterpret_cast<const SkV3 *>(origin);
}

reskia_camera_3d_t *SkCamera3D_new(void) {
    return reinterpret_cast<reskia_camera_3d_t *>(new SkCamera3D());
}

void SkCamera3D_delete(reskia_camera_3d_t *camera) {
    delete reinterpret_cast<SkCamera3D *>(camera);
}

void SkCamera3D_reset(reskia_camera_3d_t *camera) {
    if (camera == nullptr) {
        return;
    }
    reinterpret_cast<SkCamera3D *>(camera)->reset();
}

void SkCamera3D_update(reskia_camera_3d_t *camera) {
    if (camera == nullptr) {
        return;
    }
    reinterpret_cast<SkCamera3D *>(camera)->update();
}

void SkCamera3D_patchToMatrix(const reskia_camera_3d_t *camera, const reskia_patch_3d_t *patch, reskia_matrix_t *matrix) {
    if (camera == nullptr || patch == nullptr || matrix == nullptr) {
        return;
    }
    reinterpret_cast<const SkCamera3D *>(camera)->patchToMatrix(
            *reinterpret_cast<const SkPatch3D *>(patch),
            reinterpret_cast<SkMatrix *>(matrix));
}

sk_v3_t SkCamera3D_getLocation(const reskia_camera_3d_t *camera) {
    if (camera == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<const SkCamera3D *>(camera)->fLocation);
}

sk_v3_t SkCamera3D_getAxis(const reskia_camera_3d_t *camera) {
    if (camera == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<const SkCamera3D *>(camera)->fAxis);
}

sk_v3_t SkCamera3D_getZenith(const reskia_camera_3d_t *camera) {
    if (camera == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<const SkCamera3D *>(camera)->fZenith);
}

sk_v3_t SkCamera3D_getObserver(const reskia_camera_3d_t *camera) {
    if (camera == nullptr) {
        return static_sk_v3_make({});
    }
    return static_sk_v3_make(reinterpret_cast<const SkCamera3D *>(camera)->fObserver);
}

void SkCamera3D_setLocation(reskia_camera_3d_t *camera, const reskia_v3_t *location) {
    if (camera == nullptr || location == nullptr) {
        return;
    }
    reinterpret_cast<SkCamera3D *>(camera)->fLocation = *reinterpret_cast<const SkV3 *>(location);
    reinterpret_cast<SkCamera3D *>(camera)->update();
}

void SkCamera3D_setAxis(reskia_camera_3d_t *camera, const reskia_v3_t *axis) {
    if (camera == nullptr || axis == nullptr) {
        return;
    }
    reinterpret_cast<SkCamera3D *>(camera)->fAxis = *reinterpret_cast<const SkV3 *>(axis);
    reinterpret_cast<SkCamera3D *>(camera)->update();
}

void SkCamera3D_setZenith(reskia_camera_3d_t *camera, const reskia_v3_t *zenith) {
    if (camera == nullptr || zenith == nullptr) {
        return;
    }
    reinterpret_cast<SkCamera3D *>(camera)->fZenith = *reinterpret_cast<const SkV3 *>(zenith);
    reinterpret_cast<SkCamera3D *>(camera)->update();
}

void SkCamera3D_setObserver(reskia_camera_3d_t *camera, const reskia_v3_t *observer) {
    if (camera == nullptr || observer == nullptr) {
        return;
    }
    reinterpret_cast<SkCamera3D *>(camera)->fObserver = *reinterpret_cast<const SkV3 *>(observer);
    reinterpret_cast<SkCamera3D *>(camera)->update();
}

reskia_3d_view_t *Sk3DView_new(void) {
    return reinterpret_cast<reskia_3d_view_t *>(new Sk3DView());
}

void Sk3DView_delete(reskia_3d_view_t *view) {
    delete reinterpret_cast<Sk3DView *>(view);
}

void Sk3DView_save(reskia_3d_view_t *view) {
    if (view == nullptr) {
        return;
    }
    reinterpret_cast<Sk3DView *>(view)->save();
}

void Sk3DView_restore(reskia_3d_view_t *view) {
    if (view == nullptr) {
        return;
    }
    reinterpret_cast<Sk3DView *>(view)->restore();
}

void Sk3DView_translate(reskia_3d_view_t *view, float x, float y, float z) {
    if (view == nullptr) {
        return;
    }
    reinterpret_cast<Sk3DView *>(view)->translate(x, y, z);
}

void Sk3DView_rotateX(reskia_3d_view_t *view, float degrees) {
    if (view == nullptr) {
        return;
    }
    reinterpret_cast<Sk3DView *>(view)->rotateX(degrees);
}

void Sk3DView_rotateY(reskia_3d_view_t *view, float degrees) {
    if (view == nullptr) {
        return;
    }
    reinterpret_cast<Sk3DView *>(view)->rotateY(degrees);
}

void Sk3DView_rotateZ(reskia_3d_view_t *view, float degrees) {
    if (view == nullptr) {
        return;
    }
    reinterpret_cast<Sk3DView *>(view)->rotateZ(degrees);
}

void Sk3DView_getMatrix(const reskia_3d_view_t *view, reskia_matrix_t *matrix) {
    if (view == nullptr || matrix == nullptr) {
        return;
    }
    reinterpret_cast<const Sk3DView *>(view)->getMatrix(reinterpret_cast<SkMatrix *>(matrix));
}

void Sk3DView_applyToCanvas(const reskia_3d_view_t *view, reskia_canvas_t *canvas) {
    if (view == nullptr || canvas == nullptr) {
        return;
    }
    reinterpret_cast<const Sk3DView *>(view)->applyToCanvas(reinterpret_cast<SkCanvas *>(canvas));
}

float Sk3DView_dotWithNormal(const reskia_3d_view_t *view, float dx, float dy, float dz) {
    if (view == nullptr) {
        return 0.0f;
    }
    return reinterpret_cast<const Sk3DView *>(view)->dotWithNormal(dx, dy, dz);
}

} // extern "C"
