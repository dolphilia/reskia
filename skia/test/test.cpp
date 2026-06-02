//
// Created by dolphilia on 2024/01/26.
//

#include "test.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <memory>
#include <vector>

#if defined(_WIN32) || defined(_WIN64)
#define _USE_MATH_DEFINES
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
//#include <dwrite.h>
#include <cmath>
#endif
#if defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#include <CoreText/CoreText.h>
#endif
//#include "include/ports/SkFontMgr_data.h"
//#include "include/ports/SkFontMgr_fontconfig.h"
//#include "include/ports/SkTypeface_fontations.h"
//#include "include/ports/SkFontMgr_directory.h"
#include "include/core/SkData.h"
#include "include/core/SkStream.h"
#include "include/core/SkSpan.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkFontArguments.h"
#include "capi/sk_canvas.h"
#include "capi/sk_paint.h"
#include "capi/sk_rect.h"
#include "capi/sk_surface.h"
#include "capi/sk_surfaces.h"
#include "capi/sk_image.h"
#include "capi/sk_data.h"
#include "capi/sk_stream.h"
#include "capi/sk_bitmap.h"
#include "capi/sk_file_w_stream.h"
#include "capi/sk_path.h"
#include "capi/sk_point.h"
#include "capi/sk_typeface_mac.h"
#include "handles/static_sk_rect.h"
#include "handles/static_sk_image_info.h"
#include "handles/static_sk_surface.h"
#include "capi/sk_image_info.h"
#include "capi/sk_text_blob.h"
#include "capi/sk_font.h"
#include "capi/sk_typeface.h"
#include "capi/sk_gradient_shader.h"
#include "capi/sk_perlin_noise_shader.h"
#include "capi/sk_font_mgr.h"
#include "capi/sk_font_mgr_fontconfig.h"
#include "capi/sk_images.h"
#include "capi/sk_stream_asset.h"
#include "capi/sk_r_rect.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "handles/static_sk_point_two.h"

static const reskia_image_info_t *get_image_info_ptr(sk_image_info_t image_info) {
    return reinterpret_cast<const reskia_image_info_t *>(static_sk_image_info_get_ptr(image_info));
}

static const reskia_image_t *get_image_ptr(sk_image_t image) {
    return reinterpret_cast<const reskia_image_t *>(static_sk_image_get_ptr(image));
}

static const reskia_rect_t *get_rect_ptr(sk_rect_t rect) {
    return reinterpret_cast<const reskia_rect_t *>(static_sk_rect_get_ptr(rect));
}

static const reskia_point_t *get_point_two_ptr(sk_point_two_t points) {
    return reinterpret_cast<const reskia_point_t *>(static_sk_point_two_get_ptr(points));
}

static bool file_exists(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == nullptr) {
        return false;
    }
    fclose(file);
    return true;
}

static constexpr reskia_paint_style_t kPaintFillStyle = 0;
static constexpr reskia_paint_style_t kPaintStrokeStyle = 1;
static constexpr reskia_text_blob_text_encoding_t kTextEncodingUtf8 = 0;
static constexpr reskia_gradient_shader_tile_mode_t kTileModeClamp = 0;
static constexpr reskia_paint_blend_mode_t kBlendModeScreen = 14;
static constexpr reskia_paint_blend_mode_t kBlendModeOverlay = 15;

/**
 * Draws a rectangle.
 */
UTEST(cskia, drawRect) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();

    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);

    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    reskia_paint_t *paint = SkPaint_new();
    SkPaint_setColor(paint,SK_ColorRED);
    int rect_key = SkRect_MakeXYWH(100, 100, 300, 300); // Rectangle position and size
    SkCanvas_drawRect(canvas, rect_key, paint);
    static_sk_rect_delete(rect_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    // free
    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint);
}

/**
 * Draws a star path.
 */
