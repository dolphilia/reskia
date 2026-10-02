#include "capi/sk_context.h"
#include "capi/sk_gpu_context.h"
#include "capi/sk_path.h"
#include "capi/sk_string.h"
#include "include/core/SkPath.h"
#include "include/core/SkRect.h"
#include "capi/sk_image_filters.h"
#include "capi/sk_icc.h"
#include "handles/static_sk_data.h"
#include "include/core/SkData.h"
#include "include/core/SkColorSpace.h"
#include <cstring>
#include "capi/sk_font.h"
#include "capi/sk_point.h"
#include "capi/sk_shaper.h"
#include "capi/sk_text_blob_builder_run_handler.h"
#include "handles/static_sk_image_filter.h"
#include "handles/static_sk_text_blob.h"
#include "handles/static_std_string_view-internal.h"
#include "handles/static_std_string_view.h"
#include "include/core/SkImageFilter.h"
#include "include/core/SkMatrix.h"
#include "include/effects/SkRuntimeEffect.h"

#include <cmath>
#include <cstdio>
#include <limits>

bool runtime_bounds() {
    auto result = SkRuntimeEffect::MakeForShader(SkString(
            "uniform shader child; half4 main(float2 p) { return child.eval(p); }"));
    if (!result.effect) { return false; }
    SkRuntimeShaderBuilder builder(result.effect);
    const auto* cb = reinterpret_cast<const reskia_runtime_effect_builder_t*>(
            static_cast<const SkRuntimeEffectBuilder*>(&builder));
    const int child = static_string_view_make("child");
    const sk_image_filter_t input = 0;
    auto loose = SkImageFilters_RuntimeShaderWithBounds(cb, 0, child, 0, false);
    auto tight = SkImageFilters_RuntimeShaderWithChildBounds(cb, 0, &child, &input, 1, true);
    auto legacy = SkImageFilters_RuntimeShaderWithSampleRadius(cb, 0, child, 0);
    bool ok = loose && tight && legacy;
    if (ok) {
        auto bounds = [](int handle) {
            return static_cast<SkImageFilter*>(static_sk_image_filter_get_ptr(handle))->filterBounds(
                    SkIRect::MakeWH(10, 10), SkMatrix::I(), SkImageFilter::kForward_MapDirection);
        };
        ok = bounds(tight) == SkIRect::MakeWH(10, 10) &&
             bounds(loose) == bounds(legacy) && bounds(loose) != bounds(tight);
    }
    ok &= SkImageFilters_RuntimeShaderWithBounds(nullptr, 0, child, 0, true) == 0;
    ok &= SkImageFilters_RuntimeShaderWithBounds(cb, -1, child, 0, true) == 0;
    ok &= SkImageFilters_RuntimeShaderWithChildBounds(cb, 0, nullptr, nullptr, 1, true) == 0;
    const int invalid = -1;
    ok &= SkImageFilters_RuntimeShaderWithChildBounds(cb, 0, &invalid, &input, 1, true) == 0;
    static_sk_image_filter_delete(loose);
    static_sk_image_filter_delete(tight);
    static_sk_image_filter_delete(legacy);
    static_string_view_delete(child);
    return ok;
}

float tracked_endpoint(float tracking) {
    const char* text = "abcd";
    auto* shaper = SkShaper_MakePrimitive();
    auto* font = SkFont_new();
    auto offset = SkPoint_Make(0, 0);
    auto* handler = SkTextBlobBuilderRunHandler_new(text, offset);
    auto* fonts = SkShaper_MakeFontMgrRunIterator(text, 4, font, 0);
    auto* bidi = SkShaper_MakeBiDiRunIterator(text, 4, 0);
    auto* script = SkShaper_MakeScriptRunIterator(text, 4, 0x5a797979);
    auto* language = SkShaper_MakeStdLanguageRunIterator(text, 4);
    bool ok = SkShaper_shapeWithTextTracking(shaper, text, 4, fonts, bidi, script, language,
                                           nullptr, 0, 1000, tracking, handler);
    float x = std::numeric_limits<float>::quiet_NaN();
    auto blob = SkTextBlobBuilderRunHandler_makeBlob(handler);
    if (ok && blob) {
        SkTextBlob::Iter iter(*static_cast<SkTextBlob*>(static_sk_text_blob_get_ptr(blob)));
        SkTextBlob::Iter::ExperimentalRun run;
        if (iter.experimentalNext(&run) && run.count == 4 && run.positions) {
            x = run.positions[3].fX;
        }
    }
    static_sk_text_blob_delete(blob);
    SkShaper_FontRunIterator_delete(fonts);
    SkShaper_BiDiRunIterator_delete(bidi);
    SkShaper_ScriptRunIterator_delete(script);
    SkShaper_LanguageRunIterator_delete(language);
    SkTextBlobBuilderRunHandler_delete(handler);
    static_sk_point_delete(offset);
    SkFont_delete(font);
    SkShaper_delete(shaper);
    return x;
}

