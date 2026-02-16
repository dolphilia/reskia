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

void SkPathEffect_delete(reskia_path_effect_t *pathEffect); // owned: caller が保持する参照を release する
int SkPathEffect_asADash(reskia_path_effect_t *path_effect, reskia_path_effect_dash_info_t *info);
bool SkPathEffect_filterPath(reskia_path_effect_t *path_effect, reskia_path_t *dst, const reskia_path_t *src, reskia_stroke_rec_t *rec, const reskia_rect_t *cullR);
bool SkPathEffect_filterPath_2(reskia_path_effect_t *path_effect, reskia_path_t *dst, const reskia_path_t *src, reskia_stroke_rec_t *rec, const reskia_rect_t *cullR, const reskia_matrix_t *ctm);
bool SkPathEffect_needsCTM(reskia_path_effect_t *path_effect);
int SkPathEffect_getFactory(reskia_path_effect_t *path_effect);
const char * SkPathEffect_getTypeName(reskia_path_effect_t *path_effect);
void SkPathEffect_flatten(reskia_path_effect_t *path_effect, reskia_write_buffer_t *buffer);
int SkPathEffect_getFlattenableType(reskia_path_effect_t *path_effect);
int SkPathEffect_serialize(reskia_path_effect_t *path_effect, const reskia_serial_procs_t *procs);
size_t SkPathEffect_serialize_2(reskia_path_effect_t *path_effect, uint8_t *memory, size_t memory_size, const reskia_serial_procs_t *procs);
bool SkPathEffect_unique(reskia_path_effect_t *path_effect);
void SkPathEffect_ref(reskia_path_effect_t *path_effect); // retained: 参照カウントを増やす
void SkPathEffect_unref(reskia_path_effect_t *path_effect); // owned: 参照カウントを減らす

// static

int SkPathEffect_MakeSum(int first, int second);
int SkPathEffect_MakeCompose(int outer, int inner);
int SkPathEffect_GetFlattenableType();
int SkPathEffect_Deserialize(const uint8_t *data, size_t size, const reskia_deserial_procs_t *procs);
int SkPathEffect_NameToFactory(const char name[]);
const char * SkPathEffect_FactoryToName(int factory);
void SkPathEffect_Register(const char name[], int factory);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PATH_EFFECT_H
