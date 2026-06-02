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

void SkOpBuilder_delete(reskia_op_builder_t *op_builder); // No-op for NULL input.
/**
 * op_builder and path must be non-NULL, and path_operator must be in the SkPathOp range.
 * No-op for invalid input.
 */
void SkOpBuilder_add(reskia_op_builder_t *op_builder, const reskia_path_t *path, reskia_op_builder_path_op_t path_operator);
bool SkOpBuilder_resolve(reskia_op_builder_t *op_builder, reskia_path_t *result); // op_builder and result must be non-NULL. Returns false for invalid input.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_OP_BUILDER_H
