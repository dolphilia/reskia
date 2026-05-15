#include <cstdio>
#include <cstring>

#include "capi/sk_canvas.h"
#include "capi/sk_graphics.h"
#include "capi/sk_size.h"
#include "capi/sk_skottie.h"
#include "capi/sk_string.h"
#include "handles/static_sk_size_t.h"

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
    const double in_point = Skottie_Animation_inPoint(animation);
    const double out_point = Skottie_Animation_outPoint(animation);
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
    if (!check(in_point == 0.0 && out_point == 60.0, "Skottie_Animation in/out points")) {
        Skottie_Animation_release(animation);
        return false;
    }
    reskia_string_t *version = Skottie_Animation_version(animation);
    if (!check(version != nullptr && SkString_equalsText(version, "5.7.4"), "Skottie_Animation_version")) {
        SkString_delete(version);
        Skottie_Animation_release(animation);
        return false;
    }
    SkString_delete(version);
    sk_size_t size_handle = Skottie_Animation_size(animation);
    auto *size = reinterpret_cast<reskia_size_t *>(static_sk_size_get_ptr(size_handle));
    if (!check(size != nullptr && SkSize_width(size) == 64.0f && SkSize_height(size) == 64.0f, "Skottie_Animation_size")) {
        static_sk_size_delete(size_handle);
        Skottie_Animation_release(animation);
        return false;
    }
    static_sk_size_delete(size_handle);

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
