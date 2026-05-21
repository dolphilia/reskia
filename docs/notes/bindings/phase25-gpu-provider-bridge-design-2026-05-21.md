# Phase 25 GPU Provider Bridge Design

Date: 2026-05-21

## Scope

Phase 25 closes the remaining GPU provider rows that can be handled without inventing an unsafe resource lifetime:

- Graphite `ImageProvider::findOrCreate`
- Ganesh `GrExternalTexture` / `GrExternalTextureGenerator`

## Graphite ImageProvider

`ImageProvider::findOrCreate` is safe to expose now because the ownership boundaries are already present in Reskia:

- `Recorder` is an existing borrowed C pointer.
- `SkImage` is an existing borrowed C pointer.
- `SkImage::RequiredProperties` already has a handle table.
- returned `SkImage` can use existing `sk_image_t` ownership.

The C ABI exposes:

- `Graphite_ImageProvider_findOrCreate`: direct call on a borrowed provider; returns caller-owned `sk_image_t`.
- `Graphite_ImageProvider_new`: concrete C callback provider.
- `Graphite_ImageProvider_ref` / `Graphite_ImageProvider_unref`: explicit `SkRefCnt` lifetime.
- `Graphite_RecorderOptions_setImageProvider`: retains a provider into `RecorderOptions`.
- `Graphite_Context_makeRecorderWithOptions`: creates a recorder with provider-bearing options.

Callback ownership:

- The callback receives borrowed `recorder` and `image`.
- The callback receives a temporary `sk_image_required_properties_t` handle that is valid only during the callback.
- If the callback returns a non-zero `sk_image_t`, the bridge consumes it with `static_sk_image_take_entity` and transfers the resulting `sk_sp<SkImage>` to Skia.
- `release_proc` is called once when the provider object is destroyed.

## Ganesh External Texture

`GrExternalTexture` and `GrExternalTextureGenerator` should not be exposed as simple direct wrappers. The public rows are abstract hooks plus generator plumbing, and the useful user-facing API requires a concrete bridge around `SkImages::DeferredFromTextureGenerator`.

Required future bridge shape:

- C callback generator constructor accepting `SkImageInfo`.
- callback for `generateExternalTexture(GrRecordingContext*, Mipmapped)`.
- callback-created external texture object containing:
  - `getBackendTexture` callback returning an owned/copyable `GrBackendTexture` value,
  - mandatory `dispose` callback,
  - user data and release callback.
- factory returning caller-owned `sk_image_t` through `SkImages::DeferredFromTextureGenerator`.

Until that bridge is implemented, the five Ganesh external texture rows are classified as `deferred`, not `na`, because they are real public API gaps with a clear implementation route.
