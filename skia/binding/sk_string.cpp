//
// Created by dolphilia on 2024/01/11.
//

#include "sk_string.h"

#include "include/core/SkString.h"

#include "../static/static_std_string_view.h"

#include "../static/static_std_string_view-internal.h"

extern "C" {

// SkString & operator=(const SkString &)
// SkString & operator=(SkString &&)
// SkString & operator=(const char text[])
// SkString & operator+=(const SkString &s)
// SkString & operator+=(const char text[])
// SkString & operator+=(const char c)
// char operator[](size_t n)
// char & operator[](size_t n)

void *SkString_new() {
    return new SkString();
}

void *SkString_new_2(size_t len) {
    return new SkString(len);
}

void *SkString_new_3(const char text[]) {
    return new SkString(text);
}

void *SkString_new_4(const char text[], size_t len) {
    return new SkString(text, len);
}

void *SkString_new_5(const void *str) {
    return new SkString(* static_cast<const SkString *>(str));
}

void *SkString_new_6(const void *str) {
    return new SkString(* static_cast<const std::string *>(str));
}

void *SkString_new_7(string_view_t view) {
    return new SkString(static_string_view_get_entity(view));
}

void SkString_delete(void *string) {
    delete static_cast<SkString *>(string);
}
bool SkString_isEmpty(void *string) {
    return static_cast<SkString *>(string)->isEmpty();
}

size_t SkString_size(void *string) {
    return static_cast<SkString *>(string)->size();
}

const char * SkString_data(void *string) {
    return static_cast<SkString *>(string)->data();
}

char * SkString_data_2(void *string) {
    return static_cast<SkString *>(string)->data();
}

const char * SkString_c_str(void *string) {
    return static_cast<SkString *>(string)->c_str();
}

bool SkString_equals(void *string, const void *str) {
    return static_cast<SkString *>(string)->equals(* static_cast<const SkString *>(str));
}

bool SkString_equals_2(void *string, const char text[]) {
    return static_cast<SkString *>(string)->equals(text);
}

bool SkString_equals_3(void *string, const char text[], size_t len) {
    return static_cast<SkString *>(string)->equals(text, len);
}

bool SkString_startsWith(void *string, const char prefixStr[]) {
    return static_cast<SkString *>(string)->startsWith(prefixStr);
}

bool SkString_startsWith_2(void *string, const char prefixChar) {
    return static_cast<SkString *>(string)->startsWith(prefixChar);
}

//bool SkString_endsWith(SkString *string, const char suffixStr[]) {
//    return string->endsWith(suffixStr);
//}

//bool SkString_endsWith_2(SkString *string, const char suffixChar) {
//    return string->endsWith(suffixChar);
//}

bool SkString_contains(void *string, const char substring[]) {
    return static_cast<SkString *>(string)->contains(substring);
}

bool SkString_contains_2(void *string, const char subchar) {
    return static_cast<SkString *>(string)->contains(subchar);
}

int SkString_find(void *string, const char substring[]) {
    return static_cast<SkString *>(string)->find(substring);
}

int SkString_findLastOf(void *string, const char subchar) {
    return static_cast<SkString *>(string)->findLastOf(subchar);
}

void SkString_reset(void *string) {
    static_cast<SkString *>(string)->reset();
}

void SkString_resize(void *string, size_t len) {
    static_cast<SkString *>(string)->resize(len);
}

void SkString_set(void *string, const void *src) {
    static_cast<SkString *>(string)->set(* static_cast<const SkString *>(src));
}

void SkString_set_2(void *string, const char text[]) {
    static_cast<SkString *>(string)->set(text);
}

void SkString_set_3(void *string, const char text[], size_t len) {
    static_cast<SkString *>(string)->set(text, len);
}

void SkString_set_4(void *string, string_view_t str) {
    static_cast<SkString *>(string)->set(static_string_view_get_entity(str));
}

void SkString_insert(void *string, size_t offset, const char text[]) {
    static_cast<SkString *>(string)->insert(offset, text);
}

void SkString_insert_2(void *string, size_t offset, const char text[], size_t len) {
    static_cast<SkString *>(string)->insert(offset, text, len);
}

void SkString_insert_3(void *string, size_t offset, const void *str) {
    static_cast<SkString *>(string)->insert(offset, * static_cast<const SkString *>(str));
}

void SkString_insert_4(void *string, size_t offset, string_view_t str) {
    static_cast<SkString *>(string)->insert(offset, static_string_view_get_entity(str));
}

void SkString_insertUnichar(void *string, size_t offset, int unichar) {
    static_cast<SkString *>(string)->insertUnichar(offset, unichar);
}

void SkString_insertS32(void *string, size_t offset, int32_t value) {
    static_cast<SkString *>(string)->insertS32(offset, value);
}

void SkString_insertS64(void *string, size_t offset, int64_t value, int minDigits) {
    static_cast<SkString *>(string)->insertS64(offset, value, minDigits);
}

void SkString_insertU32(void *string, size_t offset, uint32_t value) {
    static_cast<SkString *>(string)->insertU32(offset, value);
}

void SkString_insertU64(void *string, size_t offset, uint64_t value, int minDigits) {
    static_cast<SkString *>(string)->insertU64(offset, value, minDigits);
}

void SkString_insertHex(void *string, size_t offset, uint32_t value, int minDigits) {
    static_cast<SkString *>(string)->insertHex(offset, value, minDigits);
}

void SkString_insertScalar(void *string, size_t offset, float v) {
    static_cast<SkString *>(string)->insertScalar(offset, v);
}

void SkString_append(void *string, const char text[]) {
    static_cast<SkString *>(string)->append(text);
}

void SkString_append_2(void *string, const char text[], size_t len) {
    static_cast<SkString *>(string)->append(text, len);
}

void SkString_append_3(void *string, const void *str) {
    static_cast<SkString *>(string)->append(* static_cast<const SkString *>(str));
}

void SkString_append_4(void *string, string_view_t str) {
    static_cast<SkString *>(string)->append(static_string_view_get_entity(str));
}

void SkString_appendUnichar(void *string, int uni) {
    static_cast<SkString *>(string)->appendUnichar(uni);
}

void SkString_appendS32(void *string, int32_t value) {
    static_cast<SkString *>(string)->appendS32(value);
}

void SkString_appendS64(void *string, int64_t value, int minDigits) {
    static_cast<SkString *>(string)->appendS64(value, minDigits);
}

void SkString_appendU32(void *string, uint32_t value) {
    static_cast<SkString *>(string)->appendU32(value);
}

void SkString_appendU64(void *string, uint64_t value, int minDigits) {
    static_cast<SkString *>(string)->appendU64(value, minDigits);
}

void SkString_appendHex(void *string, uint32_t value, int minDigits) {
    static_cast<SkString *>(string)->appendHex(value, minDigits);
}

void SkString_appendScalar(void *string, float value) {
    static_cast<SkString *>(string)->appendScalar(value);
}

void SkString_prepend(void *string, const char text[]) {
    static_cast<SkString *>(string)->prepend(text);
}

void SkString_prepend_2(void *string, const char text[], size_t len) {
    static_cast<SkString *>(string)->prepend(text, len);
}

void SkString_prepend_3(void *string, const void *str) {
    static_cast<SkString *>(string)->prepend(* static_cast<const SkString *>(str));
}

void SkString_prepend_4(void *string, string_view_t str) {
    static_cast<SkString *>(string)->prepend(static_string_view_get_entity(str));
}

void SkString_prependUnichar(void *string, int uni) {
    static_cast<SkString *>(string)->prependUnichar(uni);
}

void SkString_prependS32(void *string, int32_t value) {
    static_cast<SkString *>(string)->prependS32(value);
}

void SkString_prependS64(void *string, int32_t value, int minDigits) {
    static_cast<SkString *>(string)->prependS64(value, minDigits);
}

void SkString_prependHex(void *string, uint32_t value, int minDigits) {
    static_cast<SkString *>(string)->prependHex(value, minDigits);
}

void SkString_prependScalar(void *string, float value) {
    static_cast<SkString *>(string)->prependScalar(value);
}

void SkString_printf(void *string, const char format[], ...) {
    va_list args;
    va_start(args, format);
    static_cast<SkString*>(string)->printVAList(format, args);
    va_end(args);
}

void SkString_printVAList(void *string, const char format[], va_list args) {
    static_cast<SkString*>(string)->printVAList(format, args);
}

void SkString_appendf(void *string, const char format[], ...) {
    va_list args;
    va_start(args, format);
    static_cast<SkString*>(string)->appendVAList(format, args);
    va_end(args);
}

void SkString_appendVAList(void *string, const char format[], va_list args) {
    static_cast<SkString*>(string)->appendVAList(format, args);
}

void SkString_prependf(void *string, const char format[], ...) {
    va_list args;
    va_start(args, format);
    static_cast<SkString*>(string)->prependVAList(format, args);
    va_end(args);
}

void SkString_prependVAList(void *string, const char format[], va_list args) {
    static_cast<SkString*>(string)->prependVAList(format, args);
}

void SkString_remove(void *string, size_t offset, size_t length) {
    static_cast<SkString *>(string)->remove(offset, length);
}

void SkString_swap(void *string, void *other) {
    static_cast<SkString *>(string)->swap(* static_cast<SkString *>(other));
}

}
