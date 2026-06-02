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

reskia_string_t *SkString_new(); // () -> SkString *
reskia_string_t *SkString_newWithLength(size_t len); // (size_t len) -> SkString *
reskia_string_t *SkString_newFromText(const char text[]); // text is required; NULL returns NULL.
reskia_string_t *SkString_newFromTextWithLength(const char text[], size_t len); // text is required when len > 0; invalid input returns NULL.
reskia_string_t *SkString_newCopy(const reskia_string_t *str); // str is required; NULL returns NULL.
reskia_string_t *SkString_newFromStdString(const reskia_std_string_t *str); // str is required; NULL returns NULL.
reskia_string_t *SkString_newFromStringView(int view); // view must be a valid string_view handle; invalid handle returns NULL.
void SkString_delete(reskia_string_t *string); // (SkString *string)
bool SkString_isEmpty(reskia_string_t *string); // NULL string returns true.
size_t SkString_size(reskia_string_t *string); // NULL string returns 0.
const char * SkString_begin(reskia_string_t *string); // Returns borrowed data begin; NULL string returns NULL.
char * SkString_beginMutable(reskia_string_t *string); // Returns borrowed mutable data begin; NULL string returns NULL.
const char * SkString_end(reskia_string_t *string); // Returns borrowed data end; NULL string returns NULL.
char * SkString_endMutable(reskia_string_t *string); // Returns borrowed mutable data end; NULL string returns NULL.
const char * SkString_data(reskia_string_t *string); // Returns borrowed data; NULL string returns NULL.
char * SkString_dataMutable(reskia_string_t *string); // Returns borrowed mutable data; NULL string returns NULL.
const char * SkString_c_str(reskia_string_t *string); // Returns borrowed C string; NULL string returns NULL.
bool SkString_equals(reskia_string_t *string, const reskia_string_t *str); // NULL input returns false.
bool SkString_equalsText(reskia_string_t *string, const char text[]); // NULL input returns false.
bool SkString_equalsTextWithLength(reskia_string_t *string, const char text[], size_t len); // NULL string or NULL text with len > 0 returns false.
bool SkString_startsWith(reskia_string_t *string, const char prefixStr[]); // NULL input returns false.
bool SkString_startsWithChar(reskia_string_t *string, char prefixChar); // NULL string returns false.
bool SkString_endsWith(reskia_string_t *string, const char suffixStr[]); // NULL input returns false.
bool SkString_endsWithChar(reskia_string_t *string, char suffixChar); // NULL string returns false.

