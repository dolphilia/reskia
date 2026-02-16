//
// Created by dolphilia on 2024/01/09.
//

#include "sk_op_builder.h"

#include "include/pathops/SkPathOps.h"

extern "C" {

void SkOpBuilder_delete(reskia_op_builder_t *op_builder) {
    delete reinterpret_cast<SkOpBuilder *>(op_builder);
}

void SkOpBuilder_add(reskia_op_builder_t *op_builder, const reskia_path_t *path, reskia_op_builder_path_op_t path_operator) {
    reinterpret_cast<SkOpBuilder *>(op_builder)->add(* reinterpret_cast<const SkPath *>(path), static_cast<SkPathOp>(path_operator));
}

bool SkOpBuilder_resolve(reskia_op_builder_t *op_builder, reskia_path_t *result) {
    return reinterpret_cast<SkOpBuilder *>(op_builder)->resolve(reinterpret_cast<SkPath *>(result));
}

}
