//
// Created by dolphilia on 2024/01/11.
//

#include "sk_string.h"

#include "include/core/SkString.h"

#include "../handles/static_std_string_view.h"

#include "../handles/static_std_string_view-internal.h"

extern "C" {

// SkString & operator=(const SkString &)
// SkString & operator=(SkString &&)
// SkString & operator=(const char text[])
// SkString & operator+=(const SkString &s)
// SkString & operator+=(const char text[])
// SkString & operator+=(const char c)
// char operator[](size_t n)
// char & operator[](size_t n)

reskia_string_t *SkString_new() {
    return reinterpret_cast<reskia_string_t *>(new SkString());
}

reskia_string_t *SkString_newWithLength(size_t len) {
    return reinterpret_cast<reskia_string_t *>(new SkString(len));
}

reskia_string_t *SkString_newFromText(const char text[]) {
    return reinterpret_cast<reskia_string_t *>(new SkString(text));
}

reskia_string_t *SkString_newFromTextWithLength(const char text[], size_t len) {
    return reinterpret_cast<reskia_string_t *>(new SkString(text, len));
}

reskia_string_t *SkString_new_5(const reskia_string_t *str) {
    return reinterpret_cast<reskia_string_t *>(new SkString(* reinterpret_cast<const SkString *>(str)));
}

reskia_string_t *SkString_new_6(const reskia_std_string_t *str) {
    return reinterpret_cast<reskia_string_t *>(new SkString(* reinterpret_cast<const std::string *>(str)));
}

reskia_string_t *SkString_new_7(string_view_t view) {
    return reinterpret_cast<reskia_string_t *>(new SkString(static_string_view_get_entity(view)));
}

void SkString_delete(reskia_string_t *string) {
    delete reinterpret_cast<SkString *>(string);
}
bool SkString_isEmpty(reskia_string_t *string) {
    return reinterpret_cast<SkString *>(string)->isEmpty();
}

size_t SkString_size(reskia_string_t *string) {
    return reinterpret_cast<SkString *>(string)->size();
}

const char * SkString_data(reskia_string_t *string) {
    return reinterpret_cast<SkString *>(string)->data();
}

char * SkString_dataMutable(reskia_string_t *string) {
    return reinterpret_cast<SkString *>(string)->data();
}

const char * SkString_c_str(reskia_string_t *string) {
    return reinterpret_cast<SkString *>(string)->c_str();
}

bool SkString_equals(reskia_string_t *string, const reskia_string_t *str) {
    return reinterpret_cast<SkString *>(string)->equals(* reinterpret_cast<const SkString *>(str));
}

bool SkString_equalsText(reskia_string_t *string, const char text[]) {
    return reinterpret_cast<SkString *>(string)->equals(text);
}

bool SkString_equalsTextWithLength(reskia_string_t *string, const char text[], size_t len) {
    return reinterpret_cast<SkString *>(string)->equals(text, len);
}

bool SkString_startsWith(reskia_string_t *string, const char prefixStr[]) {
    return reinterpret_cast<SkString *>(string)->startsWith(prefixStr);
}

bool SkString_startsWithChar(reskia_string_t *string, const char prefixChar) {
    return reinterpret_cast<SkString *>(string)->startsWith(prefixChar);
}

//bool SkString_endsWith(SkString *string, const char suffixStr[]) {
//    return string->endsWith(suffixStr);
//}

//bool SkString_endsWith_2(SkString *string, const char suffixChar) {
//    return string->endsWith(suffixChar);
//}

bool SkString_contains(reskia_string_t *string, const char substring[]) {
    return reinterpret_cast<SkString *>(string)->contains(substring);
}

bool SkString_containsChar(reskia_string_t *string, const char subchar) {
    return reinterpret_cast<SkString *>(string)->contains(subchar);
}

int SkString_find(reskia_string_t *string, const char substring[]) {
    return reinterpret_cast<SkString *>(string)->find(substring);
}

int SkString_findLastOf(reskia_string_t *string, const char subchar) {
    return reinterpret_cast<SkString *>(string)->findLastOf(subchar);
}

void SkString_reset(reskia_string_t *string) {
    reinterpret_cast<SkString *>(string)->reset();
}

void SkString_resize(reskia_string_t *string, size_t len) {
    reinterpret_cast<SkString *>(string)->resize(len);
}

void SkString_set(reskia_string_t *string, const reskia_string_t *src) {
    reinterpret_cast<SkString *>(string)->set(* reinterpret_cast<const SkString *>(src));
}

void SkString_setText(reskia_string_t *string, const char text[]) {
    reinterpret_cast<SkString *>(string)->set(text);
}

void SkString_setTextWithLength(reskia_string_t *string, const char text[], size_t len) {
    reinterpret_cast<SkString *>(string)->set(text, len);
}

void SkString_setStringView(reskia_string_t *string, string_view_t str) {
    reinterpret_cast<SkString *>(string)->set(static_string_view_get_entity(str));
}

void SkString_insert(reskia_string_t *string, size_t offset, const char text[]) {
    reinterpret_cast<SkString *>(string)->insert(offset, text);
}

void SkString_insertTextWithLength(reskia_string_t *string, size_t offset, const char text[], size_t len) {
    reinterpret_cast<SkString *>(string)->insert(offset, text, len);
}

void SkString_insertString(reskia_string_t *string, size_t offset, const reskia_string_t *str) {
    reinterpret_cast<SkString *>(string)->insert(offset, * reinterpret_cast<const SkString *>(str));
}

void SkString_insertStringView(reskia_string_t *string, size_t offset, string_view_t str) {
    reinterpret_cast<SkString *>(string)->insert(offset, static_string_view_get_entity(str));
}

void SkString_insertUnichar(reskia_string_t *string, size_t offset, reskia_string_unichar_t unichar) {
    reinterpret_cast<SkString *>(string)->insertUnichar(offset, unichar);
}

void SkString_insertS32(reskia_string_t *string, size_t offset, int32_t value) {
    reinterpret_cast<SkString *>(string)->insertS32(offset, value);
}

void SkString_insertS64(reskia_string_t *string, size_t offset, int64_t value, int minDigits) {
    reinterpret_cast<SkString *>(string)->insertS64(offset, value, minDigits);
}

void SkString_insertU32(reskia_string_t *string, size_t offset, uint32_t value) {
    reinterpret_cast<SkString *>(string)->insertU32(offset, value);
}

void SkString_insertU64(reskia_string_t *string, size_t offset, uint64_t value, int minDigits) {
    reinterpret_cast<SkString *>(string)->insertU64(offset, value, minDigits);
}

void SkString_insertHex(reskia_string_t *string, size_t offset, uint32_t value, int minDigits) {
    reinterpret_cast<SkString *>(string)->insertHex(offset, value, minDigits);
}

void SkString_insertScalar(reskia_string_t *string, size_t offset, float v) {
    reinterpret_cast<SkString *>(string)->insertScalar(offset, v);
}

void SkString_append(reskia_string_t *string, const char text[]) {
    reinterpret_cast<SkString *>(string)->append(text);
}

void SkString_appendTextWithLength(reskia_string_t *string, const char text[], size_t len) {
    reinterpret_cast<SkString *>(string)->append(text, len);
}

void SkString_appendString(reskia_string_t *string, const reskia_string_t *str) {
    reinterpret_cast<SkString *>(string)->append(* reinterpret_cast<const SkString *>(str));
}

void SkString_appendStringView(reskia_string_t *string, string_view_t str) {
    reinterpret_cast<SkString *>(string)->append(static_string_view_get_entity(str));
}

void SkString_appendUnichar(reskia_string_t *string, reskia_string_unichar_t uni) {
    reinterpret_cast<SkString *>(string)->appendUnichar(uni);
}

void SkString_appendS32(reskia_string_t *string, int32_t value) {
    reinterpret_cast<SkString *>(string)->appendS32(value);
}

void SkString_appendS64(reskia_string_t *string, int64_t value, int minDigits) {
    reinterpret_cast<SkString *>(string)->appendS64(value, minDigits);
}

void SkString_appendU32(reskia_string_t *string, uint32_t value) {
    reinterpret_cast<SkString *>(string)->appendU32(value);
}

void SkString_appendU64(reskia_string_t *string, uint64_t value, int minDigits) {
    reinterpret_cast<SkString *>(string)->appendU64(value, minDigits);
}

void SkString_appendHex(reskia_string_t *string, uint32_t value, int minDigits) {
    reinterpret_cast<SkString *>(string)->appendHex(value, minDigits);
}

void SkString_appendScalar(reskia_string_t *string, float value) {
    reinterpret_cast<SkString *>(string)->appendScalar(value);
}

void SkString_prepend(reskia_string_t *string, const char text[]) {
    reinterpret_cast<SkString *>(string)->prepend(text);
}

void SkString_prependTextWithLength(reskia_string_t *string, const char text[], size_t len) {
    reinterpret_cast<SkString *>(string)->prepend(text, len);
}

void SkString_prependString(reskia_string_t *string, const reskia_string_t *str) {
    reinterpret_cast<SkString *>(string)->prepend(* reinterpret_cast<const SkString *>(str));
}

void SkString_prependStringView(reskia_string_t *string, string_view_t str) {
    reinterpret_cast<SkString *>(string)->prepend(static_string_view_get_entity(str));
}

void SkString_prependUnichar(reskia_string_t *string, reskia_string_unichar_t uni) {
    reinterpret_cast<SkString *>(string)->prependUnichar(uni);
}

void SkString_prependS32(reskia_string_t *string, int32_t value) {
    reinterpret_cast<SkString *>(string)->prependS32(value);
}

void SkString_prependS64(reskia_string_t *string, int32_t value, int minDigits) {
    reinterpret_cast<SkString *>(string)->prependS64(value, minDigits);
}

void SkString_prependHex(reskia_string_t *string, uint32_t value, int minDigits) {
    reinterpret_cast<SkString *>(string)->prependHex(value, minDigits);
}

void SkString_prependScalar(reskia_string_t *string, float value) {
    reinterpret_cast<SkString *>(string)->prependScalar(value);
}

void SkString_printf(reskia_string_t *string, const char format[], ...) {
    va_list args;
    va_start(args, format);
    reinterpret_cast<SkString *>(string)->printVAList(format, args);
    va_end(args);
}

void SkString_printVAList(reskia_string_t *string, const char format[], va_list args) {
    reinterpret_cast<SkString *>(string)->printVAList(format, args);
}

void SkString_appendf(reskia_string_t *string, const char format[], ...) {
    va_list args;
    va_start(args, format);
    reinterpret_cast<SkString *>(string)->appendVAList(format, args);
    va_end(args);
}

void SkString_appendVAList(reskia_string_t *string, const char format[], va_list args) {
    reinterpret_cast<SkString *>(string)->appendVAList(format, args);
}

void SkString_prependf(reskia_string_t *string, const char format[], ...) {
    va_list args;
    va_start(args, format);
    reinterpret_cast<SkString *>(string)->prependVAList(format, args);
    va_end(args);
}

void SkString_prependVAList(reskia_string_t *string, const char format[], va_list args) {
    reinterpret_cast<SkString *>(string)->prependVAList(format, args);
}

void SkString_remove(reskia_string_t *string, size_t offset, size_t length) {
    reinterpret_cast<SkString *>(string)->remove(offset, length);
}

void SkString_swap(reskia_string_t *string, reskia_string_t *other) {
    reinterpret_cast<SkString *>(string)->swap(* reinterpret_cast<SkString *>(other));
}

}
