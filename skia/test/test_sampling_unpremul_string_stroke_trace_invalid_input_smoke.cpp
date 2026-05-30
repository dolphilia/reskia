#include "capi/sk_cubic_resampler.h"
#include "capi/sk_paint.h"
#include "capi/sk_path.h"
#include "capi/sk_sampling_options.h"
#include "capi/sk_string.h"
#include "capi/sk_stroke_rec.h"
#include "capi/sk_trace_memory_dump.h"
#include "capi/sk_un_pre_multiply.h"
#include "handles/static_sk_cubic_resampler.h"
#include "handles/static_sk_sampling_options.h"
#include "handles/static_sk_stroke_rec.h"
#include "handles/static_std_string_view.h"
#include "handles/static_std_string_view-internal.h"
#include "include/core/SkTraceMemoryDump.h"

#include <cstdio>
#include <string>
#include <vector>

namespace {

class RecordingTraceMemoryDump final : public SkTraceMemoryDump {
public:
    void dumpNumericValue(const char *dumpName, const char *valueName, const char *units, uint64_t value) override {
        events.push_back(std::string(dumpName) + ":" + valueName + ":" + units + ":" + std::to_string(value));
    }

    void dumpStringValue(const char *dumpName, const char *str1, const char *str2) override {
        events.push_back(std::string(dumpName) + ":" + str1 + ":" + str2);
    }

    void setMemoryBacking(const char *dumpName, const char *backingType, const char *backingObjectId) override {
        events.push_back(std::string(dumpName) + ":" + backingType + ":" + backingObjectId);
    }

    void setDiscardableMemoryBacking(const char *, const SkDiscardableMemory &) override {
        events.push_back("discardable");
    }

    LevelOfDetail getRequestedDetails() const override {
        return kLight_LevelOfDetail;
    }

    bool shouldDumpWrappedObjects() const override {
        return true;
    }

    void dumpWrappedState(const char *str, bool b) override {
        events.push_back(std::string(str) + ":" + (b ? "true" : "false"));
    }

    bool shouldDumpUnbudgetedObjects() const override {
        return true;
    }

    void dumpBudgetedState(const char *str, bool b) override {
        events.push_back(std::string(str) + ":" + (b ? "true" : "false"));
    }

    bool shouldDumpSizelessObjects() const override {
        return true;
    }

