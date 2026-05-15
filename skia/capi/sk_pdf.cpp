//
// Created by dolphilia on 2024/01/13.
//

#include "sk_pdf.h"

#include "include/docs/SkPDFDocument.h"
#include "../handles/static_sk_document-internal.h"

#include <vector>

static void fill_pdf_datetime(const reskia_pdf_date_time_t &src, SkPDF::DateTime *dst) {
    dst->fTimeZoneMinutes = src.timezone_minutes;
    dst->fYear = src.year;
    dst->fMonth = src.month;
    dst->fDayOfWeek = src.day_of_week;
    dst->fDay = src.day;
    dst->fHour = src.hour;
    dst->fMinute = src.minute;
    dst->fSecond = src.second;
}

static SkPDF::Metadata to_sk_pdf_metadata(const reskia_pdf_metadata_t *src) {
    SkPDF::Metadata metadata;
    if (src == nullptr) {
        return metadata;
    }

    if (src->title != nullptr) {
        metadata.fTitle = src->title;
    }
    if (src->author != nullptr) {
        metadata.fAuthor = src->author;
    }
    if (src->subject != nullptr) {
        metadata.fSubject = src->subject;
    }
    if (src->keywords != nullptr) {
        metadata.fKeywords = src->keywords;
    }
    if (src->creator != nullptr) {
        metadata.fCreator = src->creator;
    }
    if (src->producer != nullptr) {
        metadata.fProducer = src->producer;
    }
    if (src->has_creation) {
        fill_pdf_datetime(src->creation, &metadata.fCreation);
    }
    if (src->has_modified) {
        fill_pdf_datetime(src->modified, &metadata.fModified);
    }
    if (src->raster_dpi > 0.0f) {
        metadata.fRasterDPI = src->raster_dpi;
    }
    metadata.fPDFA = src->pdfa;
    metadata.fEncodingQuality = src->encoding_quality;

    switch (src->outline) {
        case RESKIA_PDF_OUTLINE_STRUCTURE_ELEMENT_HEADERS:
            metadata.fOutline = SkPDF::Metadata::Outline::StructureElementHeaders;
            break;
        case RESKIA_PDF_OUTLINE_NONE:
        default:
            metadata.fOutline = SkPDF::Metadata::Outline::None;
            break;
    }

    switch (src->compression_level) {
        case RESKIA_PDF_COMPRESSION_NONE:
            metadata.fCompressionLevel = SkPDF::Metadata::CompressionLevel::None;
            break;
        case RESKIA_PDF_COMPRESSION_LOW_BUT_FAST:
            metadata.fCompressionLevel = SkPDF::Metadata::CompressionLevel::LowButFast;
            break;
        case RESKIA_PDF_COMPRESSION_AVERAGE:
            metadata.fCompressionLevel = SkPDF::Metadata::CompressionLevel::Average;
            break;
        case RESKIA_PDF_COMPRESSION_HIGH_BUT_SLOW:
            metadata.fCompressionLevel = SkPDF::Metadata::CompressionLevel::HighButSlow;
            break;
        case RESKIA_PDF_COMPRESSION_DEFAULT:
        default:
            metadata.fCompressionLevel = SkPDF::Metadata::CompressionLevel::Default;
            break;
    }

    switch (src->subsetter) {
        case RESKIA_PDF_SUBSETTER_SFNTLY:
            metadata.fSubsetter = SkPDF::Metadata::kSfntly_Subsetter;
            break;
        case RESKIA_PDF_SUBSETTER_HARFBUZZ:
        default:
            metadata.fSubsetter = SkPDF::Metadata::kHarfbuzz_Subsetter;
            break;
    }

    return metadata;
}

extern "C" {

void SkPDF_SetNodeId(reskia_canvas_t *dst, int nodeID) {
    if (dst == nullptr) {
        return;
    }
    SkPDF::SetNodeId(reinterpret_cast<SkCanvas *>(dst), nodeID);
}

sk_document_t SkPDF_MakeDocument(reskia_w_stream_t *stream, const reskia_pdf_metadata_t *metadata) {
    if (stream == nullptr) {
        return 0;
    }
    if (metadata == nullptr) {
        return static_sk_document_make(SkPDF::MakeDocument(reinterpret_cast<SkWStream *>(stream)));
    }
    return static_sk_document_make(SkPDF::MakeDocument(reinterpret_cast<SkWStream *>(stream), to_sk_pdf_metadata(metadata)));
}

sk_document_t SkPDF_MakeDocumentWithoutMetadata(reskia_w_stream_t *stream) {
    if (stream == nullptr) {
        return 0;
    }
    return static_sk_document_make(SkPDF::MakeDocument(reinterpret_cast<SkWStream *>(stream)));
}

reskia_pdf_attribute_list_t *AttributeList_new(void) {
    return reinterpret_cast<reskia_pdf_attribute_list_t *>(new SkPDF::AttributeList());
}

void AttributeList_delete(reskia_pdf_attribute_list_t *attributes) {
    delete reinterpret_cast<SkPDF::AttributeList *>(attributes);
}

void AttributeList_appendInt(reskia_pdf_attribute_list_t *attributes, const char owner[], const char name[], int value) {
    if (attributes == nullptr || owner == nullptr || name == nullptr) {
        return;
    }
    reinterpret_cast<SkPDF::AttributeList *>(attributes)->appendInt(owner, name, value);
}

void AttributeList_appendFloat(reskia_pdf_attribute_list_t *attributes, const char owner[], const char name[], float value) {
    if (attributes == nullptr || owner == nullptr || name == nullptr) {
        return;
    }
    reinterpret_cast<SkPDF::AttributeList *>(attributes)->appendFloat(owner, name, value);
}

void AttributeList_appendName(reskia_pdf_attribute_list_t *attributes, const char owner[], const char attrName[], const char value[]) {
    if (attributes == nullptr || owner == nullptr || attrName == nullptr || value == nullptr) {
        return;
    }
    reinterpret_cast<SkPDF::AttributeList *>(attributes)->appendName(owner, attrName, value);
}

void AttributeList_appendFloatArray(reskia_pdf_attribute_list_t *attributes, const char owner[], const char name[], const float values[], size_t count) {
    if (attributes == nullptr || owner == nullptr || name == nullptr || (values == nullptr && count > 0)) {
        return;
    }
    std::vector<float> native_values(values, values + count);
    reinterpret_cast<SkPDF::AttributeList *>(attributes)->appendFloatArray(owner, name, native_values);
}

void AttributeList_appendNodeIdArray(reskia_pdf_attribute_list_t *attributes, const char owner[], const char attrName[], const int nodeIds[], size_t count) {
    if (attributes == nullptr || owner == nullptr || attrName == nullptr || (nodeIds == nullptr && count > 0)) {
        return;
    }
    std::vector<int> native_node_ids(nodeIds, nodeIds + count);
    reinterpret_cast<SkPDF::AttributeList *>(attributes)->appendNodeIdArray(owner, attrName, native_node_ids);
}

void DateTime_toISO8601(const reskia_pdf_date_time_t *date_time, reskia_string_t *dst) {
    if (date_time == nullptr || dst == nullptr) {
        return;
    }
    SkPDF::DateTime native_date_time;
    fill_pdf_datetime(*date_time, &native_date_time);
    native_date_time.toISO8601(reinterpret_cast<SkString *>(dst));
}

}
