#include "sk_parse.h"

#include "include/utils/SkParse.h"

extern "C" {

int SkParse_Count(const char str[]) {
    return str != nullptr ? SkParse::Count(str) : 0;
}

int SkParse_CountWithSeparator(const char str[], char separator) {
    return str != nullptr ? SkParse::Count(str, separator) : 0;
}

const char *SkParse_FindColor(const char str[], uint32_t *value) {
    if (str == nullptr || value == nullptr) {
        return nullptr;
    }
    return SkParse::FindColor(str, value);
}

const char *SkParse_FindHex(const char str[], uint32_t *value) {
    if (str == nullptr || value == nullptr) {
        return nullptr;
    }
    return SkParse::FindHex(str, value);
}

const char *SkParse_FindMSec(const char str[], uint32_t *value) {
    if (str == nullptr || value == nullptr) {
        return nullptr;
    }
    return SkParse::FindMSec(str, value);
}

const char *SkParse_FindNamedColor(const char str[], size_t len, uint32_t *color) {
    if (str == nullptr || color == nullptr) {
        return nullptr;
    }
    return SkParse::FindNamedColor(str, len, color);
}

const char *SkParse_FindS32(const char str[], int32_t *value) {
    if (str == nullptr || value == nullptr) {
        return nullptr;
    }
    return SkParse::FindS32(str, value);
}

const char *SkParse_FindScalar(const char str[], float *value) {
    if (str == nullptr || value == nullptr) {
        return nullptr;
    }
    return SkParse::FindScalar(str, value);
}

const char *SkParse_FindScalars(const char str[], float value[], int count) {
    if (str == nullptr || count < 0 || (count > 0 && value == nullptr)) {
        return nullptr;
    }
    return SkParse::FindScalars(str, value, count);
}

bool SkParse_FindBool(const char str[], bool *value) {
    if (str == nullptr || value == nullptr) {
        return false;
    }
    return SkParse::FindBool(str, value);
}

int SkParse_FindList(const char str[], const char list[]) {
    if (str == nullptr || list == nullptr) {
        return -1;
    }
    return SkParse::FindList(str, list);
}

} // extern "C"
