//
// Created by Codex on 2026/05/16.
//

#include "sk_animated_image.h"

#include <utility>

#include "include/android/SkAnimatedImage.h"
#include "include/codec/SkAndroidCodec.h"
#include "include/core/SkImage.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkPicture.h"
#include "include/core/SkRect.h"

#include "../handles/static_sk_android_codec-internal.h"
#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_picture-internal.h"

namespace {

SkAnimatedImage *as_animated_image(const reskia_animated_image_t *animated_image) {
    return const_cast<SkAnimatedImage *>(
            reinterpret_cast<const SkAnimatedImage *>(animated_image));
}

reskia_animated_image_t *to_animated_image(sk_sp<SkAnimatedImage> animated_image) {
    if (!animated_image) {
        return nullptr;
    }
    return reinterpret_cast<reskia_animated_image_t *>(animated_image.release());
}

}  // namespace

extern "C" {

reskia_animated_image_t *SkAnimatedImage_Make(sk_android_codec_t codec) {
    if (codec == 0) {
        return nullptr;
    }
    std::unique_ptr<SkAndroidCodec> android_codec = static_sk_android_codec_take_entity(codec);
    if (!android_codec) {
        return nullptr;
    }
    return to_animated_image(SkAnimatedImage::Make(std::move(android_codec)));
}

reskia_animated_image_t *SkAnimatedImage_MakeWithInfo(sk_android_codec_t codec, const reskia_image_info_t *info, const reskia_i_rect_t *crop_rect, sk_picture_t post_process) {
    if (codec == 0 || info == nullptr || crop_rect == nullptr) {
        return nullptr;
    }
    std::unique_ptr<SkAndroidCodec> android_codec = static_sk_android_codec_take_entity(codec);
    if (!android_codec) {
        return nullptr;
    }
    sk_sp<SkPicture> picture = post_process == 0 ? nullptr : static_sk_picture_get_entity(post_process);
    return to_animated_image(SkAnimatedImage::Make(
            std::move(android_codec),
            *reinterpret_cast<const SkImageInfo *>(info),
            *reinterpret_cast<const SkIRect *>(crop_rect),
            std::move(picture)));
}

void SkAnimatedImage_delete(reskia_animated_image_t *animated_image) {
    if (animated_image == nullptr) {
        return;
    }
    as_animated_image(animated_image)->unref();
}

void SkAnimatedImage_reset(reskia_animated_image_t *animated_image) {
    if (animated_image == nullptr) {
        return;
    }
    as_animated_image(animated_image)->reset();
}

bool SkAnimatedImage_isFinished(const reskia_animated_image_t *animated_image) {
    return animated_image != nullptr && as_animated_image(animated_image)->isFinished();
}

int SkAnimatedImage_decodeNextFrame(reskia_animated_image_t *animated_image) {
    if (animated_image == nullptr) {
        return SkAnimatedImage::kFinished;
    }
    return as_animated_image(animated_image)->decodeNextFrame();
}

sk_image_t SkAnimatedImage_getCurrentFrame(reskia_animated_image_t *animated_image) {
    if (animated_image == nullptr) {
        return 0;
    }
    sk_sp<SkImage> image = as_animated_image(animated_image)->getCurrentFrame();
    if (!image) {
        return 0;
    }
    return static_sk_image_make(std::move(image));
}

int SkAnimatedImage_currentFrameDuration(reskia_animated_image_t *animated_image) {
    if (animated_image == nullptr) {
        return SkAnimatedImage::kFinished;
    }
    return as_animated_image(animated_image)->currentFrameDuration();
}

void SkAnimatedImage_setRepetitionCount(reskia_animated_image_t *animated_image, int count) {
    if (animated_image == nullptr) {
        return;
    }
    as_animated_image(animated_image)->setRepetitionCount(count);
}

int SkAnimatedImage_getRepetitionCount(const reskia_animated_image_t *animated_image) {
    if (animated_image == nullptr) {
        return 0;
    }
    return as_animated_image(animated_image)->getRepetitionCount();
}

int SkAnimatedImage_getFrameCount(const reskia_animated_image_t *animated_image) {
    if (animated_image == nullptr) {
        return 0;
    }
    return as_animated_image(animated_image)->getFrameCount();
}

}
