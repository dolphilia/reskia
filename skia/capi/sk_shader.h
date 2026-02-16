//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_SHADER_H
#define RAIA_SKIA_SK_SHADER_H

#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_color_filter.h"
#include "../handles/static_sk_color_space.h"
#include "../handles/static_sk_data.h"
#include "../handles/static_sk_flattenable.h"
#include "../handles/static_sk_flattenable_factory.h"
#include "../handles/static_sk_shader.h"

typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_image_t reskia_image_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_shader_t reskia_shader_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;
typedef int32_t reskia_shader_type_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkShader_release(reskia_shader_t *shader); // owned: caller が保持する参照を release する (SkShader *shader)
bool SkShader_isOpaque(reskia_shader_t *shader); // (SkShader *shader) -> bool
reskia_image_t *SkShader_isAImage(reskia_shader_t *shader, reskia_matrix_t *localMatrix, int *xy); // borrowed: 解放不要の借用ポインタ (SkShader *shader, SkMatrix *localMatrix, SkTileMode xy[2]) -> SkImage *
bool SkShader_isAImageWithoutLocalMatrixAndTileModes(reskia_shader_t *shader); // (SkShader *shader) -> bool
sk_shader_t SkShader_makeWithLocalMatrix(reskia_shader_t *shader, const reskia_matrix_t *matrix); // (SkShader *shader, const SkMatrix *matrix) -> sk_shader_t
sk_shader_t SkShader_makeWithColorFilter(reskia_shader_t *shader, sk_color_filter_t color_filter); // (SkShader *shader, sk_color_filter_t color_filter) -> sk_shader_t
sk_shader_t SkShader_makeWithWorkingColorSpace(reskia_shader_t *shader, sk_color_space_t color_space); // (SkShader *shader, sk_color_space_t color_space) -> sk_shader_t
sk_flattenable_factory_t SkShader_getFactory(reskia_shader_t *shader); // (SkShader *shader) -> sk_flattenable_factory_t
const char *SkShader_getTypeName(reskia_shader_t *shader); // (SkShader *shader) -> const char *
void SkShader_flatten(reskia_shader_t *shader, reskia_write_buffer_t *buffer); // (SkShader *shader, SkWriteBuffer *buffer)
reskia_shader_type_t SkShader_getFlattenableType(reskia_shader_t *shader); // (SkShader *shader) -> SkShader::Type
sk_data_t SkShader_serialize(reskia_shader_t *shader, const reskia_serial_procs_t *procs); // (SkShader *shader, const SkSerialProcs *procs) -> sk_data_t
size_t SkShader_serializeToMemory(reskia_shader_t *shader, void *memory, size_t memory_size, const reskia_serial_procs_t *procs); // (SkShader *shader, void *memory, size_t memory_size, const SkSerialProcs *procs) -> size_t
bool SkShader_unique(reskia_shader_t *shader); // (SkShader *shader) -> bool
void SkShader_ref(reskia_shader_t *shader); // retained: 参照カウントを増やす (SkShader *shader)
void SkShader_unref(reskia_shader_t *shader); // owned: 参照カウントを減らす (SkShader *shader)

// static

sk_flattenable_factory_t SkShader_NameToFactory(const char name[]); // (const char name[]) -> sk_flattenable_factory_t
const char *SkShader_FactoryToName(sk_flattenable_factory_t factory); // (sk_flattenable_factory_t factory) -> const char *
void SkShader_Register(const char name[], sk_flattenable_factory_t factory); // (const char name[], sk_flattenable_factory_t factory)
sk_flattenable_t SkShader_Deserialize(reskia_shader_type_t type, const void *data, size_t length, const reskia_deserial_procs_t *procs); // (SkShader::Type type, const void *data, size_t length, const SkDeserialProcs *procs) -> sk_flattenable_t

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SHADER_H
