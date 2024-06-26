//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H
#define RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H

#include "include/core/SkRasterHandleAllocator.h"

extern "C" {
RAIA_API void SkRasterHandleAllocator_delete(SkRasterHandleAllocator *raster_handle_allocator);
RAIA_API bool SkRasterHandleAllocator_allocHandle(SkRasterHandleAllocator *raster_handle_allocator, const SkImageInfo *info, SkRasterHandleAllocator::Rec *rec);
RAIA_API void SkRasterHandleAllocator_updateHandle(SkRasterHandleAllocator *raster_handle_allocator, SkRasterHandleAllocator::Handle handle, const SkMatrix *matrix, const SkIRect *irect);
}

#endif //RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H
