#include "sk_skottie.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkRect.h"
#include "modules/skottie/include/Skottie.h"

namespace {

inline skottie::Animation *to_animation(reskia_skottie_animation_t *animation) {
    return reinterpret_cast<skottie::Animation *>(animation);
}

inline const skottie::Animation *to_animation(const reskia_skottie_animation_t *animation) {
    return reinterpret_cast<const skottie::Animation *>(animation);
}

} // namespace

extern "C" {

reskia_skottie_animation_t *Skottie_Animation_Make(const char *data, size_t length) {
    if (data == nullptr || length == 0) {
        return nullptr;
    }
    auto animation = skottie::Animation::Make(data, length);
    return reinterpret_cast<reskia_skottie_animation_t *>(animation.release());
}

reskia_skottie_animation_t *Skottie_Animation_MakeFromFile(const char path[]) {
    if (path == nullptr) {
        return nullptr;
    }
    auto animation = skottie::Animation::MakeFromFile(path);
    return reinterpret_cast<reskia_skottie_animation_t *>(animation.release());
}

void Skottie_Animation_release(reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return;
    }
    to_animation(animation)->unref();
}

void Skottie_Animation_ref(reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return;
    }
    to_animation(animation)->ref();
}

void Skottie_Animation_unref(reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return;
    }
    to_animation(animation)->unref();
}

bool Skottie_Animation_seek(reskia_skottie_animation_t *animation, float t) {
    if (animation == nullptr) {
        return false;
    }
    to_animation(animation)->seek(t);
    return true;
}

bool Skottie_Animation_seekFrameTime(reskia_skottie_animation_t *animation, double t) {
    if (animation == nullptr) {
        return false;
    }
    to_animation(animation)->seekFrameTime(t);
    return true;
}

void Skottie_Animation_render(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst) {
    if (animation == nullptr || canvas == nullptr) {
        return;
    }
    to_animation(animation)->render(
            reinterpret_cast<SkCanvas *>(canvas),
            reinterpret_cast<const SkRect *>(dst)
    );
}

void Skottie_Animation_renderWithFlags(reskia_skottie_animation_t *animation, reskia_canvas_t *canvas, const reskia_rect_t *dst, uint32_t flags) {
    if (animation == nullptr || canvas == nullptr) {
        return;
    }
    to_animation(animation)->render(
            reinterpret_cast<SkCanvas *>(canvas),
            reinterpret_cast<const SkRect *>(dst),
            flags
    );
}

double Skottie_Animation_duration(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0;
    }
    return to_animation(animation)->duration();
}

double Skottie_Animation_fps(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0;
    }
    return to_animation(animation)->fps();
}

float Skottie_Animation_width(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0f;
    }
    return to_animation(animation)->size().width();
}

float Skottie_Animation_height(const reskia_skottie_animation_t *animation) {
    if (animation == nullptr) {
        return 0.0f;
    }
    return to_animation(animation)->size().height();
}

} // extern "C"
