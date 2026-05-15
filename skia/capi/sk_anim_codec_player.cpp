#include "sk_anim_codec_player.h"

#include "include/core/SkImage.h"
#include "include/core/SkSize.h"
#include "include/utils/SkAnimCodecPlayer.h"

#include "../handles/static_sk_codec-internal.h"
#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_image-internal.h"

extern "C" {

reskia_anim_codec_player_t *SkAnimCodecPlayer_new(sk_codec_t codec) {
    if (codec == 0 || static_sk_codec_borrow_entity(codec) == nullptr) {
        return nullptr;
    }
    std::unique_ptr<SkCodec> owned_codec = static_sk_codec_take_entity(codec);
    if (!owned_codec) {
        return nullptr;
    }
    return reinterpret_cast<reskia_anim_codec_player_t *>(
            new SkAnimCodecPlayer(std::move(owned_codec)));
}

void SkAnimCodecPlayer_delete(reskia_anim_codec_player_t *player) {
    delete reinterpret_cast<SkAnimCodecPlayer *>(player);
}

sk_image_t SkAnimCodecPlayer_getFrame(reskia_anim_codec_player_t *player) {
    if (player == nullptr) {
        return 0;
    }
    sk_sp<SkImage> image = reinterpret_cast<SkAnimCodecPlayer *>(player)->getFrame();
    return image ? static_sk_image_make(std::move(image)) : 0;
}

sk_i_size_t SkAnimCodecPlayer_dimensions(const reskia_anim_codec_player_t *player) {
    if (player == nullptr) {
        return 0;
    }
    return static_sk_i_size_make(reinterpret_cast<const SkAnimCodecPlayer *>(player)->dimensions());
}

uint32_t SkAnimCodecPlayer_duration(const reskia_anim_codec_player_t *player) {
    return player != nullptr ? reinterpret_cast<const SkAnimCodecPlayer *>(player)->duration() : 0;
}

bool SkAnimCodecPlayer_seek(reskia_anim_codec_player_t *player, uint32_t msec) {
    return player != nullptr && reinterpret_cast<SkAnimCodecPlayer *>(player)->seek(msec);
}

} // extern "C"
