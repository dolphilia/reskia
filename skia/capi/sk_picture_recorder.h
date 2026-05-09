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
void SkPictureRecorder_delete(reskia_picture_recorder_t *picture_recorder); // NULL 入力では no-op
reskia_canvas_t *SkPictureRecorder_beginRecording(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, int b_box_hierarchy); // bounds は非 NULL。invalid 入力では NULL。戻り値は borrowed canvas
reskia_canvas_t *SkPictureRecorder_beginRecordingWithBoundsAndFactory(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, reskia_bbh_factory_t *bbhFactory); // bounds は非 NULL、bbhFactory は NULL 許可。invalid 入力では NULL
reskia_canvas_t *SkPictureRecorder_beginRecordingWithSizeAndFactory(reskia_picture_recorder_t *picture_recorder, float width, float height, reskia_bbh_factory_t *bbhFactory); // width/height >= 0。bbhFactory は NULL 許可。invalid 入力では NULL
reskia_canvas_t *SkPictureRecorder_getRecordingCanvas(reskia_picture_recorder_t *picture_recorder); // NULL 入力や未 recording では NULL。戻り値は borrowed canvas
sk_picture_t SkPictureRecorder_finishRecordingAsPicture(reskia_picture_recorder_t *picture_recorder); // NULL 入力や生成不能では 0
sk_picture_t SkPictureRecorder_finishRecordingAsPictureWithCull(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *cullRect); // cullRect は非 NULL。invalid 入力や生成不能では 0
sk_drawable_t SkPictureRecorder_finishRecordingAsDrawable(reskia_picture_recorder_t *picture_recorder); // NULL 入力や生成不能では 0

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PICTURE_RECORDER_H
