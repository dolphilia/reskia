#include "capi/sk_image_filter.h"
#include "capi/sk_image_filters.h"
#include "handles/static_sk_image_filter.h"

#include <cstdio>

namespace {
bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[image-filter-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}
}

int main() {
    bool ok = true;

    SkImageFilter_release(nullptr);
    SkImageFilter_ref(nullptr);
    SkImageFilter_unref(nullptr);
    SkImageFilter_flatten(nullptr, nullptr);
    SkImageFilter_Register(nullptr, 0);

    ok &= check(SkImageFilter_filterBounds(nullptr, nullptr, nullptr, 0, nullptr) == 0, "filterBounds null");
    ok &= check(!SkImageFilter_isColorFilterNode(nullptr, nullptr), "isColorFilterNode null");
    ok &= check(!SkImageFilter_asColorFilter(nullptr, nullptr), "asColorFilter null");
    ok &= check(!SkImageFilter_asAColorFilter(nullptr, nullptr), "asAColorFilter null");
    ok &= check(SkImageFilter_countInputs(nullptr) == 0, "countInputs null");
    ok &= check(SkImageFilter_getInput(nullptr, 0) == nullptr, "getInput null");
    ok &= check(SkImageFilter_computeFastBounds(nullptr, nullptr) == 0, "computeFastBounds null");
    ok &= check(!SkImageFilter_canComputeFastBounds(nullptr), "canComputeFastBounds null");
    ok &= check(SkImageFilter_makeWithLocalMatrix(nullptr, nullptr) == 0, "makeWithLocalMatrix null");
    ok &= check(SkImageFilter_getFactory(nullptr) == 0, "getFactory null");
    ok &= check(SkImageFilter_getTypeName(nullptr) == nullptr, "getTypeName null");
    ok &= check(SkImageFilter_getFlattenableType(nullptr) == 0, "getFlattenableType null");
    ok &= check(SkImageFilter_serialize(nullptr, nullptr) == 0, "serialize null");
    ok &= check(SkImageFilter_serializeToMemory(nullptr, nullptr, 0, nullptr) == 0, "serializeToMemory null");
    ok &= check(!SkImageFilter_unique(nullptr), "unique null");
    ok &= check(SkImageFilter_Deserialize(nullptr, 0, nullptr) == 0, "Deserialize null");
    ok &= check(SkImageFilter_NameToFactory(nullptr) == 0, "NameToFactory null");
    ok &= check(SkImageFilter_FactoryToName(0) == nullptr, "FactoryToName null factory");

    const sk_image_filter_t empty = SkImageFilters_Empty();
    ok &= check(empty != 0, "Empty returns handle");
    static_sk_image_filter_delete(empty);

    const sk_image_filter_t blur = SkImageFilters_BlurWithoutTileMode(1.0f, 1.0f, 0, nullptr);
    ok &= check(blur != 0, "BlurWithoutTileMode null cropRect");
    static_sk_image_filter_delete(blur);

    const sk_image_filter_t shadow = SkImageFilters_DropShadow(1.0f, 1.0f, 1.0f, 1.0f, 0xff000000u, 0, nullptr);
    ok &= check(shadow != 0, "DropShadow null cropRect");
    static_sk_image_filter_delete(shadow);

    ok &= check(SkImageFilters_Crop(nullptr, 0, 0) == 0, "Crop null rect");
    ok &= check(SkImageFilters_Image(0, nullptr, nullptr, nullptr) == 0, "Image null refs");
    ok &= check(SkImageFilters_Magnifier(nullptr, 1.0f, 0.0f, nullptr, 0, nullptr) == 0, "Magnifier null refs");
    ok &= check(SkImageFilters_MatrixConvolution(nullptr, nullptr, 1.0f, 0.0f, nullptr, 0, false, 0, nullptr) == 0, "MatrixConvolution null refs");
    ok &= check(SkImageFilters_MatrixTransform(nullptr, nullptr, 0) == 0, "MatrixTransform null refs");
    ok &= check(SkImageFilters_Merge(nullptr, 1, nullptr) == 0, "Merge null filters");
    ok &= check(SkImageFilters_Picture(0, nullptr) == 0, "Picture null targetRect");
    ok &= check(SkImageFilters_RuntimeShader(nullptr, 0, 0) == 0, "RuntimeShader null builder");
    ok &= check(SkImageFilters_RuntimeShaderWithChildShaderNames(nullptr, nullptr, nullptr, 1) == 0, "RuntimeShader child arrays null");
    ok &= check(SkImageFilters_Tile(nullptr, nullptr, 0) == 0, "Tile null rects");
    ok &= check(SkImageFilters_DistantLitDiffuse(nullptr, 0, 1.0f, 1.0f, 0, nullptr) == 0, "DistantLitDiffuse null direction");
    ok &= check(SkImageFilters_PointLitSpecular(nullptr, 0, 1.0f, 1.0f, 1.0f, 0, nullptr) == 0, "PointLitSpecular null location");

    return ok ? 0 : 1;
}
