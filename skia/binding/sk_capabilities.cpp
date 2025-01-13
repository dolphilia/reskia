//
// Created by dolphilia on 2024/01/08.
//

#include "sk_capabilities.h"

#include "include/core/SkCapabilities.h"

#include "../static/static_sk_capabilities.h"

#include "../static/static_sk_capabilities-internal.h"

extern "C" {

void SkCapabilities_delete(void * capabilities) {
    delete static_cast<SkCapabilities *>(capabilities);
}

void SkCapabilities_ref(void * capabilities) {
    static_cast<SkCapabilities *>(capabilities)->ref();
}

int SkCapabilities_skslVersion(void * capabilities) {
    return static_cast<int>(static_cast<SkCapabilities *>(capabilities)->skslVersion());
}

bool SkCapabilities_unique(void * capabilities) {
    return static_cast<SkCapabilities *>(capabilities)->unique();
}

void SkCapabilities_unref(void * capabilities) {
    static_cast<SkCapabilities *>(capabilities)->unref();
}

// static

const_sk_capabilities_t SkCapabilities_RasterBackend() {
    return static_const_sk_capabilities_make(SkCapabilities::RasterBackend());
}

}