//
// Created by dolphilia on 2024/02/02.
//

#ifndef RAIA_SKIA_SK_PNG_DECODER_H
#define RAIA_SKIA_SK_PNG_DECODER_H

#ifdef __cplusplus
extern "C" {
#endif

bool SkPngDecoder_IsPng(const void* ptr, unsigned long size); // (const void* ptr, size_t size) -> bool
int SkPngDecoder_Decode(int static_stream, void * result, void * decodeContext); // (int static_stream, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
int SkPngDecoder_Decode_2(int static_data, void * result, void * decodeContext); // (int static_data, SkCodec::Result* result, SkCodecs::DecodeContext decodeContext) -> sk_codec_t
int SkPngDecoder_Decoder(); // () -> sk_codecs_decoder_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PNG_DECODER_H
