# Phase 23 GPU Provider / Async / Allocator Design

作成時刻: 2026-05-21 14:09:24 JST

## Scope

Phase 22 で header-only / local value wrapper は `include/gpu` の残行から概ね取り除いた。Phase 23 では、残る GPU 行を直接 C ABI に出せるものと、callback owner / async result / platform allocator / optional backend guard が必要なものへ切り分ける。

Phase 23B finish callback 反映後の matrix は `covered 2793`、`missing 45`、`na 171`、`include/gpu missing 44`、`modules/svg missing 1`。GPU の残りは以下の 5 系統に分かれる。

| bucket | rows | decision |
| --- | ---: | --- |
| Graphite recording / async readback / image provider | 13 | Phase 23B 以降で dedicated design + bridge。callback lifetime と GPU queue ownership を固定するまで missing 維持。 |
| Ganesh external texture / shader error callback | 6 | Phase 23C で concrete C++ bridge 候補。abstract hook そのものは direct method としては公開しない。 |
| GL interface / extension loader | 13 | Phase 23D。function table と loader callback owner が必要。`GrGLExtensions` の linked implementation 追加も同時判断。 |
| Vulkan / Metal allocator | 14 | Phase 23E。native allocator は backend-specific optional provider。portable C ABI では default 実装不可。 |
| Vulkan value / extension structs | 10 | Phase 23A で optional Vulkan backend guard として `na` に分類済み。現行 portable build は Vulkan headers が無いため、実装は Vulkan build target 作成後。 |

## Ownership Rules

- Callback owner は C-side `user_data` と `release_proc` を持つ owned handle にする。Skia object に渡した後も C bridge が owner を保持し、Skia 側 destruction または explicit release で一度だけ `release_proc` を呼ぶ。
- Async callback は completion thread が呼び出し元 thread と一致しない前提にする。callback payload の pixel memory / image handle / status は callback 中だけ borrowed にせず、必要なら owned result object に materialize する。
- Recorder / Recording / Context の関係は single-owner に寄せる。`Recorder::snap` は `std::unique_ptr<Recording>` transfer なので、C ABI では `Graphite_Recording_*` owned handle を先に作る。
- Borrowed canvas は lifetime が短い。`Recorder::makeDeferredCanvas` は borrowed `SkCanvas*` を返す場合でも、validity を "until next snap or recorder release" と明記する。
- Backend allocator は Metal/Vulkan runtime type と device lifetime に依存する。portable fallback は作らず、backend feature guard と optional build target を前提にする。

## Row Decisions

### Phase 23A: Optional Vulkan Value Guard

対象:

- `include/gpu/graphite/vk/VulkanGraphiteTypes.h`
- `include/gpu/vk/GrVkTypes.h`
- `include/gpu/vk/VulkanTypes.h`
- `include/gpu/vk/VulkanExtensions.h` の default / `hasExtension`

判断:

- 現行 GPU build は `include/third_party/vulkan/vulkan/vulkan_core.h` が無いため、native Vulkan value wrapper を compile できない。
- Dawn と同じく、Vulkan build target と header availability が揃うまでは portable C ABI coverage から外す。
- `public-api-phase-23-gpu-provider-overrides.csv` で 10 行を `na` に分類済み。
- `VulkanExtensions::init` は `VulkanGetProc` callback を受けるが、Vulkan native types が必要なため optional Vulkan backend guard 側に含めた。

### Phase 23B: Graphite Recording And Async Readback

対象:

- `Context::insertRecording`
- `Context::asyncRescaleAndReadPixels*`
- `Recorder::snap`
- `Recorder::addFinishInfo`
- `Recorder::makeDeferredCanvas`
- `Recorder::clientImageProvider`
- `ImageProvider::findOrCreate`

実装順:

1. `Graphite_Recording` owned handle: `Recorder::snap` の戻り値を受ける最小 wrapper。実装済み。
2. `Graphite_Context_insertRecording` wrapper: caller-owned recording を消費せず、C++ 側で `InsertRecordingInfo` 中だけ borrowed にする。実装済み。
3. Finish callback: `InsertFinishInfo` owner handle と result enum callback。recorder destruction / snap / insert failure の release timing を smoke で確認する。
4. Async readback: image/surface overloadを分け、result payload は callback-scoped view ではなく owned `reskia_async_read_result_t` にする。
5. ImageProvider: `RecorderOptions` に provider owner を保持させる setter を追加してから `clientImageProvider` borrowed query を扱う。

`makeDeferredCanvas` は deferred canvas の lifetime が recorder/snap に強く依存するため、上記 1-2 の後に扱う。

実装済み API:

- `Graphite_Recorder_snap`: `std::unique_ptr<Recording>` を owned `reskia_graphite_recording_t*` として返す。
- `Graphite_Recording_delete`: owned recording を破棄する。
- `Graphite_Context_insertRecording`: recording は borrowed。callback / semaphore / target surface / target texture state を指定しない最小 `InsertRecordingInfo` だけを扱う。
- `Graphite_Recorder_addFinishInfo`: C callback と `user_data` を C++ bridge context に保持し、Skia の finished callback 発火時に `release_proc` を一度だけ呼ぶ。
- `Graphite_Context_asyncRescaleAndReadPixelsFromImage` / `FromSurface`: `SkImage` / `SkSurface` async readback と同じ `reskia_async_read_pixels_callback_t` bridge を使う。
- `Graphite_Context_asyncRescaleAndReadPixelsYUV420FromImage` / `FromSurface`: `SkYUVColorSpace`、optional `sk_color_space_t`、`sk_i_size_t` を検証し、既存 async result wrapper を使う。
- `Graphite_Context_asyncRescaleAndReadPixelsYUVA420FromImage` / `FromSurface`: YUV420 と同じ callback/lifetime policy を使う。
- `Graphite_Recorder_clientImageProvider`: recorder-owned provider を borrowed opaque pointer として返す。C ABI は provider ownership を受け取らない。
- `Graphite_Recorder_makeDeferredCanvas`: `SkImageInfo` と valid `TextureInfo` を受け取り、次回 `snap` または recorder release まで有効な borrowed `reskia_canvas_t*` を返す。

