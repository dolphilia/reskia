#include "capi/sk_font.h"

#include <cstdint>

struct GlyphPathSmokeState {
    int callbacks = 0;
    bool saw_matrix = false;
};

static void glyph_path_smoke_callback(const reskia_path_t *, const reskia_matrix_t *matrix, void *ctx) {
    auto *state = static_cast<GlyphPathSmokeState *>(ctx);
    state->callbacks += 1;
    state->saw_matrix = state->saw_matrix || matrix != nullptr;
}

int main() {
    reskia_font_t *font = SkFont_new();
    if (!font) {
        return 1;
    }

    uint16_t glyphs[] = {0};
    GlyphPathSmokeState state;
    SkFont_getPaths(font, glyphs, 1, glyph_path_smoke_callback, &state);
    SkFont_delete(font);

    if (state.callbacks != 1) {
        return 2;
    }
    if (!state.saw_matrix) {
        return 3;
    }
    return 0;
}
