list(APPEND SOURCE_FILES
        capi/sk_alpha_type.cpp
        capi/sk_android_codec.cpp
        capi/sk_annotation.cpp
        capi/sk_auto_canvas_restore.cpp
        capi/sk_b_box_hierarchy.cpp
        capi/sk_bitmap.cpp
        capi/sk_blend_mode.cpp
        capi/sk_blender.cpp
        capi/sk_blenders.cpp
        capi/sk_bmp_decoder.cpp
        capi/sk_canvas.cpp
        capi/sk_capabilities.cpp
        capi/sk_codec.cpp
        capi/sk_codecs.cpp
        capi/sk_color_4f.cpp
        capi/sk_color_filter.cpp
        capi/sk_color_filters.cpp
        capi/sk_color_info.cpp
        capi/sk_color_matrix_filter.cpp
        capi/sk_color_matrix.cpp
        capi/sk_color_priv.cpp
        capi/sk_color_space_primaries.cpp
        capi/sk_color_space.cpp
        capi/sk_color_table.cpp
        capi/sk_color.cpp
        capi/sk_contour_measure_iter.cpp
        capi/sk_contour_measure.cpp
        capi/sk_corner_path_effect.cpp
        capi/sk_cubic_map.cpp
        capi/sk_cubic_resampler.cpp
        capi/sk_dash_path_effect.cpp
        capi/sk_data_table.cpp
        capi/sk_data.cpp
        capi/sk_discrete_path_effect.cpp
        capi/sk_document.cpp
        capi/sk_drawable.cpp
        capi/sk_dynamic_memory_w_stream.cpp
        capi/sk_encoded_origin.cpp
        capi/sk_encoder.cpp
        capi/sk_executor.cpp
        capi/sk_file_stream.cpp
        capi/sk_file_w_stream.cpp
        capi/sk_flattenable.cpp
        capi/sk_font_arguments.cpp
        capi/sk_font_metrics.cpp
#        capi/sk_font_mgr_fontconfig.cpp
        capi/sk_font_mgr.cpp
        capi/sk_font_style_set.cpp
        capi/sk_font_style.cpp
        capi/sk_font.cpp
        capi/sk_gradient_shader.cpp
        capi/sk_graphics.cpp
        capi/sk_high_contrast_config.cpp
        capi/sk_high_contrast_filter.cpp
        capi/sk_i_point.cpp
        capi/sk_i_rect.cpp
        capi/sk_i_size.cpp
        capi/sk_icc.cpp
        capi/sk_ico_decoder.cpp
        capi/sk_image_filter.cpp
        capi/sk_image_filters.cpp
        capi/sk_image_generator.cpp
        capi/sk_image_info.cpp
        capi/sk_image.cpp
        capi/sk_images.cpp
        capi/sk_jpeg_decoder.cpp
        capi/sk_line_2d_path_effect.cpp
        capi/sk_luma_color_filter.cpp
        capi/sk_m_44.cpp
        capi/sk_malloc_pixel_ref.cpp
        capi/sk_mask.cpp
        capi/sk_mask_builder.cpp
        capi/sk_mask_filter.cpp
        capi/sk_matrix.cpp
        capi/sk_memory_stream.cpp
        capi/sk_mesh.cpp
        capi/sk_mesh_specification.cpp
        capi/sk_meshes.cpp
        capi/sk_op_builder.cpp
        capi/sk_overdraw_canvas.cpp
        capi/sk_overdraw_color_filter.cpp
        capi/sk_paint.cpp
        capi/sk_path_1d_path_effect.cpp
        capi/sk_path_2d_path_effect.cpp
        capi/sk_path_builder.cpp
        capi/sk_path_effect.cpp
        capi/sk_path_measure.cpp
        capi/sk_path.cpp
        capi/sk_perlin_noise_shader.cpp
        capi/sk_picture_recorder.cpp
        capi/sk_picture.cpp
        capi/sk_pixel_ref.cpp
        capi/sk_pixmap_utils.cpp
        capi/sk_pixmap.cpp
        capi/sk_png_decoder.cpp
        capi/sk_png_encoder.cpp
        capi/sk_point_3.cpp
        capi/sk_point.cpp
        capi/sk_r_rect.cpp
#        capi/sk_raster_handle_allocator.cpp
        capi/sk_read_buffer.cpp
        capi/sk_rect.cpp
        capi/sk_ref_cnt_base.cpp
        capi/sk_ref_cnt.cpp
        capi/reskia_ffi.cpp
        capi/sk_region.cpp
        capi/sk_rsx_form.cpp
        capi/sk_runtime_blend_builder.cpp
        capi/sk_runtime_color_filter_builder.cpp
        capi/sk_runtime_effect_builder.cpp
        capi/sk_runtime_effect.cpp
        capi/sk_runtime_shader_builder.cpp
        capi/sk_sampling_options.cpp
        capi/sk_shader_mask_filter.cpp
        capi/sk_shader.cpp
        capi/sk_shaders.cpp
        capi/sk_size.cpp
        capi/sk_stream_asset.cpp
        capi/sk_stream_memory.cpp
        capi/sk_stream_rewindable.cpp
        capi/sk_stream_seekable.cpp
        capi/sk_stream.cpp
        capi/sk_string.cpp
        capi/sk_stroke_rec.cpp
        capi/sk_surface_props.cpp
        capi/sk_surface.cpp
        capi/sk_surfaces.cpp
        capi/sk_table_mask_filter.cpp
#        capi/sk_text_blob_builder_run_handler.cpp
        capi/sk_text_blob_builder.cpp
        capi/sk_text_blob.cpp
        capi/sk_tiled_image_utils.cpp
        capi/sk_trace_memory_dump.cpp
        capi/sk_trim_path_effect.cpp
        capi/sk_typeface.cpp
        capi/sk_un_pre_multiply.cpp
        capi/sk_v2.cpp
        capi/sk_v3.cpp
        capi/sk_v4.cpp
        capi/sk_vertices.cpp
        capi/sk_w_stream.cpp
        capi/sk_wbmp_decoder.cpp
        capi/sk_webp_decoder.cpp
        capi/sk_write_buffer.cpp
        capi/sk_yuva_info.cpp
        capi/sk_yuva_pixmap_info.cpp
        capi/sk_yuva_pixmaps.cpp
)

if(RESKIA_ENABLE_AVIF)
    list(APPEND SOURCE_FILES capi/sk_avif_decoder.cpp)
endif()

if(RESKIA_ENABLE_JPEGXL)
    list(APPEND SOURCE_FILES capi/sk_jpegxl_decoder.cpp)
endif()

if(RESKIA_ENABLE_GIF)
    list(APPEND SOURCE_FILES capi/sk_gif_decoder.cpp)
endif()

if(RESKIA_ENABLE_RAW)
    list(APPEND SOURCE_FILES capi/sk_raw_decoder.cpp)
endif()

if(RESKIA_ENABLE_JPEG_ENCODER)
    list(APPEND SOURCE_FILES capi/sk_jpeg_encoder.cpp)
endif()

if(RESKIA_ENABLE_WEBP_ENCODER)
    list(APPEND SOURCE_FILES capi/sk_webp_encoder.cpp)
endif()

if(RESKIA_ENABLE_PDF)
    list(APPEND SOURCE_FILES capi/sk_pdf.cpp)
endif()

list(APPEND SOURCE_FILES capi/sk_open_type_svg_decoder.cpp)
