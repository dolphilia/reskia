//
// Created by dolphilia on 25/02/17.
//

#include "sk_read_buffer.h"

#include "src/core/SkReadBuffer.h"
#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkTypeface.h"

#include "../static/static_sk_data.h"
#include "../static/static_sk_data-internal.h"
#include "../static/static_sk_image.h"
#include "../static/static_sk_image-internal.h"
#include "../static/static_sk_typeface.h"
#include "../static/static_sk_typeface-internal.h"
#include "../static/static_sk_sampling_options.h"
#include "../static/static_sk_sampling_options-internal.h"
#include "../static/static_sk_rect.h"
#include "../static/static_sk_rect-internal.h"
#include "../static/static_sk_paint.h"
#include "../static/static_sk_paint-internal.h"
#include "../static/static_sk_color_filter.h"
#include "../static/static_sk_color_filter-internal.h"
#include "../static/static_sk_image_filter.h"
#include "../static/static_sk_image_filter-internal.h"
#include "../static/static_sk_blender.h"
#include "../static/static_sk_blender-internal.h"
#include "../static/static_sk_mask_filter.h"
#include "../static/static_sk_mask_filter-internal.h"
#include "../static/static_sk_path_effect.h"
#include "../static/static_sk_path_effect-internal.h"
#include "../static/static_sk_shader.h"
#include "../static/static_sk_shader-internal.h"
#include "../static/static_sk_point.h"
#include "../static/static_sk_point-internal.h"

