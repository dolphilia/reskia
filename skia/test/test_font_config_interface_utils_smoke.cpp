#include <cstdio>
#include <vector>

#include "capi/sk_font_config_interface.h"
#include "capi/sk_font_style.h"
#include "capi/sk_string.h"

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[font-config-interface-utils-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    reskia_font_config_identity_t *identity = SkFontConfigInterface_FontIdentity_new();
    if (!check(identity != nullptr, "FontIdentity_new")) {
        return 1;
    }

    SkFontConfigInterface_FontIdentity_setID(identity, 42);
    SkFontConfigInterface_FontIdentity_setTTCIndex(identity, 3);
    SkFontConfigInterface_FontIdentity_setString(identity, "Reskia Sans");
    reskia_font_style_t *bold = SkFontStyle_Bold();
    if (!check(bold != nullptr, "SkFontStyle_Bold")) {
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    SkFontConfigInterface_FontIdentity_setStyle(identity, bold);

    if (!check(SkFontConfigInterface_FontIdentity_getID(identity) == 42, "FontIdentity_getID")) {
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    if (!check(SkFontConfigInterface_FontIdentity_getTTCIndex(identity) == 3, "FontIdentity_getTTCIndex")) {
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    reskia_string_t *family = SkFontConfigInterface_FontIdentity_getString(identity);
    if (!check(family != nullptr && SkString_equalsText(family, "Reskia Sans"), "FontIdentity_getString")) {
        SkString_delete(family);
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    SkString_delete(family);

    const size_t bytes = SkFontConfigInterface_FontIdentity_writeToMemory(identity, nullptr);
    if (!check(bytes > 0, "FontIdentity_writeToMemory size")) {
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    std::vector<unsigned char> buffer(bytes);
    if (!check(SkFontConfigInterface_FontIdentity_writeToMemory(identity, buffer.data()) == bytes,
               "FontIdentity_writeToMemory data")) {
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    reskia_font_config_identity_t *round_trip = SkFontConfigInterface_FontIdentity_new();
    if (!check(round_trip != nullptr, "FontIdentity_new round trip")) {
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    if (!check(SkFontConfigInterface_FontIdentity_readFromMemory(round_trip, buffer.data(), buffer.size()) == bytes,
               "FontIdentity_readFromMemory")) {
        SkFontConfigInterface_FontIdentity_delete(round_trip);
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    if (!check(SkFontConfigInterface_FontIdentity_getID(round_trip) == 42,
               "FontIdentity_readFromMemory id")) {
        SkFontConfigInterface_FontIdentity_delete(round_trip);
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }

    reskia_font_config_interface_t *direct = SkFontConfigInterface_GetSingletonDirectInterface();
    if (!check(direct != nullptr, "GetSingletonDirectInterface")) {
        SkFontConfigInterface_FontIdentity_delete(round_trip);
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    reskia_font_config_interface_t *global = SkFontConfigInterface_RefGlobal();
    if (!check(global != nullptr, "RefGlobal")) {
        SkFontConfigInterface_FontIdentity_delete(round_trip);
        SkFontStyle_delete(bold);
        SkFontConfigInterface_FontIdentity_delete(identity);
        return 1;
    }
    SkFontConfigInterface_ref(global);
    SkFontConfigInterface_unref(global);
    SkFontConfigInterface_SetGlobal(global);
    SkFontConfigInterface_SetGlobal(nullptr);
    SkFontConfigInterface_unref(global);

    SkFontConfigInterface_FontIdentity_delete(round_trip);
    SkFontStyle_delete(bold);
    SkFontConfigInterface_FontIdentity_delete(identity);
    std::fprintf(stdout, "[font-config-interface-utils-smoke] PASS\n");
    return 0;
}
