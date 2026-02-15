//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PICTURE_RECORDER_H
#define RAIA_SKIA_SK_PICTURE_RECORDER_H

#include <stdint.h>

typedef struct reskia_bbh_factory_t reskia_bbh_factory_t;
typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_picture_recorder_t reskia_picture_recorder_t;
typedef struct reskia_rect_t reskia_rect_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_picture_recorder_t *SkPictureRecorder_new(); // () -> SkPictureRecorder *
void SkPictureRecorder_delete(reskia_picture_recorder_t *picture_recorder); // (SkPictureRecorder *picture_recorder)
reskia_canvas_t *SkPictureRecorder_beginRecording(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, int b_box_hierarchy); // (SkPictureRecorder *picture_recorder, const SkRect *bounds, sk_b_box_hierarchy_t b_box_hierarchy) -> SkCanvas *
reskia_canvas_t *SkPictureRecorder_beginRecording_2(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, reskia_bbh_factory_t *bbhFactory); // (SkPictureRecorder *picture_recorder, const SkRect *bounds, SkBBHFactory *bbhFactory) -> SkCanvas *
reskia_canvas_t *SkPictureRecorder_beginRecording_3(reskia_picture_recorder_t *picture_recorder, float width, float height, reskia_bbh_factory_t *bbhFactory); // (SkPictureRecorder *picture_recorder, SkScalar width, SkScalar height, SkBBHFactory *bbhFactory) -> SkCanvas *
reskia_canvas_t *SkPictureRecorder_getRecordingCanvas(reskia_picture_recorder_t *picture_recorder); // (SkPictureRecorder *picture_recorder) -> SkCanvas *
int SkPictureRecorder_finishRecordingAsPicture(reskia_picture_recorder_t *picture_recorder); // (SkPictureRecorder *picture_recorder) -> sk_picture_t
int SkPictureRecorder_finishRecordingAsPictureWithCull(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *cullRect); // (SkPictureRecorder *picture_recorder, const SkRect *cullRect) -> sk_picture_t
int SkPictureRecorder_finishRecordingAsDrawable(reskia_picture_recorder_t *picture_recorder); // (SkPictureRecorder *picture_recorder) -> sk_drawable_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PICTURE_RECORDER_H
