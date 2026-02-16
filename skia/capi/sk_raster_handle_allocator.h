//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H
#define RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H

#include "include/core/SkRasterHandleAllocator.h"

typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_raster_handle_allocator_rec_t reskia_raster_handle_allocator_rec_t;
typedef struct reskia_raster_handle_allocator_t reskia_raster_handle_allocator_t;
typedef void *reskia_raster_handle_t;

extern "C" {

void SkRasterHandleAllocator_delete(reskia_raster_handle_allocator_t *raster_handle_allocator); // (SkRasterHandleAllocator *raster_handle_allocator)
bool SkRasterHandleAllocator_allocHandle(reskia_raster_handle_allocator_t *raster_handle_allocator, const reskia_image_info_t *info, reskia_raster_handle_allocator_rec_t *rec); // (SkRasterHandleAllocator *raster_handle_allocator, const SkImageInfo *info, SkRasterHandleAllocator::Rec *rec) -> bool
void SkRasterHandleAllocator_updateHandle(reskia_raster_handle_allocator_t *raster_handle_allocator, reskia_raster_handle_t handle, const reskia_matrix_t *matrix, const reskia_i_rect_t *irect); // (SkRasterHandleAllocator *raster_handle_allocator, SkRasterHandleAllocator::Handle handle, const SkMatrix *matrix, const SkIRect *irect)

}

#endif //RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H
