//
// Created by dolphilia on 2024/01/11.
//

#include "sk_trace_memory_dump.h"

#include "include/core/SkTraceMemoryDump.h"

extern "C" {

void SkTraceMemoryDump_delete(void * traceMemoryDump) {
    const SkTraceMemoryDump *traceMemoryDumpPtr = static_cast<SkTraceMemoryDump *>(traceMemoryDump);
    delete &traceMemoryDumpPtr;
}

void SkTraceMemoryDump_dumpNumericValue(void *trace_memory_dump, const char *dumpName, const char *valueName, const char *units, uint64_t value) {
    static_cast<SkTraceMemoryDump *>(trace_memory_dump)->dumpNumericValue(dumpName, valueName, units, value);
}

void SkTraceMemoryDump_dumpStringValue(void *trace_memory_dump, const char *dumpName, const char *str1, const char *str2) {
    static_cast<SkTraceMemoryDump *>(trace_memory_dump)->dumpStringValue(dumpName, str1, str2);
}

void SkTraceMemoryDump_setMemoryBacking(void *trace_memory_dump, const char *dumpName, const char *backingType, const char *backingObjectId) {
    static_cast<SkTraceMemoryDump *>(trace_memory_dump)->setMemoryBacking(dumpName, backingType, backingObjectId);
}

void SkTraceMemoryDump_setDiscardableMemoryBacking(void *trace_memory_dump, const char *dumpName, const void *discardableMemoryObject) {
    static_cast<SkTraceMemoryDump *>(trace_memory_dump)->setDiscardableMemoryBacking(dumpName, * static_cast<const SkDiscardableMemory *>(discardableMemoryObject));
}

int SkTraceMemoryDump_getRequestedDetails(void *trace_memory_dump) {
    return static_cast<SkTraceMemoryDump *>(trace_memory_dump)->getRequestedDetails();
}

bool SkTraceMemoryDump_shouldDumpWrappedObjects(void *trace_memory_dump) {
    return static_cast<SkTraceMemoryDump *>(trace_memory_dump)->shouldDumpWrappedObjects();
}

void SkTraceMemoryDump_dumpWrappedState(void *trace_memory_dump, const char *str, bool b) {
    static_cast<SkTraceMemoryDump *>(trace_memory_dump)->dumpWrappedState(str, b);
}

bool SkTraceMemoryDump_shouldDumpUnbudgetedObjects(void *trace_memory_dump) {
    return static_cast<SkTraceMemoryDump *>(trace_memory_dump)->shouldDumpUnbudgetedObjects();
}

void SkTraceMemoryDump_dumpBudgetedState(void *trace_memory_dump, const char *str, bool b) {
    static_cast<SkTraceMemoryDump *>(trace_memory_dump)->dumpBudgetedState(str, b);
}

}