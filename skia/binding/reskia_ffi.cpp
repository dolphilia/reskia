#include "reskia_ffi.h"

#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"

#include "../static/static_sk_b_box_hierarchy.h"
#include "../static/static_sk_blender.h"
#include "../static/static_sk_capabilities.h"
#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_color_space.h"
#include "../static/static_sk_color_table.h"
#include "../static/static_sk_contour_measure.h"
#include "../static/static_sk_data.h"
#include "../static/static_sk_data_table.h"
#include "../static/static_sk_document.h"
#include "../static/static_sk_drawable.h"
#include "../static/static_sk_flattenable.h"
#include "../static/static_sk_font_mgr.h"
#include "../static/static_sk_font_style_set.h"
#include "../static/static_sk_image.h"
#include "../static/static_sk_image_filter.h"
#include "../static/static_sk_mask_filter.h"
#include "../static/static_sk_paint.h"
#include "../static/static_sk_path.h"
#include "../static/static_sk_path_effect.h"
#include "../static/static_sk_picture.h"
#include "../static/static_sk_pixel_ref.h"
#include "../static/static_sk_runtime_effect.h"
#include "../static/static_sk_shader.h"
#include "../static/static_sk_surface.h"
#include "../static/static_sk_text_blob.h"
#include "../static/static_sk_vertices.h"

#define RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(NAME, OPAQUE_T, HANDLE_T, RETAIN_FN, RELEASE_FN, GET_PTR_FN) \
    void reskia_##NAME##_retain(OPAQUE_T *value) { \
        if (value == nullptr) { \
            return; \
        } \
        RETAIN_FN(value); \
    } \
    void reskia_##NAME##_release(OPAQUE_T *value) { \
        if (value == nullptr) { \
            return; \
        } \
        RELEASE_FN(value); \
    } \
    OPAQUE_T *reskia_##NAME##_borrow_from_handle(HANDLE_T handle) { \
        return reinterpret_cast<OPAQUE_T *>(GET_PTR_FN(handle)); \
    }

