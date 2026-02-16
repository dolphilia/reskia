//
// Created by dolphilia on 2024/01/08.
//

#ifndef RAIA_SKIA_SK_GRAPHICS_H
#define RAIA_SKIA_SK_GRAPHICS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_graphics_t reskia_graphics_t;
typedef struct reskia_trace_memory_dump_t reskia_trace_memory_dump_t;

void SkGraphics_delete(reskia_graphics_t *graphics); // (SkGraphics *graphics)

// static

void SkGraphics_Init(); // ()
size_t SkGraphics_GetFontCacheLimit(); // () -> size_t
size_t SkGraphics_SetFontCacheLimit(size_t bytes); // (size_t bytes) -> size_t
size_t SkGraphics_GetFontCacheUsed(); // () -> size_t
int SkGraphics_GetFontCacheCountUsed(); // () -> int
int SkGraphics_GetFontCacheCountLimit(); // () -> int
int SkGraphics_SetFontCacheCountLimit(int count); // (int count) -> int
void SkGraphics_PurgeFontCache(); // ()
void SkGraphics_PurgePinnedFontCache(); // ()
size_t SkGraphics_GetResourceCacheTotalBytesUsed(); // () -> size_t
size_t SkGraphics_GetResourceCacheTotalByteLimit(); // () -> size_t
size_t SkGraphics_SetResourceCacheTotalByteLimit(size_t newLimit); // (size_t newLimit) -> size_t
void SkGraphics_PurgeResourceCache(); // ()
size_t SkGraphics_GetResourceCacheSingleAllocationByteLimit(); // () -> size_t
size_t SkGraphics_SetResourceCacheSingleAllocationByteLimit(size_t newLimit); // (size_t newLimit) -> size_t
void SkGraphics_DumpMemoryStatistics(reskia_trace_memory_dump_t *dump); // (SkTraceMemoryDump *dump)
void SkGraphics_PurgeAllCaches(); // ()

// TODO
//void * SkGraphics_SetImageGeneratorFromEncodedDataFactory(void * factory); // (SkGraphics::ImageGeneratorFromEncodedDataFactory factory) -> SkGraphics::ImageGeneratorFromEncodedDataFactory
//void * SkGraphics_SetOpenTypeSVGDecoderFactory(SkGraphics::OpenTypeSVGDecoderFactory factory); // (SkGraphics::OpenTypeSVGDecoderFactory factory) -> SkGraphics::OpenTypeSVGDecoderFactory
//void * SkGraphics_GetOpenTypeSVGDecoderFactory(); // () -> SkGraphics::OpenTypeSVGDecoderFactory

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_GRAPHICS_H
