#ifndef RAIA_SKIA_SK_PAINT_FILTER_CANVAS_H
#define RAIA_SKIA_SK_PAINT_FILTER_CANVAS_H

#include "reskia_callback.h"
#include "../handles/static_sk_i_size.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_paint_filter_canvas_t reskia_paint_filter_canvas_t;
typedef struct reskia_recording_context_t reskia_recording_context_t;

typedef bool (*reskia_paint_filter_canvas_filter_proc_t)(
        reskia_paint_t *paint,
        void *user_data);

reskia_paint_filter_canvas_t *SkPaintFilterCanvas_new(reskia_canvas_t *canvas, reskia_paint_filter_canvas_filter_proc_t filter_proc, void *user_data, reskia_callback_release_proc_t release_proc);
void SkPaintFilterCanvas_delete(reskia_paint_filter_canvas_t *canvas);
reskia_canvas_t *SkPaintFilterCanvas_asCanvas(reskia_paint_filter_canvas_t *canvas); // borrowed view
sk_i_size_t SkPaintFilterCanvas_getBaseLayerSize(reskia_paint_filter_canvas_t *canvas);
reskia_recording_context_t *SkPaintFilterCanvas_recordingContext(reskia_paint_filter_canvas_t *canvas); // borrowed; NULL when unavailable

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PAINT_FILTER_CANVAS_H
