#ifndef RAIA_SKIA_SK_NWAY_CANVAS_H
#define RAIA_SKIA_SK_NWAY_CANVAS_H

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_nway_canvas_t reskia_nway_canvas_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_nway_canvas_t *SkNWayCanvas_new(int width, int height);
void SkNWayCanvas_delete(reskia_nway_canvas_t *canvas);
reskia_canvas_t *SkNWayCanvas_asCanvas(reskia_nway_canvas_t *canvas); // borrowed
void SkNWayCanvas_addCanvas(reskia_nway_canvas_t *canvas, reskia_canvas_t *target); // target is borrowed; caller must keep it alive while registered.
void SkNWayCanvas_removeCanvas(reskia_nway_canvas_t *canvas, reskia_canvas_t *target);
void SkNWayCanvas_removeAll(reskia_nway_canvas_t *canvas);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_NWAY_CANVAS_H
