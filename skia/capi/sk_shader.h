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

void SkShader_release(reskia_shader_t *shader); // owned: NULL shader is no-op.
bool SkShader_isOpaque(reskia_shader_t *shader); // NULL shader returns false.
reskia_image_t *SkShader_isAImage(reskia_shader_t *shader, reskia_matrix_t *localMatrix, int *xy); // localMatrix/xy may be NULL; NULL shader returns NULL.
bool SkShader_isAImageWithoutLocalMatrixAndTileModes(reskia_shader_t *shader); // NULL shader returns false.
sk_shader_t SkShader_makeWithLocalMatrix(reskia_shader_t *shader, const reskia_matrix_t *matrix); // shader/matrix are required; NULL result returns 0.
sk_shader_t SkShader_makeWithColorFilter(reskia_shader_t *shader, sk_color_filter_t color_filter); // color_filter may be 0; NULL shader/result returns 0.
sk_shader_t SkShader_makeWithWorkingColorSpace(reskia_shader_t *shader, sk_color_space_t color_space); // color_space may be 0; NULL shader/result returns 0.
sk_flattenable_factory_t SkShader_getFactory(reskia_shader_t *shader); // NULL shader or missing factory returns 0.
const char *SkShader_getTypeName(reskia_shader_t *shader); // NULL shader returns NULL.
void SkShader_flatten(reskia_shader_t *shader, reskia_write_buffer_t *buffer); // shader/buffer are required; NULL input is no-op.
reskia_shader_type_t SkShader_getFlattenableType(reskia_shader_t *shader); // NULL shader returns 0.
sk_data_t SkShader_serialize(reskia_shader_t *shader, const reskia_serial_procs_t *procs); // procs may be NULL; NULL shader/result returns 0.
size_t SkShader_serializeToMemory(reskia_shader_t *shader, void *memory, size_t memory_size, const reskia_serial_procs_t *procs); // procs may be NULL; NULL shader or NULL memory with nonzero size returns 0.
bool SkShader_unique(reskia_shader_t *shader); // NULL shader returns false.
void SkShader_ref(reskia_shader_t *shader); // retained: NULL shader is no-op.
void SkShader_unref(reskia_shader_t *shader); // owned: NULL shader is no-op.

// static

sk_flattenable_factory_t SkShader_NameToFactory(const char name[]); // NULL name or missing factory returns 0.
const char *SkShader_FactoryToName(sk_flattenable_factory_t factory); // invalid factory returns NULL.
void SkShader_Register(const char name[], sk_flattenable_factory_t factory); // name/factory are required; invalid input is no-op.
sk_flattenable_t SkShader_Deserialize(reskia_shader_type_t type, const void *data, size_t length, const reskia_deserial_procs_t *procs); // procs may be NULL; NULL data or zero length returns 0.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_SHADER_H
