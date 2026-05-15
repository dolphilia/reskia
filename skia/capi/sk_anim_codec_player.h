#ifndef RAIA_SKIA_SK_ANIM_CODEC_PLAYER_H
#define RAIA_SKIA_SK_ANIM_CODEC_PLAYER_H

#include <stdint.h>
#include <stdbool.h>

#include "../handles/static_sk_codec.h"
#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_image.h"

typedef struct reskia_anim_codec_player_t reskia_anim_codec_player_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_anim_codec_player_t *SkAnimCodecPlayer_new(sk_codec_t codec); // codec handle is consumed.
void SkAnimCodecPlayer_delete(reskia_anim_codec_player_t *player);
sk_image_t SkAnimCodecPlayer_getFrame(reskia_anim_codec_player_t *player);
sk_i_size_t SkAnimCodecPlayer_dimensions(const reskia_anim_codec_player_t *player);
uint32_t SkAnimCodecPlayer_duration(const reskia_anim_codec_player_t *player);
bool SkAnimCodecPlayer_seek(reskia_anim_codec_player_t *player, uint32_t msec);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_ANIM_CODEC_PLAYER_H
