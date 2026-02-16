#ifndef RAIA_SKIA_RESKIA_FFI_H
#define RAIA_SKIA_RESKIA_FFI_H

#include <stddef.h>
#include <stdint.h>

#include "sk_b_box_hierarchy.h"
#include "sk_bitmap.h"
#include "sk_blender.h"
#include "sk_canvas.h"
#include "sk_capabilities.h"
#include "sk_color_filter.h"
#include "sk_color_matrix_filter.h"
#include "sk_color_space.h"
#include "sk_color_table.h"
#include "sk_contour_measure.h"
#include "sk_data.h"
#include "sk_data_table.h"
#include "sk_document.h"
#include "sk_drawable.h"
#include "sk_executor.h"
#include "sk_file_stream.h"
#include "sk_flattenable.h"
#include "sk_font_mgr.h"
#include "sk_font_style_set.h"
#include "sk_image.h"
#include "sk_image_filter.h"
#include "sk_mask_filter.h"
#include "sk_memory_stream.h"
#include "sk_paint.h"
#include "sk_path.h"
#include "sk_path_effect.h"
#include "sk_pdf.h"
#include "sk_picture.h"
#include "sk_pixel_ref.h"
#include "sk_read_buffer.h"
#include "sk_runtime_effect.h"
#include "sk_shader.h"
#include "sk_stream.h"
#include "sk_stream_asset.h"
#include "sk_stream_memory.h"
#include "sk_stream_rewindable.h"
#include "sk_stream_seekable.h"
#include "sk_surface.h"
#include "sk_text_blob.h"
#include "sk_vertices.h"
#include "../handles/static_sk_b_box_hierarchy.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_capabilities.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_color_table.h"
#include "../handles/static_sk_contour_measure.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_data_table.h"
#include "../handles/static_sk_document.h"
#include "../handles/static_sk_drawable.h"
#include "../handles/static_sk_flattenable.h"
#include "../handles/static_sk_font_mgr.h"
#include "../handles/static_sk_font_style_set.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image_filter.h"
#include "../handles/static_sk_mask_filter.h"
#include "../handles/static_sk_paint.h"
#include "../handles/static_sk_path.h"
#include "../handles/static_sk_path_effect.h"
#include "../handles/static_sk_picture.h"
#include "../handles/static_sk_pixel_ref.h"
#include "../handles/static_sk_runtime_effect.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_surface.h"
#include "../handles/static_sk_text_blob.h"
#include "../handles/static_sk_vertices.h"

