#include "capi/sk_picture.h"
#include "capi/sk_picture_recorder.h"
#include "handles/static_sk_picture.h"
#include "handles/static_sk_rect.h"
#include "handles/static_sk_shader.h"

#include "include/core/SkRect.h"

#include <cstdio>
#include <cstdint>

namespace {

bool check(bool condition, const char *message) {
    if (!condition) {
        std::fprintf(stderr, "[picture-recorder-invalid-input-smoke] FAIL: %s\n", message);
        return false;
    }
    return true;
}

}  // namespace

int main() {
    SkPicture_release(nullptr);
    SkPicture_playback(nullptr, nullptr, nullptr);
    SkPicture_serializeToStream(nullptr, nullptr, nullptr);
    SkPicture_ref(nullptr);
    SkPicture_unref(nullptr);

    if (!check(SkPicture_cullRect(nullptr) == 0, "SkPicture_cullRect(nullptr)")) {
        return 1;
    }
    if (!check(SkPicture_uniqueID(nullptr) == 0, "SkPicture_uniqueID(nullptr)")) {
        return 2;
    }
    if (!check(SkPicture_serialize(nullptr, nullptr) == 0, "SkPicture_serialize(nullptr)")) {
        return 3;
    }
    if (!check(SkPicture_approximateOpCount(nullptr) == 0, "SkPicture_approximateOpCount(nullptr)")) {
        return 4;
    }
    if (!check(SkPicture_approximateBytesUsed(nullptr) == 0, "SkPicture_approximateBytesUsed(nullptr)")) {
        return 5;
    }
    if (!check(SkPicture_makeShader(nullptr, 0, 0, 0, nullptr, nullptr) == 0, "SkPicture_makeShader(nullptr)")) {
        return 6;
    }
    if (!check(SkPicture_makeShaderWithoutLocalMatrixAndTileRect(nullptr, 0, 0, 0) == 0, "SkPicture_makeShaderWithoutLocalMatrixAndTileRect(nullptr)")) {
        return 7;
    }
    if (!check(!SkPicture_unique(nullptr), "SkPicture_unique(nullptr)")) {
        return 8;
    }
    if (!check(SkPicture_MakeFromStream(nullptr, nullptr) == 0, "SkPicture_MakeFromStream(nullptr)")) {
        return 9;
    }
    if (!check(SkPicture_MakeFromData(nullptr, nullptr) == 0, "SkPicture_MakeFromData(nullptr)")) {
        return 10;
    }
    const uint8_t byte = 0;
    if (!check(SkPicture_MakeFromMemory(nullptr, 1, nullptr) == 0, "SkPicture_MakeFromMemory(null data)")) {
        return 11;
    }
    if (!check(SkPicture_MakeFromMemory(&byte, 0, nullptr) == 0, "SkPicture_MakeFromMemory(empty data)")) {
        return 12;
    }

    const sk_picture_t placeholder_handle = SkPicture_MakePlaceholder(0);
    auto *placeholder = static_cast<reskia_picture_t *>(static_sk_picture_get_ptr(placeholder_handle));
    if (!check(placeholder_handle != 0 && placeholder != nullptr, "SkPicture_MakePlaceholder(default rect)")) {
        return 13;
    }
    if (!check(SkPicture_uniqueID(placeholder) != 0, "SkPicture_uniqueID(valid)")) {
        static_sk_picture_delete(placeholder_handle);
        return 14;
    }
    const sk_rect_t cull_handle = SkPicture_cullRect(placeholder);
    if (!check(cull_handle != 0 && static_sk_rect_get_ptr(cull_handle) != nullptr, "SkPicture_cullRect(valid)")) {
        static_sk_picture_delete(placeholder_handle);
        return 15;
    }
    static_sk_rect_delete(cull_handle);

    if (!check(SkPicture_makeShaderWithoutLocalMatrixAndTileRect(placeholder, 99, 0, 0) == 0, "SkPicture_makeShader(invalid tile mode)")) {
        static_sk_picture_delete(placeholder_handle);
        return 16;
    }
    const sk_shader_t shader_handle = SkPicture_makeShaderWithoutLocalMatrixAndTileRect(placeholder, 0, 0, 0);
    if (!check(shader_handle != 0 && static_sk_shader_get_ptr(shader_handle) != nullptr, "SkPicture_makeShader(valid)")) {
        static_sk_picture_delete(placeholder_handle);
        return 17;
    }
    static_sk_shader_delete(shader_handle);
    SkPicture_ref(placeholder);
    SkPicture_unref(placeholder);
    static_sk_picture_delete(placeholder_handle);

    SkPictureRecorder_delete(nullptr);
    if (!check(SkPictureRecorder_beginRecording(nullptr, nullptr, 0) == nullptr, "SkPictureRecorder_beginRecording(nullptr)")) {
        return 18;
    }
    if (!check(SkPictureRecorder_beginRecordingWithBoundsAndFactory(nullptr, nullptr, nullptr) == nullptr, "SkPictureRecorder_beginRecordingWithBoundsAndFactory(nullptr)")) {
        return 19;
    }
    if (!check(SkPictureRecorder_beginRecordingWithSizeAndFactory(nullptr, 1.0f, 1.0f, nullptr) == nullptr, "SkPictureRecorder_beginRecordingWithSizeAndFactory(nullptr)")) {
        return 20;
    }
    if (!check(SkPictureRecorder_getRecordingCanvas(nullptr) == nullptr, "SkPictureRecorder_getRecordingCanvas(nullptr)")) {
        return 21;
    }
    if (!check(SkPictureRecorder_finishRecordingAsPicture(nullptr) == 0, "SkPictureRecorder_finishRecordingAsPicture(nullptr)")) {
        return 22;
    }
    if (!check(SkPictureRecorder_finishRecordingAsPictureWithCull(nullptr, nullptr) == 0, "SkPictureRecorder_finishRecordingAsPictureWithCull(nullptr)")) {
        return 23;
    }
    if (!check(SkPictureRecorder_finishRecordingAsDrawable(nullptr) == 0, "SkPictureRecorder_finishRecordingAsDrawable(nullptr)")) {
        return 24;
    }

    auto *recorder = SkPictureRecorder_new();
    if (!check(recorder != nullptr, "SkPictureRecorder_new()")) {
        return 25;
    }
    if (!check(SkPictureRecorder_getRecordingCanvas(recorder) == nullptr, "SkPictureRecorder_getRecordingCanvas(not recording)")) {
        SkPictureRecorder_delete(recorder);
        return 26;
    }
    SkRect bounds = SkRect::MakeWH(10.0f, 10.0f);
    auto *canvas = SkPictureRecorder_beginRecording(recorder, reinterpret_cast<const reskia_rect_t *>(&bounds), 0);
    if (!check(canvas != nullptr, "SkPictureRecorder_beginRecording(valid)")) {
        SkPictureRecorder_delete(recorder);
        return 27;
    }
    if (!check(SkPictureRecorder_getRecordingCanvas(recorder) == canvas, "SkPictureRecorder_getRecordingCanvas(recording)")) {
        SkPictureRecorder_delete(recorder);
        return 28;
    }
    const sk_picture_t picture_handle = SkPictureRecorder_finishRecordingAsPicture(recorder);
    if (!check(picture_handle != 0 && static_sk_picture_get_ptr(picture_handle) != nullptr, "SkPictureRecorder_finishRecordingAsPicture(valid)")) {
        SkPictureRecorder_delete(recorder);
        return 29;
    }
    static_sk_picture_delete(picture_handle);
    SkPictureRecorder_delete(recorder);

    auto *size_recorder = SkPictureRecorder_new();
    if (!check(size_recorder != nullptr, "SkPictureRecorder_new(size)")) {
        return 30;
    }
    if (!check(SkPictureRecorder_beginRecordingWithSizeAndFactory(size_recorder, -1.0f, 1.0f, nullptr) == nullptr, "SkPictureRecorder_beginRecordingWithSizeAndFactory(negative)")) {
        SkPictureRecorder_delete(size_recorder);
        return 31;
    }
    if (!check(SkPictureRecorder_beginRecordingWithSizeAndFactory(size_recorder, 1.0f, 1.0f, nullptr) != nullptr, "SkPictureRecorder_beginRecordingWithSizeAndFactory(valid)")) {
        SkPictureRecorder_delete(size_recorder);
        return 32;
    }
    const sk_picture_t cull_picture = SkPictureRecorder_finishRecordingAsPictureWithCull(size_recorder, reinterpret_cast<const reskia_rect_t *>(&bounds));
    if (!check(cull_picture != 0 && static_sk_picture_get_ptr(cull_picture) != nullptr, "SkPictureRecorder_finishRecordingAsPictureWithCull(valid)")) {
        SkPictureRecorder_delete(size_recorder);
        return 33;
    }
    static_sk_picture_delete(cull_picture);
    SkPictureRecorder_delete(size_recorder);
    return 0;
}
