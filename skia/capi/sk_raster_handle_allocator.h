//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H
#define RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H

#include "include/core/SkRasterHandleAllocator.h"
#include "../handles/static_sk_canvas.h"

typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_info_t reskia_image_info_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_raster_handle_allocator_rec_t reskia_raster_handle_allocator_rec_t;
typedef struct reskia_raster_handle_allocator_t reskia_raster_handle_allocator_t;
typedef struct reskia_surface_props_t reskia_surface_props_t;
typedef void *reskia_raster_handle_t;

extern "C" {

void SkRasterHandleAllocator_delete(reskia_raster_handle_allocator_t *raster_handle_allocator); // NULL allocator is no-op.
bool SkRasterHandleAllocator_allocHandle(reskia_raster_handle_allocator_t *raster_handle_allocator, const reskia_image_info_t *info, reskia_raster_handle_allocator_rec_t *rec); // allocator/info/rec are required. Invalid input returns false.
void SkRasterHandleAllocator_updateHandle(reskia_raster_handle_allocator_t *raster_handle_allocator, reskia_raster_handle_t handle, const reskia_matrix_t *matrix, const reskia_i_rect_t *irect); // allocator/handle/matrix/irect are required. Invalid input is no-op.
sk_canvas_t SkRasterHandleAllocator_MakeCanvas(reskia_raster_handle_allocator_t *allocator, const reskia_image_info_t *info, const reskia_raster_handle_allocator_rec_t *rec, const reskia_surface_props_t *props); // takes ownership of non-NULL allocator; rec/props may be NULL. Returns 0 on failure.

}

#endif //RAIA_SKIA_SK_RASTER_HANDLE_ALLOCATOR_H
