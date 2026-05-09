//
// Created by dolphilia on 2024/01/10.
//

#include "sk_raster_handle_allocator.h"

#include "include/core/SkSurfaceProps.h"

#include "../handles/static_sk_canvas-internal.h"

namespace {

SkRasterHandleAllocator *as_allocator(reskia_raster_handle_allocator_t *allocator) {
    return reinterpret_cast<SkRasterHandleAllocator *>(allocator);
}

const SkImageInfo *as_image_info(const reskia_image_info_t *info) {
    return reinterpret_cast<const SkImageInfo *>(info);
}

SkRasterHandleAllocator::Rec *as_rec(reskia_raster_handle_allocator_rec_t *rec) {
    return reinterpret_cast<SkRasterHandleAllocator::Rec *>(rec);
}

const SkRasterHandleAllocator::Rec *as_rec(const reskia_raster_handle_allocator_rec_t *rec) {
    return reinterpret_cast<const SkRasterHandleAllocator::Rec *>(rec);
}

const SkMatrix *as_matrix(const reskia_matrix_t *matrix) {
    return reinterpret_cast<const SkMatrix *>(matrix);
}

const SkIRect *as_irect(const reskia_i_rect_t *irect) {
    return reinterpret_cast<const SkIRect *>(irect);
}

const SkSurfaceProps *as_surface_props(const reskia_surface_props_t *props) {
    return reinterpret_cast<const SkSurfaceProps *>(props);
}

} // namespace

extern "C" {

void SkRasterHandleAllocator_delete(reskia_raster_handle_allocator_t *raster_handle_allocator) {
    delete as_allocator(raster_handle_allocator);
}

bool SkRasterHandleAllocator_allocHandle(reskia_raster_handle_allocator_t *raster_handle_allocator, const reskia_image_info_t *info, reskia_raster_handle_allocator_rec_t *rec) {
    SkRasterHandleAllocator *allocator = as_allocator(raster_handle_allocator);
    const SkImageInfo *imageInfo = as_image_info(info);
    SkRasterHandleAllocator::Rec *record = as_rec(rec);
    if (allocator == nullptr || imageInfo == nullptr || record == nullptr) {
        return false;
    }
    return allocator->allocHandle(*imageInfo, record);
}

void SkRasterHandleAllocator_updateHandle(reskia_raster_handle_allocator_t *raster_handle_allocator, reskia_raster_handle_t handle, const reskia_matrix_t *matrix, const reskia_i_rect_t *irect) {
    SkRasterHandleAllocator *allocator = as_allocator(raster_handle_allocator);
    const SkMatrix *localMatrix = as_matrix(matrix);
    const SkIRect *clipBounds = as_irect(irect);
    if (allocator == nullptr || handle == nullptr || localMatrix == nullptr || clipBounds == nullptr) {
        return;
    }
    allocator->updateHandle(
            reinterpret_cast<SkRasterHandleAllocator::Handle>(handle),
            *localMatrix,
            *clipBounds);
}

// static

sk_canvas_t SkRasterHandleAllocator_MakeCanvas(reskia_raster_handle_allocator_t *allocator, const reskia_image_info_t *info, const reskia_raster_handle_allocator_rec_t *rec, const reskia_surface_props_t *props) {
    SkRasterHandleAllocator *rasterAllocator = as_allocator(allocator);
    const SkImageInfo *imageInfo = as_image_info(info);
    if (rasterAllocator == nullptr || imageInfo == nullptr) {
        return 0;
    }
    auto canvas = SkRasterHandleAllocator::MakeCanvas(
            std::unique_ptr<SkRasterHandleAllocator>(rasterAllocator),
            *imageInfo,
            as_rec(rec),
            as_surface_props(props));
    if (!canvas) {
        return 0;
    }
    return static_sk_canvas_make(std::move(canvas));
}

}