UTEST(cskia, drawPath) {
    int image_width = 500;
    int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    reskia_path_t *path = SkPath_new();
    float cx = (float)image_width / 2;
    float cy = (float)image_height / 2;
    float outerRadius = 100;
    float innerRadius  = 50;
    int numPoints = 5;
    const float kAngleStep = (2 * (float)M_PI) / (float)numPoints;
    const float kHalfAngleStep = kAngleStep / 2;
    SkPath_moveTo(path, cx + outerRadius, cy);
    for (int i = 1; i < numPoints * 2; ++i) {
        const float angle = kAngleStep * (float)i;
        const float radius = (i % 2 == 0) ? outerRadius : innerRadius;
        SkPath_lineTo(path, cx + radius * cos(angle), cy + radius * sin(angle));
    }
    SkPath_close(path);
    reskia_paint_t *paint = SkPaint_new();
    SkPaint_setColor(paint, SK_ColorYELLOW);
    SkPaint_setAntiAlias(paint, true);
    SkCanvas_drawPath(canvas, path, paint);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output2.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    // free
    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPath_delete(path);
    SkPaint_delete(paint);
}

/**
 * Rotates the canvas.
 */
UTEST(cskia, drawRect_rotate) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    SkCanvas_save(canvas);
    SkCanvas_translate(canvas, SkIntToScalar(128), SkIntToScalar(128));
    SkCanvas_rotate(canvas, SkIntToScalar(45));
    {
        int rect_key = SkRect_MakeXYWH(-90.5f, -90.5f, 181.0f, 181.0f);
        reskia_paint_t *paint = SkPaint_new();
        SkPaint_setColor(paint, SK_ColorBLUE);
        SkCanvas_drawRect(canvas, rect_key, paint);
        static_sk_rect_delete(rect_key);
        SkPaint_delete(paint);
    }
    SkCanvas_restore(canvas);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output3.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
}

/**
 * Draws text with an installed font on macOS.
 */
#if defined(__APPLE__)
UTEST(cskia, drawTextBlob_Installedfont) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    reskia_paint_t *paint1 = SkPaint_new();
    reskia_paint_t *paint2 = SkPaint_new();
    reskia_paint_t *paint3 = SkPaint_new();

    SkPaint_setAntiAlias(paint1, true);
    SkPaint_setColor(paint1, SkColorSetRGB(255, 0, 0));
    SkPaint_setStyle(paint1, kPaintFillStyle);

    SkPaint_setAntiAlias(paint2, true);
    SkPaint_setColor(paint2, SkColorSetRGB(0, 136, 0));
    SkPaint_setStyle(paint2, kPaintStrokeStyle);
    SkPaint_setStrokeWidth(paint2, SkIntToScalar(3));

    SkPaint_setAntiAlias(paint3, true);
    SkPaint_setColor(paint3, SkColorSetRGB(136, 136, 136));

    CFStringRef fontName = CFStringCreateWithCString(NULL, "Helvetica", kCFStringEncodingUTF8);
    CGFloat fontSize = 12.0;
    CTFontRef fontRef = CTFontCreateWithName(fontName, fontSize, NULL);
    CFRelease(fontName);

    int typeface_key = Mac_SkMakeTypefaceFromCTFont(reinterpret_cast<const reskia_ct_font_t *>(fontRef));
    reskia_font_t *font = SkFont_newWithTypefaceSizeScaleXSkewX(typeface_key, 64.0f, 1.0f, 0.0f);

    int textblob_key = SkTextBlob_MakeFromString("Skia!", font, kTextEncodingUtf8);
    SkCanvas_clearColor(canvas, SK_ColorWHITE);

    SkFont_setTypeface(font, typeface_key);
    SkCanvas_drawTextBlob(canvas, textblob_key, 1.0f, 64.0f, paint1);
    static_sk_text_blob_delete(textblob_key);
    static_sk_typeface_delete(typeface_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output4.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint1);
    SkPaint_delete(paint2);
    SkPaint_delete(paint3);
    SkFont_delete(font);
    CFRelease(fontRef);
}
#endif

