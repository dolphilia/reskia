#include "capi/sk_font.h"
#include "capi/sk_text_blob.h"
#include "capi/sk_text_blob_builder.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[text-blob-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkTextBlob_release(nullptr);
    SkTextBlob_ref(nullptr);
    SkTextBlob_unref(nullptr);
    SkTextBlob_deref(nullptr);

    if (!check(SkTextBlob_bounds(nullptr) == nullptr, "SkTextBlob_bounds(nullptr)")) {
        return 1;
    }
    if (!check(SkTextBlob_uniqueID(nullptr) == 0, "SkTextBlob_uniqueID(nullptr)")) {
        return 2;
    }
    if (!check(SkTextBlob_getIntercepts(nullptr, nullptr, nullptr, nullptr) == 0, "SkTextBlob_getIntercepts(nullptr)")) {
        return 3;
    }
    if (!check(SkTextBlob_serialize(nullptr, nullptr, nullptr, 0) == 0, "SkTextBlob_serialize(nullptr)")) {
        return 4;
    }
    if (!check(SkTextBlob_serializeToData(nullptr, nullptr) == 0, "SkTextBlob_serializeToData(nullptr)")) {
        return 5;
    }
    if (!check(!SkTextBlob_unique(nullptr), "SkTextBlob_unique(nullptr)")) {
        return 6;
    }
    if (!check(!SkTextBlob_refCntGreaterThan(nullptr, 0), "SkTextBlob_refCntGreaterThan(nullptr)")) {
        return 7;
    }
    if (!check(SkTextBlob_MakeFromText(nullptr, 1, nullptr, 0) == 0, "SkTextBlob_MakeFromText invalid")) {
        return 8;
    }
    if (!check(SkTextBlob_MakeFromString(nullptr, nullptr, 0) == 0, "SkTextBlob_MakeFromString invalid")) {
        return 9;
    }
    if (!check(SkTextBlob_MakeFromPosTextH(nullptr, 1, nullptr, 0.0f, nullptr, 0) == 0, "SkTextBlob_MakeFromPosTextH invalid")) {
        return 10;
    }
    if (!check(SkTextBlob_MakeFromPosText(nullptr, 1, nullptr, nullptr, 0) == 0, "SkTextBlob_MakeFromPosText invalid")) {
        return 11;
    }
    if (!check(SkTextBlob_MakeFromRSXform(nullptr, 1, nullptr, nullptr, 0) == 0, "SkTextBlob_MakeFromRSXform invalid")) {
        return 12;
    }
    if (!check(SkTextBlob_Deserialize(nullptr, 1, nullptr) == 0, "SkTextBlob_Deserialize invalid")) {
        return 13;
    }

    SkTextBlobBuilder_delete(nullptr);
    if (!check(SkTextBlobBuilder_make(nullptr) == 0, "SkTextBlobBuilder_make(nullptr)")) {
        return 14;
    }
    if (!check(SkTextBlobBuilder_allocRun(nullptr, nullptr, 1, 0.0f, 0.0f, nullptr) == nullptr, "allocRun null")) {
        return 15;
    }
    if (!check(SkTextBlobBuilder_allocRunPosH(nullptr, nullptr, 1, 0.0f, nullptr) == nullptr, "allocRunPosH null")) {
        return 16;
    }
    if (!check(SkTextBlobBuilder_allocRunPos(nullptr, nullptr, 1, nullptr) == nullptr, "allocRunPos null")) {
        return 17;
    }
    if (!check(SkTextBlobBuilder_allocRunRSXform(nullptr, nullptr, 1) == nullptr, "allocRunRSXform null")) {
        return 18;
    }
    if (!check(SkTextBlobBuilder_allocRunText(nullptr, nullptr, 1, 0.0f, 0.0f, 0, nullptr) == nullptr, "allocRunText null")) {
        return 19;
    }
    if (!check(SkTextBlobBuilder_allocRunTextPosH(nullptr, nullptr, 1, 0.0f, 0, nullptr) == nullptr, "allocRunTextPosH null")) {
        return 20;
    }
    if (!check(SkTextBlobBuilder_allocRunTextPos(nullptr, nullptr, 1, 0, nullptr) == nullptr, "allocRunTextPos null")) {
        return 21;
    }
    if (!check(SkTextBlobBuilder_allocRunTextRSXform(nullptr, nullptr, 1, 0, nullptr) == nullptr, "allocRunTextRSXform null")) {
        return 22;
    }

    reskia_font_t *font = SkFont_new();
    if (!check(font != nullptr, "SkFont_new")) {
        return 23;
    }

    const char text[] = "A";
    const sk_text_blob_t blob_handle = SkTextBlob_MakeFromString(text, font, 0);
    if (!check(blob_handle != 0, "SkTextBlob_MakeFromString valid")) {
        SkFont_delete(font);
        return 24;
    }
    auto *blob = static_cast<reskia_text_blob_t *>(static_sk_text_blob_get_ptr(blob_handle));
    if (!check(blob != nullptr, "static_sk_text_blob_get_ptr")) {
        static_sk_text_blob_delete(blob_handle);
        SkFont_delete(font);
        return 25;
    }
    if (!check(SkTextBlob_bounds(blob) != nullptr, "SkTextBlob_bounds valid")) {
        static_sk_text_blob_delete(blob_handle);
        SkFont_delete(font);
        return 26;
    }
    if (!check(SkTextBlob_uniqueID(blob) != 0, "SkTextBlob_uniqueID valid")) {
        static_sk_text_blob_delete(blob_handle);
        SkFont_delete(font);
        return 27;
    }
    const float intercept_bounds[2] = {0.0f, 1.0f};
    if (!check(SkTextBlob_getIntercepts(blob, intercept_bounds, nullptr, nullptr) >= 0, "SkTextBlob_getIntercepts valid")) {
        static_sk_text_blob_delete(blob_handle);
        SkFont_delete(font);
        return 28;
    }
    const sk_data_t serialized = SkTextBlob_serializeToData(blob, nullptr);
    if (!check(serialized != 0, "SkTextBlob_serializeToData valid")) {
        static_sk_text_blob_delete(blob_handle);
        SkFont_delete(font);
        return 29;
    }
    static_sk_data_delete(serialized);
    SkTextBlob_ref(blob);
    SkTextBlob_unref(blob);
    static_sk_text_blob_delete(blob_handle);

    reskia_text_blob_builder_t *builder = SkTextBlobBuilder_new();
    if (!check(builder != nullptr, "SkTextBlobBuilder_new")) {
        SkFont_delete(font);
        return 30;
    }
    if (!check(SkTextBlobBuilder_make(builder) == 0, "SkTextBlobBuilder_make empty")) {
        SkTextBlobBuilder_delete(builder);
        SkFont_delete(font);
        return 31;
    }
    if (!check(SkTextBlobBuilder_allocRun(builder, font, 0, 0.0f, 0.0f, nullptr) == nullptr, "SkTextBlobBuilder_allocRun zero count")) {
        SkTextBlobBuilder_delete(builder);
        SkFont_delete(font);
        return 32;
    }
    if (!check(SkTextBlobBuilder_allocRunText(builder, font, 1, 0.0f, 0.0f, -1, nullptr) == nullptr, "SkTextBlobBuilder_allocRunText negative text")) {
        SkTextBlobBuilder_delete(builder);
        SkFont_delete(font);
        return 33;
    }
    SkTextBlobBuilder_delete(builder);
    SkFont_delete(font);

    return 0;
}
