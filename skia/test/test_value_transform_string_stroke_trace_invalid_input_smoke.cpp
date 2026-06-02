#include "capi/sk_i_point.h"
#include "capi/sk_point_3.h"
#include "capi/sk_rsx_form.h"
#include "capi/sk_size.h"
#include "capi/sk_string.h"
#include "capi/sk_stroke_rec.h"
#include "capi/sk_trace_memory_dump.h"
#include "handles/static_sk_i_point.h"
#include "handles/static_sk_point_3.h"
#include "handles/static_sk_rsx_form.h"
#include "handles/static_sk_size_t.h"
#include "handles/static_sk_stroke_rec.h"
#include "include/core/SkPoint.h"

#include <cstdio>
#include <cstring>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[value-transform-string-stroke-trace-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    ok &= check(SkIPoint_x(nullptr) == 0 && SkIPoint_y(nullptr) == 0, "IPoint null dimensions");
    ok &= check(SkIPoint_isZero(nullptr), "IPoint null isZero");
    ok &= check(!SkIPoint_equals(nullptr, 0, 0), "IPoint null equals");
    SkIPoint_set(nullptr, 1, 2);
    const sk_i_point_t ipoint_handle = SkIPoint_Make(3, 4);
    void *ipoint = static_sk_i_point_get_ptr(ipoint_handle);
    ok &= check(ipoint != nullptr && SkIPoint_x(ipoint) == 3 && SkIPoint_y(ipoint) == 4, "IPoint valid handle");

    ok &= check(SkPoint3_x(nullptr) == 0.0f && SkPoint3_y(nullptr) == 0.0f && SkPoint3_z(nullptr) == 0.0f, "Point3 null dimensions");
    ok &= check(SkPoint3_length(nullptr) == 0.0f, "Point3 null length");
    ok &= check(!SkPoint3_normalize(nullptr), "Point3 null normalize");
    ok &= check(SkPoint3_makeScale(nullptr, 2.0f) == 0, "Point3 null makeScale");
    ok &= check(SkPoint3_negate(nullptr) == 0, "Point3 null negate");
    SkPoint3_addAssign(nullptr, nullptr);
    SkPoint3_subtractAssign(nullptr, nullptr);
    ok &= check(!SkPoint3_isFinite(nullptr), "Point3 null isFinite");
    ok &= check(SkPoint3_dot(nullptr, nullptr) == 0.0f, "Point3 null dot");
    ok &= check(SkPoint3_cross(nullptr, nullptr) == 0, "Point3 null cross");
    ok &= check(SkPoint3_DotProduct(nullptr, nullptr) == 0.0f, "Point3 static null dot");
    ok &= check(SkPoint3_CrossProduct(nullptr, nullptr) == 0, "Point3 static null cross");
    const sk_point_3_t point3_handle = SkPoint3_Make(1.0f, 2.0f, 2.0f);
    const sk_point_3_t point3_other_handle = SkPoint3_Make(1.0f, 1.0f, 1.0f);
    auto *point3 = static_cast<reskia_point_3_t *>(static_sk_point_3_get_ptr(point3_handle));
    auto *point3_other = static_cast<reskia_point_3_t *>(static_sk_point_3_get_ptr(point3_other_handle));
    ok &= check(point3 != nullptr && SkPoint3_length(point3) == 3.0f, "Point3 valid handle");
    const sk_point_3_t point3_negate_handle = SkPoint3_negate(point3);
    auto *point3_negate = static_cast<reskia_point_3_t *>(static_sk_point_3_get_ptr(point3_negate_handle));
    ok &= check(point3_negate != nullptr && SkPoint3_x(point3_negate) == -1.0f, "Point3 negate valid");
    SkPoint3_addAssign(point3, point3_other);
    SkPoint3_subtractAssign(point3, point3_other);
    ok &= check(SkPoint3_x(point3) == 1.0f && SkPoint3_y(point3) == 2.0f, "Point3 assign ops valid");

    SkRSXform_setIdentity(nullptr);
    SkRSXform_set(nullptr, 1.0f, 0.0f, 2.0f, 3.0f);
    SkRSXform_toQuad(nullptr, 1.0f, 1.0f, nullptr);
    SkRSXform_toQuadWithSize(nullptr, nullptr, nullptr);
    SkRSXform_toTriStrip(nullptr, 1.0f, 1.0f, nullptr);
    ok &= check(!SkRSXform_rectStaysRect(nullptr), "RSXform null rectStaysRect");
    const sk_rsx_form_t rsx_handle = SkRSXform_Make(1.0f, 0.0f, 2.0f, 3.0f);
    auto *rsx = static_cast<reskia_rsxform_t *>(static_sk_rsx_form_get_ptr(rsx_handle));
    SkPoint quad[4] = {};
    SkRSXform_toQuad(rsx, 2.0f, 3.0f, reinterpret_cast<reskia_point_t *>(quad));
    ok &= check(rsx != nullptr && quad[0].x() == 2.0f && quad[0].y() == 3.0f, "RSXform valid toQuad");
    const sk_size_t size_handle = SkSize_Make(2.0f, 3.0f);
    auto *size = static_cast<reskia_size_t *>(static_sk_size_get_ptr(size_handle));
    SkRSXform_toQuadWithSize(rsx, size, reinterpret_cast<reskia_point_t *>(quad));
    ok &= check(size != nullptr && quad[0].x() == 2.0f && quad[0].y() == 3.0f, "RSXform valid toQuadWithSize");
    SkPoint strip[4] = {};
    SkRSXform_toTriStrip(rsx, 2.0f, 3.0f, reinterpret_cast<reskia_point_t *>(strip));
    ok &= check(strip[0].x() == 2.0f && strip[0].y() == 3.0f, "RSXform valid toTriStrip");
    const sk_rsx_form_t radians_handle = SkRSXform_MakeFromRadians(1.0f, 0.0f, 2.0f, 3.0f, 0.0f, 0.0f);
    auto *radians_rsx = static_cast<reskia_rsxform_t *>(static_sk_rsx_form_get_ptr(radians_handle));
    ok &= check(radians_rsx != nullptr && SkRSXform_rectStaysRect(radians_rsx), "RSXform MakeFromRadians valid handle");

    ok &= check(SkString_newFromText(nullptr) == nullptr, "String newFromText null");
    ok &= check(SkString_newFromTextWithLength(nullptr, 1) == nullptr, "String newFromTextWithLength null");
    ok &= check(SkString_newCopy(nullptr) == nullptr, "String copy null");
    ok &= check(SkString_newFromStdString(nullptr) == nullptr, "String std copy null");
    ok &= check(SkString_isEmpty(nullptr), "String null isEmpty");
    ok &= check(SkString_size(nullptr) == 0, "String null size");
    ok &= check(SkString_data(nullptr) == nullptr && SkString_dataMutable(nullptr) == nullptr && SkString_c_str(nullptr) == nullptr, "String null borrowed data");
    ok &= check(!SkString_equals(nullptr, nullptr), "String null equals");
    ok &= check(!SkString_equalsText(nullptr, "a"), "String null equalsText");
    ok &= check(!SkString_startsWith(nullptr, "a"), "String null startsWith");
    ok &= check(!SkString_contains(nullptr, "a"), "String null contains");
    ok &= check(SkString_find(nullptr, "a") == -1 && SkString_findLastOf(nullptr, 'a') == -1, "String null find");
    SkString_reset(nullptr);
    SkString_resize(nullptr, 4);
    SkString_set(nullptr, nullptr);
    SkString_setText(nullptr, "a");
    SkString_insert(nullptr, 0, "a");
    SkString_append(nullptr, "a");
    SkString_prepend(nullptr, "a");
    SkString_printf(nullptr, "%s", "a");
    SkString_remove(nullptr, 0, 1);
    SkString_swap(nullptr, nullptr);
    auto *string = SkString_newFromText("abc");
    ok &= check(string != nullptr && SkString_size(string) == 3 && std::strcmp(SkString_c_str(string), "abc") == 0, "String valid construction");
    char *mutable_data = SkString_dataMutable(string);
    ok &= check(mutable_data != nullptr && SkString_data(string) != nullptr, "String borrowed data valid");
    mutable_data[0] = 'z';
    ok &= check(std::strcmp(SkString_c_str(string), "zbc") == 0, "String mutable borrowed data reflects change");
    SkString_append(string, "d");
    SkString_prepend(string, "y");
    ok &= check(std::strcmp(SkString_c_str(string), "yzbcd") == 0, "String valid append prepend");

    ok &= check(SkStrokeRec_static(-1) == 0, "StrokeRec invalid init style");
    ok &= check(SkStrokeRec_staticWithPaintStyleAndResScale(nullptr, 0, 1.0f) == 0, "StrokeRec null paint style constructor");
    ok &= check(SkStrokeRec_staticWithPaintAndResScale(nullptr, 1.0f) == 0, "StrokeRec null paint constructor");
    ok &= check(SkStrokeRec_getStyle(nullptr) == 0, "StrokeRec null style");
    ok &= check(SkStrokeRec_getWidth(nullptr) == 0.0f && SkStrokeRec_getMiter(nullptr) == 0.0f, "StrokeRec null scalar getters");
    ok &= check(SkStrokeRec_getCap(nullptr) == 0 && SkStrokeRec_getJoin(nullptr) == 0, "StrokeRec null enum getters");
    ok &= check(!SkStrokeRec_isHairlineStyle(nullptr) && !SkStrokeRec_isFillStyle(nullptr), "StrokeRec null style predicates");
    SkStrokeRec_setFillStyle(nullptr);
    SkStrokeRec_setHairlineStyle(nullptr);
    SkStrokeRec_setStrokeStyle(nullptr, 1.0f, false);
    SkStrokeRec_setStrokeParams(nullptr, 0, 0, 4.0f);
    ok &= check(SkStrokeRec_getResScale(nullptr) == 0.0f, "StrokeRec null res scale");
    SkStrokeRec_setResScale(nullptr, 1.0f);
    ok &= check(!SkStrokeRec_needToApply(nullptr), "StrokeRec null needToApply");
    ok &= check(!SkStrokeRec_applyToPath(nullptr, nullptr, nullptr), "StrokeRec null applyToPath");
    SkStrokeRec_applyToPaint(nullptr, nullptr);
    ok &= check(SkStrokeRec_getInflationRadius(nullptr) == 0.0f, "StrokeRec null inflation");
    ok &= check(!SkStrokeRec_hasEqualEffect(nullptr, nullptr), "StrokeRec null equal effect");
    ok &= check(SkStrokeRec_GetInflationRadius(nullptr, 0) == 0.0f, "StrokeRec static null paint inflation");
    ok &= check(SkStrokeRec_GetInflationRadiusWithJoinMiterCapAndStrokeWidth(-1, 4.0f, 0, 1.0f) == 0.0f, "StrokeRec static invalid enum inflation");
    const sk_stroke_rec_t stroke_handle = SkStrokeRec_static(1);
    auto *stroke = static_cast<reskia_stroke_rec_t *>(static_sk_stroke_rec_get_ptr(stroke_handle));
    ok &= check(stroke != nullptr && SkStrokeRec_isFillStyle(stroke), "StrokeRec valid handle");

    SkTraceMemoryDump_dumpNumericValue(nullptr, "dump", "value", "bytes", 1);
    SkTraceMemoryDump_dumpNumericValue(nullptr, nullptr, nullptr, nullptr, 1);
    SkTraceMemoryDump_dumpStringValue(nullptr, "dump", "name", "value");
    SkTraceMemoryDump_setMemoryBacking(nullptr, "dump", "type", "id");
    SkTraceMemoryDump_setDiscardableMemoryBacking(nullptr, "dump", nullptr);
    ok &= check(SkTraceMemoryDump_getRequestedDetails(nullptr) == 0, "TraceMemoryDump null details");
    ok &= check(!SkTraceMemoryDump_shouldDumpWrappedObjects(nullptr), "TraceMemoryDump null wrapped predicate");
    SkTraceMemoryDump_dumpWrappedState(nullptr, "state", true);
    ok &= check(!SkTraceMemoryDump_shouldDumpUnbudgetedObjects(nullptr), "TraceMemoryDump null unbudgeted predicate");
    SkTraceMemoryDump_dumpBudgetedState(nullptr, "state", true);
    ok &= check(!SkTraceMemoryDump_shouldDumpSizelessObjects(nullptr), "TraceMemoryDump null sizeless predicate");

    SkString_delete(string);
    static_sk_stroke_rec_delete(stroke_handle);
    static_sk_rsx_form_delete(radians_handle);
    static_sk_size_delete(size_handle);
    static_sk_rsx_form_delete(rsx_handle);
    static_sk_point_3_delete(point3_negate_handle);
    static_sk_point_3_delete(point3_other_handle);
    static_sk_point_3_delete(point3_handle);
    static_sk_i_point_delete(ipoint_handle);
    return ok ? 0 : 1;
}
