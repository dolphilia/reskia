# Phase 32 Optional Backend Roadmap

作成時刻: 2026-05-21 20:14:50 JST

## Summary

Phase 29 final freeze では `missing 0` / `deferred 0` を固定した。Phase 32 では、その状態で `na` として閉じている optional/platform backend 行を、将来実装する場合の入口ごとに整理する。

結論:

- Phase 32 時点で portable C ABI coverage に戻すべき optional backend 行はない。
- GPU/platform 系 `na` は実装価値なしではなく、backend build target、native headers、loader/allocator ownership が揃うまで portable coverage から外している。
- 将来実装するなら、D3D/Vulkan/Dawn/Metal allocator/GL loader は同じ phase に混ぜず、backend family ごとに独立した optional bridge と smoke target を作る。

## Current Optional Backend Buckets

`public-api-coverage-matrix.csv` の `na` 198 行のうち、GPU/platform backend roadmap 対象は 77 行。

| bucket | rows | current status |
| --- | ---: | --- |
| D3D optional backend | 17 | current Reskia build targets lack Direct3D support |
| Vulkan optional backend | 29 | Vulkan native headers/types and Vulkan build target required |
| Dawn optional backend | 5 | Dawn/WebGPU C++ types and `RESKIA_ENABLE_GPU_DAWN` build target required |
| GL loader / extension follow-up | 13 | GL function table owner, extension implementation link, and loader policy required |
| Metal allocator optional bridge | 2 | Objective-C Metal allocator provider and `MtlAlloc` lifetime required |
| GPU private/internal control surface | 11 | `priv()` APIs expose internal Skia control surfaces and remain outside stable C ABI |

The remaining 121 `na` rows are non-GPU optional/internal/platform rows and are not implementation backlog for Phase 32.

## D3D Roadmap

Rows:

- `GrBackendSemaphore::initDirect3D`
- `GrBackendSemaphore::getD3DFenceInfo`
- `GrBackendFormat::MakeDxgi`
- `GrBackendFormat::asDxgiFormat`
- `GrBackendTexture` / `GrBackendRenderTarget` D3D resource info/state accessors
- `GrDirectContext::MakeDirect3D`
- `GrD3DMemoryAllocator`
- `GrD3DTextureResourceInfo`
- `GrD3DFenceInfo`

Current decision:

- Keep `na` until a Windows/D3D build target exists.
- Do not emulate these APIs in the portable build.

Implementation prerequisites:

1. Windows CMake build with Skia D3D enabled.
2. Native D3D headers and libraries in the dependency model.
3. C ABI wrappers for `DXGI_FORMAT`, D3D resource state, fence info, and texture resource info.
4. Allocator bridge design if `GrD3DMemoryAllocator` is exposed.
5. D3D smoke target that can at least construct value wrappers and, when hardware/runtime exists, create a context.

Recommended future phase:

- `Phase D3D-1`: value wrappers and context factory.
- `Phase D3D-2`: allocator/provider bridge.

## Vulkan Roadmap

Rows:

- Graphite `VulkanTextureInfo`
- Ganesh `GrVkImageInfo`
- `VulkanExtensions`
- `VulkanAlloc`
- `VulkanYcbcrConversionInfo`
- `VulkanMemoryAllocator`
- Graphite/Ganesh Vulkan semaphore/image accessors

Current decision:

- Keep `na` until a Vulkan build target exists and `include/third_party/vulkan/vulkan/vulkan_core.h` or equivalent headers are available to the Reskia build.
- Treat Vulkan allocator as a native provider bridge, not a simple value wrapper.

Implementation prerequisites:

1. `RESKIA_ENABLE_GPU_VULKAN=ON` build target with Ganesh and/or Graphite.
2. Stable inclusion of Vulkan native headers in `RESKIA_PUBLIC_INCLUDE_DIRS` or an internal-only C ABI shim.
3. Opaque C wrappers for native handles where possible; avoid exposing C++ Vulkan structs directly.
4. `VulkanMemoryAllocator` callback table with allocation, map/unmap, flush/invalidate, free, and memory accounting ownership rules.
5. Smoke target for value wrappers without requiring a physical device, plus optional runtime smoke for actual context creation.

Recommended future phase:

- `Phase Vulkan-1`: native value wrappers and extension queries.
- `Phase Vulkan-2`: allocator bridge.
- `Phase Vulkan-3`: context/semaphore/backend texture runtime smoke.

