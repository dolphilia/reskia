//
// Created by dolphilia on 2024/01/10.
//

#include "sk_picture_recorder.h"

#include "include/core/SkPictureRecorder.h"
#include "include/core/SkBBHFactory.h"

#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_drawable.h"
#include "../handles/static_sk_b_box_hierarchy.h"

#include "../handles/static_sk_picture-internal.h"
#include "../handles/static_sk_drawable-internal.h"
#include "../handles/static_sk_b_box_hierarchy-internal.h"

#include <utility>

namespace {

SkPictureRecorder *as_picture_recorder(reskia_picture_recorder_t *picture_recorder) {
    return reinterpret_cast<SkPictureRecorder *>(picture_recorder);
}

sk_drawable_t make_drawable_handle(sk_sp<SkDrawable> drawable) {
    if (!drawable) {
        return 0;
    }
    return static_sk_drawable_make(std::move(drawable));
}

sk_picture_t make_picture_handle(sk_sp<SkPicture> picture) {
    if (!picture) {
        return 0;
    }
    return static_sk_picture_make(std::move(picture));
}

}  // namespace

extern "C" {

reskia_picture_recorder_t *SkPictureRecorder_new() {
    return reinterpret_cast<reskia_picture_recorder_t *>(new SkPictureRecorder());
}

void SkPictureRecorder_delete(reskia_picture_recorder_t *picture_recorder) {
    delete as_picture_recorder(picture_recorder);
}

reskia_canvas_t *SkPictureRecorder_beginRecording(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, sk_b_box_hierarchy_t b_box_hierarchy) {
    if (picture_recorder == nullptr || bounds == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(as_picture_recorder(picture_recorder)->beginRecording(
        *reinterpret_cast<const SkRect *>(bounds),
        static_sk_b_box_hierarchy_get_entity(b_box_hierarchy)));
}

reskia_canvas_t *SkPictureRecorder_beginRecordingWithBoundsAndFactory(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *bounds, reskia_bbh_factory_t *bbhFactory) {
    if (picture_recorder == nullptr || bounds == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(as_picture_recorder(picture_recorder)->beginRecording(
        *reinterpret_cast<const SkRect *>(bounds),
        reinterpret_cast<SkBBHFactory *>(bbhFactory)));
}

reskia_canvas_t *SkPictureRecorder_beginRecordingWithSizeAndFactory(reskia_picture_recorder_t *picture_recorder, float width, float height, reskia_bbh_factory_t *bbhFactory) {
    if (picture_recorder == nullptr || width < 0.0f || height < 0.0f) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(as_picture_recorder(picture_recorder)->beginRecording(
        width,
        height,
        reinterpret_cast<SkBBHFactory *>(bbhFactory)));
}

reskia_canvas_t *SkPictureRecorder_getRecordingCanvas(reskia_picture_recorder_t *picture_recorder) {
    if (picture_recorder == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_canvas_t *>(as_picture_recorder(picture_recorder)->getRecordingCanvas());
}

sk_picture_t SkPictureRecorder_finishRecordingAsPicture(reskia_picture_recorder_t *picture_recorder) {
    if (picture_recorder == nullptr) {
        return 0;
    }
    return make_picture_handle(as_picture_recorder(picture_recorder)->finishRecordingAsPicture());
}

sk_picture_t SkPictureRecorder_finishRecordingAsPictureWithCull(reskia_picture_recorder_t *picture_recorder, const reskia_rect_t *cullRect) {
    if (picture_recorder == nullptr || cullRect == nullptr) {
        return 0;
    }
    return make_picture_handle(as_picture_recorder(picture_recorder)->finishRecordingAsPictureWithCull(*reinterpret_cast<const SkRect *>(cullRect)));
}

sk_drawable_t SkPictureRecorder_finishRecordingAsDrawable(reskia_picture_recorder_t *picture_recorder) {
    if (picture_recorder == nullptr) {
        return 0;
    }
    return make_drawable_handle(as_picture_recorder(picture_recorder)->finishRecordingAsDrawable());
}

}
