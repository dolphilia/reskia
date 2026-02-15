//
// Created by dolphilia on 2024/01/10.
//

#include "sk_picture_recorder.h"

#include "include/core/SkPictureRecorder.h"
#include "include/core/SkBBHFactory.h"

#include "../static/static_sk_picture.h"
#include "../static/static_sk_drawable.h"
#include "../static/static_sk_b_box_hierarchy.h"

#include "../static/static_sk_picture-internal.h"
#include "../static/static_sk_drawable-internal.h"
#include "../static/static_sk_b_box_hierarchy-internal.h"

extern "C" {

reskia_picture_recorder_t *SkPictureRecorder_new() {
    return reinterpret_cast<reskia_picture_recorder_t *>(new SkPictureRecorder());
}

void SkPictureRecorder_delete(reskia_picture_recorder_t *picture_recorder) {
    delete reinterpret_cast<SkPictureRecorder *>(picture_recorder);
}

reskia_canvas_t *SkPictureRecorder_beginRecording(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, sk_b_box_hierarchy_t b_box_hierarchy) {
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkPictureRecorder *>(picture_recorder)->beginRecording(
        *reinterpret_cast<const SkRect *>(bounds),
        static_sk_b_box_hierarchy_get_entity(b_box_hierarchy)));
}

reskia_canvas_t *SkPictureRecorder_beginRecording_2(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, reskia_bbh_factory_t *bbhFactory) {
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkPictureRecorder *>(picture_recorder)->beginRecording(
        *reinterpret_cast<const SkRect *>(bounds),
        reinterpret_cast<SkBBHFactory *>(bbhFactory)));
}

reskia_canvas_t *SkPictureRecorder_beginRecording_3(reskia_picture_recorder_t *picture_recorder, float width, float height, reskia_bbh_factory_t *bbhFactory) {
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkPictureRecorder *>(picture_recorder)->beginRecording(
        width,
        height,
        reinterpret_cast<SkBBHFactory *>(bbhFactory)));
}

reskia_canvas_t *SkPictureRecorder_getRecordingCanvas(reskia_picture_recorder_t *picture_recorder) {
    return reinterpret_cast<reskia_canvas_t *>(reinterpret_cast<SkPictureRecorder *>(picture_recorder)->getRecordingCanvas());
}

sk_picture_t SkPictureRecorder_finishRecordingAsPicture(reskia_picture_recorder_t *picture_recorder) {
    return static_sk_picture_make(reinterpret_cast<SkPictureRecorder *>(picture_recorder)->finishRecordingAsPicture());
}

sk_picture_t SkPictureRecorder_finishRecordingAsPictureWithCull(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *cullRect) {
    return static_sk_picture_make(reinterpret_cast<SkPictureRecorder *>(picture_recorder)->finishRecordingAsPictureWithCull(*reinterpret_cast<const SkRect *>(cullRect)));
}

sk_drawable_t SkPictureRecorder_finishRecordingAsDrawable(reskia_picture_recorder_t *picture_recorder) {
    return static_sk_drawable_make(reinterpret_cast<SkPictureRecorder *>(picture_recorder)->finishRecordingAsDrawable());
}

}
