//
// Created by dolphilia on 2024/01/10.
//

#include "sk_raster_handle_allocator.h"

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

// @TODO
//std::unique_ptr<SkCanvas> SkRasterHandleAllocator_MakeCanvas(std::unique_ptr<SkRasterHandleAllocator> allocator, const SkImageInfo &info, const SkRasterHandleAllocator::Rec *rec, const SkSurfaceProps *props) {
//    return SkRasterHandleAllocator::MakeCanvas(allocator, info, rec, props);
//}

}
