//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_GRAPHICS_H
#define RAIA_SKIA_SK_GRAPHICS_H

#include <stddef.h>

#ifdef __cplusplus
#include "include/core/SkGraphics.h"
extern "C" {
#endif

typedef struct reskia_graphics_t reskia_graphics_t;
typedef struct reskia_trace_memory_dump_t reskia_trace_memory_dump_t;

void SkGraphics_delete(reskia_graphics_t *graphics); // (SkGraphics *graphics)

// static

void SkGraphics_Init(); // Process-wide initialization; safe to call more than once.
size_t SkGraphics_GetFontCacheLimit(); // () -> size_t
size_t SkGraphics_SetFontCacheLimit(size_t bytes); // Process-wide cache limit setter.
size_t SkGraphics_GetFontCacheUsed(); // () -> size_t
int SkGraphics_GetFontCacheCountUsed(); // () -> int
int SkGraphics_GetFontCacheCountLimit(); // () -> int
int SkGraphics_SetFontCacheCountLimit(int count); // Negative count is rejected and returns the current limit.
void SkGraphics_PurgeFontCache(); // Process-wide cache purge.
void SkGraphics_PurgePinnedFontCache(); // Process-wide pinned cache purge.
size_t SkGraphics_GetResourceCacheTotalBytesUsed(); // () -> size_t
size_t SkGraphics_GetResourceCacheTotalByteLimit(); // () -> size_t
size_t SkGraphics_SetResourceCacheTotalByteLimit(size_t newLimit); // Process-wide resource cache limit setter.
void SkGraphics_PurgeResourceCache(); // Process-wide resource cache purge.
size_t SkGraphics_GetResourceCacheSingleAllocationByteLimit(); // () -> size_t
size_t SkGraphics_SetResourceCacheSingleAllocationByteLimit(size_t newLimit); // Process-wide single allocation limit setter.
void SkGraphics_DumpMemoryStatistics(reskia_trace_memory_dump_t *dump); // NULL dump is no-op.
void SkGraphics_PurgeAllCaches(); // Process-wide cache purge.

// TODO
//void * SkGraphics_SetImageGeneratorFromEncodedDataFactory(void * factory); // (SkGraphics::ImageGeneratorFromEncodedDataFactory factory) -> SkGraphics::ImageGeneratorFromEncodedDataFactory
#ifdef __cplusplus
SkGraphics::OpenTypeSVGDecoderFactory SkGraphics_SetOpenTypeSVGDecoderFactory(SkGraphics::OpenTypeSVGDecoderFactory factory); // (SkGraphics::OpenTypeSVGDecoderFactory factory) -> SkGraphics::OpenTypeSVGDecoderFactory
SkGraphics::OpenTypeSVGDecoderFactory SkGraphics_GetOpenTypeSVGDecoderFactory(); // () -> SkGraphics::OpenTypeSVGDecoderFactory
#endif

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_GRAPHICS_H
