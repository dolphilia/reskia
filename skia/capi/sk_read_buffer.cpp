//
// Created by dolphilia on 25/02/17.
//

#include "sk_read_buffer.h"

#include "src/core/SkReadBuffer.h"
#include "include/core/SkData.h"
#include "include/core/SkImage.h"
#include "include/core/SkTypeface.h"

#include <utility>

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

namespace {

SkReadBuffer *as_read_buffer(reskia_read_buffer_t *buffer) {
    return reinterpret_cast<SkReadBuffer *>(buffer);
}

bool is_valid_flattenable_type(reskia_read_buffer_flattenable_type_t type) {
    return type >= SkFlattenable::kSkColorFilter_Type && type <= SkFlattenable::kSkShader_Type;
}

template <typename T>
bool has_output(T *ptr, size_t count) {
    return count == 0 || ptr != nullptr;
}

sk_data_t make_data_handle(sk_sp<SkData> data) {
    if (!data) {
        return 0;
    }
    return static_sk_data_make(std::move(data));
}

sk_image_t make_image_handle(sk_sp<SkImage> image) {
    if (!image) {
        return 0;
    }
    return static_sk_image_make(std::move(image));
}

sk_typeface_t make_typeface_handle(sk_sp<SkTypeface> typeface) {
    if (!typeface) {
        return 0;
    }
    return static_sk_typeface_make(std::move(typeface));
}

sk_color_filter_t make_color_filter_handle(sk_sp<SkColorFilter> colorFilter) {
    if (!colorFilter) {
        return 0;
    }
    return static_sk_color_filter_make(std::move(colorFilter));
}

sk_image_filter_t make_image_filter_handle(sk_sp<SkImageFilter> imageFilter) {
    if (!imageFilter) {
        return 0;
    }
    return static_sk_image_filter_make(std::move(imageFilter));
}

sk_blender_t make_blender_handle(sk_sp<SkBlender> blender) {
    if (!blender) {
        return 0;
    }
    return static_sk_blender_make(std::move(blender));
}

sk_mask_filter_t make_mask_filter_handle(sk_sp<SkMaskFilter> maskFilter) {
    if (!maskFilter) {
        return 0;
    }
    return static_sk_mask_filter_make(std::move(maskFilter));
}

sk_path_effect_t make_path_effect_handle(sk_sp<SkPathEffect> pathEffect) {
    if (!pathEffect) {
        return 0;
    }
    return static_sk_path_effect_make(std::move(pathEffect));
}

sk_shader_t make_shader_handle(sk_sp<SkShader> shader) {
    if (!shader) {
        return 0;
    }
    return static_sk_shader_make(std::move(shader));
}

} // namespace

extern "C" {

reskia_read_buffer_t *SkReadBuffer_new() {
    return reinterpret_cast<reskia_read_buffer_t *>(new SkReadBuffer());
}

reskia_read_buffer_t *SkReadBuffer_newWithDataAndSize(const void* data, size_t size) {
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

const void* SkReadBuffer_skipCount(reskia_read_buffer_t *buffer, size_t count, size_t size) {
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

sk_point_t SkReadBuffer_readPointValue(reskia_read_buffer_t *buffer) {
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

sk_rect_t SkReadBuffer_readRectValue(reskia_read_buffer_t *buffer) {
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
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<reskia_flattenable_t *>(
            readBuffer->readRawFlattenable());
}

reskia_flattenable_t *SkReadBuffer_readFlattenable(reskia_read_buffer_t *buffer, reskia_read_buffer_flattenable_type_t type) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || !is_valid_flattenable_type(type)) {
        return nullptr;
    }
    return reinterpret_cast<reskia_flattenable_t *>(
            readBuffer->readFlattenable(static_cast<SkFlattenable::Type>(type)));
}

// template <typename T> sk_sp<T> readFlattenable()

sk_color_filter_t SkReadBuffer_readColorFilter(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_color_filter_handle(readBuffer->readColorFilter());
}

sk_image_filter_t SkReadBuffer_readImageFilter(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_image_filter_handle(readBuffer->readImageFilter());
}

sk_blender_t SkReadBuffer_readBlender(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_blender_handle(readBuffer->readBlender());
}

sk_mask_filter_t SkReadBuffer_readMaskFilter(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_mask_filter_handle(readBuffer->readMaskFilter());
}

sk_path_effect_t SkReadBuffer_readPathEffect(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_path_effect_handle(readBuffer->readPathEffect());
}

sk_shader_t SkReadBuffer_readShader(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_shader_handle(readBuffer->readShader());
}

bool SkReadBuffer_readPad32(reskia_read_buffer_t *readBuffer, void *buffer, size_t bytes) {
    SkReadBuffer *reader = as_read_buffer(readBuffer);
    if (reader == nullptr || !has_output(buffer, bytes)) {
        return false;
    }
    return reader->readPad32(buffer, bytes);
}

bool SkReadBuffer_readByteArray(reskia_read_buffer_t *buffer, void * value, size_t size) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || !has_output(value, size)) {
        return false;
    }
    return readBuffer->readByteArray(value, size);
}

