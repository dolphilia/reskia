#include "capi/sk_typeface.h"
#include "capi/sk_typeface_mac.h"
#include "handles/static_sk_typeface.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[typeface-mac-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    if (!check(Mac_SkMakeTypefaceFromCTFont(nullptr) == 0, "Mac_SkMakeTypefaceFromCTFont(nullptr)")) {
        return 1;
    }
    if (!check(Mac_SkTypeface_GetCTFontRef(nullptr) == nullptr, "Mac_SkTypeface_GetCTFontRef(nullptr)")) {
        return 2;
    }

    const sk_typeface_t typeface_handle = SkTypeface_MakeDefault();
    auto *typeface = static_cast<reskia_typeface_t *>(static_sk_typeface_get_ptr(typeface_handle));
    if (!check(typeface_handle != 0 && typeface != nullptr, "SkTypeface_MakeDefault()")) {
        return 3;
    }
    if (!check(Mac_SkTypeface_GetCTFontRef(typeface) != nullptr, "Mac_SkTypeface_GetCTFontRef(default)")) {
        static_sk_typeface_delete(typeface_handle);
        return 4;
    }
    static_sk_typeface_delete(typeface_handle);
    return 0;
}
