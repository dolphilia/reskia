#include <cstdio>
#include <cstring>

#include "capi/sk_canvas.h"
#include "capi/sk_graphics.h"
#include "capi/sk_skottie.h"

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::fprintf(stderr, "[skottie-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

bool smoke_skottie_minimal() {
    static const char* kLottieJson = R"JSON({
  "v": "5.7.4",
  "fr": 30,
  "ip": 0,
  "op": 60,
  "w": 64,
  "h": 64,
  "nm": "reskia-skottie-smoke",
  "ddd": 0,
  "assets": [],
  "layers": []
})JSON";

    reskia_skottie_animation_t* animation =
            Skottie_Animation_Make(kLottieJson, std::strlen(kLottieJson));
    if (!check(animation != nullptr, "Skottie_Animation_Make")) {
        return false;
    }

    const double duration = Skottie_Animation_duration(animation);
    const double fps = Skottie_Animation_fps(animation);
    const float width = Skottie_Animation_width(animation);
    const float height = Skottie_Animation_height(animation);

    if (!check(duration > 0.0, "Skottie_Animation_duration > 0")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(fps > 0.0, "Skottie_Animation_fps > 0")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(width > 0.0f && height > 0.0f, "Skottie_Animation_size > 0")) {
        Skottie_Animation_release(animation);
        return false;
    }

    if (!check(Skottie_Animation_seek(animation, 0.0f), "Skottie_Animation_seek(0.0)")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(Skottie_Animation_seek(animation, 0.5f), "Skottie_Animation_seek(0.5)")) {
        Skottie_Animation_release(animation);
        return false;
    }
    if (!check(Skottie_Animation_seekFrameTime(animation, duration), "Skottie_Animation_seekFrameTime(duration)")) {
        Skottie_Animation_release(animation);
        return false;
    }

    reskia_canvas_t* canvas = SkCanvas_newWithSizeProps(128, 128, nullptr);
    if (!check(canvas != nullptr, "SkCanvas_newWithSizeProps")) {
        Skottie_Animation_release(animation);
        return false;
    }

    Skottie_Animation_render(animation, canvas, nullptr);
    Skottie_Animation_renderWithFlags(animation, canvas, nullptr, 0);

    SkCanvas_delete(canvas);
    Skottie_Animation_release(animation);
    return true;
}

}  // namespace

int main() {
    SkGraphics_Init();

    if (!smoke_skottie_minimal()) {
        return 1;
    }

    std::fprintf(stdout, "[skottie-smoke] PASS\n");
    return 0;
}
