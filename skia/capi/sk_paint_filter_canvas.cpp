#include "sk_paint_filter_canvas.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"
#include "include/utils/SkPaintFilterCanvas.h"

#include "../handles/static_sk_i_size-internal.h"

namespace {

class ReskiaPaintFilterCanvas final : public SkPaintFilterCanvas {
public:
    ReskiaPaintFilterCanvas(
            SkCanvas *canvas,
            reskia_paint_filter_canvas_filter_proc_t filter_proc,
            void *user_data,
            reskia_callback_release_proc_t release_proc)
        : SkPaintFilterCanvas(canvas)
        , filter_proc_(filter_proc)
        , user_data_(user_data)
        , release_proc_(release_proc) {}

    ~ReskiaPaintFilterCanvas() override {
        if (release_proc_ != nullptr) {
            release_proc_(user_data_);
        }
    }

protected:
    bool onFilter(SkPaint& paint) const override {
        if (filter_proc_ == nullptr) {
            return true;
        }
        return filter_proc_(reinterpret_cast<reskia_paint_t *>(&paint), user_data_);
    }

private:
    reskia_paint_filter_canvas_filter_proc_t filter_proc_;
    void *user_data_;
    reskia_callback_release_proc_t release_proc_;
};

} // namespace

extern "C" {

reskia_paint_filter_canvas_t *SkPaintFilterCanvas_new(
        reskia_canvas_t *canvas,
        reskia_paint_filter_canvas_filter_proc_t filter_proc,
        void *user_data,
        reskia_callback_release_proc_t release_proc) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paint_filter_canvas_t *>(new ReskiaPaintFilterCanvas(
            reinterpret_cast<SkCanvas *>(canvas),
            filter_proc,
            user_data,
            release_proc));
}

void SkPaintFilterCanvas_delete(reskia_paint_filter_canvas_t *canvas) {
    delete reinterpret_cast<SkPaintFilterCanvas *>(canvas);
}

reskia_canvas_t *SkPaintFilterCanvas_asCanvas(reskia_paint_filter_canvas_t *canvas) {
    if (canvas == nullptr) {
        return nullptr;
    }
    auto *native = reinterpret_cast<SkPaintFilterCanvas *>(canvas);
    return reinterpret_cast<reskia_canvas_t *>(static_cast<SkCanvas *>(native));
}

sk_i_size_t SkPaintFilterCanvas_getBaseLayerSize(reskia_paint_filter_canvas_t *canvas) {
    if (canvas == nullptr) {
        return 0;
    }
    return static_sk_i_size_make(reinterpret_cast<SkPaintFilterCanvas *>(canvas)->getBaseLayerSize());
}

reskia_recording_context_t *SkPaintFilterCanvas_recordingContext(reskia_paint_filter_canvas_t *canvas) {
    if (canvas == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_recording_context_t *>(
            reinterpret_cast<SkPaintFilterCanvas *>(canvas)->recordingContext());
}

} // extern "C"
