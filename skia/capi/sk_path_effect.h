//
// Created by dolphilia on 2024/01/10.
//

#ifndef RAIA_SKIA_SK_PATH_EFFECT_H
#define RAIA_SKIA_SK_PATH_EFFECT_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_deserial_procs_t reskia_deserial_procs_t;
typedef struct reskia_matrix_t reskia_matrix_t;
typedef struct reskia_path_effect_dash_info_t reskia_path_effect_dash_info_t;
typedef struct reskia_path_effect_t reskia_path_effect_t;
typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_rect_t reskia_rect_t;
typedef struct reskia_serial_procs_t reskia_serial_procs_t;
typedef struct reskia_stroke_rec_t reskia_stroke_rec_t;
typedef struct reskia_write_buffer_t reskia_write_buffer_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkPathEffect_release(reskia_path_effect_t *pathEffect); // owned: releases the caller-held reference. No-op for NULL input.
/**
 * dst, src, and rec must be non-NULL. cullR may be NULL. Returns false for NULL input.
 */
bool SkPathEffect_filterPath(reskia_path_effect_t *path_effect, reskia_path_t *dst, const reskia_path_t *src, reskia_stroke_rec_t *rec, const reskia_rect_t *cullR);
/**
 * dst, src, rec, and ctm must be non-NULL. cullR may be NULL. Returns false for NULL input.
 */
bool SkPathEffect_filterPathWithCTM(reskia_path_effect_t *path_effect, reskia_path_t *dst, const reskia_path_t *src, reskia_stroke_rec_t *rec, const reskia_rect_t *cullR, const reskia_matrix_t *ctm);
bool SkPathEffect_needsCTM(reskia_path_effect_t *path_effect);
int SkPathEffect_getFactory(reskia_path_effect_t *path_effect);
const char * SkPathEffect_getTypeName(reskia_path_effect_t *path_effect);
void SkPathEffect_flatten(reskia_path_effect_t *path_effect, reskia_write_buffer_t *buffer); // buffer must be non-NULL. No-op for NULL input.
int SkPathEffect_getFlattenableType(reskia_path_effect_t *path_effect);
/**
 * retained data handle. procs may be NULL. Returns 0 when path_effect or result is NULL.
 */
int SkPathEffect_serialize(reskia_path_effect_t *path_effect, const reskia_serial_procs_t *procs);
/**
 * raw output buffer: memory must contain at least memory_size bytes.
 * Returns 0 when memory is NULL and memory_size is nonzero.
 */
size_t SkPathEffect_serializeToMemory(reskia_path_effect_t *path_effect, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *procs);
bool SkPathEffect_unique(reskia_path_effect_t *path_effect);
void SkPathEffect_ref(reskia_path_effect_t *path_effect); // retained: increments the reference count.
void SkPathEffect_unref(reskia_path_effect_t *path_effect); // owned: decrements the reference count.

// static

int SkPathEffect_MakeSum(int first, int second); // handle 0/invalid is treated as null effect. Returns 0 on failure.
int SkPathEffect_MakeCompose(int outer, int inner); // handle 0/invalid is treated as null effect. Returns 0 on failure.
int SkPathEffect_GetFlattenableType();
/**
 * raw input buffer: data must contain at least size bytes and be non-NULL.
 * Returns 0 when size is 0. procs may be NULL.
 */
int SkPathEffect_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs);
int SkPathEffect_NameToFactory(const char name[]); // name must be non-NULL. Returns 0 when not found.
const char * SkPathEffect_FactoryToName(int factory); // Returns NULL when factory is 0/invalid.
void SkPathEffect_Register(const char name[], int factory); // name and factory must be non-NULL/non-zero. No-op for invalid input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_EFFECT_H
