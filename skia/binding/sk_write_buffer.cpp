//
// Created by dolphilia on 25/02/17.
//

#include "sk_write_buffer.h"

#include "src/core/SkWriteBuffer.h"

#include "../static/static_std_string_view.h"
#include "../static/static_std_string_view-internal.h"

extern "C" {

void SkWriteBuffer_delete(void * writeBuffer) {
    delete static_cast<SkWriteBuffer *>(writeBuffer);
}

void SkWriteBuffer_writePad32(void * writeBuffer, const void * buffer, size_t bytes) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writePad32(buffer, bytes);
}

void SkWriteBuffer_writeByteArray(void * writeBuffer, const void * data, size_t size) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeByteArray(data, size);
}

void SkWriteBuffer_writeDataAsByteArray(void * writeBuffer, const void * data) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeDataAsByteArray(static_cast<const SkData *>(data));
}

void SkWriteBuffer_writeBool(void * writeBuffer, bool value) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeBool(value);
}

void SkWriteBuffer_writeScalar(void * writeBuffer, float value) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeScalar(value);
}

void SkWriteBuffer_writeScalarArray(void * writeBuffer, const void * value, uint32_t count) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeScalarArray(static_cast<const SkScalar *>(value), count);
}

void SkWriteBuffer_writeInt(void * writeBuffer, int32_t value) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeInt(value);
}

void SkWriteBuffer_writeIntArray(void * writeBuffer, const void * value, uint32_t count) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeIntArray(static_cast<const int32_t *>(value), count);
}

void SkWriteBuffer_writeUInt(void * writeBuffer, uint32_t value) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeUInt(value);
}

void SkWriteBuffer_write32(void * writeBuffer, int32_t value) {
    static_cast<SkWriteBuffer *>(writeBuffer)->write32(value);
}

void SkWriteBuffer_writeString(void * writeBuffer, string_view_t value) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeString(static_string_view_get(value));
}

void SkWriteBuffer_writeFlattenable(void * writeBuffer, const void * flattenable) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeFlattenable(static_cast<const SkFlattenable *>(flattenable));
}

void SkWriteBuffer_writeColor(void * writeBuffer, unsigned int color) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeColor(color);
}

void SkWriteBuffer_writeColorArray(void * writeBuffer, const void * color, uint32_t count) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeColorArray(static_cast<const SkColor *>(color), count);
}

void SkWriteBuffer_writeColor4f(void * writeBuffer, const void * color) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeColor4f(* static_cast<const SkColor4f *>(color));
}

void SkWriteBuffer_writeColor4fArray(void * writeBuffer, const void * color, uint32_t count) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeColor4fArray(static_cast<const SkColor4f *>(color), count);
}

void SkWriteBuffer_writePoint(void * writeBuffer, const void * point) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writePoint(* static_cast<const SkPoint *>(point));
}

void SkWriteBuffer_writePointArray(void * writeBuffer, const void * point, uint32_t count) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writePointArray(static_cast<const SkPoint *>(point), count);
}

void SkWriteBuffer_writePoint3(void * writeBuffer, const void * point) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writePoint3(* static_cast<const SkPoint3 *>(point));
}

void SkWriteBuffer_write(void * writeBuffer, const void * m44) {
    static_cast<SkWriteBuffer *>(writeBuffer)->write(* static_cast<const SkM44 *>(m44));
}

void SkWriteBuffer_writeMatrix(void * writeBuffer, const void * matrix) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeMatrix(* static_cast<const SkMatrix *>(matrix));
}

void SkWriteBuffer_writeIRect(void * writeBuffer, const void * rect) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeIRect(* static_cast<const SkIRect *>(rect));
}

void SkWriteBuffer_writeRect(void * writeBuffer, const void * rect) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeRect(* static_cast<const SkRect *>(rect));
}

void SkWriteBuffer_writeRegion(void * writeBuffer, const void * region) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeRegion(* static_cast<const SkRegion *>(region));
}

void SkWriteBuffer_writeSampling(void * writeBuffer, const void * options) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeSampling(* static_cast<const SkSamplingOptions *>(options));
}

void SkWriteBuffer_writePath(void * writeBuffer, const void * path) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writePath(* static_cast<const SkPath *>(path));
}

size_t SkWriteBuffer_writeStream(void * writeBuffer, void * stream, size_t length) {
    return static_cast<SkWriteBuffer *>(writeBuffer)->writeStream(static_cast<SkStream *>(stream), length);
}

void SkWriteBuffer_writeImage(void * writeBuffer, const void * image) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeImage(static_cast<const SkImage *>(image));
}

void SkWriteBuffer_writeTypeface(void * writeBuffer, void * typeface) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writeTypeface(static_cast<SkTypeface *>(typeface));
}

void SkWriteBuffer_writePaint(void * writeBuffer, const void * paint) {
    static_cast<SkWriteBuffer *>(writeBuffer)->writePaint(* static_cast<const SkPaint *>(paint));
}

const void * SkWriteBuffer_serialProcs(void * writeBuffer) {
    return &static_cast<SkWriteBuffer *>(writeBuffer)->serialProcs();
}

}
