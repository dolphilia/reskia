//
// Created by dolphilia on 2024/01/05.
//

#ifndef RAIA_SKIA_SK_ANNOTATION_H
#define RAIA_SKIA_SK_ANNOTATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_rect_t reskia_rect_t;

void SkAnnotation_SkAnnotateLinkToDestination(reskia_canvas_t *canvas, const reskia_rect_t *rect, reskia_data_t *data); // borrowed: all inputs are borrowed only (SkCanvas *canvas, const SkRect *rect, SkData *data)
void SkAnnotation_SkAnnotateNamedDestination(reskia_canvas_t *canvas, const reskia_point_t *point, reskia_data_t *data); // borrowed: all inputs are borrowed only (SkCanvas *canvas, const SkPoint *point, SkData *data)
void SkAnnotation_SkAnnotateRectWithURL(reskia_canvas_t *canvas, const reskia_rect_t *rect, reskia_data_t *data); // borrowed: all inputs are borrowed only (SkCanvas *canvas, const SkRect *rect, SkData *data)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ANNOTATION_H
