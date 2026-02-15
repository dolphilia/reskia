//
// Created by dolphilia on 25/02/17.
//

#include "sk_write_buffer.h"

#include "src/core/SkWriteBuffer.h"

#include "../static/static_std_string_view.h"
#include "../static/static_std_string_view-internal.h"

extern "C" {

void SkWriteBuffer_delete(reskia_write_buffer_t *writeBuffer) {
    delete reinterpret_cast<SkWriteBuffer *>(writeBuffer);
}

void SkWriteBuffer_writePad32(reskia_write_buffer_t *writeBuffer, const void *buffer, size_t bytes) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writePad32(buffer, bytes);
}

void SkWriteBuffer_writeByteArray(reskia_write_buffer_t *writeBuffer, const void *data, size_t size) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeByteArray(data, size);
}

void SkWriteBuffer_writeDataAsByteArray(reskia_write_buffer_t *writeBuffer, const reskia_data_t *data) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeDataAsByteArray(reinterpret_cast<const SkData *>(data));
}

void SkWriteBuffer_writeBool(reskia_write_buffer_t *writeBuffer, bool value) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeBool(value);
}

void SkWriteBuffer_writeScalar(reskia_write_buffer_t *writeBuffer, float value) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeScalar(value);
}

void SkWriteBuffer_writeScalarArray(reskia_write_buffer_t *writeBuffer, const float *value, uint32_t count) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeScalarArray(value, count);
}

void SkWriteBuffer_writeInt(reskia_write_buffer_t *writeBuffer, int32_t value) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeInt(value);
}

void SkWriteBuffer_writeIntArray(reskia_write_buffer_t *writeBuffer, const int32_t *value, uint32_t count) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeIntArray(value, count);
}

void SkWriteBuffer_writeUInt(reskia_write_buffer_t *writeBuffer, uint32_t value) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeUInt(value);
}

void SkWriteBuffer_write32(reskia_write_buffer_t *writeBuffer, int32_t value) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->write32(value);
}

void SkWriteBuffer_writeString(reskia_write_buffer_t *writeBuffer, int value) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeString(static_string_view_get_entity(value));
}

void SkWriteBuffer_writeFlattenable(reskia_write_buffer_t *writeBuffer, const reskia_flattenable_t *flattenable) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeFlattenable(reinterpret_cast<const SkFlattenable *>(flattenable));
}

void SkWriteBuffer_writeColor(reskia_write_buffer_t *writeBuffer, reskia_color_t color) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeColor(color);
}

void SkWriteBuffer_writeColorArray(reskia_write_buffer_t *writeBuffer, const reskia_color_t *color, uint32_t count) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeColorArray(reinterpret_cast<const SkColor *>(color), count);
}

void SkWriteBuffer_writeColor4f(reskia_write_buffer_t *writeBuffer, const reskia_color_4f_t *color) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeColor4f(*reinterpret_cast<const SkColor4f *>(color));
}

void SkWriteBuffer_writeColor4fArray(reskia_write_buffer_t *writeBuffer, const reskia_color_4f_t *color, uint32_t count) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeColor4fArray(reinterpret_cast<const SkColor4f *>(color), count);
}

void SkWriteBuffer_writePoint(reskia_write_buffer_t *writeBuffer, const reskia_point_t *point) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writePoint(*reinterpret_cast<const SkPoint *>(point));
}

void SkWriteBuffer_writePointArray(reskia_write_buffer_t *writeBuffer, const reskia_point_t *point, uint32_t count) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writePointArray(reinterpret_cast<const SkPoint *>(point), count);
}

void SkWriteBuffer_writePoint3(reskia_write_buffer_t *writeBuffer, const reskia_point3_t *point) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writePoint3(*reinterpret_cast<const SkPoint3 *>(point));
}

void SkWriteBuffer_write(reskia_write_buffer_t *writeBuffer, const reskia_m_44_t *m44) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->write(*reinterpret_cast<const SkM44 *>(m44));
}

void SkWriteBuffer_writeMatrix(reskia_write_buffer_t *writeBuffer, const reskia_matrix_t *matrix) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeMatrix(*reinterpret_cast<const SkMatrix *>(matrix));
}

void SkWriteBuffer_writeIRect(reskia_write_buffer_t *writeBuffer, const reskia_i_rect_t *rect) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeIRect(*reinterpret_cast<const SkIRect *>(rect));
}

void SkWriteBuffer_writeRect(reskia_write_buffer_t *writeBuffer, const reskia_rect_t *rect) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeRect(*reinterpret_cast<const SkRect *>(rect));
}

void SkWriteBuffer_writeRegion(reskia_write_buffer_t *writeBuffer, const reskia_region_t *region) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeRegion(*reinterpret_cast<const SkRegion *>(region));
}

void SkWriteBuffer_writeSampling(reskia_write_buffer_t *writeBuffer, const reskia_sampling_options_t *options) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeSampling(*reinterpret_cast<const SkSamplingOptions *>(options));
}

void SkWriteBuffer_writePath(reskia_write_buffer_t *writeBuffer, const reskia_path_t *path) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writePath(*reinterpret_cast<const SkPath *>(path));
}

size_t SkWriteBuffer_writeStream(reskia_write_buffer_t *writeBuffer, reskia_stream_t *stream, size_t length) {
    return reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeStream(reinterpret_cast<SkStream *>(stream), length);
}

void SkWriteBuffer_writeImage(reskia_write_buffer_t *writeBuffer, const reskia_image_t *image) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeImage(reinterpret_cast<const SkImage *>(image));
}

void SkWriteBuffer_writeTypeface(reskia_write_buffer_t *writeBuffer, reskia_typeface_t *typeface) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writeTypeface(reinterpret_cast<SkTypeface *>(typeface));
}

void SkWriteBuffer_writePaint(reskia_write_buffer_t *writeBuffer, const reskia_paint_t *paint) {
    reinterpret_cast<SkWriteBuffer *>(writeBuffer)->writePaint(*reinterpret_cast<const SkPaint *>(paint));
}

const reskia_serial_procs_t *SkWriteBuffer_serialProcs(reskia_write_buffer_t *writeBuffer) {
    return reinterpret_cast<const reskia_serial_procs_t *>(&reinterpret_cast<SkWriteBuffer *>(writeBuffer)->serialProcs());
}

}
