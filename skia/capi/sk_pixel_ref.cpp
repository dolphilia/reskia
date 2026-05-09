//
// Created by dolphilia on 2024/01/10.
//

#include "sk_pixel_ref.h"

#include "include/core/SkPixelRef.h"

#include "../handles/static_sk_id_change_listener.h"
#include "../handles/static_sk_i_size.h"

#include "../handles/static_sk_id_change_listener-internal.h"
#include "../handles/static_sk_i_size-internal.h"
#include "../handles/static_sk_id_change_listener.h"

namespace {

SkPixelRef *as_pixel_ref(reskia_pixel_ref_t *pixel_ref) {
    return reinterpret_cast<SkPixelRef *>(pixel_ref);
}

const SkPixelRef *as_pixel_ref(const reskia_pixel_ref_t *pixel_ref) {
    return reinterpret_cast<const SkPixelRef *>(pixel_ref);
}

} // namespace

extern "C" {

reskia_pixel_ref_t *SkPixelRef_new(int width, int height, void *addr, size_t rowBytes) {
    if (width < 0 || height < 0) {
        return nullptr;
    }
    return reinterpret_cast<reskia_pixel_ref_t *>(new SkPixelRef(width, height, addr, rowBytes));
}

void SkPixelRef_release(reskia_pixel_ref_t *pixel_ref) {
    SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return;
    }
    ref->unref();
}

sk_i_size_t SkPixelRef_dimensions(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return 0;
    }
    return static_sk_i_size_make(ref->dimensions());
}

int SkPixelRef_width(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return 0;
    }
    return ref->width();
}

int SkPixelRef_height(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return 0;
    }
    return ref->height();
}

void * SkPixelRef_pixels(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return nullptr;
    }
    return ref->pixels();
}

size_t SkPixelRef_rowBytes(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return 0;
    }
    return ref->rowBytes();
}

uint32_t SkPixelRef_getGenerationID(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return 0;
    }
    return ref->getGenerationID();
}

void SkPixelRef_notifyPixelsChanged(reskia_pixel_ref_t *pixel_ref) {
    SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return;
    }
    ref->notifyPixelsChanged();
}

bool SkPixelRef_isImmutable(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return false;
    }
    return ref->isImmutable();
}

void SkPixelRef_setImmutable(reskia_pixel_ref_t *pixel_ref) {
    SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return;
    }
    ref->setImmutable();
}

void SkPixelRef_addGenIDChangeListener(reskia_pixel_ref_t *pixel_ref, sk_id_change_listener_t id_change_listener) {
    SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr || id_change_listener == 0) {
        return;
    }
    ref->addGenIDChangeListener(static_sk_id_change_listener_get_entity(id_change_listener));
}

void SkPixelRef_notifyAddedToCache(reskia_pixel_ref_t *pixel_ref) {
    SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return;
    }
    ref->notifyAddedToCache();
}

reskia_discardable_memory_t * SkPixelRef_diagnostic_only_getDiscardable(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_discardable_memory_t *>(ref->diagnostic_only_getDiscardable());
}

bool SkPixelRef_unique(reskia_pixel_ref_t *pixel_ref) {
    const SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return false;
    }
    return ref->unique();
}

void SkPixelRef_ref(reskia_pixel_ref_t *pixel_ref) {
    SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return;
    }
    ref->ref();
}

void SkPixelRef_unref(reskia_pixel_ref_t *pixel_ref) {
    SkPixelRef *ref = as_pixel_ref(pixel_ref);
    if (ref == nullptr) {
        return;
    }
    ref->unref();
}

}
