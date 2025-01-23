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

void *SkPictureRecorder_new() {
    return new SkPictureRecorder();
}

void SkPictureRecorder_delete(void *picture_recorder) {
    delete static_cast<SkPictureRecorder *>(picture_recorder);
}

void *SkPictureRecorder_beginRecording(void *picture_recorder, const void *bounds, sk_b_box_hierarchy_t b_box_hierarchy) {
    return static_cast<SkPictureRecorder *>(picture_recorder)->beginRecording(* static_cast<const SkRect *>(bounds), static_sk_b_box_hierarchy_move(b_box_hierarchy));
}

void * SkPictureRecorder_beginRecording_2(void *picture_recorder, const void *bounds, void *bbhFactory) {
    return static_cast<SkPictureRecorder *>(picture_recorder)->beginRecording(* static_cast<const SkRect *>(bounds), static_cast<SkBBHFactory *>(bbhFactory));
}

void * SkPictureRecorder_beginRecording_3(void *picture_recorder, float width, float height, void *bbhFactory) {
    return static_cast<SkPictureRecorder *>(picture_recorder)->beginRecording(width, height, static_cast<SkBBHFactory *>(bbhFactory));
}

void * SkPictureRecorder_getRecordingCanvas(void *picture_recorder) {
    return static_cast<SkPictureRecorder *>(picture_recorder)->getRecordingCanvas();
}

sk_picture_t SkPictureRecorder_finishRecordingAsPicture(void *picture_recorder) {
    return static_sk_picture_make(static_cast<SkPictureRecorder *>(picture_recorder)->finishRecordingAsPicture());
}

sk_picture_t SkPictureRecorder_finishRecordingAsPictureWithCull(void *picture_recorder, const void *cullRect) {
    return static_sk_picture_make(static_cast<SkPictureRecorder *>(picture_recorder)->finishRecordingAsPictureWithCull(* static_cast<const SkRect *>(cullRect)));
}

sk_drawable_t SkPictureRecorder_finishRecordingAsDrawable(void *picture_recorder) {
    return static_sk_drawable_make(static_cast<SkPictureRecorder *>(picture_recorder)->finishRecordingAsDrawable());
}

}