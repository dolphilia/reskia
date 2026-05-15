#include "sk_parse_path.h"

#include "include/core/SkPath.h"
#include "include/core/SkString.h"
#include "include/utils/SkParsePath.h"

extern "C" {

bool SkParsePath_FromSVGString(const char str[], reskia_path_t *path) {
    if (str == nullptr || path == nullptr) {
        return false;
    }
    return SkParsePath::FromSVGString(str, reinterpret_cast<SkPath *>(path));
}

reskia_string_t *SkParsePath_ToSVGString(const reskia_path_t *path, reskia_parse_path_encoding_t encoding) {
    if (path == nullptr) {
        return nullptr;
    }
    SkString svg = SkParsePath::ToSVGString(
            *reinterpret_cast<const SkPath *>(path),
            static_cast<SkParsePath::PathEncoding>(encoding));
    return reinterpret_cast<reskia_string_t *>(new SkString(svg));
}

} // extern "C"
