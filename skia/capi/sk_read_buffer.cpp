//
// Created by dolphilia on 25/02/17.
//

#include "sk_read_buffer.h"

#include "src/core/SkReadBuffer.h"
#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkTypeface.h"

#include "../handles/static_sk_data.h"
#include "../handles/static_sk_data-internal.h"
#include "../handles/static_sk_image.h"
#include "../handles/static_sk_image-internal.h"
#include "../handles/static_sk_typeface.h"
#include "../handles/static_sk_typeface-internal.h"
#include "../handles/static_sk_sampling_options.h"
#include "../handles/static_sk_sampling_options-internal.h"
#include "../handles/static_sk_rect.h"
#include "../handles/static_sk_rect-internal.h"
#include "../handles/static_sk_paint.h"
#include "../handles/static_sk_paint-internal.h"
#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_filter-internal.h"
#include "../handles/static_sk_image_filter.h"
#include "../handles/static_sk_image_filter-internal.h"
#include "../handles/static_sk_blender.h"
#include "../handles/static_sk_blender-internal.h"
#include "../handles/static_sk_mask_filter.h"
#include "../handles/static_sk_mask_filter-internal.h"
#include "../handles/static_sk_path_effect.h"
#include "../handles/static_sk_path_effect-internal.h"
#include "../handles/static_sk_shader.h"
#include "../handles/static_sk_shader-internal.h"
#include "../handles/static_sk_point.h"
#include "../handles/static_sk_point-internal.h"

extern "C" {

reskia_read_buffer_t *SkReadBuffer_new() {
    return reinterpret_cast<reskia_read_buffer_t *>(new SkReadBuffer());
}

reskia_read_buffer_t *SkReadBuffer_new_2(const void* data, size_t size) {
    return reinterpret_cast<reskia_read_buffer_t *>(new SkReadBuffer(data, size));
}

void SkReadBuffer_delete(reskia_read_buffer_t *buffer) {
    delete reinterpret_cast<SkReadBuffer *>(buffer);
}

void SkReadBuffer_setMemory(reskia_read_buffer_t *buffer, const void* data, size_t size) {
    reinterpret_cast<SkReadBuffer *>(buffer)->setMemory(data, size);
}

bool SkReadBuffer_isVersionLT(reskia_read_buffer_t *buffer, reskia_read_buffer_version_t targetVersion) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->isVersionLT(static_cast<SkPicturePriv::Version>(targetVersion));
}

uint32_t SkReadBuffer_getVersion(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->getVersion();
}

void SkReadBuffer_setVersion(reskia_read_buffer_t *buffer, int version) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->setVersion(version);
}

size_t SkReadBuffer_size(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->size();
}

size_t SkReadBuffer_offset(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->offset();
}

bool SkReadBuffer_eof(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->eof();
}

const void* SkReadBuffer_skip(reskia_read_buffer_t *buffer, size_t size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->skip(size);
}

const void* SkReadBuffer_skip_2(reskia_read_buffer_t *buffer, size_t count, size_t size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->skip(count, size);
}

size_t SkReadBuffer_available(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->available();
}

// template <typename T> const T* skipT()
// template <typename T> const T* skipT(size_t count)

bool SkReadBuffer_readBool(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readBool();
}

SkColor SkReadBuffer_readColor(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readColor();
}

int32_t SkReadBuffer_readInt(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readInt();
}

SkScalar SkReadBuffer_readScalar(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readScalar();
}

uint32_t SkReadBuffer_readUInt(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readUInt();
}

int32_t SkReadBuffer_read32(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->read32();
}

// template <typename T> T read32LE(T max)

uint8_t SkReadBuffer_peekByte(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->peekByte();
}

void SkReadBuffer_readString(reskia_read_buffer_t *buffer, reskia_string_t *string) {
    reinterpret_cast<SkReadBuffer *>(buffer)->readString(reinterpret_cast<SkString *>(string));
}

void SkReadBuffer_readColor4f(reskia_read_buffer_t *buffer, reskia_color_4f_t *color) {
    reinterpret_cast<SkReadBuffer *>(buffer)->readColor4f(reinterpret_cast<SkColor4f *>(color));
}

void SkReadBuffer_readPoint(reskia_read_buffer_t *buffer, reskia_point_t *point) {
    reinterpret_cast<SkReadBuffer *>(buffer)->readPoint(reinterpret_cast<SkPoint *>(point));
}

