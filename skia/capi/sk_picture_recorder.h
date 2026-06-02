//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PICTURE_RECORDER_H
#define RAIA_SKIA_SK_PICTURE_RECORDER_H

#include <stdint.h>

#include "../handles/static_sk_drawable.h"
#include "../handles/static_sk_picture.h"

typedef struct reskia_bbh_factory_t reskia_bbh_factory_t;
typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_picture_recorder_t reskia_picture_recorder_t;
typedef struct reskia_rect_t reskia_rect_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_picture_recorder_t *SkPictureRecorder_new(); // () -> SkPictureRecorder *
void SkPictureRecorder_delete(reskia_picture_recorder_t *picture_recorder); // No-op for NULL input.
/**
 * bounds must be non-NULL.
 * Returns NULL for invalid input. Returned canvas is borrowed.
 */
reskia_canvas_t *SkPictureRecorder_beginRecording(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, int b_box_hierarchy);
/**
 * bounds must be non-NULL, and bbhFactory may be NULL.
 * Returns NULL for invalid input.
 */
reskia_canvas_t *SkPictureRecorder_beginRecordingWithBoundsAndFactory(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, reskia_bbh_factory_t *bbhFactory);
/**
 * width and height must be >= 0. bbhFactory may be NULL.
 * Returns NULL for invalid input.
 */
reskia_canvas_t *SkPictureRecorder_beginRecordingWithSizeAndFactory(reskia_picture_recorder_t *picture_recorder, float width, float height, reskia_bbh_factory_t *bbhFactory);
reskia_canvas_t *SkPictureRecorder_getRecordingCanvas(reskia_picture_recorder_t *picture_recorder); // Returns NULL for NULL input or when not recording. Returned canvas is borrowed.
sk_picture_t SkPictureRecorder_finishRecordingAsPicture(reskia_picture_recorder_t *picture_recorder); // Returns 0 for NULL input or creation failure.
/**
 * cullRect must be non-NULL.
 * Returns 0 for invalid input or creation failure.
 */
sk_picture_t SkPictureRecorder_finishRecordingAsPictureWithCull(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *cullRect);
sk_drawable_t SkPictureRecorder_finishRecordingAsDrawable(reskia_picture_recorder_t *picture_recorder); // Returns 0 for NULL input or creation failure.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PICTURE_RECORDER_H
