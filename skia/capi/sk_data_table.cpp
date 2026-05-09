//
// Created by dolphilia on 2024/01/08.
//

#include "sk_data_table.h"

#include "include/core/SkDataTable.h"

#include "../handles/static_sk_data_table.h"

#include "../handles/static_sk_data_table-internal.h"

#include <utility>

namespace {

sk_data_table_t make_data_table_handle(sk_sp<SkDataTable> data_table) {
    if (!data_table) {
        return 0;
    }
    return static_sk_data_table_make(std::move(data_table));
}

bool valid_index(const SkDataTable *data_table, int index) {
    return data_table != nullptr && index >= 0 && index < data_table->count();
}

}  // namespace

extern "C" {

void SkDataTable_release(reskia_data_table_t *data_table) {
    if (data_table == nullptr) {
        return;
    }
    reinterpret_cast<SkDataTable *>(data_table)->unref();
}

bool SkDataTable_isEmpty(reskia_data_table_t *data_table) {
    if (data_table == nullptr) {
        return true;
    }
    return reinterpret_cast<SkDataTable *>(data_table)->isEmpty();
}

int SkDataTable_count(reskia_data_table_t *data_table) {
    if (data_table == nullptr) {
        return 0;
    }
    return reinterpret_cast<SkDataTable *>(data_table)->count();
}

size_t SkDataTable_atSize(reskia_data_table_t *data_table, int index) {
    auto *table = reinterpret_cast<SkDataTable *>(data_table);
    if (!valid_index(table, index)) {
        return 0;
    }
    return table->atSize(index);
}

const uint8_t * SkDataTable_at(reskia_data_table_t *data_table, int index, size_t *size) {
    auto *table = reinterpret_cast<SkDataTable *>(data_table);
    if (!valid_index(table, index)) {
        if (size != nullptr) {
            *size = 0;
        }
        return nullptr;
    }
    return reinterpret_cast<const uint8_t *>(table->at(index, size));
}

const char * SkDataTable_atStr(reskia_data_table_t *data_table, int index) {
    auto *table = reinterpret_cast<SkDataTable *>(data_table);
    if (!valid_index(table, index)) {
        return nullptr;
    }
    return table->atStr(index);
}

bool SkDataTable_unique(reskia_data_table_t *data_table) {
    if (data_table == nullptr) {
        return false;
    }
    return reinterpret_cast<SkDataTable *>(data_table)->unique();
}

void SkDataTable_ref(reskia_data_table_t *data_table) {
    if (data_table == nullptr) {
        return;
    }
    reinterpret_cast<SkDataTable *>(data_table)->ref();
}

void SkDataTable_unref(reskia_data_table_t *data_table) {
    if (data_table == nullptr) {
        return;
    }
    reinterpret_cast<SkDataTable *>(data_table)->unref();
}

// static

sk_data_table_t SkDataTable_MakeEmpty() {
    return make_data_table_handle(SkDataTable::MakeEmpty());
}

sk_data_table_t SkDataTable_MakeCopyArrays(const uint8_t * const *ptrs, const size_t *sizes, int count) {
    if (count <= 0) {
        return SkDataTable_MakeEmpty();
    }
    if (ptrs == nullptr || sizes == nullptr) {
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        if (ptrs[i] == nullptr && sizes[i] > 0) {
            return 0;
        }
    }
    return make_data_table_handle(SkDataTable::MakeCopyArrays(reinterpret_cast<const void *const *>(ptrs), sizes, count));
}

sk_data_table_t SkDataTable_MakeCopyArray(const uint8_t *array, size_t elemSize, int count) {
    if (count <= 0) {
        return SkDataTable_MakeEmpty();
    }
    if (array == nullptr || elemSize == 0) {
        return 0;
    }
    return make_data_table_handle(SkDataTable::MakeCopyArray(array, elemSize, count));
}

sk_data_table_t SkDataTable_MakeArrayProc(const uint8_t *array, size_t elemSize, int count, void (*proc)(void*), void *context) {
    if (count <= 0) {
        return SkDataTable_MakeEmpty();
    }
    if (array == nullptr || elemSize == 0) {
        return 0;
    }
    return make_data_table_handle(SkDataTable::MakeArrayProc(array, elemSize, count, proc, context));
}

}
