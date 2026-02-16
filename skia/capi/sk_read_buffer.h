//
// Created by dolphilia on 25/02/17.
//

#ifndef SK_READ_BUFFER_H
#define SK_READ_BUFFER_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image_filter.h"
#include "../handles/static_sk_mask_filter.h"
#include "../handles/static_sk_paint.h"
#include "../handles/static_sk_path_effect.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_sampling_options.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_typeface.h"

typedef struct reskia_color_4f_t reskia_color_4f_t;
typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_flattenable_t reskia_flattenable_t;
typedef struct reskia_i_rect_t reskia_i_rect_t;
typedef struct reskia_m_44_t reskia_m_44_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_point_3_t reskia_point_3_t;
typedef struct reskia_point_t reskia_point_t;
typedef struct reskia_r_rect_t reskia_r_rect_t;
typedef struct reskia_read_buffer_t reskia_read_buffer_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_region_t reskia_region_t;
typedef struct reskia_string_t reskia_string_t;
typedef int32_t reskia_read_buffer_version_t;
typedef int32_t reskia_read_buffer_flattenable_type_t;
typedef int32_t reskia_read_buffer_legacy_fq_t;

#ifdef __cplusplus
extern "C" {
#endif

reskia_read_buffer_t *SkReadBuffer_new(); // () -> SkReadBuffer*
reskia_read_buffer_t *SkReadBuffer_newWithDataAndSize(const void* data, size_t size); // (const void* data, size_t size) -> SkReadBuffer*
void SkReadBuffer_delete(reskia_read_buffer_t *rect); // (SkReadBuffer* rect)
void SkReadBuffer_setMemory(reskia_read_buffer_t *buffer, const void* data, size_t size); // (SkReadBuffer* buffer, const void* data, size_t size)
bool SkReadBuffer_isVersionLT(reskia_read_buffer_t *buffer, reskia_read_buffer_version_t targetVersion); // (SkReadBuffer* buffer, SkPicturePriv::Version targetVersion) -> bool
uint32_t SkReadBuffer_getVersion(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> uint32_t
void SkReadBuffer_setVersion(reskia_read_buffer_t *buffer, int version); // (SkReadBuffer* buffer, int version)
size_t SkReadBuffer_size(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> size_t
size_t SkReadBuffer_offset(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> size_t
bool SkReadBuffer_eof(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> bool
const void* SkReadBuffer_skip(reskia_read_buffer_t *buffer, size_t size); // (SkReadBuffer* buffer, size_t size) -> const void*
const void* SkReadBuffer_skipCount(reskia_read_buffer_t *buffer, size_t count, size_t size); // (SkReadBuffer* buffer, size_t count, size_t size) -> const void*
size_t SkReadBuffer_available(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> size_t

// template <typename T> const T* skipT()
// template <typename T> const T* skipT(size_t count)

bool SkReadBuffer_readBool(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> bool
uint32_t SkReadBuffer_readColor(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> SkColor
int32_t SkReadBuffer_readInt(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> int32_t
float SkReadBuffer_readScalar(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> SkScalar
uint32_t SkReadBuffer_readUInt(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> uint32_t
int32_t SkReadBuffer_read32(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> int32_t

// template <typename T> T read32LE(T max)

uint8_t SkReadBuffer_peekByte(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> uint8_t
void SkReadBuffer_readString(reskia_read_buffer_t *buffer, reskia_string_t *string); // (SkReadBuffer* buffer, SkString* string)
void SkReadBuffer_readColor4f(reskia_read_buffer_t *buffer, reskia_color_4f_t *color); // (SkReadBuffer* buffer, SkColor4f* color)
void SkReadBuffer_readPoint(reskia_read_buffer_t *buffer, reskia_point_t *point); // (SkReadBuffer* buffer, SkPoint* point)
sk_point_t SkReadBuffer_readPointValue(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_point_t
void SkReadBuffer_readPoint3(reskia_read_buffer_t *buffer, reskia_point_3_t *point); // (SkReadBuffer* buffer, SkPoint3* point)
void SkReadBuffer_read(reskia_read_buffer_t *buffer, reskia_m_44_t *m44); // (SkReadBuffer* buffer, SkM44* m44)
void SkReadBuffer_readMatrix(reskia_read_buffer_t *buffer, reskia_matrix_t *matrix); // (SkReadBuffer* buffer, SkMatrix* matrix)
void SkReadBuffer_readIRect(reskia_read_buffer_t *buffer, reskia_i_rect_t *rect); // (SkReadBuffer* buffer, SkIRect* rect)
void SkReadBuffer_readRect(reskia_read_buffer_t *buffer, reskia_rect_t *rect); // (SkReadBuffer* buffer, SkRect* rect)
sk_rect_t SkReadBuffer_readRectValue(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_rect_t
void SkReadBuffer_readRRect(reskia_read_buffer_t *buffer, reskia_r_rect_t *rrect); // (SkReadBuffer* buffer, SkRRect* rrect)
void SkReadBuffer_readRegion(reskia_read_buffer_t *buffer, reskia_region_t *region); // (SkReadBuffer* buffer, SkRegion* region)
void SkReadBuffer_readPath(reskia_read_buffer_t *buffer, reskia_path_t *path); // (SkReadBuffer* buffer, SkPath* path)
sk_paint_t SkReadBuffer_readPaint(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_paint_t
reskia_flattenable_t *SkReadBuffer_readRawFlattenable(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> SkFlattenable*
reskia_flattenable_t *SkReadBuffer_readFlattenable(reskia_read_buffer_t *buffer, reskia_read_buffer_flattenable_type_t type); // (SkReadBuffer* buffer, SkFlattenable::Type type) -> SkFlattenable*

// template <typename T> sk_sp<T> readFlattenable()

sk_color_filter_t SkReadBuffer_readColorFilter(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_color_filter_t
sk_image_filter_t SkReadBuffer_readImageFilter(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_image_filter_t
sk_blender_t SkReadBuffer_readBlender(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_blender_t
sk_mask_filter_t SkReadBuffer_readMaskFilter(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_mask_filter_t
sk_path_effect_t SkReadBuffer_readPathEffect(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_path_effect_t
sk_shader_t SkReadBuffer_readShader(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_shader_t
bool SkReadBuffer_readPad32(reskia_read_buffer_t *readBuffer, void *buffer, size_t bytes); // (SkReadBuffer* readBuffer, void* buffer, size_t bytes) -> bool
bool SkReadBuffer_readByteArray(reskia_read_buffer_t *buffer, void *value, size_t size); // (SkReadBuffer* buffer, void* value, size_t size) -> bool
bool SkReadBuffer_readColorArray(reskia_read_buffer_t *buffer, uint32_t *colors, size_t size); // (SkReadBuffer* buffer, SkColor* colors, size_t size) -> bool
bool SkReadBuffer_readColor4fArray(reskia_read_buffer_t *buffer, reskia_color_4f_t *colors, size_t size); // (SkReadBuffer* buffer, SkColor4f* colors, size_t size) -> bool
bool SkReadBuffer_readIntArray(reskia_read_buffer_t *buffer, int32_t *values, size_t size); // (SkReadBuffer* buffer, int32_t* values, size_t size) -> bool
bool SkReadBuffer_readPointArray(reskia_read_buffer_t *buffer, reskia_point_t *points, size_t size); // (SkReadBuffer* buffer, SkPoint* points, size_t size) -> bool
bool SkReadBuffer_readScalarArray(reskia_read_buffer_t *buffer, float *values, size_t size); // (SkReadBuffer* buffer, SkScalar* values, size_t size) -> bool
const void* SkReadBuffer_skipByteArray(reskia_read_buffer_t *buffer, size_t *size); // (SkReadBuffer* buffer, size_t* size) -> const void*
sk_data_t SkReadBuffer_readByteArrayAsData(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_data_t
uint32_t SkReadBuffer_getArrayCount(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> uint32_t
sk_image_t SkReadBuffer_readImage(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_image_t
sk_typeface_t SkReadBuffer_readTypeface(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_typeface_t
void SkReadBuffer_setTypefaceArray(reskia_read_buffer_t *buffer, void * array, int count); // (SkReadBuffer* buffer, sk_sp<SkTypeface>* array, int count)
void SkReadBuffer_setFactoryPlayback(reskia_read_buffer_t *buffer, void * array, int count); // (SkReadBuffer* buffer, SkFlattenable::Factory* array, int count)
void SkReadBuffer_setDeserialProcs(reskia_read_buffer_t *buffer, const reskia_deserial_procs_t *procs); // (SkReadBuffer* buffer, const SkDeserialProcs* procs)
const reskia_deserial_procs_t *SkReadBuffer_getDeserialProcs(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> const SkDeserialProcs*
bool SkReadBuffer_allowSkSL(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> bool
void SkReadBuffer_setAllowSkSL(reskia_read_buffer_t *buffer, bool allow); // (SkReadBuffer* buffer, bool allow)
bool SkReadBuffer_validate(reskia_read_buffer_t *buffer, bool isValid); // (SkReadBuffer* buffer, bool isValid) -> bool

// template <typename T> bool validateCanReadN(size_t n)

bool SkReadBuffer_isValid(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> bool
bool SkReadBuffer_validateIndex(reskia_read_buffer_t *buffer, int index, int count); // (SkReadBuffer* buffer, int index, int count) -> bool
int SkReadBuffer_checkInt(reskia_read_buffer_t *buffer, int min, int max); // (SkReadBuffer* buffer, int min, int max) -> int32_t

// template <typename T> T checkRange(T min, T max)

reskia_read_buffer_legacy_fq_t SkReadBuffer_checkFilterQuality(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> SkLegacyFQ
sk_sampling_options_t SkReadBuffer_readSampling(reskia_read_buffer_t *buffer); // (SkReadBuffer* buffer) -> sk_sampling_options_t

#ifdef __cplusplus
}
#endif

#endif //SK_READ_BUFFER_H
