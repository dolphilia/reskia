//
// Created by dolphilia on 2024/01/08.
//

#include "sk_capabilities.h"

#include "include/core/SkCapabilities.h"

#include "../handles/static_sk_capabilities.h"

#include "../handles/static_sk_capabilities-internal.h"

extern "C" {

void SkCapabilities_release(void * capabilities) {
    if (capabilities == nullptr) {
        return;
    }
    static_cast<SkCapabilities *>(capabilities)->unref();
}

void SkCapabilities_ref(void * capabilities) {
    if (capabilities == nullptr) {
        return;
    }
    static_cast<SkCapabilities *>(capabilities)->ref();
}

reskia_sksl_version_t SkCapabilities_skslVersion(void * capabilities) {
    if (capabilities == nullptr) {
        return 0;
    }
    return static_cast<reskia_sksl_version_t>(static_cast<SkCapabilities *>(capabilities)->skslVersion());
}

bool SkCapabilities_unique(void * capabilities) {
    if (capabilities == nullptr) {
        return false;
    }
    return static_cast<SkCapabilities *>(capabilities)->unique();
}

void SkCapabilities_unref(void * capabilities) {
    if (capabilities == nullptr) {
        return;
    }
    static_cast<SkCapabilities *>(capabilities)->unref();
}

// static

const_sk_capabilities_t SkCapabilities_RasterBackend() {
    return static_const_sk_capabilities_make(SkCapabilities::RasterBackend());
}

}
