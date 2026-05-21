# Phase 31 Header / Naming / Ownership Audit

作成時刻: 2026-05-21 20:12:25 JST

## Summary

Phase 31 は、Phase 5A 以降に追加した callback/provider/global registration/GPU bridge の C ABI について、命名・所有権・null policy・callback lifetime の横断ルールを固定する。

結論:

- Phase 31 時点で、coverage freeze を崩す未分類 API はない。
- 直近追加した callback/provider bridge は、`owned`、`borrowed and retained`、`consumes`、`returned pointer owns a ref` の語彙で説明可能。
- 即時修正が必要な ABI 不整合は見つからない。
- 今後の追加では、`release_proc` typedef の再利用、consume 後の handle 無効化、callback-scoped pointer の明記をレビュー項目にする。

## Audited Surface

主に確認した header:

- `skia/capi/sk_gpu_context.h`
- `skia/capi/sk_skottie.h`
- `skia/capi/sk_resources.h`
- `skia/capi/sk_svg_image.h`
- `skia/capi/sk_codec.h`
- `skia/capi/sk_typeface.h`
- `skia/capi/reskia_callback.h`

関連設計 note:

- `docs/notes/bindings/phase20-global-registration-capi-design-2026-05-21.md`
- `docs/notes/bindings/phase23-gpu-provider-async-allocator-design-2026-05-21.md`
- `docs/notes/bindings/phase25-gpu-provider-bridge-design-2026-05-21.md`
- `docs/notes/bindings/public-api-phase28-ganesh-external-texture-bridge-2026-05-21.md`
- `docs/notes/bindings/public-api-phase30-verification-matrix-hardening-2026-05-21.md`

## Naming Rules

Current conventions:

| kind | naming | ownership meaning |
| --- | --- | --- |
| non-refcounted object | `Class_new` / `Class_delete` | caller-owned object, delete releases storage |
| `SkRefCnt` object | `Class_ref` / `Class_unref` / `Class_release` | ref/unref manage Skia refcount; release is the caller-owned release spelling |
| static factory returning refcounted object | `Class_Make...` | result is owned; release/unref/delete per handle family |
| callback bridge object | `Class_new(..., user_data, release_proc)` | bridge owns callback context and releases it once |
| setter retaining callback/provider | `setX(..., x)` comment says `borrowed and retained` | caller keeps its handle; callee holds its own ref |
| C++ ownership transfer | comment says `consumes` | caller must not use/delete the consumed handle afterwards |
| borrowed query | comment says `borrowed` or no release required | caller must not release returned pointer |
| output struct with handles | comment says output handles are caller-owned | caller must release each handle using the documented family |

Observed aliases:

- `Reskia_DirectContext_Release` / `Reskia_GraphiteContext_Release` are legacy/entrypoint release names and coexist with class-style wrappers.
- `Skottie_*_release` and `ImageAsset_release` are consistent for refcounted module objects.
- `TextPropertyValue_delete`, property handle `delete`, and SVG value `delete` are consistent for value/non-refcounted objects.

## Ownership Rules

### Owned return

Owned returns must be explicitly documented in the header comment or obvious from factory naming.

Examples:

- `Graphite_Recorder_snap`: recording object is owned and deleted with `Graphite_Recording_delete`.
- `Graphite_Recorder_clientImageProvider`: provider pointer owns a ref and is released with `Graphite_ImageProvider_unref`.
- `GrExternalTexture_getBackendTexture`: returns an owned backend texture copy.
- `Skottie_ExpressionManager_createNumberExpressionEvaluator`: returned pointer owns a ref and is released with the matching evaluator release.
- `SlotManager_getImageSlot`: returned pointer owns a ref and is released with `ImageAsset_release`.

### Borrowed and retained input

When a setter stores a Skia refcounted object, the C ABI should accept a borrowed input and retain internally. The caller keeps its existing ownership.

Examples:

- `Skottie_AnimationBuilder_setResourceProvider`
- `Skottie_AnimationBuilder_setLogger`
- `Skottie_AnimationBuilder_setMarkerObserver`
- `Skottie_AnimationBuilder_setPrecompInterceptor`
- `Skottie_AnimationBuilder_setPropertyObserver`
- `Skottie_AnimationBuilder_setExpressionManager`
- `TextPropertyValue_setDecorator`
- `SlotManager_setImageSlot`
- `Graphite_RecorderOptions_setImageProvider`
- `CachingResourceProvider_Make`
- `DataURIResourceProviderProxy_Make`

### Consumed input

Consumed handles must not be deleted by the caller after the call returns.

Examples:

