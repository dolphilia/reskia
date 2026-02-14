//
// Created by dolphilia on 2024/01/10.
//

#include "sk_pixel_ref.h"

#include "include/core/SkPixelRef.h"

#include "../static/static_sk_id_change_listener.h"
#include "../static/static_sk_i_size.h"

#include "../static/static_sk_id_change_listener-internal.h"
#include "../static/static_sk_i_size-internal.h"
#include "../static/static_sk_id_change_listener.h"

extern "C" {

void *SkPixelRef_new(int width, int height, void *addr, size_t rowBytes) {
    return new SkPixelRef(width, height, addr, rowBytes);
}

void SkPixelRef_delete(void *pixel_ref) {
    static_cast<SkPixelRef *>(pixel_ref)->unref();
}

sk_i_size_t SkPixelRef_dimensions(void *pixel_ref) {
    return static_sk_i_size_make(static_cast<SkPixelRef *>(pixel_ref)->dimensions());
}

int SkPixelRef_width(void *pixel_ref) {
    return static_cast<SkPixelRef *>(pixel_ref)->width();
}

int SkPixelRef_height(void *pixel_ref) {
    return static_cast<SkPixelRef *>(pixel_ref)->height();
}

void * SkPixelRef_pixels(void *pixel_ref) {
    return static_cast<SkPixelRef *>(pixel_ref)->pixels();
}

size_t SkPixelRef_rowBytes(void *pixel_ref) {
    return static_cast<SkPixelRef *>(pixel_ref)->rowBytes();
}

uint32_t SkPixelRef_getGenerationID(void *pixel_ref) {
    return static_cast<SkPixelRef *>(pixel_ref)->getGenerationID();
}

void SkPixelRef_notifyPixelsChanged(void *pixel_ref) {
    static_cast<SkPixelRef *>(pixel_ref)->notifyPixelsChanged();
}

bool SkPixelRef_isImmutable(void *pixel_ref) {
    return static_cast<SkPixelRef *>(pixel_ref)->isImmutable();
}

void SkPixelRef_setImmutable(void *pixel_ref) {
    static_cast<SkPixelRef *>(pixel_ref)->setImmutable();
}

void SkPixelRef_addGenIDChangeListener(void *pixel_ref, sk_id_change_listener_t id_change_listener) {
    static_cast<SkPixelRef *>(pixel_ref)->addGenIDChangeListener(static_sk_id_change_listener_get_entity(id_change_listener));
}

void SkPixelRef_notifyAddedToCache(void *pixel_ref) {
    static_cast<SkPixelRef *>(pixel_ref)->notifyAddedToCache();
}

void * SkPixelRef_diagnostic_only_getDiscardable(void *pixel_ref) {
    return static_cast<SkPixelRef *>(pixel_ref)->diagnostic_only_getDiscardable();
}

bool SkPixelRef_unique(void *pixel_ref) {
    return static_cast<SkPixelRef *>(pixel_ref)->unique();
}

void SkPixelRef_ref(void *pixel_ref) {
    static_cast<SkPixelRef *>(pixel_ref)->ref();
}

void SkPixelRef_unref(void *pixel_ref) {
    static_cast<SkPixelRef *>(pixel_ref)->unref();
}

}