extern "C" {

RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(b_box_hierarchy, reskia_b_box_hierarchy_t, sk_b_box_hierarchy_t, SkBBoxHierarchy_ref, SkBBoxHierarchy_unref, static_sk_b_box_hierarchy_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(blender, reskia_blender_t, sk_blender_t, SkBlender_ref, SkBlender_unref, static_sk_blender_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(color_filter, reskia_color_filter_t, sk_color_filter_t, SkColorFilter_ref, SkColorFilter_unref, static_sk_color_filter_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(color_space, reskia_color_space_t, sk_color_space_t, SkColorSpace_ref, SkColorSpace_unref, static_sk_color_space_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(color_table, reskia_color_table_t, sk_color_table_t, SkColorTable_ref, SkColorTable_unref, static_sk_color_table_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(contour_measure, reskia_contour_measure_t, sk_contour_measure_t, SkContourMeasure_ref, SkContourMeasure_unref, static_sk_contour_measure_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(data, reskia_data_t, sk_data_t, SkData_ref, SkData_unref, static_sk_data_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(data_table, reskia_data_table_t, sk_data_table_t, SkDataTable_ref, SkDataTable_unref, static_sk_data_table_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(document, reskia_document_t, sk_document_t, SkDocument_ref, SkDocument_unref, static_sk_document_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(drawable, reskia_drawable_t, sk_drawable_t, SkDrawable_ref, SkDrawable_unref, static_sk_drawable_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(flattenable, reskia_flattenable_t, sk_flattenable_t, SkFlattenable_ref, SkFlattenable_unref, static_sk_flattenable_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(font_mgr, reskia_font_mgr_t, sk_font_mgr_t, SkFontMgr_ref, SkFontMgr_unref, static_sk_font_mgr_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(font_style_set, reskia_font_style_set_t, sk_font_style_set_t, SkFontStyleSet_ref, SkFontStyleSet_unref, static_sk_font_style_set_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(image, reskia_image_t, sk_image_t, SkImage_ref, SkImage_unref, static_sk_image_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(image_filter, reskia_image_filter_t, sk_image_filter_t, SkImageFilter_ref, SkImageFilter_unref, static_sk_image_filter_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(mask_filter, reskia_mask_filter_t, sk_mask_filter_t, SkMaskFilter_ref, SkMaskFilter_unref, static_sk_mask_filter_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(path_effect, reskia_path_effect_t, sk_path_effect_t, SkPathEffect_ref, SkPathEffect_unref, static_sk_path_effect_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(picture, reskia_picture_t, sk_picture_t, SkPicture_ref, SkPicture_unref, static_sk_picture_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(pixel_ref, reskia_pixel_ref_t, sk_pixel_ref_t, SkPixelRef_ref, SkPixelRef_unref, static_sk_pixel_ref_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(runtime_effect, reskia_runtime_effect_t, sk_runtime_effect_t, SkRuntimeEffect_ref, SkRuntimeEffect_unref, static_sk_runtime_effect_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(shader, reskia_shader_t, sk_shader_t, SkShader_ref, SkShader_unref, static_sk_shader_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(surface, reskia_surface_t, sk_surface_t, SkSurface_ref, SkSurface_unref, static_sk_surface_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(text_blob, reskia_text_blob_t, sk_text_blob_t, SkTextBlob_ref, SkTextBlob_unref, static_sk_text_blob_get_ptr)
RESKIA_DEFINE_REFCOUNTED_HANDLE_WRAPPER(vertices, reskia_vertices_t, sk_vertices_t, SkVertices_ref, SkVertices_unref, static_sk_vertices_get_ptr)

void reskia_capabilities_retain(reskia_capabilities_t *value) {
    if (value == nullptr) {
        return;
    }
    SkCapabilities_ref(value);
}

void reskia_capabilities_release(reskia_capabilities_t *value) {
    if (value == nullptr) {
        return;
    }
    SkCapabilities_unref(value);
}

const reskia_capabilities_t *reskia_capabilities_borrow_from_handle(const_sk_capabilities_t handle) {
    return reinterpret_cast<const reskia_capabilities_t *>(static_const_sk_capabilities_get_ptr(handle));
}

void reskia_color_matrix_filter_retain(reskia_color_matrix_filter_t *value) {
    if (value == nullptr) {
        return;
    }
    SkColorMatrixFilter_ref(value);
}

void reskia_color_matrix_filter_release(reskia_color_matrix_filter_t *value) {
    if (value == nullptr) {
        return;
    }
    SkColorMatrixFilter_unref(value);
}

reskia_paint_t *reskia_paint_retain(const reskia_paint_t *paint) {
    if (paint == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_paint_t *>(
        new SkPaint(*reinterpret_cast<const SkPaint *>(paint))
    );
}

void reskia_paint_release(reskia_paint_t *paint) {
    if (paint == nullptr) {
        return;
    }
    SkPaint_delete(paint);
}

reskia_paint_t *reskia_paint_borrow_from_handle(sk_paint_t handle) {
    return reinterpret_cast<reskia_paint_t *>(static_sk_paint_get_ptr(handle));
}

reskia_path_t *reskia_path_retain(const reskia_path_t *path) {
    if (path == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_path_t *>(
        new SkPath(*reinterpret_cast<const SkPath *>(path))
    );
}

void reskia_path_release(reskia_path_t *path) {
    if (path == nullptr) {
        return;
    }
    SkPath_delete(path);
}

reskia_path_t *reskia_path_borrow_from_handle(sk_path_t handle) {
    return reinterpret_cast<reskia_path_t *>(static_sk_path_get_ptr(handle));
}

void reskia_executor_borrow(reskia_executor_t *executor) {
    if (executor == nullptr) {
        return;
    }
    SkExecutor_borrow(executor);
}

reskia_canvas_t *reskia_surface_borrow_canvas(reskia_surface_t *surface) {
    if (surface == nullptr) {
        return nullptr;
    }
    return SkSurface_getCanvas(surface);
}

const reskia_surface_props_t *reskia_surface_borrow_props(reskia_surface_t *surface) {
    if (surface == nullptr) {
        return nullptr;
    }
    return SkSurface_props(surface);
}

bool reskia_surface_borrow_pixels(reskia_surface_t *surface, reskia_pixmap_t *pixmap) {
    if (surface == nullptr || pixmap == nullptr) {
        return false;
    }
    return SkSurface_peekPixels(surface, pixmap);
}

bool reskia_canvas_borrow_pixels(reskia_canvas_t *canvas, reskia_pixmap_t *pixmap) {
    if (canvas == nullptr || pixmap == nullptr) {
        return false;
    }
    return SkCanvas_peekPixels(canvas, pixmap);
}

bool reskia_image_borrow_pixels(reskia_image_t *image, reskia_pixmap_t *pixmap) {
    if (image == nullptr || pixmap == nullptr) {
        return false;
    }
    return SkImage_peekPixels(image, pixmap);
}

bool reskia_bitmap_borrow_pixels(reskia_bitmap_t *bitmap, reskia_pixmap_t *pixmap) {
    if (bitmap == nullptr || pixmap == nullptr) {
        return false;
    }
    return SkBitmap_peekPixels(bitmap, pixmap);
}

void *reskia_pixel_ref_borrow_pixels(reskia_pixel_ref_t *pixel_ref) {
    if (pixel_ref == nullptr) {
        return nullptr;
    }
    return SkPixelRef_pixels(pixel_ref);
}

size_t reskia_stream_borrow_peek(reskia_stream_t *stream, void *buffer, size_t size) {
    if (stream == nullptr || buffer == nullptr) {
        return 0;
    }
    return SkStream_peek(stream, buffer, size);
}

size_t reskia_file_stream_borrow_peek(reskia_file_stream_t *file_stream, uint8_t *ptr, size_t size) {
    if (file_stream == nullptr || ptr == nullptr) {
        return 0;
    }
    return SkFILEStream_peek(file_stream, ptr, size);
}

size_t reskia_stream_asset_borrow_peek(reskia_stream_asset_t *stream_asset, void *buffer, size_t size) {
    if (stream_asset == nullptr || buffer == nullptr) {
        return 0;
    }
    return SkStreamAsset_peek(stream_asset, buffer, size);
}

size_t reskia_memory_stream_borrow_peek(reskia_memory_stream_t *memory_stream, uint8_t *buffer, size_t size) {
    if (memory_stream == nullptr || buffer == nullptr) {
        return 0;
    }
    return SkMemoryStream_peek(memory_stream, buffer, size);
}

size_t reskia_stream_memory_borrow_peek(reskia_stream_memory_t *stream_memory, void *buffer, size_t size) {
    if (stream_memory == nullptr || buffer == nullptr) {
        return 0;
    }
    return SkStreamMemory_peek(stream_memory, buffer, size);
}

size_t reskia_stream_rewindable_borrow_peek(reskia_stream_rewindable_t *stream_rewindable, void *buffer, size_t size) {
    if (stream_rewindable == nullptr || buffer == nullptr) {
        return 0;
    }
    return SkStreamRewindable_peek(stream_rewindable, buffer, size);
}

size_t reskia_stream_seekable_borrow_peek(reskia_stream_seekable_t *stream_seekable, void *buffer, size_t size) {
    if (stream_seekable == nullptr || buffer == nullptr) {
        return 0;
    }
    return SkStreamSeekable_peek(stream_seekable, buffer, size);
}

uint8_t reskia_read_buffer_borrow_peek_byte(reskia_read_buffer_t *buffer) {
    if (buffer == nullptr) {
        return 0;
    }
    return SkReadBuffer_peekByte(buffer);
}

} // extern "C"
