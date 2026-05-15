#ifndef RAIA_SKIA_SK_CAMERA_H
#define RAIA_SKIA_SK_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../handles/static_sk_v3.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_camera_3d_t reskia_camera_3d_t;
typedef struct reskia_m_44_t reskia_m_44_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_patch_3d_t reskia_patch_3d_t;
typedef struct reskia_v3_t reskia_v3_t;
typedef struct reskia_3d_view_t reskia_3d_view_t;

reskia_patch_3d_t *SkPatch3D_new(void);
void SkPatch3D_delete(reskia_patch_3d_t *patch);
void SkPatch3D_reset(reskia_patch_3d_t *patch);
void SkPatch3D_transform(const reskia_patch_3d_t *patch, const reskia_m_44_t *matrix, reskia_patch_3d_t *dst);
float SkPatch3D_dotWith(const reskia_patch_3d_t *patch, float dx, float dy, float dz);
float SkPatch3D_dotWithV3(const reskia_patch_3d_t *patch, const reskia_v3_t *v);
void SkPatch3D_rotate(reskia_patch_3d_t *patch, float x, float y, float z);
void SkPatch3D_rotateDegrees(reskia_patch_3d_t *patch, float x, float y, float z);
sk_v3_t SkPatch3D_getU(const reskia_patch_3d_t *patch);
sk_v3_t SkPatch3D_getV(const reskia_patch_3d_t *patch);
sk_v3_t SkPatch3D_getOrigin(const reskia_patch_3d_t *patch);
void SkPatch3D_setU(reskia_patch_3d_t *patch, const reskia_v3_t *u);
void SkPatch3D_setV(reskia_patch_3d_t *patch, const reskia_v3_t *v);
void SkPatch3D_setOrigin(reskia_patch_3d_t *patch, const reskia_v3_t *origin);

reskia_camera_3d_t *SkCamera3D_new(void);
void SkCamera3D_delete(reskia_camera_3d_t *camera);
void SkCamera3D_reset(reskia_camera_3d_t *camera);
void SkCamera3D_update(reskia_camera_3d_t *camera);
void SkCamera3D_patchToMatrix(const reskia_camera_3d_t *camera, const reskia_patch_3d_t *patch, reskia_matrix_t *matrix);
sk_v3_t SkCamera3D_getLocation(const reskia_camera_3d_t *camera);
sk_v3_t SkCamera3D_getAxis(const reskia_camera_3d_t *camera);
sk_v3_t SkCamera3D_getZenith(const reskia_camera_3d_t *camera);
sk_v3_t SkCamera3D_getObserver(const reskia_camera_3d_t *camera);
void SkCamera3D_setLocation(reskia_camera_3d_t *camera, const reskia_v3_t *location);
void SkCamera3D_setAxis(reskia_camera_3d_t *camera, const reskia_v3_t *axis);
void SkCamera3D_setZenith(reskia_camera_3d_t *camera, const reskia_v3_t *zenith);
void SkCamera3D_setObserver(reskia_camera_3d_t *camera, const reskia_v3_t *observer);

reskia_3d_view_t *Sk3DView_new(void);
void Sk3DView_delete(reskia_3d_view_t *view);
void Sk3DView_save(reskia_3d_view_t *view);
void Sk3DView_restore(reskia_3d_view_t *view);
void Sk3DView_translate(reskia_3d_view_t *view, float x, float y, float z);
void Sk3DView_rotateX(reskia_3d_view_t *view, float degrees);
void Sk3DView_rotateY(reskia_3d_view_t *view, float degrees);
void Sk3DView_rotateZ(reskia_3d_view_t *view, float degrees);
void Sk3DView_getMatrix(const reskia_3d_view_t *view, reskia_matrix_t *matrix);
void Sk3DView_applyToCanvas(const reskia_3d_view_t *view, reskia_canvas_t *canvas);
float Sk3DView_dotWithNormal(const reskia_3d_view_t *view, float dx, float dy, float dz);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_CAMERA_H
