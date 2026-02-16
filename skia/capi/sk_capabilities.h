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

void SkCapabilities_delete(void * capabilities); // owned: caller が保持する参照を release する (SkCapabilities *capabilities)
void SkCapabilities_ref(void * capabilities); // retained: 参照カウントを増やす (SkCapabilities *capabilities)
reskia_sksl_version_t SkCapabilities_skslVersion(void * capabilities); // (SkCapabilities *capabilities) -> SkSL::Version
bool SkCapabilities_unique(void * capabilities); // (SkCapabilities *capabilities) -> bool
void SkCapabilities_unref(void * capabilities); // owned: 参照カウントを減らす (SkCapabilities *capabilities)

// static

int SkCapabilities_RasterBackend(); // () -> const_sk_capabilities_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_CAPABILITIES_H
