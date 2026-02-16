//
// Created by dolphilia on 2024/01/09.
//

#ifndef RAIA_SKIA_SK_OP_BUILDER_H
#define RAIA_SKIA_SK_OP_BUILDER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reskia_op_builder_t reskia_op_builder_t;
typedef struct reskia_path_t reskia_path_t;
typedef int32_t reskia_op_builder_path_op_t;

void SkOpBuilder_delete(reskia_op_builder_t *op_builder); // // (SkOpBuilder *op_builder)
void SkOpBuilder_add(reskia_op_builder_t *op_builder, const reskia_path_t *path, reskia_op_builder_path_op_t path_operator); // // (SkOpBuilder *op_builder, const SkPath *path, SkPathOp path_operator)
bool SkOpBuilder_resolve(reskia_op_builder_t *op_builder, reskia_path_t *result); // // (SkOpBuilder *op_builder, SkPath *result) -> bool

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_OP_BUILDER_H
