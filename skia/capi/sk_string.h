//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_STRING_H
#define RAIA_SKIA_SK_STRING_H

#include <stddef.h>
#include <stdint.h>

typedef struct reskia_string_t reskia_string_t;
typedef struct reskia_std_string_t reskia_std_string_t;
typedef int32_t reskia_string_unichar_t;

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

// SkString & operator=(const SkString &)
// SkString & operator=(SkString &&)
// SkString & operator=(const char text[])
// SkString & operator+=(const SkString &s)
// SkString & operator+=(const char text[])
// SkString & operator+=(const char c)
// char operator[](size_t n)
// char & operator[](size_t n)

reskia_string_t *SkString_new(); // () -> SkString *
reskia_string_t *SkString_newWithLength(size_t len); // (size_t len) -> SkString *
reskia_string_t *SkString_newFromText(const char text[]); // (const char text[]) -> SkString *
reskia_string_t *SkString_newFromTextWithLength(const char text[], size_t len); // (const char text[], size_t len) -> SkString *
reskia_string_t *SkString_new_5(const reskia_string_t *str); // (const SkString *str) -> SkString *
reskia_string_t *SkString_new_6(const reskia_std_string_t *str); // (const std::string *str) -> SkString *
reskia_string_t *SkString_new_7(int view); // (string_view_t view) -> SkString *
void SkString_delete(reskia_string_t *string); // (SkString *string)
bool SkString_isEmpty(reskia_string_t *string); // (SkString *string) -> bool
size_t SkString_size(reskia_string_t *string); // (SkString *string) -> size_t
const char * SkString_data(reskia_string_t *string); // (SkString *string) -> const char *
char * SkString_dataMutable(reskia_string_t *string); // (SkString *string) -> char *
const char * SkString_c_str(reskia_string_t *string); // (SkString *string) -> const char *
bool SkString_equals(reskia_string_t *string, const reskia_string_t *str); // (SkString *string, const SkString *str) -> bool
bool SkString_equalsText(reskia_string_t *string, const char text[]); // (SkString *string, const char text[]) -> bool
bool SkString_equalsTextWithLength(reskia_string_t *string, const char text[], size_t len); // (SkString *string, const char text[], size_t len) -> bool
bool SkString_startsWith(reskia_string_t *string, const char prefixStr[]); // (SkString *string, const char prefixStr[]) -> bool
bool SkString_startsWithChar(reskia_string_t *string, char prefixChar); // (SkString *string, char prefixChar) -> bool

//bool SkString_endsWith(SkString *string, const char suffixStr[]);
//bool SkString_endsWith_2(SkString *string, const char suffixChar);

