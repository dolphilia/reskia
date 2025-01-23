//
// Created by dolphilia on 2024/01/09.
//

#include "sk_op_builder.h"

#include "include/pathops/SkPathOps.h"

extern "C" {

void SkOpBuilder_delete(void *opBuilder) {
    delete static_cast<SkOpBuilder *>(opBuilder);
}

void SkOpBuilder_add(void *op_builder, const void *path, int path_operator) {
    static_cast<SkOpBuilder *>(op_builder)->add(* static_cast<const SkPath *>(path), static_cast<SkPathOp>(path_operator));
}

bool SkOpBuilder_resolve(void *op_builder, void *result) {
    return static_cast<SkOpBuilder *>(op_builder)->resolve(static_cast<SkPath *>(result));
}

}