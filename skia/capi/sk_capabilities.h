//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_CAPABILITIES_H
#define RAIA_SKIA_SK_CAPABILITIES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t reskia_sksl_version_t;

void SkCapabilities_release(void *capabilities); // NULL capabilities is no-op.
void SkCapabilities_ref(void *capabilities); // NULL capabilities is no-op.
reskia_sksl_version_t SkCapabilities_skslVersion(void *capabilities); // NULL capabilities returns 0.
bool SkCapabilities_unique(void *capabilities); // NULL capabilities returns false.
void SkCapabilities_unref(void *capabilities); // NULL capabilities is no-op.

// static

int SkCapabilities_RasterBackend(); // Returns a caller-owned const_sk_capabilities_t handle.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CAPABILITIES_H