// Draws text with an installed font on Windows.
#if defined(_WIN32) || defined(_WIN64)
/*
#include "include/core/SkCanvas.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkImageInfo.h"
#include "include/core/SkSurface.h"
#include "include/core/SkTypeface.h"
#include "include/core/SkFont.h"
#include "include/core/SkPaint.h"
#include "include/utils/SkPaintFilterCanvas.h"
#include "include/utils/SkTextUtils.h"
#include "src/ports/SkTypeface_win_dw.h"
//#include <wrl.h>
//#include <string>
//using Microsoft::WRL::ComPtr;
UTEST(cskia, drawTextBlob_Installedfont) {
    std::wstring text = L"Hello, Skia!";
    std::wstring fontFamily = L"Arial";
    float fontSize = 50.0f;

    const int image_width = 500;
    const int image_height = 500;
    SkBitmap* bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkImageInfo * imageInfoPtr = static_sk_image_info_get_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    SkCanvas *canvas = SkCanvas_newFromBitmap(bitmap);

    SkFontArguments fontArgs;
    fontArgs.setCollectionIndex(0); // Default is 0, if the font is part of a collection.
    // fontArgs.setVariationDesignPosition(variation, count); // Use if you have specific variation settings.
    //fontArgs.setWeight(500); // Set a specific weight if needed.

    auto typeface_key = static_sk_typeface_make(DWriteFontTypeface::MakeFromStream(SkStream::MakeFromFile("Mplus1-Regular.ttf"),fontArgs));
    SkFont* font = SkFont_newWithTypefaceSizeScaleXSkewX(typeface_key, 64.0f, 1.0f, 0.0f);

    int textblob_key = SkTextBlob_MakeFromString("Skia!", font, SkTextEncoding::kUTF8);
    SkCanvas_clearColor(canvas, SK_ColorWHITE);

    SkPaint *paint1 = SkPaint_new();

    SkPaint_setAntiAlias(paint1, true);
    SkPaint_setColor(paint1, SkColorSetRGB(255, 0, 0));
    SkPaint_setStyle(paint1, kPaintFillStyle);

    SkFont_setTypeface(font, typeface_key);
    SkCanvas_drawTextBlob(canvas, textblob_key, 1.0f, 64.0f, paint1);
    static_sk_text_blob_delete(textblob_key);

    // Set up Skia paint
    //SkPaint paint;
    //paint.setAntiAlias(true);
    //paint.setColor(SK_ColorBLACK);

    // Draw the text
    //SkFont font(tf, fontSize);
    //canvas->drawSimpleText(text.c_str(), text.size(), SkTextEncoding::kUTF16, 100, 100, font, paint);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output4.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
}
 */
#endif

/**
 * Draws text with an external font on macOS.
 */
#if defined(__APPLE__)
UTEST(cskia, drawTextBlob_fromFile) {
    if (!file_exists("Mplus1-Regular.ttf")) {
        UTEST_SKIP("Mplus1-Regular.ttf is not available");
    }

    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    reskia_paint_t *paint1 = SkPaint_new();
    reskia_paint_t *paint2 = SkPaint_new();
    reskia_paint_t *paint3 = SkPaint_new();

    SkPaint_setAntiAlias(paint1, true);
    SkPaint_setColor(paint1, SkColorSetRGB(255, 0, 0));
    SkPaint_setStyle(paint1, kPaintFillStyle);

    SkPaint_setAntiAlias(paint2, true);
    SkPaint_setColor(paint2, SkColorSetRGB(0, 136, 0));
    SkPaint_setStyle(paint2, kPaintStrokeStyle);
    SkPaint_setStrokeWidth(paint2, SkIntToScalar(3));

    SkPaint_setAntiAlias(paint3, true);
    SkPaint_setColor(paint3, SkColorSetRGB(136, 136, 136));


    // Specify the font file path.
    CFStringRef fontPath = CFStringCreateWithCString(kCFAllocatorDefault, "Mplus1-Regular.ttf", kCFStringEncodingUTF8);
    CFURLRef fontURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, fontPath, kCFURLPOSIXPathStyle, false);
    CFRelease(fontPath); // Release the CFStringRef.

    // Create font descriptors.
    CFArrayRef fontDescriptors = CTFontManagerCreateFontDescriptorsFromURL(fontURL);
    CFRelease(fontURL); // Release the CFURLRef.

    // Get the first font descriptor from the array.
    CTFontDescriptorRef fontDescriptor = (CTFontDescriptorRef)CFArrayGetValueAtIndex(fontDescriptors, 0);

    // Create a CTFont from the font descriptor.
    CTFontRef theCTFont = CTFontCreateWithFontDescriptor(fontDescriptor, 12.0, NULL);


    int typeface_key = Mac_SkMakeTypefaceFromCTFont(reinterpret_cast<const reskia_ct_font_t *>(theCTFont));
    reskia_font_t *font = SkFont_newWithTypefaceSizeScaleXSkewX(typeface_key, 64.0f, 1.0f, 0.0f);

    int textblob_key = SkTextBlob_MakeFromString("Skia!", font, kTextEncodingUtf8);
    SkCanvas_clearColor(canvas, SK_ColorWHITE);

    SkFont_setTypeface(font, typeface_key);
    SkCanvas_drawTextBlob(canvas, textblob_key, 1.0f, 64.0f, paint1);
    static_sk_text_blob_delete(textblob_key);
    static_sk_typeface_delete(typeface_key);


    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output5.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint1);
    SkPaint_delete(paint2);
    SkPaint_delete(paint3);
    SkFont_delete(font);
    CFRelease(theCTFont);
    CFRelease(fontDescriptors);
}
#endif