bool context_generation_status() {
    auto options = SkContextOptions_default();
    auto* context = SkContexts_MakeRaster(nullptr);
    auto* configured = SkContexts_MakeRaster(&options);
    bool ok = context && configured && options.font_cache_count_limit > 0;
    SkContext_delete(configured);
    SkContext_delete(context);
    SkContext_delete(nullptr);
    options.font_cache_count_limit = -1;
    ok &= SkContexts_MakeRaster(&options) == nullptr;
    SkPath path = SkPath::Rect(SkRect::MakeWH(10, 20));
    auto* cpath = reinterpret_cast<reskia_path_t*>(&path);
    const uint64_t generation = SkPath_getGenerationID64(cpath);
    ok &= generation != 0 && generation == path.getGenerationID();
    ok &= SkPath_getGenerationID(cpath) == static_cast<uint32_t>(generation);
    auto* copy = SkPath_newCopy(cpath);
    ok &= SkPath_getGenerationID64(copy) == generation;
    SkPath_delete(copy);
    path = SkPath::Rect(SkRect::MakeWH(20, 30));
    ok &= SkPath_getGenerationID64(cpath) != generation;
    ok &= SkPath_getGenerationID64(nullptr) == 0 && SkPath_getGenerationID(nullptr) == 0;

    auto* status = Graphite_InsertStatus_newWithPendingCounts(0, 17, 3);
    ok &= status && Graphite_InsertStatusInfo_isSuccess(status) &&
          Graphite_InsertStatusInfo_value(status) == 0 &&
          Graphite_InsertStatus_numPendingCommands(status) == 17 &&
          Graphite_InsertStatus_numPendingPasses(status) == 3;
    Graphite_InsertStatus_deleteInfo(status);
    auto* failure = Graphite_InsertStatus_newWithMessage(1, "test failure");
    auto* message = Graphite_InsertStatusInfo_message(failure);
    const char* text = SkString_c_str(message);
    ok &= failure && !Graphite_InsertStatusInfo_isSuccess(failure) && text &&
          std::strcmp(text, "test failure") == 0 &&
          Graphite_InsertStatus_numPendingCommands(failure) == 0;
    SkString_delete(message);
    Graphite_InsertStatus_deleteInfo(failure);
    ok &= Graphite_InsertStatus_newWithPendingCounts(0, -1, 0) == nullptr &&
          Graphite_InsertStatus_newWithMessage(-1, "invalid") == nullptr &&
          Graphite_InsertStatusInfo_value(nullptr) == -1 &&
          Graphite_InsertStatus_numPendingCommands(nullptr) == 0 &&
          !Graphite_InsertStatusInfo_isSuccess(nullptr) &&
          Graphite_Context_insertRecordingWithStatus(nullptr, nullptr) == nullptr;
    Graphite_InsertStatus_deleteInfo(nullptr);
    return ok;
}

int main() {
    if (!context_generation_status()) { std::fputs("context/generation/status FAIL\n", stderr); return 5; }

    auto colorSpace = SkColorSpace::MakeSRGB();
    auto profile = SkICC_SkWriteICCProfileFromColorSpace(
            reinterpret_cast<const reskia_color_space_t*>(colorSpace.get()), nullptr);
    auto* data = static_cast<SkData*>(static_sk_data_get_ptr(profile));
    if (!data || data->size() < 40 || std::memcmp(static_cast<const char*>(data->data()) + 36, "acsp", 4) != 0 ||
        SkICC_SkWriteICCProfileFromColorSpace(nullptr, nullptr)) { return 4; }
    static_sk_data_delete(profile);
    if (!runtime_bounds()) { std::fputs("runtime bounds FAIL\n", stderr); return 1; }
    float zero = tracked_endpoint(0), positive = tracked_endpoint(0.25f);
    if (!std::isfinite(zero) || !(positive > zero)) {
        std::fprintf(stderr, "tracking FAIL: %f -> %f\n", zero, positive); return 2;
    }
    if (std::isfinite(tracked_endpoint(std::numeric_limits<float>::quiet_NaN()))) { return 3; }
    std::puts("[upgrade-api-smoke] PASS");
    return 0;
}
