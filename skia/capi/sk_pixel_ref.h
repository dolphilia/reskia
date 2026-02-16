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

reskia_pixel_ref_t *SkPixelRef_new(int width, int height, void *addr, size_t rowBytes); // owned: 呼び出し側が解放責務を持つ新規オブジェクト (int width, int height, void *addr, size_t rowBytes) -> SkPixelRef *
void SkPixelRef_delete(reskia_pixel_ref_t *pixel_ref); // owned: caller が保持する参照を release する (SkPixelRef *pixel_ref)
sk_i_size_t SkPixelRef_dimensions(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref) -> sk_i_size_t
int SkPixelRef_width(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref) -> int
int SkPixelRef_height(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref) -> int
void * SkPixelRef_pixels(reskia_pixel_ref_t *pixel_ref); // borrowed: 解放不要の借用ポインタ (SkPixelRef *pixel_ref) -> void *
size_t SkPixelRef_rowBytes(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref) -> size_t
uint32_t SkPixelRef_getGenerationID(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref) -> uint32_t
void SkPixelRef_notifyPixelsChanged(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref)
bool SkPixelRef_isImmutable(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref) -> bool
void SkPixelRef_setImmutable(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref)
void SkPixelRef_addGenIDChangeListener(reskia_pixel_ref_t *pixel_ref, sk_id_change_listener_t id_change_listener); // (SkPixelRef *pixel_ref, sk_id_change_listener_t id_change_listener)
void SkPixelRef_notifyAddedToCache(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref)
reskia_discardable_memory_t * SkPixelRef_diagnostic_only_getDiscardable(reskia_pixel_ref_t *pixel_ref); // borrowed: 解放不要の借用ポインタ (SkPixelRef *pixel_ref) -> SkDiscardableMemory *
bool SkPixelRef_unique(reskia_pixel_ref_t *pixel_ref); // (SkPixelRef *pixel_ref) -> bool
void SkPixelRef_ref(reskia_pixel_ref_t *pixel_ref); // retained: 参照カウントを増やす (SkPixelRef *pixel_ref)
void SkPixelRef_unref(reskia_pixel_ref_t *pixel_ref); // owned: 参照カウントを減らす (SkPixelRef *pixel_ref)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PIXEL_REF_H
