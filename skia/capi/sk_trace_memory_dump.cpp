//
// Created by dolphilia on 2024/01/11.
//

#include "sk_trace_memory_dump.h"

#include "include/core/SkTraceMemoryDump.h"

extern "C" {

void SkTraceMemoryDump_delete(reskia_trace_memory_dump_t *traceMemoryDump) {
    (void)traceMemoryDump;
}

void SkTraceMemoryDump_dumpNumericValue(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *valueName, const char *units, uint64_t value) {
    if (trace_memory_dump == nullptr || dumpName == nullptr || valueName == nullptr || units == nullptr) {
        return;
    }
    reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->dumpNumericValue(dumpName, valueName, units, value);
}

void SkTraceMemoryDump_dumpStringValue(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *str1, const char *str2) {
    if (trace_memory_dump == nullptr || dumpName == nullptr || str1 == nullptr || str2 == nullptr) {
        return;
    }
    reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->dumpStringValue(dumpName, str1, str2);
}

void SkTraceMemoryDump_setMemoryBacking(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const char *backingType, const char *backingObjectId) {
    if (trace_memory_dump == nullptr || dumpName == nullptr || backingType == nullptr || backingObjectId == nullptr) {
        return;
    }
    reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->setMemoryBacking(dumpName, backingType, backingObjectId);
}

void SkTraceMemoryDump_setDiscardableMemoryBacking(reskia_trace_memory_dump_t *trace_memory_dump, const char *dumpName, const reskia_discardable_memory_t *discardableMemoryObject) {
    if (trace_memory_dump == nullptr || dumpName == nullptr || discardableMemoryObject == nullptr) {
        return;
    }
    reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->setDiscardableMemoryBacking(dumpName, * reinterpret_cast<const SkDiscardableMemory *>(discardableMemoryObject));
}

reskia_trace_memory_dump_level_of_detail_t SkTraceMemoryDump_getRequestedDetails(reskia_trace_memory_dump_t *trace_memory_dump) {
    if (trace_memory_dump == nullptr) {
        return 0;
    }
    return static_cast<reskia_trace_memory_dump_level_of_detail_t>(
            reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->getRequestedDetails());
}

bool SkTraceMemoryDump_shouldDumpWrappedObjects(reskia_trace_memory_dump_t *trace_memory_dump) {
    if (trace_memory_dump == nullptr) {
        return false;
    }
    return reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->shouldDumpWrappedObjects();
}

void SkTraceMemoryDump_dumpWrappedState(reskia_trace_memory_dump_t *trace_memory_dump, const char *str, bool b) {
    if (trace_memory_dump == nullptr || str == nullptr) {
        return;
    }
    reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->dumpWrappedState(str, b);
}

bool SkTraceMemoryDump_shouldDumpUnbudgetedObjects(reskia_trace_memory_dump_t *trace_memory_dump) {
    if (trace_memory_dump == nullptr) {
        return false;
    }
    return reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->shouldDumpUnbudgetedObjects();
}

void SkTraceMemoryDump_dumpBudgetedState(reskia_trace_memory_dump_t *trace_memory_dump, const char *str, bool b) {
    if (trace_memory_dump == nullptr || str == nullptr) {
        return;
    }
    reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->dumpBudgetedState(str, b);
}

bool SkTraceMemoryDump_shouldDumpSizelessObjects(reskia_trace_memory_dump_t *trace_memory_dump) {
    if (trace_memory_dump == nullptr) {
        return false;
    }
    return reinterpret_cast<SkTraceMemoryDump *>(trace_memory_dump)->shouldDumpSizelessObjects();
}

}
