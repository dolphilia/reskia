/*
 * Compatibility symbols for prebuilt static modules compiled against older
 * Skia headers. These wrappers are not part of the public C API surface.
 */

#include "include/core/SkMatrix.h"
#include "include/core/SkPath.h"
#include "include/core/SkPathBuilder.h"
#include "include/core/SkPoint.h"
#include "include/core/SkShader.h"
#include "include/effects/SkGradient.h"
#include "include/pathops/SkPathOps.h"
#include "modules/skcms/src/skcms_public.h"

#include <utility>

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
    if (dst != nullptr) {
        *dst = self->makeTransform(matrix);
    }
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

extern "C" __attribute__((weak)) bool skcms_TransferFunction_isPQ(
        const skcms_TransferFunction* tf) {
    return tf != nullptr &&
           tf->g == -static_cast<float>(skcms_TFType_PQ) &&
           tf->b == 0.0f &&
           tf->c == 0.0f &&
           tf->d == 0.0f &&
           tf->e == 0.0f &&
           tf->f == 0.0f;
}

extern "C" __attribute__((weak)) bool skcms_TransferFunction_isHLG(
        const skcms_TransferFunction* tf) {
    return tf != nullptr &&
           tf->g == -static_cast<float>(skcms_TFType_HLG) &&
           tf->d == 0.0f &&
           tf->e == 0.0f &&
           tf->f == 0.0f;
}

extern "C" sk_sp<SkShader> SkGradientShader_MakeLinear_old_interp_compat(
        const SkPoint pts[2],
        const SkColor4f colors[],
        sk_sp<SkColorSpace> colorSpace,
        const SkScalar pos[],
        int colorCount,
        SkTileMode mode,
        const SkGradient::Interpolation& interp,
        const SkMatrix* localMatrix)
        __asm("__ZN16SkGradientShader10MakeLinearEPK7SkPointPK8SkRGBA4fIL11SkAlphaType3EE5sk_spI12SkColorSpaceEPKfi10SkTileModeRKNS_13InterpolationEPK8SkMatrix");

extern "C" sk_sp<SkShader> SkGradientShader_MakeLinear_old_interp_compat(
        const SkPoint pts[2],
        const SkColor4f colors[],
        sk_sp<SkColorSpace> colorSpace,
        const SkScalar pos[],
        int colorCount,
        SkTileMode mode,
        const SkGradient::Interpolation& interp,
        const SkMatrix* localMatrix) {
    SkGradient gradient(
            SkGradient::Colors({colors, static_cast<size_t>(colorCount)},
                               pos != nullptr ? SkSpan<const SkScalar>(pos, static_cast<size_t>(colorCount))
                                              : SkSpan<const SkScalar>(),
                               mode,
                               std::move(colorSpace)),
            interp);
    return SkShaders::LinearGradient(pts, gradient, localMatrix);
}

extern "C" sk_sp<SkShader> SkGradientShader_MakeRadial_old_interp_compat(
        const SkPoint& center,
        SkScalar radius,
        const SkColor4f colors[],
        sk_sp<SkColorSpace> colorSpace,
        const SkScalar pos[],
        int colorCount,
        SkTileMode mode,
        const SkGradient::Interpolation& interp,
        const SkMatrix* localMatrix)
        __asm("__ZN16SkGradientShader10MakeRadialERK7SkPointfPK8SkRGBA4fIL11SkAlphaType3EE5sk_spI12SkColorSpaceEPKfi10SkTileModeRKNS_13InterpolationEPK8SkMatrix");

extern "C" sk_sp<SkShader> SkGradientShader_MakeRadial_old_interp_compat(
        const SkPoint& center,
        SkScalar radius,
        const SkColor4f colors[],
        sk_sp<SkColorSpace> colorSpace,
        const SkScalar pos[],
        int colorCount,
        SkTileMode mode,
        const SkGradient::Interpolation& interp,
        const SkMatrix* localMatrix) {
    SkGradient gradient(
            SkGradient::Colors({colors, static_cast<size_t>(colorCount)},
                               pos != nullptr ? SkSpan<const SkScalar>(pos, static_cast<size_t>(colorCount))
                                              : SkSpan<const SkScalar>(),
                               mode,
                               std::move(colorSpace)),
            interp);
    return SkShaders::RadialGradient(center, radius, gradient, localMatrix);
}

extern "C" sk_sp<SkShader> SkGradientShader_MakeTwoPointConical_old_interp_compat(
        const SkPoint& start,
        SkScalar startRadius,
        const SkPoint& end,
        SkScalar endRadius,
        const SkColor4f colors[],
        sk_sp<SkColorSpace> colorSpace,
        const SkScalar pos[],
        int colorCount,
        SkTileMode mode,
        const SkGradient::Interpolation& interp,
        const SkMatrix* localMatrix)
        __asm("__ZN16SkGradientShader19MakeTwoPointConicalERK7SkPointfS2_fPK8SkRGBA4fIL11SkAlphaType3EE5sk_spI12SkColorSpaceEPKfi10SkTileModeRKNS_13InterpolationEPK8SkMatrix");

extern "C" sk_sp<SkShader> SkGradientShader_MakeTwoPointConical_old_interp_compat(
        const SkPoint& start,
        SkScalar startRadius,
        const SkPoint& end,
        SkScalar endRadius,
        const SkColor4f colors[],
        sk_sp<SkColorSpace> colorSpace,
        const SkScalar pos[],
        int colorCount,
        SkTileMode mode,
        const SkGradient::Interpolation& interp,
        const SkMatrix* localMatrix) {
    SkGradient gradient(
            SkGradient::Colors({colors, static_cast<size_t>(colorCount)},
                               pos != nullptr ? SkSpan<const SkScalar>(pos, static_cast<size_t>(colorCount))
                                              : SkSpan<const SkScalar>(),
                               mode,
                               std::move(colorSpace)),
            interp);
    return SkShaders::TwoPointConicalGradient(
            start, startRadius, end, endRadius, gradient, localMatrix);
}