- `SkImages_DeferredFromTextureGenerator` consumes `reskia_gr_external_texture_generator_t`.
- `SkTypeface_MakeFromStream` consumes `sk_stream_asset_t`.
- `SkTypeface_Register` callback receives a transferred `sk_stream_asset_t`; the callback must consume/delete it.
- `SkCodec_Register` make callback receives a transferred `sk_stream_t`; the callback must consume/delete it.

Rule: any future consumed API should include `consumes` in the header comment and should have a smoke test that does not double-delete the consumed object.

## Callback Lifetime Rules

Callback/provider bridge objects should follow this model:

1. Bridge constructor receives callback proc, `user_data`, and `release_proc`.
2. `NULL` required callback rejects construction or registration.
3. `release_proc` is called at most once.
4. If Skia owns the bridge through `sk_sp`, explicit C `release` decrements only the caller's ref; Skia may keep the object alive.
5. Callback-scoped pointers are valid only during the callback unless materialized into an owned handle.
6. Async callbacks may run on a different thread. Their payload must be either copied into an owned result object or documented as callback-scoped.

Concrete examples:

- `ExternalTrackAsset_new`: seek callback owner is released when the asset bridge is destroyed.
- `Skottie_PropertyObserver_newWithProperties`: lazy property handles are callback-scoped; materialization returns owned property handles.
- `Skottie_ArrayExpressionEvaluator_evaluate`: `out_values == NULL` / `capacity == 0` is a size query; caller-owned buffer is filled on the second call.
- `Graphite_Recorder_addFinishInfo`: finish callback context is retained by the recording work and released exactly once.
- `Graphite_Context_asyncRescaleAndReadPixels...`: async readback reuses the existing async result callback policy.
- `GrExternalTexture_new`: dispose callback is idempotent; release callback is separate from dispose and is called once on bridge destruction.
- `GrExternalTextureGenerator_new`: generate callback returns an owned external texture object which the bridge consumes into `std::unique_ptr<GrExternalTexture>`.

## Global Registration Rules

Global registrations are not ordinary borrowed callback bridges because upstream lacks unregister APIs.

Rules fixed by Phase 20:

- `SkCodec_Register` and `SkTypeface_Register` reject `NULL` callbacks.
- Replacement releases the previous context once.
- Callback function pointers must remain valid for process lifetime.
- `SkTypeface_Register` fixes the factory id on the first successful registration; later calls must use the same id.
- Tests must replace stack-owned contexts with no-release contexts before process teardown.

Future global registration APIs should not reuse ordinary provider setter wording. They need explicit replacement and process-lifetime policy.

## Null And Output Policy

Stable policy:

- `delete` / `release` / `unref` functions should treat `NULL` as no-op.
- Boolean query with invalid input should usually return `false`.
- Pointer/owned handle return with invalid input should return `NULL` or `0`.
- Numeric query with invalid input should return `0` unless the upstream enum has an established invalid sentinel such as `-1`.
- Output parameters should be required unless the header explicitly says they may be `NULL`.
- Output structs containing handles must state whether each handle is caller-owned.

Representative output-handle cases:

- `ImageAsset_getFrameData`: output handles are caller-owned.
- `SkSVGImage_LoadImage`: `out_info->image` and `out_info->dst` are caller-owned static handles when the function returns true.
- `SlotManager_getVec2Slot`: output `sk_v2_t` handle is caller-owned and deleted with `static_sk_v2_delete`.

## Observations For Future Cleanup

These are not Phase 31 blockers:

- `reskia_graphite_release_proc_t` is semantically equivalent to `reskia_callback_release_proc_t`. It is already ABI-visible, so do not churn it casually, but future callback APIs should prefer the shared `reskia_callback_release_proc_t` unless a backend-specific signature is necessary.
- Some legacy comments mix Japanese and English ownership wording. This is acceptable for existing API, but new callback/provider comments should use the exact terms `owned`, `borrowed`, `borrowed and retained`, `consumes`, and `callback-scoped`.
- `Reskia_*_Release` legacy entrypoints remain part of the ABI. New public-class wrappers should prefer class-style `Class_release` / `Class_delete` naming unless the function is a Reskia convenience entrypoint.

## Phase 31 Closeout

Phase 31 does not require C/C++ code changes.

Before future coverage freeze updates, review new APIs against this checklist:

1. Does every returned pointer/handle state owned vs borrowed?
2. Does every setter that stores an object state borrowed vs retained?
3. Does every consumed input explicitly say `consumes`?
4. Does every callback bridge have one release owner and one release timing?
5. Does every callback-scoped pointer have materialization or a scope note?
6. Does null handling match the surrounding header family?
7. Does the relevant smoke test cover release timing or ownership transfer?