sk_point_t SkReadBuffer_readPoint_2(reskia_read_buffer_t *buffer) {
    return static_sk_point_make(reinterpret_cast<SkReadBuffer *>(buffer)->readPoint());
}

void SkReadBuffer_readPoint3(reskia_read_buffer_t *buffer, reskia_point_3_t *point) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readPoint3(reinterpret_cast<SkPoint3 *>(point));
}

void SkReadBuffer_read(reskia_read_buffer_t *buffer, reskia_m_44_t *m44) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->read(reinterpret_cast<SkM44 *>(m44));
}

void SkReadBuffer_readMatrix(reskia_read_buffer_t *buffer, reskia_matrix_t *matrix) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readMatrix(reinterpret_cast<SkMatrix *>(matrix));
}

void SkReadBuffer_readIRect(reskia_read_buffer_t *buffer, reskia_i_rect_t *rect) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readIRect(reinterpret_cast<SkIRect *>(rect));
}

void SkReadBuffer_readRect(reskia_read_buffer_t *buffer, reskia_rect_t *rect) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readRect(reinterpret_cast<SkRect *>(rect));
}

sk_rect_t SkReadBuffer_readRect_2(reskia_read_buffer_t *buffer) {
    return static_sk_rect_make(reinterpret_cast<SkReadBuffer *>(buffer)->readRect());
}

void SkReadBuffer_readRRect(reskia_read_buffer_t *buffer, reskia_r_rect_t *rrect) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readRRect(reinterpret_cast<SkRRect *>(rrect));
}

void SkReadBuffer_readRegion(reskia_read_buffer_t *buffer, reskia_region_t *region) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readRegion(reinterpret_cast<SkRegion *>(region));
}

void SkReadBuffer_readPath(reskia_read_buffer_t *buffer, reskia_path_t *path) {
      return reinterpret_cast<SkReadBuffer *>(buffer)->readPath(reinterpret_cast<SkPath *>(path));
}

sk_paint_t SkReadBuffer_readPaint(reskia_read_buffer_t *buffer) {
    return static_sk_paint_make(reinterpret_cast<SkReadBuffer *>(buffer)->readPaint());
}

reskia_flattenable_t *SkReadBuffer_readRawFlattenable(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<reskia_flattenable_t *>(
            reinterpret_cast<SkReadBuffer *>(buffer)->readRawFlattenable());
}

reskia_flattenable_t *SkReadBuffer_readFlattenable(reskia_read_buffer_t *buffer, reskia_read_buffer_flattenable_type_t type) {
    return reinterpret_cast<reskia_flattenable_t *>(
            reinterpret_cast<SkReadBuffer *>(buffer)->readFlattenable(static_cast<SkFlattenable::Type>(type)));
}

// template <typename T> sk_sp<T> readFlattenable()

sk_color_filter_t SkReadBuffer_readColorFilter(reskia_read_buffer_t *buffer) {
    return static_sk_color_filter_make(reinterpret_cast<SkReadBuffer *>(buffer)->readColorFilter());
}

sk_image_filter_t SkReadBuffer_readImageFilter(reskia_read_buffer_t *buffer) {
    return static_sk_image_filter_make(reinterpret_cast<SkReadBuffer *>(buffer)->readImageFilter());
}

sk_blender_t SkReadBuffer_readBlender(reskia_read_buffer_t *buffer) {
    return static_sk_blender_make(reinterpret_cast<SkReadBuffer *>(buffer)->readBlender());
}

sk_mask_filter_t SkReadBuffer_readMaskFilter(reskia_read_buffer_t *buffer) {
    return static_sk_mask_filter_make(reinterpret_cast<SkReadBuffer *>(buffer)->readMaskFilter());
}

sk_path_effect_t SkReadBuffer_readPathEffect(reskia_read_buffer_t *buffer) {
    return static_sk_path_effect_make(reinterpret_cast<SkReadBuffer *>(buffer)->readPathEffect());
}

sk_shader_t SkReadBuffer_readShader(reskia_read_buffer_t *buffer) {
    return static_sk_shader_make(reinterpret_cast<SkReadBuffer *>(buffer)->readShader());
}

bool SkReadBuffer_readPad32(reskia_read_buffer_t *readBuffer, void *buffer, size_t bytes) {
    return reinterpret_cast<SkReadBuffer *>(readBuffer)->readPad32(buffer, bytes);
}

