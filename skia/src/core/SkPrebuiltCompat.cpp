/*
 * Compatibility symbols for prebuilt static modules compiled against older
 * Skia headers. These wrappers are not part of the public C API surface.
 */

#include "include/core/SkMatrix.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/pathops/SkPathOps.h"

extern "C" SkPath SkPathBuilder_detach_noarg_compat(SkPathBuilder* self)
        __asm("__ZN13SkPathBuilder6detachEv");

extern "C" SkPath SkPathBuilder_detach_noarg_compat(SkPathBuilder* self) {
    return self != nullptr ? self->detach(nullptr) : SkPath();
}

extern "C" void SkPath_transform_perspective_clip_compat(
        const SkPath* self,
        const SkMatrix& matrix,
        SkPath* dst,
        SkApplyPerspectiveClip)
        __asm("__ZNK6SkPath9transformERK8SkMatrixPS_22SkApplyPerspectiveClip");

extern "C" void SkPath_transform_perspective_clip_compat(
        const SkPath* self,
        const SkMatrix& matrix,
        SkPath* dst,
        SkApplyPerspectiveClip) {
    if (self == nullptr) {
        return;
    }
    self->transform(matrix, dst);
}

extern "C" bool SkPathOps_Op_outparam_compat(
        const SkPath& one,
        const SkPath& two,
        SkPathOp op,
        SkPath* result)
        __asm("__Z2OpRK6SkPathS1_8SkPathOpPS_");

extern "C" bool SkPathOps_Op_outparam_compat(
        const SkPath& one,
        const SkPath& two,
        SkPathOp op,
        SkPath* result) {
    if (result == nullptr) {
        return false;
    }
    if (auto res = Op(one, two, op)) {
        *result = *res;
        return true;
    }
    return false;
}

extern "C" bool SkPathOps_Simplify_outparam_compat(
        const SkPath& path,
        SkPath* result)
        __asm("__Z8SimplifyRK6SkPathPS_");

extern "C" bool SkPathOps_Simplify_outparam_compat(
        const SkPath& path,
        SkPath* result) {
    if (result == nullptr) {
        return false;
    }
    if (auto res = Simplify(path)) {
        *result = *res;
        return true;
    }
    return false;
}

extern "C" bool SkPathOps_AsWinding_outparam_compat(
        const SkPath& path,
        SkPath* result)
        __asm("__Z9AsWindingRK6SkPathPS_");

extern "C" bool SkPathOps_AsWinding_outparam_compat(
        const SkPath& path,
        SkPath* result) {
    if (result == nullptr) {
        return false;
    }
    if (auto res = AsWinding(path)) {
        *result = *res;
        return true;
    }
    return false;
}