bool SkString_contains(reskia_string_t *string, const char substring[]); // (SkString *string, const char substring[]) -> bool
bool SkString_containsChar(reskia_string_t *string, char subchar); // (SkString *string, char subchar) -> bool
int SkString_find(reskia_string_t *string, const char substring[]); // (SkString *string, const char substring[]) -> int
int SkString_findLastOf(reskia_string_t *string, char subchar); // (SkString *string, char subchar) -> int
void SkString_reset(reskia_string_t *string); // (SkString *string)
void SkString_resize(reskia_string_t *string, size_t len); // (SkString *string, size_t len)
void SkString_set(reskia_string_t *string, const reskia_string_t *src); // (SkString *string, const SkString *src)
void SkString_setText(reskia_string_t *string, const char text[]); // (SkString *string, const char text[])
void SkString_setTextWithLength(reskia_string_t *string, const char text[], size_t len); // (SkString *string, const char text[], size_t len)
void SkString_setStringView(reskia_string_t *string, int str); // (SkString *string, string_view_t str)
void SkString_insert(reskia_string_t *string, size_t offset, const char text[]); // (SkString *string, size_t offset, const char text[])
void SkString_insertTextWithLength(reskia_string_t *string, size_t offset, const char text[], size_t len); // (SkString *string, size_t offset, const char text[], size_t len)
void SkString_insertString(reskia_string_t *string, size_t offset, const reskia_string_t *str); // (SkString *string, size_t offset, const SkString *str)
void SkString_insertStringView(reskia_string_t *string, size_t offset, int str); // (SkString *string, size_t offset, string_view_t str)
void SkString_insertUnichar(reskia_string_t *string, size_t offset, reskia_string_unichar_t unichar); // (SkString *string, size_t offset, SkUnichar unichar)
void SkString_insertS32(reskia_string_t *string, size_t offset, int value); // (SkString *string, size_t offset, int32_t value)
void SkString_insertS64(reskia_string_t *string, size_t offset, long long value, int minDigits); // (SkString *string, size_t offset, int64_t value, int minDigits)
void SkString_insertU32(reskia_string_t *string, size_t offset, uint32_t value); // (SkString *string, size_t offset, uint32_t value)
void SkString_insertU64(reskia_string_t *string, size_t offset, uint64_t value, int minDigits); // (SkString *string, size_t offset, uint64_t value, int minDigits)
void SkString_insertHex(reskia_string_t *string, size_t offset, uint32_t value, int minDigits); // (SkString *string, size_t offset, uint32_t value, int minDigits)
void SkString_insertScalar(reskia_string_t *string, size_t offset, float v); // (SkString *string, size_t offset, SkScalar v)
void SkString_append(reskia_string_t *string, const char text[]); // (SkString *string, const char text[])
void SkString_appendTextWithLength(reskia_string_t *string, const char text[], size_t len); // (SkString *string, const char text[], size_t len)
void SkString_appendString(reskia_string_t *string, const reskia_string_t *str); // (SkString *string, const SkString *str)
void SkString_appendStringView(reskia_string_t *string, int str); // (SkString *string, string_view_t str)
void SkString_appendUnichar(reskia_string_t *string, reskia_string_unichar_t uni); // (SkString *string, SkUnichar uni)
void SkString_appendS32(reskia_string_t *string, int value); // (SkString *string, int32_t value)
void SkString_appendS64(reskia_string_t *string, long long value, int minDigits); // (SkString *string, int64_t value, int minDigits)
void SkString_appendU32(reskia_string_t *string, uint32_t value); // (SkString *string, uint32_t value)
void SkString_appendU64(reskia_string_t *string, uint64_t value, int minDigits); // (SkString *string, uint64_t value, int minDigits)
void SkString_appendHex(reskia_string_t *string, uint32_t value, int minDigits); // (SkString *string, uint32_t value, int minDigits)
void SkString_appendScalar(reskia_string_t *string, float value); // (SkString *string, SkScalar value)
void SkString_prepend(reskia_string_t *string, const char text[]); // (SkString *string, const char text[])
void SkString_prependTextWithLength(reskia_string_t *string, const char text[], size_t len); // (SkString *string, const char text[], size_t len)
void SkString_prependString(reskia_string_t *string, const reskia_string_t *str); // (SkString *string, const SkString *str)
void SkString_prependStringView(reskia_string_t *string, int str); // (SkString *string, string_view_t str)
void SkString_prependUnichar(reskia_string_t *string, reskia_string_unichar_t uni); // (SkString *string, SkUnichar uni)
void SkString_prependS32(reskia_string_t *string, int value); // (SkString *string, int32_t value)
void SkString_prependS64(reskia_string_t *string, int value, int minDigits); // (SkString *string, int32_t value, int minDigits)
void SkString_prependHex(reskia_string_t *string, uint32_t value, int minDigits); // (SkString *string, uint32_t value, int minDigits)
void SkString_prependScalar(reskia_string_t *string, float value); // (SkString *string, SkScalar value)

void SkString_printf(reskia_string_t *string, const char format[],...);
void SkString_printVAList(reskia_string_t *string, const char format[], va_list);
void SkString_appendf(reskia_string_t *string, const char format[],...);
void SkString_appendVAList(reskia_string_t *string, const char format[], va_list);
void SkString_prependf(reskia_string_t *string, const char format[],...);
void SkString_prependVAList(reskia_string_t *string, const char format[], va_list);

void SkString_remove(reskia_string_t *string, size_t offset, size_t length); // (SkString *string, size_t offset, size_t length)
void SkString_swap(reskia_string_t *string, reskia_string_t *other); // (SkString *string, SkString *other)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STRING_H