    std::vector<std::string> events;
};

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[sampling-unpremul-string-stroke-trace-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    ok &= check(SkSamplingOptions_newCopy(nullptr) == nullptr, "SamplingOptions copy null");
    ok &= check(SkSamplingOptions_newWithFilterAndMipmapModes(-1, 0) == nullptr, "SamplingOptions invalid filter");
    ok &= check(SkSamplingOptions_newWithFilterAndMipmapModes(0, 99) == nullptr, "SamplingOptions invalid mipmap");
    ok &= check(SkSamplingOptions_newWithFilterMode(99) == nullptr, "SamplingOptions invalid single filter");
    ok &= check(SkSamplingOptions_new_5(nullptr) == nullptr, "SamplingOptions null cubic");
    ok &= check(!SkSamplingOptions_equals(nullptr, nullptr), "SamplingOptions equals null");
    ok &= check(!SkSamplingOptions_notEquals(nullptr, nullptr), "SamplingOptions notEquals null");
    ok &= check(!SkSamplingOptions_isAniso(nullptr), "SamplingOptions isAniso null");
    const sk_cubic_resampler_t cubic_handle = SkCubicResampler_Mitchell();
    auto *cubic = static_cast<reskia_cubic_resampler_t *>(static_sk_cubic_resampler_get_ptr(cubic_handle));
    auto *cubic_options = SkSamplingOptions_new_5(cubic);
    ok &= check(cubic != nullptr && cubic_options != nullptr && !SkSamplingOptions_isAniso(cubic_options), "SamplingOptions valid cubic");
    const sk_sampling_options_t aniso_handle = SkSamplingOptions_Aniso(0);
    auto *aniso = static_cast<reskia_sampling_options_t *>(static_sk_sampling_options_get_ptr(aniso_handle));
    ok &= check(aniso != nullptr && SkSamplingOptions_isAniso(aniso), "SamplingOptions Aniso clamps to valid handle");
    auto *filter_options = SkSamplingOptions_newWithFilterAndMipmapModes(1, 2);
    ok &= check(filter_options != nullptr, "SamplingOptions valid filter/mipmap");
    auto *filter_options_copy = SkSamplingOptions_newCopy(filter_options);
    ok &= check(filter_options_copy != nullptr, "SamplingOptions copy valid");
    ok &= check(SkSamplingOptions_equals(filter_options, filter_options_copy), "SamplingOptions equals valid");
    ok &= check(SkSamplingOptions_notEquals(filter_options, aniso), "SamplingOptions notEquals valid");

    const reskia_un_pre_multiply_scale_t *table = SkUnPreMultiply_GetScaleTable();
    ok &= check(table != nullptr, "UnPreMultiply borrowed table");
    ok &= check(SkUnPreMultiply_GetScale(256) == 0, "UnPreMultiply invalid alpha");
    ok &= check(SkUnPreMultiply_ApplyScale(1, 256) == 0, "UnPreMultiply invalid component");
    ok &= check(SkUnPreMultiply_PMColorToColor(0) == 0, "UnPreMultiply transparent color");

    ok &= check(SkString_new_7(999999) == nullptr, "String invalid string_view constructor");
    auto *string = SkString_newFromText("base");
    ok &= check(string != nullptr, "String base allocation");
    ok &= check(!SkString_endsWith(nullptr, "se"), "String endsWith null string");
    ok &= check(!SkString_endsWith(string, nullptr), "String endsWith null suffix");
    ok &= check(!SkString_endsWithChar(nullptr, 'e'), "String endsWithChar null string");
    ok &= check(SkString_endsWith(string, "se"), "String endsWith valid suffix");
    ok &= check(SkString_endsWithChar(string, 'e'), "String endsWithChar valid suffix");
    const size_t before_invalid_view = SkString_size(string);
    SkString_setStringView(string, 999999);
    SkString_insertStringView(string, 0, 999999);
    SkString_appendStringView(string, 999999);
    SkString_prependStringView(string, 999999);
    ok &= check(SkString_size(string) == before_invalid_view, "String invalid string_view no-op");
    const string_view_t view = static_string_view_make("ok");
    auto *from_view = SkString_new_7(view);
    ok &= check(from_view != nullptr && SkString_size(from_view) == 2, "String valid string_view constructor");
    SkString_setStringView(string, view);
    ok &= check(SkString_size(string) == 2, "String valid string_view set");

    auto *paint = SkPaint_new();
    auto *src_path = SkPath_new();
    auto *dst_path = SkPath_new();
    SkPath_moveTo(src_path, 0.0f, 0.0f);
    SkPath_lineTo(src_path, 10.0f, 0.0f);
    const sk_stroke_rec_t stroke_handle = SkStrokeRec_staticWithPaintStyleAndResScale(paint, 1, 1.0f);
    auto *stroke = static_cast<reskia_stroke_rec_t *>(static_sk_stroke_rec_get_ptr(stroke_handle));
    ok &= check(stroke != nullptr, "StrokeRec valid paint/style constructor");
    SkStrokeRec_setStrokeParams(stroke, 1, 1, 4.0f);
    SkStrokeRec_setResScale(stroke, 2.0f);
    const float radius = SkStrokeRec_GetInflationRadius(paint, 1);
    ok &= check(radius >= 0.0f, "StrokeRec valid static inflation");
    const bool applied = SkStrokeRec_applyToPath(stroke, dst_path, src_path);
    ok &= check(applied || !SkStrokeRec_needToApply(stroke), "StrokeRec valid applyToPath integration");
    SkStrokeRec_applyToPaint(stroke, paint);

    RecordingTraceMemoryDump dump;
    auto *dump_ptr = reinterpret_cast<reskia_trace_memory_dump_t *>(&dump);
    SkTraceMemoryDump_dumpNumericValue(dump_ptr, "dump", "bytes", "bytes", 7);
    SkTraceMemoryDump_dumpStringValue(dump_ptr, "dump", "key", "value");
    SkTraceMemoryDump_setMemoryBacking(dump_ptr, "dump", "type", "id");
    SkTraceMemoryDump_dumpWrappedState(dump_ptr, "wrapped", true);
    SkTraceMemoryDump_dumpBudgetedState(dump_ptr, "budgeted", false);
    const size_t event_count_after_valid = dump.events.size();
    SkTraceMemoryDump_dumpNumericValue(dump_ptr, nullptr, "bytes", "bytes", 7);
    SkTraceMemoryDump_dumpStringValue(dump_ptr, "dump", nullptr, "value");
    SkTraceMemoryDump_setMemoryBacking(dump_ptr, "dump", nullptr, "id");
    SkTraceMemoryDump_dumpWrappedState(dump_ptr, nullptr, true);
    SkTraceMemoryDump_dumpBudgetedState(dump_ptr, nullptr, false);
    ok &= check(SkTraceMemoryDump_getRequestedDetails(dump_ptr) == 0, "TraceMemoryDump valid details sentinel");
    ok &= check(SkTraceMemoryDump_shouldDumpWrappedObjects(dump_ptr), "TraceMemoryDump valid wrapped predicate");
    ok &= check(SkTraceMemoryDump_shouldDumpUnbudgetedObjects(dump_ptr), "TraceMemoryDump valid unbudgeted predicate");
    ok &= check(SkTraceMemoryDump_shouldDumpSizelessObjects(dump_ptr), "TraceMemoryDump valid sizeless predicate");
    ok &= check(event_count_after_valid == 5 && dump.events.size() == event_count_after_valid, "TraceMemoryDump invalid strings no-op on concrete dump");

    SkPath_delete(dst_path);
    SkPath_delete(src_path);
    SkPaint_delete(paint);
    static_sk_stroke_rec_delete(stroke_handle);
    SkString_delete(from_view);
    static_string_view_delete(view);
    SkString_delete(string);
    SkSamplingOptions_delete(filter_options);
    SkSamplingOptions_delete(filter_options_copy);
    static_sk_sampling_options_delete(aniso_handle);
    SkSamplingOptions_delete(cubic_options);
    static_sk_cubic_resampler_delete(cubic_handle);
    return ok ? 0 : 1;
}
