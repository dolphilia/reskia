//
// Created by dolphilia on 2024/01/11.
//

#ifndef RAIA_SKIA_SK_TRACE_MEMORY_DUMP_H
#define RAIA_SKIA_SK_TRACE_MEMORY_DUMP_H

#include <stdint.h>

typedef struct reskia_discardable_memory_t reskia_discardable_memory_t;
typedef struct reskia_trace_memory_dump_t reskia_trace_memory_dump_t;

#ifdef __cplusplus
extern "C" {
#endif

void SkTraceMemoryDump_delete(reskia_trace_memory_dump_t *traceMemoryDump); // (SkTraceMemoryDump *traceMemoryDump)
void SkTraceMemoryDump_dumpNumericValue(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *valueName, const char *units, uint64_t value); // (SkTraceMemoryDump *trace_memory_dump, const char *dumpName, const char *valueName, const char *units, uint64_t value)
void SkTraceMemoryDump_dumpStringValue(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *str1, const char *str2); // (SkTraceMemoryDump *trace_memory_dump, const char *dumpName, const char *str1, const char *str2)
void SkTraceMemoryDump_setMemoryBacking(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *backingType, const char *backingObjectId); // (SkTraceMemoryDump *trace_memory_dump, const char *dumpName, const char *backingType, const char *backingObjectId)
void SkTraceMemoryDump_setDiscardableMemoryBacking(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const reskia_discardable_memory_t *discardableMemoryObject); // (SkTraceMemoryDump *trace_memory_dump, const char *dumpName, const SkDiscardableMemory *discardableMemoryObject)
int SkTraceMemoryDump_getRequestedDetails(reskia_trace_memory_dump_t *trace_memory_dump); // (SkTraceMemoryDump *trace_memory_dump) -> SkTraceMemoryDump::LevelOfDetail
bool SkTraceMemoryDump_shouldDumpWrappedObjects(reskia_trace_memory_dump_t *trace_memory_dump); // (SkTraceMemoryDump *trace_memory_dump) -> bool
void SkTraceMemoryDump_dumpWrappedState(reskia_trace_memory_dump_t *trace_memory_dump, const char *str, bool b); // (SkTraceMemoryDump *trace_memory_dump, const char *str, bool b)
bool SkTraceMemoryDump_shouldDumpUnbudgetedObjects(reskia_trace_memory_dump_t *trace_memory_dump); // (SkTraceMemoryDump *trace_memory_dump) -> bool
void SkTraceMemoryDump_dumpBudgetedState(reskia_trace_memory_dump_t *trace_memory_dump, const char *str, bool b); // (SkTraceMemoryDump *trace_memory_dump, const char *str, bool b)

#ifdef __cplusplus
}
#endif

#endif //RAIA_SKIA_SK_TRACE_MEMORY_DUMP_H
