#include "capi/sk_android_codec.h"
#include "capi/sk_annotation.h"

#include "include/codec/SkCodec.h"

#include <cstdio>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[annotation-android-codec-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    bool ok = true;

    SkAnnotation_SkAnnotateLinkToDestination(nullptr, nullptr, nullptr);
    SkAnnotation_SkAnnotateNamedDestination(nullptr, nullptr, nullptr);
    SkAnnotation_SkAnnotateRectWithURL(nullptr, nullptr, nullptr);

    SkAndroidCodec_delete(nullptr);
    ok &= check(SkAndroidCodec_getInfo(nullptr) == nullptr, "android codec getInfo null");
    ok &= check(SkAndroidCodec_getICCProfile(nullptr) == nullptr, "android codec getICCProfile null");
    ok &= check(SkAndroidCodec_getEncodedFormat(nullptr) == -1, "android codec getEncodedFormat null");
    ok &= check(SkAndroidCodec_computeOutputColorType(nullptr, 0) == -1, "android codec computeOutputColorType null");
    ok &= check(SkAndroidCodec_computeOutputAlphaType(nullptr, false) == -1, "android codec computeOutputAlphaType null");
    ok &= check(SkAndroidCodec_computeOutputColorSpace(nullptr, 0, 0) == 0, "android codec computeOutputColorSpace null");
    ok &= check(SkAndroidCodec_computeSampleSize(nullptr, nullptr) == 0, "android codec computeSampleSize null");
    ok &= check(SkAndroidCodec_getSampledDimensions(nullptr, 1) == 0, "android codec getSampledDimensions null");
    ok &= check(SkAndroidCodec_getSampledDimensions(nullptr, 0) == 0, "android codec getSampledDimensions invalid sampleSize");
    ok &= check(!SkAndroidCodec_getSupportedSubset(nullptr, nullptr), "android codec getSupportedSubset null");
    ok &= check(SkAndroidCodec_getSampledSubsetDimensions(nullptr, 1, nullptr) == 0, "android codec getSampledSubsetDimensions null");
    ok &= check(SkAndroidCodec_getSampledSubsetDimensions(nullptr, 0, nullptr) == 0, "android codec getSampledSubsetDimensions invalid sampleSize");
    ok &= check(SkAndroidCodec_getAndroidPixels(nullptr, nullptr, nullptr, 0, nullptr) == SkCodec::kInvalidParameters, "android codec getAndroidPixels null");
    ok &= check(SkAndroidCodec_getAndroidPixels_withoutOptions(nullptr, nullptr, nullptr, 0) == SkCodec::kInvalidParameters, "android codec getAndroidPixels_withoutOptions null");
    ok &= check(SkAndroidCodec_getPixels(nullptr, nullptr, nullptr, 0) == SkCodec::kInvalidParameters, "android codec getPixels null");
    ok &= check(SkAndroidCodec_codec(nullptr) == nullptr, "android codec codec null");
    sk_stream_t out_stream = 123;
    ok &= check(SkAndroidCodec_getAndroidGainmap(nullptr, nullptr, &out_stream) == RESKIA_STATUS_INVALID_ARGUMENT, "android codec gainmap invalid args");
    ok &= check(SkAndroidCodec_MakeFromCodec(0) == 0, "android codec MakeFromCodec handle 0");
    ok &= check(SkAndroidCodec_MakeFromStream(0, nullptr) == 0, "android codec MakeFromStream handle 0");
    ok &= check(SkAndroidCodec_MakeFromData(0, nullptr) == 0, "android codec MakeFromData handle 0");

    return ok ? 0 : 1;
}
