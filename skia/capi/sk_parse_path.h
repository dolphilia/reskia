#ifndef RAIA_SKIA_SK_PARSE_PATH_H
#define RAIA_SKIA_SK_PARSE_PATH_H

#include <stdbool.h>
#include <stdint.h>

typedef struct reskia_path_t reskia_path_t;
typedef struct reskia_string_t reskia_string_t;
typedef int32_t reskia_parse_path_encoding_t;

#ifdef __cplusplus
extern "C" {
#endif

bool SkParsePath_FromSVGString(const char str[], reskia_path_t *path);
reskia_string_t *SkParsePath_ToSVGString(const reskia_path_t *path, reskia_parse_path_encoding_t encoding);

#ifdef __cplusplus
}
#endif

#endif // RAIA_SKIA_SK_PARSE_PATH_H
