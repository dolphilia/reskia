//
// Created by dolphilia on 2024/01/13.
//

#include "sk_pdf.h"

#include "include/docs/SkPDFDocument.h"
#include "../handles/static_sk_document-internal.h"

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
    SkPDF::SetNodeId(reinterpret_cast<SkCanvas *>(dst), nodeID);
}

sk_document_t SkPDF_MakeDocument(reskia_w_stream_t *stream, const reskia_pdf_metadata_t *metadata) {
    if (metadata == nullptr) {
        return static_sk_document_make(SkPDF::MakeDocument(reinterpret_cast<SkWStream *>(stream)));
    }
    return static_sk_document_make(SkPDF::MakeDocument(reinterpret_cast<SkWStream *>(stream), to_sk_pdf_metadata(metadata)));
}

sk_document_t SkPDF_MakeDocumentWithoutMetadata(reskia_w_stream_t *stream) {
    return static_sk_document_make(SkPDF::MakeDocument(reinterpret_cast<SkWStream *>(stream)));
}

}
