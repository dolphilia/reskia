#ifndef RAIA_SKIA_SK_NO_DRAW_CANVAS_H
#define RAIA_SKIA_SK_NO_DRAW_CANVAS_H

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_no_draw_canvas_t reskia_no_draw_canvas_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_no_draw_canvas_t *SkNoDrawCanvas_new(int width, int height);
reskia_no_draw_canvas_t *SkNoDrawCanvas_newWithIRect(const reskia_i_rect_t *rect);
void SkNoDrawCanvas_delete(reskia_no_draw_canvas_t *canvas);
reskia_canvas_t *SkNoDrawCanvas_asCanvas(reskia_no_draw_canvas_t *canvas); // borrowed
void SkNoDrawCanvas_resetCanvas(reskia_no_draw_canvas_t *canvas, int width, int height);
void SkNoDrawCanvas_resetCanvasWithIRect(reskia_no_draw_canvas_t *canvas, const reskia_i_rect_t *rect);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_NO_DRAW_CANVAS_H