/**
 * Deprecated: checks the text drawing API path with an empty typeface.
 */
UTEST(cskia, SkTypeface_MakeEmpty) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    reskia_paint_t *paint1 = SkPaint_new();
    reskia_paint_t *paint2 = SkPaint_new();
    reskia_paint_t *paint3 = SkPaint_new();

    SkPaint_setAntiAlias(paint1, true);
    SkPaint_setColor(paint1, SkColorSetRGB(255, 0, 0));
    SkPaint_setStyle(paint1, kPaintFillStyle);

    SkPaint_setAntiAlias(paint2, true);
    SkPaint_setColor(paint2, SkColorSetRGB(0, 136, 0));
    SkPaint_setStyle(paint2, kPaintStrokeStyle);
    SkPaint_setStrokeWidth(paint2, SkIntToScalar(3));

    SkPaint_setAntiAlias(paint3, true);
    SkPaint_setColor(paint3, SkColorSetRGB(136, 136, 136));

    int typeface_key = SkTypeface_MakeEmpty();
    reskia_font_t *font = SkFont_newWithTypefaceSizeScaleXSkewX(typeface_key, 64.0f, 1.0f, 0.0f);

    int textblob_key = SkTextBlob_MakeFromString("Skia!", font, kTextEncodingUtf8);
    SkCanvas_clearColor(canvas, SK_ColorWHITE);

    SkFont_setTypeface(font, typeface_key);
    SkCanvas_drawTextBlob(canvas, textblob_key, 1.0f, 64.0f, paint1);
    static_sk_text_blob_delete(textblob_key);
    static_sk_typeface_delete(typeface_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output6.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint1);
    SkPaint_delete(paint2);
    SkPaint_delete(paint3);
    SkFont_delete(font);
}

/**
 * Draws a gradient.
 */
//#ifdef __MACOS__
UTEST(cskia, SkGradientShader) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    auto two = static_sk_point_two_make_float(0,0,500,500);
//    auto p1 = SkPoint_Make(0.0f, 0.0f);
//    auto p2 = SkPoint_Make(500.0f, 500.0f);
//    SkPoint point1 = static_sk_point_get(p1);
//    SkPoint point2 = static_sk_point_get(p2);
//    SkPoint points[2] = {point1, point2};
    SkColor colors[2] = {SK_ColorBLUE, SK_ColorYELLOW};
    reskia_paint_t *paint = SkPaint_new();
    int shader_key = SkGradientShader_MakeLinear(get_point_two_ptr(two), colors, nullptr, 2, kTileModeClamp, 0, nullptr);
    SkPaint_setShader(paint, shader_key);
    SkCanvas_drawPaint(canvas, paint);
    static_sk_shader_delete(shader_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void *bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int) SkBitmap_rowBytes(bitmap);
    stbi_write_png("output7.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int) bitmap_row_bytes);

    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint);
}
//#endif

/**
 * Draws fractal noise.
 */
UTEST(cskia, FractalNoise) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    SkCanvas_clearColor(canvas, SK_ColorWHITE);
    reskia_paint_t *paint = SkPaint_new();
    int shader_key = SkPerlinNoiseShader_MakeFractalNoise(0.05f, 0.05f, 4, 0.0f, NULL);
    SkPaint_setShader(paint, shader_key);
    SkCanvas_drawPaint(canvas, paint);
    static_sk_shader_delete(shader_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void *bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output8.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int) bitmap_row_bytes);

    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint);
}

/**
 * Loads and draws an image.
 */

