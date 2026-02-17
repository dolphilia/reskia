#ifndef RAIA_SKIA_SK_SKSG_H
#define RAIA_SKIA_SK_SKSG_H

#include <stdbool.h>

#include "sk_color.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_sksg_scene_t reskia_sksg_scene_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_sksg_scene_t *SkSG_Scene_MakeSimpleRect(float x, float y, float width, float height, reskia_color_t color);

void SkSG_Scene_release(reskia_sksg_scene_t *scene);
void SkSG_Scene_ref(reskia_sksg_scene_t *scene);
void SkSG_Scene_unref(reskia_sksg_scene_t *scene);

bool SkSG_Scene_revalidate(reskia_sksg_scene_t *scene);
bool SkSG_Scene_render(reskia_sksg_scene_t *scene, reskia_canvas_t *canvas);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_SKSG_H
