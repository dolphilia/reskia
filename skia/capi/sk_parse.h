#ifndef RAIA_SKIA_SK_PARSE_H
#define RAIA_SKIA_SK_PARSE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int SkParse_Count(const char str[]);
int SkParse_CountWithSeparator(const char str[], char separator);
const char *SkParse_FindColor(const char str[], uint32_t *value);
const char *SkParse_FindHex(const char str[], uint32_t *value);
const char *SkParse_FindNamedColor(const char str[], size_t len, uint32_t *color);
const char *SkParse_FindS32(const char str[], int32_t *value);
const char *SkParse_FindScalar(const char str[], float *value);
const char *SkParse_FindScalars(const char str[], float value[], int count);
bool SkParse_FindBool(const char str[], bool *value);
int SkParse_FindList(const char str[], const char list[]);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PARSE_H