UTEST(cskia, LoadImage) {
    if (!file_exists("miga.png")) {
        UTEST_SKIP("miga.png is not available");
    }

    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);
    SkCanvas_clearColor(canvas, SK_ColorWHITE);

    // Load a PNG image.
    int image_file_id = SkStream_MakeFromFile("miga.png");
    auto *stream_asset = reinterpret_cast<reskia_stream_asset_t *>(static_sk_stream_asset_get_ptr(image_file_id));
    size_t size = SkStreamAsset_getLength(stream_asset);
    int image_data_id = SkData_MakeFromStream(reinterpret_cast<reskia_stream_t *>(stream_asset), size);
    int image_id = SkImages_DeferredFromEncodedData(image_data_id);
    SkCanvas_drawImagePtr(canvas, get_image_ptr(image_id), 0, 0);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void *bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output9.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int) bitmap_row_bytes);

    static_sk_image_delete(image_id);
    static_sk_data_delete(image_data_id);
    static_sk_stream_asset_delete(image_file_id);
    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
}

/**
 * Draws a circle.
 */
UTEST(cskia, drawRRect) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    reskia_paint_t *paint = SkPaint_new();
    SkPaint_setColor(paint,SK_ColorRED);
    int rect_key = SkRect_MakeXYWH(100, 100, 300, 300); // Rectangle position and size
    reskia_r_rect_t *rrect = SkRRect_new();
    const reskia_rect_t *rect = get_rect_ptr(rect_key);
    SkRRect_setOval(rrect, rect);
    SkRRect_offset(rrect, 40, 60);
    SkCanvas_drawRRect(canvas, rrect, paint);
    SkRRect_delete(rrect);
    static_sk_rect_delete(rect_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output10.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    // free
    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint);
}

/**
 * Draws a rounded rectangle.
 */
UTEST(cskia, drawRoundRect) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    reskia_paint_t *paint = SkPaint_new();
    SkPaint_setColor(paint,SK_ColorRED);
    int rect_key = SkRect_MakeXYWH(100, 100, 300, 300); // Rectangle position and size
    const reskia_rect_t *rect = get_rect_ptr(rect_key);
    SkCanvas_drawRoundRect(canvas, rect, 10, 10, paint);
    static_sk_rect_delete(rect_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output11.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    // free
    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint);
}

/**
 * Draws rectangles.
 */
UTEST(cskia, BlendMode) {
    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);

    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);
    reskia_paint_t *paint = SkPaint_new();

    SkPaint_setBlendMode(paint, kBlendModeOverlay);
    SkPaint_setColor(paint,SK_ColorRED);
    int rect_key = SkRect_MakeXYWH(50, 50, 150, 150); // Rectangle position and size
    SkCanvas_drawRect(canvas, rect_key, paint);

    SkPaint_setBlendMode(paint, kBlendModeScreen);
    SkPaint_setColor(paint,SK_ColorBLUE);
    rect_key = SkRect_MakeXYWH(100, 100, 200, 200); // Rectangle position and size
    SkCanvas_drawRect(canvas, rect_key, paint);

    static_sk_rect_delete(rect_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output12.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    // free
    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint);
}

/**
 * Draws an image loaded through stb_image.
 */
UTEST(cskia, stb_image) {
    if (!file_exists("miga.png")) {
        UTEST_SKIP("miga.png is not available");
    }

    const int image_width = 500;
    const int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);
    reskia_paint_t *paint = SkPaint_new();

    // Select the PNG file to load.
    const char* filePath = "miga.png";

    // Load the PNG file as binary image data.
    int width, height, channels;
    // Load image data with STB_IMAGE.
    unsigned char* data = stbi_load(filePath, &width, &height, &channels, STBI_rgb_alpha);
    if (!data) {
        std::cerr << "Error loading PNG file: " << stbi_failure_reason() << std::endl;
        exit(1);
    }

    // Convert image data to an SkImage for Skia.
    sk_image_info_t image_info = SkImageInfo_Make(width, height, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kUnpremul_SkAlphaType);
    const reskia_image_info_t *image_info_ptr = get_image_info_ptr(image_info);

    reskia_bitmap_t *image_bitmap = SkBitmap_new();
    SkBitmap_allocPixels_withInfo(image_bitmap, image_info_ptr);
    memcpy(SkBitmap_getPixels(image_bitmap), data, width * height * 4);
    //SkSamplingOptions
    sk_image_t image = SkBitmap_asImage(image_bitmap);
    stbi_image_free(data);

    SkCanvas_drawImage(canvas, image, 0, 0);
    SkCanvas_drawImage(canvas, image, 50, 0);



    //canvas->drawBitmap(bitmap, 100, 100, &paint); // Draw at position (100, 100)

