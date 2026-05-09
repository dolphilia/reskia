//
// Created by dolphilia on 25/02/17.
//

#include "sk_write_buffer.h"

#include "src/core/SkWriteBuffer.h"

#include "../handles/static_std_string_view.h"
#include "../handles/static_std_string_view-internal.h"

namespace {

SkWriteBuffer *as_write_buffer(reskia_write_buffer_t *writeBuffer) {
    return reinterpret_cast<SkWriteBuffer *>(writeBuffer);
}

template <typename T>
bool has_input(const T *ptr, size_t count) {
    return count == 0 || ptr != nullptr;
}

} // namespace

extern "C" {

void SkWriteBuffer_delete(reskia_write_buffer_t *writeBuffer) {
    delete as_write_buffer(writeBuffer);
}

void SkWriteBuffer_writePad32(reskia_write_buffer_t *writeBuffer, const void *buffer, size_t bytes) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || !has_input(buffer, bytes)) {
        return;
    }
    writer->writePad32(buffer, bytes);
}

void SkWriteBuffer_writeByteArray(reskia_write_buffer_t *writeBuffer, const void *data, size_t size) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || !has_input(data, size)) {
        return;
    }
    writer->writeByteArray(data, size);
}

void SkWriteBuffer_writeDataAsByteArray(reskia_write_buffer_t *writeBuffer, const reskia_data_t *data) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeDataAsByteArray(reinterpret_cast<const SkData *>(data));
}

void SkWriteBuffer_writeBool(reskia_write_buffer_t *writeBuffer, bool value) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeBool(value);
}

void SkWriteBuffer_writeScalar(reskia_write_buffer_t *writeBuffer, float value) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeScalar(value);
}

void SkWriteBuffer_writeScalarArray(reskia_write_buffer_t *writeBuffer, const float *value, uint32_t count) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || !has_input(value, count)) {
        return;
    }
    writer->writeScalarArray(value, count);
}

void SkWriteBuffer_writeInt(reskia_write_buffer_t *writeBuffer, int32_t value) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeInt(value);
}

void SkWriteBuffer_writeIntArray(reskia_write_buffer_t *writeBuffer, const int32_t *value, uint32_t count) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || !has_input(value, count)) {
        return;
    }
    writer->writeIntArray(value, count);
}

void SkWriteBuffer_writeUInt(reskia_write_buffer_t *writeBuffer, uint32_t value) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeUInt(value);
}

void SkWriteBuffer_write32(reskia_write_buffer_t *writeBuffer, int32_t value) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->write32(value);
}

void SkWriteBuffer_writeString(reskia_write_buffer_t *writeBuffer, int value) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeString(static_string_view_get_entity(value));
}

void SkWriteBuffer_writeFlattenable(reskia_write_buffer_t *writeBuffer, const reskia_flattenable_t *flattenable) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeFlattenable(reinterpret_cast<const SkFlattenable *>(flattenable));
}

void SkWriteBuffer_writeColor(reskia_write_buffer_t *writeBuffer, reskia_color_t color) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeColor(color);
}

void SkWriteBuffer_writeColorArray(reskia_write_buffer_t *writeBuffer, const reskia_color_t *color, uint32_t count) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || !has_input(color, count)) {
        return;
    }
    writer->writeColorArray(reinterpret_cast<const SkColor *>(color), count);
}

void SkWriteBuffer_writeColor4f(reskia_write_buffer_t *writeBuffer, const reskia_color_4f_t *color) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || color == nullptr) {
        return;
    }
    writer->writeColor4f(*reinterpret_cast<const SkColor4f *>(color));
}

void SkWriteBuffer_writeColor4fArray(reskia_write_buffer_t *writeBuffer, const reskia_color_4f_t *color, uint32_t count) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || !has_input(color, count)) {
        return;
    }
    writer->writeColor4fArray(reinterpret_cast<const SkColor4f *>(color), count);
}

void SkWriteBuffer_writePoint(reskia_write_buffer_t *writeBuffer, const reskia_point_t *point) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || point == nullptr) {
        return;
    }
    writer->writePoint(*reinterpret_cast<const SkPoint *>(point));
}

void SkWriteBuffer_writePointArray(reskia_write_buffer_t *writeBuffer, const reskia_point_t *point, uint32_t count) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || !has_input(point, count)) {
        return;
    }
    writer->writePointArray(reinterpret_cast<const SkPoint *>(point), count);
}

void SkWriteBuffer_writePoint3(reskia_write_buffer_t *writeBuffer, const reskia_point3_t *point) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || point == nullptr) {
        return;
    }
    writer->writePoint3(*reinterpret_cast<const SkPoint3 *>(point));
}

void SkWriteBuffer_write(reskia_write_buffer_t *writeBuffer, const reskia_m_44_t *m44) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || m44 == nullptr) {
        return;
    }
    writer->write(*reinterpret_cast<const SkM44 *>(m44));
}

void SkWriteBuffer_writeMatrix(reskia_write_buffer_t *writeBuffer, const reskia_matrix_t *matrix) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || matrix == nullptr) {
        return;
    }
    writer->writeMatrix(*reinterpret_cast<const SkMatrix *>(matrix));
}

void SkWriteBuffer_writeIRect(reskia_write_buffer_t *writeBuffer, const reskia_i_rect_t *rect) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || rect == nullptr) {
        return;
    }
    writer->writeIRect(*reinterpret_cast<const SkIRect *>(rect));
}

void SkWriteBuffer_writeRect(reskia_write_buffer_t *writeBuffer, const reskia_rect_t *rect) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || rect == nullptr) {
        return;
    }
    writer->writeRect(*reinterpret_cast<const SkRect *>(rect));
}

void SkWriteBuffer_writeRegion(reskia_write_buffer_t *writeBuffer, const reskia_region_t *region) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || region == nullptr) {
        return;
    }
    writer->writeRegion(*reinterpret_cast<const SkRegion *>(region));
}

void SkWriteBuffer_writeSampling(reskia_write_buffer_t *writeBuffer, const reskia_sampling_options_t *options) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || options == nullptr) {
        return;
    }
    writer->writeSampling(*reinterpret_cast<const SkSamplingOptions *>(options));
}

void SkWriteBuffer_writePath(reskia_write_buffer_t *writeBuffer, const reskia_path_t *path) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || path == nullptr) {
        return;
    }
    writer->writePath(*reinterpret_cast<const SkPath *>(path));
}

size_t SkWriteBuffer_writeStream(reskia_write_buffer_t *writeBuffer, reskia_stream_t *stream, size_t length) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || stream == nullptr) {
        return 0;
    }
    return writer->writeStream(reinterpret_cast<SkStream *>(stream), length);
}

void SkWriteBuffer_writeImage(reskia_write_buffer_t *writeBuffer, const reskia_image_t *image) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeImage(reinterpret_cast<const SkImage *>(image));
}

void SkWriteBuffer_writeTypeface(reskia_write_buffer_t *writeBuffer, reskia_typeface_t *typeface) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return;
    }
    writer->writeTypeface(reinterpret_cast<SkTypeface *>(typeface));
}

void SkWriteBuffer_writePaint(reskia_write_buffer_t *writeBuffer, const reskia_paint_t *paint) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr || paint == nullptr) {
        return;
    }
    writer->writePaint(*reinterpret_cast<const SkPaint *>(paint));
}

const reskia_serial_procs_t *SkWriteBuffer_serialProcs(reskia_write_buffer_t *writeBuffer) {
    SkWriteBuffer *writer = as_write_buffer(writeBuffer);
    if (writer == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_serial_procs_t *>(&writer->serialProcs());
}

}