bool SkReadBuffer_readByteArray(reskia_read_buffer_t *buffer, void * value, size_t size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readByteArray(value, size);
}

bool SkReadBuffer_readColorArray(reskia_read_buffer_t *buffer, uint32_t *colors, size_t size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readColorArray(reinterpret_cast<SkColor *>(colors), size);
}

bool SkReadBuffer_readColor4fArray(reskia_read_buffer_t *buffer, reskia_color_4f_t *colors, size_t size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readColor4fArray(reinterpret_cast<SkColor4f *>(colors), size);
}

bool SkReadBuffer_readIntArray(reskia_read_buffer_t *buffer, int32_t *values, size_t size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readIntArray(reinterpret_cast<int32_t *>(values), size);
}

bool SkReadBuffer_readPointArray(reskia_read_buffer_t *buffer, reskia_point_t *points, size_t size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readPointArray(reinterpret_cast<SkPoint *>(points), size);
}

bool SkReadBuffer_readScalarArray(reskia_read_buffer_t *buffer, float *values, size_t size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->readScalarArray(reinterpret_cast<SkScalar *>(values), size);
}

const void* SkReadBuffer_skipByteArray(reskia_read_buffer_t *buffer, size_t *size) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->skipByteArray(reinterpret_cast<size_t *>(size));
}

sk_data_t SkReadBuffer_readByteArrayAsData(reskia_read_buffer_t *buffer) {
    return static_sk_data_make(reinterpret_cast<SkReadBuffer *>(buffer)->readByteArrayAsData());
}

uint32_t SkReadBuffer_getArrayCount(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->getArrayCount();
}

sk_image_t SkReadBuffer_readImage(reskia_read_buffer_t *buffer) {
    return static_sk_image_make(reinterpret_cast<SkReadBuffer *>(buffer)->readImage());
}

sk_typeface_t SkReadBuffer_readTypeface(reskia_read_buffer_t *buffer) {
    return static_sk_typeface_make(reinterpret_cast<SkReadBuffer *>(buffer)->readTypeface());
}

void SkReadBuffer_setTypefaceArray(reskia_read_buffer_t *buffer, void * array, int count) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->setTypefaceArray(static_cast<sk_sp<SkTypeface> *>(array), count);
}

void SkReadBuffer_setFactoryPlayback(reskia_read_buffer_t *buffer, void * array, int count) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->setFactoryPlayback(reinterpret_cast<SkFlattenable::Factory *>(array), count);
}

void SkReadBuffer_setDeserialProcs(reskia_read_buffer_t *buffer, const reskia_deserial_procs_t *procs) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->setDeserialProcs(* reinterpret_cast<const SkDeserialProcs *>(procs));
}

const reskia_deserial_procs_t *SkReadBuffer_getDeserialProcs(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<const reskia_deserial_procs_t *>(
            &reinterpret_cast<SkReadBuffer *>(buffer)->getDeserialProcs());
}

bool SkReadBuffer_allowSkSL(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->allowSkSL();
}

void SkReadBuffer_setAllowSkSL(reskia_read_buffer_t *buffer, bool allow) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->setAllowSkSL(allow);
}

bool SkReadBuffer_validate(reskia_read_buffer_t *buffer, bool isValid) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->validate(isValid);
}


// template <typename T> bool validateCanReadN(size_t n)

bool SkReadBuffer_isValid(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->isValid();
}

bool SkReadBuffer_validateIndex(reskia_read_buffer_t *buffer, int index, int count) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->validateIndex(index, count);
}

int32_t SkReadBuffer_checkInt(reskia_read_buffer_t *buffer, int min, int max) {
    return reinterpret_cast<SkReadBuffer *>(buffer)->checkInt(min, max);
}

// template <typename T> T checkRange(T min, T max)

reskia_read_buffer_legacy_fq_t SkReadBuffer_checkFilterQuality(reskia_read_buffer_t *buffer) {
    return static_cast<reskia_read_buffer_legacy_fq_t>(reinterpret_cast<SkReadBuffer *>(buffer)->checkFilterQuality());
}

sk_sampling_options_t SkReadBuffer_readSampling(reskia_read_buffer_t *buffer) {
    return static_sk_sampling_options_make(reinterpret_cast<SkReadBuffer *>(buffer)->readSampling());
}

}
