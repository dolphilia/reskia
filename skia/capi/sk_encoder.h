//
// Created by dolphilia on 2024/02/01.
//

#ifndef RAIA_SKIA_SK_ENCODER_H
#define RAIA_SKIA_SK_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_encoder_t reskia_encoder_t;

void SkEncoder_delete(reskia_encoder_t *encoder); // NULL encoder is no-op.
bool SkEncoder_encodeRows(reskia_encoder_t *encoder, int numRows); // NULL encoder or numRows <= 0 returns false.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_ENCODER_H