未実装の `InsertRecordingInfo` fields:

- `fTargetSurface`
- `fTargetTranslation`
- `fTargetTextureState`
- wait/signal semaphores
- `Context::insertRecording` 側の finished callback

これらは target/deferred-canvas/finish callback design として Phase 23B continuation に残す。

### Phase 23C: Ganesh External Texture And Shader Error Handler

対象:

- `ShaderErrorHandler::compileError`
- `GrExternalTexture`
- `GrExternalTextureGenerator`

判断:

- abstract virtual method を単独 C function としては公開しない。
- `ShaderErrorHandler` は `GrContextOptions` へ owned handler を設定する API とセットで意味を持つ。`GrContextOptions_setShaderErrorHandler` を Phase 23C の実装候補にする。
- `GrExternalTextureGenerator` は `SkImages::DeferredFromTextureGenerator` とセットで公開する。bridge は `generateExternalTexture` callback が `GrBackendTexture` owned copy を返し、`dispose` callback を必ず持つ形にする。

2026-05-21 update:

- `ShaderErrorHandler` は `ShaderErrorHandler_new` / `ShaderErrorHandler_delete` / `ShaderErrorHandler_compileError` と `GrContextOptions_setShaderErrorHandler` で実装済み。handler は caller-owned、`GrContextOptions` は borrowed pointer を保持する。delete 時に `release_proc` を一度だけ呼ぶ。
- `GrExternalTextureGenerator` は `SkImages::DeferredFromTextureGenerator` と `GrTextureGenerator` ownership を含むため、引き続き dedicated bridge 待ち。

### Phase 23D: GL Interface And Extension Loader

対象:

- `GrGLExtensions::init` / `has` / `remove` / `add` / `dumpJSON`
- `GrGLInterface` constructor / validate / checkError / checkAndResetOOMed / suppressErrorLogging / hasExtension / abandon

現状:

- Phase 22 で `GrGLExtensions` default / `swap` / `isInitialized` / `reset` は追加済み。
- `GrGLExtensions::copy` / `has` / `remove` / `add` は header 宣言のみで、この build の linked objects に `GrGLExtensions.cpp` が入っていないため未解決 symbol になる。

判断:

- GL extension string-set helperを実装するなら、CMake に `src/gpu/ganesh/gl/GrGLExtensions.cpp` を含める必要がある。
- `GrGLInterface` は function table の owner と platform loader policy がないと安全に初期化できない。default local objectだけを出しても使い道が薄く、`checkError` などは function pointer 未設定時の振る舞いを固定する必要がある。
- Phase 23D では先に `reskia_gr_gl_function_loader_t` design を置く。実装は GL backend smoke を用意してから行う。

2026-05-21 update:

- `GrGLExtensions::init` / `has` / `remove` / `add` / `dumpJSON` と `GrGLInterface` 8 行は `public-api-phase-23-gpu-provider-overrides.csv` で `na` に分類済み。`GrGLExtensions.cpp` link inclusion、`SkJSONWriter` ownership、GL function table owner、platform loader policy をまとめる GL loader bridge まで portable C ABI coverage から外す。

### Phase 23E: Vulkan / Metal Memory Allocator

対象:

- `VulkanMemoryAllocator`
- `MtlMemoryAllocator`

判断:

- どちらも native backend object の allocator provider で、default fallback がない。
- C ABI で出す場合は concrete bridge class と callback table が必要。
- Vulkan は allocation id / mapped pointer / flush range の lifetime、Metal は `id<MTLBuffer>` / `id<MTLTexture>` と `MtlAlloc` refcount を明記する必要がある。
- 現行 portable build では `na` 候補。optional backend target が整った後に実装する。

2026-05-21 update:

- `VulkanMemoryAllocator` 12 行は `public-api-phase-23-gpu-provider-overrides.csv` で `na` に分類済み。Vulkan native handle / enum / allocator memory object に依存し、portable C ABI では default provider を作らない。
- `MtlMemoryAllocator` 2 行は `public-api-phase-23-gpu-provider-overrides.csv` で `na` に分類済み。Metal native object と Objective-C lifetime が必要なため、optional Metal allocator bridge まで portable C ABI coverage から外す。

## Next Phase Split

| next | work |
| --- | --- |
| Phase 23A | Vulkan-only value rows を optional backend guard として override に反映する。 |
| Phase 23B | `Graphite_Recording` owned handle と `Context::insertRecording` wrapper の実装可否を調査する。 |
| Phase 23C | `ShaderErrorHandler` / `GrExternalTextureGenerator` callback bridge の API skeleton を設計する。 |
| Phase 23D | GL loader callback と `GrGLExtensions.cpp` link inclusion の方針を決める。 |
| Phase 23E | Vulkan / Metal allocator は optional backend provider として、実装しない row を `na` にするか Phase 25 に送る。 |

## Immediate Recommendation

次に進めるなら Phase 23A が最も安全。現行 build で compile 不能な Vulkan value rows を optional backend guard として明示すれば、Phase 23B 以降の callback/provider 行だけが GPU の実装候補として残る。
