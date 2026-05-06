//
// Created by dolphilia on 2024/01/10.
//

#include "sk_raster_handle_allocator.h"

#include "include/core/SkSurfaceProps.h"

#include "../handles/static_sk_canvas-internal.h"

extern "C" {

void SkRasterHandleAllocator_delete(reskia_raster_handle_allocator_t *raster_handle_allocator) {
    delete reinterpret_cast<SkRasterHandleAllocator *>(raster_handle_allocator);
}

bool SkRasterHandleAllocator_allocHandle(reskia_raster_handle_allocator_t *raster_handle_allocator, const reskia_image_info_t *info, reskia_raster_handle_allocator_rec_t *rec) {
    return reinterpret_cast<SkRasterHandleAllocator *>(raster_handle_allocator)->allocHandle(
            *reinterpret_cast<const SkImageInfo *>(info),
            reinterpret_cast<SkRasterHandleAllocator::Rec *>(rec));
}

void SkRasterHandleAllocator_updateHandle(reskia_raster_handle_allocator_t *raster_handle_allocator, reskia_raster_handle_t handle, const reskia_matrix_t *matrix, const reskia_i_rect_t *irect) {
    reinterpret_cast<SkRasterHandleAllocator *>(raster_handle_allocator)->updateHandle(
            reinterpret_cast<SkRasterHandleAllocator::Handle>(handle),
            *reinterpret_cast<const SkMatrix *>(matrix),
            *reinterpret_cast<const SkIRect *>(irect));
}

// static

sk_canvas_t SkRasterHandleAllocator_MakeCanvas(reskia_raster_handle_allocator_t *allocator, const reskia_image_info_t *info, const reskia_raster_handle_allocator_rec_t *rec, const reskia_surface_props_t *props) {
    if (!allocator || !info) {
        return 0;
    }
    auto canvas = SkRasterHandleAllocator::MakeCanvas(
            std::unique_ptr<SkRasterHandleAllocator>(reinterpret_cast<SkRasterHandleAllocator *>(allocator)),
            *reinterpret_cast<const SkImageInfo *>(info),
            reinterpret_cast<const SkRasterHandleAllocator::Rec *>(rec),
            reinterpret_cast<const SkSurfaceProps *>(props));
    if (!canvas) {
        return 0;
    }
    return static_sk_canvas_make(std::move(canvas));
}

}
