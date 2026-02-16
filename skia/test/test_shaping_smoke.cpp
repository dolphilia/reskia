#include <cmath>
#include <cstdio>
#include <cstring>

#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkFont.h"
#include "include/core/SkFontMgr.h"
#include "include/core/SkPoint.h"
#include "include/core/SkSize.h"
#include "include/core/SkStream.h"

#include "include/core/SkGraphics.h"
#include "modules/skshaper/include/SkShaper.h"
#include "modules/svg/include/SkSVGDOM.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[shaping-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_shape_utf8_bidi_linebreak() {
    const char* text = u8"Hello שלום\nمرحبا 123";

    std::unique_ptr<SkShaper> shaper = SkShaper::Make();
    if (!check(shaper != nullptr, "SkShaper::Make")) return false;

    SkFont font(nullptr, 20.0f);
    SkTextBlobBuilderRunHandler handler(text, SkPoint::Make(0.0f, 24.0f));
    shaper->shape(text, std::strlen(text), font, true, 220.0f, &handler);

    sk_sp<SkTextBlob> blob = handler.makeBlob();
    if (!check(blob != nullptr, "SkTextBlobBuilderRunHandler::makeBlob")) return false;
    if (!check(blob->bounds().width() > 0.0f, "text blob bounds width > 0")) return false;

    const SkPoint end = handler.endPoint();
    if (!check(std::isfinite(end.x()) && std::isfinite(end.y()), "shape endPoint finite")) return false;
    if (!check(end.y() > 0.0f, "shape endPoint y > 0")) return false;

    return true;
}

bool has_drawn_pixels(const SkBitmap& bitmap) {
    for (int y = 0; y < bitmap.height(); ++y) {
        for (int x = 0; x < bitmap.width(); ++x) {
            if (bitmap.getColor(x, y) != SK_ColorTRANSPARENT) {
                return true;
            }
        }
    }
    return false;
}

bool smoke_svg_text_render() {
    const char* svg = R"SVG(
<svg xmlns="http://www.w3.org/2000/svg" width="240" height="80">
  <rect x="0" y="0" width="240" height="80" fill="#ffffff"/>
  <text x="8" y="30" font-size="20">Hello שלום</text>
  <text x="8" y="60" font-size="20">مرحبا 123</text>
</svg>
)SVG";

    SkMemoryStream stream(svg, std::strlen(svg), true);
    SkSVGDOM::Builder builder;
    builder.setFontManager(SkFontMgr::RefDefault());

    sk_sp<SkSVGDOM> dom = builder.make(stream);
    if (!check(dom != nullptr, "SkSVGDOM::Builder::make")) return false;

    dom->setContainerSize(SkSize::Make(240.0f, 80.0f));

    SkBitmap bitmap;
    if (!check(bitmap.tryAllocN32Pixels(240, 80), "SkBitmap::tryAllocN32Pixels")) return false;
    bitmap.eraseColor(SK_ColorTRANSPARENT);

    SkCanvas canvas(bitmap);
    dom->render(&canvas);

    if (!check(has_drawn_pixels(bitmap), "svg text render produced pixels")) return false;
    return true;
}

}  // namespace

int main() {
    SkGraphics::Init();

    if (!smoke_shape_utf8_bidi_linebreak()) return 1;
    if (!smoke_svg_text_render()) return 1;

    std::fprintf(stdout, "[shaping-smoke] PASS\n");
    return 0;
}
