#include "capi/sk_cubic_map.h"
#include "capi/sk_cubic_resampler.h"
#include "capi/sk_encoded_origin.h"
#include "handles/static_sk_cubic_resampler.h"
#include "handles/static_sk_matrix.h"
#include "handles/static_sk_point.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[encoded-cubic-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    ok &= check(SkEncodedOrigin_SkEncodedOriginToMatrix(0, 10, 20) == 0, "encoded origin matrix low invalid");
    ok &= check(SkEncodedOrigin_SkEncodedOriginToMatrix(9, 10, 20) == 0, "encoded origin matrix high invalid");
    ok &= check(!SkEncodedOrigin_SkEncodedOriginSwapsWidthHeight(0), "encoded origin swaps low invalid");
    ok &= check(!SkEncodedOrigin_SkEncodedOriginSwapsWidthHeight(9), "encoded origin swaps high invalid");
    const sk_matrix_t origin_matrix = SkEncodedOrigin_SkEncodedOriginToMatrix(1, 10, 20);
    ok &= check(origin_matrix != 0, "encoded origin valid matrix");
    if (origin_matrix != 0) {
        static_sk_matrix_delete(origin_matrix);
    }

    ok &= check(SkCubicMap_new(0, 0) == nullptr, "cubic map new invalid handles");
    SkCubicMap_delete(nullptr);
    ok &= check(SkCubicMap_computeYFromX(nullptr, 0.5f) == 0.0f, "cubic map computeY null");
    ok &= check(SkCubicMap_computeFromT(nullptr, 0.5f) == 0, "cubic map computeFromT null");
    ok &= check(!SkCubicMap_IsLinear(0, 0), "cubic map IsLinear invalid handles");

    SkCubicResampler_delete(nullptr);
    const sk_cubic_resampler_t mitchell = SkCubicResampler_Mitchell();
    ok &= check(mitchell != 0, "cubic resampler Mitchell");
    if (mitchell != 0) {
        static_sk_cubic_resampler_delete(mitchell);
    }
    const sk_cubic_resampler_t catmull = SkCubicResampler_CatmullRom();
    ok &= check(catmull != 0, "cubic resampler CatmullRom");
    if (catmull != 0) {
        static_sk_cubic_resampler_delete(catmull);
    }

    return ok ? 0 : 1;
}
