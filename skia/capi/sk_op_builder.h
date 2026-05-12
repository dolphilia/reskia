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

void SkOpBuilder_delete(reskia_op_builder_t *op_builder); // NULL 入力では no-op
/**
 * op_builder/path は非 NULL、path_operator は SkPathOp 範囲内。invalid 入力では no-op
 */
void SkOpBuilder_add(reskia_op_builder_t *op_builder, const reskia_path_t *path, reskia_op_builder_path_op_t path_operator);
bool SkOpBuilder_resolve(reskia_op_builder_t *op_builder, reskia_path_t *result); // op_builder/result は非 NULL。invalid 入力では false

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_OP_BUILDER_H
