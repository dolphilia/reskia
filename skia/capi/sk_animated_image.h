//
// Created by Codex on 2026/05/16.
//

#ifndef RAIA_SKIA_SK_ANIMATED_IMAGE_H
#define RAIA_SKIA_SK_ANIMATED_IMAGE_H

#include <stdbool.h>

#include "../handles/static_sk_android_codec.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_picture.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_animated_image_t reskia_animated_image_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_info_t reskia_image_info_t;

reskia_animated_image_t *SkAnimatedImage_Make(sk_android_codec_t codec);
reskia_animated_image_t *SkAnimatedImage_MakeWithInfo(sk_android_codec_t codec, const reskia_image_info_t *info, const reskia_i_rect_t *crop_rect, sk_picture_t post_process);
void SkAnimatedImage_delete(reskia_animated_image_t *animated_image);
void SkAnimatedImage_reset(reskia_animated_image_t *animated_image);
bool SkAnimatedImage_isFinished(const reskia_animated_image_t *animated_image);
int SkAnimatedImage_decodeNextFrame(reskia_animated_image_t *animated_image);
sk_image_t SkAnimatedImage_getCurrentFrame(reskia_animated_image_t *animated_image);
int SkAnimatedImage_currentFrameDuration(reskia_animated_image_t *animated_image);
void SkAnimatedImage_setRepetitionCount(reskia_animated_image_t *animated_image, int count);
int SkAnimatedImage_getRepetitionCount(const reskia_animated_image_t *animated_image);
int SkAnimatedImage_getFrameCount(const reskia_animated_image_t *animated_image);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ANIMATED_IMAGE_H
