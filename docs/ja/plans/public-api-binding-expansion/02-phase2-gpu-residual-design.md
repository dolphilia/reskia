# Phase 2 GPU Residual Design

- 作成日: 2026-05-14
- 作業開始時刻: 2026-05-14 21:07:02 JST
- 対象: Phase 2 の GPU C API 残件整理、`GrSurfaceCharacterization`、backend-specific ABI 境界

## 目的

Phase 2 で低リスクな `GrDirectContext` query/cache/flush と `GrBackendFormat` / `GrBackendTexture` / `GrBackendRenderTarget` value wrapper を追加した後に残る GPU API を、次に実装できる単位へ分解する。

この文書は、`public-api-gpu-missing-triage.csv` の P1/P2 残件を以下へ分類するための基準である。

- Phase 2B: 追加実装してよい低リスク API
- Phase 2C: wrapper 設計を先に固定する API
- Phase 2D: backend-specific ABI 設計後に実装する API
- Phase 5A: callback / ownership foundation 待ち API

## Phase 2B: 追加実装候補

Phase 2B は、既存の C API 型または今回追加した backend wrapper だけで安全に表現できるものを対象にする。

候補:

- `GrDirectContext::MakeMock`
  - `GrMockOptions` wrapper を追加し、native GPU なしの Ganesh smoke を作れるようにする。
  - `GrMockOptions` の config option 配列を C ABI に全展開する前に、default options + scalar query/set の最小 API から始める。
- `GrDirectContext::createBackendTexture` の no-callback allocation overload
  - `width`, `height`, `GrBackendFormat` または `SkColorType`, `Mipmapped`, `Renderable`, `Protected`, optional label。
  - 戻り値は owned `reskia_gr_backend_texture_t *`。
  - label は `const char *` + length にする。NULL は empty label。
- `GrDirectContext::createCompressedBackendTexture` の no-callback allocation overload
  - callback/data upload を伴わない形だけ Phase 2B で扱う。
- `GrDirectContext::deleteBackendTexture`
  - 入力は borrowed `reskia_gr_backend_texture_t *`。
  - C wrapper 自体の delete とは別の GPU resource release であることを header comment に明記する。
- `GrDirectContext::precompileShader`
  - 既存 `SkData` C API handle を受ける。
  - key/data の ownership は borrowed。
- `GrContextThreadSafeProxy::createCharacterization`
  - 下記 `GrSurfaceCharacterization` wrapper を先に追加してから実装する。

Phase 2B は callback を導入しない。Skia 側 overload に callback parameter があっても default null で意味が閉じるものだけを追加する。

## GrSurfaceCharacterization Wrapper

`GrContextThreadSafeProxy::createCharacterization` の戻り値として owned wrapper を追加する。

予定 API:

```c
typedef struct reskia_gr_surface_characterization_t reskia_gr_surface_characterization_t;

reskia_gr_surface_characterization_t *GrSurfaceCharacterization_newCopy(const reskia_gr_surface_characterization_t *src);
void GrSurfaceCharacterization_delete(reskia_gr_surface_characterization_t *characterization);
bool GrSurfaceCharacterization_isValid(const reskia_gr_surface_characterization_t *characterization);
int GrSurfaceCharacterization_width(const reskia_gr_surface_characterization_t *characterization);
int GrSurfaceCharacterization_height(const reskia_gr_surface_characterization_t *characterization);
int GrSurfaceCharacterization_sampleCount(const reskia_gr_surface_characterization_t *characterization);
int GrSurfaceCharacterization_colorType(const reskia_gr_surface_characterization_t *characterization);
reskia_gpu_surface_origin_t GrSurfaceCharacterization_origin(const reskia_gr_surface_characterization_t *characterization);
reskia_gr_backend_format_t *GrSurfaceCharacterization_backendFormat(const reskia_gr_surface_characterization_t *characterization);
```

`createCharacterization` 側は以下を想定する。

```c
reskia_gr_surface_characterization_t *
GrContextThreadSafeProxy_createCharacterization(
    reskia_gr_context_thread_safe_proxy_t *proxy,
    size_t cache_max_resource_bytes,
    const reskia_image_info_t *image_info,
    const reskia_gr_backend_format_t *backend_format,
    int sample_count,
    reskia_gpu_surface_origin_t origin,
    const reskia_surface_props_t *surface_props,
    bool is_mipmapped,
    bool will_use_gl_fbo0,
    bool is_textureable,
    bool is_protected,
    bool vk_rt_supports_input_attachment,
    bool for_vulkan_secondary_command_buffer);
```

NULL input は NULL を返す。Skia が invalid characterization を返した場合も owned wrapper は返してよいが、呼び出し側は `isValid` を確認する。

## Phase 2C: Wrapper 設計待ち

Phase 2C は「API 自体は callback/backend-specific ではないが、戻り値や引数の wrapper 方針を先に固定すべきもの」を扱う。

候補:

- `GrDirectContext::MakeMetal/MakeVulkan` の `GrContextOptions` overload
  - `GrContextOptions` wrapper が必要。
  - 既存の simple factory は `Reskia_GaneshContext_MakeMetal` / `Reskia_GaneshContext_MakeVulkan` が担っている。
- `GrRecordingContext::skCapabilities`
  - `SkCapabilities` は retained wrapper にするか borrowed wrapper にするかを決める。
  - Ganesh/Graphite 共通にできる可能性があるため、GPU context だけで閉じない。

## Phase 2D: Backend-Specific ABI

Phase 2D は backend 固有 struct を C ABI にどう見せるかを固定してから実装する。

対象:

- `GrBackendSemaphore`
- `skgpu::MutableTextureState`
- `GrBackendTexture::getMtlTextureInfo`
- `GrBackendRenderTarget::getMtlTextureInfo`
- Vulkan image layout / queue family index
- native backend texture/render target info

方針:

- C ABI では backend tag を必ず持つ。
- Metal/Vulkan/Dawn/Mock を同じ struct に詰め込まない。
- backend-specific payload は backend ごとの struct に分け、共通 API は opaque wrapper + query に寄せる。
- native pointer を返す場合は borrowed か owned かを API 名と comment に明記する。
- `RESKIA_ENABLE_GPU_*` 無効時は no-op / false / NULL の安定した挙動にする。

## Phase 5A 待ち

以下は callback と resource ownership の共通規約なしに追加しない。

- `GrDirectContext::wait`
  - semaphore delete policy と backend semaphore wrapper が必要。
- `GrDirectContext::updateBackendTexture`
- `GrDirectContext::updateCompressedBackendTexture`
- pixmap/data upload を伴う `createBackendTexture` overload
- finished proc を受ける `createBackendTexture` / `createCompressedBackendTexture` overload

これらは `01-callback-global-registration-design.md` の function pointer + `void *user_data` + release proc 方針を GPU callback に適用してから実装する。

## Triage 更新方針

`public-api-gpu-missing-triage.csv` の P1 残件は、note で以下のいずれかに分類する。

- `Phase 2B`: 次の GPU 実装 batch
- `Phase 2C`: wrapper 設計待ち
- `Phase 2D`: backend-specific ABI 待ち
- `Phase 5A`: callback foundation 待ち
- `Phase 5A or Phase 2D`: data/native state と callback の両方に関係するもの

`covered` になった行は matrix 再生成後に triage から削除する。
