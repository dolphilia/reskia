#include <cstdio>
#include <cstring>

#include "capi/sk_parse.h"
#include "capi/sk_parse_path.h"
#include "capi/sk_path.h"
#include "capi/sk_string.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[parse-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_parse() {
    if (!check(SkParse_Count(nullptr) == 0, "SkParse_Count null")) {
        return false;
    }
    if (!check(SkParse_Count("1, 2, 3") == 3, "SkParse_Count")) {
        return false;
    }
    if (!check(SkParse_CountWithSeparator("a|b|c", '|') == 3, "SkParse_CountWithSeparator")) {
        return false;
    }

    uint32_t color = 0;
    color = 0xff000000;
    if (!check(SkParse_FindColor("#112233", &color) != nullptr && color == 0xff112233,
               "SkParse_FindColor")) {
        return false;
    }
    if (!check(SkParse_FindNamedColor("red", 3, &color) != nullptr && color == 0xffff0000,
               "SkParse_FindNamedColor")) {
        return false;
    }

    uint32_t hex = 0;
    if (!check(SkParse_FindHex("1a", &hex) != nullptr && hex == 0x1a,
               "SkParse_FindHex")) {
        return false;
    }
    int32_t s32 = 0;
    if (!check(SkParse_FindS32("-42", &s32) != nullptr && s32 == -42,
               "SkParse_FindS32")) {
        return false;
    }
    float scalar = 0.0f;
    if (!check(SkParse_FindScalar("3.5", &scalar) != nullptr && scalar == 3.5f,
               "SkParse_FindScalar")) {
        return false;
    }
    float scalars[3] = {0.0f, 0.0f, 0.0f};
    if (!check(SkParse_FindScalars("1 2 3", scalars, 3) != nullptr &&
               scalars[0] == 1.0f &&
               scalars[1] == 2.0f &&
               scalars[2] == 3.0f,
               "SkParse_FindScalars")) {
        return false;
    }
    bool value = false;
    if (!check(SkParse_FindBool("true", &value) && value, "SkParse_FindBool")) {
        return false;
    }
    if (!check(SkParse_FindList("beta", "alpha,beta,gamma") == 1, "SkParse_FindList")) {
        return false;
    }
    if (!check(SkParse_FindScalar(nullptr, &scalar) == nullptr &&
               !SkParse_FindBool("true", nullptr) &&
               SkParse_FindList(nullptr, "x") == -1,
               "SkParse invalid input")) {
        return false;
    }
    return true;
}

bool smoke_parse_path() {
    reskia_path_t *path = SkPath_new();
    if (!check(path != nullptr, "SkPath_new")) {
        return false;
    }
    if (!check(!SkParsePath_FromSVGString(nullptr, path), "SkParsePath_FromSVGString null str")) {
        SkPath_delete(path);
        return false;
    }
    if (!check(SkParsePath_FromSVGString("M 0 0 L 10 0 L 10 10 Z", path),
               "SkParsePath_FromSVGString")) {
        SkPath_delete(path);
        return false;
    }
    if (!check(SkPath_countVerbs(path) > 0, "SkParsePath path verbs")) {
        SkPath_delete(path);
        return false;
    }
    reskia_string_t *svg = SkParsePath_ToSVGString(path, 0);
    if (!check(svg != nullptr && SkString_size(svg) > 0, "SkParsePath_ToSVGString")) {
        SkString_delete(svg);
        SkPath_delete(path);
        return false;
    }
    const char *svg_text = SkString_c_str(svg);
    if (!check(svg_text != nullptr && std::strstr(svg_text, "M") != nullptr,
               "SkParsePath_ToSVGString content")) {
        SkString_delete(svg);
        SkPath_delete(path);
        return false;
    }
    SkString_delete(svg);
    if (!check(SkParsePath_ToSVGString(nullptr, 0) == nullptr, "SkParsePath_ToSVGString null path")) {
        SkPath_delete(path);
        return false;
    }
    SkPath_delete(path);
    return true;
}

}  // namespace

int main() {
    if (!smoke_parse()) {
        return 1;
    }
    if (!smoke_parse_path()) {
        return 1;
    }
    std::fprintf(stdout, "[parse-utils-smoke] PASS\n");
    return 0;
}