## Dawn Roadmap

Rows:

- Graphite `DawnTextureInfo` constructors
- `TextureInfo::getDawnTextureInfo`
- `BackendTexture::getDawnTexturePtr`

Current decision:

- Keep `na` until `RESKIA_ENABLE_GPU_DAWN=ON` has a real Graphite/Dawn build target.
- Dawn types are WebGPU C++ runtime types and should not be faked in portable C ABI.

Implementation prerequisites:

1. `RESKIA_ENABLE_GPU_GRAPHITE=ON` and `RESKIA_ENABLE_GPU_DAWN=ON`.
2. Dawn headers/libraries and a clear dependency mode story.
3. C ABI representation for Dawn texture pointer/descriptor fields that does not leak C++ `wgpu::Texture` ownership unsafely.
4. Graphite recorder/context smoke that can validate Dawn texture info compatibility.

Recommended future phase:

- `Phase Dawn-1`: texture info wrappers and compatibility checks.
- `Phase Dawn-2`: runtime Graphite/Dawn smoke.

## GL Loader Roadmap

Rows:

- `GrGLExtensions::init`
- `GrGLExtensions::has` / `remove` / `add` / `dumpJSON`
- `GrGLInterface` constructor/copy/validate/checkError/OOM/error logging/hasExtension/abandon

Current decision:

- Keep `na` until a GL loader bridge and linked `GrGLExtensions.cpp` policy exist.
- Do not expose default `GrGLInterface` objects without a function table owner.

Implementation prerequisites:

1. CMake inclusion of the required GL implementation objects such as `GrGLExtensions.cpp`.
2. `reskia_gr_gl_function_loader_t` or equivalent callback table with release ownership.
3. Clear EGL/display ownership if EGL callbacks are supported.
4. `SkJSONWriter` or replacement output policy for `dumpJSON`.
5. GL smoke target that validates extension set operations without requiring a fully active GL context where possible.

Recommended future phase:

- `Phase GL-1`: extension set link and value/query wrappers.
- `Phase GL-2`: function table loader bridge.
- `Phase GL-3`: diagnostics/error policy.

## Metal Allocator Roadmap

Rows:

- `MtlMemoryAllocator::newBufferWithLength`
- `MtlMemoryAllocator::newTextureWithDescriptor`

Current decision:

- Keep `na` despite existing Metal context support, because allocator exposure is not a value wrapper. It is an Objective-C provider bridge.

Implementation prerequisites:

1. Dedicated optional Metal allocator bridge class.
2. Ownership policy for `id<MTLBuffer>`, `id<MTLTexture>`, `MTLTextureDescriptor`, and `MtlAlloc`.
3. Callback table with exactly-once release.
4. Smoke target that can run both without a Metal device and with a device when available.

Recommended future phase:

- `Phase MetalAllocator-1`: design note and API skeleton.
- `Phase MetalAllocator-2`: runtime bridge and device-gated smoke.

## Private/Internal GPU Control Surfaces

Rows:

- Ganesh `priv()` accessors
- Graphite `priv()` accessors
- Recording/private control surfaces

Current decision:

- Keep `na` permanently for stable public C ABI coverage.
- These expose Skia internal control surfaces rather than stable public class methods suitable for C ABI.

Future action:

- Do not implement direct `priv()` wrappers.
- If a specific internal capability becomes necessary, expose a higher-level stable wrapper around the behavior, not the `priv()` object itself.

## Roadmap Order

Recommended order if optional backend work resumes:

1. GL extension/link cleanup, because it may unlock lightweight diagnostics and does not require a new platform build.
2. Vulkan value wrappers, after a Vulkan build target and headers are available.
3. Dawn value wrappers, after Dawn dependency mode is real.
4. Metal allocator bridge, only if a concrete user need exists.
5. D3D backend, only on a Windows build path.
6. Vulkan/D3D allocator bridges, after value/context runtime smoke exists.

## Phase 32 Closeout

Phase 32 does not change coverage status.

The `na` rows remain intentional. The freeze invariant stays:

- `missing 0`
- `deferred 0`
- `partial 0`
- `overcovered 0`

Future optional backend implementation should add a backend-specific phase override that moves only the implemented rows from `na` to `covered`, with matching smoke coverage and ownership notes.