#ifdef __cplusplus
extern "C" {
#endif

// RefCounted bridge (retain/release + borrow from static handle)
void reskia_b_box_hierarchy_retain(reskia_b_box_hierarchy_t *value);
void reskia_b_box_hierarchy_release(reskia_b_box_hierarchy_t *value);
reskia_b_box_hierarchy_t *reskia_b_box_hierarchy_borrow_from_handle(sk_b_box_hierarchy_t handle);

void reskia_blender_retain(reskia_blender_t *value);
void reskia_blender_release(reskia_blender_t *value);
reskia_blender_t *reskia_blender_borrow_from_handle(sk_blender_t handle);

void reskia_capabilities_retain(reskia_capabilities_t *value);
void reskia_capabilities_release(reskia_capabilities_t *value);
const reskia_capabilities_t *reskia_capabilities_borrow_from_handle(const_sk_capabilities_t handle);

void reskia_color_filter_retain(reskia_color_filter_t *value);
void reskia_color_filter_release(reskia_color_filter_t *value);
reskia_color_filter_t *reskia_color_filter_borrow_from_handle(sk_color_filter_t handle);

void reskia_color_matrix_filter_retain(reskia_color_matrix_filter_t *value);
void reskia_color_matrix_filter_release(reskia_color_matrix_filter_t *value);

void reskia_color_space_retain(reskia_color_space_t *value);
void reskia_color_space_release(reskia_color_space_t *value);
reskia_color_space_t *reskia_color_space_borrow_from_handle(sk_color_space_t handle);

void reskia_color_table_retain(reskia_color_table_t *value);
void reskia_color_table_release(reskia_color_table_t *value);
reskia_color_table_t *reskia_color_table_borrow_from_handle(sk_color_table_t handle);

void reskia_contour_measure_retain(reskia_contour_measure_t *value);
void reskia_contour_measure_release(reskia_contour_measure_t *value);
reskia_contour_measure_t *reskia_contour_measure_borrow_from_handle(sk_contour_measure_t handle);

void reskia_data_retain(reskia_data_t *value);
void reskia_data_release(reskia_data_t *value);
reskia_data_t *reskia_data_borrow_from_handle(sk_data_t handle);

void reskia_data_table_retain(reskia_data_table_t *value);
void reskia_data_table_release(reskia_data_table_t *value);
reskia_data_table_t *reskia_data_table_borrow_from_handle(sk_data_table_t handle);

void reskia_document_retain(reskia_document_t *value);
void reskia_document_release(reskia_document_t *value);
reskia_document_t *reskia_document_borrow_from_handle(sk_document_t handle);

void reskia_drawable_retain(reskia_drawable_t *value);
void reskia_drawable_release(reskia_drawable_t *value);
reskia_drawable_t *reskia_drawable_borrow_from_handle(sk_drawable_t handle);

void reskia_flattenable_retain(reskia_flattenable_t *value);
void reskia_flattenable_release(reskia_flattenable_t *value);
reskia_flattenable_t *reskia_flattenable_borrow_from_handle(sk_flattenable_t handle);

void reskia_font_mgr_retain(reskia_font_mgr_t *value);
void reskia_font_mgr_release(reskia_font_mgr_t *value);
reskia_font_mgr_t *reskia_font_mgr_borrow_from_handle(sk_font_mgr_t handle);

void reskia_font_style_set_retain(reskia_font_style_set_t *value);
void reskia_font_style_set_release(reskia_font_style_set_t *value);
reskia_font_style_set_t *reskia_font_style_set_borrow_from_handle(sk_font_style_set_t handle);

void reskia_image_retain(reskia_image_t *value);
void reskia_image_release(reskia_image_t *value);
reskia_image_t *reskia_image_borrow_from_handle(sk_image_t handle);

void reskia_image_filter_retain(reskia_image_filter_t *value);
void reskia_image_filter_release(reskia_image_filter_t *value);
reskia_image_filter_t *reskia_image_filter_borrow_from_handle(sk_image_filter_t handle);

void reskia_mask_filter_retain(reskia_mask_filter_t *value);
void reskia_mask_filter_release(reskia_mask_filter_t *value);
reskia_mask_filter_t *reskia_mask_filter_borrow_from_handle(sk_mask_filter_t handle);

void reskia_path_effect_retain(reskia_path_effect_t *value);
void reskia_path_effect_release(reskia_path_effect_t *value);
reskia_path_effect_t *reskia_path_effect_borrow_from_handle(sk_path_effect_t handle);

void reskia_picture_retain(reskia_picture_t *value);
void reskia_picture_release(reskia_picture_t *value);
reskia_picture_t *reskia_picture_borrow_from_handle(sk_picture_t handle);

void reskia_pixel_ref_retain(reskia_pixel_ref_t *value);
void reskia_pixel_ref_release(reskia_pixel_ref_t *value);
reskia_pixel_ref_t *reskia_pixel_ref_borrow_from_handle(sk_pixel_ref_t handle);

void reskia_runtime_effect_retain(reskia_runtime_effect_t *value);
void reskia_runtime_effect_release(reskia_runtime_effect_t *value);
reskia_runtime_effect_t *reskia_runtime_effect_borrow_from_handle(sk_runtime_effect_t handle);

void reskia_shader_retain(reskia_shader_t *value);
void reskia_shader_release(reskia_shader_t *value);
reskia_shader_t *reskia_shader_borrow_from_handle(sk_shader_t handle);

void reskia_surface_retain(reskia_surface_t *value);
void reskia_surface_release(reskia_surface_t *value);
reskia_surface_t *reskia_surface_borrow_from_handle(sk_surface_t handle);

void reskia_text_blob_retain(reskia_text_blob_t *value);
void reskia_text_blob_release(reskia_text_blob_t *value);
reskia_text_blob_t *reskia_text_blob_borrow_from_handle(sk_text_blob_t handle);

void reskia_vertices_retain(reskia_vertices_t *value);
void reskia_vertices_release(reskia_vertices_t *value);
reskia_vertices_t *reskia_vertices_borrow_from_handle(sk_vertices_t handle);

// Value/Object bridge (copy retain/release + borrow from handle)
reskia_paint_t *reskia_paint_retain(const reskia_paint_t *paint);
void reskia_paint_release(reskia_paint_t *paint);
reskia_paint_t *reskia_paint_borrow_from_handle(sk_paint_t handle);

reskia_path_t *reskia_path_retain(const reskia_path_t *path);
void reskia_path_release(reskia_path_t *path);
reskia_path_t *reskia_path_borrow_from_handle(sk_path_t handle);

// Borrowed bridge APIs
void reskia_executor_borrow(reskia_executor_t *executor);
reskia_canvas_t *reskia_surface_borrow_canvas(reskia_surface_t *surface);
const reskia_surface_props_t *reskia_surface_borrow_props(reskia_surface_t *surface);
bool reskia_surface_borrow_pixels(reskia_surface_t *surface, reskia_pixmap_t *pixmap);
bool reskia_canvas_borrow_pixels(reskia_canvas_t *canvas, reskia_pixmap_t *pixmap);
bool reskia_image_borrow_pixels(reskia_image_t *image, reskia_pixmap_t *pixmap);
bool reskia_bitmap_borrow_pixels(reskia_bitmap_t *bitmap, reskia_pixmap_t *pixmap);
void *reskia_pixel_ref_borrow_pixels(reskia_pixel_ref_t *pixel_ref);
size_t reskia_stream_borrow_peek(reskia_stream_t *stream, void *buffer, size_t size);
size_t reskia_file_stream_borrow_peek(reskia_file_stream_t *file_stream, uint8_t *ptr, size_t size);
size_t reskia_stream_asset_borrow_peek(reskia_stream_asset_t *stream_asset, void *buffer, size_t size);
size_t reskia_memory_stream_borrow_peek(reskia_memory_stream_t *memory_stream, uint8_t *buffer, size_t size);
size_t reskia_stream_memory_borrow_peek(reskia_stream_memory_t *stream_memory, void *buffer, size_t size);
size_t reskia_stream_rewindable_borrow_peek(reskia_stream_rewindable_t *stream_rewindable, void *buffer, size_t size);
size_t reskia_stream_seekable_borrow_peek(reskia_stream_seekable_t *stream_seekable, void *buffer, size_t size);
uint8_t reskia_read_buffer_borrow_peek_byte(reskia_read_buffer_t *buffer);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_RESKIA_FFI_H