extern "C" {

void * SkReadBuffer_new() {
    return new SkReadBuffer();
}

void * SkReadBuffer_new_2(const void* data, size_t size) {
    return new SkReadBuffer(data, size);
}

void SkReadBuffer_delete(void * buffer) {
    delete static_cast<SkReadBuffer *>(buffer);
}

void SkReadBuffer_setMemory(void * buffer, const void* data, size_t size) {
    static_cast<SkReadBuffer *>(buffer)->setMemory(data, size);
}

bool SkReadBuffer_isVersionLT(void * buffer, int targetVersion) {
    return static_cast<SkReadBuffer *>(buffer)->isVersionLT(static_cast<SkPicturePriv::Version>(targetVersion));
}

uint32_t SkReadBuffer_getVersion(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->getVersion();
}

void SkReadBuffer_setVersion(void * buffer, int version) {
    return static_cast<SkReadBuffer *>(buffer)->setVersion(version);
}

size_t SkReadBuffer_size(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->size();
}

size_t SkReadBuffer_offset(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->offset();
}

bool SkReadBuffer_eof(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->eof();
}

const void* SkReadBuffer_skip(void * buffer, size_t size) {
    return static_cast<SkReadBuffer *>(buffer)->skip(size);
}

const void* SkReadBuffer_skip_2(void * buffer, size_t count, size_t size) {
    return static_cast<SkReadBuffer *>(buffer)->skip(count, size);
}

size_t SkReadBuffer_available(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->available();
}

// template <typename T> const T* skipT()
// template <typename T> const T* skipT(size_t count)

bool SkReadBuffer_readBool(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->readBool();
}

SkColor SkReadBuffer_readColor(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->readColor();
}

int32_t SkReadBuffer_readInt(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->readInt();
}

SkScalar SkReadBuffer_readScalar(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->readScalar();
}

uint32_t SkReadBuffer_readUInt(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->readUInt();
}

int32_t SkReadBuffer_read32(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->read32();
}

// template <typename T> T read32LE(T max)

uint8_t SkReadBuffer_peekByte(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->peekByte();
}

void SkReadBuffer_readString(void * buffer, void * string) {
    static_cast<SkReadBuffer *>(buffer)->readString(static_cast<SkString *>(string));
}

void SkReadBuffer_readColor4f(void * buffer, void * color) {
    static_cast<SkReadBuffer *>(buffer)->readColor4f(static_cast<SkColor4f *>(color));
}

void SkReadBuffer_readPoint(void * buffer, void * point) {
    static_cast<SkReadBuffer *>(buffer)->readPoint(static_cast<SkPoint *>(point));
}

sk_point_t SkReadBuffer_readPoint_2(void * buffer) {
    return static_sk_point_make(static_cast<SkReadBuffer *>(buffer)->readPoint());
}

void SkReadBuffer_readPoint3(void * buffer, void * point) {
    return static_cast<SkReadBuffer *>(buffer)->readPoint3(static_cast<SkPoint3 *>(point));
}

void SkReadBuffer_read(void * buffer, void * m44) {
    return static_cast<SkReadBuffer *>(buffer)->read(static_cast<SkM44 *>(m44));
}

void SkReadBuffer_readMatrix(void * buffer, void * matrix) {
    return static_cast<SkReadBuffer *>(buffer)->readMatrix(static_cast<SkMatrix *>(matrix));
}

void SkReadBuffer_readIRect(void * buffer, void * rect) {
    return static_cast<SkReadBuffer *>(buffer)->readIRect(static_cast<SkIRect *>(rect));
}

void SkReadBuffer_readRect(void * buffer, void * rect) {
    return static_cast<SkReadBuffer *>(buffer)->readRect(static_cast<SkRect *>(rect));
}

sk_rect_t SkReadBuffer_readRect_2(void * buffer) {
    return static_sk_rect_make(static_cast<SkReadBuffer *>(buffer)->readRect());
}

void SkReadBuffer_readRRect(void * buffer, void * rrect) {
    return static_cast<SkReadBuffer *>(buffer)->readRRect(static_cast<SkRRect *>(rrect));
}

void SkReadBuffer_readRegion(void * buffer, void * region) {
    return static_cast<SkReadBuffer *>(buffer)->readRegion(static_cast<SkRegion *>(region));
}

void SkReadBuffer_readPath(void * buffer, void * path) {
      return static_cast<SkReadBuffer *>(buffer)->readPath(static_cast<SkPath *>(path));
}

sk_paint_t SkReadBuffer_readPaint(void * buffer) {
    return static_sk_paint_make(static_cast<SkReadBuffer *>(buffer)->readPaint());
}

void * SkReadBuffer_readRawFlattenable(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->readRawFlattenable();
}

void * SkReadBuffer_readFlattenable(void * buffer, int type) {
    return static_cast<SkReadBuffer *>(buffer)->readFlattenable(static_cast<SkFlattenable::Type>(type));
}

// template <typename T> sk_sp<T> readFlattenable()

sk_color_filter_t SkReadBuffer_readColorFilter(void * buffer) {
    return static_sk_color_filter_make(static_cast<SkReadBuffer *>(buffer)->readColorFilter());
}

sk_image_filter_t SkReadBuffer_readImageFilter(void * buffer) {
    return static_sk_image_filter_make(static_cast<SkReadBuffer *>(buffer)->readImageFilter());
}

sk_blender_t SkReadBuffer_readBlender(void * buffer) {
    return static_sk_blender_make(static_cast<SkReadBuffer *>(buffer)->readBlender());
}

sk_mask_filter_t SkReadBuffer_readMaskFilter(void * buffer) {
    return static_sk_mask_filter_make(static_cast<SkReadBuffer *>(buffer)->readMaskFilter());
}

sk_path_effect_t SkReadBuffer_readPathEffect(void * buffer) {
    return static_sk_path_effect_make(static_cast<SkReadBuffer *>(buffer)->readPathEffect());
}

sk_shader_t SkReadBuffer_readShader(void * buffer) {
    return static_sk_shader_make(static_cast<SkReadBuffer *>(buffer)->readShader());
}

bool SkReadBuffer_readPad32(void * readBuffer, void * buffer, size_t bytes) {
    return static_cast<SkReadBuffer *>(readBuffer)->readPad32(buffer, bytes);
}

bool SkReadBuffer_readByteArray(void * buffer, void * value, size_t size) {
    return static_cast<SkReadBuffer *>(buffer)->readByteArray(value, size);
}

bool SkReadBuffer_readColorArray(void * buffer, void * colors, size_t size) {
    return static_cast<SkReadBuffer *>(buffer)->readColorArray(static_cast<SkColor *>(colors), size);
}

bool SkReadBuffer_readColor4fArray(void * buffer, void * colors, size_t size) {
    return static_cast<SkReadBuffer *>(buffer)->readColor4fArray(static_cast<SkColor4f *>(colors), size);
}

bool SkReadBuffer_readIntArray(void * buffer, void * values, size_t size) {
    return static_cast<SkReadBuffer *>(buffer)->readIntArray(static_cast<int32_t *>(values), size);
}

bool SkReadBuffer_readPointArray(void * buffer, void * points, size_t size) {
    return static_cast<SkReadBuffer *>(buffer)->readPointArray(static_cast<SkPoint *>(points), size);
}

bool SkReadBuffer_readScalarArray(void * buffer, void * values, size_t size) {
    return static_cast<SkReadBuffer *>(buffer)->readScalarArray(static_cast<SkScalar *>(values), size);
}

const void* SkReadBuffer_skipByteArray(void * buffer, void * size) {
    return static_cast<SkReadBuffer *>(buffer)->skipByteArray(static_cast<size_t *>(size));
}

sk_data_t SkReadBuffer_readByteArrayAsData(void * buffer) {
    return static_sk_data_make(static_cast<SkReadBuffer *>(buffer)->readByteArrayAsData());
}

uint32_t SkReadBuffer_getArrayCount(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->getArrayCount();
}

sk_image_t SkReadBuffer_readImage(void * buffer) {
    return static_sk_image_make(static_cast<SkReadBuffer *>(buffer)->readImage());
}

sk_typeface_t SkReadBuffer_readTypeface(void * buffer) {
    return static_sk_typeface_make(static_cast<SkReadBuffer *>(buffer)->readTypeface());
}

void SkReadBuffer_setTypefaceArray(void * buffer, void * array, int count) {
    return static_cast<SkReadBuffer *>(buffer)->setTypefaceArray(static_cast<sk_sp<SkTypeface> *>(array), count);
}

void SkReadBuffer_setFactoryPlayback(void * buffer, void * array, int count) {
    return static_cast<SkReadBuffer *>(buffer)->setFactoryPlayback(static_cast<SkFlattenable::Factory *>(array), count);
}

void SkReadBuffer_setDeserialProcs(void * buffer, const void * procs) {
    return static_cast<SkReadBuffer *>(buffer)->setDeserialProcs(* static_cast<const SkDeserialProcs *>(procs));
}

const void * SkReadBuffer_getDeserialProcs(void * buffer) {
    return &static_cast<SkReadBuffer *>(buffer)->getDeserialProcs();
}

bool SkReadBuffer_allowSkSL(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->allowSkSL();
}

void SkReadBuffer_setAllowSkSL(void * buffer, bool allow) {
    return static_cast<SkReadBuffer *>(buffer)->setAllowSkSL(allow);
}

bool SkReadBuffer_validate(void * buffer, bool isValid) {
    return static_cast<SkReadBuffer *>(buffer)->validate(isValid);
}


// template <typename T> bool validateCanReadN(size_t n)

bool SkReadBuffer_isValid(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->isValid();
}

bool SkReadBuffer_validateIndex(void * buffer, int index, int count) {
    return static_cast<SkReadBuffer *>(buffer)->validateIndex(index, count);
}

int32_t SkReadBuffer_checkInt(void * buffer, int min, int max) {
    return static_cast<SkReadBuffer *>(buffer)->checkInt(min, max);
}

// template <typename T> T checkRange(T min, T max)

int SkReadBuffer_checkFilterQuality(void * buffer) {
    return static_cast<SkReadBuffer *>(buffer)->checkFilterQuality();
}

sk_sampling_options_t SkReadBuffer_readSampling(void * buffer) {
    return static_sk_sampling_options_make(static_cast<SkReadBuffer *>(buffer)->readSampling());
}

}