//    SkPaint_setBlendMode(paint, SkBlendMode::kOverlay);
//    SkPaint_setColor(paint,SK_ColorRED);
//    int rect_key = SkRect_MakeXYWH(50, 50, 150, 150); // Rectangle position and size
//    SkCanvas_drawRect(canvas, rect_key, paint);
//
//    SkPaint_setBlendMode(paint, SkBlendMode::kScreen);
//    SkPaint_setColor(paint,SK_ColorBLUE);
//    rect_key = SkRect_MakeXYWH(100, 100, 200, 200); // Rectangle position and size
//    SkCanvas_drawRect(canvas, rect_key, paint);
//
//    static_sk_rect_delete(rect_key);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output13.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    // free
    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPaint_delete(paint);
}

UTEST(cskia, SkColors_SkPoints) {
    struct point_t {
        float fx;
        float fy;
    };
    point_t point = {0,0};
    SkPoint sk_point = SkPoint::Make(point.fx, point.fy);
    point_t point2 = { 500, 500};
    SkPoint sk_point2 = SkPoint::Make(point2.fx, point2.fy);
    SkPoint points[2] = {sk_point, sk_point2};
}

/**
 * Draws a curved path.
 */
UTEST(cskia, drawPath2) {
    int image_width = 500;
    int image_height = 500;
    reskia_bitmap_t *bitmap = SkBitmap_new();
    sk_image_info_t imageInfo = SkImageInfo_Make(500, 500, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    const reskia_image_info_t *imageInfoPtr = get_image_info_ptr(imageInfo);
    SkBitmap_allocPixels_withInfo(bitmap, imageInfoPtr);
    reskia_canvas_t *canvas = SkCanvas_newFromBitmap(bitmap);

    reskia_path_t *path = SkPath_new();
    //SkPath_moveTo(path, 100, 100);
    //SkPath_quadTo(path, 150, 50, 200, 100); // Add a quadratic Bezier curve.
    //SkPath_cubicTo(path, 250, 150, 300, 50, 350, 100); // Add a cubic Bezier curve.
    //SkPath_lineTo(path, 400, 200);     // Add a straight line.
    SkPath_moveTo(path, 200, 100);      // Start point
    SkPath_lineTo(path, 400, 100);      // Top edge
    SkPath_arcToTangent(path, 450, 100, 450, 150, 50); // Round the upper-right corner.
    SkPath_lineTo(path, 450, 250);      // Right edge
    SkPath_arcToTangent(path, 450, 300, 400, 300, 50); // Round the lower-right corner.
    SkPath_lineTo(path, 250, 300);      // Bottom edge
    SkPath_lineTo(path, 220, 350);      // Callout point
    SkPath_lineTo(path, 200, 300);      // Callout point
    SkPath_lineTo(path, 150, 300);      // Bottom edge
    SkPath_arcToTangent(path, 100, 300, 100, 250, 50); // Round the lower-left corner.
    SkPath_lineTo(path, 100, 150);      // Left edge
    SkPath_arcToTangent(path, 100, 100, 150, 100, 50); // Round the upper-left corner.
    SkPath_close(path);

    reskia_paint_t *paint = SkPaint_new();
    SkPaint_setAntiAlias(paint, true);

    // Fill
    SkPaint_setColor(paint,SK_ColorYELLOW);
    SkPaint_setStyle(paint, kPaintFillStyle);
    SkCanvas_drawPath(canvas, path, paint);

    // Stroke
    SkPaint_setColor(paint, SK_ColorBLACK);
    SkPaint_setStyle(paint, kPaintStrokeStyle);
    SkPaint_setStrokeWidth(paint, 4);
    SkCanvas_drawPath(canvas, path, paint);

    int bitmap_width = SkBitmap_width(bitmap);
    int bitmap_height = SkBitmap_height(bitmap);
    void* bitmap_pixels = SkBitmap_getPixels(bitmap);
    int bitmap_row_bytes = (int)SkBitmap_rowBytes(bitmap);
    stbi_write_png("output14.png", bitmap_width, bitmap_height, 4, bitmap_pixels, (int)bitmap_row_bytes);

    // free
    SkBitmap_delete(bitmap);
    SkCanvas_delete(canvas);
    SkPath_delete(path);
    SkPaint_delete(paint);
}

UTEST_MAIN()
