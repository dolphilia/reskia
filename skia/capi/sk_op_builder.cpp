//
// Created by dolphilia on 2024/01/09.
//

#include "sk_op_builder.h"

#include "include/pathops/SkPathOps.h"

namespace {

SkOpBuilder *as_op_builder(reskia_op_builder_t *opBuilder) {
    return reinterpret_cast<SkOpBuilder *>(opBuilder);
}

bool is_valid_path_op(reskia_op_builder_path_op_t pathOperator) {
    return pathOperator >= kDifference_SkPathOp && pathOperator <= kReverseDifference_SkPathOp;
}

}  // namespace

extern "C" {

void SkOpBuilder_delete(reskia_op_builder_t *op_builder) {
    delete as_op_builder(op_builder);
}

void SkOpBuilder_add(reskia_op_builder_t *op_builder, const reskia_path_t *path, reskia_op_builder_path_op_t path_operator) {
    if (op_builder == nullptr || path == nullptr || !is_valid_path_op(path_operator)) {
        return;
    }
    as_op_builder(op_builder)->add(* reinterpret_cast<const SkPath *>(path), static_cast<SkPathOp>(path_operator));
}

bool SkOpBuilder_resolve(reskia_op_builder_t *op_builder, reskia_path_t *result) {
    if (op_builder == nullptr || result == nullptr) {
        return false;
    }
    return as_op_builder(op_builder)->resolve(reinterpret_cast<SkPath *>(result));
}

}
