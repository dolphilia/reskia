//
// Created by dolphilia on 2024/01/13.
//

#ifndef RAIA_SKIA_SK_PDF_H
#define RAIA_SKIA_SK_PDF_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../handles/static_sk_document.h"

typedef struct reskia_canvas_t reskia_canvas_t;
typedef struct reskia_pdf_attribute_list_t reskia_pdf_attribute_list_t;
typedef struct reskia_string_t reskia_string_t;
typedef struct reskia_w_stream_t reskia_w_stream_t;

typedef struct reskia_pdf_date_time_t {
    int16_t timezone_minutes;
    uint16_t year;
    uint8_t month;
    uint8_t day_of_week;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
} reskia_pdf_date_time_t;

typedef enum reskia_pdf_outline_t {
    RESKIA_PDF_OUTLINE_NONE = 0,
    RESKIA_PDF_OUTLINE_STRUCTURE_ELEMENT_HEADERS = 1,
} reskia_pdf_outline_t;

typedef enum reskia_pdf_compression_level_t {
    RESKIA_PDF_COMPRESSION_DEFAULT = -1,
    RESKIA_PDF_COMPRESSION_NONE = 0,
    RESKIA_PDF_COMPRESSION_LOW_BUT_FAST = 1,
    RESKIA_PDF_COMPRESSION_AVERAGE = 6,
    RESKIA_PDF_COMPRESSION_HIGH_BUT_SLOW = 9,
} reskia_pdf_compression_level_t;

typedef enum reskia_pdf_subsetter_t {
    RESKIA_PDF_SUBSETTER_HARFBUZZ = 0,
    RESKIA_PDF_SUBSETTER_SFNTLY = 1,
} reskia_pdf_subsetter_t;

typedef struct reskia_pdf_metadata_t {
    const char *title;
    const char *author;
    const char *subject;
    const char *keywords;
    const char *creator;
    const char *producer;
    reskia_pdf_date_time_t creation;
    bool has_creation;
    reskia_pdf_date_time_t modified;
    bool has_modified;
    float raster_dpi;
    bool pdfa;
    int32_t encoding_quality;
    int32_t outline;
    int32_t compression_level;
    int32_t subsetter;
} reskia_pdf_metadata_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkPDF_SetNodeId(reskia_canvas_t *dst, int nodeID); // NULL canvas is no-op.
sk_document_t SkPDF_MakeDocument(reskia_w_stream_t *stream, const reskia_pdf_metadata_t *metadata); // stream required; metadata may be NULL; invalid/failure returns 0.
sk_document_t SkPDF_MakeDocumentWithoutMetadata(reskia_w_stream_t *stream); // stream required; invalid/failure returns 0.
reskia_pdf_attribute_list_t *AttributeList_new(void);
void AttributeList_delete(reskia_pdf_attribute_list_t *attributes);
void AttributeList_appendInt(reskia_pdf_attribute_list_t *attributes, const char owner[], const char name[], int value);
void AttributeList_appendFloat(reskia_pdf_attribute_list_t *attributes, const char owner[], const char name[], float value);
void AttributeList_appendName(reskia_pdf_attribute_list_t *attributes, const char owner[], const char attrName[], const char value[]);
void AttributeList_appendFloatArray(reskia_pdf_attribute_list_t *attributes, const char owner[], const char name[], const float values[], size_t count);
void AttributeList_appendNodeIdArray(reskia_pdf_attribute_list_t *attributes, const char owner[], const char attrName[], const int nodeIds[], size_t count);
void DateTime_toISO8601(const reskia_pdf_date_time_t *date_time, reskia_string_t *dst);

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_PDF_H
