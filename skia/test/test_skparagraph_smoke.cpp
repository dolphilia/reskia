#include <cstdio>

#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkGraphics.h"
#if defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_IOS)
#include "include/ports/SkFontMgr_mac_ct.h"
#endif

#include "modules/skparagraph/include/FontCollection.h"
#include "modules/skparagraph/include/Paragraph.h"
#include "modules/skparagraph/include/ParagraphBuilder.h"
#include "modules/skparagraph/include/ParagraphStyle.h"
#include "modules/skparagraph/include/TextStyle.h"
#include "modules/skunicode/include/SkUnicode.h"
#include "modules/skunicode/include/SkUnicode_icu.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[skparagraph-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool has_non_white_pixel(const SkBitmap& bitmap) {
    for (int y = 0; y < bitmap.height(); ++y) {
        for (int x = 0; x < bitmap.width(); ++x) {
            if (bitmap.getColor(x, y) != SK_ColorWHITE) {
                return true;
            }
        }
    }
    return false;
}

sk_sp<SkUnicode> make_unicode() {
    return SkUnicodes::ICU::Make();
}

bool smoke_layout_and_paint() {
    using namespace skia::textlayout;

    sk_sp<FontCollection> fonts = sk_make_sp<FontCollection>();
#if defined(SK_BUILD_FOR_MAC) || defined(SK_BUILD_FOR_IOS)
    fonts->setDefaultFontManager(SkFontMgr_New_CoreText(nullptr));
#else
    fonts->setDefaultFontManager(SkFontMgr::RefEmpty());
#endif

    ParagraphStyle paragraph_style;
    TextStyle text_style;
    text_style.setFontSize(24.0f);
    text_style.setColor(SK_ColorBLACK);
    text_style.setFontFamilies({SkString("sans-serif")});
    paragraph_style.setTextStyle(text_style);

    std::unique_ptr<ParagraphBuilder> builder = ParagraphBuilder::make(paragraph_style, fonts, make_unicode());
    if (!check(builder != nullptr, "ParagraphBuilder::make")) return false;

    builder->pushStyle(text_style);
    builder->addText("Hello Skia\nParagraph 123");
    builder->pop();

    std::unique_ptr<Paragraph> paragraph = builder->Build();
    if (!check(paragraph != nullptr, "ParagraphBuilder::Build")) return false;

    paragraph->layout(280.0f);
    if (!check(paragraph->getHeight() > 0.0f, "paragraph height > 0")) return false;
    if (!check(paragraph->lineNumber() >= 2, "paragraph line count >= 2")) return false;

    SkBitmap bitmap;
    if (!check(bitmap.tryAllocN32Pixels(300, 140), "SkBitmap::tryAllocN32Pixels")) return false;
    bitmap.eraseColor(SK_ColorWHITE);

    SkCanvas canvas(bitmap);
    paragraph->paint(&canvas, 8.0f, 8.0f);

    if (!check(has_non_white_pixel(bitmap), "paragraph paint produced pixels")) return false;
    return true;
}

}  // namespace

int main() {
    SkGraphics::Init();

    if (!smoke_layout_and_paint()) {
        return 1;
    }

    std::fprintf(stdout, "[skparagraph-smoke] PASS\n");
    return 0;
}
