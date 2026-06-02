//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TRACE_MEMORY_DUMP_H
#define RAIA_SKIA_SK_TRACE_MEMORY_DUMP_H

#include <stdint.h>

typedef struct reskia_discardable_memory_t reskia_discardable_memory_t;
typedef struct reskia_trace_memory_dump_t reskia_trace_memory_dump_t;
typedef int32_t reskia_trace_memory_dump_level_of_detail_t; // SkTraceMemoryDump::LevelOfDetail

#ifdef __cplusplus
extern "C" {
#endif

void SkTraceMemoryDump_delete(reskia_trace_memory_dump_t *traceMemoryDump); // No-op for borrowed/non-owned dump pointers.
void SkTraceMemoryDump_dumpNumericValue(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *valueName, const char *units, uint64_t value); // Required strings and dump pointer; invalid input is no-op.
void SkTraceMemoryDump_dumpStringValue(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *str1, const char *str2); // Required strings and dump pointer; invalid input is no-op.
void SkTraceMemoryDump_setMemoryBacking(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *backingType, const char *backingObjectId); // Required strings and dump pointer; invalid input is no-op.
void SkTraceMemoryDump_setDiscardableMemoryBacking(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const reskia_discardable_memory_t *discardableMemoryObject); // dumpName and discardable object are required; invalid input is no-op.
reskia_trace_memory_dump_level_of_detail_t SkTraceMemoryDump_getRequestedDetails(reskia_trace_memory_dump_t *trace_memory_dump); // NULL trace_memory_dump returns 0.
bool SkTraceMemoryDump_shouldDumpWrappedObjects(reskia_trace_memory_dump_t *trace_memory_dump); // NULL trace_memory_dump returns false.
void SkTraceMemoryDump_dumpWrappedState(reskia_trace_memory_dump_t *trace_memory_dump, const char *str, bool b); // trace_memory_dump and str are required; invalid input is no-op.
bool SkTraceMemoryDump_shouldDumpUnbudgetedObjects(reskia_trace_memory_dump_t *trace_memory_dump); // NULL trace_memory_dump returns false.
void SkTraceMemoryDump_dumpBudgetedState(reskia_trace_memory_dump_t *trace_memory_dump, const char *str, bool b); // trace_memory_dump and str are required; invalid input is no-op.
bool SkTraceMemoryDump_shouldDumpSizelessObjects(reskia_trace_memory_dump_t *trace_memory_dump); // NULL trace_memory_dump returns false.

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TRACE_MEMORY_DUMP_H
