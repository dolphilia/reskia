//
// Created by dolphilia on 25/02/17.
//

#ifndef SK_WRITE_BUFFER_H
#define SK_WRITE_BUFFER_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef uint32_t reskia_color_t;
typedef struct reskia_data_t reskia_data_t;
typedef struct reskia_flattenable_t reskia_flattenable_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_m_44_t reskia_m_44_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_paint_t reskia_paint_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point3_t reskia_point3_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_region_t reskia_region_t;
typedef struct reskia_sampling_options_t reskia_sampling_options_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_stream_t reskia_stream_t;
typedef struct reskia_typeface_t reskia_typeface_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkWriteBuffer_delete(reskia_write_buffer_t *writeBuffer);
void SkWriteBuffer_writePad32(reskia_write_buffer_t *writeBuffer, const void *buffer, size_t bytes); // (SkWriteBuffer* writeBuffer, const void* buffer, size_t bytes)
void SkWriteBuffer_writeByteArray(reskia_write_buffer_t *writeBuffer, const void *data, size_t size); // (SkWriteBuffer* writeBuffer, const void* data, size_t size)
void SkWriteBuffer_writeDataAsByteArray(reskia_write_buffer_t *writeBuffer, const reskia_data_t *data); // (SkWriteBuffer* writeBuffer, const SkData* data)
void SkWriteBuffer_writeBool(reskia_write_buffer_t *writeBuffer, bool value); // (SkWriteBuffer* writeBuffer, bool value)
void SkWriteBuffer_writeScalar(reskia_write_buffer_t *writeBuffer, float value); // (SkWriteBuffer* writeBuffer, SkScalar value)
void SkWriteBuffer_writeScalarArray(reskia_write_buffer_t *writeBuffer, const float *value, uint32_t count); // (SkWriteBuffer* writeBuffer, const SkScalar* value, uint32_t count)
void SkWriteBuffer_writeInt(reskia_write_buffer_t *writeBuffer, int32_t value); // (SkWriteBuffer* writeBuffer, int32_t value)
void SkWriteBuffer_writeIntArray(reskia_write_buffer_t *writeBuffer, const int32_t *value, uint32_t count); // (SkWriteBuffer* writeBuffer, const int32_t* value, uint32_t count)
void SkWriteBuffer_writeUInt(reskia_write_buffer_t *writeBuffer, uint32_t value); // (SkWriteBuffer* writeBuffer, uint32_t value)
void SkWriteBuffer_write32(reskia_write_buffer_t *writeBuffer, int32_t value); // (SkWriteBuffer* writeBuffer, int32_t value)
void SkWriteBuffer_writeString(reskia_write_buffer_t *writeBuffer, int value); // (SkWriteBuffer* writeBuffer, string_view_t value)
void SkWriteBuffer_writeFlattenable(reskia_write_buffer_t *writeBuffer, const reskia_flattenable_t *flattenable); // (SkWriteBuffer* writeBuffer, const SkFlattenable* flattenable)
void SkWriteBuffer_writeColor(reskia_write_buffer_t *writeBuffer, reskia_color_t color); // (SkWriteBuffer* writeBuffer, SkColor color)
void SkWriteBuffer_writeColorArray(reskia_write_buffer_t *writeBuffer, const reskia_color_t *color, uint32_t count); // (SkWriteBuffer* writeBuffer, const SkColor* color, uint32_t count)
void SkWriteBuffer_writeColor4f(reskia_write_buffer_t *writeBuffer, const reskia_color_4f_t *color); // (SkWriteBuffer* writeBuffer, const SkColor4f* color)
void SkWriteBuffer_writeColor4fArray(reskia_write_buffer_t *writeBuffer, const reskia_color_4f_t *color, uint32_t count); // (SkWriteBuffer* writeBuffer, const SkColor4f* color, uint32_t count)
void SkWriteBuffer_writePoint(reskia_write_buffer_t *writeBuffer, const reskia_point_t *point); // (SkWriteBuffer* writeBuffer, const SkPoint* point)
void SkWriteBuffer_writePointArray(reskia_write_buffer_t *writeBuffer, const reskia_point_t *point, uint32_t count); // (SkWriteBuffer* writeBuffer, const SkPoint* point, uint32_t count)
void SkWriteBuffer_writePoint3(reskia_write_buffer_t *writeBuffer, const reskia_point3_t *point); // (SkWriteBuffer* writeBuffer, const SkPoint3* point)
void SkWriteBuffer_write(reskia_write_buffer_t *writeBuffer, const reskia_m_44_t *m44); // (SkWriteBuffer* writeBuffer, const SkM44* m44)
void SkWriteBuffer_writeMatrix(reskia_write_buffer_t *writeBuffer, const reskia_matrix_t *matrix); // (SkWriteBuffer* writeBuffer, const SkMatrix* matrix)
void SkWriteBuffer_writeIRect(reskia_write_buffer_t *writeBuffer, const reskia_i_rect_t *rect); // (SkWriteBuffer* writeBuffer, const SkIRect* rect)
void SkWriteBuffer_writeRect(reskia_write_buffer_t *writeBuffer, const reskia_rect_t *rect); // (SkWriteBuffer* writeBuffer, const SkRect* rect)
void SkWriteBuffer_writeRegion(reskia_write_buffer_t *writeBuffer, const reskia_region_t *region); // (SkWriteBuffer* writeBuffer, const SkRegion* region)
void SkWriteBuffer_writeSampling(reskia_write_buffer_t *writeBuffer, const reskia_sampling_options_t *options); // (SkWriteBuffer* writeBuffer, const SkSamplingOptions* options)
void SkWriteBuffer_writePath(reskia_write_buffer_t *writeBuffer, const reskia_path_t *path); // (SkWriteBuffer* writeBuffer, const SkPath* path)
size_t SkWriteBuffer_writeStream(reskia_write_buffer_t *writeBuffer, reskia_stream_t *stream, size_t length); // (SkWriteBuffer* writeBuffer, SkStream* stream, size_t length) -> size_t
void SkWriteBuffer_writeImage(reskia_write_buffer_t *writeBuffer, const reskia_image_t *image); // (SkWriteBuffer* writeBuffer, const SkImage* image)
void SkWriteBuffer_writeTypeface(reskia_write_buffer_t *writeBuffer, reskia_typeface_t *typeface); // (SkWriteBuffer* writeBuffer, SkTypeface* typeface)
void SkWriteBuffer_writePaint(reskia_write_buffer_t *writeBuffer, const reskia_paint_t *paint); // (SkWriteBuffer* writeBuffer, const SkPaint& paint)
const reskia_serial_procs_t *SkWriteBuffer_serialProcs(reskia_write_buffer_t *writeBuffer); // (SkWriteBuffer* writeBuffer) -> const SkSerialProcs*

#ifdef __cplusplus
}
#endif

#endif //SK_WRITE_BUFFER_H
