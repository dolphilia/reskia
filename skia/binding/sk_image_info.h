//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_IMAGE_INFO_H
#define RAIA_SKIA_SK_IMAGE_INFO_H

#include <stddef.h>
#include <stdint.h>
#include "../static/static_sk_color_info.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_i_rect.h"
#include "../static/static_sk_i_size.h"
#include "../static/static_sk_image_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_color_info_t reskia_color_info_t;
typedef struct reskia_color_space_t reskia_color_space_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_i_size_t reskia_i_size_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef uint64_t reskia_u64_t;
typedef int32_t reskia_image_info_color_type_t;
typedef int32_t reskia_image_info_alpha_type_t;

//bool operator==(const SkImageInfo &other)
//bool operator!=(const SkImageInfo &other)
reskia_image_info_t *SkImageInfo_new(); // () -> SkImageInfo *
void SkImageInfo_delete(reskia_image_info_t *image_info); // (SkImageInfo *image_info)
int SkImageInfo_width(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> int
int SkImageInfo_height(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> int
reskia_image_info_color_type_t SkImageInfo_colorType(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> SkColorType
reskia_image_info_alpha_type_t SkImageInfo_alphaType(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> SkAlphaType
reskia_color_space_t *SkImageInfo_colorSpace(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> SkColorSpace *
sk_color_space_t SkImageInfo_refColorSpace(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> sk_color_space_t
bool SkImageInfo_isEmpty(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> bool
sk_color_info_t SkImageInfo_colorInfo(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> sk_color_info_t
bool SkImageInfo_isOpaque(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> bool
sk_i_size_t SkImageInfo_dimensions(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> sk_i_size_t
sk_i_rect_t SkImageInfo_bounds(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> sk_i_rect_t
bool SkImageInfo_gammaCloseToSRGB(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> bool
sk_image_info_t SkImageInfo_makeWH(reskia_image_info_t *image_info, int newWidth, int newHeight); // (SkImageInfo *image_info, int newWidth, int newHeight) -> sk_image_info_t
sk_image_info_t SkImageInfo_makeDimensions(reskia_image_info_t *image_info, sk_i_size_t newSize); // (SkImageInfo *image_info, sk_i_size_t newSize) -> sk_image_info_t
sk_image_info_t SkImageInfo_makeAlphaType(reskia_image_info_t *image_info, reskia_image_info_alpha_type_t newAlphaType); // (SkImageInfo *image_info, SkAlphaType newAlphaType) -> sk_image_info_t
sk_image_info_t SkImageInfo_makeColorType(reskia_image_info_t *image_info, reskia_image_info_color_type_t newColorType); // (SkImageInfo *image_info, SkColorType newColorType) -> sk_image_info_t
sk_image_info_t SkImageInfo_makeColorSpace(reskia_image_info_t *image_info, sk_color_space_t color_space); // (SkImageInfo *image_info, sk_color_space_t color_space) -> sk_image_info_t
int SkImageInfo_bytesPerPixel(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> int
int SkImageInfo_shiftPerPixel(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> int
reskia_u64_t SkImageInfo_minRowBytes64(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> uint64_t
size_t SkImageInfo_minRowBytes(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> size_t
size_t SkImageInfo_computeOffset(reskia_image_info_t *image_info, int x, int y, size_t rowBytes); // (SkImageInfo *image_info, int x, int y, size_t rowBytes) -> size_t
size_t SkImageInfo_computeByteSize(reskia_image_info_t *image_info, size_t rowBytes); // (SkImageInfo *image_info, size_t rowBytes) -> size_t
size_t SkImageInfo_computeMinByteSize(reskia_image_info_t *image_info); // (SkImageInfo *image_info) -> size_t
bool SkImageInfo_validRowBytes(reskia_image_info_t *image_info, size_t rowBytes); // (SkImageInfo *image_info, size_t rowBytes) -> bool
void SkImageInfo_reset(reskia_image_info_t *image_info); // (SkImageInfo *image_info)

// static

sk_image_info_t SkImageInfo_Make(int width, int height, reskia_image_info_color_type_t ct, reskia_image_info_alpha_type_t at); // (int width, int height, SkColorType ct, SkAlphaType at) -> sk_image_info_t
sk_image_info_t SkImageInfo_Make_2(int width, int height, reskia_image_info_color_type_t ct, reskia_image_info_alpha_type_t at, sk_color_space_t color_space); // (int width, int height, SkColorType ct, SkAlphaType at, sk_color_space_t color_space) -> sk_image_info_t
sk_image_info_t SkImageInfo_Make_3(sk_i_size_t dimensions, reskia_image_info_color_type_t ct, reskia_image_info_alpha_type_t at); // (sk_i_size_t dimensions, SkColorType ct, SkAlphaType at) -> sk_image_info_t
sk_image_info_t SkImageInfo_Make_4(sk_i_size_t dimensions, reskia_image_info_color_type_t ct, reskia_image_info_alpha_type_t at, sk_color_space_t color_space); // (sk_i_size_t dimensions, SkColorType ct, SkAlphaType at, sk_color_space_t color_space) -> sk_image_info_t
sk_image_info_t SkImageInfo_Make_5(sk_i_size_t dimensions, const reskia_color_info_t *colorInfo); // (sk_i_size_t dimensions, const SkColorInfo *colorInfo) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeN32(int width, int height, reskia_image_info_alpha_type_t at); // (int width, int height, SkAlphaType at) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeN32_2(int width, int height, reskia_image_info_alpha_type_t at, sk_color_space_t color_space); // (int width, int height, SkAlphaType at, sk_color_space_t color_space) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeS32(int width, int height, reskia_image_info_alpha_type_t at); // (int width, int height, SkAlphaType at) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeN32Premul(int width, int height); // (int width, int height) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeN32Premul_2(int width, int height, sk_color_space_t color_space); // (int width, int height, sk_color_space_t color_space) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeN32Premul_3(sk_i_size_t dimensions); // (sk_i_size_t dimensions) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeN32Premul_4(sk_i_size_t dimensions, sk_color_space_t color_space); // (sk_i_size_t dimensions, sk_color_space_t color_space) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeA8(int width, int height); // (int width, int height) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeA8_2(sk_i_size_t dimensions); // (sk_i_size_t dimensions) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeUnknown(int width, int height); // (int width, int height) -> sk_image_info_t
sk_image_info_t SkImageInfo_MakeUnknown_2(); // () -> sk_image_info_t
bool SkImageInfo_ByteSizeOverflowed(size_t byteSize); // (size_t byteSize) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_IMAGE_INFO_H