bool SkString_contains(reskia_string_t *string, const char substring[]); // NULL input returns false.
bool SkString_containsChar(reskia_string_t *string, char subchar); // NULL string returns false.
int SkString_find(reskia_string_t *string, const char substring[]); // NULL input returns -1.
int SkString_findLastOf(reskia_string_t *string, char subchar); // NULL string returns -1.
void SkString_reset(reskia_string_t *string); // NULL string is no-op.
void SkString_resize(reskia_string_t *string, size_t len); // NULL string is no-op.
void SkString_set(reskia_string_t *string, const reskia_string_t *src); // NULL input is no-op.
void SkString_setText(reskia_string_t *string, const char text[]); // NULL input is no-op.
void SkString_setTextWithLength(reskia_string_t *string, const char text[], size_t len); // NULL string or NULL text with len > 0 is no-op.
void SkString_setStringView(reskia_string_t *string, int str); // NULL string or invalid string_view handle is no-op.
void SkString_insert(reskia_string_t *string, size_t offset, const char text[]); // NULL input is no-op.
void SkString_insertTextWithLength(reskia_string_t *string, size_t offset, const char text[], size_t len); // NULL string or NULL text with len > 0 is no-op.
void SkString_insertString(reskia_string_t *string, size_t offset, const reskia_string_t *str); // NULL input is no-op.
void SkString_insertStringView(reskia_string_t *string, size_t offset, int str); // NULL string or invalid string_view handle is no-op.
void SkString_insertUnichar(reskia_string_t *string, size_t offset, reskia_string_unichar_t unichar); // (SkString *string, size_t offset, SkUnichar unichar)
void SkString_insertS32(reskia_string_t *string, size_t offset, int value); // (SkString *string, size_t offset, int32_t value)
void SkString_insertS64(reskia_string_t *string, size_t offset, long long value, int minDigits); // (SkString *string, size_t offset, int64_t value, int minDigits)
void SkString_insertU32(reskia_string_t *string, size_t offset, uint32_t value); // (SkString *string, size_t offset, uint32_t value)
void SkString_insertU64(reskia_string_t *string, size_t offset, uint64_t value, int minDigits); // (SkString *string, size_t offset, uint64_t value, int minDigits)
void SkString_insertHex(reskia_string_t *string, size_t offset, uint32_t value, int minDigits); // (SkString *string, size_t offset, uint32_t value, int minDigits)
void SkString_insertScalar(reskia_string_t *string, size_t offset, float v); // (SkString *string, size_t offset, SkScalar v)
void SkString_append(reskia_string_t *string, const char text[]); // NULL input is no-op.
void SkString_addAssign(reskia_string_t *string, char c); // operator+=(char); NULL string is no-op.
void SkString_appendTextWithLength(reskia_string_t *string, const char text[], size_t len); // NULL string or NULL text with len > 0 is no-op.
void SkString_appendString(reskia_string_t *string, const reskia_string_t *str); // NULL input is no-op.
void SkString_appendStringView(reskia_string_t *string, int str); // NULL string or invalid string_view handle is no-op.
void SkString_appendUnichar(reskia_string_t *string, reskia_string_unichar_t uni); // (SkString *string, SkUnichar uni)
void SkString_appendS32(reskia_string_t *string, int value); // (SkString *string, int32_t value)
void SkString_appendS64(reskia_string_t *string, long long value, int minDigits); // (SkString *string, int64_t value, int minDigits)
void SkString_appendU32(reskia_string_t *string, uint32_t value); // (SkString *string, uint32_t value)
void SkString_appendU64(reskia_string_t *string, uint64_t value, int minDigits); // (SkString *string, uint64_t value, int minDigits)
void SkString_appendHex(reskia_string_t *string, uint32_t value, int minDigits); // (SkString *string, uint32_t value, int minDigits)
void SkString_appendScalar(reskia_string_t *string, float value); // (SkString *string, SkScalar value)
void SkString_prepend(reskia_string_t *string, const char text[]); // NULL input is no-op.
void SkString_prependTextWithLength(reskia_string_t *string, const char text[], size_t len); // NULL string or NULL text with len > 0 is no-op.
void SkString_prependString(reskia_string_t *string, const reskia_string_t *str); // NULL input is no-op.
void SkString_prependStringView(reskia_string_t *string, int str); // NULL string or invalid string_view handle is no-op.
void SkString_prependUnichar(reskia_string_t *string, reskia_string_unichar_t uni); // (SkString *string, SkUnichar uni)
void SkString_prependS32(reskia_string_t *string, int value); // (SkString *string, int32_t value)
void SkString_prependS64(reskia_string_t *string, int value, int minDigits); // (SkString *string, int32_t value, int minDigits)
void SkString_prependHex(reskia_string_t *string, uint32_t value, int minDigits); // (SkString *string, uint32_t value, int minDigits)
void SkString_prependScalar(reskia_string_t *string, float value); // (SkString *string, SkScalar value)

void SkString_printf(reskia_string_t *string, const char format[],...); // NULL string or format is no-op.
void SkString_printVAList(reskia_string_t *string, const char format[], va_list); // NULL string or format is no-op.
void SkString_appendf(reskia_string_t *string, const char format[],...); // NULL string or format is no-op.
void SkString_appendVAList(reskia_string_t *string, const char format[], va_list); // NULL string or format is no-op.
void SkString_prependf(reskia_string_t *string, const char format[],...); // NULL string or format is no-op.
void SkString_prependVAList(reskia_string_t *string, const char format[], va_list); // NULL string or format is no-op.

void SkString_remove(reskia_string_t *string, size_t offset, size_t length); // NULL string is no-op.
void SkString_swap(reskia_string_t *string, reskia_string_t *other); // NULL input is no-op.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_STRING_H