bool SkReadBuffer_readColorArray(reskia_read_buffer_t *buffer, uint32_t *colors, size_t size) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || !has_output(colors, size)) {
        return false;
    }
    return readBuffer->readColorArray(reinterpret_cast<SkColor *>(colors), size);
}

bool SkReadBuffer_readColor4fArray(reskia_read_buffer_t *buffer, reskia_color_4f_t *colors, size_t size) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || !has_output(colors, size)) {
        return false;
    }
    return readBuffer->readColor4fArray(reinterpret_cast<SkColor4f *>(colors), size);
}

bool SkReadBuffer_readIntArray(reskia_read_buffer_t *buffer, int32_t *values, size_t size) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || !has_output(values, size)) {
        return false;
    }
    return readBuffer->readIntArray(reinterpret_cast<int32_t *>(values), size);
}

bool SkReadBuffer_readPointArray(reskia_read_buffer_t *buffer, reskia_point_t *points, size_t size) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || !has_output(points, size)) {
        return false;
    }
    return readBuffer->readPointArray(reinterpret_cast<SkPoint *>(points), size);
}

bool SkReadBuffer_readScalarArray(reskia_read_buffer_t *buffer, float *values, size_t size) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || !has_output(values, size)) {
        return false;
    }
    return readBuffer->readScalarArray(reinterpret_cast<SkScalar *>(values), size);
}

const void* SkReadBuffer_skipByteArray(reskia_read_buffer_t *buffer, size_t *size) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || size == nullptr) {
        return nullptr;
    }
    return readBuffer->skipByteArray(size);
}

sk_data_t SkReadBuffer_readByteArrayAsData(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_data_handle(readBuffer->readByteArrayAsData());
}

uint32_t SkReadBuffer_getArrayCount(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return readBuffer->getArrayCount();
}

sk_image_t SkReadBuffer_readImage(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_image_handle(readBuffer->readImage());
}

sk_typeface_t SkReadBuffer_readTypeface(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return make_typeface_handle(readBuffer->readTypeface());
}

void SkReadBuffer_setTypefaceArray(reskia_read_buffer_t *buffer, void * array, int count) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || count < 0 || (count > 0 && array == nullptr)) {
        return;
    }
    readBuffer->setTypefaceArray(static_cast<sk_sp<SkTypeface> *>(array), count);
}

void SkReadBuffer_setFactoryPlayback(reskia_read_buffer_t *buffer, void * array, int count) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || count < 0 || (count > 0 && array == nullptr)) {
        return;
    }
    readBuffer->setFactoryPlayback(reinterpret_cast<SkFlattenable::Factory *>(array), count);
}

void SkReadBuffer_setDeserialProcs(reskia_read_buffer_t *buffer, const reskia_deserial_procs_t *procs) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || procs == nullptr) {
        return;
    }
    readBuffer->setDeserialProcs(*reinterpret_cast<const SkDeserialProcs *>(procs));
}

const reskia_deserial_procs_t *SkReadBuffer_getDeserialProcs(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return nullptr;
    }
    return reinterpret_cast<const reskia_deserial_procs_t *>(&readBuffer->getDeserialProcs());
}

bool SkReadBuffer_allowSkSL(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return false;
    }
    return readBuffer->allowSkSL();
}

void SkReadBuffer_setAllowSkSL(reskia_read_buffer_t *buffer, bool allow) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return;
    }
    readBuffer->setAllowSkSL(allow);
}

bool SkReadBuffer_validate(reskia_read_buffer_t *buffer, bool isValid) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return false;
    }
    return readBuffer->validate(isValid);
}


// template <typename T> bool validateCanReadN(size_t n)

bool SkReadBuffer_isValid(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return false;
    }
    return readBuffer->isValid();
}

bool SkReadBuffer_validateIndex(reskia_read_buffer_t *buffer, int index, int count) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || count < 0) {
        return false;
    }
    return readBuffer->validateIndex(index, count);
}

int32_t SkReadBuffer_checkInt(reskia_read_buffer_t *buffer, int min, int max) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr || min > max) {
        return 0;
    }
    return readBuffer->checkInt(min, max);
}

// template <typename T> T checkRange(T min, T max)

reskia_read_buffer_legacy_fq_t SkReadBuffer_checkFilterQuality(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return -1;
    }
    return static_cast<reskia_read_buffer_legacy_fq_t>(readBuffer->checkFilterQuality());
}

sk_sampling_options_t SkReadBuffer_readSampling(reskia_read_buffer_t *buffer) {
    SkReadBuffer *readBuffer = as_read_buffer(buffer);
    if (readBuffer == nullptr) {
        return 0;
    }
    return static_sk_sampling_options_make(readBuffer->readSampling());
}

}
