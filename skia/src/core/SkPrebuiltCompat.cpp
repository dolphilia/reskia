/*
 * Compatibility symbols for prebuilt static modules compiled against older
 * Skia headers. These wrappers are not part of the public C API surface.
 */

#include "include/core/SkMatrix.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"

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
