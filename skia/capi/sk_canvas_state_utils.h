#ifndef RAIA_SKIA_SK_CANVAS_STATE_UTILS_H
#define RAIA_SKIA_SK_CANVAS_STATE_UTILS_H

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_canvas_state_t reskia_canvas_state_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_canvas_state_t *SkCanvasStateUtils_CaptureCanvasState(reskia_canvas_t *canvas);
reskia_canvas_t *SkCanvasStateUtils_MakeFromCanvasState(const reskia_canvas_state_t *state); // returned canvas is owned; delete with SkCanvas_delete.
void SkCanvasStateUtils_ReleaseCanvasState(reskia_canvas_state_t *state);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_CANVAS_STATE_UTILS_H
