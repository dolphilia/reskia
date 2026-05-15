#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "include/core/SkBlendMode.h"

#include "capi/sk_canvas.h"
#include "capi/sk_data.h"
#include "capi/sk_document.h"
#include "capi/sk_dynamic_memory_w_stream.h"
#include "capi/sk_graphics.h"
#include "capi/sk_pdf.h"
#include "capi/sk_string.h"

#include "handles/static_sk_data.h"
#include "handles/static_sk_document.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[pdf-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool draw_single_page(reskia_document_t* document) {
    auto* canvas = SkDocument_beginPage(document, 120.0f, 80.0f, nullptr);
    if (!check(canvas != nullptr, "SkDocument_beginPage")) {
        return false;
    }

    SkPDF_SetNodeId(canvas, 1);
    SkCanvas_drawColorU32(canvas, 0xFF336699u, static_cast<reskia_blend_mode_t>(SkBlendMode::kSrcOver));
    SkDocument_endPage(document);
    SkDocument_close(document);
    return true;
}

bool validate_pdf_bytes(sk_data_t data_handle, const char* label) {
    if (!check(data_handle != 0, label)) {
        return false;
    }

    auto* data = reinterpret_cast<reskia_data_t*>(static_sk_data_get_ptr(data_handle));
    if (!check(data != nullptr, "static_sk_data_get_ptr")) {
        static_sk_data_delete(data_handle);
        return false;
    }

    const size_t size = SkData_size(data);
    if (!check(size > 0, "SkData_size > 0")) {
        static_sk_data_delete(data_handle);
        return false;
    }

    const auto* bytes = SkData_bytes(data);
    if (!check(bytes != nullptr, "SkData_bytes")) {
        static_sk_data_delete(data_handle);
        return false;
    }

    if (!check(size >= 5 && std::memcmp(bytes, "%PDF-", 5) == 0, "PDF signature")) {
        static_sk_data_delete(data_handle);
        return false;
    }

    static_sk_data_delete(data_handle);
    return true;
}

bool smoke_without_metadata() {
    auto* stream = SkDynamicMemoryWStream_new();
    if (!check(stream != nullptr, "SkDynamicMemoryWStream_new(no metadata)")) {
        return false;
    }

    const sk_document_t document_handle =
        SkPDF_MakeDocumentWithoutMetadata(reinterpret_cast<reskia_w_stream_t*>(stream));
    if (!check(document_handle != 0, "SkPDF_MakeDocumentWithoutMetadata")) {
        SkDynamicMemoryWStream_delete(stream);
        return false;
    }

    auto* document = reinterpret_cast<reskia_document_t*>(static_sk_document_get_ptr(document_handle));
    if (!check(document != nullptr, "static_sk_document_get_ptr(no metadata)")) {
        static_sk_document_delete(document_handle);
        SkDynamicMemoryWStream_delete(stream);
        return false;
    }

    if (!draw_single_page(document)) {
        static_sk_document_delete(document_handle);
        SkDynamicMemoryWStream_delete(stream);
        return false;
    }

    static_sk_document_delete(document_handle);

    const sk_data_t data = SkDynamicMemoryWStream_detachAsData(stream);
    const bool ok = validate_pdf_bytes(data, "SkDynamicMemoryWStream_detachAsData(no metadata)");
    SkDynamicMemoryWStream_delete(stream);
    return ok;
}

bool smoke_with_metadata() {
    auto* stream = SkDynamicMemoryWStream_new();
    if (!check(stream != nullptr, "SkDynamicMemoryWStream_new(with metadata)")) {
        return false;
    }

    reskia_pdf_metadata_t metadata{};
    metadata.title = "reskia-pdf-smoke";
    metadata.author = "codex";
    metadata.creator = "phase5";
    metadata.producer = "reskia-test";
    metadata.raster_dpi = 72.0f;
    metadata.encoding_quality = 95;
    metadata.compression_level = RESKIA_PDF_COMPRESSION_AVERAGE;
    metadata.subsetter = RESKIA_PDF_SUBSETTER_HARFBUZZ;
    metadata.outline = RESKIA_PDF_OUTLINE_NONE;
    metadata.pdfa = false;

    const sk_document_t document_handle =
        SkPDF_MakeDocument(reinterpret_cast<reskia_w_stream_t*>(stream), &metadata);
    if (!check(document_handle != 0, "SkPDF_MakeDocument")) {
        SkDynamicMemoryWStream_delete(stream);
        return false;
    }

    auto* document = reinterpret_cast<reskia_document_t*>(static_sk_document_get_ptr(document_handle));
    if (!check(document != nullptr, "static_sk_document_get_ptr(with metadata)")) {
        static_sk_document_delete(document_handle);
        SkDynamicMemoryWStream_delete(stream);
        return false;
    }

    if (!draw_single_page(document)) {
        static_sk_document_delete(document_handle);
        SkDynamicMemoryWStream_delete(stream);
        return false;
    }

    static_sk_document_delete(document_handle);

    const sk_data_t data = SkDynamicMemoryWStream_detachAsData(stream);
    const bool ok = validate_pdf_bytes(data, "SkDynamicMemoryWStream_detachAsData(with metadata)");
    SkDynamicMemoryWStream_delete(stream);
    return ok;
}

bool smoke_pdf_value_helpers() {
    reskia_pdf_attribute_list_t *attributes = AttributeList_new();
    if (!check(attributes != nullptr, "AttributeList_new")) {
        return false;
    }

    AttributeList_appendInt(attributes, "Layout", "RowSpan", 2);
    AttributeList_appendFloat(attributes, "Layout", "Width", 12.5f);
    AttributeList_appendName(attributes, "Layout", "Placement", "Block");
    const float bounds[] = {0.0f, 1.0f, 2.0f, 3.0f};
    AttributeList_appendFloatArray(attributes, "Layout", "BBox", bounds, sizeof(bounds) / sizeof(bounds[0]));
    const int node_ids[] = {1, 2, 3};
    AttributeList_appendNodeIdArray(attributes, "Table", "Headers", node_ids, sizeof(node_ids) / sizeof(node_ids[0]));
    AttributeList_delete(attributes);

    reskia_pdf_date_time_t date_time{};
    date_time.timezone_minutes = 9 * 60;
    date_time.year = 2026;
    date_time.month = 5;
    date_time.day = 16;
    date_time.hour = 12;
    date_time.minute = 34;
    date_time.second = 56;

    reskia_string_t *iso = SkString_new();
    if (!check(iso != nullptr, "SkString_new for DateTime_toISO8601")) {
        return false;
    }
    DateTime_toISO8601(&date_time, iso);
    const char *text = SkString_c_str(iso);
    const bool ok = check(text != nullptr && std::strstr(text, "2026-05-16T12:34:56") != nullptr,
                          "DateTime_toISO8601");
    SkString_delete(iso);
    return ok;
}

}  // namespace

int main() {
    SkGraphics_Init();

    if (!smoke_without_metadata()) {
        return 1;
    }
    if (!smoke_with_metadata()) {
        return 1;
    }
    if (!smoke_pdf_value_helpers()) {
        return 1;
    }

    std::fprintf(stdout, "[pdf-smoke] PASS\n");
    return 0;
}
