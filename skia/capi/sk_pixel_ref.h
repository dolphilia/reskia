//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PIXEL_REF_H
#define RAIA_SKIA_SK_PIXEL_REF_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_i_size.h"
#include "../handles/static_sk_id_change_listener.h"

typedef struct reskia_discardable_memory_t reskia_discardable_memory_t;
typedef struct reskia_pixel_ref_t reskia_pixel_ref_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * owned: negative width/height returns NULL. addr may be NULL if caller intentionally creates an empty/borrowed pixel ref.
 */
reskia_pixel_ref_t *SkPixelRef_new(int width, int height, void *addr, size_t rowBytes);
void SkPixelRef_release(reskia_pixel_ref_t *pixel_ref); // owned: caller が保持する参照を release する。NULL 入力では no-op。
sk_i_size_t SkPixelRef_dimensions(reskia_pixel_ref_t *pixel_ref); // NULL 入力では 0。
int SkPixelRef_width(reskia_pixel_ref_t *pixel_ref); // NULL 入力では 0。
int SkPixelRef_height(reskia_pixel_ref_t *pixel_ref); // NULL 入力では 0。
void * SkPixelRef_pixels(reskia_pixel_ref_t *pixel_ref); // borrowed: 解放不要の借用ポインタ。NULL 入力では NULL。
size_t SkPixelRef_rowBytes(reskia_pixel_ref_t *pixel_ref); // NULL 入力では 0。
uint32_t SkPixelRef_getGenerationID(reskia_pixel_ref_t *pixel_ref); // NULL 入力では 0。
void SkPixelRef_notifyPixelsChanged(reskia_pixel_ref_t *pixel_ref); // NULL 入力では no-op。
bool SkPixelRef_isImmutable(reskia_pixel_ref_t *pixel_ref); // NULL 入力では false。
void SkPixelRef_setImmutable(reskia_pixel_ref_t *pixel_ref); // NULL 入力では no-op。
/**
 * pixel_ref and listener handle are required.
 * invalid input is no-op.
 */
void SkPixelRef_addGenIDChangeListener(reskia_pixel_ref_t *pixel_ref, sk_id_change_listener_t id_change_listener);
void SkPixelRef_notifyAddedToCache(reskia_pixel_ref_t *pixel_ref); // NULL 入力では no-op。
reskia_discardable_memory_t * SkPixelRef_diagnostic_only_getDiscardable(reskia_pixel_ref_t *pixel_ref); // borrowed: 解放不要の借用ポインタ。NULL 入力では NULL。
bool SkPixelRef_unique(reskia_pixel_ref_t *pixel_ref); // NULL 入力では false。
void SkPixelRef_ref(reskia_pixel_ref_t *pixel_ref); // retained: 参照カウントを増やす。NULL 入力では no-op。
void SkPixelRef_unref(reskia_pixel_ref_t *pixel_ref); // owned: 参照カウントを減らす。NULL 入力では no-op。

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PIXEL_REF_H
